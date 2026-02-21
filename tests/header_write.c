
#include <check.h>

#include "ser_test_data.h"

#include "../cserio.h"


START_TEST(idx_record_write) {
    serfile* s;
    SERHdrStructure check_hdr = {0};

    int status = 0;
    ser_open_memory(
            &s,
            (uint8_t*)&check_hdr,
            sizeof(check_hdr),
            READWRITE,
            &status
    );

    for (size_t i = 0 ; i < HDR_UNIT_COUNT; i++) {
        ser_write_idx_record(
                s, 
                ((uint8_t*)&test_data_3x50) + key_map[i],
                i,
                len_map[i],
                &status
        );
        ck_assert_int_eq(status, NO_ERROR);
        ck_assert_mem_eq(
                ((uint8_t*)&check_hdr) + key_map[i],
                ((uint8_t*)&test_data_3x50) + key_map[i],
                len_map[i]
        );
    }

    ser_close_memory(s, &status);
} END_TEST

START_TEST(idx_record_write_oob_idx) {
    serfile* s;
    SERHdrStructure check_hdr = {0};
    const SERHdrStructure blank_hdr = {0};

    int status = 0;
    ser_open_memory(
            &s,
            (uint8_t*)&check_hdr,
            sizeof(check_hdr),
            READWRITE,
            &status
    );

    /* under bound */
    ser_write_idx_record(
            s, 
            ((uint8_t*)&test_data_3x50) + key_map[0],
            -1,
            len_map[0],
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

    /* over bound */
    ser_write_idx_record(
            s, 
            ((uint8_t*)&test_data_3x50) + key_map[0],
            HDR_UNIT_COUNT + 1,
            len_map[0],
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

    ser_close_memory(s, &status);
} END_TEST

START_TEST(idx_record_write_null_data) {
    serfile* s;
    SERHdrStructure check_hdr = {0};
    const SERHdrStructure blank_hdr = {0};

    int status = 0;
    ser_open_memory(
            &s,
            (uint8_t*)&check_hdr,
            sizeof(check_hdr),
            READWRITE,
            &status
    );

    for (size_t i = 0 ; i < HDR_UNIT_COUNT; i++) {
        ser_write_idx_record(
                s,
                NULL,
                i,
                len_map[i],
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

    ser_close_memory(s, &status);
} END_TEST

START_TEST(idx_record_write_null_ser) {
    int status = 0;

    for (size_t i = 0 ; i < HDR_UNIT_COUNT; i++) {
        ser_write_idx_record(
                NULL, 
                ((uint8_t*)&test_data_3x50) + key_map[i],
                i,
                len_map[i],
                &status
        );
        ck_assert_int_ne(status, NO_ERROR);
    }

} END_TEST

START_TEST(key_record_write) {
    serfile* s;
    SERHdrStructure check_hdr = {0};

    int status = 0;
    ser_open_memory(
            &s,
            (uint8_t*)&check_hdr,
            sizeof(check_hdr),
            READWRITE,
            &status
    );

    for (size_t i = 0 ; i < HDR_UNIT_COUNT; i++) {
        ser_write_key_record(
                s, 
                ((uint8_t*)&test_data_3x50) + key_map[i],
                key_map[i],
                len_map[i],
                &status
        );
        ck_assert_int_eq(status, NO_ERROR);
        ck_assert_mem_eq(
                ((uint8_t*)&check_hdr) + key_map[i],
                ((uint8_t*)&test_data_3x50) + key_map[i],
                len_map[i]
        );
    }

    ser_close_memory(s, &status);
} END_TEST

START_TEST(key_record_write_invalid_key) {
    serfile* s;
    SERHdrStructure check_hdr = {0};
    const SERHdrStructure blank_hdr = {0};

    int status = 0;
    ser_open_memory(
            &s,
            (uint8_t*)&check_hdr,
            sizeof(check_hdr),
            READWRITE,
            &status
    );

    int invalid_keys[3] = {-1, 213, FILEID_KEY + 1};
    for (size_t i = 0; i < 3; i++) {
        ser_write_key_record(
                s, 
                ((uint8_t*)&test_data_3x50) + key_map[0],
                invalid_keys[i],
                len_map[0],
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

    ser_close_memory(s, &status);
} END_TEST

START_TEST(key_record_write_null_data) {
    serfile* s;
    SERHdrStructure check_hdr = {0};
    const SERHdrStructure blank_hdr = {0};

    int status = 0;
    ser_open_memory(
            &s,
            (uint8_t*)&check_hdr,
            sizeof(check_hdr),
            READWRITE,
            &status
    );

    for (size_t i = 0 ; i < HDR_UNIT_COUNT; i++) {
        ser_write_key_record(
                s,
                NULL,
                key_map[i],
                len_map[i],
                &status
        );
        ck_assert_int_ne(status, NO_ERROR);
        ck_assert_mem_eq(
                ((uint8_t*)&check_hdr) + key_map[i],
                ((uint8_t*)&blank_hdr) + key_map[i],
                len_map[i]
        );
    }

    ser_close_memory(s, &status);
} END_TEST

START_TEST(key_record_write_null_ser) {
    int status = 0;

    for (size_t i = 0 ; i < HDR_UNIT_COUNT; i++) {
        ser_write_key_record(
                NULL, 
                ((uint8_t*)&test_data_3x50) + key_map[i],
                key_map[i],
                len_map[i],
                &status
        );
        ck_assert_int_ne(status, NO_ERROR);
    }

} END_TEST

Suite* header_write_suite() {
    Suite* s;
    s = suite_create("Header Write");

    TCase* tc_idx_record;
    tc_idx_record = tcase_create("idx_record");
    tcase_add_test(tc_idx_record, idx_record_write);
    tcase_add_test(tc_idx_record, idx_record_write_oob_idx);
    tcase_add_test(tc_idx_record, idx_record_write_null_data);
    tcase_add_test(tc_idx_record, idx_record_write_null_ser);
    suite_add_tcase(s, tc_idx_record);

    TCase* tc_key_record;
    tc_key_record = tcase_create("idx_record");
    tcase_add_test(tc_key_record, key_record_write);
    tcase_add_test(tc_key_record, key_record_write_invalid_key);
    tcase_add_test(tc_key_record, key_record_write_null_data);
    tcase_add_test(tc_key_record, key_record_write_null_ser);
    suite_add_tcase(s, tc_key_record);

    return s;
}

