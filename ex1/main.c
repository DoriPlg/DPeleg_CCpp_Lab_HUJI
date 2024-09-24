#include "cipher.h"
#include "tests.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARG_NUM_ERR  "The program receives 1 or 4 arguments only.\n"
#define FILE_ERR  "The given file is invalid.\n"
#define INT_ERR  "The given shift value is invalid.\n"
#define COMMAND_ERR  "The given command is invalid.\n"
#define SINGLE_ARG_ERR  "Usage: cipher test\n"
#define MAX_CHAR_LINE 1024
#define TEST_ARG "test"
#define CIPHER_ARG "cipher"
#define DECIPHER_ARG "decipher"
#define DECIMAL_BASE 10
#define FOUR_ARGS 5
#define ONE_ARG 2
#define NUMBER_OF_TESTS 10

enum Arguments {
  COMMAND_NAME = 1,
  KEY,
  SOURCE_FILE,
  OUT_FILE,
} ;

// Checks if charset is a proper integer.
// Returns true if it is, false otherwise.
// @param charset: a string to check if it's an integer.
bool is_not_int (const char charset[]) {
  for (int i = 0; charset[i]; i++) {
    if ((charset[i]<'0' || charset[i]>'9')&&(i != 0 || charset[i]!='-')) {
        return true;
    }
  }
  return false;
}


// Returns EXIT_FAILURE if the number of arguments is not 1 or 4.
int num_arg_fail (){
  fprintf(stderr,"%s", ARG_NUM_ERR);
  return EXIT_FAILURE;
}

// Returns EXIT_FAILURE if one argument is used but is not "test".
int single_arg_fail (){
  fprintf(stderr,"%s", SINGLE_ARG_ERR);
  return EXIT_FAILURE;
}

// Returns EXIT_FAILURE if 4 arguments are used but the
// command is not "cipher" or "decipher".
int command_fail (){
  fprintf(stderr,"%s", COMMAND_ERR);
  return EXIT_FAILURE;
}

// Returns EXIT_FAILURE if 4 arguments are used but the second argument
// is not an integer.
int int_arg_fail (){
  fprintf(stderr,"%s", INT_ERR);
  return EXIT_FAILURE;
}

// Returns EXIT_FAILURE if one of the files recieved is invalid.
int file_fail (){
  fprintf(stderr,"%s", FILE_ERR);
  return EXIT_FAILURE;
}


/**
 * Tests all the functions in the program.
 * @return true if all tests pass and false otherwise.
 */
bool test_all ()
{
    /// Counts up the number of tests properly executed
    int test_sum = 0;
    test_sum += test_cipher_non_cyclic_lower_case_positive_k();
    test_sum += test_cipher_cyclic_lower_case_special_char_positive_k();
    test_sum += test_cipher_non_cyclic_lower_case_special_char_negative_k();
    test_sum += test_cipher_cyclic_lower_case_negative_k();
    test_sum += test_cipher_cyclic_upper_case_positive_k();
    test_sum += test_decipher_non_cyclic_lower_case_positive_k();
    test_sum += test_decipher_cyclic_lower_case_special_char_positive_k();
    test_sum += test_decipher_non_cyclic_lower_case_special_char_negative_k();
    test_sum += test_decipher_cyclic_lower_case_negative_k();
    test_sum += test_decipher_cyclic_upper_case_positive_k();
    return test_sum == NUMBER_OF_TESTS ? EXIT_SUCCESS:EXIT_FAILURE;
}

int main (int argc, char *argv[]) {
  const char *command = argv[COMMAND_NAME];
  if (argc == FOUR_ARGS){ /// First input type.
    /// Verifies proper command, on way of negation.
    if (strcmp(command,CIPHER_ARG) && strcmp(command,DECIPHER_ARG)) {
        return command_fail();
    }
    else { /// Either decipher or cipher.
        /// Handles the second argument, ensures that it is an integer.
        if (is_not_int(argv[KEY])) { return int_arg_fail(); }
        char *str_prt;
        const int k = strtol(argv[KEY], &str_prt, DECIMAL_BASE);
        /// Handling the files and the possible errors
        FILE *file_input = fopen(argv[SOURCE_FILE], "r");
        FILE  *file_output = fopen (argv[OUT_FILE], "w");
        if (file_input == NULL || file_output == NULL){return file_fail();}
        /// Runs through the file encoding each line met
        char line[MAX_CHAR_LINE];
        while (fgets(line, MAX_CHAR_LINE, file_input)) {
            /// Cipher explicitly, decipher by default.
            strcmp(command,CIPHER_ARG)==0?cipher(line,k):decipher(line,k);
            fputs(line, file_output);
        }
        fclose(file_input);
        fclose(file_output);} /// If the command is improper.
  }
  else if (argc == ONE_ARG){ /// Second input type
      return strcmp(command,TEST_ARG) == 0 ? test_all() : single_arg_fail();
  }
  else { /// Wrong amount of arguments.
    return num_arg_fail();
  }
  return EXIT_SUCCESS;
}
