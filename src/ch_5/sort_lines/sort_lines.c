/* <h

Reads and sorts text lines from some input. Writes sorted lines.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sort_lines.h"

// pointer array to text lines
char *line_ptr[N_MAX_LINES];
// pointer to `line_ptr`
char **p_line_ptr = line_ptr;

int main (int argc, char *argv[]) {
// Reads and sorts text lines. Writes sorted lines.

    int n_lines;                   // number of input lines read
    int rev_flag = 0;              // 1 if reverse sort (descending order)
    int (*fcomp)(char *, char *);  // pointer to comparison function.
    fcomp = &strcmp;               // `strcmp` by default.

    // <s Get input flags.
    // Create pointer to `argv`.
    char **p_argv = argv;
    *p_argv++;
    while (--argc > 0) {
        if (strcmp(*p_argv, "-n") == 0) {  // `numcmp` as comp function
            fcomp = &numcmp;
        } else if (strcmp(*p_argv, "-r") == 0) {  // reverse sort
            rev_flag = 1;
        } else {
            printf("Warning: Improper usage. Proper usage is "\
                    "`-n <n_lines>`. Default to `-n 10`.");
            break;
        }
        *p_argv++;
    }
    // /s>

    // Read.
    n_lines = read_lines(p_line_ptr, N_MAX_LINES);                   
    // Cast args to `fcomp` as voids and sort.
    my_qsort((void **) line_ptr, 0, n_lines - 1, \
             (int (*)(void *, void *))(fcomp));
    // Write.
    write_lines(p_line_ptr, n_lines, rev_flag);

    return 0;
}
