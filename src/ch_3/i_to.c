/* <h

Converts chars into specified base character strings.

/h> */


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LEN_CHAR 50

// reverses a string `s` in place
void reverse(char s[]);
// converts each digit in `n` into a char in `s` in base 10
void i_to_a(char n, char s[]);
// converts each digit in `n` into a char in `s` in any base
void i_to_b(char n, char s[], int b);

// the number to convert into a string
char n;
// the string as converted from `n`
char s[MAX_LEN_CHAR];
// iterators
int i, i2;
// placeholder
int tmp;
// the sign of `n`
int sign;
// the maximum chars for a given base by index
char base_chars[36] = "0123456789abcdefghijklmnopqrstuvwxyz";


void reverse(char s[]) {

// Reverses a string `s` in place
//
// Inputs
//   `s`: string whose chars to reverse

    for (i = 0, i2 = strlen(s) - 1; i < i2; i++, i2--) {
        tmp = s[i];
        s[i] = s[i2];
        s[i2] = tmp;
    }

}


void i_to_a(char n, char s[]) {
    
    // Converts each digit in `n` into a char in `s` in base 10
    //
    // Inputs
    //   `n`: number whose digits to convert to string
    //   `s`: string containing digits from `n`

    // We'll supply the digits of `n` to `s` in reverse order, and then
    // reverse `s`.
    

    sign = n;  // sign of `n`

    // Get digits in reverse order until dividing `n` by 10 yields 0.
    do {
        s[i++] = abs(n % 10) + '0';
    } while (n /= 10);

    // Close and reverse `s`.
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);

}


void i_to_b(char n, char s[], int b) {
    
    // Converts each digit in `n` into a char in `s` in base `b`
    //
    // Supports bases from base 2-36
    //
    // Inputs
    //   `n`: number whose digits to convert to string
    //   `s`: string containing digits from `n`
    //   `b`: the number base used to convert each digit in `n` to a char

    // We'll supply the digits of `n` to `s` in reverse order, and then
    // reverse `s`.
    

    sign = n;  // sign of `n`

    // Get digits in reverse order until dividing `n` by 10 yields 0.
    do {
        s[i++] = base_chars[abs(n % b)];
    } while (n /= b);

    // Close and reverse `s`.
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);

}


int main(void) {

    i_to_b(n=64, s, 16);
    printf("\n%s", s);

}