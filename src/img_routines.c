/** @file img_routines.c
 *  @brief Definitions for image routines
 *
 *  @author Ryan V. Ngo
 */

#include "cserio.h"

/*-------------------- Image Routines --------------------*/

/** @brief Get number of dimensions of a frame
 *
 *  @param  sptr    (I) - Pointer to serfile.
 *  @param  ndim    (IO) - Pointer to int do set as dim count.
 *  @param  status  (IO) - Error status.
 *  @return Error status.
 */
int ser_get_frame_dim(serfile* sptr, int* ndim, int* status);

/** @brief Get the size of a target dimension
 *
 *  @param  sptr    (I) - Pointer to serfile.
 *  @param  size    (IO) - Pointer to int to set as size.
 *  @param  dim     (I) - Dimension to get size of.
 *  @param  status  (IO) - Error status. 
 *  @return Error status.
 */
int ser_get_frame_size(serfile* sptr, int* size, int dim, int* status);

/** @brief  Read the image frame at the index.
 *  
 *  Note that this function returns the entire data entry for
 *  the target frame. Ensure that the dest buffer can store
 *  the entire frame.
 *
 *  @param  sptr    (I) - Pointer to serfile.
 *  @param  dest    (IO) - Pointer to destination buffer.
 *  @param  idx     (I) - Index of the frame.
 *  @param  status  (IO) - Error status. 
 *  @return Error status.
 */
int ser_read_frame(serfile* sptr, void* dest, int idx, int* status) {
    /* sptr exists */
    if (!sptr) {
        *status = NULL_SPTR;
        return (*status);
    }

    /* destination buffer exists */
    if (!dest) {
        *status = NULL_DEST_BUFF;
        return (*status);
    }

    return (*status);
}
