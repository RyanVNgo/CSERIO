/** @file   tests_main.c
 *  @brief  Primary source file for tests
 *
 *  @author Ryan V. Ngo
 */

#include "test_routines.h"

/*-------------------- Main --------------------*/

int main(int argc, char* argv[]) {

  run_core_routines_suite();
  run_header_routines_suite();
  run_img_routines_suite();

  return 0;
}
