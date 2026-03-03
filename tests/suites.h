
#ifndef SUITES_H
#define SUITES_H

#include <check.h>

Suite* core_suite();

Suite* create_memory_suite();
Suite* open_view_suite();
Suite* open_memory_suite();
Suite* create_file_suite();
Suite* open_file_suite();

Suite* header_get_suite();
Suite* header_set_suite();

Suite* image_info_suite();
Suite* image_read_suite();
Suite* image_write_suite();

Suite* trailer_read_suite();


#endif

