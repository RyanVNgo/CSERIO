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

/*-------------------- SER File Symbolic Constants --------------------*/

#define SER_EXT ".ser"
#define SER_EXT_LEN 4

/*-------------------- SER File IO Modes --------------------*/

#define READONLY 0
#define READWRITE 1

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

/*#################### DEFINED STRUCTURES AND TYPES ####################*/ 

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
int ser_get_key_record(serfile* sptr, void* dest, HDR_KEY key, int* status);

#endif
