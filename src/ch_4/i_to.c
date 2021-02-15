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

    static int i = 0, j;
    char c;

    // Get the length of the string.
    if (i == 0) {
        j = strlen(s);
    }

    // While index `i` is less than the length of the string, store `s[i]` in 
    // the temp variable `c`, and decrement `j`.
    if (strlen(s) > i) {
        c = s[i++];
        j--;
    }

    // Recursive calls until we have stored each char in `s` in a `c`.
    if (strlen(s) > i) {
        reverse(s);
    }

    // Unwrap the stored `c` values back into `s`.
    s[j++] = c;
}


void i_to_a(char n, char s[]) {  
// Converts each digit in `n` into a char in `s` in base 10
//
// Inputs
//   `n`: number whose digits to convert to string
//   `s`: string containing digits from `n`

    // We'll supply the digits of `n` to `s` in reverse order, and then
    // reverse `s`.

    static int i = 0;
    sign = n;  // sign of `n`

    // Get digits in reverse order until dividing `n` by 10 yields 0.
    while (n /= 10) {
        s[i++] = abs(n % 10) + '0';
        i_to_a(n, s);
    }
    s[i++] = abs(n % 10) + '0';  // last digit

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

    char test_str[] = "str";
    printf("\n%s", test_str);
    reverse(test_str);
    printf("\n%s", test_str);

}