/* <h

Compares a set of files, printing the first line of each where they are not all the same.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// max allowed chars in a line
enum {MAX_CH_LINE = 1000};
// max number of files allowed in input
enum {MAX_N_FILES = 10};


int main(int argc, char *argv[]) {

    // the string holding the current line being read
    char buf[MAX_CH_LINE];
    // placeholder int
    int i;
    // file pointer
    FILE *fp[MAX_N_FILES] = { 0 };
    FILE **pfp = fp;
    // filenames pointer
    char *fnames[MAX_N_FILES];
    char **pfnames = fnames;
    // strings of lines
    char *lines[MAX_N_FILES];
    // number of files to compare
    unsigned int n_files = 0;
    // line number
    unsigned int line_n = 0;
    // flag for matching lines
    int lines_match = 1;

    // Parse input args to get filenames and open files.
    char **p_argv = argv;
    while (--argc)  {
        n_files++;
        *pfnames++ = *++p_argv;
        *pfp++ = fopen(*p_argv, "r"); 
        if (*(pfp - 1) == NULL) {perror("Error."); }}

    // Compare lines across files
    while (lines_match) {
        line_n++;
        // Get lines.
        for (i = 0; i < n_files; i++) {
            fgets(buf, MAX_CH_LINE, fp[i]);
            lines[i] = strdup(buf); }
            // `strdup` above calls `malloc` to allocate space. equivalent to:
            // ```
            // char * str;
            // str = (char *) malloc(strlen(buf) + 1);
            // strcpy(str, buf);
            // lines[i] = str;
            // ```
        // Compare lines.
        for (i = (n_files - 1); i >= 1; i--) {
            if (strcmp(lines[i], lines[i - 1]) != 0) {
                lines_match = 0;
                break; }}}

    printf("\nFiles mismatched on respective line %u:\n", line_n);
    for (i = 0; i < n_files; i++) {
        printf("File '%s' line %u: %s", fnames[i], line_n, lines[i]); }}
