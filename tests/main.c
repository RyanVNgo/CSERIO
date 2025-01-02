#include <stdio.h>

#include "include/cserio.h"

int main(int argc, char** argv) {
  float version_num = cserio_version_number(NULL);
  printf("CSERIO Version - %f\n", version_num);
  return 0;
}
