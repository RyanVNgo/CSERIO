/*  @file   cserio.h
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
#include <stdbool.h>


/*-------------------- CSERIO Version --------------------*/

#define CSERIO_MAJOR                        2
#define CSERIO_MINOR                        1
#define CSERIO_MICRO                        0

/*-------------------- Core Errors --------------------*/

#define NO_ERROR                            0

#define MEM_ALLOC                           101
#define NULL_SPTR                           102
#define NULL_DEST_BUFF                      103
#define NULL_PARAM                          104

#define EOF_ERROR                           111
#define FREAD_ERROR                         112
#define READ_ERROR                          113

#define WRITE_ON_READONLY                   131

/*-------------------- File Access Errors --------------------*/

#define NULL_PATH                           201
#define FILE_EXISTS                         202
#define FILE_DNE                            203

#define FILE_OPEN_ERROR                     211
#define FILE_CLOSE_ERROR                    212

#define INVALID_STRUCTURE                   222

/*-------------------- Header Routine Errors --------------------*/

#define INVALID_HDR_IDX                     301
#define INVALID_HDR_KEY                     302

#define HDR_WRITE_WARN                      311

#define INVALID_SET_STATE                   321
#define INVALID_SET_VALUE                   322

/*-------------------- Image Routine Errors --------------------*/

#define INVALID_DIM_IDX                     401
#define INVALID_FRAME_IDX                   402

#define IMAGE_WRITE_WARN                    411

/*-------------------- Trailer Routine Errors --------------------*/

#define TRAILER_DNE                         501

#define INVALID_TRAILER_ENABLE              511
#define INVALID_TRAILER_IDX                 512

#define TRAILER_CLOSE_WARN                  521

/*-------------------- SER File IO Modes --------------------*/

#define READONLY                            0
#define READWRITE                           1

/*-------------------- Header Symbolic Constants --------------------*/

#define HDR_UNIT_COUNT                      13
#define HDR_SIZE                            178

/* 
 *  Constants that represent the byte length of each header component.
 */
#define FILEID_LEN                          14
#define LUID_LEN                            4
#define COLORID_LEN                         4
#define LITTLEENDIAN_LEN                    4 
#define IMAGEWIDTH_LEN                      4 
#define IMAGEHEIGHT_LEN                     4 
#define PIXELDEPTHPERPLANE_LEN              4 
#define FRAMECOUNT_LEN                      4 
#define OBSERVER_LEN                        40 
#define INSTRUMENT_LEN                      40 
#define TELESCOPE_LEN                       40 
#define DATETIME_LEN                        8 
#define DATETIMEUTC_LEN                     8 

/*  
 *  Byte index position of each header component.
 */
#define FILEID_KEY                          0
#define LUID_KEY                            14
#define COLORID_KEY                         18
#define LITTLEENDIAN_KEY                    22
#define IMAGEWIDTH_KEY                      26
#define IMAGEHEIGHT_KEY                     30
#define PIXELDEPTHPERPLANE_KEY              34
#define FRAMECOUNT_KEY                      38
#define OBSERVER_KEY                        42
#define INSTRUMENT_KEY                      82
#define TELESCOPE_KEY                       122
#define DATETIME_KEY                        162
#define DATETIMEUTC_KEY                     170

/* 
 * Color ID types.
 */
#define MONO                                0
#define BAYER_RGGB                          8
#define BAYER_GRBG                          9
#define BAYER_GBRG                          10
#define BAYER_BGGR                          11
#define BAYER_CYYM                          16
#define BAYER_YCMY                          17
#define BAYER_YMCY                          18
#define BAYER_MYYC                          19
#define RGB                                 100
#define BGR                                 101

/* 
 * Little Endian types.
 */
#define LITTLEENDIAN_TRUE                   1
#define LITTLEENDIAN_FALSE                  0


/*-------------------- Image Symbolic Constants --------------------*/

typedef int DIM_TYPE;
#define DIM_LAYER                           0
#define DIM_WIDTH                           1
#define DIM_HEIGHT                          2

/*-------------------- SER Structure --------------------*/


/*  serfile is the primary structure used to interact with nearly all
 *  CSERIO routines. 
 *
 *  This structure should not be directly interacted with by 
 *  the user.
 */
typedef struct serfile serfile;


/*------------------------------------------------------------------*/
/* CSERIO Definitions */ 
/*------------------------------------------------------------------*/

/*-------------------- Core Routines --------------------*/

void cserio_version_number(int* major, int* minor, int* micro);

/*-------------------- SER Access Routines --------------------*/

void ser_create_memory(serfile** sptr, int* status);
void ser_open_view(serfile** sptr, uint8_t* data, size_t size, int mode, int* status);
void ser_open_memory(serfile** sptr, const uint8_t* data, size_t size, int mode, int* status);
void ser_close_memory(serfile* sptr, int* status);

void ser_create_file(serfile** sptr, const char* path, int* status);
void ser_open_file(serfile** sptr, const char* path, int mode, int* status);
void ser_close_file(serfile* sptr, int* status);

/*-------------------- Header Routines --------------------*/

void ser_get_rec_count(serfile* sptr, int* rec_count, int* status);

void ser_get_idx_record(serfile* sptr, void* dest, size_t idx, int* status);
void ser_get_key_record(serfile* sptr, void* dest, int key, int* status);

void ser_write_idx_record(serfile* sptr, const void* data, size_t idx, size_t size, int* status);
void ser_write_key_record(serfile* sptr, const void* data, int key, size_t size, int* status);

void ser_get_file_id(const serfile* sptr, char* file_id, int* status);
void ser_get_lu_id(const serfile* sptr, int32_t* lu_id, int* status);
void ser_get_color_id(const serfile* sptr, int32_t* color_id, int* status);
void ser_get_little_endian(const serfile* sptr, int32_t* little_endian, int* status);
void ser_get_image_width(const serfile* sptr, int32_t* image_width, int* status);
void ser_get_image_height(const serfile* sptr, int32_t* image_height, int* status);
void ser_get_pixel_depth_per_plane(const serfile* sptr, int32_t* pixel_depth_per_plane, int* status);
void ser_get_frame_count(const serfile* sptr, int32_t* frame_count, int* status);
void ser_get_observer(const serfile* sptr, char* observer, int* status);
void ser_get_instrument(const serfile* sptr, char* instrument, int* status);
void ser_get_telescope(const serfile* sptr, char* telescope, int* status);
void ser_get_date_time(const serfile* sptr, int64_t* date_time, int* status);
void ser_get_date_time_utc(const serfile* sptr, int64_t* date_time_utc, int* status);

void ser_set_file_id(serfile* sptr, const char* file_id, int* status);
void ser_set_lu_id(serfile* sptr, const int32_t lu_id, int* status);
void ser_set_color_id(serfile* sptr, const int32_t color_id, int* status);
void ser_set_little_endian(serfile* sptr, const int32_t little_endian, int* status);
void ser_set_image_width(serfile* sptr, const uint32_t image_width, int* status);
void ser_set_image_height(serfile* sptr, const uint32_t image_height, int* status);
void ser_set_pixel_depth_per_plane(serfile* sptr, const int32_t pixel_depth_per_plane, int* status);
// void ser_set_frame_count(serfile* sptr, const int32_t frame_count, int* status);
void ser_set_observer(serfile* sptr, const char* observer, int* status);
void ser_set_instrument(serfile* sptr, const char* instrument, int* status);
void ser_set_telescope(serfile* sptr, const char* telescope, int* status);
void ser_set_date_time(serfile* sptr, const int64_t date_time, int* status);
void ser_set_date_time_utc(serfile* sptr, const int64_t date_time_utc, int* status);

/*-------------------- Image Routines --------------------*/

void ser_get_frame_dim_size(serfile* sptr, int* size, int dim, int* status);

void ser_get_bytes_per_pixel(serfile* sptr, unsigned long* bytes_per_pixel, int* status); 
void ser_get_frame_byte_size(serfile* sptr, unsigned long* byte_size, int* status);

void ser_read_frame(serfile* sptr, void* dest, size_t idx, int* status);
void ser_append_frame(serfile* sptr, const void* data, uint64_t timestamp, int* status);

/*-------------------- Trailer Routines --------------------*/

void ser_enable_trailer(serfile* sptr, int* status);
void ser_get_timestamp(serfile* sptr, int64_t* dest, size_t idx, int* status);


/*------------------------------------------------------------------*/
/* CSERIO Implementation */ 
/*------------------------------------------------------------------*/

#if defined(CSERIO_IMPLEMENTATION)

/*-------------------- Internal Implementation --------------------*/

/*  
 *  serfile implementation.
 */
typedef struct serfile {
    void*       io_context;
    size_t      (*reader)(void* io_context, void* buffer, size_t size, size_t offset);
    size_t      (*writer)(void* io_context, const void* data, size_t size, size_t offset);
    int         access_mode;

	char		file_id[FILEID_LEN];
	int32_t		lu_id;
	int32_t		color_id;
	int32_t		little_endian;
	int32_t		image_width;
	int32_t		image_height;
	int32_t		pixel_depth_per_plane;
	int32_t		frame_count;
	char		observer[OBSERVER_LEN];
	char		instrument[INSTRUMENT_LEN];
	char		telescope[TELESCOPE_LEN];
	int64_t		date_time;
	int64_t		date_time_utc;

    bool        has_trailer;
    int64_t*    timestamps;
    size_t      timestamp_count;
} serfile;

typedef struct {
    uint8_t* data;
    size_t size;
    size_t view_size;
    bool owns_buffer;
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

static size_t ser_memory_write(void* io_context, const void* data, size_t size, size_t offset) {
    serMem* memory_io = (serMem*)(io_context);

    if (!memory_io->owns_buffer) {
        if (memory_io->size < offset) {
            return 0;
        }

        if (memory_io->size < offset + size) {
            size_t cut_size = memory_io->size - offset;
            memcpy(memory_io->data + offset, data, cut_size);
            return cut_size;
        }
    } else {
        if (memory_io->size < offset + size) {
            void* new_block = realloc(memory_io->data, offset + size);
            if (new_block) {
                memory_io->data = (uint8_t*)new_block;
                memory_io->size = offset + size;
            } else {
                size_t cut_size = memory_io->size - offset;
                memcpy(memory_io->data + offset, data, cut_size);
                return cut_size;
            }
        }
    }

    memcpy(memory_io->data + offset, data, size);

    return size;
}

static size_t ser_file_read(void* io_context, void* buffer, size_t size, size_t offset) {
    FILE* file_io = (FILE*)io_context;
    fseek(file_io, offset, SEEK_SET);
    return fread(buffer, 1, size, file_io);
}

static size_t ser_file_write(void* io_context, const void* data, size_t size, size_t offset) {
    FILE* file_io = (FILE*)io_context;
    fseek(file_io, offset, SEEK_SET);
    return fwrite(data, 1, size, file_io);
}


/*-------------------- Core Routines --------------------*/

/*  @brief  Provides the Major, Minor, and Micro numbers for
 *          the current version of CSERIO.
 *  @param  major       (IO)    - Pointer to Major int.
 *  @param  minor       (IO)    - Pointer to Minor int.
 *  @param  micro       (IO)    - Pointer to Micro int.
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


/*-------------------- SER Access Routines --------------------*/

/*  @brief  Opens new in-memory SER file.
 *  @param  sptr        (IO)    - Pointer to a pointer of a serfile.
 *  @param  status      (IO)    - Error status.
 *  @return Void.
 */
void ser_create_memory(serfile** sptr, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    /* allocate memory for serfile */
    *sptr = (serfile*)malloc(sizeof(serfile));
    if (!*sptr) {
        return (void)(*status = MEM_ALLOC);
    }

    /* allocate data reference */
    serMem* ser_data = (serMem*)malloc(sizeof(serMem));
    ser_data->data = (uint8_t*)malloc(HDR_SIZE);
    ser_data->size = HDR_SIZE;
    ser_data->owns_buffer = true;

    /* general setup */
    (*sptr)->io_context = ser_data;
    (*sptr)->reader = ser_memory_read;
    (*sptr)->writer = ser_memory_write;
    (*sptr)->access_mode = READWRITE;

    /* intialize file metadata */
    memset((*sptr)->file_id, 0, FILEID_LEN);
    (*sptr)->lu_id = 0;
    (*sptr)->color_id = MONO;
    (*sptr)->little_endian = 1;
    (*sptr)->image_width = 0;
    (*sptr)->image_height = 0;
    (*sptr)->pixel_depth_per_plane = 8;
    (*sptr)->frame_count = 0;
    memset((*sptr)->observer, 0, OBSERVER_LEN);
    memset((*sptr)->instrument, 0, INSTRUMENT_LEN);
    memset((*sptr)->telescope, 0, TELESCOPE_LEN);
    (*sptr)->date_time = 0;
    (*sptr)->date_time_utc = 0;

    /* initialize trailer */
    (*sptr)->has_trailer = false;
    (*sptr)->timestamps = NULL;
    (*sptr)->timestamp_count = 0;

    return;
}

/*  @brief  Opens in-memory SER file.
 *
 *  For when a SER file is located in memory. Note that the 
 *  data must persist so long as it is opened to the serfile.
 *  Read and write routines only operate within the range
 *  provided by size. 
 *
 *  @param  sptr      (IO)  - Pointer to a pointer of a serfile.
 *  @param  data      (I)   - Pointer to data.
 *  @param  size      (I)   - Size of data view.
 *  @param  mode      (I)   - Access type (READONLY or READWRITE).
 *  @param  status    (IO)  - Error status.
 *  @return Void.
 */
void ser_open_view(serfile** sptr, uint8_t* data, size_t size, int mode, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!data) {
        return (void)(*status = NULL_PARAM);
    }

    /* determine validity of header */
    if (size < HDR_SIZE) {
        return (void)(*status = INVALID_STRUCTURE);
    }

    /* allocate memory for serfile */
    *sptr = (serfile*)malloc(sizeof(serfile));
    if (!(*sptr)) {
        return (void)(*status = MEM_ALLOC);
    }

    /* allocate data reference */
    serMem* ser_data = (serMem*)malloc(sizeof(serMem));
    ser_data->data = data;
    ser_data->size = size;
    ser_data->owns_buffer = false;

    /* general setup */
    (*sptr)->io_context = ser_data;
    (*sptr)->reader = ser_memory_read;
    (*sptr)->writer = ser_memory_write;
    (*sptr)->access_mode = mode == READWRITE ? READWRITE : READONLY;
    ser_get_key_record(*sptr, (*sptr)->file_id, FILEID_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->lu_id, LUID_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->color_id, COLORID_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->little_endian, LITTLEENDIAN_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->image_width, IMAGEWIDTH_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->image_height, IMAGEHEIGHT_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->pixel_depth_per_plane, PIXELDEPTHPERPLANE_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->frame_count, FRAMECOUNT_KEY, status);
    ser_get_key_record(*sptr, (*sptr)->observer, OBSERVER_KEY, status);
    ser_get_key_record(*sptr, (*sptr)->instrument, INSTRUMENT_KEY, status);
    ser_get_key_record(*sptr, (*sptr)->telescope, TELESCOPE_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->date_time, DATETIME_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->date_time_utc, DATETIMEUTC_KEY, status);
    (*sptr)->has_trailer = false;
    (*sptr)->timestamps = NULL;
    (*sptr)->timestamp_count = 0;

    /* determine if valid hdr + data or hdr + data + trailer */
    size_t frame_byte_size = 0;
    ser_get_frame_byte_size(*sptr, &frame_byte_size, status);
    size_t hdr_data_size = HDR_SIZE + (*sptr)->frame_count * frame_byte_size;

    /* hdr + data */
    if (size == hdr_data_size) {
        return;
    }

    /* hdr + data + trailer */
    if ((size - hdr_data_size) == (*sptr)->frame_count * sizeof(uint64_t)) {
        (*sptr)->has_trailer = true;
        (*sptr)->timestamps = (int64_t*)realloc((*sptr)->timestamps, (*sptr)->frame_count * sizeof(uint64_t));
        (*sptr)->timestamp_count = (*sptr)->frame_count;
        (*sptr)->reader(
                (*sptr)->io_context,
                (*sptr)->timestamps,
                (*sptr)->frame_count * sizeof(uint64_t),
                hdr_data_size
        );
        return;
    }

    /* if reached, invalid structure */
    free(((serMem*)(*sptr)->io_context));
    free((*sptr));
    *sptr = NULL;
    return (void)(*status = INVALID_STRUCTURE);
}

/*  @brief  Opens/Copies in-memory SER file.
 *
 *  Memory is allocated and managed by the serfile. If data is not
 *  NULL, the data of length size is copied over.
 *
 *  @param  sptr        (IO)    - Pointer to a pointer of a serfile.
 *  @param  data        (I)     - Pointer to data.
 *  @param  size        (I)     - Size to initially allocate / copy over.
 *  @param  mode        (I)     - Access type (READONLY or READWRITE).
 *  @param  status      (IO)    - Error status.
 *  @return Void.
 */
void ser_open_memory(serfile** sptr, const uint8_t* data, size_t size, int mode, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!data) {
        return (void)(*status = NULL_PARAM);
    }

    /* determine validity of header */
    if (size < HDR_SIZE) {
        return (void)(*status = INVALID_STRUCTURE);
    }

    /* allocate memory for serfile */
    *sptr = (serfile*)malloc(sizeof(serfile));
    if (!(*sptr)) {
        return (void)(*status = MEM_ALLOC);
    }

    /* allocate data reference */
    serMem* ser_data = (serMem*)malloc(sizeof(serMem));
    ser_data->data = (uint8_t*)malloc(size);
    if (data) {
        memcpy(ser_data->data, data, size);
    }
    ser_data->size = size;
    ser_data->owns_buffer = true;

    /* general setup */
    (*sptr)->io_context = ser_data;
    (*sptr)->reader = ser_memory_read;
    (*sptr)->writer = ser_memory_write;
    (*sptr)->access_mode = mode == READWRITE ? READWRITE : READONLY;
    ser_get_key_record(*sptr, (*sptr)->file_id, FILEID_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->lu_id, LUID_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->color_id, COLORID_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->little_endian, LITTLEENDIAN_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->image_width, IMAGEWIDTH_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->image_height, IMAGEHEIGHT_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->pixel_depth_per_plane, PIXELDEPTHPERPLANE_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->frame_count, FRAMECOUNT_KEY, status);
    ser_get_key_record(*sptr, (*sptr)->observer, OBSERVER_KEY, status);
    ser_get_key_record(*sptr, (*sptr)->instrument, INSTRUMENT_KEY, status);
    ser_get_key_record(*sptr, (*sptr)->telescope, TELESCOPE_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->date_time, DATETIME_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->date_time_utc, DATETIMEUTC_KEY, status);
    (*sptr)->has_trailer = false;
    (*sptr)->timestamps = NULL;
    (*sptr)->timestamp_count = 0;

    /* determine if valid hdr + data or hdr + data + trailer */
    size_t frame_byte_size = 0;
    ser_get_frame_byte_size(*sptr, &frame_byte_size, status);
    size_t hdr_data_size = HDR_SIZE + (*sptr)->frame_count * frame_byte_size;

    /* hdr + data */
    if (size == hdr_data_size) {
        return;
    }

    /* hdr + data + trailer */
    if ((size - hdr_data_size) == (*sptr)->frame_count * sizeof(uint64_t)) {
        (*sptr)->has_trailer = true;
        (*sptr)->timestamps = (int64_t*)realloc((*sptr)->timestamps, (*sptr)->frame_count * sizeof(uint64_t));
        (*sptr)->timestamp_count = (*sptr)->frame_count;
        (*sptr)->reader(
                (*sptr)->io_context,
                (*sptr)->timestamps,
                (*sptr)->frame_count * sizeof(uint64_t),
                hdr_data_size
        );
        return;
    }

    /* if reached, invalid structure */
    free(((serMem*)(*sptr)->io_context)->data);
    free(((serMem*)(*sptr)->io_context));
    free((*sptr));
    *sptr = NULL;
    return (void)(*status = INVALID_STRUCTURE);
}

/*  @brief  Close in-memory SER file
 *
 *  Closes the serfile and frees the structure. Parameter sptr will
 *  be set to NULL.
 *
 *  @param  sptr        (IO)    - Pointer to a serfile.
 *  @param  status      (IO)    - Error status.
 *  @return Void.
 */
void ser_close_memory(serfile* sptr, int* status) {
    if (!sptr) { 
        return (void)(*status = NULL_SPTR); 
    }

    if (sptr->access_mode == READWRITE) {
		ser_write_key_record(sptr, &sptr->file_id, FILEID_KEY, FILEID_LEN, status);
		ser_write_key_record(sptr, &sptr->lu_id, LUID_KEY, LUID_LEN, status);
		ser_write_key_record(sptr, &sptr->color_id, COLORID_KEY, COLORID_LEN, status);
		ser_write_key_record(sptr, &sptr->little_endian, LITTLEENDIAN_KEY, LITTLEENDIAN_LEN, status);
		ser_write_key_record(sptr, &sptr->image_width, IMAGEWIDTH_KEY, IMAGEWIDTH_LEN, status);
		ser_write_key_record(sptr, &sptr->image_height, IMAGEHEIGHT_KEY, IMAGEHEIGHT_LEN, status);
		ser_write_key_record(sptr, &sptr->pixel_depth_per_plane, PIXELDEPTHPERPLANE_KEY, PIXELDEPTHPERPLANE_LEN, status);
		ser_write_key_record(sptr, &sptr->frame_count, FRAMECOUNT_KEY, FRAMECOUNT_LEN, status);
		ser_write_key_record(sptr, &sptr->observer, OBSERVER_KEY, OBSERVER_LEN, status);
		ser_write_key_record(sptr, &sptr->instrument, INSTRUMENT_KEY, INSTRUMENT_LEN, status);
		ser_write_key_record(sptr, &sptr->telescope, TELESCOPE_KEY, TELESCOPE_LEN, status);
		ser_write_key_record(sptr, &sptr->date_time, DATETIME_KEY, DATETIME_LEN, status);
		ser_write_key_record(sptr, &sptr->date_time_utc, DATETIMEUTC_KEY, DATETIMEUTC_LEN, status);
    }

    if (sptr->timestamps && sptr->access_mode == READWRITE) {
        size_t image_frame_byte_size = 0;
        ser_get_frame_byte_size(sptr, &image_frame_byte_size, status);
        size_t image_data_size = sptr->frame_count * image_frame_byte_size;

        size_t trailer_offset = HDR_SIZE + image_data_size;
        size_t trailer_size = sizeof(int64_t) * sptr->timestamp_count;

        size_t bytes_written = sptr->writer(
                sptr->io_context,
                sptr->timestamps,
                trailer_size,
                trailer_offset
        );
        if (bytes_written != trailer_size) {
            *status = TRAILER_CLOSE_WARN;
        }
        free(sptr->timestamps);
    }

    serMem* memory_io = (serMem*)(sptr->io_context);
    if (memory_io->owns_buffer) {
        free(memory_io->data);
    }

    free(sptr->io_context);
    free(sptr);
    sptr = NULL;
    return;
}

/*  @brief  Create a new SER file.
 *
 *  @param  sptr        (IO)    - Pointer to pointer of a serfile.
 *  @param  path        (I)     - File path.
 *  @param  status      (IO)    - Error status.
 *  @return Void.
 */
void ser_create_file(serfile** sptr, const char* path, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!path) {
        return (void)(*status = NULL_PATH);
    }

    FILE* file;
    if ((file = fopen(path, "r"))) {
        fclose(file);
        return (void)(*status = FILE_EXISTS);
    }

    file = fopen(path, "w+b");
    if (!file) {
        return (void)(*status = FILE_OPEN_ERROR);
    }

    *sptr = (serfile*)malloc(sizeof(serfile));
    if (!*sptr) {
        fclose(file);
        return (void)(*status = MEM_ALLOC);
    }

    (*sptr)->io_context = file;
    (*sptr)->reader = ser_file_read;
    (*sptr)->writer = ser_file_write;
    (*sptr)->access_mode = READWRITE;

    memset((*sptr)->file_id, 0, FILEID_LEN);
    (*sptr)->lu_id = 0;
    (*sptr)->color_id = MONO;
    (*sptr)->little_endian = 1;
    (*sptr)->image_width = 0;
    (*sptr)->image_height = 0;
    (*sptr)->pixel_depth_per_plane = 8;
    (*sptr)->frame_count = 0;
    memset((*sptr)->observer, 0, OBSERVER_LEN);
    memset((*sptr)->instrument, 0, INSTRUMENT_LEN);
    memset((*sptr)->telescope, 0, TELESCOPE_LEN);
    (*sptr)->date_time = 0;
    (*sptr)->date_time_utc = 0;

    (*sptr)->has_trailer = false;
    (*sptr)->timestamps = NULL;
    (*sptr)->timestamp_count = 0;

    return;
}

/*  @brief  Opens existing SER file
 *
 *  @param  sptr        (IO)    - Pointer to a pointer of a serfile.
 *  @param  path        (I)     - SER file path.
 *  @param  mode        (I)     - Access type (READONLY or READWRITE).
 *  @param  status      (IO)    - Error status.
 *  @return Void.
 */
void ser_open_file(serfile** sptr, const char* path, int mode, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!path) {
        return (void)(*status = NULL_PATH);
    }

    FILE* file;
    switch (mode) {
        case READWRITE:
            file = fopen(path, "r+b");
            break;
        case READONLY:
        default:
            file = fopen(path, "rb");
    }
    
    if (!file) {
        return (void)(*status = FILE_DNE);
    }

    /* retrieve size of file and return to start */
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    /* determine validity of header */
    if (file_size < HDR_SIZE) {
        fclose(file);
        return (void)(*status = INVALID_STRUCTURE);
    }

    /* allocate memory for serfile */
    *sptr = (serfile*)malloc(sizeof(serfile));
    if (!*sptr) {
        fclose(file);
        return (void)(*status = MEM_ALLOC);
    }

    /* general setup */
    (*sptr)->io_context = file;
    (*sptr)->reader = ser_file_read;
    (*sptr)->writer = ser_file_write;
    (*sptr)->access_mode = mode == READWRITE ? READWRITE : READONLY;
    ser_get_key_record(*sptr, (*sptr)->file_id, FILEID_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->lu_id, LUID_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->color_id, COLORID_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->little_endian, LITTLEENDIAN_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->image_width, IMAGEWIDTH_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->image_height, IMAGEHEIGHT_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->pixel_depth_per_plane, PIXELDEPTHPERPLANE_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->frame_count, FRAMECOUNT_KEY, status);
    ser_get_key_record(*sptr, (*sptr)->observer, OBSERVER_KEY, status);
    ser_get_key_record(*sptr, (*sptr)->instrument, INSTRUMENT_KEY, status);
    ser_get_key_record(*sptr, (*sptr)->telescope, TELESCOPE_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->date_time, DATETIME_KEY, status);
    ser_get_key_record(*sptr, &(*sptr)->date_time_utc, DATETIMEUTC_KEY, status);
    (*sptr)->has_trailer = false;
    (*sptr)->timestamps = NULL;
    (*sptr)->timestamp_count = 0;

    /* determine if valid hdr + data or hdr + data + trailer */
    size_t frame_byte_size = 0;
    ser_get_frame_byte_size(*sptr, &frame_byte_size, status);
    size_t hdr_data_size = HDR_SIZE + (*sptr)->frame_count * frame_byte_size;

    /* hdr + data */
    if (file_size == hdr_data_size) {
        return;
    }

    /* hdr + data + trailer */
    if ((file_size - hdr_data_size) == (*sptr)->frame_count * sizeof(uint64_t)) {
        (*sptr)->has_trailer = true;
        (*sptr)->timestamps = (int64_t*)realloc((*sptr)->timestamps, (*sptr)->frame_count * sizeof(uint64_t));
        (*sptr)->timestamp_count = (*sptr)->frame_count;
        (*sptr)->reader(
                (*sptr)->io_context,
                (*sptr)->timestamps,
                (*sptr)->frame_count * sizeof(uint64_t),
                hdr_data_size
        );
        return;
    }

    /* if reached, invalid structure */
    fclose(file);
    free((*sptr));
    *sptr = NULL;
    return (void)(*status = INVALID_STRUCTURE);
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

    if (sptr->access_mode == READWRITE) {
		ser_write_key_record(sptr, &sptr->file_id, FILEID_KEY, FILEID_LEN, status);
		ser_write_key_record(sptr, &sptr->lu_id, LUID_KEY, LUID_LEN, status);
		ser_write_key_record(sptr, &sptr->color_id, COLORID_KEY, COLORID_LEN, status);
		ser_write_key_record(sptr, &sptr->little_endian, LITTLEENDIAN_KEY, LITTLEENDIAN_LEN, status);
		ser_write_key_record(sptr, &sptr->image_width, IMAGEWIDTH_KEY, IMAGEWIDTH_LEN, status);
		ser_write_key_record(sptr, &sptr->image_height, IMAGEHEIGHT_KEY, IMAGEHEIGHT_LEN, status);
		ser_write_key_record(sptr, &sptr->pixel_depth_per_plane, PIXELDEPTHPERPLANE_KEY, PIXELDEPTHPERPLANE_LEN, status);
		ser_write_key_record(sptr, &sptr->frame_count, FRAMECOUNT_KEY, FRAMECOUNT_LEN, status);
		ser_write_key_record(sptr, &sptr->observer, OBSERVER_KEY, OBSERVER_LEN, status);
		ser_write_key_record(sptr, &sptr->instrument, INSTRUMENT_KEY, INSTRUMENT_LEN, status);
		ser_write_key_record(sptr, &sptr->telescope, TELESCOPE_KEY, TELESCOPE_LEN, status);
		ser_write_key_record(sptr, &sptr->date_time, DATETIME_KEY, DATETIME_LEN, status);
		ser_write_key_record(sptr, &sptr->date_time_utc, DATETIMEUTC_KEY, DATETIMEUTC_LEN, status);
    }

    if (sptr->timestamps && sptr->access_mode == READWRITE) {
        size_t image_frame_byte_size = 0;
        ser_get_frame_byte_size(sptr, &image_frame_byte_size, status);
        size_t image_data_size = sptr->frame_count * image_frame_byte_size;

        size_t trailer_offset = HDR_SIZE + image_data_size;
        size_t trailer_size = sizeof(int64_t) * sptr->timestamp_count;

        size_t bytes_written = sptr->writer(
                sptr->io_context,
                sptr->timestamps,
                trailer_size,
                trailer_offset
        );
        if (bytes_written != trailer_size) {
            *status = TRAILER_CLOSE_WARN;
        }
        free(sptr->timestamps);
    }

    if (!sptr->io_context || fclose((FILE*)sptr->io_context)) {
        *status = FILE_CLOSE_ERROR;
    }

    free(sptr);
    sptr = NULL;
    return;
}

/*-------------------- Header Routines --------------------*/

/*  @brief  Returns number of records in the header
 *
 *  Note that as of Version 3 SER files, the number of records 
 *  in a header is a constant 13.
 *
 *  @param  sptr        (I)   - Pointer to serfile.
 *  @param  rec_count   (IO)  - Number of records.
 *  @param  status      (IO)  - Error status.
 *  @return Void.
 */
void ser_get_rec_count(serfile* sptr, int* rec_count, int* status) {
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
 *  Ensure the dest buffer is large enough to store the data.
 *  Data of size [key]_LEN will be copied over.
 *
 *  @param  sptr    (I)   - Pointer to serfile.
 *  @param  dest    (IO)  - Destination buffer.
 *  @param  idx     (I)   - Record index.
 *  @param  status  (IO)  - Error status.
 *  @return Void.
 */
void ser_get_idx_record(serfile* sptr, void* dest, size_t idx, int* status) {
    if (!sptr) { return (void)(*status = NULL_SPTR); }
    if (!dest) { return (void)(*status = NULL_DEST_BUFF); }

    if (idx >= HDR_UNIT_COUNT) { return (void)(*status = INVALID_HDR_IDX); }

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

    int bytes_read = sptr->reader(sptr->io_context, dest, byte_len, fpos);
    if (bytes_read < byte_len) {
        *status = READ_ERROR;
    }

    return;
}

/*  @brief  Return data at header key
 *
 *  Ensure the dest buffer is large enough to store the data.
 *  Data of size [key]_LEN will be copied over.
 *
 *  @param  sptr    (I)   - Pointer to serfile.
 *  @param  dest    (IO)  - Destination buffer.
 *  @param  key     (I)   - Record key.
 *  @param  status  (IO)  - Error status.
 *  @return Void.
 */
void ser_get_key_record(serfile* sptr, void* dest, int key, int* status) {
    if (!sptr) { 
        return (void)(*status = NULL_SPTR); 
    }

    if (!dest) { 
        return (void)(*status = NULL_DEST_BUFF); 
    }

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

    int bytes_read = sptr->reader(sptr->io_context, dest, byte_len, key);

    if (bytes_read < byte_len) {
        *status = READ_ERROR;
    }

    return;
}

/*  @brief  Get File ID
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  file_id     (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Void.
 */
void ser_get_file_id(const serfile* sptr, char* file_id, int* status) {
    if (!sptr) { 
        return (void)(*status = NULL_SPTR); 
    }

    if (!file_id) { 
        return (void)(*status = NULL_DEST_BUFF); 
    }

    memcpy(file_id, sptr->file_id, FILEID_LEN);
}

/*  @brief  Get LU ID
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  lu_id       (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Void.
 */
void ser_get_lu_id(const serfile* sptr, int32_t* lu_id, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!lu_id) {
        return (void)(*status = NULL_DEST_BUFF);
    }

    *lu_id = sptr->lu_id;
}

/*  @brief  Get Color ID
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  color_id    (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Void.
 */
void ser_get_color_id(const serfile* sptr, int32_t* color_id, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!color_id) {
        return (void)(*status = NULL_DEST_BUFF);
    }

    *color_id = sptr->color_id;
}

/*  @brief  Get Litte Endian
 *  @param  sptr            (I)     - Pointer to serfile.
 *  @param  little_endian   (IO)    - Destination buffer.
 *  @param  status          (IO)    - Error status.
 *  @return Void.
 */
void ser_get_little_endian(const serfile* sptr, int32_t* little_endian, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!little_endian) {
        return (void)(*status = NULL_DEST_BUFF);
    }

    *little_endian = sptr->little_endian;
}

/*  @brief  Get Image Width
 *  @param  sptr            (I)     - Pointer to serfile.
 *  @param  image_width     (IO)    - Destination buffer.
 *  @param  status          (IO)    - Error status.
 *  @return Void.
 */
void ser_get_image_width(const serfile* sptr, int32_t* image_width, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!image_width) {
        return (void)(*status = NULL_DEST_BUFF);
    }

    *image_width = sptr->image_width;
}

/*  @brief  Get Image Height 
 *  @param  sptr            (I)     - Pointer to serfile.
 *  @param  image_height    (IO)    - Destination buffer.
 *  @param  status          (IO)    - Error status.
 *  @return Void.
 */
void ser_get_image_height(const serfile* sptr, int32_t* image_height, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!image_height) {
        return (void)(*status = NULL_DEST_BUFF);
    }

    *image_height= sptr->image_height;
}

/*  @brief  Get Pixel Depth Per Plane
 *  @param  sptr                    (I)     - Pointer to serfile.
 *  @param  pixel_depth_per_plane   (IO)    - Destination buffer.
 *  @param  status                  (IO)    - Error status.
 *  @return Void.
 */
void ser_get_pixel_depth_per_plane(const serfile* sptr, int32_t* pixel_depth_per_plane, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!pixel_depth_per_plane) {
        return (void)(*status = NULL_DEST_BUFF);
    }

    *pixel_depth_per_plane = sptr->pixel_depth_per_plane;
}

/*  @brief  Get Frame Count
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  frame_count (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Void.
 */
void ser_get_frame_count(const serfile* sptr, int32_t* frame_count, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!frame_count) {
        return (void)(*status = NULL_DEST_BUFF);
    }

    *frame_count = sptr->frame_count;
}

/*  @brief  Get Observer
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  observer    (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Void.
 */
void ser_get_observer(const serfile* sptr, char* observer, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!observer) {
        return (void)(*status = NULL_DEST_BUFF);
    }

    memcpy(observer, sptr->observer, OBSERVER_LEN);
}

/*  @brief  Get Instrument 
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  instrument  (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Void.
 */
void ser_get_instrument(const serfile* sptr, char* instrument, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!instrument) {
        return (void)(*status = NULL_DEST_BUFF);
    }

    memcpy(instrument, sptr->instrument, INSTRUMENT_LEN);
}

/*  @brief  Get Telescope
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  telescope   (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Void.
 */
void ser_get_telescope(const serfile* sptr, char* telescope, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!telescope) {
        return (void)(*status = NULL_DEST_BUFF);
    }

    memcpy(telescope, sptr->telescope, TELESCOPE_LEN);
}

/*  @brief  Get Date Time
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  date_time   (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Void.
 */
void ser_get_date_time(const serfile* sptr, int64_t* date_time, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!date_time) {
        return (void)(*status = NULL_DEST_BUFF);
    }

    *date_time = sptr->date_time;
}

/*  @brief  Get Date Time UTC
 *  @param  sptr            (I)     - Pointer to serfile.
 *  @param  date_time_utc   (IO)    - Destination buffer.
 *  @param  status          (IO)    - Error status.
 *  @return Void.
 */
void ser_get_date_time_utc(const serfile* sptr, int64_t* date_time_utc, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!date_time_utc) {
        return (void)(*status = NULL_DEST_BUFF);
    }

    *date_time_utc = sptr->date_time_utc;
}

/*  @brief  Write data to header idx 
 *  
 *  This write routine is capped such that it will write less
 *  than or up to the maximum size of the record space.
 *
 *  @param  sptr    (I)     - Pointer to serfile.
 *  @param  data    (IO)    - Pointer to data.
 *  @param  idx     (I)     - Header record index.
 *  @param  size    (I)     - Size of data in bytes.
 *  @param  status  (IO)    - Error status.
 *  @return Error status.
 */
void ser_write_idx_record(serfile* sptr, const void* data, size_t idx, size_t size, int* status) {
    if (!sptr) { 
        return (void)(*status = NULL_SPTR); 
    }

    if (!data) { 
        return (void)(*status = NULL_PARAM); 
    }

    if (idx >= HDR_UNIT_COUNT) { 
        return (void)(*status = INVALID_HDR_IDX); 
    }

    if (sptr->access_mode != READWRITE) { 
        return (void)(*status = WRITE_ON_READONLY); 
    }

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

    size_t bytes_written = sptr->writer(sptr->io_context, data, size, fpos);
    if (bytes_written != size) {
        *status = HDR_WRITE_WARN;
    }

    return;
}

/*  @brief  Write data to header key
 *  
 *  This write routine is capped such that it will write less
 *  than or up to the maximum size of the record space.
 *
 *  @param  sptr    (I)     - Pointer to serfile.
 *  @param  data    (IO)    - Pointer to data.
 *  @param  key     (I)     - Record key.
 *  @param  size    (I)     - Size of data in bytes.
 *  @param  status  (IO)    - Error status.
 *  @return Void.
 */
void ser_write_key_record(serfile* sptr, const void* data, int key, size_t size, int* status) {
    if (!sptr) { 
        return (void)(*status = NULL_SPTR); 
    }

    if (!data) { 
        return (void)(*status = NULL_PARAM); 
    }

    if (sptr->access_mode != READWRITE) { 
        return (void)(*status = WRITE_ON_READONLY); 
    }

    size_t max_byte_len = 0;
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

    size_t bytes_written = sptr->writer(sptr->io_context, data, size, key);
    if (bytes_written != size) {
        *status = HDR_WRITE_WARN;
    }

    return;
}

/*  @brief  Set File ID.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  file_id             (I)     - New File ID (char* string).
 *  @param  status              (IO)    - Error status.
 *  @return Void.
 */
void ser_set_file_id(serfile* sptr, const char* file_id, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!file_id) {
        return (void)(*status = NULL_PARAM);
    }

    memcpy(sptr->file_id, file_id, FILEID_LEN);

    return;
}

/*  @brief  Set LU ID.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  lu_id               (I)     - New LU ID.
 *  @param  status              (IO)    - Error status.
 *  @return Void.
 */
void ser_set_lu_id(serfile* sptr, const int32_t lu_id, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    sptr->lu_id = lu_id;

    return;
}

/*  @brief  Set Color ID.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  color_id            (I)     - New Color ID
 *  @param  status              (IO)    - Error status.
 *  @return Void.
 */
void ser_set_color_id(serfile* sptr, const int32_t color_id, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    /* valid color id value */
    switch (color_id) {
		case MONO:
		case BAYER_RGGB:
		case BAYER_GRBG:
		case BAYER_GBRG:
		case BAYER_BGGR:
		case BAYER_CYYM:
		case BAYER_YCMY:
		case BAYER_YMCY:
		case BAYER_MYYC:
		case RGB:
		case BGR:
            break;
        default:
            return (void)(*status = INVALID_SET_VALUE);
    }

    /* check for switch between 1 byte and 3 byte color ids */
    if (sptr->color_id < 100 && color_id >= 100) {
            return (void)(*status = INVALID_SET_STATE);
    }
    if (sptr->color_id >= 100 && color_id < 100) {
            return (void)(*status = INVALID_SET_STATE);
    }

    sptr->color_id = color_id;

    return;
}

/*  @brief  Set Little Endian.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  little_endian       (I)     - New Little Endian
 *  @param  status              (IO)    - Error status.
 *  @return Void.
 */
void ser_set_little_endian(serfile* sptr, const int32_t little_endian, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }
    
    if (little_endian == LITTLEENDIAN_TRUE || little_endian == LITTLEENDIAN_FALSE) {
        sptr->little_endian = little_endian;
        return;
    }

    return (void)(*status = INVALID_SET_VALUE);
}

/*  @brief  Set Image Width.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  image_width         (I)     - New Image Width.
 *  @param  status              (IO)    - Error status.
 *  @return Void.
 */
void ser_set_image_width(serfile* sptr, const uint32_t image_width, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (sptr->frame_count > 0) {
        return (void)(*status = INVALID_SET_STATE);
    }

    sptr->image_width = image_width;

    return;
}

/*  @brief  Set Image Height. 
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  image_height        (I)     - New Image Height.
 *  @param  status              (IO)    - Error status.
 *  @return Void.
 */
void ser_set_image_height(serfile* sptr, const uint32_t image_height, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (sptr->frame_count > 0) {
        return (void)(*status = INVALID_SET_STATE);
    }

    sptr->image_height = image_height;

    return;
}

/*  @brief  Set Pixel Depth Per Plane.  
 *  @param  sptr                    (I)     - Pointer to serfile.
 *  @param  pixel_depth_per_plane   (I)     - New Pixel Depth Per Plane.  
 *  @param  status                  (IO)    - Error status.
 *  @return Void.
 */
void ser_set_pixel_depth_per_plane(serfile* sptr, const int32_t pixel_depth_per_plane, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    /* pdpp must between a value from 1 - 16 */
    if (16 < pixel_depth_per_plane || pixel_depth_per_plane <= 0) {
        return (void)(*status = INVALID_SET_VALUE);
    }

    /* if frames present, pdpp cannot switch between 1 and 2 bytes */
    if (sptr->frame_count > 0) {
        if (sptr->pixel_depth_per_plane <= 8 && pixel_depth_per_plane > 8) {
            return (void)(*status = INVALID_SET_STATE);
        }
        if (sptr->pixel_depth_per_plane > 8 && pixel_depth_per_plane <= 8) {
            return (void)(*status = INVALID_SET_STATE);
        }
    }

    sptr->pixel_depth_per_plane = pixel_depth_per_plane;

    return;
}

/*  @brief  Set Observer.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  observer            (I)     - New Observer (char* string).
 *  @param  status              (IO)    - Error status.
 *  @return Void.
 */
void ser_set_observer(serfile* sptr, const char* observer, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!observer) {
        return (void)(*status = NULL_PARAM);
    }

    memcpy(sptr->observer, observer, OBSERVER_LEN);

    return;
}

/*  @brief  Set Instrument. 
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  instrument          (I)     - New Instrument (char* string).
 *  @param  status              (IO)    - Error status.
 *  @return Void.
 */
void ser_set_instrument(serfile* sptr, const char* instrument, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!instrument) {
        return (void)(*status = NULL_PARAM);
    }

    memcpy(sptr->instrument, instrument, INSTRUMENT_LEN);

    return;
}

/*  @brief  Set Telescope. 
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  telescope           (I)     - New Telescope (char* string).
 *  @param  status              (IO)    - Error status.
 *  @return Void.
 */
void ser_set_telescope(serfile* sptr, const char* telescope, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (!telescope) {
        return (void)(*status = NULL_PARAM);
    }

    memcpy(sptr->telescope, telescope, TELESCOPE_LEN);

    return;
}

/*  @brief  Set Date Time. 
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  date_time           (I)     - New Date Time.
 *  @param  status              (IO)    - Error status.
 *  @return Void.
 */
void ser_set_date_time(serfile* sptr, const int64_t date_time, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    sptr->date_time = date_time;

    return;
}

/*  @brief  Set Date Time. 
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  date_time_utc       (I)     - New Date Time UTC.
 *  @param  status              (IO)    - Error status.
 *  @return Void.
 */
void ser_set_date_time_utc(serfile* sptr, const int64_t date_time_utc, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    sptr->date_time_utc = date_time_utc;

    return;
}


/*-------------------- Image Symbolic Constants --------------------*/

/* Currently, all SER file frames have just 3 dimensions. */
#define MIN_DIM_IDX         0
#define MAX_DIM_IDX         2

#define DATA_START_SET      178

/*-------------------- Image Routines --------------------*/

/*  @brief Get the size of a target dimension.
 *  @param  sptr    (I)   - Pointer to serfile.
 *  @param  size    (IO)  - Pointer to int.
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
    int temp_size = 0;
    ser_get_key_record(sptr, &temp_size, key, status);
    if (*status) { 
        return;
    }
    *size = temp_size;

    /*  If the first dimension is called, then size will
     *  be set to the color ID of the SER, the size of the
     *  dimension is derived from the color ID by the
     *  following case.
     */
    if (key == COLORID_KEY) {
        *size = *size < 100 ? 1 : 3;
    }

    return;
}

/*  @brief  Returns the number of bytes representing each pixel.
 *
 *  The value returns the total number of bytes to represent
 *  one pixel value. SER files in a multi-plane format like RGB 
 *  or BGR include all color layers in the byte size.
 *
 *  @param  sptr            (I)   - Pointer to serfile.
 *  @param  bytes_per_pixel (IO)  - Pointer to long. 
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

    int number_of_planes = sptr->color_id < 100 ? 1 : 3;
    int pixel_depth = sptr->pixel_depth_per_plane;

    if (pixel_depth <= 8) {
        *bytes_per_pixel = number_of_planes; /* 1 byte per pixel */
    } else {
        *bytes_per_pixel = number_of_planes * 2; /* 2 bytes per pixel */
    }

    return;
}

/*  @brief  Returns the byte size of a single frame
 *  @param  sptr        (I)   - Pointer to serfile.
 *  @param  byte_size   (IO)  - Pointer to long.
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

    unsigned long bytes_per_pixel = 0;
    ser_get_bytes_per_pixel(sptr, &bytes_per_pixel, status);
    if (*status) { 
        return;
    }

    int32_t width = sptr->image_width;
    int32_t height = sptr->image_height;

    *byte_size = bytes_per_pixel * width * height;

    return;
}

/*  @brief  Read the image frame at the index.
 *  
 *  The entire frame is returned, ensure the dest buffer has the
 *  appropriate capacity. Data between 1-8 bits is NOT shifted 
 *  when data is returned.
 *  
 *  @param  sptr    (I)   - Pointer to serfile.
 *  @param  dest    (IO)  - Pointer to destination buffer.
 *  @param  idx     (I)   - Index of the frame.
 *  @param  status  (IO)  - Error status. 
 *  @return Void.
 */
void ser_read_frame(serfile* sptr, void* dest, size_t idx, int* status) {
    if (!sptr) { 
        return (void)(*status = NULL_SPTR); 
    }

    if (!dest) { 
        return (void)(*status = NULL_DEST_BUFF); 
    }

    size_t frame_count = sptr->frame_count;

    if (idx >= frame_count) {
        return (void)(*status = INVALID_FRAME_IDX); 
    }

    unsigned long frame_byte_size = 0;
    ser_get_frame_byte_size(sptr, &frame_byte_size, status);
    if (*status) { 
        return; 
    }

    unsigned long frame_offset = DATA_START_SET + (frame_byte_size * idx);

    size_t bytes_read = sptr->reader(sptr->io_context, dest, frame_byte_size, frame_offset);
    if (bytes_read < frame_byte_size) {
        *status = READ_ERROR;
    }

    return;
}

/*  @brief  Write image frame at the index.
 *
 *  The byte size of a whole frame is written from data.
 *  Data between 1-8 bits is NOT shifted when the data is written.
 *  If the SER does not have a trailer, nothing is done with timestamp.
 *
 *  @param  sptr        (I)   - Pointer to serfile.
 *  @param  data        (I)   - Pointer to data buffer.
 *  @param  timestamp   (I)   - Timestamp.
 *  @param  status      (IO)  - Error status. 
 *  @return Void.
 */
void ser_append_frame(serfile* sptr, const void* data, uint64_t timestamp, int* status) {
    if (!sptr) { 
        return (void)(*status = NULL_SPTR); 
    }

    if (!data) { 
        return (void)(*status = NULL_PARAM); 
    }

    size_t frame_count = sptr->frame_count;

    size_t frame_byte_size = 0;
    ser_get_frame_byte_size(sptr, &frame_byte_size, status);
    if (*status) { 
        return; 
    }

    unsigned long frame_offset = DATA_START_SET + (frame_byte_size * frame_count);

    size_t bytes_written = sptr->writer(
            sptr->io_context,
            data,
            frame_byte_size,
            frame_offset
    );
    if (bytes_written < frame_byte_size) {
        return (void)(*status = IMAGE_WRITE_WARN);
    }
    sptr->frame_count += 1;

    if (sptr->has_trailer) {
        sptr->timestamp_count += 1;
        size_t new_trailer_size = sptr->timestamp_count * sizeof(int64_t);
        sptr->timestamps = (int64_t*)realloc(sptr->timestamps, new_trailer_size);
        sptr->timestamps[sptr->timestamp_count - 1] = timestamp;
    }

    return;
}

/*-------------------- Trailer Routines --------------------*/

/*  @brief Enable the optional timestamp trailer.
 *
 *  Note that this may only be called in the case that there
 *  is no image data present in the SER. Attempts to call
 *  this method after data has been written with no associated
 *  timestamps will result in an error.
 *
 *  @param  sptr    (I)     - Pointer to serfile.
 *  @param  status  (IO)    - Error status.
 *  @return Void.
 */
void ser_enable_trailer(serfile* sptr, int* status) {
    if (!sptr) {
        return (void)(*status = NULL_SPTR);
    }

    if (sptr->frame_count != 0 && !sptr->has_trailer) {
        return (void)(*status = INVALID_TRAILER_ENABLE);
    }

    sptr->has_trailer = true;

    return;
}

/*  @brief  Read trailer time stamp at index.
 *  @param  sptr    (I)     - Pointer to serfile.
 *  @param  dest    (IO)    - Pointer to data buffer.
 *  @param  idx     (I)     - Index of time stamp.
 *  @param  status  (IO)    - Error status.
 *  @return Void.
 */
void ser_get_timestamp(serfile* sptr, int64_t* dest, size_t idx, int* status) {
    if (!sptr) { 
        return (void)(*status = NULL_SPTR); 
    }

    if (!dest) { 
        return (void)(*status = NULL_DEST_BUFF); 
    }

    if (!sptr->has_trailer) {
        return (void)(*status = TRAILER_DNE);
    }

    if (idx >= sptr->timestamp_count) {
        return (void)(*status = INVALID_TRAILER_IDX); 
    }

    *dest = sptr->timestamps[idx];

    return;
}


#endif /* CSERIO_IMPLEMENTATION */

#endif /* CSERIO_H */

