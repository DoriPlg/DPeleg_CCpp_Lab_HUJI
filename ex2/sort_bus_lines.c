#include "sort_bus_lines.h"
#include <stdio.h>


// swap two bus lines in a partition or bubblesort function
// @param a - a pointer to the first bus line
// @param b - a pointer to the second bus line
void swap (BusLine *a, BusLine *b){
    // create a temporary bus line to store the first bus line's value
    BusLine temp = *a;
    *a = *b;
    *b = temp;
}

BusLine *partition (BusLine *start, BusLine *end, SortType sort_type){
    // intialize the pivot to the last element, and the i and j to the first
    BusLine *pivot = end;
    BusLine *i = start;
    BusLine *j = start;
    while (j < pivot){
        if (sort_type == DISTANCE){
        // if the distance is less than the pivot's distance, swap the values
        // and increment i. In any case, increment j.
            if (j->distance < pivot->distance){
                swap(i++, j);
                }
            j++;
        }
        else if (sort_type == DURATION){
        // if the duration is less than the pivot's duration, swap the values
        // and increment i. In any case, increment j.
            if (j->duration < pivot->duration){
                swap(i++, j);
                }
            j++;
        }
    }
    // swap the pivot with the value at i, as currently i is pointing
    // to the first element greater than the pivot
    swap(i, pivot);
    return i;
}

void quick_sort (BusLine *start, BusLine *end, SortType sort_type){
    if (start < end){
        // partition the array and sort the two partitions, find the pivot
        BusLine *pivot = partition(start, end, sort_type);
        // recursively sort the two partitions
        quick_sort(start, pivot-1, sort_type);
        quick_sort(pivot + 1, end, sort_type);
    }
}

void bubble_sort (BusLine *start, BusLine *end){
    for (int i = 0; i <= end-start; i++){ //loop for the number of elements
        for (BusLine *j = start; j < end ; j++){ //loop on the pointers
            if (strcmp(j->name, (j+1)->name) > 0){ //compare the names
                swap(j, j+1);
            }
        }
    }
}
