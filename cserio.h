/** @file   cserio.h
 *  @brief  Library definitions and function implementations.
 *
 *  This file contains all library definitions and function 
 *  implementations for the CSERIO library.
 *
 *  @author Ryan V. Ngo
 */

#ifndef CSERIO_H
#define CSERIO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


/*-------------------- CSERIO Version --------------------*/

#define CSERIO_MAJOR    2
#define CSERIO_MINOR    0
#define CSERIO_MICRO    0

/*-------------------- Core Errors --------------------*/

#define NO_ERROR            0

#define MEM_ALLOC           101
#define NULL_SPTR           102
#define NULL_DEST_BUFF      103
#define NULL_PARAM          104

#define EOF_ERROR           110
#define FREAD_ERROR         111
#define READ_ERROR          112

#define INTERN_CALL_ERROR   121

#define WRITE_ON_READONLY   131

/*-------------------- File Access Errors --------------------*/

#define NULL_FILENAME       201
#define INVALID_FILENAME    202

#define FILE_OPEN_ERROR     211
#define FILE_CLOSE_ERROR    212

/*-------------------- Header Routine Errors --------------------*/

#define INVALID_HDR_IDX     301
#define INVALID_HDR_KEY     302

#define HDR_WRITE_WARN       311

/*-------------------- Image Routine Errors --------------------*/

#define INVALID_DIM_IDX     401
#define INVALID_FRAME_IDX   402

/*-------------------- SER File Symbolic Constants --------------------*/

#define SER_EXT ".ser"
#define SER_EXT_LEN 4

/*-------------------- SER File IO Modes --------------------*/

#define READONLY 0
#define READWRITE 1

/*-------------------- Header Types --------------------*/

typedef char* S_STRING;
typedef int32_t S_INT32;
typedef int64_t S_INT64;

/*-------------------- Header Symbolic Constants --------------------*/

#define HDR_UNIT_COUNT 13

/*  These constants represent the byte length of each header component
 *  for V3 SER files.
 *
 *  Note that these values represent the byte length as they are in the
 *  SER file.
 */
#define FILEID_LEN              14
#define LUID_LEN                4
#define COLORID_LEN             4
#define LITTLEENDIAN_LEN        4 
#define IMAGEWIDTH_LEN          4 
#define IMAGEHEIGHT_LEN         4 
#define PIXELDEPTHPERPLANE_LEN  4 
#define FRAMECOUNT_LEN          4 
#define OBSERVER_LEN            40 
#define INSTRUMENT_LEN          40 
#define TELESCOPE_LEN           40 
#define DATETIME_LEN            8 
#define DATETIMEUTC_LEN         8 

/*  The following functionally operate as the byte index position 
 *  within the SER file.
 */
#define FILEID_KEY              0
#define LUID_KEY                14
#define COLORID_KEY             18
#define LITTLEENDIAN_KEY        22
#define IMAGEWIDTH_KEY          26
#define IMAGEHEIGHT_KEY         30
#define PIXELDEPTHPERPLANE_KEY  34
#define FRAMECOUNT_KEY          38
#define OBSERVER_KEY            42
#define INSTRUMENT_KEY          82
#define TELESCOPE_KEY           122
#define DATETIME_KEY            162
#define DATETIMEUTC_KEY         170

/* Color ID types */
#define MONO          0
#define BAYER_RGGB    8
#define BAYER_GRBG    9
#define BAYER_GBRG    10
#define BAYER_BGGR    11
#define BAYER_CYYM    16
#define BAYER_YCMY    17
#define BAYER_YMCY    18
#define BAYER_MYYC    19
#define RGB           100
#define BGR           101

/* Little Endian types */
#define LITTLEENDIAN_TRUE   1
#define LITTLEENDIAN_FALSE  0


/*-------------------- Image Symbolic Constants --------------------*/

typedef int DIM_TYPE;
#define DIM_LAYER   0
#define DIM_WIDTH   1
#define DIM_HEIGHT  2

/*-------------------- SER Structure --------------------*/

/*  SERfile is the core data structure that permits the access and
 *  modification of SER files. This structure should not be directly
 *  utilized by the user.
 */
typedef struct SERfile {
  void* io_context;
  size_t (*reader)(void* io_context, void* buffer, size_t size, size_t offset);
  size_t (*writer)(void* io_context, void* data, size_t size, size_t offset);
  int access_mode;
} SERfile;


/*  serfile is the primary data structure that users should utilize
 *  to interact with SER files. This structure should only be utilized
 *  and modified by methods provided in this library. Utilization and
 *  modificaiton of this structure by the user should be considered
 *  undefined behavior.
 */
typedef struct serfile {
  SERfile* SER_file;
} serfile;



/*------------------------------------------------------------------*/
/* CSERIO Definitions */ 
/*------------------------------------------------------------------*/

/*-------------------- Core Routines --------------------*/

void cserio_version_number(int* major, int* minor, int* micro);

/*-------------------- File Access Routines --------------------*/

void ser_open_file(serfile** sptr, char* filename, int mode, int* status);
void ser_close_file(serfile* sptr, int* status);

/*-------------------- Memory Access Routines --------------------*/

void ser_open_memory(serfile** sptr, uint8_t* data, size_t size, int* status);
void ser_close_memory(serfile* sptr, int* status);

/*-------------------- Header Routines --------------------*/

void ser_get_hdr_count(serfile* sptr, int* rec_count, int* status);
void ser_get_idx_record(serfile* sptr, void* dest, int idx, int* status);
void ser_get_key_record(serfile* sptr, void* dest, int key, int* status);

void ser_write_idx_record(serfile* sptr, void* data, int idx, size_t size, int* status);
void ser_write_key_record(serfile* sptr, void* data, int key, size_t size, int* status);

/*-------------------- Image Routines --------------------*/

void ser_get_frame_count(serfile* sptr, int* frame_count, int* status);
void ser_get_frame_dim_size(serfile* sptr, int* size, int dim, int* status);

void ser_get_bytes_per_pixel(serfile* sptr, unsigned long* bytes_per_pixel, int* status); 
void ser_get_frame_byte_size(serfile* sptr, unsigned long* byte_size, int* status);

void ser_read_frame(serfile* sptr, void* dest, int idx, int* status);


/*------------------------------------------------------------------*/
/* Testing Components */ 
/*------------------------------------------------------------------*/

/*
#define SER_TESTING
#define CSERIO_IMPLEMENTATION
*/


#if defined(SER_TESTING)

typedef struct {
  uint8_t* data;
  size_t size;
} serMem;

static size_t ser_memory_read(void* io_context, void* buffer, size_t size, size_t offset) {
  serMem* memory_io = (serMem*)(io_context);

  if (memory_io->size < offset) {
    return 0;
  }

  if (memory_io->size < offset + size) {
    size_t cut_size = memory_io->size - offset;
    memcpy(buffer, memory_io->data + offset, cut_size);
    return cut_size;
  }

  memcpy(buffer, memory_io->data + offset, size);

  return size;
}

static size_t ser_memory_write(void* io_context, void* data, size_t size, size_t offset) {
  serMem* memory_io = (serMem*)(io_context);

  if (memory_io->size < offset) {
    return 0;
  }

  if (memory_io->size < offset + size) {
    size_t cut_size = memory_io->size - offset;
    memcpy(memory_io->data + offset, data, cut_size);
    return cut_size;
  }

  memcpy(memory_io->data + offset, data, size);

  return size;
}

void ser_open_memory(serfile** sptr, uint8_t* data, size_t size, int* status) {
    if (!sptr) {
      return (void)(*status = NULL_SPTR);
    }

    *sptr = (serfile*)malloc(sizeof(serfile));
    if (!*sptr) {
        return (void)(*status = MEM_ALLOC);
    }


    (*sptr)->SER_file = (SERfile*)malloc(sizeof(SERfile));
    if (!(*sptr)->SER_file) {
        free(*sptr);
        return (void)(*status = MEM_ALLOC);
    }

    serMem* ser_data = (serMem*)malloc(sizeof(serMem));
    ser_data->data = data;
    ser_data->size = size;

    (*sptr)->SER_file->io_context = ser_data;
    (*sptr)->SER_file->reader = ser_memory_read;
    (*sptr)->SER_file->writer = ser_memory_write;
    (*sptr)->SER_file->access_mode = READWRITE;

    return;
}

void ser_close_memory(serfile* sptr, int* status) {
    if (!sptr) { 
      return (void)(*status = NULL_SPTR); 
    }

    free(sptr->SER_file);
    free(sptr);
    sptr = NULL;

    return;
}

#endif

/*------------------------------------------------------------------*/
/* CSERIO Implementation */ 
/*------------------------------------------------------------------*/

#if defined(CSERIO_IMPLEMENTATION)

/*-------------------- Internal Helpers --------------------*/

static size_t ser_file_read(void* io_context, void* buffer, size_t size, size_t offset) {
  FILE* file_io = (FILE*)io_context;
  fseek(file_io, offset, SEEK_SET);
  return fread(buffer, 1, size, file_io);
}

static size_t ser_file_write(void* io_context, void* data, size_t size, size_t offset) {
  FILE* file_io = (FILE*)io_context;
  fseek(file_io, offset, SEEK_SET);
  return fwrite(data, 1, size, file_io);
}

/*-------------------- Core Routines --------------------*/

/*  @brief  Provides the Major, Minor, and Micro numbers for
 *          the current version of CSERIO.
 *  @param  major     (IO)  - Pointer to Major int.
 *  @param  minor     (IO)  - Pointer to Minor int.
 *  @param  micro     (IO)  - Pointer to Micro int.
 *  @return Void.
 */
void cserio_version_number(int* major, int* minor, int* micro) {
    if (major) {
      *major = CSERIO_MAJOR;
    }
    if (minor) {
      *minor = CSERIO_MINOR;
    }
    if (micro) {
      *micro = CSERIO_MICRO;
    }
    return;
}

/*-------------------- File Access Routines --------------------*/

/*  @brief  Opens SER file
 *
 *  The memory for the serfile structure is automatically allocated
 *  on file open and freed on file close.
 *
 *  @param  sptr      (IO)  - Pointer to a pointer of a serfile.
 *  @param  filename  (I)   - root name of the SER file to open.
 *  @param  mode      (I)   - Access type, either READONLY or READWRITE.
 *  @param  status    (IO)  - Error status.
 *  @return Void.
 */
void ser_open_file(serfile** sptr, char* filename, int mode, int* status) {
    if (!sptr) {
      return (void)(*status = NULL_SPTR);
    }

    if (!filename) {
      return (void)(*status = NULL_FILENAME);
    }

    char* ext = strrchr(filename, '.');
    if (!ext || strncmp(ext, SER_EXT, SER_EXT_LEN)) {
        return (void)(*status = INVALID_FILENAME);
    }

    FILE* ser_file;
    if (mode == READWRITE) {
        ser_file = fopen(filename, "r+");
    } else {
        ser_file = fopen(filename, "r"); /* default behavior */
    }

    if (!ser_file) {
        return (void)(*status = FILE_OPEN_ERROR);
    }

    *sptr = (serfile*)malloc(sizeof(serfile));
    if (!*sptr) {
        fclose(ser_file);
        return (void)(*status = MEM_ALLOC);
    }

    (*sptr)->SER_file = (SERfile*)malloc(sizeof(SERfile));
    if (!(*sptr)->SER_file) {
        fclose(ser_file);
        free(*sptr);
        return (void)(*status = MEM_ALLOC);
    }

    (*sptr)->SER_file->io_context = ser_file;
    (*sptr)->SER_file->reader = ser_file_read;
    (*sptr)->SER_file->writer = ser_file_write;
    (*sptr)->SER_file->access_mode = mode;

    return;
}

/*  @brief  Close SER file
 *
 *  Closes the serfile and frees the structure. Parameter sptr will
 *  be set to NULL.
 *
 *  @param  sptr      (IO)  - Pointer to a serfile.
 *  @param  status    (IO)  - Error status.
 *  @return Void.
 */
void ser_close_file(serfile* sptr, int* status) {
    if (!sptr) { 
      return (void)(*status = NULL_SPTR); 
    }

    if (!sptr->SER_file->io_context || fclose((FILE*)sptr->SER_file->io_context)) {
        *status = FILE_CLOSE_ERROR;
    }

    free(sptr->SER_file);
    free(sptr);
    sptr = NULL;

    return;
}

/*-------------------- Header Routines --------------------*/

/*  @brief  Returns number of records in the header
 *
 *  Assigns passed hdr_count integer with number of records
 *  in the header. (Note that as of Version 3 SER files, the
 *  number of records in a header is a constant 13 which makes
 *  up the first 178 bytes of data)
 *
 *  @param  sptr        (I)   - Pointer to serfile
 *  @param  rec_count   (IO)  - Number of records
 *  @param  status      (IO)  - Error status.
 *  @return Void.
 */
void ser_get_hdr_count(serfile* sptr, int* rec_count, int* status) {
    if (!sptr) { 
      return (void)(*status = NULL_SPTR); 
    }

    if (!rec_count) { 
      return (void)(*status = NULL_PARAM); 
    }

    *rec_count = HDR_UNIT_COUNT;
    return;
}

/*  @brief  Return data at header idx 
 *  
 *  Ensure that the dest buff to which the data will be written
 *  to has enough space to store the data. Refer to the defines in
 *  cserio.h or follow the LEN_(key) format. Note that this method
 *  does a raw data copy to the dest buffer, no conversion is done.
 *
 *  @param  sptr    (I)   - Pointer to serfile
 *  @param  dest    (IO)  - Destination buffer for header data
 *  @param  idx     (I)   - Record index of data to fetch
 *  @param  status  (IO)  - Error status.
 *  @return Void.
 */
void ser_get_idx_record(serfile* sptr, void* dest, int idx, int* status) {
    if (!sptr) { return (void)(*status = NULL_SPTR); }
    if (!dest) { return (void)(*status = NULL_DEST_BUFF); }

    if (idx < 0 || idx >= HDR_UNIT_COUNT) { return (void)(*status = INVALID_HDR_IDX); }

    int byte_len = 0;
    int fpos = 0;
    switch (idx) {
        case 0:
            byte_len = FILEID_LEN;
            fpos = FILEID_KEY;
            break;
        case 1:
            byte_len = LUID_LEN;
            fpos = LUID_KEY;
            break;
        case 2:
            byte_len = COLORID_LEN;
            fpos = COLORID_KEY;
            break;
        case 3:
            byte_len = LITTLEENDIAN_LEN;
            fpos = LITTLEENDIAN_KEY;
            break;
        case 4:
            byte_len = IMAGEWIDTH_LEN;
            fpos = IMAGEWIDTH_KEY;
            break;
        case 5:
            byte_len = IMAGEHEIGHT_LEN;
            fpos = IMAGEHEIGHT_KEY;
            break;
        case 6:
            byte_len = PIXELDEPTHPERPLANE_LEN;
            fpos = PIXELDEPTHPERPLANE_KEY;
            break;
        case 7:
            byte_len = FRAMECOUNT_LEN;
            fpos = FRAMECOUNT_KEY;
            break;
        case 8:
            byte_len = OBSERVER_LEN;
            fpos = OBSERVER_KEY;
            break;
        case 9:
            byte_len = INSTRUMENT_LEN;
            fpos = INSTRUMENT_KEY;
            break;
        case 10:
            byte_len = TELESCOPE_LEN;
            fpos = TELESCOPE_KEY;
            break;
        case 11:
            byte_len = DATETIME_LEN;
            fpos = DATETIME_KEY;
            break;
        case 12:
            byte_len = DATETIMEUTC_LEN;
            fpos = DATETIMEUTC_KEY;
            break;
    }
    
    SERfile* sfile = sptr->SER_file;
    int bytes_read = sfile->reader(sfile->io_context, dest, byte_len, fpos);
    if (bytes_read < byte_len) {
      *status = READ_ERROR;
    }

    return;
}

/*  @brief  Return data at header key
 *
 *  Ensure that the dest buff to which the data will be written
 *  to has enough space to store the data. Refer to the defines in
 *  header_routines.h or follow the (key)_LEN format.
 *
 *  @param  sptr    (I)   - Pointer to serfile
 *  @param  dest    (IO)  - Destination buffer for header data
 *  @param  key     (I)   - Record key of data to fetch
 *  @param  status  (IO)  - Error status.
 *  @return Void.
 */
void ser_get_key_record(serfile* sptr, void* dest, int key, int* status) {
    if (!sptr) { return (void)(*status = NULL_SPTR); }
    if (!dest) { return (void)(*status = NULL_DEST_BUFF); }

    int byte_len = 0;
    switch (key) {
        case FILEID_KEY:
            byte_len = FILEID_LEN;
            break;
        case LUID_KEY:
            byte_len = LUID_LEN;
            break;
        case COLORID_KEY:
            byte_len = COLORID_LEN;
            break;
        case LITTLEENDIAN_KEY:
            byte_len = LITTLEENDIAN_LEN;
            break;
        case IMAGEWIDTH_KEY:
            byte_len = IMAGEWIDTH_LEN;
            break;
        case IMAGEHEIGHT_KEY:
            byte_len = IMAGEHEIGHT_LEN;
            break;
        case PIXELDEPTHPERPLANE_KEY:
            byte_len = PIXELDEPTHPERPLANE_LEN;
            break;
        case FRAMECOUNT_KEY:
            byte_len = FRAMECOUNT_LEN;
            break;
        case OBSERVER_KEY:
            byte_len = OBSERVER_LEN;
            break;
        case INSTRUMENT_KEY:
            byte_len = INSTRUMENT_LEN;
            break;
        case TELESCOPE_KEY:
            byte_len = TELESCOPE_LEN;
            break;
        case DATETIME_KEY:
            byte_len = DATETIME_LEN;
            break;
        case DATETIMEUTC_KEY:
            byte_len = DATETIMEUTC_LEN;
            break;
        default:
            byte_len = 0;
    }
    
    if (byte_len == 0) { 
      return (void)(*status = INVALID_HDR_KEY); 
    }

    SERfile* sfile = sptr->SER_file;
    int bytes_read = sfile->reader(sfile->io_context, dest, byte_len, key);

    if (bytes_read < byte_len) {
      *status = READ_ERROR;
    }

    return;
}

/** @brief  Write data to header idx 
 *  
 *  This write routine is capped such that it will write less
 *  than or up to the maximum size of the header record space.
 *
 *  @param  sptr    (I)     - Pointer to serfile
 *  @param  data    (IO)    - Pointer to data to write 
 *  @param  idx     (I)     - Header record index
 *  @param  size    (I)     - Size of data in bytes
 *  @param  status  (IO)    - Error status.
 *  @return Error status.
 */
void ser_write_idx_record(serfile* sptr, void* data, int idx, size_t size, int* status) {
    if (!sptr) { return (void)(*status = NULL_SPTR); }
    if (!data) { return (void)(*status = NULL_PARAM); }
    if (idx < 0 || idx >= HDR_UNIT_COUNT) { return (void)(*status = INVALID_HDR_IDX); }
    if (sptr->SER_file->access_mode != READWRITE) { return (void)(*status = WRITE_ON_READONLY); }

    size_t max_byte_len = 0;
    int fpos = 0;
    switch (idx) {
        case 0:
            max_byte_len = FILEID_LEN;
            fpos = FILEID_KEY;
            break;
        case 1:
            max_byte_len = LUID_LEN;
            fpos = LUID_KEY;
            break;
        case 2:
            max_byte_len = COLORID_LEN;
            fpos = COLORID_KEY;
            break;
        case 3:
            max_byte_len = LITTLEENDIAN_LEN;
            fpos = LITTLEENDIAN_KEY;
            break;
        case 4:
            max_byte_len = IMAGEWIDTH_LEN;
            fpos = IMAGEWIDTH_KEY;
            break;
        case 5:
            max_byte_len = IMAGEHEIGHT_LEN;
            fpos = IMAGEHEIGHT_KEY;
            break;
        case 6:
            max_byte_len = PIXELDEPTHPERPLANE_LEN;
            fpos = PIXELDEPTHPERPLANE_KEY;
            break;
        case 7:
            max_byte_len = FRAMECOUNT_LEN;
            fpos = FRAMECOUNT_KEY;
            break;
        case 8:
            max_byte_len = OBSERVER_LEN;
            fpos = OBSERVER_KEY;
            break;
        case 9:
            max_byte_len = INSTRUMENT_LEN;
            fpos = INSTRUMENT_KEY;
            break;
        case 10:
            max_byte_len = TELESCOPE_LEN;
            fpos = TELESCOPE_KEY;
            break;
        case 11:
            max_byte_len = DATETIME_LEN;
            fpos = DATETIME_KEY;
            break;
        case 12:
            max_byte_len = DATETIMEUTC_LEN;
            fpos = DATETIMEUTC_KEY;
            break;
    }

    if (size > max_byte_len) {
      size = max_byte_len;
    }

    SERfile* sfile = sptr->SER_file;
    size_t bytes_written = sfile->writer(sfile->io_context, data, size, fpos);
    if (bytes_written != size) {
      *status = HDR_WRITE_WARN;
    }

    return;
}


/** @brief  Write data to header key
 *  
 *  This write routine is capped such that it will write less
 *  than or up to the maximum size of the header record space.
 *
 *  @param  sptr    (I)     - Pointer to serfile
 *  @param  data    (IO)    - Pointer to data to write 
 *  @param  key     (I)     - Record key
 *  @param  size    (I)     - Size of data in bytes
 *  @param  status  (IO)    - Error status.
 *  @return Void.
 */
void ser_write_key_record(serfile* sptr, void* data, int key, size_t size, int* status) {
    if (!sptr) { return (void)(*status = NULL_SPTR); }
    if (!data) { return (void)(*status = NULL_PARAM); }
    if (sptr->SER_file->access_mode != READWRITE) { return (void)(*status = WRITE_ON_READONLY); }

    int max_byte_len = 0;
    switch (key) {
        case FILEID_KEY:
            max_byte_len = FILEID_LEN;
            break;
        case LUID_KEY:
            max_byte_len = LUID_LEN;
            break;
        case COLORID_KEY:
            max_byte_len = COLORID_LEN;
            break;
        case LITTLEENDIAN_KEY:
            max_byte_len = LITTLEENDIAN_LEN;
            break;
        case IMAGEWIDTH_KEY:
            max_byte_len = IMAGEWIDTH_LEN;
            break;
        case IMAGEHEIGHT_KEY:
            max_byte_len = IMAGEHEIGHT_LEN;
            break;
        case PIXELDEPTHPERPLANE_KEY:
            max_byte_len = PIXELDEPTHPERPLANE_LEN;
            break;
        case FRAMECOUNT_KEY:
            max_byte_len = FRAMECOUNT_LEN;
            break;
        case OBSERVER_KEY:
            max_byte_len = OBSERVER_LEN;
            break;
        case INSTRUMENT_KEY:
            max_byte_len = INSTRUMENT_LEN;
            break;
        case TELESCOPE_KEY:
            max_byte_len = TELESCOPE_LEN;
            break;
        case DATETIME_KEY:
            max_byte_len = DATETIME_LEN;
            break;
        case DATETIMEUTC_KEY:
            max_byte_len = DATETIMEUTC_LEN;
            break;
        default:
            max_byte_len = 0;
    }
    
    if (max_byte_len == 0) { 
      return (void)(*status = INVALID_HDR_KEY); 
    }

    if (size > max_byte_len) {
      size = max_byte_len;
    }

    SERfile* sfile = sptr->SER_file;
    size_t bytes_written = sfile->writer(sfile->io_context, data, size, key);
    if (bytes_written != size) {
      *status = HDR_WRITE_WARN;
    }

    return;
}

/*-------------------- Image Symbolic Constants --------------------*/

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
    if (!sptr) { 
      return (void)(*status = NULL_SPTR); 
    }

    if (!frame_count) { 
      return (void)(*status = NULL_PARAM); 
    }

    /* get frame count from header */
    int intern_status = 0;
    int temp_frame_count = 0;
    ser_get_key_record(sptr, &temp_frame_count, FRAMECOUNT_KEY, &intern_status);

    if (intern_status) { 
      return (void)(*status = INTERN_CALL_ERROR); 
    }
    
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
    if (!sptr) { 
      return (void)(*status = NULL_SPTR); 
    }

    if (!size) { 
      return (void)(*status = NULL_PARAM); 
    }

    if (dim < MIN_DIM_IDX || dim > MAX_DIM_IDX) { 
      return (void)(*status = INVALID_DIM_IDX); 
    }

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
      return (void)(*status = INTERN_CALL_ERROR); 
    }
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
    if (!sptr) { 
      return (void)(*status = NULL_SPTR); 
    }

    if (!bytes_per_pixel) { 
      return (void)(*status = NULL_PARAM); 
    }

    int intern_status = 0;
    int color_ID = 0;
    ser_get_key_record(sptr, &color_ID, COLORID_KEY, &intern_status);
    if (intern_status) { 
      return (void)(*status = INTERN_CALL_ERROR); 
    }
    int number_of_planes = color_ID < 100? 1 : 3;

    int pixel_depth = 0;
    ser_get_key_record(sptr, &pixel_depth, PIXELDEPTHPERPLANE_KEY, &intern_status);
    if (intern_status) { 
      return (void)(*status = INTERN_CALL_ERROR); 
    }

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
    if (!sptr) { 
      return (void)(*status = NULL_SPTR); 
    }

    if (!byte_size) { 
      return (void)(*status = NULL_PARAM); 
    }

    int intern_status = 0;
    unsigned long bytes_per_pixel = 0;
    ser_get_bytes_per_pixel(sptr, &bytes_per_pixel, &intern_status);
    if (intern_status) { 
      return (void)(*status = INTERN_CALL_ERROR); 
    }

    int width = 0;
    ser_get_key_record(sptr, &width, IMAGEWIDTH_KEY, &intern_status);
    if (intern_status) { 
      return (void)(*status = INTERN_CALL_ERROR); 
    }

    int height = 0;
    ser_get_key_record(sptr, &height, IMAGEHEIGHT_KEY, &intern_status);
    if (intern_status) { 
      return (void)(*status = INTERN_CALL_ERROR); 
    }

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
    if (!sptr) { 
      return (void)(*status = NULL_SPTR); 
    }

    if (!dest) { 
      return (void)(*status = NULL_DEST_BUFF); 
    }

    int intern_status = 0;
    int frame_count = 0;
    ser_get_key_record(sptr, &frame_count, FRAMECOUNT_KEY, &intern_status);
    if (intern_status) { 
      return (void)(*status = INTERN_CALL_ERROR); 
    }

    if (idx < 0 || idx >= frame_count) {
      return (void)(*status = INVALID_FRAME_IDX); 
    }

    unsigned long frame_byte_size = 0;
    ser_get_frame_byte_size(sptr, &frame_byte_size, &intern_status);
    if (intern_status) { 
      return (void)(*status = INTERN_CALL_ERROR); 
    }

    unsigned long frame_offset = DATA_START_SET + (frame_byte_size * idx);

    SERfile* sfile = sptr->SER_file;
    int bytes_read = sfile->reader(sfile->io_context, dest, frame_byte_size, frame_offset);
    if (bytes_read < frame_byte_size) {
      *status = READ_ERROR;
    }

    return;
}

#endif /* CSERIO_IMPLEMENTATION */

#endif /* CSERIO_H */

