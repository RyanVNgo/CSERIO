
#include "suites.h"

#include <check.h>

#include "ser_test_data.h"

#include "../cserio.h"


void trailer_setup() {
    int status = 0;
    ser_open_memory(
            &test_ser_3x50,
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50),
            READONLY,
            &status
    );
}

void trailer_teardown() {
    int status = 0;
    ser_close_memory(test_ser_3x50, &status);
}

START_TEST(enable_trailer_success) {
    SERHdrStructure test_data = {
        .color_id = MONO,
        .image_width = 10,
        .image_height = 10,
        .pixel_depth_per_plane = 8,
        .frame_count = 0
    };

    int status = 0;
    serfile* test_ser = NULL;
    ser_open_view(
            &test_ser, 
            (uint8_t*)&test_data,
            sizeof(test_data),
            READONLY,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);

    ser_enable_trailer(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);

    ser_close_memory(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);
} END_TEST

START_TEST(enable_trailer_invalid_state) {
    int status = 0;
    serfile* test_ser = NULL;
    ser_open_view(
            &test_ser, 
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50.hdr) + sizeof(test_data_3x50.data),
            READONLY,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);

    ser_enable_trailer(test_ser, &status);
    ck_assert_int_eq(status, INVALID_TRAILER_ENABLE);

    status = 0;
    ser_close_memory(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);
} END_TEST

START_TEST(enable_trailer_null_ser) {
    int status = 0;

    ser_enable_trailer(NULL, &status);
    ck_assert_int_eq(status, NULL_SPTR);

} END_TEST

START_TEST(get_timestamp_success) {
    int status = 0;
    int64_t check_stamp = 0;

    for (size_t i = 0; i < 3; i++) {
        ser_get_timestamp(
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

START_TEST(get_timestamp_no_trailer) {
    int status = 0;
    serfile* test_ser = NULL;
    ser_open_view(
            &test_ser, 
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50.hdr) + sizeof(test_data_3x50.data),
            READONLY,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);

    int64_t check_stamp = 0;
    ser_get_timestamp(
            test_ser,
            &check_stamp,
            0,
            &status
    );
    ck_assert_int_eq(status, TRAILER_DNE);
    ck_assert_int_eq(check_stamp, 0);

    status = 0;
    ser_close_memory(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);
} END_TEST

START_TEST(get_timestamp_oob_idx) {
    int status = 0;
    int64_t check_stamp = 0;

    /* under bound */
    status = 0;
    ser_get_timestamp(
            test_ser_3x50,
            &check_stamp,
            -1,
            &status
    );
    ck_assert_int_eq(status, INVALID_TRAILER_IDX);
    ck_assert_int_eq(check_stamp, 0);

    /* over bound */
    status = 0;
    ser_get_timestamp(
            test_ser_3x50,
            &check_stamp,
            4,
            &status
    );
    ck_assert_int_eq(status, INVALID_TRAILER_IDX);
    ck_assert_int_eq(check_stamp, 0);

} END_TEST

START_TEST(get_timestamp_null_dest) {
    int status = 0;

    ser_get_timestamp(
            test_ser_3x50,
            NULL,
            0,
            &status
    );
    ck_assert_int_eq(status, NULL_DEST_BUFF);

} END_TEST

START_TEST(get_timestamp_null_ser) {
    int status = 0;
    int64_t check_stamp = 0;

    ser_get_timestamp(
            NULL,
            &check_stamp,
            0,
            &status
    );
    ck_assert_int_eq(status, NULL_SPTR);
    ck_assert_int_eq(check_stamp, 0);

} END_TEST

Suite* trailer_read_suite() {
    Suite* s;
    s = suite_create("Trailer");

    TCase* tc_enable_trailer;
    tc_enable_trailer = tcase_create("enable_trailer");
    tcase_add_test(tc_enable_trailer, enable_trailer_success);
    tcase_add_test(tc_enable_trailer, enable_trailer_invalid_state);
    tcase_add_test(tc_enable_trailer, enable_trailer_null_ser);
    suite_add_tcase(s, tc_enable_trailer);

    TCase* tc_get_timestamp;
    tc_get_timestamp = tcase_create("get_timestamp");
    tcase_add_checked_fixture(tc_get_timestamp, trailer_setup, trailer_teardown);
    tcase_add_test(tc_get_timestamp, get_timestamp_success);
    tcase_add_test(tc_get_timestamp, get_timestamp_no_trailer);
    tcase_add_test(tc_get_timestamp, get_timestamp_oob_idx);
    tcase_add_test(tc_get_timestamp, get_timestamp_null_dest);
    tcase_add_test(tc_get_timestamp, get_timestamp_null_ser);
    suite_add_tcase(s, tc_get_timestamp);

    return s;
}


