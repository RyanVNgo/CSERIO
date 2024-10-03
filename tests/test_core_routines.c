/** @file test_core_routines.c
 *  @brief Implementation of testing core routines
 *
 *  @author Ryan V. Ngo
 */

#include "test_routines.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "test_utils.h"
#include "temp_files.h"

#include "cserio.h"

/*-------------------- Helper Functions --------------------*/

void test_data_1(FileHeader* file_header, void* pix_buff) {
  uint8_t img_data[9] = {
    255, 0, 255,
    0, 255, 0,
    255, 0, 255
  };
  memcpy(pix_buff, img_data, 9);

  FileHeader temp_file_header = {0};
  memcpy(temp_file_header.file_ID, "TEMP_FILE_1", 11);
  temp_file_header.lu_ID = 0;
  temp_file_header.color_ID = 0;
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

void test_ser_file_open() {
  /* opening valid file */
  uint8_t file_1_data[9];
  FileHeader file_1_header;
  test_data_1(&file_1_header, file_1_data);
  char* file_1_path = "/tmp/tmp_file_1.ser";
  generate_tmp_file(file_1_path, &file_1_header, file_1_data, 0);

  int status = 0;
  serfile* file_1_ser;
  ser_open_file(&file_1_ser, file_1_path, READONLY, &status);
  check_error(status, NO_ERROR);
  ser_close_file(file_1_ser, &status);
  remove_tmp_file(file_1_path);

  /* opening with null ser ptr */
  uint8_t file_2_data[9];
  FileHeader file_2_header;
  test_data_1(&file_2_header, file_2_data);
  char* file_2_path = "/tmp/tmp_file_2.ser";
  generate_tmp_file(file_2_path, &file_2_header, file_2_data, 0);

  status = 0;
  ser_open_file(NULL, file_2_path, READONLY, &status);
  check_error(status, NULL_SPTR);
  remove_tmp_file(file_2_path);

  /* opening an valid path, invalid type*/
  /* the content of the file is still in ser format, but ext is invalid */
  uint8_t file_3_data[9];
  FileHeader file_3_header;
  test_data_1(&file_3_header, file_3_data);
  char* file_3_path = "/tmp/tmp_file_3.txt";
  generate_tmp_file(file_3_path, &file_3_header, file_3_data, 0);

  status = 0;
  serfile* file_3_ser;
  ser_open_file(&file_3_ser, file_3_path, READONLY, &status);
  check_error(status, INVALID_FILENAME);
  remove_tmp_file(file_3_path);

  /* opening an invalid path */
  char* file_4_path = "/tmp/tmp_file_4.txt";

  status = 0;
  serfile* file_4_ser;
  ser_open_file(&file_4_ser, file_4_path, READONLY, &status);
  check_error(status, INVALID_FILENAME);

  /* null path */
  status = 0;
  serfile* file_5_ser;
  ser_open_file(&file_5_ser, NULL, READONLY, &status);
  check_error(status, NULL_FILENAME);

  return;
}

void test_ser_file_close() {
  /* generating a file to open */
  int status = 0;
  uint8_t tmp_data[9];
  FileHeader tmp_header;
  test_data_1(&tmp_header, tmp_data);
  char* tmp_file_path = "/tmp/tmp_ser.ser";
  generate_tmp_file(tmp_file_path, &tmp_header, tmp_data, 0);
  serfile* tmp_ser;
  ser_open_file(&tmp_ser, tmp_file_path, READONLY, &status);

  /* NULL ser ptr */
  status = 0;
  ser_close_file(NULL, &status);
  check_error(status, NULL_SPTR);

  /* broken ser */
  fclose(tmp_ser->SER_file->s_file);  /* breaking ser */
  tmp_ser->SER_file->s_file = NULL;   /* breaking ser */
  status = 0;
  ser_close_file(tmp_ser, &status);
  check_error(status, FILE_CLOSE_ERROR);

  /* valid close */
  ser_open_file(&tmp_ser, tmp_file_path, READONLY, &status); /* reopening */
  status = 0;
  ser_close_file(tmp_ser, &status);
  check_error(status, NO_ERROR);

  remove_tmp_file(tmp_file_path);
  return;
}

/*-------------------- Main Test Call --------------------*/

void run_core_routines_suite(int is_verbose) {
  printf("!-- RUNNING CORE ROUTINES SUITE --!\n");
  IS_VERBOSE = is_verbose;

  test_ser_file_open();
  test_ser_file_close();

  return;
}

