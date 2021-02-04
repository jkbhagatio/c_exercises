/* <h

Deletes all chars from a string, `str1`, that appear in another string, `str2`.

Statically allocated arrays cannot be resized, so we will fill in the "extra"
vals in `str1` with null ('\0').

/h> */


#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

// maximum length of strings
#define MAX_STR_LEN 1000

// Deletes all chars in `str1`, that appear in `str2`.
void squeeze(char str1[], char str2[]);

// index for writing to (i.e. overwriting) `str`
int i_w = 0;
// iterators
int i, i2, i3 = 0;
// test strings
char test_str1[] = "hello";
char test_str2[] = "howdee";


void squeeze(char str1[], char str2[]) {

// Deletes all chars from `str1` that appear in `str2`.
//
// Inputs
//   `str1`: string from which to remove chars
//   `str2`: string from which to read chars

    // For each char in `str1`, go through each char in `str2` and see if
    // there's a match; if there is, move to the next char in `str1` without
    // incrementing `i_w` (this will effectively overwrite the char in `i_w`
    // for `str1`; if there's no match, move to the next char in `str` and
    // increment `i_w`
    
    // Terminate when the null char is reached or exceeded max length
    while ( (str1[i] != '\0') && (i < MAX_STR_LEN) ) {
        while (str2[i2] != '\0' && (i2 < MAX_STR_LEN)) {
            if (str1[i] == str2[i2]) {
                break;
            }
            ++i2;
        }
        // If we didn't find a match, assingn to `str1` and increment `i_w`
        if ( (str2[i2] == '\0') || (i2 >= (MAX_STR_LEN - 1)) ) {
            str1[i_w++] = str1[i];
        }
        ++i;
    }
    // Fill in trailing chars with nulls
    for (i3 = i_w; i3 <= i; ++i3) {
        str1[i3] = '\0';
    }
    // Print message if max string length was reached
    if ( (i >= (MAX_STR_LEN - 1)) || (i2 >= (MAX_STR_LEN - 1)) ) {
        printf("Max string length of %i was reached, characters beyond this "\
                "length have been cut off", MAX_STR_LEN);
    }

}


int main(void) {

    printf("\npresqueeze: %s", test_str1);
    squeeze(test_str1, test_str2);
    printf("\nsqueezed: %s", test_str1);

}