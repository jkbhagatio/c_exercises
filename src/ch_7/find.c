/* <h

An implementation of the Linux command, `find`, for finding input lines that
match some pattern from a set of given files.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// max allowed chars in a line
enum {MAX_CH_LINE = 1000};
// max number of files allowed in input
enum {MAX_N_FILES = 10};

int get_line(char *s, int lim, FILE *fp);


int main(int argc, char *argv[]) {

    // the string holding the current line being read
    char s[MAX_CH_LINE];
    // the number of lines that match
    unsigned int match_ct = 0;
    // the line number of the current match
    unsigned int line_n; 
    // flag to print line numbers
    unsigned char line_n_flag = 0;
    // flag to print nonmatches
    unsigned char except_flag = 0;
    // string containing the current input argument.
    char* arg_opt;
    // file pointer
    FILE *fp[MAX_N_FILES] = { 0 };
    FILE **pfp = fp;
    FILE **pfp0 = pfp;
    // filenames pointer
    char *fnames[MAX_N_FILES];
    char **pfnames = fnames;
    char **pfnames0 = pfnames;

    // Parse input args (option flags).
    char **p_argv = argv;
    while (--argc > 1)  {  // the final argument is the pattern to match
        arg_opt = *++p_argv;
        if (strcmp(arg_opt, "-n") == 0) {
            line_n_flag = 1;
            // Make table header.
            printf("\nFile          Line #          Line");
            printf("\n----------------------------------\n"); }
        else if (strcmp(arg_opt, "-x") == 0) {
            except_flag = 1; }
        else {  // filename
            *pfnames++ = *p_argv;
            *pfp++ = fopen(*p_argv, "r"); 
            if (*(pfp - 1) == NULL) {
                perror("Error."); }}}
    // Set `fp` to `stdin` if no files given as input args.
    if (fp[0] == NULL) { *fp = stdin; }
    *++p_argv;

    // Find matches in lines.
    do {
        line_n = 0;
        while (get_line(s, MAX_CH_LINE, *pfp0) > 0) {
            if (line_n_flag) { line_n++; }
            // Find match or nonmatch according to the nonmatch flag.
            if ((strstr(s, *p_argv) != NULL) != except_flag) {
                if (line_n_flag) { 
                    printf("%s          %u           %s", \
                           *pfnames0, line_n, s); }
                else {
                    printf("%s", s); }
                match_ct++; }}
                *pfnames0++; }
    while (*++pfp0);
    
    printf("\nNumber of matches found: %i\n", match_ct);
    return 0; }


int get_line(char *s, int lim, FILE *fp) {
// Reads a line from some input into `s` and returns its length.

    // initial address of string
    char *s0 = s; 
    // placeholder
    int c;

    // Add chars to `s` while within: char limit, file, or single line.
    while ( (lim--) && ((c = getc(fp)) != EOF) ) {
        if (c != '\r') {  // skip carriage returns
            *s++ = (char) c; }
        if (c == '\n') {  // break on new lines
            break; }}
    *s = '\0';  // close string
    if (lim == 0) {
        printf("Warning: line may have been cut off: number of chars on line "\
               "exceeded limit of %i", lim); }
    return s - s0; }
