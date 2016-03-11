#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct record {
    char *tmp;
    size_t length;
};

int main(int args, char *argv[]) {


    char *path = argv[1];
    int length = atoi(argv[2]);

    FILE *fd = fopen(path, "r");
    if (fd == NULL) {
        printf("File not opened");
        exit(1);
    }

    long end;
    struct record *tmp = malloc(sizeof(struct record));
    struct record *tmp2 = malloc(sizeof(struct record));
    tmp->tmp = malloc(length * sizeof(char));
    tmp2->tmp = malloc(length * sizeof(char));

    fseek(fd, 0L, SEEK_END);
    end = ftell(fd);
    fseek(fd, 0l, SEEK_SET);

    int i;
    int cnt = 0;
    for (i = 1; i * length < end; i++) {
        fseek(fd, (i - 1) * length, SEEK_SET);
        tmp->length = fread(tmp->tmp, 1, (size_t) length, fd);
        tmp2->length = fread(tmp2->tmp, 1, (size_t) length, fd);
        if (tmp->tmp[0] > tmp2->tmp[0]) {
            printf("%d %s", cnt++, "sth wrong\n");
        }
    }

    fclose(fd);
    return 0;
}