/* <h

Implements table look up via hash search.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define N_ENTRIES 1001
// table entry
struct entry {
    struct entry *next;  // next entry in table
    char *name;          // name
    char *val; };        // value
// pointer table
static struct entry *table[N_ENTRIES];

// searches for a name in the table
struct entry * lookup(char *);
// records a name and value in the table
struct entry * install(char *, char *);
// hashes a value for a string
unsigned hash(char *);


int main(int argc, char *argv[]) {
    
    
    return 0; }


struct entry * lookup(char *name) {

    struct entry *p_entry;

    for (p_entry = )
}


unsigned hash (char *name) {

    unsigned hash_val;

    for (hash_val = 0; *name != '\0'; name++) {
        
    }
}


// struct entry * install(char *name, char *val) {

//     struct entry *p_entry;
//     unsigned hash_val;
//     char *word_cp;

//     // If name not found in table, create entry.
//     if ((p_entry = lookup(name)) == NULL) {
//         p_entry = (struct entry *) malloc(sizeof(*p_entry));
//         word_cp = (char *) malloc(strlen(name) + 1);
//         if (p_entry == NULL)
//     }
    
//     word_cp = (char *) malloc(strlen(word) + 1);
//     strcpy(word_cp, word);
// }