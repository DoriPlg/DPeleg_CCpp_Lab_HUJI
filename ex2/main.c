#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sort_bus_lines.h"
#include "test_bus_lines.h"

#define DURATION_ARG "by_duration"
#define DISTANCE_ARG "by_distance"
#define NAME_ARG "by_name"
#define TEST_ARG "test"
#define ARGUMENTS 2
#define COMMAND_ARG 1
#define SINGLE_INPUT_LEN 21
#define MAX_INPUT_LEN 60
#define MAX_DISTANCE 1000
#define MIN_DISTANCE 0
#define MAX_DURATION 100
#define MIN_DURATION 10
#define USAGE "Usage: sort_lines <by_duration/by_distance/by_name/test>\n"
#define ENTER "Enter line info. Then enter\n"
#define ERROR_NAME 
#define ERROR_DURATION 

// the main part of the code is the main function, 
// which is responsible for the input and the sorting of the bus lines. 
// important convention - the "end" pointer is always the last element
//  of the array, and the "start" pointer is always the 
// first element of the array.


// copy array from start to end to copy, a pointer to the start a new array
// @param start - pointer to the start of the array
// @param end - pointer to the last item of the array
// @param copy - pointer to the start of the new array
void copy_array(BusLine *start, BusLine *end, BusLine *copy){
    // loop on the array and copy the values
    for (int i = 0; i <= end-start; i++){
        *(copy+i) = *(start+i);
    }
}

// check if the input is a positive integer
// @param str - the string to check
// @return - 0 if the string is not a positive integer, the integer otherwise
int pos_int(char *str){
    int num;
    for (int i = 0; str[i]; i++){ // loop on the string
        if (!(('0'<=str[i] && str[i]<='9') || str[i]=='\n')){
            // return false if the string is not a positive integer
            return 0;
        }
    }
    // convert the string to an integer
    sscanf(str, "%d", &num);
    return num;
}

// get the length of the from the user
// @return - the length of the desired list
int get_list_length(){
    int length;
    char length_str[SINGLE_INPUT_LEN];
    printf("Enter number of lines. Then enter\n");
    // get the input from the user
    while (!(length=pos_int(fgets(length_str, SINGLE_INPUT_LEN, stdin)))){
        printf("Error: Number of lines should be a positive integer\n");
        printf("Enter number of lines. Then enter\n");
    }
    return length;
}

// check if the name is valid
// @param name - the name to check
// @return - the name if valid, NULL otherwise
char *check_name(char *name){
    for (int i = 0; i < SINGLE_INPUT_LEN; i++){ // loop on the name
        if (!(('0'<=name[i] && name[i]<='9') || 
            ('a'<=name[i] && name[i]<='z') || name[i]=='\0')){
            // return NULL if the name is comprised of invalid characters
            return NULL; 
        }
    }
    return name;
}

// check if the distance is valid
// @param distance - the distance to check
// @return - true if the distance is valid, false otherwise
bool check_distance(int distance){
    return (MIN_DISTANCE<=distance&&distance<=MAX_DISTANCE);
}

// check if the duration is valid
// @param duration - the duration to check
// @return - true if the duration is valid, false otherwise
bool check_duration(int duration){
    return (MIN_DURATION<=duration&&duration<=MAX_DURATION);
}

// get the input from the user for a single bus line
// @param name - a pointer to the name of the bus line
// @param distance - a pointer to the distance of the bus line
// @param duration - a pointer to the duration of the bus line
void get_input(char *name, int *distance, int *duration){
    printf(ENTER);
    char str[MAX_INPUT_LEN];
    fgets(str,MAX_INPUT_LEN, stdin);
    int index = 0;
    // get the name from the input, loops until a comma is reached
    while (str[index] != ','){
        name[index] = str[index];
        index++;
    }
    name[index++] = '\0';
    // get the distance and duration from the input, from the comma
    sscanf(str + index, "%d,%d", distance, duration);
}

// allows the user to input a list of bus lines
// @param start - a pointer to the start of the list
// @param end - a pointer to the last item of the list
void get_list(BusLine *start, BusLine *end){
    //loops from the starting pointer to the end pointer
    for (BusLine *bus = start; bus <= end; bus++){ 
        // initialize the name, distance and duration, with value
        char name[SINGLE_INPUT_LEN]={0};
        int distance=0, duration=0;
        // get the input from the user
        get_input(name, &distance, &duration);
    // check if the input is valid, if not, display the error and ask again
        while (!(check_name(name) && check_distance(distance)
                && check_duration(duration))){
            if (!check_name(name)){
                printf(
"Error: bus name should contains only digits and small chars\n");
            }
            if (!check_distance(distance)){
                printf(
"Error: distance should be an integer between 0 and 1000 (includes)\n");
            }
            if (!check_duration(duration)){
                printf(
"Error: duration should be an integer between 10 and 100 (includes)\n");
            }
            get_input( name, &distance, &duration);
        }
        // copy the values to the bus line
        strcpy(bus->name, name);
        bus->distance = distance;
        bus->duration = duration;
    }
}

// test the distance sorting and the equality of the lists
// @param start - a pointer to the start of the list
// @param end - a pointer to the last item of the list
void test_distance(BusLine *start, BusLine *end){
    // create a copy of the list
    int length = end-start+1;
    BusLine *old = malloc(length * sizeof(BusLine));
    copy_array(start, end, old);
    // sort the list by distance
    quick_sort(start, end, DISTANCE);
    // run the tests
    printf(is_sorted_by_distance(start, end)
            ?"TEST 1 PASSED: The array is sorted by distance\n"
            :"TEST 1 FAILED: Not sorted by distance.\n");
    printf(is_equal(start, end, old, old+(length-1))
            ?"TEST 2 PASSED: The array has the same items after sorting\n"
            :"TEST 2 FAILED: Lists not equal.\n");
    free(old); // #free_memory
}

// test the duration sorting and the equality of the lists
// @param start - a pointer to the start of the list
// @param end - a pointer to the last item of the list
void test_duration(BusLine *start, BusLine *end){
    // create a copy of the list
    int length = end-start+1;
    BusLine *old = malloc(length * sizeof(BusLine));
    copy_array(start, end, old);
    // sort the list by duration
    quick_sort(start, end, DURATION);
    // run the tests
    printf(is_sorted_by_duration(start, end)
            ?"TEST 3 PASSED: The array is sorted by duration\n"
            :"TEST 3 FAILED: Not sorted by duration.\n");
    printf(is_equal(start, end,old, old+(length-1))
            ?"TEST 4 PASSED: The array has the same items after sorting\n"
            :"TEST 4 FAILED: Lists not equal.\n");
    free(old); // #free_memory
}

// test the name sorting and the equality of the lists
// @param start - a pointer to the start of the list
// @param end - a pointer to the last item of the list
void test_name(BusLine *start, BusLine *end){
    // create a copy of the list
    int length = end-start+1;
    BusLine *old = malloc(length * sizeof(BusLine));
    copy_array(start, end, old);
    // sort the list by name
    bubble_sort(start, end);
    // run the tests
    printf(is_sorted_by_name(start, end)
            ?"TEST 5 PASSED: The array is sorted by name\n":
            "TEST 5 FAILED: Not sorted by name.\n");
    printf(is_equal(start, end, old, old+(length-1))
            ?"TEST 6 PASSED: The array has the same items after sorting\n"
            :"TEST 6 FAILED: Lists not equal.\n");
    free(old); // #free_memory
}

// test all the sorting and equality of the lists
// @param start - a pointer to the start of the list
// @param end - a pointer to the last item of the list
void test_all (BusLine *start, BusLine *end){
    // run all the tests
    test_distance(start, end);
    test_duration(start, end);
    test_name(start, end);
}

// print the list of bus lines
// @param start - a pointer to the start of the list
// @param end - a pointer to the last item of the list
void print_all(BusLine *start, BusLine *end){
    for (BusLine *bus = start; bus <= end; bus++){ // loop on the list
    // print the name, distance and duration
        printf("%s,%d,%d\n", bus->name, bus->distance, bus->duration);
    }
}


// main function, handling the input and the sorting
int main (int argc, char *argv[])
{
// check if the input is valid
if (argc == ARGUMENTS && (strcmp(argv[COMMAND_ARG], TEST_ARG) == 0 ||
                            strcmp(argv[COMMAND_ARG], DURATION_ARG) == 0 ||
                            strcmp(argv[COMMAND_ARG], DISTANCE_ARG) == 0 ||
                            strcmp(argv[COMMAND_ARG], NAME_ARG) == 0))
{
    // get the list length and allocate memory for the list
    int list_length = get_list_length();
    BusLine *bus_lines = malloc(list_length * sizeof(BusLine));
    if (!bus_lines){ // check if the memory allocation failed
        // printf("Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    // get the list of bus lines
    get_list(bus_lines, bus_lines + list_length-1);
    if (strcmp(argv[COMMAND_ARG], TEST_ARG) == 0){ // run the test
        test_all(bus_lines, bus_lines + list_length-1);
    }
    else if (strcmp(argv[COMMAND_ARG], DURATION_ARG) == 0){
        // sort and print the list by duration
        quick_sort(bus_lines, bus_lines + list_length-1, DURATION);
        print_all(bus_lines, bus_lines + list_length-1);
    }
    else if (strcmp(argv[COMMAND_ARG], DISTANCE_ARG) == 0){
        // sort and print the list by distance
        quick_sort(bus_lines, bus_lines + list_length-1, DISTANCE);
        print_all(bus_lines, bus_lines + list_length-1);
    }
    else if (strcmp(argv[COMMAND_ARG], NAME_ARG) == 0){
        // sort and print the list by name
        bubble_sort(bus_lines, bus_lines + list_length-1);
        print_all(bus_lines, bus_lines + list_length-1);
    }
    free(bus_lines); // #free_memory
    return EXIT_SUCCESS;
}
else{ // print the usage if the input is invalid
    printf(USAGE);}
return EXIT_FAILURE;
}
