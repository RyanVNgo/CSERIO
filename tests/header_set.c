
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

START_TEST(header_set_success) {
    char dir[] = "/tmp/cserio_testXXXXXX";
    char filepath[512];
    SERHdrStructure blank_hdr = {0};
    memset(&blank_hdr, 0, sizeof(blank_hdr));
    create_temp_ser(filepath, dir, &blank_hdr, sizeof(blank_hdr));
    /* <- File Setup */

    int status = 0;
    serfile* test_ser = NULL;
    ser_open_file(&test_ser, filepath, READWRITE, &status);

    SERHdrStructure test_data = {
		.file_id = "TEST_FILEID",
		.lu_id = 0x71,
		.color_id = BAYER_RGGB,
		.little_endian = LITTLEENDIAN_TRUE,
		.image_width = 10,
		.image_height = 10,
		.pixel_depth_per_plane = 8,
		.frame_count = 0,
		.observer = "TEST_OBSERVER_2.1.0",
		.instrument = "TEST_INSTRUMENT_2.1.0",
		.telescope = "TEST_TELESCOPE_2.1.0",
		.date_time = TEST_TIMESTAMP_VALUE,
		.date_time_utc = TEST_TIMESTAMP_VALUE
    };

    ser_set_file_id(test_ser, test_data.file_id, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_set_lu_id(test_ser, test_data.lu_id, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_set_color_id(test_ser, test_data.color_id, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_set_little_endian(test_ser, test_data.little_endian, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_set_image_width(test_ser, test_data.image_width, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_set_image_height(test_ser, test_data.image_height, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_set_pixel_depth_per_plane(test_ser, test_data.pixel_depth_per_plane, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_set_observer(test_ser, test_data.observer, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_set_instrument(test_ser, test_data.instrument, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_set_telescope(test_ser, test_data.telescope, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_set_date_time(test_ser, test_data.date_time, &status);
    ck_assert_int_eq(status, NO_ERROR);
    ser_set_date_time_utc(test_ser, test_data.date_time_utc, &status);
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

    /* is header written as set */
    ck_assert_mem_eq(check_buff, &test_data, sizeof(test_data));

    /*
    for (size_t i = 0; i < sizeof(test_data); i++) {
        if (check_buff[i] != ((uint8_t*)(&test_data))[i]) {
            ck_abort_msg("Data mismatch at offset: %ld", i);
        }
    }
    */

    /* Teardown -> */
    free(check_buff);
    destroy_temp_ser(filepath, dir);
} END_TEST

START_TEST(header_set_invalid_set) {
} END_TEST

START_TEST(header_set_null_data) {
} END_TEST

START_TEST(header_set_null_ser) {
} END_TEST

Suite* header_set_suite() {
    Suite* s;
    s = suite_create("Header Set");

    TCase* tc_header_set;
    tc_header_set = tcase_create("header_set");
    tcase_add_test(tc_header_set, header_set_success);
    tcase_add_test(tc_header_set, header_set_invalid_set);
    tcase_add_test(tc_header_set, header_set_null_data);
    tcase_add_test(tc_header_set, header_set_null_ser);
    suite_add_tcase(s, tc_header_set);

    return s;
}

