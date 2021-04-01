/* <h

An implementation of the Linux command, `cat`, for file concatenation. 

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>

// file pointer
FILE *fp;

// copies `ifp` to `ofp`
void filecopy(FILE *ifp, FILE *ofp);


int main(int argc, char *argv[]) {
    
    if (argc == 1)  {// no args: copy stdi
        filecopy(stdin, stdout); }
    else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {  // if can't open file
                fprintf(stderr, "\nCan't open file '%s'\n", *argv);
                return 1; }
            else {
                filecopy(fp, stdout);
                fclose(fp); }}}}


void filecopy(FILE *ifp, FILE *ofp) {

    int c;
    while ((c = getc(ifp)) != EOF) {
        putc(c, ofp); }}
