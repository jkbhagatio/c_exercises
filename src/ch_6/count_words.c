/* <h

Counts the occurrences of all words in a text file.

Implements a binary tree of sorted words via structs.

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
// flag to print line numbers words were found on
int printlines = 0;
// the number of times the word with the most repeats was found in the input
int max_repeat = 1;
// max word length of all words found
int max_word_len = 0;
// current line number being read
int cur_line_num = 1;
// placeholder int
int i;
// words to skip when reading from input
char *skip_words[];

// adds new node to tree, or updates an existing node
struct node * add_node(struct node *p_node, char *word);
// prints the tree alphabetically
void print_tree_a(struct node *root);
// prints the tree by word counts
void print_tree_c(struct node *root);


int main(int argc, char *argv[]) {
    
    // Get input flags.
    char **p_argv = argv;
    while (*++p_argv) {
        if (strcmp(*p_argv, "-sort") == 0) {
            if (strcmp(*++p_argv, "c") == 0) {
                sort_by_count = 1; }}
        else if (strcmp(*p_argv, "-printlines") == 0) {
            printlines = 1; }
        else if (strcmp(*p_argv, "-skip") == 0)
            if (strcmp(*++p_argv, "default") == 0) {
                char *skip_words[] = {"a", "is", "of", "the", "by"};
            }}

    // Add nodes to tree recursively while reading input.
    root = NULL;
    while ((i = get_word(word, WORD_LEN_LIM)) != EOF) {
        // On new lines, increment `cur_line_num` and continue.
        if (printlines && (i == '\n')) {
            cur_line_num++; 
            continue; }
        root = add_node(root, word); }

    // Print tree.
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
        print_tree_a(root); }
    
    printf("\n");
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
        if (word_cp != NULL) {
            strcpy(word_cp, word); }
        p_node->word = word_cp;
        p_node->count = 1;
        p_node->left = p_node->right = NULL;
        // Store line number, and add pointer to it to node.
        if (printlines) {
            line_nums = (int *) malloc(sizeof(int) * N_REPEATS_LIM);
            *line_nums = cur_line_num;
            p_node->line = line_nums; }
            // *line_nums++ = cur_line_num; }
        if ( (i = strlen(word)) > max_word_len) {
            max_word_len = i; }}
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

    if (p_node != NULL) {
        print_tree_a(p_node->left);
        printf("\n%3i       %*s", p_node->count, max_word_len, \
               p_node->word);
        if (printlines) {
            while (*(p_node->line)) {
                printf("%i ", (*(p_node->line)--)); }
        }
        print_tree_a(p_node->right); }}
 

void print_tree_c(struct node *p_node) {

    if (p_node != NULL) {
        print_tree_c(p_node->left);
        if (p_node->count == max_repeat) {
            printf("\n%3i    %*s        ", p_node->count, max_word_len, \
                   p_node->word);
            if (printlines) {
                while (*(p_node->line)) {
                    printf("%i ", (*(p_node->line)--)); }}}
        print_tree_c(p_node->right); }}
