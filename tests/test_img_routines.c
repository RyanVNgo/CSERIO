/** @file test_img_routines.c
 *  @brief Implementation of testing img routines
 *
 *  @author Ryan V. Ngo
 */

#include "errors.h"
#include "test_routines.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "test_utils.h"
#include "temp_files.h"

#include "cserio.h"

/*-------------------- Helper Functions --------------------*/

void test_8_bit_mono_data(FileHeader* file_header, void* pix_buff) {
  uint8_t img_data[27] = {
    255, 0, 255,
    0, 255, 0,
    255, 0, 255,

    0, 255, 0,
    0, 255, 0,
    0, 255, 0,

    255, 255, 255,
    0, 0, 0,
    255, 255, 255
  };
  memcpy(pix_buff, img_data, sizeof(img_data));

  FileHeader temp_file_header = {0};
  memcpy(temp_file_header.file_ID, "TEMP_FILE_8M", 12);
  temp_file_header.lu_ID = 0;
  temp_file_header.color_ID = BAYER_RGGB;
  temp_file_header.little_endian = LITTLEENDIAN_TRUE;
  temp_file_header.image_width = 3;
  temp_file_header.image_height = 3;
  temp_file_header.pixel_depth_per_plane = 8;
  temp_file_header.frame_count = 3;
  memcpy(temp_file_header.observer, "OBSERVER", 8);
  memcpy(temp_file_header.instrment, "INSTRUMENT", 10);
  memcpy(temp_file_header.telescope, "TELESCOPE", 9);
  temp_file_header.date_time =  -1 * time(NULL);
  temp_file_header.date_time_UTC = time(NULL);

  memcpy(file_header, &temp_file_header, sizeof(FileHeader));

  return;
}

void test_8_bit_color_data(FileHeader* file_header, void* pix_buff) {
  uint8_t img_data[81] = {
    255, 255, 255, 0, 0, 0, 255, 255, 255,
    0, 0, 0, 255, 255, 255, 0, 0, 0,
    255, 255, 255, 0, 0, 0, 255, 255, 255,
    
    0, 0, 0, 255, 255, 255, 0, 0, 0,
    0, 0, 0, 255, 255, 255, 0, 0, 0,
    0, 0, 0, 255, 255, 255, 0, 0, 0,

    255, 255, 255, 255, 255, 255, 255, 255, 255,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    255, 255, 255, 255, 255, 255, 255, 255, 255
  };
  memcpy(pix_buff, img_data, sizeof(img_data));

  FileHeader temp_file_header = {0};
  memcpy(temp_file_header.file_ID, "TEMP_FILE_8C", 12);
  temp_file_header.lu_ID = 0;
  temp_file_header.color_ID = RGB;
  temp_file_header.little_endian = LITTLEENDIAN_TRUE;
  temp_file_header.image_width = 3;
  temp_file_header.image_height = 3;
  temp_file_header.pixel_depth_per_plane = 8;
  temp_file_header.frame_count = 3;
  memcpy(temp_file_header.observer, "OBSERVER", 8);
  memcpy(temp_file_header.instrment, "INSTRUMENT", 10);
  memcpy(temp_file_header.telescope, "TELESCOPE", 9);
  temp_file_header.date_time =  -1 * time(NULL);
  temp_file_header.date_time_UTC = time(NULL);

  memcpy(file_header, &temp_file_header, sizeof(FileHeader));
  return;
}

void test_16_bit_mono_data(FileHeader* file_header, void* pix_buff) {
  uint16_t img_data[27] = {
    255, 0, 255,
    0, 255, 0,
    255, 0, 255,

    0, 255, 0,
    0, 255, 0,
    0, 255, 0,

    255, 255, 255,
    0, 0, 0,
    255, 255, 255
  };
  memcpy(pix_buff, img_data, sizeof(img_data));

  FileHeader temp_file_header = {0};
  memcpy(temp_file_header.file_ID, "TEMP_FILE_16M", 13);
  temp_file_header.lu_ID = 0;
  temp_file_header.color_ID = BAYER_RGGB;
  temp_file_header.little_endian = LITTLEENDIAN_TRUE;
  temp_file_header.image_width = 3;
  temp_file_header.image_height = 3;
  temp_file_header.pixel_depth_per_plane = 16;
  temp_file_header.frame_count = 3;
  memcpy(temp_file_header.observer, "OBSERVER", 8);
  memcpy(temp_file_header.instrment, "INSTRUMENT", 10);
  memcpy(temp_file_header.telescope, "TELESCOPE", 9);
  temp_file_header.date_time =  -1 * time(NULL);
  temp_file_header.date_time_UTC = time(NULL);

  memcpy(file_header, &temp_file_header, sizeof(FileHeader));
  return;
}

void test_16_bit_color_data(FileHeader* file_header, void* pix_buff) {
  uint16_t img_data[81] = {
    65535, 65535, 65535, 0, 0, 0, 65535, 65535, 65535,
    0, 0, 0, 65535, 65535, 65535, 0, 0, 0,
    65535, 65535, 65535, 0, 0, 0, 65535, 65535, 65535,
    
    0, 0, 0, 65535, 65535, 65535, 0, 0, 0,
    0, 0, 0, 65535, 65535, 65535, 0, 0, 0,
    0, 0, 0, 65535, 65535, 65535, 0, 0, 0,

    65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535,
  };
  memcpy(pix_buff, img_data, sizeof(img_data));

  FileHeader temp_file_header = {0};
  memcpy(temp_file_header.file_ID, "TEMP_FILE_16C", 13);
  temp_file_header.lu_ID = 0;
  temp_file_header.color_ID = RGB;
  temp_file_header.little_endian = LITTLEENDIAN_TRUE;
  temp_file_header.image_width = 3;
  temp_file_header.image_height = 3;
  temp_file_header.pixel_depth_per_plane = 16;
  temp_file_header.frame_count = 3;
  memcpy(temp_file_header.observer, "OBSERVER", 8);
  memcpy(temp_file_header.instrment, "INSTRUMENT", 10);
  memcpy(temp_file_header.telescope, "TELESCOPE", 9);
  temp_file_header.date_time =  -1 * time(NULL);
  temp_file_header.date_time_UTC = time(NULL);

  memcpy(file_header, &temp_file_header, sizeof(FileHeader));
  return;
}

/*-------------------- Unit Tests --------------------*/

void test_ser_get_frame_count(serfile* sptr, FileHeader* file_header, void* pix_buff) {
  int status = 0;
  int frame_count = 0;

  /* NULL sptr */
  status = 0;
  ser_get_frame_count(NULL, &frame_count, &status); 
  check_error(status, NULL_SPTR);

  /* NULL frame_coount*/
  status = 0;
  ser_get_frame_count(sptr, NULL, &status); 
  check_error(status, NULL_PARAM);

  /* Pass */
  status = 0;
  ser_get_frame_count(sptr, &frame_count, &status); 
  check_error(status, NO_ERROR);
  check_int(frame_count, file_header->frame_count);

  return;
}

void test_ser_get_frame_dim_size(serfile* sptr, FileHeader* file_header, void* pix_buff) {
  int status = 0;
  int size = 0;

  /* NULL sptr */
  status = 0;
  ser_get_frame_dim_size(NULL, &size, DIM_LAYER, &status);
  check_error(status, NULL_SPTR);

  /* NULL size */
  status = 0;
  ser_get_frame_dim_size(sptr, NULL, DIM_LAYER, &status);
  check_error(status, NULL_PARAM);

  /* Invalid dimension */
  status = 0;
  ser_get_frame_dim_size(sptr, &size, -1, &status);
  check_error(status, INVALID_DIM_IDX);

  status = 0;
  ser_get_frame_dim_size(sptr, &size, 3, &status);
  check_error(status, INVALID_DIM_IDX);

  /* Pass */
  status = 0;
  int layer = 0;
  int width = 0;
  int height = 0;
  ser_get_frame_dim_size(sptr, &layer, DIM_LAYER, &status);
  ser_get_frame_dim_size(sptr, &width, DIM_WIDTH, &status);
  ser_get_frame_dim_size(sptr, &height, DIM_HEIGHT, &status);
  check_error(status, NO_ERROR);

  if (file_header->color_ID < 100) {
    check_int(layer, 1);
  } else {
    check_int(layer, 3);
  }

  check_int(width, file_header->image_width);
  check_int(height, file_header->image_height);

  return;
}

void test_ser_get_bytes_per_pixel(serfile* sptr, FileHeader* file_header, void* pix_buff) {
  int status = 0;
  unsigned long bytes_per_pixel = 0;

  /* NULL sptr */
  status = 0;
  ser_get_bytes_per_pixel(NULL, &bytes_per_pixel, &status);
  check_error(status, NULL_SPTR);

  /* NULL bytes_per_pixel */
  status = 0;
  ser_get_bytes_per_pixel(sptr, NULL, &status);
  check_error(status, NULL_PARAM);
  
  /* Pass */
  status = 0;
  ser_get_bytes_per_pixel(sptr, &bytes_per_pixel, &status);
  check_error(status, NO_ERROR);

  int number_of_planes = 0;
  ser_get_frame_dim_size(sptr, &number_of_planes, DIM_LAYER, &status);

  if (file_header->pixel_depth_per_plane <= 8) {
    check_int(bytes_per_pixel, number_of_planes);
  } else {
    check_int(bytes_per_pixel, 2 * number_of_planes);
  }

  return;
}

void test_ser_get_frame_byte_size(serfile* sptr, FileHeader* file_header, void* pix_buff, unsigned long byte_size) {
  int status = 0;
  unsigned long byte_size_out = 0;

  /* NULL sptr */
  status = 0;
  ser_get_frame_byte_size(NULL, &byte_size_out, &status);
  check_error(status, NULL_SPTR);
  
  /* NULL byte_size */
  status = 0;
  ser_get_frame_byte_size(sptr, NULL, &status);
  check_error(status, NULL_PARAM);

  /* Pass */
  status = 0;
  ser_get_frame_byte_size(sptr, &byte_size_out, &status);
  check_error(status, NO_ERROR);
  check_unsigned_long(byte_size_out, byte_size);

  return;
}

void test_ser_read_frame(serfile* sptr, FileHeader* file_header, void* pix_buff) {
  int status = 0;
  unsigned long byte_size = 0;
  ser_get_frame_byte_size(sptr, &byte_size, &status);
  uint8_t read_buff[byte_size];

  /* NULL sptr */
  status = 0;
  ser_read_frame(NULL, &read_buff, 0, &status);
  check_error(status, NULL_SPTR);

  /* NULL dest */
  status = 0;
  ser_read_frame(sptr, NULL, 0, &status);
  check_error(status, NULL_DEST_BUFF);

  /* invalid index */
  status = 0;
  ser_read_frame(sptr, &read_buff, -1, &status);
  check_error(status, INVALID_FRAME_IDX);

  status = 0;
  ser_read_frame(sptr, &read_buff, file_header->frame_count, &status);
  check_error(status, INVALID_FRAME_IDX);

  /* Pass */
  /* Check every frame */
  status = 0;
  for (int i = 0; i < file_header->frame_count; i++) {
    ser_read_frame(sptr, &read_buff, i, &status);
    check_error(status, NO_ERROR);
    check_buff(read_buff, pix_buff + (i * byte_size), byte_size);
  }

  return;
}

/*-------------------- Main Test Call --------------------*/

void run_img_routines_suite() {
  printf("!-- RUNNING IMAGE ROUTINES SUITE --!\n");
  
  /* sequentially shared data */
  FileHeader temp_header;
  int status = 0;
  unsigned long byte_size = 0;

  /* 8-bit mono image testing */
  char* temp_8M_file_path = "/tmp/tmp_8M_file.ser";
  uint8_t temp_8M_buff[27];
  test_8_bit_mono_data(&temp_header, temp_8M_buff);

  generate_tmp_file(temp_8M_file_path, &temp_header, temp_8M_buff, 0);
  serfile* ser_8M;
  ser_open_file(&ser_8M, temp_8M_file_path, READONLY, &status);

  test_ser_get_frame_count(ser_8M, &temp_header, temp_8M_buff);
  test_ser_get_frame_dim_size(ser_8M, &temp_header, temp_8M_buff);
  test_ser_get_bytes_per_pixel(ser_8M, &temp_header, temp_8M_buff);
  byte_size = sizeof(temp_8M_buff) / temp_header.frame_count;
  test_ser_get_frame_byte_size(ser_8M, &temp_header, temp_8M_buff, byte_size);
  test_ser_read_frame(ser_8M, &temp_header, temp_8M_buff);

  ser_close_file(ser_8M, &status);
  remove_tmp_file(temp_8M_file_path);

  /* 8-bit color image testing */
  char* temp_8C_file_path = "/tmp/tmp_8C_file.ser";
  uint8_t temp_8C_buff[81];
  test_8_bit_color_data(&temp_header, temp_8C_buff);

  generate_tmp_file(temp_8C_file_path, &temp_header, temp_8C_buff, 0);
  serfile* ser_8C;
  ser_open_file(&ser_8C, temp_8C_file_path, READONLY, &status);

  test_ser_get_frame_count(ser_8C, &temp_header, temp_8C_buff);
  test_ser_get_frame_dim_size(ser_8C, &temp_header, temp_8C_buff);
  test_ser_get_bytes_per_pixel(ser_8C, &temp_header, temp_8C_buff);
  byte_size = sizeof(temp_8C_buff) / temp_header.frame_count;
  test_ser_get_frame_byte_size(ser_8C, &temp_header, temp_8C_buff, byte_size);
  test_ser_read_frame(ser_8C, &temp_header, temp_8C_buff);

  ser_close_file(ser_8C, &status);
  remove_tmp_file(temp_8C_file_path);

  /* 16-bit mono image testing */
  char* temp_16M_file_path = "/tmp/tmp_16M_file.ser";
  uint16_t temp_16M_buff[27];
  test_16_bit_mono_data(&temp_header, temp_16M_buff);

  generate_tmp_file(temp_16M_file_path, &temp_header, temp_16M_buff, 0);
  serfile* ser_16M;
  ser_open_file(&ser_16M, temp_16M_file_path, READONLY, &status);

  test_ser_get_frame_count(ser_16M, &temp_header, temp_16M_buff);
  test_ser_get_frame_dim_size(ser_16M, &temp_header, temp_16M_buff);
  test_ser_get_bytes_per_pixel(ser_16M, &temp_header, temp_16M_buff);
  byte_size = sizeof(temp_16M_buff) / temp_header.frame_count;
  test_ser_get_frame_byte_size(ser_16M, &temp_header, temp_16M_buff, byte_size);
  test_ser_read_frame(ser_16M, &temp_header, temp_16M_buff);

  ser_close_file(ser_16M, &status);
  remove_tmp_file(temp_16M_file_path);

  /* 16-bit color image testing */
  char* temp_16C_file_path = "/tmp/tmp_16C_file.ser";
  uint16_t temp_16C_buff[81];
  test_16_bit_color_data(&temp_header, temp_16M_buff);

  generate_tmp_file(temp_16C_file_path, &temp_header, temp_16C_buff, 0);
  serfile* ser_16C;
  ser_open_file(&ser_16C, temp_16C_file_path, READONLY, &status);

  test_ser_get_frame_count(ser_16C, &temp_header, temp_16C_buff);
  test_ser_get_frame_dim_size(ser_16C, &temp_header, temp_16C_buff);
  test_ser_get_bytes_per_pixel(ser_16C, &temp_header, temp_16C_buff);
  byte_size = sizeof(temp_16C_buff) / temp_header.frame_count;
  test_ser_get_frame_byte_size(ser_16C, &temp_header, temp_16C_buff, byte_size);
  test_ser_read_frame(ser_16C, &temp_header, temp_16C_buff);

  ser_close_file(ser_16C, &status);
  remove_tmp_file(temp_16C_file_path);
 
  return;
}
