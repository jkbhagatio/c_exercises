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
// flag to indicate whether print the end tree by words according to count 
// (as opposed to alphabetically)
int sort_by_count = 0;
// flag to print line numbers words were found on
int printlines = 0;
// the number of times the word with the most repeats was found in the input
int max_repeat = 0;

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
        else if (strcmp(*p_argv, "-printlines")) {
            printlines = 1; }}

    // Add nodes to tree recursively while reading input.
    root = NULL;
    while (get_word(word, WORD_LEN_LIM) != EOF) {
        root = add_node(root, word); }

    // Print tree.
    if (printlines) {
        printf("\nCount:    Word:          Line Number"); 
        printf("\n------------------------------------"); }
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

    int cmp_flag;   // string comparison flag
    char *word_cp;  // placeholder array to copy `word`

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
        p_node->left = p_node->right = NULL; }
    // Update node for a repeated word.
    else if ( (cmp_flag = strcmp(word, p_node->word)) == 0) {
        p_node->count++;
        max_repeat++; }
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
        printf("\n%3i       %s", p_node->count, p_node->word);
        // if (printlines)
        print_tree_a(p_node->right); }}
 

void print_tree_c(struct node *p_node) {

    if (p_node != NULL) {
        print_tree_c(p_node->left);
        if (p_node->count == max_repeat) {
            printf("\n%3i       %s", p_node->count, p_node->word); }
        print_tree_c(p_node->right); }}
