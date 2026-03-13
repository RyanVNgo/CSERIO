
# Home

## Intro

CSERIO is a single header C library that provides read and write routines for `.ser` format 
files.


---
# Usage

## Integration 
Compile `cserio.c` with your software like any other source file and include the `cserio.h` 
header like normal.

In very simple cases, you could just include the `cserio.h` header and define 
`CSERIO_IMPLEMENTATION` before the include which will define the implementation.
```C
#define CSERIO_IMPLMENTATION
#include "cserio.h"
```


## Example Usage
```C
#define CSERIO_IMPLMENTATION

#include "cserio.h"


int main(void) {
    int status = 0;             /* define and initialize status value */
    serfile* my_ser = NULL;     /* define and initialize pointer to the SER file */

    /* Open an existing SER file */
    ser_open_file(
            &my_ser,
            "/path/saturn_capture.ser",
            READONLY,
            &status
    );

    /* check if routine failed */
    if (status) {
        fprintf(stderr, "Error opening ser: %d\n", status);
        exit(EXIT_FAILURE);
    }

    /* get frame count */
    /* passing address of buffer that the routine will write the frame count to */
    int32_t frame_count = 0;
    ser_get_frame_count(my_ser, &frame_count, &status);

    /* check if routine failed */
    if (status) {
        fprintf(stderr, "Error getting frame count: %d\n", status);
        ser_close_file(my_ser, &status);       /* close the SER file before exiting */
        exit(EXIT_FAILURE);
    }

    /* retrieved frame count */
    printf("Frame count: %d\n", frame_count);

    /* finished; close the SER file */
    ser_close_file(my_ser, &status);

    /* check if routine failed  */
    if (status) {
        fprintf(stderr, "Error closing ser: %d\n", status);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
```


---

# Guidelines

## `serfile` Structure

```C
typedef struct serfile serfile;
```
The `serfile` structure is used by CSERIO to store relevant data about a SER file and 
defines how it should interact with it. Applications must define a pointer to a
`serfile` for every SER file that is to be opened or created. This structure is
initialized when a pointer to this pointer is passed to any of the open or create
routines. Once initialized, the pointer is passed as the first argument to nearly all
other CSERIO. The close routines will handle the closure and deallocation of the 
structure. Applications should not attempt to modify the contents of the structure
or manually allocate/deallocate it.


## Multi-threaded Environments & Multi-open Implementations 
> [!CAUTION]
> CSERIO **does not** support multi-threaded operations or multi-open implementations.
> Multiple threads performing operations with the same `serfile` may result in a
> malformed SER file. If one SER file is opened mulitple times and operations are
> peformed independently on each `serfile`, this may result in a malformed SER file.
> *This is a general precaution as we work on better defining and characterizing the
> behavior.*


## Definitions

A number of symbolic constants are provided to help in usage of CSERIO.

```C
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
```


## Character Buffers

Some header read/write routines call for a pointer to a character buffer (`char*`).
These routines operate on the buffer with the expectation that its size is equal
to the size of the header field. These sizes are provided by `cserio.h` and have the 
suffix `_LEN`, namely `FILEID_LEN`, `OBSERVER_LEN`, `INSTRUMENT_LEN`, and 
`TELESCOPE_LEN`. When creating a buffer to pass as an argument for these routines,
it is recommended that you use these lengths provided by CSERIO.

### Example
```C
char fileid[FILEID_LEN];
```


---
# Routines

## Core Routines

### cserio_version_number

```C
/*  @brief  Provides the Major, Minor, and Micro numbers for
 *          the current version of CSERIO.
 *  @param  major       (IO)    - Pointer to Major int.
 *  @param  minor       (IO)    - Pointer to Minor int.
 *  @param  micro       (IO)    - Pointer to Micro int.
 *  @return Void.
 */
void cserio_version_number(int* major, int* minor, int* micro);
```
This method simply exists to provide a more programmatic way of parsing the version
numbers for CSERIO. The arguments for this method can be `NULL`. 


## SER Access Routines

### ser_create_file
```C
/*  @brief  Create a new SER file.
 *
 *  @param  sptr        (IO)    - Pointer to pointer of a serfile.
 *  @param  path        (I)     - File path.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_create_file(serfile** sptr, const char* path, int* status);
```
If the specified path already exists, the routine will fail and exit early. All header
fields of the SER file are initialized to 0 aside from the little endian field, which
is set to `LITTLEENDIAN_TRUE == 1`, and the pixel-depth-per-plane field, which is
initialized to `8`.


### ser_open_file
```C
/*  @brief  Opens existing SER file
 *
 *  @param  sptr        (IO)    - Pointer to a pointer of a serfile.
 *  @param  path        (I)     - SER file path.
 *  @param  mode        (I)     - Access type (READONLY or READWRITE).
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_open_file(serfile** sptr, const char* path, int mode, int* status);
```
If the argument passed for `mode` is set to any value beside `READWRITE`, then the routine
will default to `READONLY` and continue. The routine will check the validity of the file
by ensuring the header data correctly aligns with the image data and trailer data if 
present. If the data does not align, the file is considered invalid and the routine will 
fail, close the file, and exit.


### ser_close_file
```C
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
```
This is one of the few routines in CSERIO that does not exit immediately if `status` is 
non-zero or `!= NO_ERROR`. It ignores the passed status and attempts to close the file
anyway.


## Header Routines

### ser_get_rec_count
```C
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
int ser_get_rec_count(serfile* sptr, int* rec_count, int* status);
```

### ser_read_file_id
```C
/*  @brief  Read File ID
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  file_id     (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_file_id(const serfile* sptr, char* file_id, int* status);
```

### ser_read_lu_id
```C
/*  @brief  Read LU ID
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  lu_id       (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_lu_id(const serfile* sptr, int32_t* lu_id, int* status);
```

### ser_read_color_id
```C
/*  @brief  Read Color ID
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  color_id    (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_color_id(const serfile* sptr, int32_t* color_id, int* status);
```

### ser_read_little_endian
```C
/*  @brief  Read Litte Endian
 *  @param  sptr            (I)     - Pointer to serfile.
 *  @param  little_endian   (IO)    - Destination buffer.
 *  @param  status          (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_little_endian(const serfile* sptr, int32_t* little_endian, int* status);
```

### ser_read_image_width
```C
/*  @brief  Read Image Width
 *  @param  sptr            (I)     - Pointer to serfile.
 *  @param  image_width     (IO)    - Destination buffer.
 *  @param  status          (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_image_width(const serfile* sptr, int32_t* image_width, int* status);
```

### ser_read_image_height
```C
/*  @brief  Read Image Height 
 *  @param  sptr            (I)     - Pointer to serfile.
 *  @param  image_height    (IO)    - Destination buffer.
 *  @param  status          (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_image_height(const serfile* sptr, int32_t* image_height, int* status);
```

### ser_read_pixel_depth_per_plane
```C
/*  @brief  Read Pixel Depth Per Plane
 *  @param  sptr                    (I)     - Pointer to serfile.
 *  @param  pixel_depth_per_plane   (IO)    - Destination buffer.
 *  @param  status                  (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_pixel_depth_per_plane(const serfile* sptr, int32_t* pixel_depth_per_plane, int* status);
```

### ser_read_frame_count
```C
/*  @brief  Read Frame Count
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  frame_count (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_frame_count(const serfile* sptr, int32_t* frame_count, int* status);
```

### ser_read_observer
```C
/*  @brief  Read Observer
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  observer    (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_observer(const serfile* sptr, char* observer, int* status);
```

### ser_read_instrument
```C
/*  @brief  Read Instrument 
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  instrument  (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_instrument(const serfile* sptr, char* instrument, int* status);
```

### ser_read_telescope
```C
/*  @brief  Read Telescope
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  telescope   (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_telescope(const serfile* sptr, char* telescope, int* status);
```

### ser_read_date_time
```C
/*  @brief  Read Date Time
 *  @param  sptr        (I)     - Pointer to serfile.
 *  @param  date_time   (IO)    - Destination buffer.
 *  @param  status      (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_date_time(const serfile* sptr, int64_t* date_time, int* status);
```

### ser_read_date_time_utc
```C
/*  @brief  Read Date Time UTC
 *  @param  sptr            (I)     - Pointer to serfile.
 *  @param  date_time_utc   (IO)    - Destination buffer.
 *  @param  status          (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_date_time_utc(const serfile* sptr, int64_t* date_time_utc, int* status);
```

### ser_write_file_id
```C
/*  @brief  Write File ID.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  file_id             (I)     - New File ID (char* string).
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_file_id(serfile* sptr, const char* file_id, int* status);
```

### ser_write_lu_id
```C
/*  @brief  Write LU ID.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  lu_id               (I)     - New LU ID.
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_lu_id(serfile* sptr, const int32_t lu_id, int* status);
```

### ser_write_color_id
```C
/*  @brief  Write Color ID.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  color_id            (I)     - New Color ID
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_color_id(serfile* sptr, const int32_t color_id, int* status);
```
The value passed for `color_id` must be one of the valid color IDs defined by 
`cserio.h`, otherwise the routine will fail and exit early. Additionally, if the 
color ID changes to one with a different data format, currently distinguished by
color IDs less than 100 being single value formats and color IDs greater than or
equal to 100 being triple value formats, while frame data is present, the routine 
will fail and exit early.

### ser_write_little_endian
```C
/*  @brief  Write Little Endian.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  little_endian       (I)     - New Little Endian
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_little_endian(serfile* sptr, const int32_t little_endian, int* status);
```
The value passed for `little_endian` must be either `LITTLEENDIAN_TRUE` or 
`LITTLEENDIAN_FALSE`, otherwise the routine will fail and exit early.

### ser_write_image_width
```C
/*  @brief  Write Image Width.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  image_width         (I)     - New Image Width.
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_image_width(serfile* sptr, const uint32_t image_width, int* status);
```
The image width may only be changed so long as there is no frame data present,
otherwise the routine will fail ane exit early.

### ser_write_image_height
```C
/*  @brief  Write Image Height. 
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  image_height        (I)     - New Image Height.
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_image_height(serfile* sptr, const uint32_t image_height, int* status);
```
The image height may only be changed so long as there is no frame data present,
otherwise the routine will fail ane exit early.

### ser_write_pixel_depth_per_plane
```C
/*  @brief  Write Pixel Depth Per Plane.  
 *  @param  sptr                    (I)     - Pointer to serfile.
 *  @param  pixel_depth_per_plane   (I)     - New Pixel Depth Per Plane.  
 *  @param  status                  (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_pixel_depth_per_plane(serfile* sptr, const int32_t pixel_depth_per_plane, int* status);
```
The value passed for `pixel_depth_per_plane` must be between 1 and 16, both including,
otherwise the routine will fail and exit early. If frame data is present, switching
from a depth that is less than or equal to 8 to a depth greater than 8, and vice versa,
is invalid and the routine will fail and exit early.

### ser_write_observer
```C
/*  @brief  Write Observer.
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  observer            (I)     - New Observer (char* string).
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_observer(serfile* sptr, const char* observer, int* status);
```

### ser_write_instrument
```C
/*  @brief  Write Instrument. 
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  instrument          (I)     - New Instrument (char* string).
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_instrument(serfile* sptr, const char* instrument, int* status);
```

### ser_write_telescope
```C
/*  @brief  Write Telescope. 
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  telescope           (I)     - New Telescope (char* string).
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_telescope(serfile* sptr, const char* telescope, int* status);
```

### ser_write_date_time
```C
/*  @brief  Write Date Time. 
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  date_time           (I)     - New Date Time.
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_date_time(serfile* sptr, const int64_t date_time, int* status);
```
The date-time field for SER files serves as the indicator for whether or not
a timestamp trailer exists or not. If the value is `<= 0`, there is no trailer,
and if it is `> 0`, the trailer exists. If the value passed for `date_time` 
switches the trailer state while frame data is present, the routine will fail
and exit early.

### ser_write_date_time_utc
```C
/*  @brief  Write Date Time. 
 *  @param  sptr                (I)     - Pointer to serfile.
 *  @param  date_time_utc       (I)     - New Date Time UTC.
 *  @param  status              (IO)    - Error status.
 *  @return Error Status.
 */
int ser_write_date_time_utc(serfile* sptr, const int64_t date_time_utc, int* status);
```


## Image Routines

### ser_get_number_of_planes
```C
/*  @brief  Get number of planes per frame.
 *  @param  sptr    (I)     - Pointer to serfile.
 *  @param  nop     (IO)    - Destination buffer.
 *  @param  status  (IO)    - Error status.
 *  @return Error status.
 */
int ser_get_number_of_planes(serfile* sptr, int* nop, int* status);
```

### ser_get_bytes_per_pixel
```C
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
```

### ser_get_frame_byte_size
```C
/*  @brief  Returns the byte size of a single frame
 *  @param  sptr        (I)   - Pointer to serfile.
 *  @param  byte_size   (IO)  - Pointer to long.
 *  @param  status      (IO)  - Error status.
 *  @return Error status.
 */
int ser_get_frame_byte_size(serfile* sptr, unsigned long* byte_size, int* status);
```

### ser_read_frame
```C
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
```

### ser_append_frame
```C
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
```

## Trailer Routines

### ser_get_timestamp
```C
/*  @brief  Read trailer time stamp at index.
 *  @param  sptr    (I)     - Pointer to serfile.
 *  @param  dest    (IO)    - Pointer to data buffer.
 *  @param  idx     (I)     - Index of time stamp.
 *  @param  status  (IO)    - Error status.
 *  @return Error Status.
 */
int ser_read_timestamp(serfile* sptr, int64_t* dest, size_t idx, int* status);
```


---
# Errors

## Error Handling
Almost every routine in CSERIO communicates an error status value to the user in two 
ways: as a modification of the `status` paramater of the routine, and as the return 
value of the routine.

> [!IMPORTANT]
> The `status` parameter of a routine call **must be** valid and therefore not NULL. 
> Passing a NULL value for `status` will likely result in a crash.

Nearly all routines that have a `status` parameter 'inherit' the value assigned to 
`status` and fail immediately if the value is non-zero or not equal to `NO_ERROR`. 
This means that a routine will first check the value of `status` and if non-zero, 
it assumes an error from an earlier routine occured and had its value passed down. 
To minimize the chances for errors or invalid state in the SER file, the routine will 
fail immediately and will not alter the `status` value.


## CSERIO Errors
If you're handling error codes, it is suggested to use the mnemonic definitions rather 
than their actual integer values. 

```C
/*-------------------- Core Errors --------------------*/

#define NO_ERROR                            0

#define MEM_ALLOC                           101
#define NULL_SPTR                           102
#define NULL_DEST_BUFF                      103
#define NULL_PARAM                          104
#define NULL_SPTRPTR                        105
#define SPTR_OCCUPIED                       106

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

#define INVALID_SET_STATE                   321
#define INVALID_SET_VALUE                   322

/*-------------------- Image Routine Errors --------------------*/

#define INVALID_FRAME_IDX                   402
#define INVALID_FRAME_SIZE                  403

#define IMAGE_WRITE_WARN                    411

/*-------------------- Trailer Routine Errors --------------------*/

#define TRAILER_DNE                         501

#define INVALID_TRAILER_IDX                 512

#define TRAILER_CLOSE_WARN                  521

```


