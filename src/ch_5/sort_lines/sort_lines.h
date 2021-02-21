/* <h

Header file for `sort_lines`. Declares functions in `alloc`, `rw_lines`, and 
`sort`. 

/h> */

#ifndef SORT_LINES_H
#define SORT_LINES_H

// maximum allowed number of text lines
#define N_MAX_LINES 10000
// maximum number of chars in a line
#define N_MAX_CH 1000

int read_lines(char **, int);         // in `rw_lines`
void write_lines(char **, int, int);  // in `rw_lines`
char * my_alloc(int);  // in `alloc`
void my_free(char *);  // in `alloc`
void my_qsort(void **, int, int, int (*fcomp)(void *, void *));  // in `sort`
int numcmp(char *, char *);                                      // in `sort`

#endif
