/* <h

Plays with strings using pointers.

/h> */

#include <stdio.h>
#include <stdlib.h>

// maximum elements in a char array or file line
#define MAX_CH_SIZE 10000


void str_cat(char *s, char *t) {
// Concatenates string `t` to the end of string `s`.

    // Set `*s` one back from end of string.
    while (*++s);
    // While we're not at end of `t`, concatenate char-by-char to `s`.
    while (*s++ = *t++);

}


int str_end(char *s, char *t) {
// Checks if string `t` occurs at the end of string `s`.    

    // Get to end of `s` and `t`.
    while (*s++);
    while (*t++);
    // Compare `t` to `s` from end to beginning.
    while(*--t == *--s);
    // If we get to the start of `t`, then we know it's a match.
    if (*t == '\0') {
        return 1;
    } else {
        return 0;
    }
}


int get_line(char *s, int lim) {
// Reads a line into `s`, returns length.

    char *s0 = s;  // initial address of string 
    // Add chars to `s` while within: file, single line, or char limit.
    while ( ((*s++ = getchar()) != EOF) && (--lim > 0) && (*(s - 1) != '\n') );
    return s - s0;
}


void reverse(char *s) {
// Reverses a string `s` in place
//
// Inputs
//   `s`: string whose chars to reverse

    char c;  // placeholder char
    char *s2 = s;  // initial address of string 
    while (*++s2);  // set pointer to end of initial string
    // Swap chars of `s` via `*s` & `*s2` until they meet in the middle.
    for(--s2; s <= s2; s++, s2--) {
        c = *s;
        *s = *s2;
        *s2 = c;
    }
}

char * i_to_a(char n, char *s) {  
// Converts each digit in `n` into a char in `s` in base 10
//
// Inputs
//   `n`: number whose digits to convert to string
//   `s`: string containing digits from `n`

    // We'll supply the digits of `n` to `s` in reverse order, and then
    // reverse `s`.

    int sign = n;  // sign of `n`
    char *s0 = s;  // initial address of string
    // Get digits in reverse order until dividing `n` by 10 yields 0.
    do {
        *s++ = abs(n % 10) + '0';
    } while (n /= 10);

    // Reverse and close `s`.
    if (sign < 0) {
        *s++ = '-';
    }
    *s = '\0';
    reverse(s0);
    return s0;
}


int main() {

    char s[MAX_CH_SIZE] = "howdy";
    char t[MAX_CH_SIZE] = "boy";
    printf("\n%i", str_end(s, t));         // returns 0
    printf("\n%i", str_end("hello", "lo"));  // returns 1
    str_cat(s, t);
    printf("\n%s", s);  // returns "hellolo"
    printf("\n%i", get_line(s, MAX_CH_SIZE));
    printf("\n%s", s);
    reverse(s);
    printf("\n%s", s);
    char s2[MAX_CH_SIZE];
    printf("\n%s", i_to_a((char) 123, s));
    printf("\n");
}