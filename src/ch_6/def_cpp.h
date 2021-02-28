/* <h

Header file for `def_cpp`. 

/h> */

#ifndef DEF_CPP_H
#define DEF_CPP_H

// reads word from input: special case for `#define`s
int get_defines(char *, int);
// installs a name and value in the table
struct entry * install(char *, char *);
// looks up a name in the table
struct entry * lookup(char *);
// hashes a value for a string
unsigned hash(char *);
// uninstalls a name and value from the table
void uninstall(char *);

#endif
