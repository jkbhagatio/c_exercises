/* <h

Counts the occurrences of all words in a text file.

Implements a binary tree of sorted words via structs.

@todo: group by identicality
    - get all words in a string array
    - create an arbitrary number of groups (create an array of an array of strings)
    - group them by comparing each word to the previous
    - for each group, print out the strings, separate groups by a new line.
/h> */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "count_words.h"

// maximum word length
#define WORD_LEN_LIM 100
// maximum allowable repeat counts on unique lines of the input
#define N_REPEATS_LIM 100
// maximum allowable number of words to skip
#define N_SKIP_WORDS_LIM 100
// maxmimum allowable unique words
#define N_UNIQUE_WORDS_LIM 10000

// struct representing node in tree. 
struct node {
    char *word;          // the word
    int count;           // count of word in source
    struct node *left;   // child node to left
    struct node *right;  // child node to right
    int *line;           // the line(s) the word was found on
};
// pointer to root node
struct node *root;
// array holding current word read
char word[WORD_LEN_LIM];
// flag to indicate whether to print the tree by words sorted on their count 
// (as opposed to alphabetically)
int sort_by_count = 0;
// flag to indicate whether to print words grouped by similarity
int group_flag = 0;
// number of chars of similarity between words for grouping
int n_group_chars;
// flag to print line numbers words were found on
int printlines = 0;
// flag to skip words under a certain length
int min_length_flag = 0;
// words below this length will be skipped
int min_length_word;
// flag to skip certain words from input
int skip_flag = 0;
// flag to skip current word (only used if `skip_flag == 1`)
int skip_cur_word;
// words to skip when reading from input
char *skip_words[] = {"a", "is", "of", "the", "by"};
int skip_ct = 5;
char *skip_words2[N_SKIP_WORDS_LIM];
char **p_skip_words2 = skip_words2;
// the number of times the word with the most repeats was found in the input
int max_repeat = 1;
// max word length of all words found
int max_word_len = 0;
// current line number being read
int cur_line_num = 1;
// placeholder ints
int i, i2;
// placeholder char array
char *str;
// array of strings of unique words of input
char *unique_words[N_UNIQUE_WORDS_LIM];
char **p_unique_words = unique_words;
// number of unique words
int num_unique_words = 0;

// adds new node to tree, or updates an existing node
struct node * add_node(struct node *p_node, char *word);
// prints the tree alphabetically
void print_tree_a(struct node *root);
// prints the tree by word counts
void print_tree_c(struct node *root);
// prints the tree by group categories
void print_tree_groups(char **);
// returns all unique words from the tree (from the input) in a string array
void get_tree_words(struct node *root);


int main(int argc, char *argv[]) {
    
    // Get input flags.
    char **p_argv = argv;
    while (*++p_argv) {
        if (strcmp(*p_argv, "--sort") == 0) {
            if (strcmp(*++p_argv, "c") == 0) {
                sort_by_count = 1; }}
        else if (strcmp(*p_argv, "--group") == 0) {
            n_group_chars = atof(*++p_argv);
            group_flag = 1; }
        else if (strcmp(*p_argv, "--print-lines") == 0) {
            printlines = 1; }
        else if (strcmp(*p_argv, "--min-length-word") == 0) {
            min_length_flag = 1;
            min_length_word = atof(*++p_argv); } 
        else if (strcmp(*p_argv, "--skip-default") == 0) {
            skip_flag = 1; }
        else if (strcmp(*p_argv, "--skip") == 0) {  // must be final input arg
            skip_ct = 0;
            skip_flag = 2;
            while (*++p_argv) {
                str = (char *) malloc(strlen(*p_argv) + 1);
                strcpy(str, *p_argv);
                *p_skip_words2++ = str;
                skip_ct++; }
            break; }}

    // Add nodes to tree recursively while reading input.
    root = NULL;
    while ((i = get_word(word, WORD_LEN_LIM)) != EOF) {
        // On new lines, increment `cur_line_num` and continue.
        if (printlines && (i == '\n')) {
            cur_line_num++; 
            continue; }
        // Skip words if `skip_flag` specified.
        if (skip_flag == 1) {
            for (i2 = 0; i2 < skip_ct; i2++) {
                if (strcmp(word, skip_words[i2]) == 0) {
                    skip_cur_word = 1;
                    break; }}}
        if (skip_flag == 2) {
            for (i2 = 0; i2 < skip_ct; i2++) {
                if (strcmp(word, skip_words2[i2]) == 0) {
                    skip_cur_word = 1;
                    break; }}}
        if (skip_cur_word) {
            skip_cur_word = 0;
            continue; }
        if (min_length_word) {
            if (strlen(word) < min_length_word) {
                continue; }}
        root = add_node(root, word); }

    // Print tree.
    if (group_flag) {
        get_tree_words(root);
        print_tree_groups(p_unique_words);
    }
    else {
        if (printlines) {
            printf("\nCount:         Word:         Line Number(s)"); 
            printf("\n-------------------------------------------"); }
        else {
            printf("\nCount:    Word:"); 
            printf("\n---------------"); }
        if (sort_by_count) {         // print by count
            while (max_repeat) {
                print_tree_c(root);
                max_repeat--; }}
        else {                       // print alphabetically
            print_tree_a(root); }}
    
    printf("\n\n");
    return 0; }


struct node * add_node(struct node *p_node, char *word) {

    int cmp_flag;    // string comparison flag
    char *word_cp;   // placeholder array to copy `word`
    int *line_nums;  // placeholder for `p_node->line`

    // Add new node to tree.
    if (p_node == NULL) {  
        // Allocate memory for new node.
        p_node = (struct node *) malloc(sizeof(struct node));
        // Store read word, and add pointer to it to node.
        word_cp = (char *) malloc(strlen(word) + 1);
        strcpy(word_cp, word);
        p_node->word = word_cp;
        p_node->count = 1;
        p_node->left = p_node->right = NULL;
        // Store line number, and add pointer to it to node.
        if (printlines) {
            line_nums = (int *) malloc(sizeof(int) * N_REPEATS_LIM);
            *line_nums = cur_line_num;
            p_node->line = line_nums; }
        if ( (i = strlen(word)) > max_word_len) {
            max_word_len = i; }
        num_unique_words++; }
    // Update node for a repeated word.
    else if ( (cmp_flag = strcmp(word, p_node->word)) == 0) {
        p_node->count++;
        if (p_node->count > max_repeat) {
            max_repeat = p_node->count; }
        if (printlines) {
            *( (p_node->line) += 1) = cur_line_num; }}
    // Update left node child if new word is before current node's word.
    else if ( (cmp_flag < 0)) {
        p_node->left = add_node(p_node->left, word); }
    // Update right node child if new word is after current node's word.
    else {
        p_node->right = add_node(p_node->right, word); }
    
    return p_node; }


void print_tree_a(struct node *p_node) {

    // Go down the left side, then go down the right side.
    if (p_node != NULL) {
        print_tree_a(p_node->left);
        printf("\n%3i   %*s        ", p_node->count, max_word_len, \
               p_node->word);
        if (printlines) {
            while (*(p_node->line)) {
                printf("%i ", (*(p_node->line)--)); }
        }
        print_tree_a(p_node->right); }}
 

void print_tree_c(struct node *p_node) {

    // Go down the left side, then go down the right side.
    if (p_node != NULL) {
        print_tree_c(p_node->left);
        if (p_node->count == max_repeat) {
            printf("\n%3i    %*s        ", p_node->count, max_word_len, \
                   p_node->word);
            if (printlines) {
                while (*(p_node->line)) {
                    printf("%i ", (*(p_node->line)--)); }}}
        print_tree_c(p_node->right); }}


void print_tree_groups(char **words) {

    int i, i2, group_ct;
    char *c, *c2;
    int s_g_flag = 0;  // same group flag
    
    // reset `unique_words` pointer
    i = num_unique_words;
    for(; i; i--, *p_unique_words--);

    printf("\nGroup 1:");
    printf("\n--------");
    printf("\n%s", *p_unique_words++);
    group_ct = 2;
    for (i = 1; i < num_unique_words; i++) {
        i2 = n_group_chars;
        c = *p_unique_words;
        c2 = *(p_unique_words - 1);
        while (*c++ == *c2++) {
            i2--; }
        if (i2 <= 0) {
            printf("\n%s", *p_unique_words++); }
        else {  // group separator
            printf("\n\nGroup %i:", group_ct++);
            printf("\n--------");
            printf("\n%s", *p_unique_words++); }}}


void get_tree_words(struct node *p_node) {
    
    // Go down the left side, then go down the right side.
    if (p_node != NULL) {
        get_tree_words(p_node->left);
        *p_unique_words++ = p_node->word;
        get_tree_words(p_node->right); }}
