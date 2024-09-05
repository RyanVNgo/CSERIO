/** @file cserio.c
 *  @brief Function definitions for `cserio.h` prototypes.
 *
 *  Provides function definitions for all functions prototyped
 *  in `cserio.h`. This file also serves as the designated
 *  source file for autoconf, therefore this file must NEVER
 *  be removed or drastically altered unless explicit changes 
 *  are made to the `configure.ac` file.
 *
 *  @author Ryan V. Ngo
 */

#include "cserio.h"
#include "errors.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*-------------------- Core Routines --------------------*/

/** @brief  Assigns and returns the current version number
 *          of the CSERIO library.
 *  @param  version     (IO) - Address of float to assign 
 *                      the version number. Address must be
 *                      valid or NULL.
 *  @return Version number.
 */
float cserio_version_number(float* version) {
    /* @param Version - NULL condition */
    if (!version) {
        return 
            (float)CSERIO_MAJOR + 
            (float)(0.01 * CSERIO_MINOR) + 
            (float)(0.0001 * CSERIO_MICRO);
    }

    *version = 
        (float)CSERIO_MAJOR + 
        (float)(0.01 * CSERIO_MINOR) + 
        (float)(0.0001 * CSERIO_MICRO);

    return (*version);
}

/*-------------------- File Access Routines --------------------*/

/** @brief  Opens SER file
 *  @param  sptr      (IO) - Pointer to a pointer of a serfile. The
 *                    memory for the structure is automatically
 *                    allocated on file open and freed on file close.
 *  @param  filename  (I) - root name of the SER file to open.
 *  @param  mode      (I) - Access type, either READONLY or READWRITE.
 *  @param  status    (IO) - Error status.
 *  @return Error status.
 */
int ser_open_file(serfile** sptr, char* filename, int mode, int* status) {
    if (!sptr) {
        *status = NULL_SPTR;
        return (*status);
    }

    *sptr = NULL;

    /* check if filename exists and has valid extension */
    if (!filename) {
        *status = NULL_FILENAME;
        return (*status);
    }

    /* !!! */

    /**
     * Behavior is set such that it will default to READONLY if not READWRITE,
     * regardless of whether or not mode = READONLY or mode was invalid.
     * Can alter behavior to throw an error for an invalid mode.
     */
    FILE* ser_file;
    if (mode == READWRITE) {
        ser_file = fopen(filename, "r+");
    } else {
        ser_file = fopen(filename, "r"); /* default behavior */
    }

    if (!ser_file) {
        *status = FILE_OPEN_ERROR;
        return (*status);
    }

    *sptr = (serfile*)malloc(sizeof(serfile));
    if (!*sptr) {
        *status = MEM_ALLOC;
        return (*status);
    }

    (*sptr)->SER_file = (SERfile*)malloc(sizeof(SERfile));
    if (!(*sptr)->SER_file) {
        *status = MEM_ALLOC;
        return (*status);
    }

    /* Fill structure data */
    /* s_file */
    (*sptr)->SER_file->s_file = ser_file;

    /* filename */
    strncpy((*sptr)->SER_file->filename, filename, FILENAME_MAX);

    /* size_in_bytes */
    fseek((*sptr)->SER_file->s_file, 0, SEEK_END);
    long size = ftell((*sptr)->SER_file->s_file);
    fseek((*sptr)->SER_file->s_file, 0, SEEK_SET);
    (*sptr)->SER_file->size_in_bytes = size;

    return (*status);
}

/** @brief  Close SER file
 *
 *  Closes the serfile and frees the structure. Parameter sptr will
 *  be set to NULL.
 *
 *  @param  sptr      (IO) - Pointer to a serfile.
 *  @param  status    (IO) - Error status.
 *  @return Error status.
 */
int ser_close_file(serfile* sptr, int* status) {
    if (!sptr) {
        *status = NULL_SPTR;
        return (*status);
    }

    /* Clear SER structre data */
    if (!sptr->SER_file->s_file || fclose(sptr->SER_file->s_file)) {
        *status = FILE_CLOSE_ERROR;
    }

    /* Free SER structure data and SER file structure */
    free(sptr->SER_file);
    free(sptr);
    sptr = NULL;

    return (*status);
}

