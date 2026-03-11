
#include "suites.h"

#include <check.h>

#include "ser_test_data.h"

#include "../cserio.h"


void header_read_setup() {
    int status = 0;
    ser_open_view(
            &test_ser_3x50,
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50),
            READONLY,
            &status
    );
}

void header_read_teardown() {
    int status = 0;
    ser_close_memory(test_ser_3x50, &status);
}

START_TEST(header_read_success) {
    int status = 0;

    SERHdrStructureNonPacked check_hdr;
    memset(&check_hdr, 0, sizeof(check_hdr));

    ser_read_file_id(test_ser_3x50, check_hdr.file_id, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_read_lu_id(test_ser_3x50, &check_hdr.lu_id, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_read_color_id(test_ser_3x50, &check_hdr.color_id, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_read_little_endian(test_ser_3x50, &check_hdr.little_endian, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_read_image_width(test_ser_3x50, &check_hdr.image_width, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_read_image_height(test_ser_3x50, &check_hdr.image_height, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_read_pixel_depth_per_plane(test_ser_3x50, &check_hdr.pixel_depth_per_plane, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_read_frame_count(test_ser_3x50, &check_hdr.frame_count, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_read_observer(test_ser_3x50, check_hdr.observer, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_read_instrument(test_ser_3x50, check_hdr.instrument, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_read_telescope(test_ser_3x50, check_hdr.telescope, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_read_date_time(test_ser_3x50, &check_hdr.date_time, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_read_date_time_utc(test_ser_3x50, &check_hdr.date_time_utc, &status);
    ck_assert_int_eq(status, NO_ERROR);

    ck_assert_mem_eq(test_data_3x50.hdr.file_id, check_hdr.file_id, FILEID_LEN);
    ck_assert_int_eq(test_data_3x50.hdr.lu_id, check_hdr.lu_id);
    ck_assert_int_eq(test_data_3x50.hdr.color_id, check_hdr.color_id);
    ck_assert_int_eq(test_data_3x50.hdr.little_endian, check_hdr.little_endian);
    ck_assert_int_eq(test_data_3x50.hdr.image_width, check_hdr.image_width);
    ck_assert_int_eq(test_data_3x50.hdr.image_height, check_hdr.image_height);
    ck_assert_int_eq(test_data_3x50.hdr.pixel_depth_per_plane, check_hdr.pixel_depth_per_plane);
    ck_assert_int_eq(test_data_3x50.hdr.frame_count, check_hdr.frame_count);
    ck_assert_mem_eq(test_data_3x50.hdr.observer, check_hdr.observer, OBSERVER_LEN);
    ck_assert_mem_eq(test_data_3x50.hdr.instrument, check_hdr.instrument, INSTRUMENT_LEN); 
    ck_assert_mem_eq(test_data_3x50.hdr.telescope, check_hdr.telescope, TELESCOPE_LEN);
    ck_assert_int_eq(test_data_3x50.hdr.date_time, check_hdr.date_time);
    ck_assert_int_eq(test_data_3x50.hdr.date_time_utc, check_hdr.date_time_utc);

} END_TEST

START_TEST(header_read_null_data) {
    int status = 0;

    ser_read_file_id(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_read_lu_id(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_read_color_id(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_read_little_endian(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_read_image_width(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_read_image_height(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_read_pixel_depth_per_plane(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_read_frame_count(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_read_observer(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_read_instrument(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_read_telescope(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_read_date_time(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_read_date_time_utc(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;

} END_TEST

START_TEST(header_read_null_ser) {
    int status = 0;

    SERHdrStructureNonPacked baseline_hdr;
    memset(&baseline_hdr, 0, sizeof(baseline_hdr));
    SERHdrStructureNonPacked check_hdr;
    memset(&check_hdr, 0, sizeof(check_hdr));

    ser_read_file_id(NULL, check_hdr.file_id, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_read_lu_id(NULL, &check_hdr.lu_id, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_read_color_id(NULL, &check_hdr.color_id, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_read_little_endian(NULL, &check_hdr.little_endian, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_read_image_width(NULL, &check_hdr.image_width, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_read_image_height(NULL, &check_hdr.image_height, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_read_pixel_depth_per_plane(NULL, &check_hdr.pixel_depth_per_plane, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_read_frame_count(NULL, &check_hdr.frame_count, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_read_observer(NULL, check_hdr.observer, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_read_instrument(NULL, check_hdr.instrument, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_read_telescope(NULL, check_hdr.telescope, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_read_date_time(NULL, &check_hdr.date_time, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_read_date_time_utc(NULL, &check_hdr.date_time_utc, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;

    ck_assert_mem_eq(baseline_hdr.file_id, check_hdr.file_id, FILEID_LEN);
    ck_assert_int_eq(baseline_hdr.lu_id, check_hdr.lu_id);
    ck_assert_int_eq(baseline_hdr.color_id, check_hdr.color_id);
    ck_assert_int_eq(baseline_hdr.little_endian, check_hdr.little_endian);
    ck_assert_int_eq(baseline_hdr.image_width, check_hdr.image_width);
    ck_assert_int_eq(baseline_hdr.image_height, check_hdr.image_height);
    ck_assert_int_eq(baseline_hdr.pixel_depth_per_plane, check_hdr.pixel_depth_per_plane);
    ck_assert_int_eq(baseline_hdr.frame_count, check_hdr.frame_count);
    ck_assert_mem_eq(baseline_hdr.observer, check_hdr.observer, OBSERVER_LEN);
    ck_assert_mem_eq(baseline_hdr.instrument, check_hdr.instrument, INSTRUMENT_LEN); 
    ck_assert_mem_eq(baseline_hdr.telescope, check_hdr.telescope, TELESCOPE_LEN);
    ck_assert_int_eq(baseline_hdr.date_time, check_hdr.date_time);
    ck_assert_int_eq(baseline_hdr.date_time_utc, check_hdr.date_time_utc);

} END_TEST

Suite* header_read_suite() {
    Suite* s;
    s = suite_create("Header Read");

    TCase* tc_header_read;
    tc_header_read = tcase_create("header_read");
    tcase_add_checked_fixture(tc_header_read, header_read_setup, header_read_teardown);
    tcase_add_test(tc_header_read, header_read_success);
    tcase_add_test(tc_header_read, header_read_null_data);
    tcase_add_test(tc_header_read, header_read_null_ser);
    suite_add_tcase(s, tc_header_read);

    return s;
}


