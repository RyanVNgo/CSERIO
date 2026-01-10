
#include <stdio.h>

#if defined(UNITY_TEST)
#define CSERIO_IMPLEMENTATION
#endif

#include "../cserio.h"

int main() {

  int major = 0;
  int minor = 0;
  int micro = 0;
  cserio_version_number(&major, &minor, &micro);
  printf("CSERIO Version: %d.%d.%d\n", major, minor, micro);

  return 0;
}

