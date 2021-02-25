/* <h

Counts the occurrences of C keywords in a C source file.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

// struct definition
struct keyword {
    char *word;
    int count;
};
// struct array
struct keyword tab[] = {
    "auto", 0, "break", 0, "case", 0, "char", 0, "const", 0, "continue", 0,
    "default", 0, "do", 0, "double", 0, "else", 0, "enum", 0, "extern", 0, 
    "float", 0, "for", 0, "goto", 0, "if", 0, "int", 0, "long", 0,
    "register", 0, "return", 0, "short", 0, "signed", 0, "sizeof", 0, "static", 0, "struct", 0, "switch", 0, "typedef", 0, "union", 0, "unsigned", 0, "void", 0, "volatile", 0, "while", 0
};
// pointer to struct array
struct keyword *p_tab = tab;
// number of keywords
enum {N_KEYWORDS = (sizeof tab / sizeof tab[0])};
// maximum chars in a word
enum {MAX_CH_WORD = 100};
// maximum chars in the char buffer
enum {MAX_CH_OP = 100};
// char buffer
char buf[MAX_CH_OP];
// index to buf
int i_buf = 0;

// gets a word from input
int get_word(char *, int);
// performs binary search to see if a word matches a string in `tab`
struct keyword * bin_search(char *, struct keyword *, int);

int main(void) {
    
    // index in `keyword_tab`
    int i;
    // the current word read
    char word[MAX_CH_WORD];

    // Find keywords.
    while (get_word(word, MAX_CH_WORD) != EOF) {
        if (p_tab = bin_search(word, tab, N_KEYWORDS)) {
            p_tab->count++;
        }
    }
    // Print results.
    p_tab = tab;  // set pointer back to beginning of `tab`.
    printf("\n   Keyword: \tCount:");
    printf("\n-------------------------");
    for (i = 0; i < N_KEYWORDS; i++, p_tab++) {
        printf("\n%10s: \t%3i", p_tab->word, p_tab->count);
    }
    printf("\n");
    return 0;
}


int get_word(char *word, int lim) {

    int c, c2;       // placeholder chars
    char *w = word;  // pointer to beginning of `word`
    // gets next char from `buf` or `getchar()`
    #define get_next_ch(c, buf, i) (c = (i > 0) ? buf[--i] : getchar())

    // Skip non-alphabetic chars, white space, strings, comments, and 
    // preprocessor directives.
    while (!isalpha(get_next_ch(c, buf, i_buf))) {
        if (isspace(c)) {                              // skip white space
            while (isspace(get_next_ch(c, buf, i_buf)));   
        }
        if (c == '\"' || c == '\'') {                  // skip strings
            c2 = c;
            do {
                get_next_ch(c, buf, i_buf);
            } while (c != c2);
        }
        if (c == '/') {
            if (get_next_ch(c2, buf, i_buf) == '/') {  // skip `//` comments
                while (get_next_ch(c, buf, i_buf) != '\n');
            } else if (c2 == '*') {                    // skip `/*` comments
                while (1) {
                    get_next_ch(c, buf, i_buf);
                    if (c == '*') {
                        if (get_next_ch(c2, buf, i_buf) == '/') {
                            break;
                        } else {
                        buf[i_buf++] = c2;
                        }
                    }
                }
            } else {  // replace `c2`
                buf[i_buf++] = c2;
            }
        }
        if (c == '#' ) {                               // skip to white space
            while (!isspace(get_next_ch(c, buf, i_buf)));
        }
        if (c == '<') {                                // skip to `>`
            while ((get_next_ch(c, buf, i_buf)) != '>');
        }
        // Return if EOF.
        if (c == EOF) {
            return c;
        }
    }

    // Get word.
    *w = c;
    while (--lim) {
        get_next_ch(*++w, buf, i_buf);
        // Break on non-alpha non-underscore.
        if (!isalnum(*w) && !(*w == '_')) {
            buf[i_buf++] = *w;  // put char back on buffer
            break;
        }
    }
    if (lim == 0) {
        printf("Warning: Max word length limit (%i) reached", MAX_CH_WORD);
    }

    // Close string.
    *w = '\0';
    return word[0];
}


struct keyword * bin_search(char *word, struct keyword *tab, int n) {

    int cmp_flag;  // comparison flag
    struct keyword *low = &tab[0];
    struct keyword *high = &tab[n];
    struct keyword *mid;

    while (low < high) {
        mid = low + ((high - low) / 2);
        if ( (cmp_flag = strcmp(word, mid->word)) < 0) {
            high = mid;
        } else if (cmp_flag > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return NULL;  // if matching word not found in `tab`
}
