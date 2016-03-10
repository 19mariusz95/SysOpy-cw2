#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <ftw.h>


char *permissions;

typedef struct FTW FTW;

void find1(char *path, char *permissions);

void find2(char *path, char *permissions);

int fun(char *permissions, struct stat stat1);

void nftw(char *path, int (*info)(const char *, const struct stat *, int, struct FTW *), int i, int flag);

int display_info(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbus) {

    if (fun(*sb)) {
        char p[PATH_MAX];
        realpath(fpath, p);
        printf("%s\n", p);

    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("%s\n", "You have to input all arguments");
        return 1;
    }
    char *path = argv[1];
    permissions = argv[2];

    if (strlen(permissions) != 9) {
        printf("Trolollo");
        exit(1);
    }

    find2(path, permissions);

    return 0;
}

void find1(char *path, char *permissions) {

    DIR *dir = opendir(path);
    struct stat filestat;
    stat(path, &filestat);
    if (dir == NULL) {
        return;
    }

    size_t len = strlen(path);

    char fn[FILENAME_MAX];
    strcpy(fn, path);
    fn[len++] = '/';

    struct dirent *ent;

    while ((ent = readdir(dir)) != NULL) {
        if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
            continue;
        strncpy(fn + len, ent->d_name, FILENAME_MAX - len);
        stat(fn, &filestat);
        if (S_ISDIR(filestat.st_mode)) {
            find1(fn, permissions);
        }
        else if (S_ISREG(filestat.st_mode) == 1) {
            if (fun(filestat))
                printf("%s\n", ent->d_name);
        }
    }
    closedir(dir);
}

void find2(char *path, char *permissions) {
    DIR *dir = opendir(path);
    nftw(path, display_info, 10, FTW_F);
}

int fun(struct stat stat1) {
    char pr[10];
    pr[9] = '\0';
    if (stat1.st_mode & S_IRUSR)
        pr[0] = 'r';
    else
        pr[0] = '-';
    if (stat1.st_mode & S_IWUSR)
        pr[1] = 'w';
    else
        pr[1] = '-';
    if (stat1.st_mode & S_IXUSR)
        pr[2] = 'x';
    else
        pr[2] = '-';
    if (stat1.st_mode & S_IRGRP)
        pr[3] = 'r';
    else
        pr[3] = '-';
    if (stat1.st_mode & S_IWGRP)
        pr[4] = 'w';
    else
        pr[4] = '-';
    if (stat1.st_mode & S_IXGRP)
        pr[5] = 'x';
    else
        pr[5] = '-';
    if (stat1.st_mode & S_IROTH)
        pr[6] = 'r';
    else
        pr[6] = '-';
    if (stat1.st_mode & S_IWOTH)
        pr[7] = 'w';
    else
        pr[7] = '-';
    if (stat1.st_mode & S_IXOTH)
        pr[8] = 'x';
    else
        pr[8] = '-';
    if (strcmp(pr, permissions) == 0)
        return 1;
    return 0;
}