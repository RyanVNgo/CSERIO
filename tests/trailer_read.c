
#include "suites.h"

#include <check.h>

#include "ser_test_data.h"

#include "../cserio.h"


void trailer_read_setup() {
    int status = 0;
    ser_open_memory(
            &test_ser_3x50,
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50),
            true,
            READONLY,
            &status
    );
}

void trailer_read_teardown() {
    int status = 0;
    ser_close_memory(test_ser_3x50, &status);
}

START_TEST(trlr_record_reading_success) {
    int status = 0;
    int64_t check_stamp = 0;

    for (size_t i = 0; i < 3; i++) {
        ser_get_trlr_record(
                test_ser_3x50,
                &check_stamp,
                i,
                &status
        );
        ck_assert_int_eq(status, NO_ERROR);
        ck_assert_int_eq(
                check_stamp,
                test_data_3x50.trlr[i]
        );
    }

} END_TEST

START_TEST(trlr_record_reading_oob_idx) {
    int status = 0;
    int64_t check_stamp = 0;

    /* under bound */
    ser_get_trlr_record(
            test_ser_3x50,
            &check_stamp,
            -1,
            &status
    );
    ck_assert_int_ne(status, NO_ERROR);
    ck_assert_int_eq(check_stamp, 0);

    /* over bound */
    ser_get_trlr_record(
            test_ser_3x50,
            &check_stamp,
            4,
            &status
    );
    ck_assert_int_ne(status, NO_ERROR);
    ck_assert_int_eq(check_stamp, 0);

} END_TEST


START_TEST(trlr_record_reading_null_dest) {
    int status = 0;

    ser_get_trlr_record(
            test_ser_3x50,
            NULL,
            0,
            &status
    );
    ck_assert_int_ne(status, NO_ERROR);

} END_TEST

START_TEST(trlr_record_reading_null_ser) {
    int status = 0;
    int64_t check_stamp = 0;

    ser_get_trlr_record(
            NULL,
            &check_stamp,
            0,
            &status
    );
    ck_assert_int_ne(status, NO_ERROR);
    ck_assert_int_eq(check_stamp, 0);

} END_TEST

Suite* trailer_read_suite() {
    Suite* s;
    s = suite_create("Trailer Read");

    TCase* tc_trlr_record;
    tc_trlr_record = tcase_create("trlr_record");
    tcase_add_checked_fixture(tc_trlr_record, trailer_read_setup, trailer_read_teardown);
    tcase_add_test(tc_trlr_record, trlr_record_reading_success);
    tcase_add_test(tc_trlr_record, trlr_record_reading_oob_idx);
    tcase_add_test(tc_trlr_record, trlr_record_reading_null_dest);
    tcase_add_test(tc_trlr_record, trlr_record_reading_null_ser);
    suite_add_tcase(s, tc_trlr_record);

    return s;
}


