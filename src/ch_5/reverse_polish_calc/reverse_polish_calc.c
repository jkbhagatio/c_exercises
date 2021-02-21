/* <h

Implements a calculator using Reverse Polish notation.

Operations are performed on operands (numbers) in a stack. All operations are 
binary (two operands per operation). Input is from command-line args.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "reverse_polish_calc.h"

// the current operand/operator being read
char cur_op;
// the first operand on the stack
double op1;
// the second operand on the stack.
double op2;
// current stack index
int i_stack = 0;

int main(int argc, char *argv[]) {
// Runs the calculator.

    // Create pointer to `argv`.
    char **p_argv = argv;
    // Placeholder pointer.
    char *p;

    // While next operator/operand is not EOF:
    //   If operand (i.e. number):
    //     Push it onto a stack
    //   Else if operator: 
    //     Pop all operands off stack, perform operation, push result on stack
    //   Else if LF or CR:
    //     Pop and print result (top of stack)
    //   Else:
    //     Error
    while (--argc > 0) {
        switch (cur_op = get_op(*++p_argv)) {
            case NUMBER:
                push_op(strtod(*p_argv, &p));
                break;
            case '+':
                push_op(pop_op() + pop_op());
                break;
            case '*':
                push_op(pop_op() * pop_op());
                break;
            case '-':
                op2 = pop_op();
                push_op(pop_op() - op2);
                break;
            case '/':
                op2 = pop_op();
                push_op(pop_op() - op2);
                break;
            case '%':
                op2 = pop_op();
                op1 = pop_op();
                printf("\nWarning: both operands in '%g %% %g' will be "\
                "converted to ints.", op1, op2);
                push_op((int) op1 % (int) op2);
                break;
            // Print top, duplicate top, swap top two, or clear stack.
            case 'P':  case 'D': case 'S': case 'C':
                special_ops(cur_op);
                break;
            case BUILTIN_MATH:
                if (strcmp(*p_argv, "sin") == 0) {
                    push_op(sin(pop_op()));
                } else if (strcmp(*p_argv, "exp") == 0) {
                    push_op(exp(pop_op()));
                } else if (strcmp(*p_argv, "pow") == 0) {
                    op2 = pop_op();
                    push_op(pow(pop_op(), op2));
                } else {
                    fprintf(stderr, "\nError: '%s' is not an accepted "\
                            "operation", *p_argv);
                }
                break;
            case '\n':
                printf("\n%.5g", pop_op());
                break;
            default:
                fprintf(stderr, "\nError: Unacceptable input: %c\n", cur_op);
                exit(1);
        }
    }

    // If stack isn't empty (e.g. if input ended on EOF before \n), pop it.
    if (i_stack) {
        printf("\n%.5g", pop_op());
    }
    printf("\n");
    return 0;
}
