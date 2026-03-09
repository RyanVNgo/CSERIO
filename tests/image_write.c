
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

START_TEST(append_frame_success_no_trailer) {
    char dir[] = "/tmp/cserio_testXXXXXX";
    char filepath[512];
    size_t init_file_size = sizeof(test_data_3x50) - sizeof(test_data_3x50.trlr);
    create_temp_ser(
            filepath,
            dir,
            &test_data_3x50, 
            init_file_size
    );
    /* <- File Setup */

    int status = 0;
    serfile* test_ser = NULL;
    ser_open_file(
            &test_ser,
            filepath,
            READWRITE,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);

    /* TEST */
    uint8_t test_data[50 * 50] = {0};
    memset(test_data, 0xA0, sizeof(test_data));
    ser_append_frame(
            test_ser,
            test_data,
            TEST_TIMESTAMP_VALUE,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);
    ser_close_file(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);

    /* retrieve file details */
    FILE* test_file = fopen(filepath, "rb");
    if (!test_file) {
        ck_abort_msg("Failed to open test SER");
    }
    fseek(test_file, 0, SEEK_END);
    size_t file_size = ftell(test_file);

    uint8_t* check_buff = malloc(file_size);
    fseek(test_file, 0, SEEK_SET);
    fread(check_buff, 1, file_size, test_file);

    fclose(test_file);

    /* file size check */
    ck_assert_int_eq(file_size, init_file_size + sizeof(test_data));

    /* was data written as desired location */
    size_t exp_frame_offset = HDR_SIZE + sizeof(test_data_3x50.data);
    ck_assert_mem_eq(
            check_buff + exp_frame_offset,
            test_data,
            sizeof(test_data)
    );

    /* is data before frame (hdr) intact */
    SERHdrStructure new_hdr = test_data_3x50.hdr;
    new_hdr.frame_count += 1;
    ck_assert_mem_eq(
            check_buff,
            &new_hdr,
            sizeof(test_data_3x50.hdr)
    );

    /* Teardown -> */
    free(check_buff);
    destroy_temp_ser(filepath, dir);
} END_TEST

START_TEST(append_frame_success_with_trailer) {
    char dir[] = "/tmp/cserio_testXXXXXX";
    char filepath[512];
    size_t init_file_size = sizeof(test_data_3x50);
    create_temp_ser(
            filepath,
            dir,
            &test_data_3x50, 
            init_file_size
    );
    /* <- File Setup */

    int status = 0;
    serfile* test_ser = NULL;
    ser_open_file(
            &test_ser,
            filepath,
            READWRITE,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);

    /* TEST */
    uint8_t test_data[50 * 50] = {0};
    memset(test_data, 0xA0, sizeof(test_data));
    ser_append_frame(
            test_ser,
            test_data,
            TEST_TIMESTAMP_VALUE,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);
    ser_close_file(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);

    /* retrieve file details */
    FILE* test_file = fopen(filepath, "rb");
    if (!test_file) {
        ck_abort_msg("Failed to open test SER");
    }
    fseek(test_file, 0, SEEK_END);
    size_t file_size = ftell(test_file);

    uint8_t* check_buff = malloc(file_size);
    fseek(test_file, 0, SEEK_SET);
    fread(check_buff, 1, file_size, test_file);

    fclose(test_file);

    /* file size check */
    ck_assert_int_eq(file_size, init_file_size + sizeof(test_data) + sizeof(int64_t));

    /* was data written as desired location */
    size_t exp_frame_offset = HDR_SIZE + sizeof(test_data_3x50.data);
    ck_assert_mem_eq(
            check_buff + exp_frame_offset,
            test_data,
            sizeof(test_data)
    );

    /* is data before frame (hdr) intact */
    SERHdrStructure new_hdr = test_data_3x50.hdr;
    new_hdr.frame_count += 1;
    ck_assert_mem_eq(
            check_buff,
            &new_hdr,
            sizeof(test_data_3x50.hdr)
    );

    /* was timestamp written */
    ck_assert_int_eq(
            *((int64_t*)(check_buff + file_size - sizeof(int64_t))), 
            TEST_TIMESTAMP_VALUE
    );

    /* Teardown -> */
    free(check_buff);
    destroy_temp_ser(filepath, dir);
} END_TEST

START_TEST(append_frame_success_empty_no_trailer) {
    SERHdrStructure test_hdr = {
        .color_id = MONO,
        .image_width = 10,
        .image_height = 10,
        .pixel_depth_per_plane = 8,
        .frame_count = 0
    };
    char dir[] = "/tmp/cserio_testXXXXXX";
    char filepath[512];
    create_temp_ser(filepath, dir, &test_hdr, sizeof(test_hdr));
    /* <- File Setup */

    int status = 0;
    serfile* test_ser = NULL;
    ser_open_file(
            &test_ser,
            filepath,
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

    ser_close_file(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);

    /* retrieve file details */
    FILE* test_file = fopen(filepath, "rb");
    if (!test_file) {
        ck_abort_msg("Failed to open test SER");
    }
    fseek(test_file, 0, SEEK_END);
    size_t file_size = ftell(test_file);

    uint8_t* check_buff = malloc(file_size);
    fseek(test_file, 0, SEEK_SET);
    fread(check_buff, 1, file_size, test_file);

    fclose(test_file);

    /* file size check */
    ck_assert_int_eq(file_size, sizeof(test_hdr) + sizeof(test_data));

    /* was data written as desired location */
    ck_assert_mem_eq(
            check_buff + HDR_SIZE,
            test_data,
            sizeof(test_data)
    );

    /* is data before frame (hdr) intact */
    SERHdrStructure new_hdr = test_hdr;
    new_hdr.frame_count += 1;
    ck_assert_mem_eq(
            check_buff,
            &new_hdr,
            sizeof(test_data_3x50.hdr)
    );

    /* Teardown -> */
    free(check_buff);
    destroy_temp_ser(filepath, dir);
} END_TEST

START_TEST(append_frame_success_empty_with_trailer) {
    SERHdrStructure test_hdr = {
        .color_id = MONO,
        .image_width = 10,
        .image_height = 10,
        .pixel_depth_per_plane = 8,
        .frame_count = 0
    };
    char dir[] = "/tmp/cserio_testXXXXXX";
    char filepath[512];
    create_temp_ser(filepath, dir, &test_hdr, sizeof(test_hdr));
    /* <- File Setup */

    int status = 0;
    serfile* test_ser = NULL;
    ser_open_file(
            &test_ser,
            filepath,
            READWRITE,
            &status
    );
    ck_assert_int_eq(status, NO_ERROR);
    ser_enable_trailer(test_ser, &status);
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
    ser_close_file(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);

    /* retrieve file details */
    FILE* test_file = fopen(filepath, "rb");
    if (!test_file) {
        ck_abort_msg("Failed to open test SER");
    }
    fseek(test_file, 0, SEEK_END);
    size_t file_size = ftell(test_file);

    uint8_t* check_buff = malloc(file_size);
    fseek(test_file, 0, SEEK_SET);
    fread(check_buff, 1, file_size, test_file);

    fclose(test_file);

    /* file size check */
    ck_assert_int_eq(file_size, sizeof(test_hdr) + sizeof(test_data) + sizeof(int64_t));

    /* was data written as desired location */
    ck_assert_mem_eq(
            check_buff + HDR_SIZE,
            test_data,
            sizeof(test_data)
    );

    /* is data before frame (hdr) intact */
    SERHdrStructure new_hdr = test_hdr;
    new_hdr.frame_count += 1;
    ck_assert_mem_eq(
            check_buff,
            &new_hdr,
            sizeof(test_data_3x50.hdr)
    );

    /* was timestamp written */
    ck_assert_int_eq(
            *((int64_t*)(check_buff + file_size - sizeof(int64_t))), 
            TEST_TIMESTAMP_VALUE
    );

    /* Teardown -> */
    free(check_buff);
    destroy_temp_ser(filepath, dir);
} END_TEST

START_TEST(append_frame_invalid_size) {
    SERHdrStructure test_hdr = {
        .color_id = MONO,
        .image_width = 0,
        .image_height = 10,
        .pixel_depth_per_plane = 8,
        .frame_count = 0
    };
    char dir[] = "/tmp/cserio_testXXXXXX";
    char filepath[512];
    create_temp_ser(filepath, dir, &test_hdr, sizeof(test_hdr));
    /* <- File Setup */

    int status = 0;
    serfile* test_ser = NULL;
    ser_open_file(
            &test_ser,
            filepath,
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
    ck_assert_int_eq(status, INVALID_FRAME_SIZE);

    status = 0;
    ser_close_file(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);

    /* retrieve file details */
    FILE* test_file = fopen(filepath, "rb");
    if (!test_file) {
        ck_abort_msg("Failed to open test SER");
    }
    fseek(test_file, 0, SEEK_END);
    size_t file_size = ftell(test_file);

    uint8_t* check_buff = malloc(file_size);
    fseek(test_file, 0, SEEK_SET);
    fread(check_buff, 1, file_size, test_file);

    fclose(test_file);

    /* file size check */
    ck_assert_int_eq(file_size, sizeof(test_hdr));

    /* is data before frame (hdr) intact */
    ck_assert_mem_eq(
            check_buff,
            &test_hdr,
            sizeof(test_hdr)
    );

    /* Teardown -> */
    free(check_buff);
    destroy_temp_ser(filepath, dir);
}

START_TEST(append_frame_null_data) {
    SERHdrStructure test_hdr = {
        .color_id = MONO,
        .image_width = 10,
        .image_height = 10,
        .pixel_depth_per_plane = 8,
        .frame_count = 0
    };
    char dir[] = "/tmp/cserio_testXXXXXX";
    char filepath[512];
    create_temp_ser(filepath, dir, &test_hdr, sizeof(test_hdr));
    /* <- File Setup */

    int status = 0;
    serfile* test_ser = NULL;
    ser_open_file(
            &test_ser,
            filepath,
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
    ser_close_file(test_ser, &status);
    ck_assert_int_eq(status, NO_ERROR);

    /* retrieve file details */
    FILE* test_file = fopen(filepath, "rb");
    if (!test_file) {
        ck_abort_msg("Failed to open test SER");
    }
    fseek(test_file, 0, SEEK_END);
    size_t file_size = ftell(test_file);

    uint8_t* check_buff = malloc(file_size);
    fseek(test_file, 0, SEEK_SET);
    fread(check_buff, 1, file_size, test_file);

    fclose(test_file);

    /* file size check */
    ck_assert_int_eq(file_size, sizeof(test_hdr));

    /* is data before frame (hdr) intact */
    ck_assert_mem_eq(
            check_buff,
            &test_hdr,
            sizeof(test_hdr)
    );

    /* Teardown -> */
    free(check_buff);
    destroy_temp_ser(filepath, dir);
} END_TEST

START_TEST(append_frame_null_ser) {
    int status = 0;

    uint8_t test_data[10 * 10] = {0};
    memset(test_data, 0xA0, sizeof(test_data));
    ser_append_frame(
            NULL,
            test_data,
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
    tcase_add_test(tc_append_frame, append_frame_success_no_trailer);
    tcase_add_test(tc_append_frame, append_frame_success_with_trailer);
    tcase_add_test(tc_append_frame, append_frame_success_empty_no_trailer);
    tcase_add_test(tc_append_frame, append_frame_success_empty_with_trailer);
    tcase_add_test(tc_append_frame, append_frame_invalid_size);
    tcase_add_test(tc_append_frame, append_frame_null_data);
    tcase_add_test(tc_append_frame, append_frame_null_ser);
    suite_add_tcase(s, tc_append_frame);

    return s;
}

