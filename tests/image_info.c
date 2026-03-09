
#include "suites.h"

#include <check.h>

#include "ser_test_data.h"

#include "../cserio.h"


void image_info_setup() {
    int status = 0;
    ser_open_memory(
            &test_ser_3x50,
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50),
            READONLY,
            &status
    );
}

void image_info_teardown() {
    int status = 0;
    ser_close_memory(test_ser_3x50, &status);
}

START_TEST(frame_count_success) {
    int status = 0;
    int frame_count = 0;

    ser_get_frame_count(
            test_ser_3x50,
            &frame_count,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);
    ck_assert_int_eq(
            frame_count,
            test_data_3x50.hdr.frame_count
    );

} END_TEST

START_TEST(frame_count_null_data) {
    int status = 0;

    ser_get_frame_count(
            test_ser_3x50,
            NULL,
            &status
    );
    ck_assert_int_ne(status, NO_ERROR);

} END_TEST

START_TEST(frame_count_null_ser) {
    int status = 0;
    int frame_count = 0;

    ser_get_frame_count(
            NULL,
            &frame_count,
            &status
    );
    ck_assert_int_ne(status, NO_ERROR);
    ck_assert_int_eq(frame_count, 0);

} END_TEST

START_TEST(number_of_planes_success) {
    int status = 0;

    int nop = 0;
    ser_get_number_of_planes(
            test_ser_3x50,
            &nop,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);
    ck_assert_int_eq(nop, test_data_3x50.hdr.color_id < 100 ? 1 : 3);

} END_TEST

START_TEST(number_of_planes_null_data) {
    int status = 0; 

    status = 0;
    ser_get_number_of_planes(
            test_ser_3x50,
            NULL,
            &status
    );
    ck_assert_int_eq(status, NULL_PARAM);

} END_TEST

START_TEST(number_of_planes_null_ser) {
    int status = 0; 

    int nop = 0;
    ser_get_number_of_planes(
            NULL,
            &nop,
            &status
    );
    ck_assert_int_eq(status, NULL_SPTR);
    ck_assert_int_eq(nop, 0);

} END_TEST

START_TEST(bytes_per_pixel_success) {
    int status = 0;
    unsigned long bpp = 0;

    ser_get_bytes_per_pixel(
            test_ser_3x50,
            &bpp,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);
    ck_assert_int_gt(bpp, 0);

} END_TEST

START_TEST(bytes_per_pixel_null_data) {
    int status = 0;

    ser_get_bytes_per_pixel(
            test_ser_3x50,
            NULL,
            &status
    );
    ck_assert_int_ne(status, NO_ERROR);

} END_TEST

START_TEST(bytes_per_pixel_null_ser) {
    int status = 0;
    unsigned long bpp = 0;

    ser_get_bytes_per_pixel(
            NULL,
            &bpp,
            &status
    );
    ck_assert_int_ne(status, NO_ERROR);
    ck_assert_int_eq(bpp, 0);

} END_TEST

START_TEST(frame_byte_size_success) {
    int status = 0;
    unsigned long byte_size = 0;

    ser_get_frame_byte_size(
            test_ser_3x50,
            &byte_size,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);
    ck_assert_int_gt(byte_size, 0);

} END_TEST

START_TEST(frame_byte_size_null_data) {
    int status = 0;

    ser_get_frame_byte_size(
            test_ser_3x50,
            NULL,
            &status
    );
    ck_assert_int_ne(status, NO_ERROR);

} END_TEST

START_TEST(frame_byte_size_null_ser) {
    int status = 0;
    unsigned long byte_size = 0;

    ser_get_frame_byte_size(
            NULL,
            &byte_size,
            &status
    );
    ck_assert_int_ne(status, NO_ERROR);
    ck_assert_int_eq(byte_size, 0);

} END_TEST

Suite* image_info_suite() {
    Suite* s;
    s = suite_create("Image Info");

    TCase* tc_frame_count;
    tc_frame_count = tcase_create("frame_count");
    tcase_add_checked_fixture(tc_frame_count, image_info_setup, image_info_teardown);
    tcase_add_test(tc_frame_count, frame_count_success);
    tcase_add_test(tc_frame_count, frame_count_null_data);
    tcase_add_test(tc_frame_count, frame_count_null_ser);
    suite_add_tcase(s, tc_frame_count);

    TCase* tc_number_of_planes;
    tc_number_of_planes = tcase_create("number_of_planes");
    tcase_add_checked_fixture(tc_number_of_planes, image_info_setup, image_info_teardown);
    tcase_add_test(tc_number_of_planes, number_of_planes_success);
    tcase_add_test(tc_number_of_planes, number_of_planes_null_data);
    tcase_add_test(tc_number_of_planes, number_of_planes_null_ser);
    suite_add_tcase(s, tc_number_of_planes);

    TCase* tc_bytes_per_pixel;
    tc_bytes_per_pixel = tcase_create("bytes_per_pixel");
    tcase_add_checked_fixture(tc_bytes_per_pixel, image_info_setup, image_info_teardown);
    tcase_add_test(tc_bytes_per_pixel, bytes_per_pixel_success);
    tcase_add_test(tc_bytes_per_pixel, bytes_per_pixel_null_data);
    tcase_add_test(tc_bytes_per_pixel, bytes_per_pixel_null_ser);
    suite_add_tcase(s, tc_bytes_per_pixel);

    TCase* tc_frame_byte_size;
    tc_frame_byte_size = tcase_create("frame_byte_size");
    tcase_add_checked_fixture(tc_frame_byte_size, image_info_setup, image_info_teardown);
    tcase_add_test(tc_frame_byte_size, frame_byte_size_success);
    tcase_add_test(tc_frame_byte_size, frame_byte_size_null_data);
    tcase_add_test(tc_frame_byte_size, frame_byte_size_null_ser);
    suite_add_tcase(s, tc_frame_byte_size);

    return s;
}

