
#include "suites.h"

#include <check.h>
#include <unistd.h>
#include <sys/stat.h>

#include "../cserio.h"


START_TEST(create_file_success) {
    char dir[] = "/tmp/cserio_testXXXXXX";
    if (!mkdtemp(dir)) {
        ck_abort_msg("Failed to make temp directory");
    }

    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s/cserio_test_file.ser", dir);

    serfile* test_ser = NULL;
    int status = 0;
    ser_create_file(
            &test_ser,
            filepath,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);

    struct stat st;
    if (stat(filepath, &st) != 0) {
        ck_abort_msg("File not created");
    }

    ser_close_file(test_ser, &status);

    unlink(filepath);
    rmdir(dir);
} END_TEST;

START_TEST(create_file_already_exists) {
    char dir[] = "/tmp/cserio_testXXXXXX";
    if (!mkdtemp(dir)) {
        ck_abort_msg("Failed to make temp directory");
    }

    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s/cserio_test_file.ser", dir);

    /* create first file */
    serfile* test_ser_1 = NULL;
    int status = 0;
    ser_create_file(
            &test_ser_1,
            filepath,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);

    struct stat st;
    if (stat(filepath, &st) != 0) {
        ck_abort_msg("Base file not created");
    }

    /* attempt to create second with same path, should fail */
    serfile* test_ser_2 = NULL;
    status = 0;
    ser_create_file(
            &test_ser_2,
            filepath,
            &status
    );
    ck_assert_int_eq(status, FILE_EXISTS);

    ser_close_file(test_ser_1, &status);

    unlink(filepath);
    rmdir(dir);
} END_TEST

START_TEST(create_file_null_path) {
    serfile* test_ser = NULL;
    int status = 0;

    ser_create_file(
            &test_ser,
            NULL,
            &status
    );
    ck_assert_int_eq(status, NULL_PATH);

    ser_close_file(test_ser, &status);
} END_TEST

START_TEST(create_file_null_ser) {
    char dir[] = "/tmp/cserio_testXXXXXX";
    if (!mkdtemp(dir)) {
        ck_abort_msg("Failed to make temp directory");
    }

    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s/cserio_test_file.ser", dir);

    int status = 0;
    ser_create_file(
            NULL,
            filepath,
            &status
    );
    ck_assert_int_eq(status, NULL_SPTRPTR);

    struct stat st;
    if (stat(filepath, &st) == 0) {
        ck_abort_msg("File was created");
    }

    unlink(filepath);
    rmdir(dir);
} END_TEST

Suite* create_file_suite() {
    Suite* s;
    s = suite_create("Create file");

    TCase* tc_create_file = tcase_create("create_file");
    tcase_add_test(tc_create_file, create_file_success);
    tcase_add_test(tc_create_file, create_file_already_exists);
    tcase_add_test(tc_create_file, create_file_null_path);
    tcase_add_test(tc_create_file, create_file_null_ser);
    suite_add_tcase(s, tc_create_file);

    return s;
}

