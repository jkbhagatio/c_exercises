
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

// // Array of string arrays (3d array: array of array of array of chars). 
// // Because multidimensional arrays must specify bounds for all dimensions besides the first.
// char **array_str_array[] = {{"hello", "hey", "hi"}, {"bello", "bay", "bye"}};
// char *(*p_array_str_array)[3] = array_str_array;

// // Array of array of string arrays (4d array: array of array of array of array of chars)
// char *array_array_str_array[][2][2] = \
// {{{"hello", "hey"}, {"bello", "bay"}}, {{"cello", "chay"}, {"dello", "day"}}};
// char **(*p_array_array_str_array)[2] = array_array_str_array;

// char str[5] = "hello";
// char *p_str = str;

// int i = 5;

// char *str_array_p[] = {"hello", "hey", "hi"};
// char **p_str_array_p;
// *p_str_array_p = &str_array_p;

// char str_array_p[][10] = {"hello", "hey", "hi"};
// char *p_str_array_p = str_array_p[0];

// char *p_str_array_p2 = str_array_p[0];

// char s[] = "hello";
// char *p_s = s;
// char *p2_s = s;


void show(int x) {
   
   printf("Value of x is %d\n", x);
}

int main() {
   
    void (*p)(int);
    p = &show;
    (*p)(7);
    return 0;
}