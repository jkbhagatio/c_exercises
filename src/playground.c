
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>


char c = 'l';
char s[] = "hello";
char s2[] = "hola1";
unsigned char u;
unsigned char x = 0;
int n = 3;
int p = 3;
int nbits;
int f;
int mask;


int main(void) {

  // We'll do an exclusive-or b/w `x` and a mask.
  
  // Create a mask whose last `n` bits are ones, and all others zeros.
  mask = ~(~0 << n);
  // Shift mask so the `n` one-bits align with the bits in `x` we want to flip.
  mask = mask << ( (sizeof(x) * 8) - (p + n) );
  // Flip em with exclusive-or.
  f =  x ^ mask;

  printf("%i", sizeof(x) * 8 - (p + n));

}
