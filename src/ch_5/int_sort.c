/* <h

Sorts input strings.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void swap(int *, int, int);


void my_qsort(int array[], int left, int right) {
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
        if (array[i] < array[left]) {
            swap(array, ++last, i);
        }
    }
    // Restore pivot (so everything to left is < and to right is >=).
    swap(array, left, last);
    // Sort elements to left of pivot.
    my_qsort(array, left, last - 1);
    // Sort elements to right of pivot.
    my_qsort(array, last + 1, right);
}


void swap(int array[], int i, int j) {
// Swaps pointers to two strings in a string pointer array.

    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}


int main() {
    int array[] = {2, 5, 3, 4, 1};
    my_qsort(array, 0, 4);

}
