/* <h

Header file for `reverse_polish_calc`. Declares some constants and seven 
functions that exist in the `stack`, `get_op`, and `utils` source files.

/h> */

#ifndef REVERSE_POLISH_CALC_H
#define REVERSE_POLISH_CALC_H

// indicates that the string just read is a digit
#define NUMBER 'N'
// indicates that the string just read is a built-in math operation
#define BUILTIN_MATH 'M' 

void push_op(double);           // in `stack`
double pop_op(void);            // in `stack`
void special_ops(char);         // in `stack`
char get_op(char *);            // in `get_op`
double str_to_double(char []);  // in `utils`

#endif