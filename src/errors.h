/** @file errors.h
 *  @brief Constants and functions for interpreting errors
 *  @author Ryan V. Ngo
 */

#ifndef ERRORS_H
#define ERRORS_H

/*-------------------- Core Errors --------------------*/

#define NO_ERROR 0

#define MEM_ALLOC 101
#define NULL_SPTR 102

/*-------------------- File Access Errors --------------------*/

#define NULL_FILENAME 201
#define INVALID_FILENAME 202

#define FILE_OPEN_ERROR 211
#define FILE_CLOSE_ERROR 212

#endif
