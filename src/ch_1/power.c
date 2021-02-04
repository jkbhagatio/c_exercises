/* 
<h

Creates and runs a prototype function that takes the power of an integer base 
raised to another integer.

/h> 
*/

#include <stdio.h>

// Declare power function.
int power(int base, int n);

// Call power function.
int main ()
{
    int i;
    printf(" n\t  2^n\t  -3^n\n-----------------------\n");
    for (i = 0; i < 10; i++) {
        printf("%2d\t%4d\t%6d\n", i, power(2,i), power(-3,i));
    }

}

// Define power function.
int power(int base, int n) {
    int i, p;

    p = 1;
    while(n > 0) {
        p = p * base;
        n--;
    }
    return p;
}

