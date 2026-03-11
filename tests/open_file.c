
#include "suites.h"

#include <check.h>
#include <unistd.h>
#include <sys/stat.h>

#include "ser_test_data.h"

#include "../cserio.h"


static void create_temp_ser(char* filepath, char* dir, void* data, size_t size) {
    if (!mkdtemp(dir)) {
        ck_abort_msg("Failed to make temp directory");
    }
    snprintf(filepath, 512, "%s/cserio_test_file.ser", dir);

    FILE* file = fopen(filepath, "w+b");
    if (!file) {
        ck_abort_msg("Test Init Failure: Failed to make test file");
    }

    struct stat st;
    if (stat(filepath, &st) != 0) {
        ck_abort_msg("File not created");
    }

    fwrite(data, 1, size, file);
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    ck_assert_int_eq(file_size, size);

    fclose(file);
    return;
}

static void destroy_temp_ser(char* filepath, char* dir) {
    unlink(filepath);
    rmdir(dir);
}

START_TEST(open_file_success) {
    char dir[] = "/tmp/cserio_testXXXXXX";
    char filepath[512];
    create_temp_ser(filepath, dir, &test_data_3x50, sizeof(test_data_3x50));
    /* <- Setup */
    
    int status = 0;
    serfile* test_ser = NULL;
    ser_open_file(
            &test_ser,
            filepath,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);

    status = 0;
    ser_close_file(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);

    /* Teardown -> */
    destroy_temp_ser(filepath, dir);
} END_TEST

START_TEST(open_file_no_trailer) {
    char dir[] = "/tmp/cserio_testXXXXXX";
    char filepath[512];
    SERTest3x50Structure test_data = test_data_3x50;
    test_data.hdr.date_time = 0; /* disable trailer */
    create_temp_ser(
            filepath,
            dir,
            &test_data,
            sizeof(test_data) - sizeof(test_data.trlr)
    );
    /* <- Setup */
    
    int status = 0;
    serfile* test_ser = NULL;
    ser_open_file(
            &test_ser,
            filepath,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);

    status = 0;
    ser_close_file(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);

    /* Teardown -> */
    destroy_temp_ser(filepath, dir);
} END_TEST

START_TEST(open_file_short_trailer) {
    char dir[] = "/tmp/cserio_testXXXXXX";
    char filepath[512];
    create_temp_ser(
            filepath,
            dir,
            &test_data_3x50,
            sizeof(test_data_3x50) - sizeof(test_data_3x50.trlr) + 1
    );
    /* <- Setup */
    
    int status = 0;
    serfile* test_ser = NULL;
    ser_open_file(
            &test_ser,
            filepath,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, INVALID_STRUCTURE);
    ck_assert_ptr_null(test_ser);

    /* Teardown -> */
    destroy_temp_ser(filepath, dir);
} END_TEST

START_TEST(open_file_short_data_section) {
    char dir[] = "/tmp/cserio_testXXXXXX";
    char filepath[512];
    create_temp_ser(filepath, dir, &test_data_3x50, sizeof(test_data_3x50) - sizeof(test_data_3x50.trlr) - 1);
    /* <- Setup */
    
    int status = 0;
    serfile* test_ser = NULL;
    ser_open_file(
            &test_ser,
            filepath,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, INVALID_STRUCTURE);
    ck_assert_ptr_null(test_ser);

    /* Teardown -> */
    destroy_temp_ser(filepath, dir);
} END_TEST

START_TEST(open_file_short_header) {
    char dir[] = "/tmp/cserio_testXXXXXX";
    char filepath[512];
    create_temp_ser(filepath, dir, &test_data_3x50, HDR_SIZE - 1);
    /* <- Setup */
    
    int status = 0;
    serfile* test_ser = NULL;
    ser_open_file(
            &test_ser,
            filepath,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, INVALID_STRUCTURE);
    ck_assert_ptr_null(test_ser);

    /* Teardown -> */
    destroy_temp_ser(filepath, dir);
} END_TEST

START_TEST(open_file_ser_occupied) {
    char dir[] = "/tmp/cserio_testXXXXXX";
    char filepath[512];
    create_temp_ser(filepath, dir, &test_data_3x50, HDR_SIZE - 1);
    /* <- Setup */
    
    int status = 0;
    int ptr_provide = 0;
    serfile* test_ser = (serfile*)&ptr_provide;
    ser_open_file(
            &test_ser,
            filepath,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, SPTR_OCCUPIED);

    /* Teardown -> */
    destroy_temp_ser(filepath, dir);
}

START_TEST(open_file_null_ser) {
    char dir[] = "/tmp/cserio_testXXXXXX";
    char filepath[512];
    create_temp_ser(filepath, dir, &test_data_3x50, HDR_SIZE - 1);
    /* <- Setup */
    
    int status = 0;
    ser_open_file(
            NULL,
            filepath,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, NULL_SPTRPTR);

    /* Teardown -> */
    destroy_temp_ser(filepath, dir);
} END_TEST

START_TEST(open_file_null_path) {
    char dir[] = "/tmp/cserio_testXXXXXX";
    char filepath[512];
    create_temp_ser(filepath, dir, &test_data_3x50, HDR_SIZE - 1);
    /* <- Setup */
    
    int status = 0;
    serfile* test_ser = NULL;
    ser_open_file(
            &test_ser,
            NULL,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, NULL_PATH);
    ck_assert_ptr_null(test_ser);

    /* Teardown -> */
    destroy_temp_ser(filepath, dir);
} END_TEST

START_TEST(open_file_invalid_path) {
    char dir[] = "/tmp/cserio_testXXXXXX";
    char filepath[512];
    create_temp_ser(filepath, dir, &test_data_3x50, HDR_SIZE - 1);
    /* <- Setup */

    /* Pre-emptive Teardown -> */
    destroy_temp_ser(filepath, dir);
    
    int status = 0;
    serfile* test_ser = NULL;
    ser_open_file(
            &test_ser,
            filepath,
            READONLY,
            &status
    );
    ck_assert_int_eq(status, FILE_DNE);
    ck_assert_ptr_null(test_ser);

} END_TEST

Suite* open_file_suite() {
    Suite* s;
    s = suite_create("Open File");

    TCase* tc_open_file = tcase_create("open_file");
    tcase_add_test(tc_open_file, open_file_success);
    tcase_add_test(tc_open_file, open_file_no_trailer);
    tcase_add_test(tc_open_file, open_file_short_trailer);
    tcase_add_test(tc_open_file, open_file_short_data_section);
    tcase_add_test(tc_open_file, open_file_short_header);
    tcase_add_test(tc_open_file, open_file_ser_occupied);
    tcase_add_test(tc_open_file, open_file_null_ser);
    tcase_add_test(tc_open_file, open_file_null_path);
    tcase_add_test(tc_open_file, open_file_invalid_path);
    suite_add_tcase(s, tc_open_file);

    return s;
}

