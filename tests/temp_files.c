/** @file   temp_files.c
 *  @brief  Function definitions and generations for `temp_files.h`.
 *
 *  @author Ryan V. Ngo
 */

#include "temp_files.h"
#include "cserio.h"

#include <stdint.h>
#include <stdio.h>

/*-------------------- Temp File Generation Routines --------------------*/

/** @brief  Generates a temp ser file.
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
int generate_tmp_file(char* full_path, FileHeader* file_header, void* pix_buff, long pix_buff_size) {
  /* open file, exit if it already exists */
  if (fopen(full_path, "r")) {
    printf("TMP FILE ALREADY EXISTS\n");
    return 0;
  }

  FILE* temp_file = fopen(full_path, "w+");
  if (!temp_file) {
    printf("Failed to create temp file\n");
    return 0;
  }

  /* Check for file_header */
  if (!file_header) {
    printf("NULL FILE HEADER\n");
    fclose(temp_file);
    remove(full_path);
    return 0;
  }

  /* write header to file */
  fwrite(file_header->file_ID, LEN_FILEID, 1, temp_file);
  fwrite(&file_header->lu_ID, LEN_LUID, 1, temp_file);
  fwrite(&file_header->color_ID, LEN_COLORID, 1, temp_file);
  fwrite(&file_header->little_endian, LEN_LITTLEENDIAN, 1, temp_file);
  fwrite(&file_header->image_width, LEN_IMAGEWIDTH, 1, temp_file);
  fwrite(&file_header->image_height, LEN_IMAGEHEIGHT, 1, temp_file);
  fwrite(&file_header->pixel_depth_per_plane, LEN_PIXELDEPTHPERPLANE, 1, temp_file);
  fwrite(&file_header->frame_count, LEN_FRAMECOUNT, 1, temp_file);
  fwrite(file_header->observer, LEN_OBSERVER, 1, temp_file);
  fwrite(file_header->instrment, LEN_INSTRUMENT, 1, temp_file);
  fwrite(file_header->telescope, LEN_TELESCOPE, 1, temp_file);
  fwrite(&file_header->date_time, LEN_DATETIME, 1, temp_file);
  fwrite(&file_header->date_time_UTC, LEN_DATETIMEUTC, 1, temp_file);

  /* write pix_buff to file */
  if (pix_buff_size) {
    fwrite(pix_buff, pix_buff_size, 1, temp_file);
  } else {
    int size_of_pixel = 0;
    if (file_header->pixel_depth_per_plane <= 8) size_of_pixel = 1;
    else size_of_pixel = 2;

    int num_of_planes = 0;
    if (file_header->color_ID < 100) num_of_planes = 1;
    else num_of_planes = 3;

    uint32_t width = file_header->image_width;
    uint32_t height = file_header->image_height;
    pix_buff_size = width * height * num_of_planes * size_of_pixel;
    fwrite(pix_buff, pix_buff_size, 1, temp_file);
  }

  fclose(temp_file);
  return 1;
}

/** @brief  Deletes temp ser file
 *  @param  full_path   (I) - name of temporary file
 *  @return 1 on success, 0 on fail. 
 */
int remove_tmp_file(char* full_path) {
  remove(full_path);
  return 1;
}


