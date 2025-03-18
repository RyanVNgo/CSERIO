/** @file img_routines.c
 *  @brief Definitions for image routines
 *  @author Ryan V. Ngo
 */

#include "cserio.h"

#include <stdio.h>


/*-------------------- Hidden Image Symbolic Constants --------------------*/

/* Currently, all SER file frames have just 3 dimensions. */
#define MIN_DIM_IDX 0
#define MAX_DIM_IDX 2

#define DATA_START_SET 178

/*-------------------- Image Routines --------------------*/

/*  @brief Get the number of image frames
 *  @param  sptr        (I)   - Pointer to serfile.
 *  @param  frame_count (IO)  - Pointer to int to set as frame count.
 *  @param  status      (IO)  - Error status.
 *  @return Void.
 */
void ser_get_frame_count(serfile* sptr, int* frame_count, int* status) {
    /* sptr exists */
    if (!sptr) { return (void)(*status = NULL_SPTR); }

    /* frame_count pointer exists */
    if (!frame_count) { return (void)(*status = NULL_PARAM); }

    /* get frame count from header */
    int intern_status= 0;
    int temp_frame_count = 0;
    ser_get_key_record(sptr, &temp_frame_count, FRAMECOUNT_KEY, &intern_status);
    if (intern_status) { return (void)(*status = INTERN_CALL_ERROR); }
    *frame_count = temp_frame_count;

    return;
}

/*  @brief Get the size of a target dimension
 *  @param  sptr    (I)   - Pointer to serfile.
 *  @param  size    (IO)  - Pointer to int to set as size.
 *  @param  dim     (I)   - Dimension to get size of.
 *  @param  status  (IO)  - Error status. 
 *  @return Void
 */
void ser_get_frame_dim_size(serfile* sptr, int* size, DIM_TYPE dim, int* status) {
    if (!sptr) { return (void)(*status = NULL_SPTR); }
    if (!size) { return (void)(*status = NULL_PARAM); }
    if (dim < MIN_DIM_IDX || dim > MAX_DIM_IDX) { return (void)(*status = INVALID_DIM_IDX); }

    int key = 0;
    switch (dim) {
        case 0:
            key = COLORID_KEY;
            break;
        case 1:
            key = IMAGEWIDTH_KEY;
            break;
        case 2:
            key = IMAGEHEIGHT_KEY;
            break;
    }

    /* get size from header */
    int intern_status = 0;
    int temp_size = 0;
    ser_get_key_record(sptr, &temp_size, key, &intern_status);
    if (intern_status) { return (void)(*status = INTERN_CALL_ERROR); }
    *size = temp_size;
    
    /*  If the first dimension is called, then size will
     *  be set to the color ID of the SER, the size of the
     *  dimension is derived from the color ID by the
     *  following case.
     */
    if (key  == COLORID_KEY) {
        *size = *size < 100 ? 1 : 3;
    }

    return;
}

/*  @brief  Returns the number of bytes representing each pixel.
 *
 *  This value returns the total number of bytes to represent
 *  the whole pixel value. Meaning SER files in a multi-plane
 *  format like RGB or BGR includes all color layers in the
 *  byte size.
 *
 *  @param  sptr            (I)   - Pointer to serfile.
 *  @param  bytes_per_pixel (IO)  - Pointer to long to set.
 *  @param  status          (IO)  - Error status.
 *  @return Error status.
 */
void ser_get_bytes_per_pixel(serfile* sptr, unsigned long* bytes_per_pixel, int* status) {
    if (!sptr) { return (void)(*status = NULL_SPTR); }
    if (!bytes_per_pixel) { return (void)(*status = NULL_PARAM); }

    int intern_status = 0;
    int color_ID = 0;
    ser_get_key_record(sptr, &color_ID, COLORID_KEY, &intern_status);
    if (intern_status) { return (void)(*status = INTERN_CALL_ERROR); }
    int number_of_planes = color_ID < 100? 1 : 3;

    int pixel_depth = 0;
    ser_get_key_record(sptr, &pixel_depth, PIXELDEPTHPERPLANE_KEY, &intern_status);
    if (intern_status) { return (void)(*status = INTERN_CALL_ERROR); }

    if (pixel_depth <= 8) {
        *bytes_per_pixel = number_of_planes; /* 1 byte per pixel */
    } else {
        *bytes_per_pixel = number_of_planes * 2; /* 2 bytes per pixel */
    }

    return;
}

/** @brief  Returns the byte size of a single frame
 *  @param  sptr        (I)   - Pointer to serfile.
 *  @param  byte_size   (IO)  - Pointer to long to set.
 *  @param  status      (IO)  - Error status.
 *  @return Error status.
 */
void ser_get_frame_byte_size(serfile* sptr, unsigned long* byte_size, int* status) {
    if (!sptr) { return (void)(*status = NULL_SPTR); }
    if (!byte_size) { return (void)(*status = NULL_PARAM); }

    int intern_status = 0;
    unsigned long bytes_per_pixel = 0;
    ser_get_bytes_per_pixel(sptr, &bytes_per_pixel, &intern_status);
    if (intern_status) { return (void)(*status = INTERN_CALL_ERROR); }

    int width = 0;
    ser_get_key_record(sptr, &width, IMAGEWIDTH_KEY, &intern_status);
    if (intern_status) { return (void)(*status = INTERN_CALL_ERROR); }

    int height = 0;
    ser_get_key_record(sptr, &height, IMAGEHEIGHT_KEY, &intern_status);
    if (intern_status) { return (void)(*status = INTERN_CALL_ERROR); }

    *byte_size = bytes_per_pixel * width * height;

    return;
}

/*  @brief  Read the image frame at the index.
 *  
 *  Note that this function returns the entire data entry for
 *  the target frame. Ensure that the dest buffer can store
 *  the entire frame. Function uses 0 based indexing.
 *
 *  @param  sptr    (I)   - Pointer to serfile.
 *  @param  dest    (IO)  - Pointer to destination buffer.
 *  @param  idx     (I)   - Index of the frame.
 *  @param  status  (IO)  - Error status. 
 *  @return Error status.
 */
void ser_read_frame(serfile* sptr, void* dest, int idx, int* status) {
    if (!sptr) { return (void)(*status = NULL_SPTR); }
    if (!dest) { return (void)(*status = NULL_DEST_BUFF); }

    int intern_status = 0;
    int frame_count = 0;
    ser_get_key_record(sptr, &frame_count, FRAMECOUNT_KEY, &intern_status);
    if (intern_status) { return (void)(*status = INTERN_CALL_ERROR); }

    if (idx < 0 || idx >= frame_count) { return (void)(*status = INVALID_FRAME_IDX); }

    unsigned long frame_byte_size = 0;
    ser_get_frame_byte_size(sptr, &frame_byte_size, &intern_status);
    if (intern_status) { return (void)(*status = INTERN_CALL_ERROR); }

    unsigned long frame_offset = DATA_START_SET + (frame_byte_size * idx);
    fseek(sptr->SER_file->s_file, frame_offset, SEEK_SET);

    int bytes_read = 0;
    bytes_read = fread(dest, 1, frame_byte_size, sptr->SER_file->s_file);

    if (bytes_read < frame_byte_size) {
        if (feof(sptr->SER_file->s_file)) { *status = EOF_ERROR; }
        if (ferror(sptr->SER_file->s_file)) { *status = FREAD_ERROR; }
    }

    return;
}

