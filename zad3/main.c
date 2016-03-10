#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

char trololo[7][21] = {"1: set read lock", "2: set write lock", "3: show locked chars", "4: unlock", "5: read char", "6: write char","7: end"};

void print_options();

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("You have to specify file path");
        exit(1);
    }
    char *filename = argv[1];
    int fd;
    fd = open(filename,O_RDWR);
    if (fd>=0) {
        int flag=1;
        print_options();
        char input;
        while(flag && (input= (char) getchar()) != '7'){
            switch (input){
                case '1':{
                    int n;
                    scanf("%d",&n);
                    struct flock fl;
                    fl.l_type=F_RDLCK;
                    fl.l_pid=getpid();
                    fl.l_whence=SEEK_SET;
                    fl.l_len=1;
                    fl.l_start=n;
                    fcntl(fd,F_SETLK,fl);
                    break;
                }
                case '2':{
                    int n;
                    scanf("%d",&n);
                    struct flock fl;
                    fl.l_type=F_WRLCK;
                    fl.l_pid=getpid();
                    fl.l_whence=SEEK_SET;
                    fl.l_len=1;
                    fl.l_start=n;
                    fcntl(fd,F_SETLK,fl);
                    break;
                }
                case '3':{
                    FILE *file = fopen(filename,"r");
                    fseek(file,SEEK_END,0);
                    long l = ftell(file);
                    long i;
                    for(i=0;i<l;i++){
                        struct flock fl;
                        fl.l_whence=SEEK_SET;
                        fl.l_len=1;
                        fl.l_start=i;
                        fl.l_type=F_WRLCK;
                        fcntl(fd,F_GETLK,fl);
                        if(fl.l_type!=F_UNLCK){
                            printf("%li\n",i);
                        }
                    }

                    fclose(file);
                    break;
                }
                case '4':{
                    int n;
                    scanf("%d",&n);
                    struct flock fl;
                    fl.l_type=F_UNLCK;
                    fl.l_pid=getpid();
                    fl.l_whence=SEEK_SET;
                    fl.l_len=1;
                    fl.l_start=n;
                    fcntl(fd,F_SETLK,fl);
                    break;
                }
                case '5':{
                    int n;
                    scanf("%d",&n);
                    char c;
                    FILE * file = fopen(filename,"r");
                    if(!file){
                        printf("trololoo");
                        exit(1);
                    }
                    fseek(file,SEEK_SET,n);
                    c= (char) getc(file);
                    fclose(file);
                    printf("%c\n",c);
                    break;
                }
                case '6':{
                    int n;
                    scanf("%d",&n);
                    char c;
                    scanf("%c",&c);
                    FILE * file = fopen(filename,"w");
                    if(!file){
                        printf("trololoo");
                        exit(1);
                    }
                    fseek(file,SEEK_SET,n);
                    putc(c,file);
                    break;
                }
                case '7':{
                    flag=0;
                    break;
                }
                default:{
                    printf("There is no option %s",&input);
                    break;
                }
            }
            print_options();
        }
        close(fd);
    } else {
        printf("Trololololo\n");
        exit(1);
    }
    return 0;
}

void print_options() {
    int i;
    for(i=0;i<7;i++)
        printf("%s\n",trololo[i]);
}