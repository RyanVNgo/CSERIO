
#include <check.h>

#include "ser_test_data.h"

#include "../cserio.h"


void header_read_setup() {
  int status;
  ser_open_memory(&test_ser, (uint8_t*)&test_data, sizeof(test_data), &status);
}

void header_read_teardown() {
  int status;
  ser_close_memory(test_ser, &status);
}

START_TEST(idx_record_reading_success) {
  int status = 0;
  DummySERFile check_ser;

  int key_map[HDR_UNIT_COUNT] = {
    FILEID_KEY              ,
    LUID_KEY                ,
    COLORID_KEY             ,
    LITTLEENDIAN_KEY        ,
    IMAGEWIDTH_KEY          ,
    IMAGEHEIGHT_KEY         ,
    PIXELDEPTHPERPLANE_KEY  ,
    FRAMECOUNT_KEY          ,
    OBSERVER_KEY            , 
    INSTRUMENT_KEY          , 
    TELESCOPE_KEY           , 
    DATETIME_KEY            ,
    DATETIMEUTC_KEY         
  };

  int len_map[HDR_UNIT_COUNT] = {
    FILEID_LEN              ,
    LUID_LEN                ,
    COLORID_LEN             ,
    LITTLEENDIAN_LEN        ,
    IMAGEWIDTH_LEN          ,
    IMAGEHEIGHT_LEN         ,
    PIXELDEPTHPERPLANE_LEN  ,
    FRAMECOUNT_LEN          ,
    OBSERVER_LEN            , 
    INSTRUMENT_LEN          , 
    TELESCOPE_LEN           , 
    DATETIME_LEN            ,
    DATETIMEUTC_LEN         
  };

  for (size_t i = 0; i < HDR_UNIT_COUNT; i++) {
    ser_get_idx_record(test_ser, ((uint8_t*)&check_ser) + key_map[i], i, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ck_assert_mem_eq(
        ((uint8_t*)&test_data) + key_map[i], 
        ((uint8_t*)&check_ser) + key_map[i], 
        len_map[i]
    );
  }

} END_TEST

START_TEST(idx_record_reading_null_ser) {
  int status = 0;
  DummySERFile check_ser;

  int key_map[HDR_UNIT_COUNT] = {
    FILEID_KEY              ,
    LUID_KEY                ,
    COLORID_KEY             ,
    LITTLEENDIAN_KEY        ,
    IMAGEWIDTH_KEY          ,
    IMAGEHEIGHT_KEY         ,
    PIXELDEPTHPERPLANE_KEY  ,
    FRAMECOUNT_KEY          ,
    OBSERVER_KEY            , 
    INSTRUMENT_KEY          , 
    TELESCOPE_KEY           , 
    DATETIME_KEY            ,
    DATETIMEUTC_KEY         
  };

  for (size_t i = 0; i < HDR_UNIT_COUNT; i++) {
    ser_get_idx_record(NULL, ((uint8_t*)&check_ser) + key_map[i], i, &status);
    ck_assert_int_ne(status, NO_ERROR);
  }

} END_TEST

START_TEST(idx_record_reading_null_dest) {
  int status = 0;
  DummySERFile check_ser;

  for (size_t i = 0; i < HDR_UNIT_COUNT; i++) {
    ser_get_idx_record(test_ser, NULL, i, &status);
    ck_assert_int_ne(status, NO_ERROR);
  }

} END_TEST

START_TEST(key_record_reading_success) {
  int status = 0;
  DummySERFile check_ser;

  int key_map[HDR_UNIT_COUNT] = {
    FILEID_KEY              ,
    LUID_KEY                ,
    COLORID_KEY             ,
    LITTLEENDIAN_KEY        ,
    IMAGEWIDTH_KEY          ,
    IMAGEHEIGHT_KEY         ,
    PIXELDEPTHPERPLANE_KEY  ,
    FRAMECOUNT_KEY          ,
    OBSERVER_KEY            , 
    INSTRUMENT_KEY          , 
    TELESCOPE_KEY           , 
    DATETIME_KEY            ,
    DATETIMEUTC_KEY         
  };

  int len_map[HDR_UNIT_COUNT] = {
    FILEID_LEN              ,
    LUID_LEN                ,
    COLORID_LEN             ,
    LITTLEENDIAN_LEN        ,
    IMAGEWIDTH_LEN          ,
    IMAGEHEIGHT_LEN         ,
    PIXELDEPTHPERPLANE_LEN  ,
    FRAMECOUNT_LEN          ,
    OBSERVER_LEN            , 
    INSTRUMENT_LEN          , 
    TELESCOPE_LEN           , 
    DATETIME_LEN            ,
    DATETIMEUTC_LEN         
  };

  for (size_t i = 0; i < HDR_UNIT_COUNT; i++) {
    ser_get_key_record(test_ser, ((uint8_t*)&check_ser) + key_map[i], key_map[i], &status);
    ck_assert_int_eq(status, NO_ERROR);
    ck_assert_mem_eq(
        ((uint8_t*)&test_data) + key_map[i], 
        ((uint8_t*)&check_ser) + key_map[i], 
        len_map[i]
    );
  }

} END_TEST

START_TEST(key_record_reading_null_ser) {
  int status = 0;
  DummySERFile check_ser;

  int key_map[HDR_UNIT_COUNT] = {
    FILEID_KEY              ,
    LUID_KEY                ,
    COLORID_KEY             ,
    LITTLEENDIAN_KEY        ,
    IMAGEWIDTH_KEY          ,
    IMAGEHEIGHT_KEY         ,
    PIXELDEPTHPERPLANE_KEY  ,
    FRAMECOUNT_KEY          ,
    OBSERVER_KEY            , 
    INSTRUMENT_KEY          , 
    TELESCOPE_KEY           , 
    DATETIME_KEY            ,
    DATETIMEUTC_KEY         
  };

  for (size_t i = 0; i < HDR_UNIT_COUNT; i++) {
    ser_get_key_record(NULL, ((uint8_t*)&check_ser) + key_map[i], key_map[i], &status);
    ck_assert_int_ne(status, NO_ERROR);
  }

} END_TEST

START_TEST(key_record_reading_null_dest) {
  int status = 0;
  DummySERFile check_ser;

  int key_map[HDR_UNIT_COUNT] = {
    FILEID_KEY              ,
    LUID_KEY                ,
    COLORID_KEY             ,
    LITTLEENDIAN_KEY        ,
    IMAGEWIDTH_KEY          ,
    IMAGEHEIGHT_KEY         ,
    PIXELDEPTHPERPLANE_KEY  ,
    FRAMECOUNT_KEY          ,
    OBSERVER_KEY            , 
    INSTRUMENT_KEY          , 
    TELESCOPE_KEY           , 
    DATETIME_KEY            ,
    DATETIMEUTC_KEY         
  };

  for (size_t i = 0; i < HDR_UNIT_COUNT; i++) {
    ser_get_key_record(test_ser, NULL, key_map[i], &status);
    ck_assert_int_ne(status, NO_ERROR);
  }

} END_TEST

Suite* header_read_suite() {
  Suite* s;
  s = suite_create("Header Read");

  TCase* tc_idx_record;
  tc_idx_record = tcase_create("idx_record");
  tcase_add_checked_fixture(tc_idx_record, header_read_setup, header_read_teardown);
  tcase_add_test(tc_idx_record, idx_record_reading_success);
  tcase_add_test(tc_idx_record, idx_record_reading_null_ser);
  tcase_add_test(tc_idx_record, idx_record_reading_null_dest);
  suite_add_tcase(s, tc_idx_record);

  TCase* tc_key_record;
  tc_key_record = tcase_create("key_record");
  tcase_add_checked_fixture(tc_key_record, header_read_setup, header_read_teardown);
  tcase_add_test(tc_key_record, key_record_reading_success);
  tcase_add_test(tc_key_record, key_record_reading_null_ser);
  tcase_add_test(tc_key_record, key_record_reading_null_dest);
  suite_add_tcase(s, tc_key_record);

  return s;
}

