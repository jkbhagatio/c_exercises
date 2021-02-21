/* <h

Implements popping from and pushing to the stack for the calculator.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include "reverse_polish_calc.h"

// maximum stack length
#define MAX_STACK_LEN 100
// the stack
double stack[MAX_STACK_LEN];


void push_op(double op) {
// Pushes a value onto the stack.
//
// Inputs
//   `op`: a value (either an operand or the result from an operation)

    extern int i_stack;
    if (i_stack >= MAX_STACK_LEN) {
        fprintf(stderr, "\nError: Calculator max stack length (%i) "\
                "exceeded.\n", MAX_STACK_LEN);
        exit(1);
    }
    stack[i_stack++] = op;
}


double pop_op(void) {
// Pops a value from the stack (an operand for an operation, or the end result)

    extern int i_stack;
    if (i_stack <= 0) {
        fprintf(stderr, "\nError: Calculator tried to pop value from an "\
                "empty stack.\n");
        exit(1);
    }
    return stack[--i_stack];
}


void special_ops(char c) {
// Performs some special operations on the stack.
//
// Inputs
//   `c`: a char signal indicating the operation to perform.

    extern int i_stack;
    switch (c) {
        case 'P':  // print top
            printf("\nTop of stack is: %g", stack[i_stack]);
            break;
        case 'D':  // duplicate top
            printf("\nDuplicating top of stack (%g).", stack[i_stack]);
            push_op(stack[i_stack]);
            break;
        case 'S':  // swap top two
            printf("\nSwapping top two stack vals (%g <-> %g).", \
                   stack[i_stack], stack[i_stack - 1]);
            stack[i_stack] = stack[i_stack] + stack[i_stack - 1];
            stack[i_stack - 1] = stack[i_stack] - stack[i_stack - 1];
            stack[i_stack] = stack[i_stack] - stack[i_stack - 1];
            break;
        case 'C':  // clear stack
            printf("\nClearing stack.");
            i_stack = 0;
            break;
        default:
            fprintf(stderr, "\nError: Calculator has no support for char "\
                    "'%c'", c);
            exit(1);
    }
}