#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif 
//EX2_REPO_SORTBUSLINES_H
#include <string.h>
#define NAME_LEN 21
/**
 * Bus line struct for the exercise.
 */
typedef struct BusLine
{
    char name[NAME_LEN];
    int distance, duration;
} BusLine;

/*
    * enumeration for the sort type
    * DISTANCE - sort by distance
    * DURATION - sort by duration
 */
typedef enum SortType
{
    DISTANCE,
    DURATION
} SortType;

/**
 * bubble sort for bus lines
 * @param start - a pointer to the start of the list
 * @param end - a pointer to the last item of the list
 */
void bubble_sort (BusLine *start, BusLine *end);

/**
 * Performs quicksort on the given array of bus lines,
 * for distance or duration.
 * @param start - a pointer to the start of the list
 * @param end - a pointer to the last item of the list
 * @param sort_type - the type of sorting to be performed
 */
void quick_sort (BusLine *start, BusLine *end, SortType sort_type);

/**
 * partition function for quicksort
 * @param start - a pointer to the start of the list
 * @param end - a pointer to the last item of the list
 * @param sort_type - the type of sorting to be performed
 */
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type);
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif 
//EX2_REPO_SORTBUSLINES_H
#endif //EX2_REPO_SORTBUSLINES_H
