/** @file test_routines.h
 *  @brief Calls for all testing routines
 *
 *  @author Ryan V. Ngo
 */

#ifndef TEST_CORE_ROUTINES_H
#define TEST_CORE_ROUTINES_H

static int IS_VERBOSE = 0;

void run_core_routines_suite(int is_verbose);
void run_header_routines_suite(int is_verbose);
void run_img_routines_suite(int is_verbose);

#endif
