/* <h

Implements table look-up via hash search.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// number of entries in table
#define N_ENTRIES 1001
// table entry template
struct entry {
    struct entry *next;  // next entry in chain of entries with same hash
    char *name;          // name
    char *val; };        // value
// table
static struct entry *table[N_ENTRIES];

// installs a name and value in the table
struct entry * install(char *, char *);
// looks up a name in the table
struct entry * lookup(char *);
// hashes a value for a string
unsigned hash(char *);
// uninstalls a name and value from the table
void uninstall(char *);
// gets word from input file: special case for `#define`s
int get_defines(char *word, int lim);


struct entry * install(char *name, char *val) {

    struct entry *p_entry;
    unsigned hash_val;
    char *s;  // placeholder string

    // If name not found in table, create entry.
    if ((p_entry = lookup(name)) == NULL) {
        p_entry = (struct entry *) malloc(sizeof(*p_entry));
        s = (char *) malloc(strlen(name) + 1);
        strcpy(s, name);
        p_entry->name = s;
        hash_val = hash(name);
        p_entry->next = table[hash_val];
        table[hash_val] = p_entry; }
    // Else, free previous value.
    else {
        free( (void *) p_entry->val); }
    
    // Assign `val` to entry in table.
    s = (char *) malloc(strlen(val) + 1);
    strcpy(s, val);
    p_entry->val = s;
    
    return p_entry; }


struct entry * lookup(char *name) {

    struct entry *p_entry;

    // Look up entry (in chained entries) given hash value associated with a 
    // name.
    for (p_entry = table[hash(name)]; p_entry != NULL; \
         p_entry = p_entry->next) {
        if (strcmp(name, p_entry->name) == 0) {
            return p_entry; }}
    return NULL; }


unsigned hash (char *name) {

    unsigned hash_val;
    
    // Set a hash value for `name` as a value between 0 - `N_ENTRIES`
    for (hash_val = 0; *name != '\0'; name++) {
        hash_val = *name + (31 * hash_val); }
    return hash_val % N_ENTRIES;
}


void uninstall(char *name) {

    // place holder `entry`s for a chain of entries for `hash(name)`
    struct entry *p_entry, *p_entry2;
    // hash val for `name`
    unsigned hash_val;

    // Get `name`'s hash val, and go through chained entries for this hash val 
    // until `name` is found (at which point free the entry) or print a 
    // message if not found.
    hash_val = hash(name);
    for (p_entry = table[hash_val], p_entry2 = NULL; p_entry != NULL; \
         p_entry2 = p_entry, p_entry = p_entry->next) {
        // If a match is found...
        if (strcmp(name, p_entry->name) == 0) {
            // At the first entry in the chain...
            if (p_entry2 == NULL) {
                // Then set the hash val in the table to next entry
                table[hash_val] = p_entry->next; }
            // Else match is found somewhere later in the chain...
            else {
                // So where match is found, set the previous entry's `next`
                // to the match's `next` to bypass the match in the chain.
                p_entry2->next = p_entry->next; }
            // Free the entry (the struct AND its individual members, since space for members wasn't allocated (members were just defined as pointers) when the struct was defined).
            free(p_entry->name);
            free(p_entry->val);
            free(p_entry); }}

    printf("Warning: '%s' not found in table.", name); }


#define MAX_CH_WORD 100
// maximum chars in the char buffer
#define MAX_CH_OP 100
// char buffer
char buf[MAX_CH_OP];
// index to buf
int i_buf = 0;

int get_defines(char *word, int lim) {

    int c, c2;       // placeholder chars
    char *w = word;  // pointer to beginning of `word`
    // gets next char from `buf` or `getchar()`
    #define get_next_ch(c, buf, i) (c = (i > 0) ? buf[--i] : getchar())

    // Skip non-alphanum chars, white space, strings, and comments.
    get_next_ch(c, buf, i_buf);
    while (!isalnum(c)) {
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
        else if (c == '#' ) {                           // break on cpp dir
            break; }
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
        // Break on non-alphanumeric, non-underscore, non-single quote.
        if (!isalnum(*w) && !(*w == '_') && !(*w == '\'')) {
            buf[i_buf++] = *w;  // put char back on buffer
            break; }}

    if (lim == 0) {
        printf("Warning: Max word length limit (%i) reached", MAX_CH_WORD);
    }

    // Close string.
    *w = '\0';
    return word[0]; }