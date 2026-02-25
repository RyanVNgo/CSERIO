
#include "suites.h"

#include <check.h>

#include "ser_test_data.h"

#include "../cserio.h"


void image_write_setup() {
    int status = 0;
    memset(test_data_3x50.data, 0, sizeof(test_data_3x50.data));
    ser_open_view(
            &test_ser_3x50,
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50),
            READWRITE,
            &status
    );
}

void image_write_teardown() {
    int status = 0;
    memset(test_data_3x50.data, 0, sizeof(test_data_3x50.data));
    ser_close_memory(test_ser_3x50, &status);
}

/*
START_TEST(write_frame_success) {
    int status = 0;

    size_t width = test_data_3x50.hdr.image_width;
    size_t height = test_data_3x50.hdr.image_height;
    size_t frame_size = width * height;

    uint8_t buffer[50 * 50] = {0};
    for (size_t i = 0; i < test_data_3x50.hdr.frame_count; i++) {
        switch (i) {
            case 0:
                set_pattern_A(buffer, frame_size);
                break;
            case 1:
                set_pattern_B(buffer, frame_size);
                break;
            default:
                set_pattern_C(buffer, frame_size);
        }

        ser_write_frame(
                test_ser_3x50,
                buffer,
                i,
                &status
        );
        ck_assert_int_eq(status, NO_ERROR);

        for (size_t j = 0; j < frame_size; j++) {
            ck_assert_int_eq(buffer[j], test_data_3x50.data[j + i * frame_size]);
        }
    }

} END_TEST

START_TEST(write_frame_oob_idx) {
    int status = 0;

    size_t width = test_data_3x50.hdr.image_width;
    size_t height = test_data_3x50.hdr.image_height;
    size_t frame_size = width * height;

    uint8_t buffer[50 * 50] = {0};
    set_pattern_A(buffer, frame_size);

    status = 0;
    ser_write_frame(
            test_ser_3x50,
            buffer,
            -1,
            &status
    );
    ck_assert_int_ne(status, NO_ERROR);
    for (size_t i = 0; i < sizeof(test_data_3x50.data); i++) {
        ck_assert_int_eq(test_data_3x50.data[i], 0);
    }

    status = 0;
    ser_write_frame(
            test_ser_3x50,
            buffer,
            test_data_3x50.hdr.frame_count,
            &status
    );
    ck_assert_int_ne(status, NO_ERROR);
    for (size_t i = 0; i < sizeof(test_data_3x50.data); i++) {
        ck_assert_int_eq(test_data_3x50.data[i], 0);
    }

} END_TEST

START_TEST(write_frame_null_data) {
    int status = 0;

    ser_write_frame(
            test_ser_3x50,
            NULL,
            0,
            &status
    );
    ck_assert_int_ne(status, NO_ERROR);
    for (size_t i = 0; i < sizeof(test_data_3x50.data); i++) {
        ck_assert_int_eq(test_data_3x50.data[i], 0);
    }

} END_TEST

START_TEST(write_frame_null_ser) {
    int status = 0;

    uint8_t buffer[50 * 50] = {0};
    ser_write_frame(
            NULL,
            buffer,
            0,
            &status
    );
    ck_assert_int_ne(status, NO_ERROR);

} END_TEST
*/

Suite* image_write_suite() {
    Suite* s;
    s = suite_create("Image Write");

    /*
    TCase* tc_image_write;
    tc_image_write = tcase_create("write_frame");
    tcase_add_checked_fixture(tc_image_write, image_write_setup, image_write_teardown);
    tcase_add_test(tc_image_write, write_frame_success);
    tcase_add_test(tc_image_write, write_frame_oob_idx);
    tcase_add_test(tc_image_write, write_frame_null_data);
    tcase_add_test(tc_image_write, write_frame_null_ser);
    suite_add_tcase(s, tc_image_write);
    */

    return s;
}

