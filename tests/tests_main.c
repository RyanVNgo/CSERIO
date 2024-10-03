/** @file   tests_main.c
 *  @brief  Primary source file for tests
 *
 *  @author Ryan V. Ngo
 */

#include "test_routines.h"

#include <string.h>

/*-------------------- Main --------------------*/

int main(int argc, char* argv[]) {
  int is_verbose = 0;

  /* check for verbose flag */
  if (argc > 1) {
    char* flag = argv[1];
    if (!strncmp(flag, "-v", 2)) {
      is_verbose= 1;
    }
  }

  run_core_routines_suite(is_verbose);
  run_header_routines_suite(is_verbose);
  run_img_routines_suite(is_verbose);

  return 0;
}
