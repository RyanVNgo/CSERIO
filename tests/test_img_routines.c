/** @file test_img_routines.c
 *  @brief Implementation of testing img routines
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

void test_8_bit_mono_data(FileHeader* file_header, void* pix_buff) {
  return;
}

void test_8_bit_color_data(FileHeader* file_header, void* pix_buff) {
  return;
}

void test_16_bit_mono_data(FileHeader* file_header, void* pix_buff) {
  return;
}

void test_16_bit_color_data(FileHeader* file_header, void* pix_buff) {
  return;
}

/*-------------------- Unit Tests --------------------*/

void test_ser_get_frame_count(serfile* sptr, FileHeader* file_header, void* pix_buff) {
  return;
}

void test_ser_get_frame_dim_size(serfile* sptr, FileHeader* file_header, void* pix_buff) {
  return;
}

void test_ser_get_bytes_per_pixel(serfile* sptr, FileHeader* file_header, void* pix_buff) {
  return;
}

void test_ser_get_frame_byte_size(serfile* sptr, FileHeader* file_header, void* pix_buff) {
  return;
}

void test_ser_read_frame(serfile* sptr, FileHeader* file_header, void* pix_buff) {
  return;
}

/*-------------------- Main Test Call --------------------*/

void run_img_routines_suite() {
  printf("!-- RUNNING HEADER ROUTINES SUITE --!\n");
  
  /* sequentially shared data */
  FileHeader temp_header;

  /* 8-bit mono image testing */
  char* temp_8M_file_path = "/tmp/tmp_8M_file.ser";
  uint8_t temp_8M_buff[27];
  test_8_bit_mono_data(&temp_header, temp_8M_buff);

  generate_tmp_file(temp_8M_file_path, &temp_header, temp_8M_buff, 0);
  serfile* ser_8M;

  test_ser_get_frame_count(ser_8M, &temp_header, temp_8M_buff);
  test_ser_get_frame_dim_size(ser_8M, &temp_header, temp_8M_buff);
  test_ser_get_bytes_per_pixel(ser_8M, &temp_header, temp_8M_buff);
  test_ser_get_frame_byte_size(ser_8M, &temp_header, temp_8M_buff);
  test_ser_read_frame(ser_8M, &temp_header, temp_8M_buff);

  remove_tmp_file(temp_8M_file_path);

  /* 8-bit color image testing */
  /*
  char* temp_8C_file_path = "/tmp/tmp_8C_file.ser";
  uint8_t temp_8C_buff[81];
  test_8_bit_color_data(&temp_header, temp_8C_buff);

  generate_tmp_file(temp_8C_file_path, &temp_header, temp_8C_buff, 0);
  serfile* ser_8C;

  test_ser_get_frame_count(ser_8C, &temp_header, temp_8C_buff);
  test_ser_get_frame_dim_size(ser_8C, &temp_header, temp_8C_buff);
  test_ser_get_bytes_per_pixel(ser_8C, &temp_header, temp_8C_buff);
  test_ser_get_frame_byte_size(ser_8C, &temp_header, temp_8C_buff);
  test_ser_read_frame(ser_8C, &temp_header, temp_8C_buff);

  remove_tmp_file(temp_8C_file_path);
  */

  /* 16-bit mono image testing */
  /*
  char* temp_16M_file_path = "/tmp/tmp_16M_file.ser";
  uint16_t temp_16M_buff[27];
  test_8_bit_color_data(&temp_header, temp_16M_buff);

  generate_tmp_file(temp_16M_file_path, &temp_header, temp_16M_buff, 0);
  serfile* ser_16M;

  test_ser_get_frame_count(ser_16M, &temp_header, temp_16M_buff);
  test_ser_get_frame_dim_size(ser_16M, &temp_header, temp_16M_buff);
  test_ser_get_bytes_per_pixel(ser_16M, &temp_header, temp_16M_buff);
  test_ser_get_frame_byte_size(ser_16M, &temp_header, temp_16M_buff);
  test_ser_read_frame(ser_16M, &temp_header, temp_16M_buff);

  remove_tmp_file(temp_16M_file_path);
  */

  /* 16-bit color image testing */
  /*
  char* temp_16C_file_path = "/tmp/tmp_16C_file.ser";
  uint16_t temp_16C_buff[81];
  test_8_bit_color_data(&temp_header, temp_16C_buff);

  generate_tmp_file(temp_16C_file_path, &temp_header, temp_16C_buff, 0);
  serfile* ser_16C;

  test_ser_get_frame_count(ser_16C, &temp_header, temp_16C_buff);
  test_ser_get_frame_dim_size(ser_16C, &temp_header, temp_16C_buff);
  test_ser_get_bytes_per_pixel(ser_16C, &temp_header, temp_16C_buff);
  test_ser_get_frame_byte_size(ser_16C, &temp_header, temp_16C_buff);
  test_ser_read_frame(ser_16C, &temp_header, temp_16C_buff);

  remove_tmp_file(temp_16C_file_path);
  */
 
  return;
}
