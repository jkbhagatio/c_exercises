/* <h

Flips a specific number of bits of a char, starting at a certain location.

We'll do an X-OR b/w the char whose bits to flip and a mask.

/h> */


#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

// flips a specific number of bits `n` of `x` starting at bit index `p`.
unsigned char flip_bits(unsigned char x, unsigned char p, unsigned char n);

// char whose bits to flip
unsigned char x;
// position at which to start flipping bits
unsigned char p;
// number of bits to flip
unsigned char n;
// number of bits in `x`
unsigned char n_bits;
// mask used to flip bits
unsigned char mask;
// return value
unsigned char y;


unsigned char flip_bits(unsigned char x, unsigned char p, unsigned char n) {

// Flips `n` bits of `x` starting at bit index `p`.
//
// Inputs
//   `x`: int whose bits to flip
//   `p`: position at which to start flipping bits
//   `n`: number of bits to flip
//
// Outputs
//   `y`: the bit-flipped `x`

    // Ensure proper inputs.
    n_bits = sizeof(x) * 8;
    if (p + n > n_bits || p < 0 || n < 0) {
        fprintf(stderr, "Invalid values for `p` (%i) and `n` (%i): must be "\
                        "positive values that sum to less than or equal to "\
                        "the number of bits in `x`.", p, n);
    }

    // Create a mask whose last `n` bits are ones, and all others zeros.
    mask = ~(~0 << n);
    // Shift mask so the `n` one-bits align with the bits in `x` we want to
    // flip.
    mask = mask << (n_bits - (p + n));
    // Flip em with X-OR.
    y =  x ^ mask;
}


int main(void) {

    // 10101010 (170) -> 10010010 (146)
    printf("\n%i", flip_bits(x=170, p=2, n=3));
    printf("\n%x", x);

    return 0;
}