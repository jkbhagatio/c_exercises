/* <h

Implements a rudimentary storage allocator.

/h> */

#include <stdio.h>
#include <stdlib.h>

// number of elements of available storage space
#define ALLOC_SIZE 100000
// storage
static char alloc_buf[ALLOC_SIZE];
// pointer position in `alloc_buf`
static char *allocp = alloc_buf;

char * my_alloc(int n) {
// Returns a pointer to `alloc_buf`

    // If within storage limit, update `allocp` and return pointer to the 
    // beginning of the newly allocated space.
    if (alloc_buf + ALLOC_SIZE - allocp >= n) {
        allocp += n;  
        return allocp - n;
    } else {
        return NULL;
    }
}

void my_free(char *p) {
// Free storage pointed to by pointer `p`.

    // If `p` is somewhere within `alloc_buf`, set `allocp` to `p`.
    if ( (p >= alloc_buf) && (p < (alloc_buf + ALLOC_SIZE)) ) {
        allocp = p;
    }
}
