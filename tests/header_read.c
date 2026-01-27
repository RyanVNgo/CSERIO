
#include <check.h>

#include "ser_test_data.h"

#include "../cserio.h"


void test_data_setup() {
  int status;
  ser_open_memory(&test_ser, (uint8_t*)&test_data, sizeof(test_data), &status);
}

void test_data_teardown() {
  int status;
  ser_close_memory(test_ser, &status);
}

START_TEST(idx_record_fileid_success) {
  int status = 0;
  char fileid_buffer[FILEID_LEN];

  ser_get_idx_record(test_ser, fileid_buffer, 0, &status);
  ck_assert_int_eq(status, NO_ERROR);
  ck_assert_mem_eq(test_data.file_id, fileid_buffer, FILEID_LEN);
} END_TEST

START_TEST(idx_record_fileid_null_ser) {
  int status = 0;
  char fileid_buffer[FILEID_LEN];

  ser_get_idx_record(NULL, fileid_buffer, 0, &status);
  ck_assert_int_ne(status, NO_ERROR);
  ck_assert_int_eq(status, NULL_SPTR);
} END_TEST

START_TEST(idx_record_fileid_null_param) {
  int status = 0;
  char fileid_buffer[FILEID_LEN];

  ser_get_idx_record(test_ser, NULL, 0, &status);
  ck_assert_int_ne(status, NO_ERROR);
  ck_assert_int_eq(status, NULL_DEST_BUFF);
} END_TEST

Suite* header_read_suite() {
  Suite* s;
  s = suite_create("header_read");

  TCase* tc_idx_record_fileid;
  tc_idx_record_fileid = tcase_create("idx_record_fileid");
  tcase_add_checked_fixture(tc_idx_record_fileid, test_data_setup, test_data_teardown);
  tcase_add_test(tc_idx_record_fileid, idx_record_fileid_success);
  tcase_add_test(tc_idx_record_fileid, idx_record_fileid_null_ser);
  tcase_add_test(tc_idx_record_fileid, idx_record_fileid_null_param);

  suite_add_tcase(s, tc_idx_record_fileid);

  return s;
}

