
#include <check.h>

#include "ser_test_data.h"

#include "../cserio.h"


void get_metadata_setup() {
    int status = 0;
    ser_open_view(
            &test_ser_3x50,
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50),
            READONLY,
            &status
    );
}

void get_metadata_teardown() {
    int status = 0;
    ser_close_memory(test_ser_3x50, &status);
}

START_TEST(get_metadata_success) {
    int status = 0;

    SERHdrStructureNonPacked check_hdr;
    memset(&check_hdr, 0, sizeof(check_hdr));

    ser_get_file_id(test_ser_3x50, check_hdr.file_id, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_get_lu_id(test_ser_3x50, &check_hdr.lu_id, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_get_color_id(test_ser_3x50, &check_hdr.color_id, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_get_little_endian(test_ser_3x50, &check_hdr.little_endian, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_get_image_width(test_ser_3x50, &check_hdr.image_width, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_get_image_height(test_ser_3x50, &check_hdr.image_height, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_get_pixel_depth_per_plane(test_ser_3x50, &check_hdr.pixel_depth_per_plane, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_get_frame_count(test_ser_3x50, &check_hdr.frame_count, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_get_observer(test_ser_3x50, check_hdr.observer, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_get_instrument(test_ser_3x50, check_hdr.instrument, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_get_telescope(test_ser_3x50, check_hdr.telescope, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_get_date_time(test_ser_3x50, &check_hdr.date_time, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_get_date_time_utc(test_ser_3x50, &check_hdr.date_time_utc, &status);
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

START_TEST(get_metadata_null_data) {
    int status = 0;

    ser_get_file_id(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_get_lu_id(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_get_color_id(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_get_little_endian(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_get_image_width(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_get_image_height(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_get_pixel_depth_per_plane(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_get_frame_count(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_get_observer(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_get_instrument(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_get_telescope(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_get_date_time(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;
    ser_get_date_time_utc(test_ser_3x50, NULL, &status);
    ck_assert_int_eq(status, NULL_DEST_BUFF); status = 0;

} END_TEST

START_TEST(get_metadata_null_ser) {
    int status = 0;

    SERHdrStructureNonPacked baseline_hdr;
    memset(&baseline_hdr, 0, sizeof(baseline_hdr));
    SERHdrStructureNonPacked check_hdr;
    memset(&check_hdr, 0, sizeof(check_hdr));

    ser_get_file_id(NULL, check_hdr.file_id, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_get_lu_id(NULL, &check_hdr.lu_id, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_get_color_id(NULL, &check_hdr.color_id, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_get_little_endian(NULL, &check_hdr.little_endian, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_get_image_width(NULL, &check_hdr.image_width, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_get_image_height(NULL, &check_hdr.image_height, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_get_pixel_depth_per_plane(NULL, &check_hdr.pixel_depth_per_plane, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_get_frame_count(NULL, &check_hdr.frame_count, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_get_observer(NULL, check_hdr.observer, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_get_instrument(NULL, check_hdr.instrument, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_get_telescope(NULL, check_hdr.telescope, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_get_date_time(NULL, &check_hdr.date_time, &status);
    ck_assert_int_eq(status, NULL_SPTR); status = 0;
    ser_get_date_time_utc(NULL, &check_hdr.date_time_utc, &status);
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

Suite* get_metadata_suite() {
    Suite* s;
    s = suite_create("Get Metadata");

    TCase* tc_get_metadata;
    tc_get_metadata = tcase_create("get_metadata");
    tcase_add_checked_fixture(tc_get_metadata, get_metadata_setup, get_metadata_teardown);
    tcase_add_test(tc_get_metadata, get_metadata_success);
    tcase_add_test(tc_get_metadata, get_metadata_null_data);
    tcase_add_test(tc_get_metadata, get_metadata_null_ser);
    suite_add_tcase(s, tc_get_metadata);

    return s;
}


