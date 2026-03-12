
#include "suites.h"

#include <check.h>

#include "ser_test_data.h"

#include "../cserio.h"


START_TEST(open_memory_success) {
    serfile* test_ser = NULL;
    int status = 0;

    ser_open_memory(
            &test_ser,
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50),
            READONLY,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);

    ser_close_memory(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);
} END_TEST

START_TEST(open_memory_hdr_only) {
    serfile* test_ser = NULL;
    int status = 0;
    SERHdrStructure test_hdr = {};

    ser_open_memory(
            &test_ser,
            (uint8_t*)&test_hdr,
            sizeof(test_hdr),
            READONLY,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);

    ser_close_memory(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);
} END_TEST

START_TEST(open_memory_no_trailer) {
    serfile* test_ser = NULL;
    int status = 0;

    SERTest3x50Structure test_data = test_data_3x50;
    test_data.hdr.date_time = 0;
    ser_open_memory(
            &test_ser,
            (uint8_t*)&test_data,
            sizeof(test_data) - sizeof(test_data.trlr),
            READONLY,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);

    ser_close_memory(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);

} END_TEST

START_TEST(open_memory_no_trailer_fail) {
    serfile* test_ser = NULL;
    int status = 0;

    SERTest3x50Structure test_data = test_data_3x50;
    test_data.hdr.date_time = 0;
    ser_open_memory(
            &test_ser,
            (uint8_t*)&test_data,
            sizeof(test_data),
            READONLY,
            &status
    );
    ck_assert_int_eq(status, INVALID_STRUCTURE);
    ck_assert_ptr_null(test_ser);

} END_TEST

START_TEST(open_memory_with_trailer_fail) {
    serfile* test_ser = NULL;
    int status = 0;

    SERTest3x50Structure test_data = test_data_3x50;
    ser_open_memory(
            &test_ser,
            (uint8_t*)&test_data,
            sizeof(test_data) - sizeof(test_data.trlr),
            READONLY,
            &status
    );
    ck_assert_int_eq(status, INVALID_STRUCTURE);
    ck_assert_ptr_null(test_ser);

} END_TEST

START_TEST(open_memory_short_trailer) {
    serfile* test_ser = NULL;
    int status = 0;

    /* Trailer only 1 byte long (does not match hdr metadata) */
    ser_open_memory(
            &test_ser,
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50) - sizeof(test_data_3x50.trlr) + 1,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, INVALID_STRUCTURE);
    ck_assert_ptr_null(test_ser);
} END_TEST;

START_TEST(open_memory_short_data_section) {
    serfile* test_ser = NULL;
    int status = 0;

    /* Data section short by 1 */
    ser_open_memory(
            &test_ser,
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50) - sizeof(test_data_3x50.trlr) - 1,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, INVALID_STRUCTURE);
    ck_assert_ptr_null(test_ser);
} END_TEST

START_TEST(open_memory_short_header) {
    serfile* test_ser = NULL;
    int status = 0;

    /* full header not present */
    ser_open_memory(
            &test_ser,
            (uint8_t*)&test_data_3x50,
            HDR_SIZE - 1, 
            READONLY,
            &status
    );
    ck_assert_int_eq(status, INVALID_STRUCTURE);
    ck_assert_ptr_null(test_ser);
} END_TEST

START_TEST(open_memory_ser_occupied) {
    int status = 0;

    int ptr_provide = 0;
    serfile* test_ser = (serfile*)&ptr_provide;
    ser_open_memory(
            &test_ser,
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50),
            READONLY,
            &status
    );
    ck_assert_int_eq(status, SPTR_OCCUPIED);
} END_TEST

START_TEST(open_memory_null_ser) {
    int status = 0;

    ser_open_memory(
            NULL,
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50),
            READONLY,
            &status
    );
    ck_assert_int_eq(status, NULL_SPTRPTR);
} END_TEST

START_TEST(open_memory_null_data) {
    serfile* test_ser = NULL;
    int status = 0;

    ser_open_memory(
            &test_ser,
            NULL,
            sizeof(test_data_3x50),
            READONLY,
            &status
    );
    ck_assert_int_eq(status, NULL_PARAM);
    ck_assert_ptr_null(test_ser);
} END_TEST

Suite* open_memory_suite() {
    Suite* s;
    s = suite_create("Open Memory");

    TCase* tc_open_memory = tcase_create("open_memory");
    tcase_add_test(tc_open_memory, open_memory_success);
    tcase_add_test(tc_open_memory, open_memory_hdr_only);
    tcase_add_test(tc_open_memory, open_memory_no_trailer);
    tcase_add_test(tc_open_memory, open_memory_no_trailer_fail);
    tcase_add_test(tc_open_memory, open_memory_with_trailer_fail);
    tcase_add_test(tc_open_memory, open_memory_short_trailer);
    tcase_add_test(tc_open_memory, open_memory_short_data_section);
    tcase_add_test(tc_open_memory, open_memory_short_header);
    tcase_add_test(tc_open_memory, open_memory_ser_occupied);
    tcase_add_test(tc_open_memory, open_memory_null_ser);
    tcase_add_test(tc_open_memory, open_memory_null_data);
    suite_add_tcase(s, tc_open_memory);

    return s;
}


