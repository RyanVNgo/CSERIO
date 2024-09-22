/** @file img_routines.c
 *  @brief Definitions for image routines
 *
 *  @author Ryan V. Ngo
 */

#include "cserio.h"
#include "errors.h"

/*-------------------- Hidden Image Symbolic Constants --------------------*/

/**
 *  Currently, all SER file frames have just 3 dimensions.
 */
#define MIN_DIM_IDX 0
#define MAX_DIM_IDX 2

/*-------------------- Image Routines --------------------*/

/** @brief Get the number of image frames
 *
 *  @param  sptr        (I) - Pointer to serfile.
 *  @param  frame_count (IO) - Pointer to int to set as frame count.
 *  @param  status      (IO) - Error status.
 *  @return Error status.
 */
int ser_get_frame_count(serfile* sptr, int* frame_count, int* status) {
    /* sptr exists */
    if (!sptr) {
        *status = NULL_SPTR;
        return (*status);
    }

    /* frame_count pointer exists */
    if (!frame_count) {
        *status = NULL_PARAM;
        return (*status);
    }

    /* get frame count from header */
    int intern_status= 0;
    int temp_frame_count = 0;
    ser_get_key_record(sptr, &temp_frame_count, FRAMECOUNT_KEY, &intern_status);
    if (intern_status) {
        *status = INTERN_CALL_ERROR;
        return (*status);
    }
    *frame_count = temp_frame_count;

    return (*status);
}

/** @brief Get the size of a target dimension
 *
 *  @param  sptr    (I) - Pointer to serfile.
 *  @param  size    (IO) - Pointer to int to set as size.
 *  @param  dim     (I) - Dimension to get size of.
 *  @param  status  (IO) - Error status. 
 *  @return Error status.
 */
int ser_get_frame_size(serfile* sptr, int* size, DIM_TYPE dim, int* status) {
    /* sptr exists */
    if (!sptr) {
        *status = NULL_SPTR;
        return (*status);
    }

    /* size pointer exists */
    if (!size) {
        *status = NULL_PARAM;
        return (*status);
    }

    /* invalid dimension index */
    if (dim < MIN_DIM_IDX || dim > MAX_DIM_IDX) {
        *status = INVALID_DIM_IDX;
        return (*status);
    }

    /* get dimension key */
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
    if (intern_status) {
        *status = INTERN_CALL_ERROR;
        return (*status);
    }
    *size = temp_size;
    
    /**
     *  If the first dimension is called, then size will
     *  be set to the color ID of the SER, the size of the
     *  dimension is derived from the color ID by the
     *  following case.
     */
    if (key  == COLORID_KEY) {
        *size = *size < 100 ? 1 : 3;
    }

    return (*status);
}

/** @brief  Read the image frame at the index.
 *  
 *  Note that this function returns the entire data entry for
 *  the target frame. Ensure that the dest buffer can store
 *  the entire frame.
 *
 *  @param  sptr    (I) - Pointer to serfile.
 *  @param  dest    (IO) - Pointer to destination buffer.
 *  @param  idx     (I) - Index of the frame.
 *  @param  status  (IO) - Error status. 
 *  @return Error status.
 */
int ser_read_frame(serfile* sptr, void* dest, int idx, int* status) {
    /* sptr exists */
    if (!sptr) {
        *status = NULL_SPTR;
        return (*status);
    }

    /* destination buffer exists */
    if (!dest) {
        *status = NULL_DEST_BUFF;
        return (*status);
    }

    /* get the frame count */
    int intern_status = 0;
    int frame_count = 0;
    ser_get_key_record(sptr, &frame_count, FRAMECOUNT_KEY, &intern_status);
    if (intern_status) {
        *status = INTERN_CALL_ERROR;
        return (*status);
    }

    /* invalid frame index */
    if (idx < 0 || idx >= frame_count) {
        *status = INVALID_FRAME_IDX;
        return (*status);
    }



    return (*status);
}
