#include <stdio.h>
#include <stdlib.h>

int str_end(char *s, char *t) {
// Checks if string `t` occurs at the end of string `s`.    

    // Get to end of `s` and `t`.
    while (*s++ != '\0');
    while (*t++ != '\0');
    // Compare `t` to `s` from end to beginning.
    while(*--t == *--s);
    // If we get to the start of `t`, then we know it's a match.
    if (*t == '\0') {
        return 1;
    } else {
        return 0;
    }
}

int main() {

    char *s = "hello";
    char *t = "lo";
    printf("\n%i\n", str_end(s, t));         // returns 1
    printf("\n%i", str_end("hello", "ll"));  // returns 0
}