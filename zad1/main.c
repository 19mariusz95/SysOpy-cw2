#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sortlib(char *path, int length);

void sortsys(char *path, int length);

int main(int argc, char *argv[]) {

    if (argc < 4) {
        printf("%s\n", "You have to input all arguments");
        return 1;
    }
    char *path = argv[1];
    int length = atoi(argv[2]);
    char *fun = argv[3];

    if (length == 0 || strcmp(argv[2], "0") == 0) {
        printf("%s\n", "Record's length is not correct");
        return 1;
    }
    if (!strcmp(fun, "lib") == 0 && !strcmp(fun, "sys") == 0) {
        printf("%s\n", "Bad function");
        return 1;
    }

    if (strcmp(fun, "lib") == 0) {
        sortlib(path, length);
    } else {
        sortsys(path, length);
    }


    return 0;
}

void sortsys(char *path, int length) {
    printf("%s\n", "Trolololololo");
}

void sortlib(char *path, int length) {
    printf("%s\n", "Trolololololo");
}