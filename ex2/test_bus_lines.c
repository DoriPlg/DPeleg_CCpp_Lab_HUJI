#include "test_bus_lines.h"
#include <stdio.h>

int is_equal (const BusLine *start_sorted,
              const BusLine *end_sorted,
              const BusLine *start_original,
              const BusLine *end_original){
    // initialize the matches counter
    int matches = 0;
    // loop on the two lists
    for (int i = 0; i <= end_sorted-start_sorted; i++){ 
    for (int j = 0; j <= end_original-start_original; j++){
        if (strcmp(start_original[i].name, start_sorted[j].name) == 0){
            matches++; // increment the matches counter if the names are equal
        }
    }
    }
    // check if the number of matches is equal to the length of the lists
    // if so, the lists are equal (by trasitivity of equality)
    return matches == (end_sorted - start_sorted+1)
           && matches == (end_original - start_original+1); 
}

int is_sorted_by_distance (const BusLine *start, const BusLine *end){
    for (int i = 0; i < end-start; i++){ // loop on the list
        if (start[i].distance > start[i+1].distance){
// if the distance is greater than the next distance, the list is not sorted
            return false;
        }
    }
    // if the loop ends, the list is sorted
    return true;
}

int is_sorted_by_duration (const BusLine *start, const BusLine *end){
    for (int i = 0; i < end-start; i++){ // loop on the list
        if (start[i].duration > start[i+1].duration){
// if the duration is greater than the next duration, the list is not sorted
            return false;
        }
    }
// if the loop ends, the list is sorted
    return true;
}

int is_sorted_by_name (const BusLine *start, const BusLine *end){
    for (int i = 0; i < end-start; i++){ // loop on the list
        if (strcmp(start[i].name, start[i+1].name) > 0){
// if the name is greater than the next name, the list is not sorted
            return false;
        }
    }
    // if the loop ends, the list is sorted
    return true;
}