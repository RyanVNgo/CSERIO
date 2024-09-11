/** @file header_routines.c
 *  @brief Definitions for header routines
 *
 *  @author Ryan V. Ngo
 */

#include "cserio.h"

/*-------------------- Header Routines --------------------*/

/** @brief  Returns number of records in the header
 *
 *  Assigns passed hdr_count integer with number of records
 *  in the header. (Note that as of Version 3 SER files, the
 *
 *  @param  sptr        (I) - Pointer to serfile
 *  @param  rec_count   (IO) - Number of records
 *  @param  status      (IO) - Error status.
 *  @return Error status.
 */
int ser_get_hdr_count(serfile* sptr, int* rec_count, int* status) {


    return (*status);
}

/** @brief  Return data at header idx 
 *  
 *  Ensure that the dest buff to which the data will be written
 *  to has enough space to store the data. Refer to the defines in
 *  header_routines.h or follow the LEN_(key) format.
 *
 *  @param  sptr    (I) - Pointer to serfile
 *  @param  dest    (IO) - Destination buffer for header data
 *  @param  idx     (I) - Record index of data to fetch
 *  @param  status  (IO) - Error status.
 *  @return Error status.
 */
int ser_get_idx_record(serfile* sptr, void* dest, int idx, int* status) {


    return (*status);
}

/** @brief  Return data at header key
 *
 *  Ensure that the dest buff to which the data will be written
 *  to has enough space to store the data. Refer to the defines in
 *  header_routines.h or follow the LEN_(key) format.
 *
 *  @param  sptr    (I) - Pointer to serfile
 *  @param  dest    (IO) - Destination buffer for header data
 *  @param  key     (I) - Record key of data to fetch
 *  @param  status  (IO) - Error status.
 *  @return Error status.
 */
int ser_get_key_record(serfile* sptr, void* dest, HDR_KEY key, int* status) {


    return (*status);
}


