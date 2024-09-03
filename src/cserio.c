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

/*-------------------- core routines --------------------*/

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
