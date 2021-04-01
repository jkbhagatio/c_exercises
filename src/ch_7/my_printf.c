/* <h

A minimal implementation of `printf`. 

An example of processing a variable-length arg list. Calls `printf` to do the 
actual printing.

Format specifiers:
------------------

%a                           : hexadecimal float
%c                           : char
%d OR %i                     : signed int (by default, long)
%e                           : float (double), sci notation format
%f                           : float (double), extended notation format
%g                           : use the shortest representation: %e or %f
%hh                          : char
%h                           : short
%l                           : long
%ll                          : long long
%L                           : long double
%n                           : prints nothing
%o                           : octal (by default, long)
%p                           : pointer address
%s                           : string (char arrays)
%t                           : ptrdiff_t
%u                           : unsigned int (by default, long)
%x                           : hexadecimal int (by default, long)
%z                           : size_t
%%                           : prints '%'

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>

void my_printf(char *f_str, ...);


void my_printf(char *f_str, ...) {

    // arg pointer
    va_list arg_p;
    // int to be printed for a `%i` or `%d` format spec
    int i;
    // double to be printed for a `%f` format spec
    double d;
    // char to be printed for a `%c` format spec
    char c;
    // pointer to chars in string for a `%s` format spec
    char *s;

    // Point to the first unnamed arg.
    va_start(arg_p, f_str);
    do {
        if (*f_str != '%') {  // skip non '%'
            putchar(*f_str);
            continue; }

        // If *f_str == '%', get proper spec
        switch (*++f_str) {
            case 'd' : case 'i' :
                i = va_arg(arg_p, int);
                printf("%i", i);
                break;
            case 'f':
                d = va_arg(arg_p, double);
                printf("%f", d);
                break;
            case 'g':
                d = va_arg(arg_p, double);
                printf("%g", d);
                break;
            case 'c':
                // *note*: char is promoted to int when passed thru `...`
                c = va_arg(arg_p, int);
                putchar(c);
                break;
            case 's':
                for (s = va_arg(arg_p, char *); *s; *s++) {
                    putchar(*s); }
                break;
            default:
                putchar(*f_str); }
    } while (*++f_str);
    
    // Clean up.
    va_end(arg_p); }


int main (void) {
    char str[] = "hello";
    my_printf("\n%s\n", str);
}

