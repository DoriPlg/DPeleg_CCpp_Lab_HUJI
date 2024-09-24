#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
// write only between #define EX2_REPO_TESTBUSLINES_H and #endif 
//EX2_REPO_TESTBUSLINES_H
#include <stdbool.h>
#include "sort_bus_lines.h"

/**
 * Asserts if the array is sorted bus lines distance.
 * @param start - a pointer to the start of the list
 * @param end - a pointer to the last item of the list
 */
int is_sorted_by_distance (const BusLine *start, const BusLine *end);

/**
 * Asserts if the array is sorted bus lines duration.
 * @param start - a pointer to the start of the list
 * @param end - a pointer to the last item of the list
 */
int is_sorted_by_duration (const BusLine *start, const BusLine *end);

/**
 * Asserts if the array is sorted bus lines name. 
 * @param start - a pointer to the start of the list
 * @param end - a pointer to the last item of the list
 */
int is_sorted_by_name (const BusLine *start, const BusLine *end);

/**
 * Asserts if the two arrays are equal, so the names of the bus
 * lines are the same, and the list length is the same.
 * @param start_sorted - a pointer to the start of the sorted list
 * @param end_sorted - a pointer to the last item of the sorted list
 * @param start_original - a pointer to the start of the original list
 * @param end_original - a pointer to the last item of the original list
 */
int is_equal (const BusLine *start_sorted,
              const BusLine *end_sorted,
              const BusLine *start_original,
              const BusLine *end_original);
// write only between #define EX2_REPO_TESTBUSLINES_H and #endif
//EX2_REPO_TESTBUSLINES_H
#endif //EX2_REPO_TESTBUSLINES_H
