/** @file test_header_routines.c
 *  @brief Implementation of testing header routines
 *
 *  @author Ryan V. Ngo
 */

#include "test_routines.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "test_utils.h"
#include "temp_files.h"

#include "cserio.h"

/*-------------------- Helper Functions --------------------*/

void test_data(FileHeader* file_header, void* pix_buff) {
  uint8_t img_data[9] = {
    255, 0, 255,
    0, 255, 0,
    255, 0, 255
  };
  memcpy(pix_buff, img_data, 9);

  FileHeader temp_file_header = {0};
  memcpy(temp_file_header.file_ID, "TEMP_FILE_1", 11);
  temp_file_header.lu_ID = 0;
  temp_file_header.color_ID = 8;
  temp_file_header.little_endian = 1;
  temp_file_header.image_width = 3;
  temp_file_header.image_height = 3;
  temp_file_header.pixel_depth_per_plane = 8;
  temp_file_header.frame_count = 1;
  memcpy(temp_file_header.observer, "OBSERVER", 8);
  memcpy(temp_file_header.instrment, "INSTRUMENT", 10);
  memcpy(temp_file_header.telescope, "TELESCOPE", 9);
  temp_file_header.date_time =  -1 * time(NULL);
  temp_file_header.date_time_UTC = time(NULL);

  memcpy(file_header, &temp_file_header, sizeof(FileHeader));

  return;
}

/*-------------------- Unit Tests --------------------*/

void test_ser_get_hdr_count() {
  int status = 0;
  int rec_count = 0;

  /* create and open temporary file */
  uint8_t file_data[9];
  FileHeader file_header;
  test_data(&file_header, file_data);
  char* file_path = "/tmp/tmp_file_for_header_routines.ser";
  generate_tmp_file(file_path, &file_header, file_data, 0);
  serfile* tmp_ser;
  ser_open_file(&tmp_ser, file_path, READONLY, &status);

  /* NULL sptr */
  status = 0;
  ser_get_hdr_count(NULL, &rec_count, &status);
  check_error(status, NULL_SPTR);
  check_int(rec_count, 0);

  /* NULL rec_count ptr */
  status = 0;
  ser_get_hdr_count(tmp_ser, NULL, &status);
  check_error(status, NULL_PARAM);
  check_int(rec_count, 0);

  /* No error */
  status = 0;
  ser_get_hdr_count(tmp_ser, &rec_count, &status);
  check_error(status, NO_ERROR);
  check_int(rec_count, HDR_UNIT_COUNT);

  ser_close_file(tmp_ser, &status);
  remove_tmp_file(file_path);
  return; 
}

void test_ser_get_idx_record() {
  const unsigned long byte_len = 40;
  char* empty_test_dest[40] = {0}; /* used to check is dest buffer was written to on fail */
  char* test_dest[40] = {0};
  int status = 0;

  /* create and open temporary file */
  uint8_t file_data[9];
  FileHeader file_header;
  test_data(&file_header, file_data);
  char* file_path = "/tmp/tmp_file_for_header_routines.ser";
  generate_tmp_file(file_path, &file_header, file_data, 0);
  serfile* tmp_ser;
  ser_open_file(&tmp_ser, file_path, READONLY, &status);

  /* NULL sptr */
  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_idx_record(NULL, test_dest, 0, &status);
  check_error(status, NULL_SPTR);
  check_buff(test_dest, empty_test_dest, byte_len);

  /* NULL dest*/
  status = 0;
  ser_get_idx_record(tmp_ser, NULL, 0, &status);
  check_error(status, NULL_DEST_BUFF);

  /* Negative index */
  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_idx_record(tmp_ser, test_dest, -1, &status);
  check_error(status, INVALID_HDR_IDX);
  check_buff(test_dest, empty_test_dest, byte_len);

  /* Out of upper bound index */
  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_idx_record(tmp_ser, test_dest, 13, &status);
  check_error(status, INVALID_HDR_IDX);
  check_buff(test_dest, empty_test_dest, byte_len);

  /* Check each record */
  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_idx_record(tmp_ser, test_dest, 0, &status); /* FILEID */
  check_error(status, NO_ERROR);
  check_buff(test_dest, file_header.file_ID, FILEID_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_idx_record(tmp_ser, test_dest, 1, &status); /* LUID */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.lu_ID, LUID_LEN);
  
  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_idx_record(tmp_ser, test_dest, 2, &status); /* COLORID */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.color_ID, COLORID_LEN);
  
  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_idx_record(tmp_ser, test_dest, 3, &status); /* LITTLEENDIAN */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.little_endian, LITTLEENDIAN_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_idx_record(tmp_ser, test_dest, 4, &status); /* IMAGEWIDTH */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.image_width, IMAGEWIDTH_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_idx_record(tmp_ser, test_dest, 5, &status); /* IMAGEHEIGHT */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.image_height, IMAGEHEIGHT_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_idx_record(tmp_ser, test_dest, 6, &status); /* PIXELDEPTHPERPLANE */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.pixel_depth_per_plane, PIXELDEPTHPERPLANE_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_idx_record(tmp_ser, test_dest, 7, &status); /* FRAMECOUNT */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.frame_count, FRAMECOUNT_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_idx_record(tmp_ser, test_dest, 8, &status); /* OBSERVER */
  check_error(status, NO_ERROR);
  check_buff(test_dest, file_header.observer, OBSERVER_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_idx_record(tmp_ser, test_dest, 9, &status); /* INSTRUMENT */
  check_error(status, NO_ERROR);
  check_buff(test_dest, file_header.instrment, INSTRUMENT_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_idx_record(tmp_ser, test_dest, 10, &status); /* TELESCOPE */
  check_error(status, NO_ERROR);
  check_buff(test_dest, file_header.telescope, TELESCOPE_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_idx_record(tmp_ser, test_dest, 11, &status); /* DATETIME */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.date_time, DATETIME_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_idx_record(tmp_ser, test_dest, 12, &status); /* DATETIMEUTC */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.date_time_UTC, DATETIMEUTC_LEN);

  ser_close_file(tmp_ser, &status);
  remove_tmp_file(file_path);
  return;
}

void test_ser_get_key_record() {
  const unsigned long byte_len = 40;
  char* empty_test_dest[40] = {0}; /* used to check is dest buffer was written to on fail */
  char* test_dest[40] = {0};
  int status = 0;

  /* create and open temporary file */
  uint8_t file_data[9];
  FileHeader file_header;
  test_data(&file_header, file_data);
  char* file_path = "/tmp/tmp_file_for_header_routines.ser";
  generate_tmp_file(file_path, &file_header, file_data, 0);
  serfile* tmp_ser;
  ser_open_file(&tmp_ser, file_path, READONLY, &status);

  /* NULL sptr */
  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_key_record(NULL, test_dest, FILEID_KEY, &status);
  check_error(status, NULL_SPTR);
  check_buff(test_dest, empty_test_dest, byte_len);

  /* NULL dest*/
  status = 0;
  ser_get_key_record(tmp_ser, NULL, FILEID_KEY, &status);
  check_error(status, NULL_DEST_BUFF);

  /* Invalid key (invoked through manual integer input) */
  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_key_record(tmp_ser, test_dest, -1 , &status);
  check_error(status, INVALID_HDR_KEY);
  check_buff(test_dest, empty_test_dest, byte_len);

  /* Check each valid key */
  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_key_record(tmp_ser, test_dest, FILEID_KEY , &status); /* FILEID */
  check_error(status, NO_ERROR);
  check_buff(test_dest, file_header.file_ID, FILEID_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_key_record(tmp_ser, test_dest, LUID_KEY, &status); /* LUID */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.lu_ID, LUID_LEN);
  
  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_key_record(tmp_ser, test_dest, COLORID_KEY, &status); /* COLORID */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.color_ID, COLORID_LEN);
  
  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_key_record(tmp_ser, test_dest, LITTLEENDIAN_KEY, &status); /* LITTLEENDIAN */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.little_endian, LITTLEENDIAN_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_key_record(tmp_ser, test_dest, IMAGEWIDTH_KEY, &status); /* IMAGEWIDTH */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.image_width, IMAGEWIDTH_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_key_record(tmp_ser, test_dest, IMAGEHEIGHT_KEY, &status); /* IMAGEHEIGHT */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.image_height, IMAGEHEIGHT_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_key_record(tmp_ser, test_dest, PIXELDEPTHPERPLANE_KEY, &status); /* PIXELDEPTHPERPLANE */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.pixel_depth_per_plane, PIXELDEPTHPERPLANE_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_key_record(tmp_ser, test_dest, FRAMECOUNT_KEY, &status); /* FRAMECOUNT */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.frame_count, FRAMECOUNT_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_key_record(tmp_ser, test_dest, OBSERVER_KEY, &status); /* OBSERVER */
  check_error(status, NO_ERROR);
  check_buff(test_dest, file_header.observer, OBSERVER_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_key_record(tmp_ser, test_dest, INSTRUMENT_KEY, &status); /* INSTRUMENT */
  check_error(status, NO_ERROR);
  check_buff(test_dest, file_header.instrment, INSTRUMENT_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_key_record(tmp_ser, test_dest, TELESCOPE_KEY, &status); /* TELESCOPE */
  check_error(status, NO_ERROR);
  check_buff(test_dest, file_header.telescope, TELESCOPE_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_key_record(tmp_ser, test_dest, DATETIME_KEY, &status); /* DATETIME */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.date_time, DATETIME_LEN);

  status = 0;
  memset(test_dest, 0, byte_len);
  ser_get_key_record(tmp_ser, test_dest, DATETIMEUTC_KEY, &status); /* DATETIMEUTC */
  check_error(status, NO_ERROR);
  check_buff(test_dest, &file_header.date_time_UTC, DATETIMEUTC_LEN);

  ser_close_file(tmp_ser, &status);
  remove_tmp_file(file_path);
  return;
}

/*-------------------- Main Test Call --------------------*/

void run_header_routines_suite() {
  printf("!-- RUNNING HEADER ROUTINES SUITE --!\n");

  test_ser_get_hdr_count();
  test_ser_get_idx_record();
  test_ser_get_key_record();

  return;
}

