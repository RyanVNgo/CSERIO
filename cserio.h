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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>


/*------------------------------------------------------------------*/
/* CSERIO Version */ 
/*------------------------------------------------------------------*/

#define CSERIO_MAJOR                        4
#define CSERIO_MINOR                        0
#define CSERIO_MICRO                        0


/*------------------------------------------------------------------*/
/* CSERIO Errors */ 
/*------------------------------------------------------------------*/

/*-------------------- Core Errors --------------------*/

#define NO_ERROR                            0

#define MEM_ALLOC                           101
#define NULL_SPTR                           102
#define NULL_DEST_BUFF                      103
#define NULL_PARAM                          104
#define NULL_SPTRPTR                        105
#define SPTR_OCCUPIED                       106

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
#define INVALID_CHAR_STRING                 323

/*-------------------- Image Routine Errors --------------------*/

#define INVALID_DIM_IDX                     401
#define INVALID_FRAME_IDX                   402
#define INVALID_FRAME_SIZE                  403

#define IMAGE_WRITE_WARN                    411

/*-------------------- Trailer Routine Errors --------------------*/

#define TRAILER_DNE                         501

#define INVALID_TRAILER_ENABLE              511
#define INVALID_TRAILER_IDX                 512

#define TRAILER_CLOSE_WARN                  521


/*------------------------------------------------------------------*/
/* CSERIO Constants */ 
/*------------------------------------------------------------------*/

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


/*------------------------------------------------------------------*/
/* CSERIO SER Structure and Routines */ 
/*------------------------------------------------------------------*/

/*-------------------- SER Structure --------------------*/

/*  serfile is the primary structure used to interact with nearly all
 *  CSERIO routines. 
 *
 *  This structure should not be directly interacted with by 
 *  the user.
 */
typedef struct serfile serfile;


/*-------------------- Core Routines --------------------*/

/*  @brief  Provides the Major, Minor, and Micro numbers for
 *          the current version of CSERIO.
 *  @param  major       (IO)    - Pointer to Major int.
 *  @param  minor       (IO)    - Pointer to Minor int.
 *  @param  micro       (IO)    - Pointer to Micro int.
 *  @return Void.
 */
void cserio_version_number(int* major, int* minor, int* micro);

/*-------------------- SER Access Routines --------------------*/

/*  @brief  Create a new SER file.
 *
 *  @param  sptr        (IO)    - Pointer to pointer of a serfile.
 *  @param  path        (I)     - File path.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_create_file(serfile** sptr, const char* path, int* status);

/*  @brief  Opens existing SER file
 *
 *  @param  sptr        (IO)    - Pointer to a pointer of a serfile.
 *  @param  path        (I)     - SER file path.
 *  @param  mode        (I)     - Access type (READONLY or READWRITE).
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_open_file(serfile** sptr, const char* path, int mode, int* status);

/*  @brief  Close SER file
 *
 *  Closes the serfile and frees the structure. Parameter sptr will
 *  be set to NULL.
 *
 *  @param  sptr      (IO)  - Pointer to a serfile.
 *  @param  status    (IO)  - Error status.
 *  @return Error Status.
 */
int ser_close_file(serfile* sptr, int* status);

/*-------------------- Header Routines --------------------*/

/*  @brief  Returns number of records in the header
 *
 *  Note that as of Version 3 SER files, the number of records 
 *  in a header is a constant 13.
 *
 *  @param  sptr        (I)   - Pointer to serfile.
 *  @param  rec_count   (IO)  - Number of records.
 *  @param  status      (IO)  - Error status.
 *  @return Error Status.
 */
int ser_read_rec_count(serfile* sptr, int* rec_count, int* status);

/*  @brief  Read File ID
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  file_id     (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_file_id(const serfile* sptr, char* file_id, int* status);

/*  @brief  Read LU ID
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  lu_id       (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_lu_id(const serfile* sptr, int32_t* lu_id, int* status);

/*  @brief  Read Color ID
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  color_id    (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_color_id(const serfile* sptr, int32_t* color_id, int* status);

/*  @brief  Read Litte Endian
 *  @param  sptr            (I)     - Pointer to serfile.
 *  @param  little_endian   (IO)    - Destination buffer.
 *  @param  status          (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_little_endian(const serfile* sptr, int32_t* little_endian, int* status);

/*  @brief  Read Image Width
 *  @param  sptr            (I)     - Pointer to serfile.
 *  @param  image_width     (IO)    - Destination buffer.
 *  @param  status          (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_image_width(const serfile* sptr, int32_t* image_width, int* status);

/*  @brief  Read Image Height 
 *  @param  sptr            (I)     - Pointer to serfile.
 *  @param  image_height    (IO)    - Destination buffer.
 *  @param  status          (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_image_height(const serfile* sptr, int32_t* image_height, int* status);

/*  @brief  Read Pixel Depth Per Plane
 *  @param  sptr                    (I)     - Pointer to serfile.
 *  @param  pixel_depth_per_plane   (IO)    - Destination buffer.
 *  @param  status                  (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_pixel_depth_per_plane(const serfile* sptr, int32_t* pixel_depth_per_plane, int* status);

/*  @brief  Read Frame Count
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  frame_count (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_frame_count(const serfile* sptr, int32_t* frame_count, int* status);

/*  @brief  Read Observer
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  observer    (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_observer(const serfile* sptr, char* observer, int* status);

/*  @brief  Read Instrument 
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  instrument  (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_instrument(const serfile* sptr, char* instrument, int* status);

/*  @brief  Read Telescope
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  telescope   (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_telescope(const serfile* sptr, char* telescope, int* status);

/*  @brief  Read Date Time
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  date_time   (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_date_time(const serfile* sptr, int64_t* date_time, int* status);

/*  @brief  Read Date Time UTC
 *  @param  sptr            (I)     - Pointer to serfile.
 *  @param  date_time_utc   (IO)    - Destination buffer.
 *  @param  status          (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_date_time_utc(const serfile* sptr, int64_t* date_time_utc, int* status);

/*  @brief  Write File ID.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  file_id             (I)     - New File ID (char* string).
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_file_id(serfile* sptr, const char* file_id, int* status);

/*  @brief  Write LU ID.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  lu_id               (I)     - New LU ID.
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_lu_id(serfile* sptr, const int32_t lu_id, int* status);

/*  @brief  Write Color ID.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  color_id            (I)     - New Color ID
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_color_id(serfile* sptr, const int32_t color_id, int* status);

/*  @brief  Write Little Endian.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  little_endian       (I)     - New Little Endian
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_little_endian(serfile* sptr, const int32_t little_endian, int* status);

/*  @brief  Write Image Width.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  image_width         (I)     - New Image Width.
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_image_width(serfile* sptr, const uint32_t image_width, int* status);

/*  @brief  Write Image Height. 
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  image_height        (I)     - New Image Height.
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_image_height(serfile* sptr, const uint32_t image_height, int* status);

/*  @brief  Write Pixel Depth Per Plane.  
 *  @param  sptr                    (I)     - Pointer to serfile.
 *  @param  pixel_depth_per_plane   (I)     - New Pixel Depth Per Plane.  
 *  @param  status                  (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_pixel_depth_per_plane(serfile* sptr, const int32_t pixel_depth_per_plane, int* status);

/*  @brief  Write Observer.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  observer            (I)     - New Observer (char* string).
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_observer(serfile* sptr, const char* observer, int* status);

/*  @brief  Write Instrument. 
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  instrument          (I)     - New Instrument (char* string).
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_instrument(serfile* sptr, const char* instrument, int* status);

/*  @brief  Write Telescope. 
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  telescope           (I)     - New Telescope (char* string).
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_telescope(serfile* sptr, const char* telescope, int* status);

/*  @brief  Write Date Time. 
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  date_time           (I)     - New Date Time.
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_date_time(serfile* sptr, const int64_t date_time, int* status);

/*  @brief  Write Date Time. 
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  date_time_utc       (I)     - New Date Time UTC.
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_date_time_utc(serfile* sptr, const int64_t date_time_utc, int* status);

/*-------------------- Image Routines --------------------*/

/*  @brief  Get number of planes per frame.
 *  @param  sptr    (I)     - Pointer to serfile.
 *  @param  nop     (IO)    - Destination buffer.
 *  @param  status  (IO)    - Error status.
 *  @return Error status.
 */
int ser_get_number_of_planes(serfile* sptr, int* nop, int* status);

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
int ser_get_bytes_per_pixel(serfile* sptr, unsigned long* bytes_per_pixel, int* status); 

/*  @brief  Returns the byte size of a single frame
 *  @param  sptr        (I)   - Pointer to serfile.
 *  @param  byte_size   (IO)  - Pointer to long.
 *  @param  status      (IO)  - Error status.
 *  @return Error status.
 */
int ser_get_frame_byte_size(serfile* sptr, unsigned long* byte_size, int* status);

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
 *  @return Error Status.
 */
int ser_read_frame(serfile* sptr, void* dest, size_t idx, int* status);

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
 *  @return Error Status.
 */
int ser_append_frame(serfile* sptr, const void* data, uint64_t timestamp, int* status);

/*-------------------- Trailer Routines --------------------*/

/*  @brief  Read trailer time stamp at index.
 *  @param  sptr    (I)     - Pointer to serfile.
 *  @param  dest    (IO)    - Pointer to data buffer.
 *  @param  idx     (I)     - Index of time stamp.
 *  @param  status  (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_timestamp(serfile* sptr, int64_t* dest, size_t idx, int* status);


/*-------------------- Memory-Backed SER Access Routines --------------------*/

/*  @brief  Opens new in-memory SER file.
 *  @param  sptr        (IO)    - Pointer to a pointer of a serfile.
 *  @param  status      (IO)    - Error status.
 *  @return Error status.
 */
int ser_create_memory(serfile** sptr, int* status);

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
 *  @return Error status.
 */
int ser_open_view(serfile** sptr, uint8_t* data, size_t size, int mode, int* status);

/*  @brief  Opens/Copies in-memory SER file.
 *
 *  Memory is allocated and managed by the serfile.
 *
 *  @param  sptr        (IO)    - Pointer to a pointer of a serfile.
 *  @param  data        (I)     - Pointer to data.
 *  @param  size        (I)     - Size to initially allocate / copy over.
 *  @param  mode        (I)     - Access type (READONLY or READWRITE).
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_open_memory(serfile** sptr, const uint8_t* data, size_t size, int mode, int* status);

/*  @brief  Close in-memory SER file
 *
 *  Closes the serfile and frees the structure. Parameter sptr will
 *  be set to NULL.
 *
 *  @param  sptr        (IO)    - Pointer to a serfile.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_close_memory(serfile* sptr, int* status);


/*------------------------------------------------------------------*/
/* CSERIO Implementation */ 
/*------------------------------------------------------------------*/

#if defined(CSERIO_IMPLEMENTATION)


/*-------------------- Structure Implementation --------------------*/

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
    bool owns_buffer;
} serMem;


/*-------------------- Internal Routines --------------------*/

#define RETURN_IF_STATUS_IS_ERROR(status)       \
    do {                                        \
        if ( *status ) { return (*status); }    \
    } while(0)                                  \

#define RETURN_IF_NULL_SPTRPTR(sptr, status)                \
    do {                                                    \
        if ( !sptr ) { return (*status = NULL_SPTRPTR); }   \
    } while(0)                                              \

#define RETURN_IF_SPTR_OCCUPIED(sptr, status)               \
    do {                                                    \
        if ( *sptr ) { return (*status = SPTR_OCCUPIED); }  \
    } while(0)                                              \

#define RETURN_IF_NULL_SPTR(sptr, status)               \
    do {                                                \
        if ( !sptr ) { return (*status = NULL_SPTR); }  \
    } while(0)                                          \


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

static void ser_header_initializations(serfile* sptr) {
    memset(sptr->file_id,           0, FILEID_LEN);
    sptr->lu_id =                   0;
    sptr->color_id =                MONO;
    sptr->little_endian =           LITTLEENDIAN_TRUE;
    sptr->image_width =             0;
    sptr->image_height =            0;
    sptr->pixel_depth_per_plane =   8;
    sptr->frame_count =             0;
    memset(sptr->observer,          0, OBSERVER_LEN);
    memset(sptr->instrument,        0, INSTRUMENT_LEN);
    memset(sptr->telescope,         0, TELESCOPE_LEN);
    sptr->date_time =               0;
    sptr->date_time_utc =           0;
}


/*-------------------- Core Routines --------------------*/

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

int ser_create_file(serfile** sptr, const char* path, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTRPTR(sptr, status);
	RETURN_IF_SPTR_OCCUPIED(sptr, status);

    if (!path) {
        return (*status = NULL_PATH);
    }

    FILE* file;
    if ((file = fopen(path, "r"))) {
        fclose(file);
        return (*status = FILE_EXISTS);
    }

    file = fopen(path, "w+b");
    if (!file) {
        return (*status = FILE_OPEN_ERROR);
    }

    *sptr = (serfile*)malloc(sizeof(serfile));
    if (!*sptr) {
        fclose(file);
        return (*status = MEM_ALLOC);
    }

    (*sptr)->io_context = file;
    (*sptr)->reader = ser_file_read;
    (*sptr)->writer = ser_file_write;
    (*sptr)->access_mode = READWRITE;

    ser_header_initializations(*sptr);
    /*
    memset((*sptr)->file_id, 0, FILEID_LEN);
    (*sptr)->lu_id = 0;
    (*sptr)->color_id = MONO;
    (*sptr)->little_endian = LITTLEENDIAN_TRUE;
    (*sptr)->image_width = 0;
    (*sptr)->image_height = 0;
    (*sptr)->pixel_depth_per_plane = 8;
    (*sptr)->frame_count = 0;
    memset((*sptr)->observer, 0, OBSERVER_LEN);
    memset((*sptr)->instrument, 0, INSTRUMENT_LEN);
    memset((*sptr)->telescope, 0, TELESCOPE_LEN);
    (*sptr)->date_time = 0;
    (*sptr)->date_time_utc = 0;
    */

    (*sptr)->has_trailer = (*sptr)->date_time <= 0 ? false : true;
    (*sptr)->timestamps = NULL;
    (*sptr)->timestamp_count = 0;

    return (*status);
}

int ser_open_file(serfile** sptr, const char* path, int mode, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTRPTR(sptr, status);
	RETURN_IF_SPTR_OCCUPIED(sptr, status);

    if (!path) {
        return (*status = NULL_PATH);
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
        return (*status = FILE_DNE);
    }

    /* retrieve size of file and return to start */
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    /* determine validity of header */
    if (file_size < HDR_SIZE) {
        fclose(file);
        return (*status = INVALID_STRUCTURE);
    }

    /* allocate memory for serfile */
    *sptr = (serfile*)malloc(sizeof(serfile));
    if (!*sptr) {
        fclose(file);
        return (*status = MEM_ALLOC);
    }

    /* general setup */
    (*sptr)->io_context = file;
    (*sptr)->reader = ser_file_read;
    (*sptr)->writer = ser_file_write;
    (*sptr)->access_mode = mode == READWRITE ? READWRITE : READONLY;
    (*sptr)->reader(file, (*sptr)->file_id, FILEID_LEN, FILEID_KEY);
    (*sptr)->reader(file, &(*sptr)->lu_id, LUID_LEN, LUID_KEY);
    (*sptr)->reader(file, &(*sptr)->color_id, COLORID_LEN, COLORID_KEY);
    (*sptr)->reader(file, &(*sptr)->little_endian, LITTLEENDIAN_LEN, LITTLEENDIAN_KEY);
    (*sptr)->reader(file, &(*sptr)->image_width, IMAGEWIDTH_LEN, IMAGEWIDTH_KEY);
    (*sptr)->reader(file, &(*sptr)->image_height, IMAGEHEIGHT_LEN, IMAGEHEIGHT_KEY);
    (*sptr)->reader(file, &(*sptr)->pixel_depth_per_plane, PIXELDEPTHPERPLANE_LEN, PIXELDEPTHPERPLANE_KEY);
    (*sptr)->reader(file, &(*sptr)->frame_count, FRAMECOUNT_LEN, FRAMECOUNT_KEY);
    (*sptr)->reader(file, (*sptr)->observer, OBSERVER_LEN, OBSERVER_KEY);
    (*sptr)->reader(file, (*sptr)->instrument, INSTRUMENT_LEN, INSTRUMENT_KEY);
    (*sptr)->reader(file, (*sptr)->telescope, TELESCOPE_LEN, TELESCOPE_KEY);
    (*sptr)->reader(file, &(*sptr)->date_time, DATETIME_LEN, DATETIME_KEY);
    (*sptr)->reader(file, &(*sptr)->date_time_utc, DATETIMEUTC_LEN, DATETIMEUTC_KEY);
    (*sptr)->has_trailer = (*sptr)->date_time <= 0 ? false : true;
    (*sptr)->timestamps = NULL;
    (*sptr)->timestamp_count = 0;

    /* determine if valid hdr + data or hdr + data + trailer */
    size_t frame_byte_size = 0;
    ser_get_frame_byte_size(*sptr, &frame_byte_size, status);
    size_t trailer_offset = HDR_SIZE + (*sptr)->frame_count * frame_byte_size;

    if ((*sptr)->has_trailer) {
        if (file_size == trailer_offset + (*sptr)->frame_count * sizeof(uint64_t)) {
            (*sptr)->timestamps = (int64_t*)realloc((*sptr)->timestamps, (*sptr)->frame_count * sizeof(uint64_t));
            (*sptr)->timestamp_count = (*sptr)->frame_count;
            (*sptr)->reader(
                    (*sptr)->io_context,
                    (*sptr)->timestamps,
                    (*sptr)->frame_count * sizeof(uint64_t),
                    trailer_offset
            );
            return (*status);
        }
    } else {
        if (file_size == trailer_offset) {
            return (*status);
        }
    }

    /* if reached, invalid structure */
    fclose(file);
    free((*sptr));
    *sptr = NULL;
    return (*status = INVALID_STRUCTURE);
}

int ser_close_file(serfile* sptr, int* status) {
	RETURN_IF_NULL_SPTR(sptr, status);

    if (sptr->access_mode == READWRITE) {
        sptr->writer(sptr->io_context, sptr->file_id, FILEID_LEN, FILEID_KEY);
        sptr->writer(sptr->io_context, &sptr->lu_id, LUID_LEN, LUID_KEY);
        sptr->writer(sptr->io_context, &sptr->color_id, COLORID_LEN, COLORID_KEY);
        sptr->writer(sptr->io_context, &sptr->little_endian, LITTLEENDIAN_LEN, LITTLEENDIAN_KEY);
        sptr->writer(sptr->io_context, &sptr->image_width, IMAGEWIDTH_LEN, IMAGEWIDTH_KEY);
        sptr->writer(sptr->io_context, &sptr->image_height, IMAGEHEIGHT_LEN, IMAGEHEIGHT_KEY);
        sptr->writer(sptr->io_context, &sptr->pixel_depth_per_plane, PIXELDEPTHPERPLANE_LEN, PIXELDEPTHPERPLANE_KEY);
        sptr->writer(sptr->io_context, &sptr->frame_count, FRAMECOUNT_LEN, FRAMECOUNT_KEY);
        sptr->writer(sptr->io_context, sptr->observer, OBSERVER_LEN, OBSERVER_KEY);
        sptr->writer(sptr->io_context, sptr->instrument, INSTRUMENT_LEN, INSTRUMENT_KEY);
        sptr->writer(sptr->io_context, sptr->telescope, TELESCOPE_LEN, TELESCOPE_KEY);
        sptr->writer(sptr->io_context, &sptr->date_time, DATETIME_LEN, DATETIME_KEY);
        sptr->writer(sptr->io_context, &sptr->date_time_utc, DATETIMEUTC_LEN, DATETIMEUTC_KEY);
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
    return (*status);
}

/*-------------------- Header Routines --------------------*/

int ser_read_rec_count(serfile* sptr, int* rec_count, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!rec_count) { 
        return (*status = NULL_PARAM); 
    }

    *rec_count = HDR_UNIT_COUNT;
    
    return (*status);
}

int ser_read_file_id(const serfile* sptr, char* file_id, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!file_id) { 
        return (*status = NULL_DEST_BUFF); 
    }

    memcpy(file_id, sptr->file_id, FILEID_LEN);

    return (*status);
}

int ser_read_lu_id(const serfile* sptr, int32_t* lu_id, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!lu_id) {
        return (*status = NULL_DEST_BUFF);
    }

    *lu_id = sptr->lu_id;

    return (*status);
}

int ser_read_color_id(const serfile* sptr, int32_t* color_id, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!color_id) {
        return (*status = NULL_DEST_BUFF);
    }

    *color_id = sptr->color_id;

    return (*status);
}

int ser_read_little_endian(const serfile* sptr, int32_t* little_endian, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!little_endian) {
        return (*status = NULL_DEST_BUFF);
    }

    *little_endian = sptr->little_endian;

    return (*status);
}

int ser_read_image_width(const serfile* sptr, int32_t* image_width, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!image_width) {
        return (*status = NULL_DEST_BUFF);
    }

    *image_width = sptr->image_width;

    return (*status);
}

int ser_read_image_height(const serfile* sptr, int32_t* image_height, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!image_height) {
        return (*status = NULL_DEST_BUFF);
    }

    *image_height= sptr->image_height;

    return (*status);
}

int ser_read_pixel_depth_per_plane(const serfile* sptr, int32_t* pixel_depth_per_plane, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!pixel_depth_per_plane) {
        return (*status = NULL_DEST_BUFF);
    }

    *pixel_depth_per_plane = sptr->pixel_depth_per_plane;

    return (*status);
}

int ser_read_frame_count(const serfile* sptr, int32_t* frame_count, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!frame_count) {
        return (*status = NULL_DEST_BUFF);
    }

    *frame_count = sptr->frame_count;

    return (*status);
}

int ser_read_observer(const serfile* sptr, char* observer, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!observer) {
        return (*status = NULL_DEST_BUFF);
    }

    memcpy(observer, sptr->observer, OBSERVER_LEN);

    return (*status);
}

int ser_read_instrument(const serfile* sptr, char* instrument, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!instrument) {
        return (*status = NULL_DEST_BUFF);
    }

    memcpy(instrument, sptr->instrument, INSTRUMENT_LEN);

    return (*status);
}

int ser_read_telescope(const serfile* sptr, char* telescope, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!telescope) {
        return (*status = NULL_DEST_BUFF);
    }

    memcpy(telescope, sptr->telescope, TELESCOPE_LEN);

    return (*status);
}

int ser_read_date_time(const serfile* sptr, int64_t* date_time, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!date_time) {
        return (*status = NULL_DEST_BUFF);
    }

    *date_time = sptr->date_time;

    return (*status);
}

int ser_read_date_time_utc(const serfile* sptr, int64_t* date_time_utc, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!date_time_utc) {
        return (*status = NULL_DEST_BUFF);
    }

    *date_time_utc = sptr->date_time_utc;

    return (*status);
}

int ser_write_file_id(serfile* sptr, const char* file_id, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!file_id) {
        return (*status = NULL_PARAM);
    }

    if (sptr->access_mode == READONLY) {
        return (*status = WRITE_ON_READONLY);
    }

    memcpy(sptr->file_id, file_id, FILEID_LEN);
    sptr->writer(sptr->io_context, sptr->file_id, FILEID_LEN, FILEID_KEY);

    return (*status);
}

int ser_write_lu_id(serfile* sptr, const int32_t lu_id, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (sptr->access_mode == READONLY) {
        return (*status = WRITE_ON_READONLY);
    }

    sptr->lu_id = lu_id;
    sptr->writer(sptr->io_context, &sptr->lu_id, LUID_LEN, LUID_KEY);

    return (*status);
}

int ser_write_color_id(serfile* sptr, const int32_t color_id, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (sptr->access_mode == READONLY) {
        return (*status = WRITE_ON_READONLY);
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
            return (*status = INVALID_SET_VALUE);
    }

    /* check for switch between 1 byte and 3 byte color ids */
    if (sptr->color_id < 100 && color_id >= 100) {
            return (*status = INVALID_SET_STATE);
    }
    if (sptr->color_id >= 100 && color_id < 100) {
            return (*status = INVALID_SET_STATE);
    }

    sptr->color_id = color_id;
    sptr->writer(sptr->io_context, &sptr->color_id, COLORID_LEN, COLORID_KEY);

    return (*status);
}

int ser_write_little_endian(serfile* sptr, const int32_t little_endian, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);
    
    if (sptr->access_mode == READONLY) {
        return (*status = WRITE_ON_READONLY);
    }

    if (little_endian == LITTLEENDIAN_TRUE || little_endian == LITTLEENDIAN_FALSE) {
        sptr->little_endian = little_endian;
        sptr->writer(sptr->io_context, &sptr->little_endian, LITTLEENDIAN_LEN, LITTLEENDIAN_KEY);
        return (*status);
    }

    return (*status = INVALID_SET_VALUE);
}

int ser_write_image_width(serfile* sptr, const uint32_t image_width, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (sptr->access_mode == READONLY) {
        return (*status = WRITE_ON_READONLY);
    }

    if (sptr->frame_count > 0) {
        return (*status = INVALID_SET_STATE);
    }

    sptr->image_width = image_width;
    sptr->writer(sptr->io_context, &sptr->image_width, IMAGEWIDTH_LEN, IMAGEWIDTH_KEY);

    return (*status);
}

int ser_write_image_height(serfile* sptr, const uint32_t image_height, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (sptr->access_mode == READONLY) {
        return (*status = WRITE_ON_READONLY);
    }

    if (sptr->frame_count > 0) {
        return (*status = INVALID_SET_STATE);
    }

    sptr->image_height = image_height;
    sptr->writer(sptr->io_context, &sptr->image_height, IMAGEHEIGHT_LEN, IMAGEHEIGHT_KEY);

    return (*status);
}

int ser_write_pixel_depth_per_plane(serfile* sptr, const int32_t pixel_depth_per_plane, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (sptr->access_mode == READONLY) {
        return (*status = WRITE_ON_READONLY);
    }

    /* pdpp must between a value from 1 - 16 */
    if (16 < pixel_depth_per_plane || pixel_depth_per_plane <= 0) {
        return (*status = INVALID_SET_VALUE);
    }

    /* if frames present, pdpp cannot switch between 1 and 2 bytes */
    if (sptr->frame_count > 0) {
        if (sptr->pixel_depth_per_plane <= 8 && pixel_depth_per_plane > 8) {
            return (*status = INVALID_SET_STATE);
        }
        if (sptr->pixel_depth_per_plane > 8 && pixel_depth_per_plane <= 8) {
            return (*status = INVALID_SET_STATE);
        }
    }

    sptr->pixel_depth_per_plane = pixel_depth_per_plane;
    sptr->writer(sptr->io_context, &sptr->pixel_depth_per_plane, PIXELDEPTHPERPLANE_LEN, PIXELDEPTHPERPLANE_KEY);

    return (*status);
}

int ser_write_observer(serfile* sptr, const char* observer, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (sptr->access_mode == READONLY) {
        return (*status = WRITE_ON_READONLY);
    }

    if (!observer) {
        return (*status = NULL_PARAM);
    }

    memcpy(sptr->observer, observer, OBSERVER_LEN);
    sptr->writer(sptr->io_context, sptr->observer, OBSERVER_LEN, OBSERVER_KEY);

    return (*status);
}

int ser_write_instrument(serfile* sptr, const char* instrument, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (sptr->access_mode == READONLY) {
        return (*status = WRITE_ON_READONLY);
    }

    if (!instrument) {
        return (*status = NULL_PARAM);
    }

    memcpy(sptr->instrument, instrument, INSTRUMENT_LEN);
    sptr->writer(sptr->io_context, sptr->instrument, INSTRUMENT_LEN, INSTRUMENT_KEY);

    return (*status);
}

int ser_write_telescope(serfile* sptr, const char* telescope, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (sptr->access_mode == READONLY) {
        return (*status = WRITE_ON_READONLY);
    }

    if (!telescope) {
        return (*status = NULL_PARAM);
    }

    memcpy(sptr->telescope, telescope, TELESCOPE_LEN);
    sptr->writer(sptr->io_context, sptr->telescope, TELESCOPE_LEN, TELESCOPE_KEY);

    return (*status);
}

int ser_write_date_time(serfile* sptr, const int64_t date_time, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (sptr->access_mode == READONLY) {
        return (*status = WRITE_ON_READONLY);
    }

    /* if frames are present and the new data_time would change trailer state, fail */
    if (sptr->frame_count > 0) {
        /* has trailer -> no trailer */
        if (sptr->date_time > 0 && date_time <= 0) {
            return (*status = INVALID_SET_STATE);
        }
        /* no trailer -> has trailer */
        if (sptr->date_time <= 0 && date_time > 0) {
            return (*status = INVALID_SET_STATE);
        }
    }

    sptr->date_time = date_time;
    sptr->has_trailer = sptr->date_time <= 0 ? false : true;
    sptr->writer(sptr->io_context, &sptr->date_time, DATETIME_LEN, DATETIME_KEY);

    return (*status);
}

int ser_write_date_time_utc(serfile* sptr, const int64_t date_time_utc, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (sptr->access_mode == READONLY) {
        return (*status = WRITE_ON_READONLY);
    }

    sptr->date_time_utc = date_time_utc;
    sptr->writer(sptr->io_context, &sptr->date_time_utc, DATETIMEUTC_LEN, DATETIMEUTC_KEY);

    return (*status);
}


/*-------------------- Image Routines --------------------*/

int ser_get_number_of_planes(serfile* sptr, int* nop, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!nop) {
        return (*status = NULL_PARAM);
    }

    *nop = sptr->color_id < 100 ? 1 : 3;

    return (*status);
}

int ser_get_bytes_per_pixel(serfile* sptr, unsigned long* bytes_per_pixel, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!bytes_per_pixel) { 
        return (*status = NULL_PARAM); 
    }

    int number_of_planes = sptr->color_id < 100 ? 1 : 3;
    int pixel_depth = sptr->pixel_depth_per_plane;

    if (pixel_depth <= 8) {
        *bytes_per_pixel = number_of_planes; /* 1 byte per pixel */
    } else {
        *bytes_per_pixel = number_of_planes * 2; /* 2 bytes per pixel */
    }

    return (*status);
}

int ser_get_frame_byte_size(serfile* sptr, unsigned long* byte_size, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!byte_size) { 
        return (*status = NULL_PARAM); 
    }

    unsigned long bytes_per_pixel = 0;
    ser_get_bytes_per_pixel(sptr, &bytes_per_pixel, status);
    if (*status) { 
        return (*status);
    }

    int32_t width = sptr->image_width;
    int32_t height = sptr->image_height;

    *byte_size = bytes_per_pixel * width * height;

    return (*status);
}

int ser_read_frame(serfile* sptr, void* dest, size_t idx, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!dest) { 
        return (*status = NULL_DEST_BUFF); 
    }

    if (idx >= sptr->frame_count) {
        return (*status = INVALID_FRAME_IDX); 
    }

    unsigned long frame_byte_size = 0;
    ser_get_frame_byte_size(sptr, &frame_byte_size, status);
    if (*status) { 
        return (*status); 
    }

    unsigned long frame_offset = HDR_SIZE + (frame_byte_size * idx);

    size_t bytes_read = sptr->reader(sptr->io_context, dest, frame_byte_size, frame_offset);
    if (bytes_read < frame_byte_size) {
        *status = READ_ERROR;
    }

    return (*status);
}

int ser_append_frame(serfile* sptr, const void* data, uint64_t timestamp, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (sptr->access_mode == READONLY) {
        return (*status = WRITE_ON_READONLY);
    }

    if (!data) { 
        return (*status = NULL_PARAM); 
    }

    size_t frame_count = sptr->frame_count;

    size_t frame_byte_size = 0;
    ser_get_frame_byte_size(sptr, &frame_byte_size, status);
    if (*status) { 
        return (*status); 
    }

    if (frame_byte_size == 0) {
        return (*status = INVALID_FRAME_SIZE);
    }

    unsigned long frame_offset = HDR_SIZE + (frame_byte_size * frame_count);

    size_t bytes_written = sptr->writer(
            sptr->io_context,
            data,
            frame_byte_size,
            frame_offset
    );
    if (bytes_written < frame_byte_size) {
        return (*status = IMAGE_WRITE_WARN);
    }
    sptr->frame_count += 1;

    if (sptr->has_trailer) {
        sptr->timestamp_count += 1;
        size_t new_trailer_size = sptr->timestamp_count * sizeof(int64_t);
        sptr->timestamps = (int64_t*)realloc(sptr->timestamps, new_trailer_size);
        sptr->timestamps[sptr->timestamp_count - 1] = timestamp;
    }

    return (*status);
}

/*-------------------- Trailer Routines --------------------*/

int ser_read_timestamp(serfile* sptr, int64_t* dest, size_t idx, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTR(sptr, status);

    if (!dest) { 
        return (*status = NULL_DEST_BUFF); 
    }

    if (!sptr->has_trailer) {
        return (*status = TRAILER_DNE);
    }

    if (idx >= sptr->timestamp_count) {
        return (*status = INVALID_TRAILER_IDX); 
    }

    *dest = sptr->timestamps[idx];

    return (*status);
}

/*-------------------- Memory-Backed SER Access Routines --------------------*/

int ser_create_memory(serfile** sptr, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTRPTR(sptr, status);
	RETURN_IF_SPTR_OCCUPIED(sptr, status);

    /* allocate memory for serfile */
    *sptr = (serfile*)malloc(sizeof(serfile));
    if (!*sptr) {
        return (*status = MEM_ALLOC);
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
    ser_header_initializations(*sptr);
    /*
    memset((*sptr)->file_id, 0, FILEID_LEN);
    (*sptr)->lu_id = 0;
    (*sptr)->color_id = MONO;
    (*sptr)->little_endian = LITTLEENDIAN_TRUE;
    (*sptr)->image_width = 0;
    (*sptr)->image_height = 0;
    (*sptr)->pixel_depth_per_plane = 8;
    (*sptr)->frame_count = 0;
    memset((*sptr)->observer, 0, OBSERVER_LEN);
    memset((*sptr)->instrument, 0, INSTRUMENT_LEN);
    memset((*sptr)->telescope, 0, TELESCOPE_LEN);
    (*sptr)->date_time = 0;
    (*sptr)->date_time_utc = 0;
    */

    /* initialize trailer */
    (*sptr)->has_trailer = (*sptr)->date_time <= 0 ? false : true;
    (*sptr)->timestamps = NULL;
    (*sptr)->timestamp_count = 0;

    return (*status);
}

int ser_open_view(serfile** sptr, uint8_t* data, size_t size, int mode, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTRPTR(sptr, status);
	RETURN_IF_SPTR_OCCUPIED(sptr, status);

    if (!data) {
        return (*status = NULL_PARAM);
    }

    /* determine validity of header */
    if (size < HDR_SIZE) {
        return (*status = INVALID_STRUCTURE);
    }

    /* allocate memory for serfile */
    *sptr = (serfile*)malloc(sizeof(serfile));
    if (!(*sptr)) {
        return (*status = MEM_ALLOC);
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
    (*sptr)->reader(ser_data, (*sptr)->file_id, FILEID_LEN, FILEID_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->lu_id, LUID_LEN, LUID_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->color_id, COLORID_LEN, COLORID_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->little_endian, LITTLEENDIAN_LEN, LITTLEENDIAN_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->image_width, IMAGEWIDTH_LEN, IMAGEWIDTH_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->image_height, IMAGEHEIGHT_LEN, IMAGEHEIGHT_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->pixel_depth_per_plane, PIXELDEPTHPERPLANE_LEN, PIXELDEPTHPERPLANE_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->frame_count, FRAMECOUNT_LEN, FRAMECOUNT_KEY);
    (*sptr)->reader(ser_data, (*sptr)->observer, OBSERVER_LEN, OBSERVER_KEY);
    (*sptr)->reader(ser_data, (*sptr)->instrument, INSTRUMENT_LEN, INSTRUMENT_KEY);
    (*sptr)->reader(ser_data, (*sptr)->telescope, TELESCOPE_LEN, TELESCOPE_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->date_time, DATETIME_LEN, DATETIME_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->date_time_utc, DATETIMEUTC_LEN, DATETIMEUTC_KEY);
    (*sptr)->has_trailer = (*sptr)->date_time <= 0 ? false : true;
    (*sptr)->timestamps = NULL;
    (*sptr)->timestamp_count = 0;

    /* determine if valid hdr + data or hdr + data + trailer */
    size_t frame_byte_size = 0;
    ser_get_frame_byte_size(*sptr, &frame_byte_size, status);
    size_t trailer_offset = HDR_SIZE + (*sptr)->frame_count * frame_byte_size;

    if ((*sptr)->has_trailer) {
        if (size == trailer_offset + (*sptr)->frame_count * sizeof(uint64_t)) {
            (*sptr)->timestamps = (int64_t*)realloc((*sptr)->timestamps, (*sptr)->frame_count * sizeof(uint64_t));
            (*sptr)->timestamp_count = (*sptr)->frame_count;
            (*sptr)->reader(
                    (*sptr)->io_context,
                    (*sptr)->timestamps,
                    (*sptr)->frame_count * sizeof(uint64_t),
                    trailer_offset
            );
            return (*status);
        }
    } else {
        if (size == trailer_offset) {
            return (*status);
        }
    }

    /* if reached, invalid structure */
    free(((serMem*)(*sptr)->io_context));
    free((*sptr));
    *sptr = NULL;
    return (*status = INVALID_STRUCTURE);
}

int ser_open_memory(serfile** sptr, const uint8_t* data, size_t size, int mode, int* status) {
	RETURN_IF_STATUS_IS_ERROR(status);
	RETURN_IF_NULL_SPTRPTR(sptr, status);
	RETURN_IF_SPTR_OCCUPIED(sptr, status);

    if (!data) {
        return (*status = NULL_PARAM);
    }

    /* determine validity of header */
    if (size < HDR_SIZE) {
        return (*status = INVALID_STRUCTURE);
    }

    /* allocate memory for serfile */
    *sptr = (serfile*)malloc(sizeof(serfile));
    if (!(*sptr)) {
        return (*status = MEM_ALLOC);
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
    (*sptr)->reader(ser_data, (*sptr)->file_id, FILEID_LEN, FILEID_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->lu_id, LUID_LEN, LUID_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->color_id, COLORID_LEN, COLORID_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->little_endian, LITTLEENDIAN_LEN, LITTLEENDIAN_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->image_width, IMAGEWIDTH_LEN, IMAGEWIDTH_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->image_height, IMAGEHEIGHT_LEN, IMAGEHEIGHT_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->pixel_depth_per_plane, PIXELDEPTHPERPLANE_LEN, PIXELDEPTHPERPLANE_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->frame_count, FRAMECOUNT_LEN, FRAMECOUNT_KEY);
    (*sptr)->reader(ser_data, (*sptr)->observer, OBSERVER_LEN, OBSERVER_KEY);
    (*sptr)->reader(ser_data, (*sptr)->instrument, INSTRUMENT_LEN, INSTRUMENT_KEY);
    (*sptr)->reader(ser_data, (*sptr)->telescope, TELESCOPE_LEN, TELESCOPE_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->date_time, DATETIME_LEN, DATETIME_KEY);
    (*sptr)->reader(ser_data, &(*sptr)->date_time_utc, DATETIMEUTC_LEN, DATETIMEUTC_KEY);
    (*sptr)->has_trailer = (*sptr)->date_time <= 0 ? false : true;
    (*sptr)->timestamps = NULL;
    (*sptr)->timestamp_count = 0;

    /* determine if valid hdr + data or hdr + data + trailer */
    size_t frame_byte_size = 0;
    ser_get_frame_byte_size(*sptr, &frame_byte_size, status);
    size_t trailer_offset = HDR_SIZE + (*sptr)->frame_count * frame_byte_size;

    if ((*sptr)->has_trailer) {
        if (size == trailer_offset + (*sptr)->frame_count * sizeof(uint64_t)) {
            (*sptr)->timestamps = (int64_t*)realloc((*sptr)->timestamps, (*sptr)->frame_count * sizeof(uint64_t));
            (*sptr)->timestamp_count = (*sptr)->frame_count;
            (*sptr)->reader(
                    (*sptr)->io_context,
                    (*sptr)->timestamps,
                    (*sptr)->frame_count * sizeof(uint64_t),
                    trailer_offset
            );
            return (*status);
        }
    } else {
        if (size == trailer_offset) {
            return (*status);
        }
    }

    /* if reached, invalid structure */
    free(((serMem*)(*sptr)->io_context)->data);
    free(((serMem*)(*sptr)->io_context));
    free((*sptr));
    *sptr = NULL;
    return (*status = INVALID_STRUCTURE);
}

int ser_close_memory(serfile* sptr, int* status) {
	RETURN_IF_NULL_SPTR(sptr, status);

    if (sptr->access_mode == READWRITE) {
        sptr->writer(sptr->io_context, sptr->file_id, FILEID_LEN, FILEID_KEY);
        sptr->writer(sptr->io_context, &sptr->lu_id, LUID_LEN, LUID_KEY);
        sptr->writer(sptr->io_context, &sptr->color_id, COLORID_LEN, COLORID_KEY);
        sptr->writer(sptr->io_context, &sptr->little_endian, LITTLEENDIAN_LEN, LITTLEENDIAN_KEY);
        sptr->writer(sptr->io_context, &sptr->image_width, IMAGEWIDTH_LEN, IMAGEWIDTH_KEY);
        sptr->writer(sptr->io_context, &sptr->image_height, IMAGEHEIGHT_LEN, IMAGEHEIGHT_KEY);
        sptr->writer(sptr->io_context, &sptr->pixel_depth_per_plane, PIXELDEPTHPERPLANE_LEN, PIXELDEPTHPERPLANE_KEY);
        sptr->writer(sptr->io_context, &sptr->frame_count, FRAMECOUNT_LEN, FRAMECOUNT_KEY);
        sptr->writer(sptr->io_context, sptr->observer, OBSERVER_LEN, OBSERVER_KEY);
        sptr->writer(sptr->io_context, sptr->instrument, INSTRUMENT_LEN, INSTRUMENT_KEY);
        sptr->writer(sptr->io_context, sptr->telescope, TELESCOPE_LEN, TELESCOPE_KEY);
        sptr->writer(sptr->io_context, &sptr->date_time, DATETIME_LEN, DATETIME_KEY);
        sptr->writer(sptr->io_context, &sptr->date_time_utc, DATETIMEUTC_LEN, DATETIMEUTC_KEY);
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
    return (*status);
}

#endif /* CSERIO_IMPLEMENTATION */

#ifdef __cplusplus
}
#endif

#endif /* CSERIO_H */

