#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint-gcc.h>

void sortlib(char *path, int length);

void sortsys(char *path, int length);


struct record {
    char *chars;
};


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

    clock_t time;
    struct tms *t_cpu1 = malloc(sizeof(struct tms));
    struct tms *t_cpu2 = malloc(sizeof(struct tms));
    if (t_cpu1 == NULL || t_cpu2 == NULL) {
        printf("%s", "Allocation memory failed");
        return 1;
    }

    time = times(t_cpu1);
    if (strcmp(fun, "lib") == 0) {
        sortlib(path, length);
    } else {
        sortsys(path, length);
    }

    time = times(t_cpu2) - time;

    intmax_t res[3] = {(intmax_t) time, (intmax_t) (t_cpu2->tms_utime - t_cpu1->tms_utime),
                       (intmax_t) (t_cpu2->tms_stime - t_cpu1->tms_stime)};


    FILE *wyn = fopen("wyniki.txt", "a");

    if (wyn) {
        fprintf(wyn, "%s ", fun);
        fprintf(wyn, "%s %d\n", "length: ", length);
        char t[3][25] = {"Real Time: ", "User Time: ", "System Time: "};
        int i;
        for (i = 0; i < 3; i++) {
            fprintf(wyn, "%s%jd\n", t[i], res[i]);
        }
        fprintf(wyn, "\n");
        fclose(wyn);
    }

    free(t_cpu1);
    free(t_cpu2);
    return 0;
}

void sortsys(char *path, int length) {
    int fd = open(path, O_RDWR);
    if (fd < 0) {
        printf("File not opened");
        exit(1);
    }

    long end;
    struct record *tmp = malloc(sizeof(struct record));
    struct record *tmp2 = malloc(sizeof(struct record));
    tmp->chars = malloc(length * sizeof(char));
    tmp2->chars = malloc(length * sizeof(char));
    if (tmp->chars == NULL || tmp2->chars == NULL) {
        printf("%s", "Allocation failed");
        exit(1);
    }

    end = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    long i;
    for (i = 1; i * length < end; i++) {
        long j;
        lseek(fd, i * length, SEEK_SET);
        read(fd, tmp->chars, (size_t) length);
        for (j = i - 1; j >= 0; j--) {
            lseek(fd, j * length, SEEK_SET);
            (size_t) read(fd, tmp2->chars, (size_t) length);
            if (tmp2->chars[0] <= tmp->chars[0]) {
                break;
            }
        }
        for (long k = j + 1; k <= i; k++) {
            lseek(fd, k * length, SEEK_SET);
            read(fd, tmp2->chars, (size_t) length);
            lseek(fd, k * length, SEEK_SET);
            write(fd, tmp->chars, (size_t) length);
            strcpy(tmp->chars, tmp2->chars);
        }

    }
    free(tmp->chars);
    free(tmp);
    free(tmp2->chars);
    free(tmp2);

    close(fd);
}

void sortlib(char *path, int length) {
    FILE *file = fopen(path, "r+");
    long end;
    if (file == NULL) {
        printf("File not opened");
        exit(1);
    }
    struct record *tmp = malloc(sizeof(struct record));
    struct record *tmp2 = malloc(sizeof(struct record));
    tmp->chars = malloc(length * sizeof(char));
    tmp2->chars = malloc(length * sizeof(char));
    if (tmp->chars == NULL || tmp2->chars == NULL) {
        printf("%s", "Allocation failed");
        exit(1);
    }

    fseek(file, 0L, SEEK_END);
    end = ftell(file);
    fseek(file, 0l, SEEK_SET);
    long i;
    for (i = 1; i * length < end; i++) {
        long j;
        fseek(file, i * length, SEEK_SET);
        fread(tmp->chars, 1, (size_t) length, file);
        for (j = i - 1; j >= 0; j--) {
            fseek(file, j * length, SEEK_SET);
            fread(tmp2->chars, 1, (size_t) length, file);
            if (tmp2->chars[0] <= tmp->chars[0]) {
                break;
            }
        }
        for (long k = j + 1; k <= i; k++) {
            fseek(file, k * length, SEEK_SET);
            fread(tmp2->chars, 1, (size_t) length, file);
            fseek(file, k * length, SEEK_SET);
            fwrite(tmp->chars, 1, (size_t) length, file);
            strcpy(tmp->chars, tmp2->chars);
        }

    }
    free(tmp->chars);
    free(tmp);
    free(tmp2->chars);
    free(tmp2);

    fclose(file);
}
