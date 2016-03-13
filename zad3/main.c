#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <bits/errno.h>
#include <string.h>

char trololo[7][21] = {"1: set read lock", "2: set write lock", "3: show locked chars", "4: unlock", "5: read char",
                       "6: write char", "7: end"};

void print_options();

void free_is();

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("You have to specify file path\n");
        exit(1);
    }
    char *filename = argv[1];
    int fd;
    fd = open(filename, O_RDWR);
    if (fd >= 0) {
        int flag = 1;
        print_options();
        char input;
        while (flag) {
            input = (char) getchar();
            if (input != '\n') {
                free_is();
                switch (input) {
                    case '1': {
                        int n;
                        scanf("%d", &n);
                        struct flock fl;
                        fl.l_type = F_RDLCK;
                        fl.l_pid = getpid();
                        fl.l_whence = SEEK_SET;
                        fl.l_len = 1;
                        fl.l_start = n;
                        if (fcntl(fd, F_SETLK, &fl) == -1) {
                            perror(NULL);
                        }
                        break;
                    }
                    case '2': {
                        int n;
                        scanf("%d", &n);
                        struct flock fl;
                        fl.l_type = F_WRLCK;
                        fl.l_pid = getpid();
                        fl.l_whence = SEEK_SET;
                        fl.l_len = 1;
                        fl.l_start = n;
                        if (fcntl(fd, F_SETLK, &fl) == -1) {
                            perror(NULL);
                        }
                        break;
                    }
                    case '3': {
                        long l = lseek(fd, 0L, SEEK_END);
                        long i;
                        for (i = 0; i < l; i++) {
                            struct flock fl;
                            fl.l_whence = SEEK_SET;
                            fl.l_len = 1;
                            fl.l_start = i;
                            fl.l_type = F_WRLCK;
                            if (fcntl(fd, F_GETLK, &fl) == -1) {
                                perror(NULL);
                            }
                            else if (fl.l_type != F_UNLCK) {
                                printf("%li %d %s\n", i, fl.l_pid, "write");
                            }
                            fl.l_whence = SEEK_SET;
                            fl.l_len = 1;
                            fl.l_start = i;
                            fl.l_type = F_RDLCK;
                            if (fcntl(fd, F_GETLK, &fl) == -1) {
                                perror(NULL);
                            }
                            else if (fl.l_type != F_UNLCK) {
                                printf("%li %d %s\n", i, fl.l_pid, "read");
                            }
                        }
                        break;
                    }
                    case '4': {
                        int n;
                        scanf("%d", &n);
                        struct flock fl;
                        fl.l_type = F_UNLCK;
                        fl.l_pid = getpid();
                        fl.l_whence = SEEK_SET;
                        fl.l_len = 1;
                        fl.l_start = n;
                        if (fcntl(fd, F_SETLK, &fl) == -1) {
                            perror(NULL);
                        }
                        break;
                    }
                    case '5': {
                        int n;
                        scanf("%d", &n);
                        char c[1];
                        lseek(fd, n, SEEK_SET);
                        read(fd, c, 1);
                        printf("%c\n", c[0]);
                        break;
                    }
                    case '6': {
                        int n;
                        scanf("%d", &n);
                        free_is();
                        lseek(fd, n, SEEK_SET);
                        char c[1];
                        scanf("%c", &c[0]);
                        write(fd, c, 1);
                        break;
                    }
                    case '7': {
                        flag = 0;
                        break;
                    }
                    default: {
                        printf("There is no option %c\n", input);
                        break;
                    }
                }
                print_options();
            }
        }
        close(fd);
    } else {
        perror(NULL);
        exit(1);
    }
    return 0;
}

void free_is() {
    while ((getchar()) != '\n');
}

void print_options() {
    int i;
    for (i = 0; i < 7; i++)
        printf("%s\n", trololo[i]);
}