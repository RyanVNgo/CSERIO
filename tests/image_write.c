
#include "suites.h"

#include <check.h>

#include "ser_test_data.h"

#include "../cserio.h"


START_TEST(append_frame_success_empty_no_trailer) {
    /* setup test ser and arena */
    SERHdrStructure test_hdr = {
        .color_id = MONO,
        .image_width = 10,
        .image_height = 10,
        .pixel_depth_per_plane = 8,
        .frame_count = 0
    };
    size_t ser_arena_size = 1024;
    uint8_t* ser_arena = malloc(ser_arena_size);
    memset(ser_arena, 0, ser_arena_size);
    memcpy(ser_arena, &test_hdr, sizeof(test_hdr));

    int status = 0;
    serfile* test_ser = NULL;
    ser_open_view(
            &test_ser,
            ser_arena,
            ser_arena_size,
            false,
            READWRITE,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);

    /* TEST */
    uint8_t test_data[10 * 10] = {0};
    memset(test_data, 0xA0, sizeof(test_data));
    ser_append_frame(
            test_ser,
            test_data,
            TEST_TIMESTAMP_VALUE,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);
    ser_close_memory(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);

    /* was data written as desired location */
    ck_assert_mem_eq(
            test_data,
            ser_arena + HDR_SIZE,
            sizeof(test_data)
    );

    /* is data before frame (hdr) intact */
    ck_assert_mem_eq(
            &test_hdr,
            ser_arena,
            sizeof(test_hdr)
    );

    /* is data after frame intact */
    uint8_t empty_buff[32] = {0};
    memset(empty_buff, 0, sizeof(empty_buff));
    ck_assert_mem_eq(
            empty_buff, 
            ser_arena + HDR_SIZE + sizeof(test_data),
            sizeof(empty_buff)
    );

    free(ser_arena);
} END_TEST

START_TEST(append_frame_success_empty_with_trailer) {
    /* setup test ser and arena */
    SERHdrStructure test_hdr = {
        .color_id = MONO,
        .image_width = 10,
        .image_height = 10,
        .pixel_depth_per_plane = 8,
        .frame_count = 0
    };
    size_t ser_arena_size = 1024;
    uint8_t* ser_arena = malloc(ser_arena_size);
    memset(ser_arena, 0, ser_arena_size);
    memcpy(ser_arena, &test_hdr, sizeof(test_hdr));

    int status = 0;
    serfile* test_ser = NULL;
    ser_open_view(
            &test_ser,
            ser_arena,
            ser_arena_size,
            true,
            READWRITE,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);

    /* TEST */
    uint8_t test_data[10 * 10] = {0};
    memset(test_data, 0xA0, sizeof(test_data));
    ser_append_frame(
            test_ser,
            test_data,
            TEST_TIMESTAMP_VALUE,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);
    ser_close_memory(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);

    /* was data written as desired location */
    ck_assert_mem_eq(
            test_data,
            ser_arena + HDR_SIZE,
            sizeof(test_data)
    );

    /* is data before frame (hdr) intact */
    ck_assert_mem_eq(
            &test_hdr,
            ser_arena,
            sizeof(test_hdr)
    );

    /* does data after frame have trailer (after close) */
    int64_t expect_trailer[1] = {TEST_TIMESTAMP_VALUE};
    ck_assert_mem_eq(
            expect_trailer, 
            ser_arena + HDR_SIZE + sizeof(test_data),
            sizeof(expect_trailer)
    );

    free(ser_arena);
} END_TEST

START_TEST(append_frame_null_data) {
    /* setup test ser and arena */
    SERHdrStructure test_hdr = {
        .color_id = MONO,
        .image_width = 10,
        .image_height = 10,
        .pixel_depth_per_plane = 8,
        .frame_count = 0
    };
    size_t ser_arena_size = 1024;
    uint8_t* ser_arena = malloc(ser_arena_size);
    memset(ser_arena, 0, ser_arena_size);
    memcpy(ser_arena, &test_hdr, sizeof(test_hdr));

    int status = 0;
    serfile* test_ser = NULL;
    ser_open_view(
            &test_ser,
            ser_arena,
            ser_arena_size,
            true,
            READWRITE,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);

    /* TEST */
    ser_append_frame(
            test_ser,
            NULL,
            TEST_TIMESTAMP_VALUE,
            &status
    );
    ck_assert_int_eq(status, NULL_PARAM);
    status = 0;
    ser_close_memory(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);

    /* was no data written as expected location */
    uint8_t test_data[10 * 10] = {0};
    memset(test_data, 0, sizeof(test_data));
    ck_assert_mem_eq(
            test_data,
            ser_arena + HDR_SIZE,
            sizeof(test_data)
    );

    /* is data before frame (hdr) intact */
    ck_assert_mem_eq(
            &test_hdr,
            ser_arena,
            sizeof(test_hdr)
    );

    /* does data after frame have no trailer (after close) */
    int64_t expect_trailer[1] = {0};
    ck_assert_mem_eq(
            expect_trailer, 
            ser_arena + HDR_SIZE + sizeof(test_data),
            sizeof(expect_trailer)
    );

    free(ser_arena);
} END_TEST

START_TEST(append_frame_null_ser) {
    int status = 0;

    uint8_t test_data[10 * 10] = {0};
    memset(test_data, 0xA0, sizeof(test_data));
    ser_append_frame(
            NULL,
            &test_data,
            TEST_TIMESTAMP_VALUE,
            &status
    );
    ck_assert_int_eq(status, NULL_SPTR);

} END_TEST

Suite* image_write_suite() {
    Suite* s;
    s = suite_create("Image Write");

    TCase* tc_append_frame;
    tc_append_frame = tcase_create("append_frame");
    tcase_add_test(tc_append_frame, append_frame_success_empty_no_trailer);
    tcase_add_test(tc_append_frame, append_frame_success_empty_with_trailer);
    tcase_add_test(tc_append_frame, append_frame_null_data);
    tcase_add_test(tc_append_frame, append_frame_null_ser);
    suite_add_tcase(s, tc_append_frame);

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

