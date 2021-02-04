/* <h

Returns the first location in a string, `str1`, where a char in another string, `str2`, appears. Returns -1 if no chars in `str2` appear in `str1`.

/h> */


#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

// maximum length of strings
#define MAX_STR_LEN 1000

// Deletes all chars in `str1`, that appear in `str2`.
int any(char str1[], char str2[]);

// Index of first location in `str1` that has a char that matches a char in 
// `str2`.
int i_first_loc = -1;
// iterators
int i, i2 = 0;
// test strings
char test_str1[] = "olah";
char test_str2[] = "he";


int any(char str1[], char str2[]) {

// Finds first index in `str1` of a char that appears in `str2`.
//
// Inputs
//   `str1`: string from which to find the index
//   `str2`: string from which to read chars

    // For each char in `str1`, go through each char in `str2` and see if
    // there's a match; if there is, return the index in `str1`; if there's no
    // match, move to the next char in `str1`
    
    // Terminate when the null char is reached or exceeded max length
    while ( (str1[i] != '\0') && (i < MAX_STR_LEN) ) {
        while (str2[i2] != '\0' && (i2 < MAX_STR_LEN)) {
            if (str1[i] == str2[i2]) {
                return i_first_loc = i;
            }
            ++i2;
        }
        i2 = 0;
        ++i;
    }
    // Print message if max string length was reached
    if ( (i >= (MAX_STR_LEN - 1)) || (i2 >= (MAX_STR_LEN - 1)) ) {
        printf("Max string length of %i was reached, characters beyond this "\
                "length have been cut off", MAX_STR_LEN);
    }

    return i_first_loc;

}


int main(void) {

    
    printf("\nindex of first loc: %i", any(test_str1, test_str2));

}