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
  /* creating temporary file */
  uint8_t file_data[9];
  FileHeader file_header;
  test_data(&file_header, file_data);
  char* file_path = "/tmp/tmp_file_for_header_routines.ser";
  generate_tmp_file(file_path, &file_header, file_data, 0);




  remove_tmp_file(file_path);
  return; 
}

void test_ser_get_idx_record() {

  return;
}

void test_ser_get_key_record() {

  return;
}

/*-------------------- Main Test Call --------------------*/

void run_core_routines_suite() {
  printf("!-- RUNNING HEADER ROUTINES SUITE --!\n");

  test_ser_get_hdr_count();
  test_ser_get_idx_record();
  test_ser_get_key_record();

  return;
}

