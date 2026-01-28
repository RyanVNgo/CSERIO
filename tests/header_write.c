
#include <check.h>

#include "ser_test_data.h"

#include "../cserio.h"


void header_write_setup() {
  int status;
  ser_open_memory(&test_ser, (uint8_t*)&test_data, sizeof(test_data), &status);
}

void header_write_teardown() {
  int status;
  ser_close_memory(test_ser, &status);
}


Suite* header_write_suite() {
  Suite* s;
  s = suite_create("Header Write");

  TCase* tc_idx_record;
  tc_idx_record = tcase_create("idx_record");
  tcase_add_checked_fixture(tc_idx_record, header_write_setup, header_write_teardown);
  suite_add_tcase(s, tc_idx_record);

  TCase* tc_key_record;
  tc_key_record = tcase_create("key_record");
  tcase_add_checked_fixture(tc_key_record, header_write_setup, header_write_teardown);
  suite_add_tcase(s, tc_key_record);

  return s;
}

