#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generate(FILE *pFILE, int length, int n);

char *randomtext(int length);

int main(int argc, char *argv[]) {

    if (argc < 4) {
        printf("%s\n", "You have to input all arguments");
        return 1;
    }
    char *name = argv[1];
    int length = atoi(argv[2]);
    int n = atoi(argv[3]);
    if (length == 0 || strcmp(argv[2], "0") == 0) {
        printf("%s\n", "Record's length is not correct");
        return 1;
    }
    if (n == 0 || strcmp(argv[3], "0") == 0) {
        printf("%s\n", "Record's amount is not correct");
        return 1;
    }

    srand((unsigned int) time(NULL));

    FILE *file = fopen(name, "w");

    if (file) {
        generate(file, length, n);
        printf("trolololo");
    }

    if (file)
        fclose(file);

    return 0;
}

void generate(FILE *pFILE, int length, int n) {
    int i;
    for (i = 0; i < n; i++) {
        char *tmp = randomtext(length);
        fwrite(tmp, 1, (size_t) length, pFILE);
        free(tmp);
    }
}

char *randomtext(int length) {
    char *tmp = malloc((length) * sizeof(char));
    int i;
    for (i = 0; i < length; i++) {
        tmp[i] = (char) (rand() % 95 + 32);
    }
    return tmp;
}
