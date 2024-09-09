/** @file test_utils.h
 *  @brief Helper routines for unit testing
 *
 *  @author Ryan V. Ngo
 */

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

/*-------------------- Test Utils --------------------*/

/** @brief Check if status values are equal
 *  
 *  This method checks whether or not the passed status value
 *  is equal to the target value where the target value
 *  is a library defined error.
 *
 *  You shouldn't need to use check_error_v directly as the
 *  check_error define excludes the last two params but is
 *  called through definition.
 *
 *  @param  status    (I) - status value.
 *  @param  target    (I) - target value.
 *  @param  file      (I) - source file of error
 *  @param  line      (I) - line number of error
 *  @return Void.
 */
void check_error_v(int status, int target, char* file, int line);
#define check_error(status, target) check_error_v(status, target, __FILE__, __LINE__)

#endif 
