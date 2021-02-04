/* <h

Creates a histogram of the counts of the length of words from a given input.

Here, a "word" is any consecutive sequence of characters without spaces, tabs,
or newlines.

/h> */

#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LEN_LIM 50  //  the maxmimum allowable word

// gets word length
int get_word_len(int max_word_len_lim);
// makes histogram
void draw_hist(int hist_array[], int max_word_len, int max_ct);
// the array from which histogram will be made
int hist_array[MAX_WORD_LEN_LIM + 1];
// the current char being read
int c;
// the count of the word being read
int char_ct = 0;
// iterators
int i, i2, i3;
// the max word len found
int max_word_len;
// the maximum count in the histogram
int max_ct = 0;

int main() {
    // Read through input and get char count of the current word until EOF.
    while ((char_ct = get_word_len(MAX_WORD_LEN_LIM)) > -1) {
        // Add the current word length to the hist array.
        if (char_ct > 0) {
            hist_array[char_ct]++;
        }
    }
    // Get max word length and max length count from `hist_array`.
    for (i = 0; i <= MAX_WORD_LEN_LIM; i++) {
        if (hist_array[i]) {
            max_word_len = i;
            if (hist_array[i] > max_ct) {
                max_ct = hist_array[i];
            }
        }
    }
    // Draw hist.
    draw_hist(hist_array, max_word_len, max_ct);
}

int get_word_len(int max_word_len_lim) {
    char_ct = 0;
    // While not at EOF, new line, tab, or space, get next char, and...
    while (1) {
        c = getchar();
        // If carriage return, new line, tab, or space, return char count, ...
        if (c == '\r' || c == '\n' || c == '\t' || c == ' ') {
            return char_ct;
        // Else if at EOF, return -1, ...
        } else if (c == EOF) {  // this assumes EOF occurs after a blank line
            return -1;
        // Else increment char count.
        } else {
            char_ct++;
        }
        // Throw error if word exceeds length limit.
        if (char_ct >= max_word_len_lim) {
            fprintf(stderr, "The current word being read is greater than " \
                    "%i, the maximum length for allowed words.", \
                    max_word_len_lim);
        }
    }
}

void draw_hist(int hist_array[], int max_word_len, int max_ct) {
    // Draw horizontal hist.
    printf("\nHorizontal hist (x-axis = count; y-axis = word length):\n\n");
    // Loop over each word length.
    for (i = 1; i <= max_word_len; i++) { 
        printf("%i:  ", i);
        // Loop over the count number for the current word length.
        for (i2 = 1; i2 <= hist_array[i]; i2++) {
            printf("+");
        }
        // Move to next word length.
        printf("\n");
    }

    // Draw vertical hist.
    printf("\n--------------------------------------------------\n");
    printf("\nVertical hist (x-axis = word length; y-axis = count):\n\n");
    // Loop over the count numbers.
    for (i = max_ct; i >= 1; i--) {
        // Loop over the word lengths for the current count number. If 
        // the current word's length count >= current count, put "+", otherwise
        // put " ", and prettify to align with x-axis (and extra space for
        // axis numbers (word lengths) >= 10).
        for (i2 = 1; i2 <= max_word_len; i2++) {
            if (hist_array[i2] >= i && i2 < 10) {
                printf("+ ");
            } else if (hist_array[i2] >= i && i2 >= 10) {
                printf("+  ");
            } else if (hist_array[i2] < i && i2 < 10) {
                printf("  ");
            } else if (hist_array[i2] < i && i2 >= 10) {
                printf("   ");
            }
        }
        // Move to next count.
        printf("\n");
    }
    // Prettify x-axis.
    printf("\n");
    for (i = 1; i <= max_word_len; i++) {
        printf("%i ", i);
    }
    printf("\n\n");
}
