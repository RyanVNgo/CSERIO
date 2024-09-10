/** @file header_routines.c
 *  @brief Definitions for header routines
 *
 *  @author Ryan V. Ngo
 */

#include "header_routines.h"

#include "errors.h"

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
int ser_read_hdr_idx(serfile* sptr, void* dest, int idx, int* status) {

    return (*status);
}

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
int ser_read_hdr_key(serfile* sptr, void* dest, HDR_KEY key, int* status) {

    return (*status);
}


