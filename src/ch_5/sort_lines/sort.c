/* <h

Sorts input strings.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sort_lines.h"


void swap(void **, int, int);
int numcmp(char *, char *);


void my_qsort(void *array[], int left, int right, \
              int (*fcomp)(void *, void *)) {
// "Quicksort" algorithm to sort values (of any datatype) in `array`.

    int i;     // iterator
    int last;  // most recent left-most swapped element
    int pivot = (left + right) / 2;  // pivot element
    // Do nothing if array has less than two elements
    if (left >= right) {
        return;
    }
    // Move pivot to left.
    swap(array, left, pivot);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if ((*fcomp)(array[i], array[left]) < 0) {
            swap(array, ++last, i);
        }
    }
    // Restore pivot (so everything to left is < and to right is >=).
    swap(array, left, last);
    // Sort elements to left of pivot.
    my_qsort(array, left, last - 1, fcomp);
    // Sort elements to right of pivot.
    my_qsort(array, last + 1, right, fcomp);
}


void swap(void *array[], int i, int j) {
// Swaps pointers to two strings in a string pointer array.

    void *temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}


int numcmp(char *s1, char *s2) {
// Numerical comparison of two strings.
//
// Converts strings to doubles and performs `strcmp`-like comparison.

    double v1, v2;

    // Convert strings to double vals.
    v1 = atof(s1);
    v2 = atof(s2);

    // Perform comparison.
    if (v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    } else {
        return 0;
    }
}
