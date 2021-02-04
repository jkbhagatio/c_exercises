/* <h

Rotates the bits of a char a certain number of positions to the right.

We'll do an OR b/w left-shifted and right-shifted forms of the char.

/h> */


#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

// flips a specific number of bits `n` of `x` starting at bit index `p`.
unsigned char right_rot_bits(unsigned char x, unsigned char n);

// char whose bits to flip
unsigned char x;
// number of bits to rotate
unsigned char n;
// number of bits in `x`
unsigned char n_bits;
// right shifted form of `x`
unsigned char right_shift_x;
// left shifted form of `x`
unsigned char left_shift_x;
// return value
unsigned char y;


unsigned char right_rot_bits(unsigned char x, unsigned char n) {

// Right-rotates `n` bits of `x`.
//
// Inputs
//   `x`: int whose bits to flip
//   `n`: number of bits to rotate
//
// Outputs
//   `y`: the right-rotated `x`

    // Ensure proper inputs.
    n_bits = sizeof(x) * 8;
    if (n > n_bits || n < 0) {
        fprintf(stderr, "Invalid value for `n` (%i): must be a positive "\
                        "value less than or equal to the number of bits in "\
                        "`x`.", n);
    }

    // Do an OR b/w a left-shifted and right-shifted forms of `x`.
    right_shift_x = x >> n;
    left_shift_x = x << (n_bits - n);
    y =  right_shift_x | left_shift_x;

}


int main(void) {

    // 10101010 (170) -> 01010101 (85)
    printf("\n%i", right_rot_bits(x=170, n=3));

}