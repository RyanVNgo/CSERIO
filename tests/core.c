
#include <check.h>

#include "../cserio.h"


START_TEST(version_check) {
    int major, minor, micro;
    cserio_version_number(&major, &minor, &micro);

    ck_assert_int_eq(major, CSERIO_MAJOR);
    ck_assert_int_eq(minor, CSERIO_MINOR);
    ck_assert_int_eq(micro, CSERIO_MICRO);

} END_TEST

Suite* core_suite() {
    Suite* s;
    s = suite_create("Core");

    TCase* tc_version_check = tcase_create("version_check");
    tcase_add_test(tc_version_check, version_check);
    suite_add_tcase(s, tc_version_check);

    return s;
}

