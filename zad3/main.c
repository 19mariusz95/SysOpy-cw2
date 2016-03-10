#include <stdio.h>
#include <stdlib.h>
char trololo[][6] = {"set read lock", "set write lock", "show locked chars", "unlock", "read char", "write char"};

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("You have to specify file path");
        exit(1);
    }
    char *filename = argv[1];
    FILE *file = fopen(filename, "rw");
    if (file) {

    } else {
        printf("Trololololo\n");
        exit(1);
    }
    return 0;
}