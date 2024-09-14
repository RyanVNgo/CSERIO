/** @file test_utils.c
 *  @brief Helper routines for unit testing
 *
 *  @author Ryan V. Ngo
 */

#include "test_utils.h"

#include <stdio.h>
#include <string.h>

/*-------------------- Test Utils --------------------*/

/** @brief Check if status values are equal
 *  
 *  This method checks whether or not the passed status value
 *  is equal to the target value where the target value
 *  is a library defined error.
 *
 *  You shouldn't need to use this method directly as the
 *  check_error defined excludes the last two params but is
 *  called through definition.
 *
 *  @param  status    (I) - status value.
 *  @param  target    (I) - target value.
 *  @param  file      (I) - source file of error
 *  @param  line      (I) - line number of error
 *  @return Void.
 */
void check_error_v(int status, int target, char* file, int line) {
  if (status == target) {
    printf("!CHECK STATUS SUCCESS! IN FILE %s ON LINE %4d: %4d == %4d\n", file, line, status, target);
  } else {
    printf("!CHECK STATUS FAILED!\n");
    printf("  -> IN FILE %s ON LINE %d\n", file, line);
    printf("    -> STATUS DID NOT MATCH TARGET: %d != %d\n", status, target);
  }
  return;
}

/** @brief  Check if the result and target buffers are equal
 *
 *  @param  result    (I) - Result buffer.
 *  @param  target    (I) - Target buffer.
 *  @param  byte_len  (I) - Number of bytes to compare.
 *  @param  file      (I) - source file of error
 *  @param  line      (I) - line number of error
 *  @return Void.
 */
void check_buff_v(void* result, void* target, unsigned long byte_len, char* file, int line) {
  if (!memcmp(result, target, byte_len)) {
    printf("!CHECK BUFFERS SUCCESS! IN FILE %s ON LINE %4d\n", file, line);
  } else {
    printf("!CHECK BUFF FAILED!\n");
    printf("  -> IN FILE %s ON LINE %d\n", file, line);
    printf("    -> BUFFERS WERE NOT EQUAL!\n");
  }
  return;
}

/** @brief  Check if the result and target integers are equal
 *
 *  @param  result    (I) - Result integer.
 *  @param  target    (I) - Target integer.
 *  @param  file      (I) - source file of error.
 *  @param  line      (I) - line number of error.
 *  @return Void.
 */
void check_int_v(int result, int target, char* file, int line) {
  if (result == target) {
    printf("!CHECK INTEGERS SUCCESS! IN FILE %s ON LINE %4d: %4d == %4d\n", file, line, result, target);
  } else {
    printf("!CHECK INTEGERS FAILED!\n");
    printf("  -> IN FILE %s ON LINE %d\n", file, line);
    printf("    -> INTEGERS WERE NOT EQUAL: %4d != %4d\n", result, target);
  }
  return;
}

