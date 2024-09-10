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

/*-------------------- CSERIO Version --------------------*/

/**
 * For now, ensure that the version defined here matches
 * that one defined in the `configure.ac` file.
 */
#define CSERIO_VERSION 1.2.0
#define CSERIO_MICRO 0
#define CSERIO_MINOR 2
#define CSERIO_MAJOR 1

/*-------------------- SER File Symbolic Constants --------------------*/

#define SER_EXT ".ser"
#define SER_EXT_LEN 4

/*-------------------- SER Structure --------------------*/

typedef struct SERfile {
  FILE* s_file;
  char filename[FILENAME_MAX];
  long size_in_bytes;
} SERfile;


typedef struct serfile {
  SERfile* SER_file;
} serfile;

/*-------------------- Core Routines --------------------*/

/** @brief  Assigns and returns the current version number
 *          of the CSERIO library.
 *  @param  version   (IO) - Address of float to assign 
 *                    the version number, address must be
 *                    valid or NULL.
 *  @return Version number.
 */
float cserio_version_number(float* version);

/*-------------------- File Access Routines --------------------*/

/* Flags for file access routines */
#define READONLY 0
#define READWRITE 1

/** @brief  Opens SER file
 *
 *  The memory for the serfile structure is automatically allocated
 *  on file open and freed on file close.
 *
 *  @param  sptr      (IO) - Pointer to a pointer of a serfile.
 *  @param  filename  (I) - root name of the SER file to open.
 *  @param  mode      (I) - Access type, either READONLY or READWRITE.
 *  @param  status    (IO) - Error status.
 *  @return Error status.
 */
int ser_open_file(serfile** sptr, char* filename, int mode, int* status);

/** @brief  Close SER file
 *
 *  Closes the serfile and frees the structure. Parameter sptr will
 *  be set to NULL.
 *
 *  @param  sptr      (IO) - Pointer to a serfile.
 *  @param  status    (IO) - Error status.
 *  @return Error status.
 */
int ser_close_file(serfile* sptr, int* status);

/*-------------------- Library Headers --------------------*/

#include "errors.h"
#include "header_routines.h"

#endif
