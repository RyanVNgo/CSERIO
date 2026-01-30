
#include <check.h>

#include "ser_test_data.h"

#include "../cserio.h"

START_TEST(version_check) {
    int major, minor, micro;
    cserio_version_number(&major, &minor, &micro);

    ck_assert_int_eq(major, CSERIO_MAJOR);
    ck_assert_int_eq(minor, CSERIO_MINOR);
    ck_assert_int_eq(micro, CSERIO_MICRO);
} END_TEST

START_TEST(open_memory) {
    serfile* test_ser;
    int status = 0;
    ser_open_memory(&test_ser, (uint8_t*)&readonly_test_data, sizeof(readonly_test_data), READWRITE, &status);
    ck_assert_int_eq(status, NO_ERROR);

    ser_close_memory(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);
} END_TEST

Suite* core_suite() {
    Suite* s;
    s = suite_create("Core");

    TCase* tc_version_check = tcase_create("version_check");
    tcase_add_test(tc_version_check, version_check);

    TCase* tc_open_data = tcase_create("open_data");
    tcase_add_test(tc_open_data, open_memory);

    suite_add_tcase(s, tc_version_check);
    suite_add_tcase(s, tc_open_data);

    return s;
}

