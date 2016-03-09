#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

void find(char *path, char *privileges);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("%s\n", "You have to input all arguments");
        return 1;
    }
    char *path = argv[1];
    char *access_privileges = argv[2];

    if (strlen(access_privileges) != 9) {
        printf("Trolollo");
        exit(1);
    }

    find(path, access_privileges);

    return 0;
}

void find(char *path, char *privileges) {

    printf("%s\n", path);
    DIR *dir = opendir(path);
    if (dir == NULL) {
        ///
        return;
    }
    struct stat filestat;
    stat(path, &filestat);

    size_t len = strlen(path);

    char fn[FILENAME_MAX];
    strcpy(fn, path);
    fn[len++] = '/';

    struct dirent *ent;

    while ((ent = readdir(dir)) != NULL) {
        if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
            continue;
        if (S_ISDIR(filestat.st_mode)) {
            strncpy(fn + len, ent->d_name, FILENAME_MAX - len);
            find(fn, privileges);
        }
        else if (S_ISREG(filestat.st_mode) == 1) {
            printf("%s\n", ent->d_name);
        }
    }
    closedir(dir);
}

void fun1(struct dirent *ent) {
    printf("%s\n", ent->d_name);
}