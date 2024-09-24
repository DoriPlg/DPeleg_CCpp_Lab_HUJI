#include "tests.h"

#define K_1 3
#define K_2 2
#define K_3 -1
#define K_4 -3
#define K_5 29


// See full documentation in header file
int test_cipher_non_cyclic_lower_case_positive_k ()
{
  char in[] = "abc";
  char out[] = "def";
  cipher (in, K_1);
  return strcmp (in, out) == 0;
}

// See full documentation in header file
int test_cipher_cyclic_lower_case_special_char_positive_k ()
{
    char in[] = "ab!y";
    char out[] = "cd!a";
    cipher (in, K_2);
    return strcmp (in, out) == 0;
}

// See full documentation in header file
int test_cipher_non_cyclic_lower_case_special_char_negative_k ()
{
    char in[] = "d@ef";
    char out[] = "c@de";
    cipher (in, K_3);
    return strcmp (in, out) == 0;
}

// See full documentation in header file
int test_cipher_cyclic_lower_case_negative_k ()
{
    char in[] = "dab";
    char out[] = "axy";
    cipher (in, K_4);
    return strcmp (in, out) == 0;
}

// See full documentation in header file
int test_cipher_cyclic_upper_case_positive_k ()
{
    char in[] = "AXL";
    char out[] = "DAO";
    cipher (in, K_5);
    return strcmp (in, out) == 0;
}

// See full documentation in header file
int test_decipher_non_cyclic_lower_case_positive_k ()
{
  char in[] = "def";
  char out[] = "abc";
  decipher (in, K_1);
  return strcmp (in, out) == 0;
}

// See full documentation in header file
int test_decipher_cyclic_lower_case_special_char_positive_k ()
{
    char in[] = "cd&a";
    char out[] = "ab&y";
    decipher (in, K_2);
    return strcmp (in, out) == 0;
}

// See full documentation in header file
int test_decipher_non_cyclic_lower_case_special_char_negative_k ()
{
    char in[] = "cde#";
    char out[] = "def#";
    decipher (in, K_3);
    return strcmp (in, out) == 0;
}

// See full documentation in header file
int test_decipher_cyclic_lower_case_negative_k ()
{
    char in[] = "axy";
    char out[] = "dab";
    decipher (in, K_4);
    return strcmp (in, out) == 0;
}

// See full documentation in header file
int test_decipher_cyclic_upper_case_positive_k ()
{
    char in[] = "DAO";
    char out[] = "AXL";
    decipher (in, K_5);
    return strcmp (in, out) == 0;
}

