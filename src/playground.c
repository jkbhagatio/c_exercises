
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

char c = -128;
float f;

int i;

int main(void) {

    for (i = 0; i < 10; i++) {
      printf("\n%i", i);
    }

    printf("\n");

    for (i = 1; i <= 1; ++i) {
      printf("\n%i", i /= 2);
    }

}