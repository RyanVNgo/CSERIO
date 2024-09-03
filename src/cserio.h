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

/**
 * For now, ensure that the version defined here matches
 * that one defined in the `configure.ac` file.
 */
#define CSERIO_VERSION 1.0.0
#define CSERIO_MICRO 0
#define CSERIO_MINOR 0
#define CSERIO_MAJOR 1

/*-------------------- core routines --------------------*/

/** @brief  Assigns and returns the current version number
 *          of the CSERIO library.
 *  @param  version     (IO) - Address of float to assign 
 *                      the version number, address must be
 *                      valid or NULL.
 *  @return Version number.
 */
float cserio_version_number(float* version);

#endif
