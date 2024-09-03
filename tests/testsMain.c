/** @file testsMain.c
 *  @brief Primary source file for tests
 *
 *  @author Ryan V. Ngo
 */

#include <stdio.h>

#include "cserio.h"

int main(int argc, char* argv[]) {
  /* temporary core test */
  float v_num = 0;
  cserio_version_number(&v_num);
  printf("%2.4f\n", v_num);
  
  return 0;
}
