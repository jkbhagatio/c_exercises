/* <h

Simulates the part of the C preprocessor that deals with `#define` statements. Reads and input (C source) file, and adds name and values to a hash table.

/h> */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "def_cpp.h"


int main(void) {

// Get word. 
// If `#define`, get next two words (name and value), put em in a string array.
// `install(name, value)`

// <s Variables
// maximum word length
#define WORD_LEN_LIM 100
// number of entries in hash table
#define N_ENTRIES 1001
// table entry template
struct entry {
    struct entry *next;  // next entry in chain of entries with same hash
    char *name;          // name
    char *val; };        // value
// table
static struct entry *table[N_ENTRIES];
// output from `get_defines`.
int word_type;
// word to compare to `"#defines"`
char word[WORD_LEN_LIM];
// name of table entry
char name[WORD_LEN_LIM]; 
// val of table entry
char val[WORD_LEN_LIM];
// table entry
struct entry *p_entry;
// iterator
int i;
// /s>

while ((word_type = get_defines(word, WORD_LEN_LIM)) != EOF) {
    if (strcmp(word, "#define") == 0) {
        get_defines(name, WORD_LEN_LIM);
        get_defines(val, WORD_LEN_LIM);
        p_entry = install(name, val);
        table[hash(name)] = p_entry; 
        word[0] = '\0'; }}

for (i = 0; i < N_ENTRIES; i++) {
    if (table[i]) {
        printf("\n Name: '%20s', Val: %s", table[i]->name, table[i]->val); }}
printf("\n");

return 0; }