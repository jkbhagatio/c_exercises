/* <h

Prints the last `-n` lines of its input.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// maximum allowed number of text lines
#define N_MAX_LINES 10000
// maximum number of chars in a line
#define N_MAX_CH 1000
// pointer array to text lines
char *line_ptr[N_MAX_LINES];
// pointer to `line_ptr`
char **p_line_ptr = line_ptr;
// number of elements of available storage space
#define ALLOC_SIZE 100000
// storage
static char alloc_buf[ALLOC_SIZE];
// pointer position in `alloc_buf`
static char *allocp = alloc_buf;

int read_lines(char **, int);                
int get_line(char *, int);


int main(int argc, char *argv[]) {

    // number of lines that have been read from 
    int n_lines_read;
    // number of lines to print
    int n_lines_print = 10;
    // placeholder pointers
    char *p;

    // Create pointer to `argv`.
    char **p_argv = argv;
    *p_argv++;

    // Get input flags.
    while (--argc > 0) {
        if (strcmp(*p_argv, "-n") == 0) {
            if (isdigit((*++p_argv)[0])) {
                n_lines_print = strtod(*p_argv, &p);
                break;
            } else {
                printf("Warning: Improper usage. Proper usage is "\
                       "`-n <n_lines>`. Default to `-n 10`.");
            }
        } else {
            printf("Warning: Improper usage. Proper usage is "\
                    "`-n <n_lines>`. Default to `-n 10`.");
            break;
        }
    }

    // Read lines.
    n_lines_read = read_lines(p_line_ptr, N_MAX_LINES);
    int n_lines_read_cp = n_lines_read;
    while (n_lines_read_cp--) {
        *++p_line_ptr;
    }

    // Print lines.
    while ((n_lines_print--) && (n_lines_read--)) {
        printf("%s\n", *--p_line_ptr);
    }
}


int read_lines(char **p_line_ptr, int n_max_lines) {
// Reads lines from some input and adds pointer for each line to `line_ptr`

    char *p;              // pointer for current line
    char line[N_MAX_CH];  // char array for current line
    int line_len;         // length of current line
    int n_lines = 0;      // number of lines read

    // While there are still lines to be read, store line and get pointer to it
    while (line_len = get_line(line, N_MAX_CH)) {
        p = (alloc_buf + ALLOC_SIZE - allocp >= line_len) \
            ? allocp += line_len : 0;
        if ( (++n_lines >= N_MAX_LINES) || (p == NULL) ) {
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
