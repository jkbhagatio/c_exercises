/* <h

Reads and writes lines from some input.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sort_lines.h"

int get_line(char *, int);


int read_lines(char **p_line_ptr, int n_max_lines) {
// Reads lines from some input and adds pointer for each line to `line_ptr`

    char *p;              // pointer for current line
    char line[N_MAX_CH];  // char array for current line
    int line_len;         // length of current line
    int n_lines = 0;      // number of lines read

    // While there are still lines to be read, store line and get pointer to it
    while ((line_len = get_line(line, N_MAX_CH))) {
        if ((++n_lines >= N_MAX_LINES) || ((p = my_alloc(line_len)) == NULL)) {
            printf("Warning: Maximum storage space reached. Returning early.");
            return n_lines;
        } else {
            // Close string, removing any escape sequence.
            line[line_len - 1] = '\0';
            strcpy(p, line);
            *p_line_ptr++ = p;
        }
    }
    return n_lines;
}


int get_line(char *s, int lim) {
// Reads a line from some input into `s` and returns length.

    char *s0 = s;  // initial address of string 
    int c;  // placeholder
    // Add chars to `s` while within: char limit, file, or single line.
    while ( (lim--) && ((c = getchar()) != EOF) ) {
        if (c != '\r') {  // skip carriage returns
            *s++ = (char) c;
        }
        if (c == '\n') {  // break on new lines
            break;
        }
    }
    if (lim == 0) {
        printf("Warning: line may have been cut off: number of chars "\
               "exceeded limit of %i", lim);
    }
    return s - s0;
}



void write_lines(char **p_line_ptr, int n_lines, int rev_flag) {
// Prints out `n_lines` text lines from `line_ptr`.

    if (rev_flag) {  // print as if reverse sorted
        int n_lines_cp = n_lines;
        while (n_lines_cp--) {
            *p_line_ptr++;
        }
        while (n_lines--) {
            printf("%s\n", *--p_line_ptr);
        }
    } else {  // normal sort print
        while (n_lines--) {
            printf("%s\n", *p_line_ptr++);
        }
    }
}
