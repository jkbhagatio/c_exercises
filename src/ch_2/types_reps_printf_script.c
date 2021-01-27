/*
Playing with different datatypes and format specifiers to see implicit and
explicit representations.

Defines a bunch of variables of different types, prints these definitions, and
then prints a table with 6 columns:
1) 'x': an expression that acts on at least one of the variables
2) 'b10 spec': a `printf` format specifier that is used to print the base10
               value of 'x'
3) 'b10 val':  the base10 value that is printed when `printf` is called with 
               'x' and 'num spec'
4) 'hex spec': a `printf` format specifier that is used to print the 
               hexadecimal value of 'x'
5) 'hex val':  the hexadecimal value that is printed when `printf` is called
               with 'x' and 'hex spec'
6) 'n_bytes':  the number of bytes returned from `sizeof('x')`             


C Data Types:
-------------

char    : 8-bit, signed (can also be unsigned).
          Used for ASCII chars (0-127) or 8-bit ints.
int     : 32-bit signed int 
          (can also be 16 or 64-bit, and can also be unsigned)
float   : 32-bit float 
          (1 bit for sign, 8 bits for 'x' in '2^x', 23 bits for mantissa)
double  : 64-bit float (can also be 128-bit)
          (1 bit for sign, 11 bits for 'x' in '2^x', 32 bits for mantissa)


Data Type Qualifiers:
---------------------

bit encodings: long (32-bit, default) OR short (16-bit) OR long long (64-bit)
sign: signed (default) OR unsigned


Format specifiers:
------------------

%a                           : hexadecimal float
%c                           : char
%d OR %i                     : signed int (by default, long)
%e                           : float (double), sci notation format
%f                           : float (double), extended notation format
%g                           : use the shortest representation: %e or %f
%hh                          : char
%h                           : short
%l                           : long
%ll                          : long long
%L                           : long double
%n                           : prints nothing
%o                           : octal (by default, long)
%p                           : pointer address
%s                           : string (char arrays)
%t                           : ptrdiff_t
%u                           : unsigned int (by default, long)
%x OR %X                     : hexadecimal int (by default, long)
%z                           : size_t
%%                           : prints '%'

*Note*: format specifiers can be combined: e.g. print in short, signed int 
format with `%hi`; print in long long, hexademical format with `%llx`



Notes:
------------------------------

- ** Explicitly use the correct specs / functions for the respective data type,
  the below are examples of undefined behavior! **

- Each function can only return one specific type. e.g. `pow` (only 
  returns doubles) vs. `powf` (floats) vs. `powl` (long doubles)

- When an operation acts on two variables with different datatypes, the
  output's type is cast according to the following precedence:
  (e.g. unsigned > signed; double > float > long long > Long > short > char)

- A longer data type can be printed in a shorter format, but not vice versa.

- Confusingly, *some* format specifiers work with datatypes they weren't
  specified for, instead of throwing an error:

    - Signed vs. unsigned:
      - A signed can be printed as an unsigned with the unsigned spec, though
        not vice versa (using a signed spec with an unsigned does not change
        the printing of the signed).
    
    - Different bit encodings:
      - A negative, signed char can be printed as a short or a long, but not as
        a long long (when the long long spec is used, it prints as a long)
      - A negative, signed, short int can be printed as a long long, but not as
        a long.
      - A long int can be printed as a short int or a long long.
      - A long long int can be printed as a long or a short.

- Negative signed chars for some reason are represented in 4-byte instead of 
  1-byte.

- A float can only be printed as a double  


Todos
------

- use `*tohex` function to convert all hex representations to strings, and
  print them this way

- play with setting warnings

- go back through all examples

- review chapter 2 and make full notes here

*/

#include <stdio.h>
#include <math.h>


// Data types to play with:
// ------------------------

// Chars:
// default is 8-bit signed
char c;  // == `signed char`
signed char c_s;
unsigned char c_u;

// Ints:
// default is 32-bit signed
int i;  // == `long signed int`
short signed int i_s_s;
short unsigned int i_s_u;
long signed int i_l_s;
long unsigned int i_l_u;
long long signed int i_l_l_s;
long long unsigned int i_l_l_u;

// Float:
// can only be 32-bit signed 
float f;

// Doubles:
// default is 64-bit signed
double d;
long double d_l;

// buffer to hold hex values (up to 16 bytes)
char buf[33];

// *Note*: There's no hardware support for unsigned floats, so no support in C.

// converts a value to hex in little endian format
char *tohex(char *buf, const void *val, size_t n) {
    char *p = buf;
    const unsigned char *src = val;
    while (n --> 0) {
        p += sprintf(p, "%02X", src[n]);
    }
    return buf;
}

int main() {
    
    printf("\nDefined variables:\n");
    printf("\n    char c");
    printf("\n    signed char c_s");
    printf("\n    unsigned char c_u");
    printf("\n    int i");
    printf("\n    short signed int i_s_s");
    printf("\n    short unsigned int i_s_u");
    printf("\n    long signed int i_l_s");
    printf("\n    long unsigned int i_l_u");
    printf("\n    long long signed int i_l_l_s");
    printf("\n    long long unsigned int i_l_l_u");
    printf("\n    float f");
    printf("\n    double d");
    printf("\n    long double d_l");

    printf("\n\n\nTable of expressions:\n");
    printf("\n|                        x                        | b10 spec |"\
           "                     b10 out                     | hex spec |" \
           "      hex out      | n_bytes |");
    printf("\n_______________________________________________________________"\
           "_________________________________________________________________"\
           "_______________________");


    // <s Chars

    // Chars are represented as ints, and can be displayed in char or int 
    // format depending on the specifier.
    c = 'a';
    // display `c` as char ('a')
    printf("\n %49s %10s %49c %10s %19x %9i", \
           "c = 'a'; c {sc}", "%c", c, "%x", c, sizeof(c));
    // display `c` as int ('97')
    printf("\n %49s %10s %49i %10s %19x %9i", \
           "c = 'a'; c {sc}", "%i", c, "%x", c, sizeof(c));
    // display `97` as char ('a'): note this is represented by 4 bytes since
    // 97 is by default cast as a long int.
    printf("\n %49s %10s %49c %10s %19x %9i", \
           "97 {lsi}", "%c", 97, "%x", 97, sizeof(97));

    // Signed char precision.
    // If we set `c` so that overflow occurs, we see that, surprisingly,
    // negative chars are represented in hexadecimal with 4 bytes, even though
    // their size remains only 1 byte
    c = 128;
    printf("\n %49s %10s %49i %10s %19x %9i", \
           "c = 128; c {sc}", "%i", c, "%x", c, sizeof(c));
    // we can see that we can shorten the hex representation to 2 bytes with
    // the `%hx` spec, but `%hi` does not change the b10 representation
    printf("\n %49s %10s %49hi %10s %19hx %9i", \
           "c = 128; c {sc}", "%hi", c, "%hx", c, sizeof(c));
    c = 127;
    // when we add 1 to c, the output is a long, so no overflow
    printf("\n %49s %10s %49i %10s %19llx %9i", \
           "c = 127; c + 1 {lsi}", "%i", c + 1, "%x", c + 1, sizeof(c + 1));
    // we can also print as an unsigned, which will change the overflow 
    // behavior:
    c = 128;
    // as an unsigned, so -128 + 2^32, ...
    printf("\n %49s %10s %49u %10s %19x %9i", \
           "c = 128; c {sc}", "%u", c, "%x", c, sizeof(c));
    // or as an unsigned, so -128 + 2^32, with short hex, ...
    printf("\n %49s %10s %49u %10s %19hx %9i", \
           "c = 128; c {sc}", "%u", c, "%hx", c, sizeof(c));
    // or as an unsigned short, so -128 + 2^16, ...
    printf("\n %49s %10s %49hu %10s %19x %9i", \
           "c = 128; c {sc}", "%hu", c, "%x", c, sizeof(c));
    // but when we try as an unsigned long long, with a long long hex, neither
    // of these specs changes the printed behavior (they stay in long format)
    printf("\n %49s %10s %49llu %10s %19llx %9i", \
           "c = 128; c {sc}", "%llu", c, "%llx", c, sizeof(c));
    
    // Unsigned char precision.
    
    c_u = 255;
    printf("\n %49s %10s %49u %10s %19x %9i", \
           "c_u = 255; c {uc}", "%u", c_u, "%x", c_u, sizeof(c_u));
    // surprisingly, "%i" specifier works the same as "%u" for unsigned chars 
    // (whereas before we saw that the "%u" specifier casts signed to unsigned)
    printf("\n %49s %10s %49i %10s %19x %9i", \
           "c_u = 255; c {uc}", "%i", c_u, "%x", c_u, sizeof(c_u));
    // surprisingly, combining signed and unsigned chars yields an int??
    c = 127;
    c_u = 128;
    printf("\n %49s %10s %49i %10s %19x %9i", \
           "c = 127; c_u = 128; c + c_u {lsi}", "%i", c + c_u, "%x", \
           c + c_u, sizeof(c + c_u));

    // /s>
    

    // <s Ints

    // Ints by default are 32-bit (long) signed, but like chars, can be cast to
    // unsigned with the "%u" specifier.

    i = 2147483647;  // 2^31 - 1, max positive value of long signed int
    printf("\n %49s %10s %49i %10s %19x %9i", \
           "i = 2147483647; i {lsi}", "%i", i, "%x", i, sizeof(i));
    // trying to print den & hex as long long does not change behavior
    printf("\n %49s %10s %49lli %10s %19llx %9i", \
           "i = 2147483647; i {lsi}", "%lli", i, "%llx", i, sizeof(i));
    // printing as short int causes overflow; also surprisingly can print hex
    // in short format: this cuts off the leading '7fff' to leave only 'ffff', 
    // which is clearly not the correct representation
    printf("\n %49s %10s %49hi %10s %19hx %9i", \
           "i = 2147483647; i {lsi}", "%hi", i, "%hx", i, sizeof(i));
    // adding 1 and printing as unsigned avoids overflow, successfully prints
    // as unsigned
    printf("\n %49s %10s %49lu %10s %19x %9i", \
           "i = 2147483647; i + 1 {lsi}", "%lu", i + 1, "%x", i + 1, \
           sizeof(i + 1));
    // adding 1 and printing as long long signed avoids overflow, successfully
    // prints as long long signed, but can't print hex in long long format
    printf("\n %49s %10s %49lli %10s %19llx %9i", \
           "i = 2147483647; i + 1 {lsi}", "%lli", i + 1, "%llx", i + 1, \
           sizeof(i + 1));
    // surprisingly, adding 1 to what would overflow unsigned long int and 
    // trying to print as long long unsigned doesn't work: just overflows 
    // unsigned long int
    i_l_u = 4294967295;  // 2^32 - 1
    printf("\n %49s %10s %49llu %10s %19llx %9i", \
           "i_l_u = 4294967295; i_l_u + 1 {llu}", "%llu", i_l_u + 1, "%llx", \
           i_l_u + 1, sizeof(i_l_u + 1));
    // adding char/short unsigned int to long signed int yields long int
    c_u = 255;  // 2^8 - 1
    i_s_u = 32767;  // 2^15 - 1
    i = 1073741824;  // 2^30
    printf("\n %49s %10s %49i %10s %19x %9i", \
           "i = 1073741824; c_u = 255; i + c_u {lsi}", "%i", i + c_u, "%x", \
           i + c_u, sizeof(i + c_u));
    printf("\n %49s %10s %49i %10s %19x %9i", \
           "i = 1073741824; i_s_u = 32767; i + i_s_u {lsi}", "%i", i + i_s_u, \
           "%x", i + i_s_u, sizeof(i + i_s_u));
    // adding signed and unsigned long ints yields signed long int, avoids 
    // overflow...
    i_l_u = 1073741824;  // 2^30
    i = 1073741824;
    printf("\n %49s %10s %49lu %10s %19x %9i", \
           "i = i_l_u = 1073741824; i + i_l_u {lui}", "%lu", i + i_l_u, \
           "%x", i + i_l_u, sizeof(i + i_l_u));
    // but we can create the overflow if we specify the signed long int spec
    printf("\n %49s %10s %49i %10s %19x %9i", \
           "i = i_l_u = 1073741824; i + i_l_u {lui}", "%i", i_l_u + i, \
           "%x", i_l_u + i, sizeof(i_l_u + i));
    // adding a chart, short, or long to a long long yields a long long
    i_l_l_s = 9223370000000000000;  // ~ 2^63
    i_l_u = 4294967295;  // 2^32 - 1
    printf("\n %49s %10s %49lli %10s %19llx %9i", \
           "i_l_l_s~2^63; i_l_u=2^32-1; i_l_l_s + i_l_u {lli}", "%lli", \
           i_l_u + i_l_l_s, "%llx", i_l_u + i_l_l_s, sizeof(i_l_u + i_l_l_s));
    // surprisingly, with `pow` we can go above bit representation but there
    // is no overflow: the value is the max possible value
    i_l_l_s = pow(2, 99);
    i_l_l_u = pow(2, 99);
    printf("\n %49s %10s %49lli %10s %19llx %9i", \
           "i_l_l_s = pow(2, 99); i_l_l_s {lli}", "%lli", \
           i_l_l_s, "%llx", i_l_l_s, sizeof(i_l_l_s));
    printf("\n %49s %10s %49llu %10s %19llx %9i", \
           "i_l_l_u = pow(2, 99); i_l_l_u {llu}", "%llu", \
           i_l_l_u, "%llx", i_l_l_u, sizeof(i_l_l_u));
    // if we add one to either of these values, overflow occurs
    printf("\n %49s %10s %49lli %10s %19llx %9i", \
           "i_l_l_s + 1 {lli}", "%lli", \
           i_l_l_s + 1, "%llx", i_l_l_s + 1, sizeof(i_l_l_s + 1));
    printf("\n %49s %10s %49llu %10s %19llx %9i", \
           "i_l_l_u + 1 {llu}", "%llu", \
           i_l_l_u + 1, "%llx", i_l_l_u + 1, sizeof(i_l_l_u + 1));
    // we can also cause overflow by using a shorter format's spec
    printf("\n %49s %10s %49i %10s %19x %9i", \
           "i_l_l_s {lli}", "%i", \
           i_l_l_s, "%x", i_l_l_s, sizeof(i_l_l_s ));

    // /s>

    // <s Floats & Doubles

    // Overflow float's exponent.
    f = 3.4e38;  // ~ abs max value limit, ~ 2^128
    // print in sci notation format
    printf("\n %49s %10s %49e %10s %19x %9i", \
           "f = 3.4e38; f {f}", "%e", f, "%x", f, sizeof(f));
    // print in extended notation format
    printf("\n %49s %10s %49f %10s %19x %9i", \
           "f = 3.4e38; f {f}", "%f", f, "%x", f, sizeof(f));
    // overflow occurs.
    f = 3.5e38;
    // sci notation
    printf("\n %49s %10s %49e %10s %19x %9i", \
           "f = 3.5e38; f {f}", "%e", f, "%x", f, sizeof(f));
    // extended notation (and we can print with hex in long because `printf`
    // converts floats to doubles implicitly)
    printf("\n %49s %10s %49f %10s %19llx %9i", \
           "f = 3.5e38; f {f}", "%f", f, "%llx", f, sizeof(f));
    
    // Underflow float's exponent.
    // abs min value limit, surprisingly less than 2^-127, which is 5.9E-39
    f = 1e-39;
    printf("\n %49s %10s %49e %10s %19x %9i", \
           "f = 1e-39; f {f}", "%e", f, "%x", f, sizeof(f));
    // gradual underflow occurs.
    f = 9e-40;
    printf("\n %49s %10s %49e %10s %19x %9i", \
           "f = 9e-40; f {f}", "%e", f, "%x", f, sizeof(f));
    // abrupt underflow occurs.
    f = 1e-46;
    printf("\n %49s %10s %49e %10s %19x %9i", \
           " f = 1e-46; f {f}", "%e", f, "%x", f, sizeof(f));

    // Overflow float's mantissa.
    f = 3.1234567e38;
    // sci notation
    printf("\n %49s %10s %49e %10s %19x %9i", \
           "f = 3.1234567e38; f {f}", "%e", f, "%x", f, sizeof(f));
    // extended notation
    printf("\n %49s %10s %49f %10s %19x %9i", \
           "f = 3.1234567e38; f {f}", "%f", f, "%x", f, sizeof(f));
    // overflow occurs
    f = 3.12345678e38;
    printf("\n %49s %10s %49e %10s %19x %9zu", \
           "f = 3.12345678e38; f {f}", "%e", f, "%x", f, sizeof(f));
    printf("\n %49s %10s %49f %10s %19x %9i", \
           "f = 3.12345678e38; f {f}", "%f", f, "%x", f, sizeof(f));

    // Adding a long long to float yields a float (though the value of the long
    // long is to small to make a difference given the precision of the float 
    // mantissa)...
    i_l_l_u = pow(2, 63);
    printf("\n %49s %10s %49f %10s %19x %9zi", \
           "i_l_l_u = pow(2, 63); f + i_l_l_u {llu}", \
           "%e", f + i_l_l_u, "%x", f + i_l_l_u, sizeof(f + i_l_l_u));
    // but we can print it as a long long, with hex in long long format.
    // printf("\n %49s %10s %49llu %10s %19llx %9i", \
    //        "i_l_l_u = pow(2, 63); f + i_l_l_u {llu}", \
    //        "%llu", f + i_l_l_u, "%llx", f + i_l_l_u, sizeof(f + i_l_l_u));
    
    // overflow double's exponent.
    d = pow(2, 1023);
    printf("\n %49s %10s %49e %10s %19a %9i", \
           "d = pow(2, 1023);; d {d}", \
           "%e", d, "%a", d, sizeof(d));
    // overflow occurs.
    d = pow(2, 1024);
    printf("\n %49s %10s %49e %10s %19a %9i", \
           "d = pow(2, 1024);; d {d}", \
           "%e", d, "%a", d, sizeof(d));
    
    // overflow double's mantissa.

    // compare long double to double.
    // (for some reason, this doesn't work in Windows terminal (prints as
    // an overflowed double), but does in GNU/Linux)
    d_l = powl(2, 1024);
    printf("\n %49s %10s %49Le %10s %19La %9zi", \
           "d_l = powl(2, 1024); d_l {ld}", \
           "%Le", d_l, "%La", d_l, sizeof(d_l));   

    // overflow long double's exponent.

    // overflow long double's mantissa.

    // /s>

}

