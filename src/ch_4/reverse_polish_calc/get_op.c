/* <h

Gets the next operator or operand from the input string for the calculator.

Pushes "read-too-far" chars (due to the nature of `getchar()`) in a buffer,
which can then be popped from. (E.g. when reading "523 437+", the '+' has to be
read for us to know that we have come to the end of the second number ('437'),
so then we need to place the '+' in a buffer so we can re-read it in future.)

*Note: We have error-checking in `reverse_polish_calc/main()` so don't need it 
here.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "reverse_polish_calc.h"

// current index in string of operand being read
int i_str = 0;
// current char from operand being read or from char buffer
char cur_ch;
// next char from operand being read or from char buffer
char next_ch;
// char buffer
char buf[MAX_CH_OP];
// current index in char buffer
int i_buf = 0;


char get_op(void) {
// Gets the next operator or operand from the input string for the calculator.

    i_str = 0;
    // Skip white space.
    cur_ch = pop_op_buf();
    while ( (cur_ch == ' ') || (cur_ch == '\t') || (cur_ch == '\v') \
            || (cur_ch == '\f') || (cur_ch == '\r') ) {
        cur_ch = pop_op_buf();
    }
    // Check if `cur_ch` is a '+' or '-' prefix.
    if ( (cur_ch == '-') || (cur_ch == '+') ) {
        if (isdigit(next_ch = pop_op_buf())) {
            str_op[i_str++] = cur_ch;
            str_op[i_str] = next_ch;
            cur_ch = next_ch;
        } else {
            push_op_buf(next_ch);
        }
    }
    // If `cur_ch` is a digit or decimal then get rest of consecutive digits.
    if ( (isdigit(cur_ch)) || (cur_ch == '.')) {
        str_op[i_str++] = cur_ch;
        while (isdigit(cur_ch = pop_op_buf())) {
            str_op[i_str++] = cur_ch;
        }
        // Close operand string.
        str_op[i_str] = '\0';
        // Put the first "read-too-far" char onto the char buffer.
        push_op_buf(cur_ch);
        return NUMBER;
    // If `cur_ch` isn't a digit or decimal, it's an operator.
    } else {
        if (!isalpha(cur_ch)) {  // if it's a simple math operator
            return cur_ch;
        } else {  // it's an escape sequence, special op, or math function
            while (isalpha(cur_ch)) {
                str_op[i_str++] = cur_ch;
                cur_ch = pop_op_buf();
            }
            push_op_buf(cur_ch);
            if (str_op[1] == 0) {  // if escape sequence or special op
                return str_op[0];
            } else {
                return BUILTIN_MATH;
            }
        }
    }
}


char pop_op_buf(void) {
// Pops char from char buffer if there is one, else calls `getchar`.

    return (i_buf > 0) ? buf[--i_buf] : getchar();
}


void push_op_buf(char c) {
// Pushes char to char buffer.
//
// Inputs
//   `c`: char to push to buffer

    if (i_buf > MAX_CH_OP) {
        fprintf(stderr, "\nError: Char buffer of calculator exceeds max "\
                "limit of %i\n", MAX_CH_OP);
        exit(1);
    }
    buf[i_buf++] = c;
}
