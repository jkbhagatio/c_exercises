/* 
<h

Prints the reversed lines of a given text input and the length of each line.

At EOF, prints again the longest found line, reversed.

/h> 
*/

#include <stdio.h>
#include <stdlib.h>

#define LINE_CHAR_LIM 1000  //  the maxmimum # of chars in a line

// gets a line from an input
int get_line(char line[], int line_char_lim);
// reverses the chars in a line
void reverse_line(char line[], int len_line);
// the length of a line
int len_line;
// the length of the longest line
int len_longest_line = 0;
// the characters of the current line
char line[LINE_CHAR_LIM];
// the characters of the longest line (reversed)
char longest_line[LINE_CHAR_LIM];
// iterators
int i, i2, tmp;
// a single character
int c;

int main() {

    // Get lines while we are not at EOF. (We can't check directly for EOF w/
    // `getchar()` here b/c it causes issues with precedence of updating 
    // char arrays)
    while ((len_line = get_line(line, LINE_CHAR_LIM)) > 0) {
        // Reverse line.
        reverse_line(line, len_line);
        // Print out reversed line and its length.
        // (subtract 2 for for the '\n' and '\O' chars)
        printf("%s, (%i chars)", line, (len_line - 2));
        // Check length and set longest line.
        if (len_line > len_longest_line) {
            len_longest_line = len_line;
            for(i = 0; i < len_line; i++) {
                longest_line[i] = line[i];
            }
        }
    }
    printf("The longest line, reversed, was: %s (%i chars)", \
           longest_line, len_longest_line - 2);
}

int get_line(char line[], int line_char_lim) {
    
    // Search through characters until reaching EOF...
    for (i = 0; (i < line_char_lim ) && ((c = getchar()) != EOF); i++) {
        line[i] = c;
        // Or new line. If a new line is hit, break.
        if (c == '\n') {
            i++;
            break;
        }
    }
    // Add the null character to the end of the line.
    line[i] = '\0';  
    return i;
}

void reverse_line(char line[], int len_line) {

    i2 = len_line - 1;
    for (i = 0; i < (len_line / 2); i++) {
        tmp = line[i];
        line[i] = line[i2];
        line[i2] = tmp;
        i2--;
    }
}