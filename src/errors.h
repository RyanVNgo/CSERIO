/** @file errors.h
 *  @brief Constants and functions for interpreting errors
 *  @author Ryan V. Ngo
 */

#ifndef ERRORS_H
#define ERRORS_H

/*-------------------- Core Errors --------------------*/

#define NO_ERROR            0

#define MEM_ALLOC           101
#define NULL_SPTR           102
#define NULL_DEST_BUFF      103
#define NULL_PARAM          104

#define EOF_ERROR           110
#define FREAD_ERROR         111

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

#endif
