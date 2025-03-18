/*  @file   cserio.c
 *  @brief  Function definitions for `cserio.h` prototypes.
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*-------------------- Core Routines --------------------*/

/*  @brief  Provides the Major, Minor, and Micro numbers for
 *          the current version of CSERIO.
 *  @param  major     (IO)  - Pointer to Major int.
 *  @param  minor     (IO)  - Pointer to Minor int.
 *  @param  micro     (IO)  - Pointer to Micro int.
 *  @return Void.
 */
void cserio_version_number(int* major, int* minor, int* micro) {
    if (major) { *major = CSERIO_MAJOR; }
    if (minor) { *minor = CSERIO_MINOR; }
    if (micro) { *micro = CSERIO_MICRO; }
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
    if (!sptr) { return (void)(*status = NULL_SPTR); }
    *sptr = NULL;

    if (!filename) { return (void)(*status = NULL_FILENAME); }

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

    (*sptr)->SER_file->s_file = ser_file;
    strncpy((*sptr)->SER_file->filename, filename, FILENAME_MAX);

    fseek((*sptr)->SER_file->s_file, 0, SEEK_END);
    long size = ftell((*sptr)->SER_file->s_file);
    fseek((*sptr)->SER_file->s_file, 0, SEEK_SET);
    (*sptr)->SER_file->size_in_bytes = size;

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
    if (!sptr) { return (void)(*status = NULL_SPTR); }

    if (!sptr->SER_file->s_file || fclose(sptr->SER_file->s_file)) {
        *status = FILE_CLOSE_ERROR;
    }

    free(sptr->SER_file);
    free(sptr);
    sptr = NULL;

    return;
}

