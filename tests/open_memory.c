
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
            true,
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

    /* has trailer */
    ser_open_memory(
            &test_ser,
            (uint8_t*)&test_hdr,
            sizeof(test_hdr),
            true,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);
    ck_assert_int_eq(test_ser->SER_file->has_trailer, true);

    ser_close_memory(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);

    /* no trailer */
    ser_open_memory(
            &test_ser,
            (uint8_t*)&test_hdr,
            sizeof(test_hdr),
            false,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);
    ck_assert_int_eq(test_ser->SER_file->has_trailer, false);

    ser_close_memory(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);
} END_TEST

START_TEST(open_memory_no_trailer) {
    serfile* test_ser = NULL;
    int status = 0;

    ser_open_memory(
            &test_ser,
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50) - sizeof(test_data_3x50.trlr),
            true,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);
    ck_assert_int_eq(test_ser->SER_file->has_trailer, false);

    ser_close_memory(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);

} END_TEST

START_TEST(open_memory_invalid_trailer) {
    serfile* test_ser = NULL;
    int status = 0;

    /* Trailer only 1 byte long (does not match hdr metadata) */
    ser_open_memory(
            &test_ser,
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50) - sizeof(test_data_3x50.trlr) + 1,
            false,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, INVALID_TRAILER);
    ck_assert_int_eq(test_ser->SER_file->has_trailer, true);

    status = 0;
    ser_close_memory(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);
} END_TEST;

START_TEST(open_memory_invalid_structure) {
    serfile* test_ser = NULL;
    int status = 0;

    /* Data section short by 1 */
    ser_open_memory(
            &test_ser,
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50) - sizeof(test_data_3x50.trlr) - 1,
            true,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, INVALID_STRUCTURE);

    status = 0;
    ser_close_memory(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);

} END_TEST

START_TEST(open_memory_invalid_file) {
    serfile* test_ser = NULL;
    int status = 0;

    /* full header not present */
    ser_open_memory(
            &test_ser,
            (uint8_t*)&test_data_3x50,
            HDR_SIZE - 1, 
            true,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, INVALID_FILE);

} END_TEST

START_TEST(open_memory_null_ser) {
    int status = 0;

    ser_open_memory(
            NULL,
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50),
            true,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, NULL_SPTR);

} END_TEST

START_TEST(open_memory_null_data) {
    serfile* test_ser;
    int status = 0;

    ser_open_memory(
            &test_ser,
            NULL,
            sizeof(test_data_3x50),
            true,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, NULL_PARAM);

} END_TEST

Suite* open_memory_suite() {
    Suite* s;
    s = suite_create("Open Memory");

    TCase* tc_open_memory = tcase_create("open_memory");
    tcase_add_test(tc_open_memory, open_memory_success);
    tcase_add_test(tc_open_memory, open_memory_hdr_only);
    tcase_add_test(tc_open_memory, open_memory_no_trailer);
    tcase_add_test(tc_open_memory, open_memory_invalid_trailer);
    tcase_add_test(tc_open_memory, open_memory_invalid_structure);
    tcase_add_test(tc_open_memory, open_memory_invalid_file);
    tcase_add_test(tc_open_memory, open_memory_null_ser);
    tcase_add_test(tc_open_memory, open_memory_null_data);
    suite_add_tcase(s, tc_open_memory);

    return s;
}


