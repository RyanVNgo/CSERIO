/** @file   temp_files.h
 *  @brief  Defines and prototypes for temp file creation routines.
 *
 *  This file provides the functions necessary to easily create 
 *  temporary files for unit testing.
 *
 *  @author Ryan V. Ngo
 */

#ifndef TEMP_FILES_H
#define TEMP_FILES_H

/*-------------------- SER Header Symbolic Constants --------------------*/

/**
 * These constants represent the byte length of each header component
 * for V3 SER files.
 */
#define LEN_FILEID 14
#define LEN_LUID 4
#define LEN_COLORID 4 
#define LEN_LITTLEENDIAN 4 
#define LEN_IMAGEWIDTH 4 
#define LEN_IMAGEHEIGHT 4 
#define LEN_PIXELDEPTHPERPLANE 4 
#define LEN_FRAMECOUNT 4 
#define LEN_OBSERVER 40 
#define LEN_INSTRUMENT 40 
#define LEN_TELESCOPE 40 
#define LEN_DATETIME 8 
#define LEN_DATETIMEUTC 8 

/*-------------------- SER File Header Structure --------------------*/

#include <stdint.h>

/**
 *  Struct for the organization of a ser file header.
 */
typedef struct FileHeader{
  unsigned char file_ID[LEN_FILEID]; 
  uint32_t lu_ID;
  uint32_t color_ID;
  uint32_t little_endian;
  uint32_t image_width;
  uint32_t image_height;
  uint32_t pixel_depth_per_plane;
  uint32_t frame_count;
  unsigned char observer[LEN_OBSERVER];
  unsigned char instrment[LEN_INSTRUMENT];
  unsigned char telescope[LEN_TELESCOPE];
  int64_t date_time;
  int64_t date_time_UTC;
} FileHeader;

/*-------------------- Temp File Generation Routines --------------------*/

/** @brief  Generates a ser file.
 *
 *  Although this purely generates a ser file, this should be followed by
 *  a remove_tmp_file call to the same file path to remove the temp file.
 *
 *  If the file already exists, the method will not create the file and
 *  return.
 *  
 *  If byte_len is 0, this method will use the metadata from the passed 
 *  file_header to write the passed pix_buff data to the file. Ensure 
 *  that the file_header correctly describes the pix_buff data in this
 *  scenario.
 *
 *  @param  full_path     (I) - path of temp file
 *  @param  file_header   (I) - header to write to temp file
 *  @param  pix_buff      (I) - start of image data
 *  @param  pix_buff_size (I) - size of pix_buff in bytes
 *  @return 1 on success, 0 on fail. 
 */
int generate_tmp_file(char* full_path, FileHeader* file_header, void* pix_buff, long pix_buff_size);

/** @brief  Deletes temp file
 *  @param  filename   (I) - name of temporary file
 *  @return 1 on success, 0 on fail. 
 */
int remove_tmp_file(char* full_path);

#endif
