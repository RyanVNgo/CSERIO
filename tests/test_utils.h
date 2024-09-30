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
 *  @param  file      (I) - source file of error.
 *  @param  line      (I) - line number of error.
 *  @return Void.
 */
void check_error_v(int status, int target, char* file, int line);
#define check_error(status, target) check_error_v(status, target, __FILE__, __LINE__)

/** @brief  Check if the result and target buffers are equal
 *
 *  Ensure that the number of bytes compared is within range
 *  of the two buffers as to not cause a seg fault.
 *
 *  @param  result    (I) - Result buffer.
 *  @param  target    (I) - Target buffer.
 *  @param  byte_len  (I) - Number of bytes to compare.
 *  @param  file      (I) - source file of error.
 *  @param  line      (I) - line number of error.
 *  @return Void.
 */
void check_buff_v(void* result, void* target, unsigned long byte_len, char* file, int line);
#define check_buff(result, target, byte_len) check_buff_v(result, target, byte_len, __FILE__, __LINE__)

/** @brief  Check if the result and target integers are equal
 *
 *  @param  result    (I) - Result integer.
 *  @param  target    (I) - Target integer.
 *  @param  file      (I) - source file of error.
 *  @param  line      (I) - line number of error.
 *  @return Void.
 */
void check_int_v(int result, int target, char* file, int line);
#define check_int(result, target) check_int_v(result, target, __FILE__, __LINE__)

/** @brief  Check if the result and target unsigned longs are equal
 *
 *  @param  result    (I) - Result unsigned long.
 *  @param  target    (I) - Target unsigned long.
 *  @param  file      (I) - source file of error.
 *  @param  line      (I) - line number of error.
 *  @return Void.
 */
void check_unsigned_long_v(unsigned long result, unsigned long target, char* file, int line);
#define check_unsigned_long(result, target) check_unsigned_long_v(result, target, __FILE__, __LINE__)



#endif 
