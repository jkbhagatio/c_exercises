/* <h

Gets a word from an input file.

@todo: change code within main `while` to switch-case, and change formatting of `{}`

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

enum {MAX_CH_WORD = 100};
// maximum chars in the char buffer
enum {MAX_CH_OP = 100};
// char buffer
char buf[MAX_CH_OP];
// index to buf
int i_buf = 0;

int get_word(char *word, int lim) {

    int c, c2;       // placeholder chars
    char *w = word;  // pointer to beginning of `word`
    // gets next char from `buf` or `getchar()`
    #define get_next_ch(c, buf, i) (c = (i > 0) ? buf[--i] : getchar())

    // Skip non-alphabetic chars, white space, strings, comments, and 
    // preprocessor directives.
    get_next_ch(c, buf, i_buf);
    while (!isalpha(c)) {
        if (isspace(c)) {                                // skip white space
            while (isspace(c)) {                            
                if (c == '\n') {                         // return new line
                    return c; }
                else {
                    get_next_ch(c, buf, i_buf); }}}
        else if (c == '\"' || c == '\'')  {             // skip strings
            c2 = c;
            do {
                get_next_ch(c, buf, i_buf); }
            while (c != c2);
            get_next_ch(c, buf, i_buf); }
        else if (c == '/') {                            // skip comments
            if (get_next_ch(c2, buf, i_buf) == '/') {   // skip `//` comments
                while (get_next_ch(c, buf, i_buf) != '\n'); }
            else if (c2 == '*') {                       // skip `/*` comments
                while (1) {
                    get_next_ch(c, buf, i_buf);
                    if (c == '*') {
                        if (get_next_ch(c2, buf, i_buf) == '/') {
                            break; } 
                        else {  // replace `c2`
                            buf[i_buf++] = c2; }}}} 
            else {  // replace `c2`
                buf[i_buf++] = c2; }}
        else if (c == '#' ) {                           // skip to white space
            while (!isspace(get_next_ch(c, buf, i_buf))); }
        else if (c == '<') {                            // skip to `>`
            while ((get_next_ch(c, buf, i_buf)) != '>'); }
        else if (c == EOF) {                            // return EOF
            return c; }
        else {
            get_next_ch(c, buf, i_buf); }}

    // Get word.
    *w = c;
    while (--lim) {
        get_next_ch(*++w, buf, i_buf);
        // Break on non-alpha, non-underscore, non-single quote.
        if (!isalnum(*w) && !(*w == '_') && !(*w == '\'')) {
            buf[i_buf++] = *w;  // put char back on buffer
            break; }}

    if (lim == 0) {
        printf("Warning: Max word length limit (%i) reached", MAX_CH_WORD);
    }

    // Close string.
    *w = '\0';
    return word[0]; }