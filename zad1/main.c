#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <stdint.h>

void sortlib(char *path, int length);

void sortsys(char *path, int length);

struct record {
    char *tmp;
    size_t length;
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

    printf("Real Time: %jd, User Time: %jd, System Time: %jd\n",
           (intmax_t) time, (intmax_t) (t_cpu2->tms_utime - t_cpu1->tms_utime),
           (intmax_t) (t_cpu2->tms_stime - t_cpu1->tms_stime));

    free(t_cpu1);
    free(t_cpu2);
    return 0;
}

void sortsys(char *path, int length) {  //read write
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("File not opened");
        exit(1);
    }

    fclose(file);
}

void sortlib(char *path, int length) { //fread fwrite
    FILE *file = fopen(path, "rw");
    long end;
    if (file == NULL) {
        printf("File not opened");
        exit(1);
    }
    struct record *tmp = malloc(sizeof(struct record));
    struct record *tmp2 = malloc(sizeof(struct record));
    tmp->tmp = malloc(length * sizeof(char));
    tmp2->tmp = malloc(length * sizeof(char));

    fseek(file, 0L, SEEK_END);
    end = ftell(file);
    printf("%ld\n", end);
    fseek(file, 0l, SEEK_SET);
    long i;
    for (i = 1; i * length < end; i++) {
        printf("%ld %ld\n", i * length, end);
        long j;
        fseek(file, i * length, SEEK_SET);
        tmp->length = fread(tmp->tmp, 1, (size_t) length, file);
        for (j = i - 1; j >= 0; j--) {
            fseek(file, j * length, SEEK_SET);
            tmp2->length = fread(tmp2->tmp, 1, (size_t) length, file);
            if (tmp2->tmp[0] <= tmp->tmp[0]) {
                printf("%s %c %c\n", "tutaj", tmp2->tmp[0], tmp->tmp[0]);
                for (long k = j + 1; k <= i; k++) {
                    fseek(file, k * length, SEEK_SET);
                    tmp2->length = fread(tmp2->tmp, 1, (size_t) length, file);
                    fseek(file, k * length, SEEK_SET);
                    fwrite(tmp->tmp, 1, (size_t) length, file);
                    strcpy(tmp->tmp, tmp2->tmp);
                }
                break;
            }
        }
        if (j == -1) {
            for (long k = j + 1; k <= i; k++) {
                fseek(file, k * length, SEEK_SET);
                tmp2->length = fread(tmp2->tmp, 1, (size_t) length, file);
                fseek(file, k * length, SEEK_SET);
                fwrite(tmp->tmp, 1, (size_t) length, file);
                strcpy(tmp->tmp, tmp2->tmp);
            }
        }
    }
    free(tmp->tmp);
    free(tmp);
    free(tmp2->tmp);
    free(tmp2);

    fclose(file);
}
