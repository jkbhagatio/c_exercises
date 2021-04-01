
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


struct keyword {
    char *word;
    int count;
};
struct keyword tab[] = {  // struct array
    "auto", 0, "break", 0, "case", 0, "char", 0, "const", 0, "continue", 0,
    "default", 0, "do", 0, "double", 0, "else", 0, "enum", 0, "extern", 0, 
    "float", 0, "for", 0, "goto", 0, "if", 0, "int", 0, "long", 0,
    "register", 0, "return", 0, "short", 0, "signed", 0, "sizeof", 0, "static", 0, "struct", 0, "switch", 0, "typedef", 0, "union", 0, "unsigned", 0, "void", 0, "volatile", 0, "while", 0
};
struct keyword *p_tab = tab;
enum {N_KEYWORDS = (sizeof tab / sizeof tab[0])};
// char buffer
char buf[] = "hello";
// pointer to char buffer
char *p_buf = buf;

#define get_next_ch(a, b) (a = b ? b : getchar())

#define swap(t, x, y) \
    { x = (t) x + (t) y; \
      y = (t) x - (t) y; \
      x = (t) x - (t) y; }

int main() {

    char *lines[2];
    char buf[] = "hello";
    char * str;
    str = (char *) malloc(strlen(buf) + 1);
    strcpy(str, buf);
    lines[0] = buf;
    lines[1] = str;
    printf("\n%s", lines[0]);
    printf("\n%s", lines[1]);
}

