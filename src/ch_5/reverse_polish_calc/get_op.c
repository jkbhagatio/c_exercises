/* <h

Gets the next operator or operand from the command line input arg for the 
calculator.

*Note: We have error-checking in `reverse_polish_calc/main()` so don't need it 
here.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "reverse_polish_calc.h"


char get_op(char *op) {
// Gets the next operator or operand from the input string for the calculator.

    // Check if `op` is a '+' or '-' prefix.
    if ( (*op == '-') || (*op == '+') ) {  // check for leading '+' or '-'
        *++op;
        if ((isdigit(*op)) || (*op == '.')) {  // number
            return NUMBER;
        } else {  // `+` or `-` operator.
            return *--op;
        }
    } else if ((isdigit(*op)) || (*op == '.')) {  // number
        return NUMBER;
    } else if (isalpha(*op)) {  // special op
        return BUILTIN_MATH;  
    } else {  // it's a normal math operator or escape sequence
        return *op;
    }
}