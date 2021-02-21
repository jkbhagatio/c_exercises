
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

// https://stackoverflow.com/questions/8824057/pointer-to-string-array-in-c

// Create a string array (2d array: array of array of chars)
char str_array[3][10] = {"hello", "hey", "hi"};
// Create a pointer to a string array equivalent to the one above
char *str_array_p[] = {"hello", "hey", "hi"};
// Create a pointer to `str_array` array
char (*p_str_array)[10] = str_array;
// Create a copy of the above pointer
char (*p_str_array_cp)[10] = str_array;
// Create a pointer to `p_str_array` pointer.
char **p_str_array_p = str_array_p;
// Create a copy of the above pointer
char **p_str_array_p_cp = str_array_p;

// Array of string arrays (3d array: array of array of array of chars)
char *array_str_array[][3] = {{"hello", "hey", "hi"}, {"bello", "bay", "bye"}};
char ***p_array_str_array = array_str_array;


int main(void) {

    // Increment the top-level of the pointer-to-array to print the second element (string) within the top level of `str_array`.

    printf("\n%s", *++p_str_array); // "hey"

    // Use the copied pointer-to-array to print the element it's pointing to, to show that this pointer and the above pointer are indeed pointing to distinct addresses.

    printf("\n%s", *p_str_array_cp);  // "hello"
    printf("\n%i", p_str_array - p_str_array_cp);  // "1"

    printf("\n");

    // Do the above but for the pointer-to-pointer and its copy.

    printf("\n%s", *++p_str_array_p);  // "hey"
    printf("\n%s", *p_str_array_p_cp);  // "hello"

    printf("\n");

    // Increment the second level of each of the above pointers to increment
    // chars within individual string elements.

    // not modifiable l-value
    printf("\n%s", *p_str_array_cp + 1);  // "ello"
    // modifiable l-value
    printf("\n%s", *p_str_array_p += 1);  // "ey"

    printf("\n");

    // We can also print from the original array and pointer-to-array.

    printf("\n%s", str_array);  // "hello"
    printf("\n%s", *(str_array_p));  // "hello"

    printf("\n");

    // And increment the pointer of the original array and the original pointer-to-array at both the top-level and second-levels. (Here we can see that `str_array_p` points to the same thing as the second level of `p_str_array_p`, which makes sense since this latter pointer was created from the former)

    // at top levels
    printf("\n%s", *(str_array + 1));  // "hey"
    printf("\n%s", *(str_array_p + 1));  // "ey"
    printf("\n%s", *p_str_array_p -= 1);  // "hey"
    printf("\n%s", *(str_array_p + 1));  // "hey"
    // at second levels
    printf("\n%s", *str_array + 1);  // "ello"
    printf("\n%s", *(str_array_p) + 1);  // "ello"

    printf("\n");

    // Play with assigning to pointers and terminating strings with null char `'\0'`    
    char str_op[100];
    char *p_str_op;
    p_str_op = str_op;
    *p_str_op++ = 'h';
    *p_str_op++ = 'i';
    *p_str_op++ = '\0';
    *(p_str_op -= 3);  // points back at `str_op[0]` ('h')
    printf("\n%c", *p_str_op);
    printf("\n%c", *(p_str_op += 1));
    printf("\n%c", *(p_str_op += 1) = 'i');
    printf("\n%s", str_op);

    printf("\n");

}
