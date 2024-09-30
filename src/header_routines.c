/** @file header_routines.c
 *  @brief Definitions for header routines
 *
 *  @author Ryan V. Ngo
 */

#include "cserio.h"
#include "errors.h"

/*-------------------- Header Routines --------------------*/

/** @brief  Returns number of records in the header
 *
 *  Assigns passed hdr_count integer with number of records
 *  in the header. (Note that as of Version 3 SER files, the
 *  number of records in a header is a constant 13 which makes
 *  up the first 178 bytes of data)
 *
 *  @param  sptr        (I) - Pointer to serfile
 *  @param  rec_count   (IO) - Number of records
 *  @param  status      (IO) - Error status.
 *  @return Error status.
 */
int ser_get_hdr_count(serfile* sptr, int* rec_count, int* status) {
    /* sptr exists */
    if (!sptr) {
        *status = NULL_SPTR;
        return (*status);
    }

    /* rec_count pointer exists */
    if (!rec_count) {
        *status = NULL_PARAM;
        return (*status);
    }

    /* get number of header records */

    /**
     * As ov Version 3 SER files, the number of records in a header
     * is a constant 13 that totals 178 bytes of data.
     */
    *rec_count = HDR_UNIT_COUNT;

    return (*status);
}

/** @brief  Return data at header idx 
 *  
 *  Ensure that the dest buff to which the data will be written
 *  to has enough space to store the data. Refer to the defines in
 *  cserio.h or follow the LEN_(key) format. Note that this method
 *  does a raw data copy to the dest buffer, no conversion is done.
 *
 *  @param  sptr    (I) - Pointer to serfile
 *  @param  dest    (IO) - Destination buffer for header data
 *  @param  idx     (I) - Record index of data to fetch
 *  @param  status  (IO) - Error status.
 *  @return Error status.
 */
int ser_get_idx_record(serfile* sptr, void* dest, int idx, int* status) {
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

    /* check if idx is in bounds */
    if (idx < 0 || idx >= HDR_UNIT_COUNT) {
        *status = INVALID_HDR_IDX;
        return (*status);
    }

    /* get byte length of record */
    int byte_len = 0;
    int fpos = 0;
    switch (idx) {
        case 0:
            byte_len = FILEID_LEN;
            fpos = FILEID_KEY;
            break;
        case 1:
            byte_len = LUID_LEN;
            fpos = LUID_KEY;
            break;
        case 2:
            byte_len = COLORID_LEN;
            fpos = COLORID_KEY;
            break;
        case 3:
            byte_len = LITTLEENDIAN_LEN;
            fpos = LITTLEENDIAN_KEY;
            break;
        case 4:
            byte_len = IMAGEWIDTH_LEN;
            fpos = IMAGEWIDTH_KEY;
            break;
        case 5:
            byte_len = IMAGEHEIGHT_LEN;
            fpos = IMAGEHEIGHT_KEY;
            break;
        case 6:
            byte_len = PIXELDEPTHPERPLANE_LEN;
            fpos = PIXELDEPTHPERPLANE_KEY;
            break;
        case 7:
            byte_len = FRAMECOUNT_LEN;
            fpos = FRAMECOUNT_KEY;
            break;
        case 8:
            byte_len = OBSERVER_LEN;
            fpos = OBSERVER_KEY;
            break;
        case 9:
            byte_len = INSTRUMENT_LEN;
            fpos = INSTRUMENT_KEY;
            break;
        case 10:
            byte_len = TELESCOPE_LEN;
            fpos = TELESCOPE_KEY;
            break;
        case 11:
            byte_len = DATETIME_LEN;
            fpos = DATETIME_KEY;
            break;
        case 12:
            byte_len = DATETIMEUTC_LEN;
            fpos = DATETIMEUTC_KEY;
            break;
    }
    
    /* seek file position of key */
    fseek(sptr->SER_file->s_file, fpos, SEEK_SET);

    /* read out data */
    int bytes_read = 0; /* to check number of bytes read */
    bytes_read = fread(dest, 1, byte_len, sptr->SER_file->s_file);

    /* check if an error occured during read */
    if (bytes_read < byte_len) {
        if (feof(sptr->SER_file->s_file)) {
            *status = EOF_ERROR;
        }
        if (ferror(sptr->SER_file->s_file)) {
            *status = FREAD_ERROR;
        }
    }

    return (*status);
}

/** @brief  Return data at header key
 *
 *  Ensure that the dest buff to which the data will be written
 *  to has enough space to store the data. Refer to the defines in
 *  header_routines.h or follow the (key)_LEN format.
 *
 *  @param  sptr    (I) - Pointer to serfile
 *  @param  dest    (IO) - Destination buffer for header data
 *  @param  key     (I) - Record key of data to fetch
 *  @param  status  (IO) - Error status.
 *  @return Error status.
 */
int ser_get_key_record(serfile* sptr, void* dest, int key, int* status) {
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

    /* get byte length of record */
    int byte_len = 0;
    switch (key) {
        case FILEID_KEY:
            byte_len = FILEID_LEN;
            break;
        case LUID_KEY:
            byte_len = LUID_LEN;
            break;
        case COLORID_KEY:
            byte_len = COLORID_LEN;
            break;
        case LITTLEENDIAN_KEY:
            byte_len = LITTLEENDIAN_LEN;
            break;
        case IMAGEWIDTH_KEY:
            byte_len = IMAGEWIDTH_LEN;
            break;
        case IMAGEHEIGHT_KEY:
            byte_len = IMAGEHEIGHT_LEN;
            break;
        case PIXELDEPTHPERPLANE_KEY:
            byte_len = PIXELDEPTHPERPLANE_LEN;
            break;
        case FRAMECOUNT_KEY:
            byte_len = FRAMECOUNT_LEN;
            break;
        case OBSERVER_KEY:
            byte_len = OBSERVER_LEN;
            break;
        case INSTRUMENT_KEY:
            byte_len = INSTRUMENT_LEN;
            break;
        case TELESCOPE_KEY:
            byte_len = TELESCOPE_LEN;
            break;
        case DATETIME_KEY:
            byte_len = DATETIME_LEN;
            break;
        case DATETIMEUTC_KEY:
            byte_len = DATETIMEUTC_LEN;
            break;
        default:
            byte_len = 0;
    }
    
    /* check that if byte_len was 0, then the key was invalid */
    if (byte_len == 0) {
        *status = INVALID_HDR_KEY;
        return (*status);
    }

    /* seek file position of key */
    fseek(sptr->SER_file->s_file, key, SEEK_SET);

    /* read out data */
    int bytes_read = 0; /* to check number of bytes read */
    bytes_read = fread(dest, 1, byte_len, sptr->SER_file->s_file);

    /* check if an error occured during read */
    if (bytes_read < byte_len) {
        if (feof(sptr->SER_file->s_file)) {
            *status = EOF_ERROR;
        }
        if (ferror(sptr->SER_file->s_file)) {
            *status = FREAD_ERROR;
        }
    }

    return (*status);
}


