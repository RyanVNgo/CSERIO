
#include "suites.h"

#include <check.h>
#include <unistd.h>
#include <sys/stat.h>

#include "../cserio.h"


START_TEST(create_memory_success) {
    int status = 0;
    serfile* test_ser = NULL;

    ser_create_memory(
            &test_ser, 
            true,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);
    ck_assert_int_eq(test_ser->SER_file->has_trailer, true);

    ser_close_memory(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);
} END_TEST

START_TEST(create_memory_null_ser) {
    int status = 0;

    ser_create_memory(
            NULL, 
            true,
            &status
    );
    ck_assert_int_eq(status, NULL_SPTR);

} END_TEST

Suite* create_memory_suite() {
    Suite* s;
    s = suite_create("Create Memory");

    TCase* tc_create_memory = tcase_create("create_memory");
    tcase_add_test(tc_create_memory, create_memory_success);
    tcase_add_test(tc_create_memory, create_memory_null_ser);
    suite_add_tcase(s, tc_create_memory);

    return s;
}

