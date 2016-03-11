#include <stdlib.h>
#include <stdio.h>

struct record {
    char *tmp;
    size_t length;
};

int main(int args, char *argv[]) {


    char *path = argv[1];
    int length = atoi(argv[2]);

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("File not opened");
        exit(1);
    }

    long end;
    struct record *tmp = malloc(sizeof(struct record));
    struct record *tmp2 = malloc(sizeof(struct record));
    tmp->tmp = malloc(length * sizeof(char));
    tmp2->tmp = malloc(length * sizeof(char));

    fseek(file, 0L, SEEK_END);
    end = ftell(file);
    fseek(file, 0l, SEEK_SET);

    int cnt = 0;
    int i;
    for (i = 1; i * length < end; i++) {
        fseek(file, SEEK_SET, length * (i - 1));
        printf("%ld %d ", ftell(file), length * (i - 1));
        tmp->length = fread(tmp->tmp, 1, (size_t) length, file);
        tmp2->length = fread(tmp2->tmp, 1, (size_t) length, file);
        printf("%c %c\n", tmp->tmp[0], tmp2->tmp[0]);
        if (tmp->tmp[0] > tmp2->tmp[0]) {
            //printf("%d %s",cnt++,"sth wrong\n");
        }
    }

    fclose(file);
    return 0;
}