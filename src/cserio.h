/** @file cserio.h
 *  @brief Core definitions and function prototypes.
 *
 *  This file contains all the core definitions and function 
 *  prototypes for the CSERIO library. This file also serves 
 *  as the primary entry point for the library meaning
 *  including this file should be all that is necessary to
 *  utilize the entire CSERIO library.
 *
 *  @author Ryan V. Ngo
 */

#ifndef CSERIO_H
#define CSERIO_H

#include <stdio.h>
#include <stdint.h>

/*#################### PUBLIC SYMBOLIC CONSTANTS ####################*/ 

/*-------------------- CSERIO Version --------------------*/

/**
 * For now, ensure that the version defined here matches
 * that one defined in the `configure.ac` file.
 */
#define CSERIO_VERSION 1.2.0
#define CSERIO_MICRO 0
#define CSERIO_MINOR 2
#define CSERIO_MAJOR 1

/*-------------------- Error Include --------------------*/

#include "errors.h"

/*#################### DEFINES, STRUCTURES, AND TYPES ####################*/ 

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

/**
 * These constants represent the byte length of each header component
 * for V3 SER files.
 *
 * Note that these values represent the byte length as they are in the
 * SER file.
 */
#define FILEID_LEN 14
#define LUID_LEN 4
#define COLORID_LEN 4 
#define LITTLEENDIAN_LEN  4 
#define IMAGEWIDTH_LEN  4 
#define IMAGEHEIGHT_LEN  4 
#define PIXELDEPTHPERPLANE_LEN  4 
#define FRAMECOUNT_LEN  4 
#define OBSERVER_LEN  40 
#define INSTRUMENT_LEN  40 
#define TELESCOPE_LEN  40 
#define DATETIME_LEN  8 
#define DATETIMEUTC_LEN  8 

/*-------------------- Header Constant References --------------------*/

/**
 * These functionally operate as the byte intex position within the
 * SER file.
 */
#define FILEID_KEY 0
#define LUID_KEY 14
#define COLORID_KEY 18
#define LITTLEENDIAN_KEY 22
#define IMAGEWIDTH_KEY 26
#define IMAGEHEIGHT_KEY 30
#define PIXELDEPTHPERPLANE_KEY 34
#define FRAMECOUNT_KEY 38
#define OBSERVER_KEY 42
#define INSTRUMENT_KEY 82
#define TELESCOPE_KEY 122
#define DATETIME_KEY 162
#define DATETIMEUTC_KEY 170

/*-------------------- SER Structure --------------------*/

typedef struct SERfile {
  FILE* s_file;
  char filename[FILENAME_MAX];
  long size_in_bytes;
} SERfile;


typedef struct serfile {
  SERfile* SER_file;
} serfile;

/*#################### PUBLIC FUNCTION PROTOTYPES ####################*/ 

/*-------------------- Core Routines --------------------*/

float cserio_version_number(float* version);

/*-------------------- File Access Routines --------------------*/

int ser_open_file(serfile** sptr, char* filename, int mode, int* status);
int ser_close_file(serfile* sptr, int* status);

/*-------------------- Header Routines --------------------*/

int ser_get_hdr_count(serfile* sptr, int* rec_count, int* status);
int ser_get_idx_record(serfile* sptr, void* dest, int idx, int* status);
int ser_get_key_record(serfile* sptr, void* dest, int key, int* status);

#endif
