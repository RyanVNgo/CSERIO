/** @file testsMain.c
 *  @brief Primary source file for tests
 *
 *  @author Ryan V. Ngo
 */

#include <stdio.h>
#include "cserio.h"

int main(int argc, char* argv[]) {
  if (argc <= 1) return 0;

  int status = 0;
  serfile* my_ser_file;
  ser_open_file(&my_ser_file, argv[1], READONLY, &status);

  printf("%d\n", status);
  printf("%p\n", my_ser_file);

  ser_close_file(my_ser_file, &status);
  return 0;
}
