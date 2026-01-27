
#include <check.h>

#if defined(UNITY_TEST)
#define CSERIO_IMPLEMENTATION
#define SER_TESTING
#endif

#include "../cserio.h"

#include "header_read.c"

START_TEST(version_check) {
  int major, minor, micro;
  cserio_version_number(&major, &minor, &micro);

  ck_assert_int_eq(major, CSERIO_MAJOR);
  ck_assert_int_eq(minor, CSERIO_MINOR);
  ck_assert_int_eq(micro, CSERIO_MICRO);

} END_TEST

START_TEST(open_memory) {
  serfile* test_ser;
  int status = 0;
  ser_open_memory(&test_ser, (uint8_t*)&test_data, sizeof(test_data), &status);
  ck_assert_int_eq(status, NO_ERROR);

  ser_close_memory(test_ser, &status);
  ck_assert_int_eq(status, NO_ERROR);
} END_TEST

Suite* core_suite() {
  Suite* s;
  s = suite_create("Core Suite");

  TCase* tc_version_check = tcase_create("version_check");
  tcase_add_test(tc_version_check, version_check);

  TCase* tc_open_data = tcase_create("open_data");
  tcase_add_test(tc_open_data, open_memory);

  suite_add_tcase(s, tc_version_check);
  suite_add_tcase(s, tc_open_data);

  return s;
}

int main() {
  int number_failed = 0;

  Suite* core_s; 
  core_s = core_suite();
  SRunner* core_sr = srunner_create(core_s);
  srunner_run_all(core_sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(core_sr);
  srunner_free(core_sr);

  Suite* hdr_read_s; 
  hdr_read_s = header_read_suite();
  SRunner* hdr_read_sr = srunner_create(hdr_read_s);
  srunner_run_all(hdr_read_sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(hdr_read_sr);
  srunner_free(hdr_read_sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

