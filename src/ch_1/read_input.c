#include <stdio.h>

// Reads input from the keyboard.

int main() {
    int c;
    long nc;

	printf("%i\n", EOF);

    // fprintf(stderr, "can't open the jawn.");
    // exit(1);
    printf("%i\n", getchar());

    // while ((c = getchar()) != EOF) {
    //     putchar(c);
    // }

    nc = 0;
    while (getchar() != EOF) {
        ++nc;
        printf("%ld\n", nc);
    }
    

}
