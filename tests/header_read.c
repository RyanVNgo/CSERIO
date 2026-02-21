
#include <check.h>
#include <time.h>

#include "ser_test_data.h"

#include "../cserio.h"


void header_read_setup() {
    int status;
    ser_open_memory(
            &test_ser_3x50,
            (uint8_t*)&test_data_3x50,
            sizeof(test_data_3x50),
            READONLY,
            &status
    );
}

void header_read_teardown() {
    int status;
    ser_close_memory(test_ser_3x50, &status);
}

START_TEST(idx_record_reading_success) {
    int status = 0;
    SERHdrStructure check_hdr = {0};

    for (size_t i = 0; i < HDR_UNIT_COUNT; i++) {
        ser_get_idx_record(
                test_ser_3x50,
                ((uint8_t*)&check_hdr) + key_map[i],
                i,
                &status
        );
        ck_assert_int_eq(status, NO_ERROR);
        ck_assert_mem_eq(
                ((uint8_t*)&test_data_3x50) + key_map[i], 
                ((uint8_t*)&check_hdr) + key_map[i], 
                len_map[i]
        );
    }

} END_TEST

START_TEST(idx_record_reading_oob_idx) {
    int status = 0;
    SERHdrStructure check_hdr = {0};
    const SERHdrStructure blank_hdr = {0};

    /* under bound */
    ser_get_idx_record(
            test_ser_3x50,
            ((uint8_t*)&check_hdr),
            -1,
            &status
    );
    ck_assert_int_ne(status, NO_ERROR);
    for (size_t i = 0; i < HDR_UNIT_COUNT; i++) {
        ck_assert_mem_eq(
                ((uint8_t*)&check_hdr) + key_map[i],
                ((uint8_t*)&blank_hdr) + key_map[i],
                len_map[i]
        );
    }

    /* over bound */
    ser_get_idx_record(
            test_ser_3x50,
            ((uint8_t*)&check_hdr),
            HDR_UNIT_COUNT + 1,
            &status
    );
    ck_assert_int_ne(status, NO_ERROR);
    for (size_t i = 0; i < HDR_UNIT_COUNT; i++) {
        ck_assert_mem_eq(
                ((uint8_t*)&check_hdr) + key_map[i],
                ((uint8_t*)&blank_hdr) + key_map[i],
                len_map[i]
        );
    }

} END_TEST

START_TEST(idx_record_reading_null_dest) {
    int status = 0;

    for (size_t i = 0; i < HDR_UNIT_COUNT; i++) {
        ser_get_idx_record(test_ser_3x50, NULL, i, &status);
        ck_assert_int_ne(status, NO_ERROR);
    }

} END_TEST

START_TEST(idx_record_reading_null_ser) {
    int status = 0;
    SERHdrStructure check_hdr = {0};
    const SERHdrStructure blank_hdr = {0};

    for (size_t i = 0; i < HDR_UNIT_COUNT; i++) {
        ser_get_idx_record(
                NULL,
                ((uint8_t*)&check_hdr) + key_map[i],
                i,
                &status
        );
        ck_assert_int_ne(status, NO_ERROR);
    }

    for (size_t i = 0; i < HDR_UNIT_COUNT; i++) {
        ck_assert_mem_eq(
                ((uint8_t*)&check_hdr) + key_map[i],
                ((uint8_t*)&blank_hdr) + key_map[i],
                len_map[i]
        );
    }

} END_TEST

START_TEST(key_record_reading_success) {
    int status = 0;
    SERHdrStructure check_hdr = {0};

    for (size_t i = 0; i < HDR_UNIT_COUNT; i++) {
        ser_get_key_record(
                test_ser_3x50,
                ((uint8_t*)&check_hdr) + key_map[i],
                key_map[i],
                &status
        );

        ck_assert_int_eq(status, NO_ERROR);
        ck_assert_mem_eq(
                ((uint8_t*)&test_data_3x50) + key_map[i], 
                ((uint8_t*)&check_hdr) + key_map[i], 
                len_map[i]
        );
    }

} END_TEST

START_TEST(key_record_reading_invalid_key) {
    int status = 0;
    SERHdrStructure check_hdr = {0};
    const SERHdrStructure blank_hdr = {0};

    int invalid_keys[3] = {-1, 213, FILEID_KEY + 1};
    for (size_t i = 0; i < 3; i++) {
        ser_get_key_record(
                test_ser_3x50, 
                ((uint8_t*)&check_hdr) + key_map[i],
                invalid_keys[i],
                &status
        );

        ck_assert_int_ne(status, NO_ERROR);
        for (size_t j = 0; j < HDR_UNIT_COUNT; j++) {
            ck_assert_mem_eq(
                    ((uint8_t*)&check_hdr) + key_map[j],
                    ((uint8_t*)&blank_hdr) + key_map[j],
                    len_map[j]
            );
        }
    }

} END_TEST

START_TEST(key_record_reading_null_dest) {
    int status = 0;

    for (size_t i = 0; i < HDR_UNIT_COUNT; i++) {
        ser_get_key_record(test_ser_3x50, NULL, key_map[i], &status);
        ck_assert_int_ne(status, NO_ERROR);
    }

} END_TEST

START_TEST(key_record_reading_null_ser) {
    int status = 0;
    SERHdrStructure check_hdr = {0};
    const SERHdrStructure blank_hdr = {0};

    for (size_t i = 0; i < HDR_UNIT_COUNT; i++) {
        ser_get_key_record(
                NULL,
                ((uint8_t*)&check_hdr) + key_map[i],
                key_map[i],
                &status
        );
        ck_assert_int_ne(status, NO_ERROR);
    }

    for (size_t i = 0; i < HDR_UNIT_COUNT; i++) {
        ck_assert_mem_eq(
                ((uint8_t*)&check_hdr) + key_map[i],
                ((uint8_t*)&blank_hdr) + key_map[i],
                len_map[i]
        );
    }

} END_TEST

Suite* header_read_suite() {
    Suite* s;
    s = suite_create("Header Read");

    TCase* tc_idx_record;
    tc_idx_record = tcase_create("idx_record");
    tcase_add_checked_fixture(tc_idx_record, header_read_setup, header_read_teardown);
    tcase_add_test(tc_idx_record, idx_record_reading_success);
    tcase_add_test(tc_idx_record, idx_record_reading_oob_idx);
    tcase_add_test(tc_idx_record, idx_record_reading_null_dest);
    tcase_add_test(tc_idx_record, idx_record_reading_null_ser);
    suite_add_tcase(s, tc_idx_record);

    TCase* tc_key_record;
    tc_key_record = tcase_create("key_record");
    tcase_add_checked_fixture(tc_key_record, header_read_setup, header_read_teardown);
    tcase_add_test(tc_key_record, key_record_reading_success);
    tcase_add_test(tc_key_record, key_record_reading_invalid_key);
    tcase_add_test(tc_key_record, key_record_reading_null_dest);
    tcase_add_test(tc_key_record, key_record_reading_null_ser);
    suite_add_tcase(s, tc_key_record);

    return s;
}

