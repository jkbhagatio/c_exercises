
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

double x = 1;
int y = 2;
double *dp = &x;
int *ip = &y;
int a[10];
int *ap = &a[0];

char *pmessage = "hello world";


int main(void) {
    // printf("\ndp: %%p: %p, %%i: %i", dp, dp);
    // printf("\n*ip (%%i): %i, *ip (%%p): %p, *(ip + 1) (%%i): %i, *(ip + 1) (%%p): %p",*dp, *dp, *(dp + 1), *(dp + 1));
    // printf("\nx: %%p: %p, %%i: %i", x, x);
    // printf("\n\n%i", y = *&x);
    // a[0] = 1;
    // a[1] = 2;
    // printf("\n%i, %i.", *(ap - 1), a[-1]);
    // printf("\nip: %%p: %p, %%i: %i", ip, ip);
    // printf("\nap: %%p: %p, %%i: %i", ap, ap);


}
