/* <h

Converts a hexademical string to an integer value.

Each char in the string should convert to an integer value between 0-15.

/h> */


#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>


// maximum length of hexadecimal string
#define MAX_STR_LEN 1000

// Converts a hexademical string to an integer value.
unsigned int h_to_i(char str[]);

// the integer value of the hexadecimal string
int int_val;
// iterator
int i;
// the lowercase value of the current char
int l_c;

// a test string
char test_str[] = "FF 7F43";


unsigned int h_to_i(char str[]) {

// Converts a hexademical string to an integer value.
//
// Inputs
//   `str`: a hexadecimal string
//
// Outputs
//   `int_val`: the integer value of the hexadecimal string

    int_val = 0;
    // Skip over initial '0x' or '0X'
    if (tolower(str[1]) == 'x') {
        i = 2;
    } else {
        i = 0;
    }
    // Terminate when the null char is reached or at max string length.
    while ( (str[i] != '\0') && (i < MAX_STR_LEN) ) {
        l_c = tolower(str[i]);
        // Check if valid input (letter, digit, or space)
        if ( (l_c < 'a' || l_c > 'f') \
              && (!isdigit(str[i])) \
              && (str[i] != ' ') ) {
            fprintf(stderr, "Invalid input: %c is a non-hexadecimal value.", \
                    str[i]);
           }
        // if cur char is a digit
        if (isdigit(str[i])) {
            int_val += str[i] - '0';
        // else if cur char is a letter (i.e. not a space; we've already 
        // checked to make sure its a valid input)
        } else if (l_c != ' ') {
            int_val += l_c - 'a' + 10;
        }
        ++i;
    }
    // Print message if max string length was reached
    if (i >= (MAX_STR_LEN - 1)) {
        printf("Max string length of %i reached, characters beyond this " \
                "length have been cut off", MAX_STR_LEN);
    }
    return int_val;

}

int main(void) {


    int_val = h_to_i(test_str);
    printf("%i", int_val);

}