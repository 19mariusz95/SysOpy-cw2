#include <stdio.h>

void find(char *path, char *privileges);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("%s\n", "You have to input all arguments");
        return 1;
    }
    char *path = argv[1];
    char *access_privileges = argv[2];

    find(path, access_privileges);

    return 0;
}

void find(char *path, char *privileges) {
    
}