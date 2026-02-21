
#include <check.h>

#if defined(UNITY_TEST)
#define CSERIO_IMPLEMENTATION
#endif

#include "core.c"
#include "header_read.c"
#include "header_write.c"
#include "image_info.c"
#include "trailer_read.c"


int main() {
    int number_failed = 0;

    Suite* core_s; 
    core_s = core_suite();
    SRunner* core_sr = srunner_create(core_s);
    srunner_run_all(core_sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(core_sr);
    srunner_free(core_sr);

    Suite* hdr_read_s; 
    hdr_read_s = header_read_suite();
    SRunner* hdr_read_sr = srunner_create(hdr_read_s);
    srunner_run_all(hdr_read_sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(hdr_read_sr);
    srunner_free(hdr_read_sr);

    Suite* hdr_write_s; 
    hdr_write_s = header_write_suite();
    SRunner* hdr_write_sr = srunner_create(hdr_write_s);
    srunner_run_all(hdr_write_sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(hdr_write_sr);
    srunner_free(hdr_write_sr);

    Suite* image_info_s; 
    image_info_s = image_info_suite();
    SRunner* image_info_sr = srunner_create(image_info_s);
    srunner_run_all(image_info_sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(image_info_sr);
    srunner_free(image_info_sr);

    Suite* trlr_read_s; 
    trlr_read_s = trailer_read_suite();
    SRunner* trlr_read_sr = srunner_create(trlr_read_s);
    srunner_run_all(trlr_read_sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(trlr_read_sr);
    srunner_free(trlr_read_sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

