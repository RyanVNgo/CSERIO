/** @file header_routines.h
 *  @brief Defines and prototypes for header routines
 *
 *  @author Ryan V. Ngo
 */

#ifndef HEADER_ROUTINES_H
#define HEADER_ROUTINES_H

#include <stdint.h>

#include "cserio.h"

/*-------------------- Header Symbolic Constants --------------------*/

#define HDR_UNIT_COUNT 14

/**
 * These constants represent the byte length of each header component
 * for V3 SER files.
 */
#define LEN_FILEID 14
#define LEN_LUID 4
#define LEN_COLORID 4 
#define LEN_LITTLEENDIAN 4 
#define LEN_IMAGEWIDTH 4 
#define LEN_IMAGEHEIGHT 4 
#define LEN_PIXELDEPTHPERPLANE 4 
#define LEN_FRAMECOUNT 4 
#define LEN_OBSERVER 40 
#define LEN_INSTRUMENT 40 
#define LEN_TELESCOPE 40 
#define LEN_DATETIME 8 
#define LEN_DATETIMEUTC 8 

/*-------------------- Header Types --------------------*/

typedef char* S_STRING;
typedef int32_t S_INT32;
typedef int64_t S_INT64;

/*-------------------- Header Enums --------------------*/

typedef enum HDR_KEY {
  KEY_FILEID = 0,
  KEY_LUID = 14,
  KEY_COLORID = 18,
  KEY_LITTLEENDIAN = 22,
  KEY_IMAGEWIDTH = 26,
  KEY_IMAGEHEIGHT = 30,
  KEY_PIXELDEPTHPERPLANE = 34,
  KEY_FRAMECOUNT = 38,
  KEY_OBSERVER = 42,
  KEY_INSTRUMENT = 82,
  KEY_TELESCOPE = 122,
  KEY_DATETIME = 162,
  KEY_DATETIMEUTC = 170
} HDR_KEY;

/*-------------------- Header Routines --------------------*/

/** @brief Return data at header idx 
 *  
 *  Ensure that the dest buff to which the data will be written
 *  to has enough space to store the data. Refer to the defines in
 *  header_routines.h or follow the LEN_(key) format.
 *
 *  @param  sptr    (I) - Pointer to serfile
 *  @param  dest    (IO) - Destination buffer for header data
 *  @param  idx     (I) - Header index of data to fetch (0 - 13)
 *  @param  status  (IO) - Error status.
 *  @return Error status.
 */
int ser_read_hdr_idx(serfile* sptr, void* dest, int idx, int* status);

/** @brief Return data at header key
 *
 *  Ensure that the dest buff to which the data will be written
 *  to has enough space to store the data. Refer to the defines in
 *  header_routines.h or follow the LEN_(key) format.
 *
 *  @param  sptr    (I) - Pointer to serfile
 *  @param  dest    (IO) - Destination buffer for header data
 *  @param  key     (I) - Header key of data to fetch
 *  @param  status  (IO) - Error status.
 *  @return Error status.
 */
int ser_read_hdr_key(serfile* sptr, void* dest, HDR_KEY key, int* status);

#endif 
