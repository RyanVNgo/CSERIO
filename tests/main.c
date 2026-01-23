
#include <stdio.h>

#if defined(UNITY_TEST)
#define CSERIO_IMPLEMENTATION
#define SER_TESTING
#endif

#include "../cserio.h"

int main() {

  int major = 0;
  int minor = 0;
  int micro = 0;
  cserio_version_number(&major, &minor, &micro);
  printf("CSERIO Version: %d.%d.%d\n", major, minor, micro);

  uint8_t test_data[] = "LUCAM-RECORDER";
  serfile* test_ser;
  int status = 0;
  ser_open_memory(&test_ser, test_data, 14, &status);
  printf("ser_open_memory STATUS: %d\n", status);

  uint8_t buffer_1[15] = {'\n'};
  ser_get_idx_record(test_ser, buffer_1, 0, &status); 
  printf("ser_get_idx_record STATUS: %d\n", status);
  printf("ser_get_idx_record result: %s\n", buffer_1);

  ser_close_memory(test_ser, &status);
  printf("ser_close_memory STATUS: %d\n", status);
  return 0;
}

