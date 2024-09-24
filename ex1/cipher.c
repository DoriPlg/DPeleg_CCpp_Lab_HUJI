#include "cipher.h"

#define LET_IN_ENG 26
/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.

/**
 * Encodes a given character according to the given shift value - k.
 * @param c - given character.
 * @param k - given shift value.*/
char shift_char (char c, int k)
{
    k %= LET_IN_ENG; // to save loops
    int new_num = k + c;
    /// For lowercase letters
    if ('a' <= c && c <= 'z') {
        if ('a' <= new_num && new_num <= 'z') {
            return new_num;
        }
        return (new_num<'a')?('z'-('a'-new_num-1)):('a'+(new_num-'z'-1));
    }
    /// For uppercase letters
    if ('A' <= c && c <= 'Z') {
        if ('A' <= new_num && new_num <= 'Z') {
            return new_num;
        }
        return (new_num<'A')?('Z'-('A'-new_num-1)):('A'+(new_num-'Z'-1));
    }
    /// For special characters
    return c;
}

// See full documentation in header file
void cipher (char s[], int k)
{
    for (int i = 0; s[i]; i++){
        s[i] = shift_char(s[i],k);
    }
}

// See full documentation in header file
void decipher (char s[], int k)
{
    for (int i = 0; s[i]; i++){
        s[i] = shift_char(s[i],-k);
    }
}
