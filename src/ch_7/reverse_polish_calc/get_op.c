/* <h

Gets the next operator or operand from the input string for the calculator
using `scanf`.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "reverse_polish_calc.h"

// current operator or operand being read by `scanf`
char *cur_op;
// placeholder
int n;


char get_op(void) {
// Gets the next operator or operand from the input string for the calculator.

    scanf("%s", cur_op);

    if (isdigit(cur_op[0])) {
        for (n = 0; n <= strlen(cur_op); n++) {
            str_op[n] = cur_op[n]; }
        return NUMBER;
    }

    // Check if `cur_op` is a '+' or '-' or '.' prefix.
    if ( (cur_op[0] == '-') || (cur_op[0] == '+') || (cur_op[0] == '.') ) {
        if (isdigit(cur_op[1])) {
            for (n = 0; n <= strlen(cur_op); n++) {
                str_op[n] = cur_op[n]; }
            return NUMBER;
        } else {
            return cur_op[0];
        }
    }

    // If `cur_ch` isn't a digit or decimal, it's an operator.
    if (!isalpha(cur_op[0])) {  // if it's a simple math operator
        return cur_op[0]; }
    else {  // it's an escape sequence, special op, or math function
        if (cur_op[1] == '\0') { // escape sequence or special op
            return cur_op[0]; }
        else {
            return BUILTIN_MATH; }}}
