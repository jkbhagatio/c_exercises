/* <h

A minimal implementation of `scanf`. 

An example of processing a variable-length arg list. Calls `scanf` to do the
actual scanning.

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

// max word length when scanning input
enum { MAX_WORD_LEN = 50 };

int my_scanf(char *f_str, ...);


int my_scanf(char *f_str, ...) {

    // Skip white space.
    // Return when input fails to match spec, or when input string is 
    // exhausted.

    // arg pointer
    va_list arg_p;
    // char placeholder
    char c;
    // str pointer placeholder
    char *s;
    // count of number of matches of spec to input
    int match_ct = 0;
    // placeholder word when scanning input
    char word[MAX_WORD_LEN];
    // pointer to `word`
    char *p_word = word;
    // pointer to `p_word` (used to reset `p_word` after each read word)
    char *p0_word = p_word;
    int word_ct = 0;

    // Point to the first unnamed arg.
    va_start(arg_p, f_str);
    do {
        if (*f_str != '%') {  // skip non '%'
            continue; }
        // Get the current word.
        while (!isspace(*p_word++ = c = getchar())); 
        *(--p_word) = '\0';
        // If *f_str == '%', get proper spec, and assign to current arg
        switch (*++f_str) {
            case 'd' : case 'i' :
                *va_arg(arg_p, int *) = atoi(word);
                match_ct++;
                break;
            case 'f':
                *va_arg(arg_p, double *) = strtod(word, &s);
                match_ct++;
                break;
            // todo: this doesn't break, but it doesn't work:
            case 's':
                *va_arg(arg_p, char **) = word;
                break;
            default:
                break; }
        // Move to the start of the next word in the input.
        while (isspace(c = getchar()));
        ungetc(c, stdin);
        // Reset word pointer.
        p_word = p0_word;
    } while (*++f_str);
    
    // Clean up.
    va_end(arg_p); 
    return match_ct; }


int main (void) {
    int i1, i2, i3, ct;
    char s1[MAX_WORD_LEN], s2[MAX_WORD_LEN];
    ct = my_scanf("%i %i %i", &i1, &i2, &i3);
    printf("\n%i\n%i\n%i\nct: %i\n", i1, i2, i3, ct);
    // Seek back to beginning of file.
    fseek(stdin, 0, 0);
    ct = my_scanf("%i %i %i %s %s", &i1, &i2, &i3, s1, s2);
    printf("\n%i\n%i\n%i\n%s\n%s\nct: %i\n", i1, i2, i3, s1, s2, ct);
}

