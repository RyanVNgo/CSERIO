
#ifndef SUITES_H
#define SUITES_H

#include <check.h>

Suite* core_suite();
Suite* open_view_suite();
Suite* open_memory_suite();
Suite* create_file_suite();
Suite* open_file_suite();
Suite* header_read_suite();
Suite* header_write_suite();
Suite* get_metadata_suite();
Suite* image_info_suite();
Suite* image_read_suite();
Suite* trailer_read_suite();


#endif

