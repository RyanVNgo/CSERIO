/** @file test_core_routines.c
 *  @brief Implementation of testing core routines
 *
 *  @author Ryan V. Ngo
 */

#include "test_core_routines.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

  uint8_t file_1_data[9];
  FileHeader file_1_header;
  test_data_1(&file_1_header, file_1_data);
  char* file_1_path = "/tmp/tmp_file_1.ser";
  generate_tmp_file(file_1_path, &file_1_header, file_1_data, 0);

  int status = 0;
  serfile* file_1_ser;

  ser_open_file(&file_1_ser, file_1_path, READONLY, &status);



  ser_close_file(file_1_ser, &status);

  remove_tmp_file(file_1_path);

  return;
}

void test_ser_file_close() {

  return;
}

/*-------------------- Main Test Call --------------------*/

void run_core_routines_suite() {

  test_ser_file_open();
  test_ser_file_close();

  return;
}

