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

    int fd = open(path,O_RDONLY);
    if (fd<0) {
        printf("File not opened");
        exit(1);
    }

    long end;
    struct record *tmp = malloc(sizeof(struct record));
    struct record *tmp2 = malloc(sizeof(struct record));
    tmp->tmp = malloc(length * sizeof(char));
    tmp2->tmp = malloc(length * sizeof(char));

    lseek(fd, 0L, SEEK_END);
    end = lseek(fd,0,SEEK_CUR);
    lseek(fd, 0l, SEEK_SET);

    int cnt = 0;
    int i;
    for (i = 1; i * length < end; i++) {
        lseek(fd, SEEK_SET, length * (i - 1));
        printf("%ld %d ", lseek(fd,0,SEEK_CUR), length * (i - 1));
        tmp->length = (size_t) read(fd, tmp->tmp, (size_t) length);
        tmp2->length = (size_t) read(fd, tmp2->tmp, (size_t) length);
        printf("%c %c\n", tmp->tmp[0], tmp2->tmp[0]);
        if (tmp->tmp[0] > tmp2->tmp[0]) {
            //printf("%d %s",cnt++,"sth wrong\n");
        }
    }

    close(fd);
    return 0;
}