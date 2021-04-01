/* <h

Utility functions.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// *Note* this function exists in the stdlib as `strtod`
double str_to_double(char str[]) {
// Converts a string (char array) to a double
//
// Inputs
//   `str`: string to convert to double

    // iterator
    int i;
    // sign of the number
    int sign;
    // the value of the number
    double val;
    // the decimal place of the number
    double dec;

    // Skip white space.
    for (i = 0; isspace(str[i]); i++);
    // Get sign.
    sign = (str[i] == '-') ? -1 : 1;
    // Skip a beginning '+' or '-'.
    i += (str[i] == '+' || str[i] == '-') ? 1 : 0;
    // Get mantissa value.
    for (val = 0.0; isdigit(str[i]); i++) {
        val = 10.0 * val + (str[i] - '0');
    }
    // Check for decimal.
    i += (str[i] == '.') ? 1 : 0;
    // Get decimal value.
    for (dec = 1.0; isdigit(str[i]); i++) {
        val = 10.0 * val + (str[i] - '0');
        dec *= 10.0;
    }
    return sign * val / dec;
}
