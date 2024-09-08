/** @file test_utils.c
 *  @brief Helper routines for unit testing
 *
 *  @author Ryan V. Ngo
 */

#include "test_utils.h"

#include <stdio.h>

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
    printf("!CHECK SUCCESS! IN FILE %s ON LINE %4d: %4d == %4d\n", file, line, status, target);
  } else {
    printf("!CHECK FAILED!\n");
    printf("  -> IN FILE %s ON LINE %d\n", file, line);
    printf("    -> STATUS DID NOT MATCH TARGET: %d != %d\n", status, target);
  }
  return;
}
