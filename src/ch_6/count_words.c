/* <h

Counts the occurrences of all words in a text file.

Implements a binary tree of sorted words via structs.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "count_words.h"

#define MAX_WORD_LEN 100

// struct representing node in tree. 
struct node {
    char *word;          // the word
    int count;           // count of word in source
    struct node *left;   // child node to left
    struct node *right;  // child node to right 
};
// pointer to root node
struct node *root;
// array holding current word read
char word[MAX_WORD_LEN];
// flag to indicate whether print the end tree by words according to count 
// (as opposed to alphabetically)
int sort_by_count = 0;

// adds new node to tree, or updates an existing node
struct node * add_node(struct node *p_node, char *word);
// prints the tree
void print_tree(struct node *root);


int main(int argc, char *argv[]) {
    
    // Get input flags.
    char **p_argv = argv;
    *p_argv++;
    while (--argc > 0) {
        if (strcmp(*p_argv, "-sort")) {
            if (strcmp(*++p_argv, "c")) {
                sort_by_count = 1; }}
        *p_argv++; }

    root = NULL;
    // Add nodes to tree recursively while reading input.
    while (get_word(word, MAX_WORD_LEN) != EOF) {
        root = add_node(root, word);}
    printf("\nCount:    Word:");
    printf("\n---------------");
    print_tree(root);
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
        p_node->count++; }
    // Update left node child if new word is before current node's word.
    else if ( (cmp_flag < 0)) {
        p_node->left = add_node(p_node->left, word); }
    // Update right node child if new word is after current node's word.
    else {
        p_node->right = add_node(p_node->right, word); }
    
    return p_node; }


void print_tree(struct node *p_node) {
    
    if (!sort_by_count) {
        if (p_node != NULL) {
            print_tree(p_node->left);
            printf("\n%3i       %s", p_node->count, p_node->word);
            print_tree(p_node->right); }}
    else {

    }}
