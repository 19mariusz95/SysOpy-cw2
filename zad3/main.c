#include <stdio.h>
#include <stdlib.h>
char trololo[7][21] = {"1: set read lock", "2: set write lock", "3: show locked chars", "4: unlock", "5: read char", "6: write char","7: end"};

void print_options();

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("You have to specify file path");
        exit(1);
    }
    char *filename = argv[1];
    FILE *file = fopen(filename, "rw");
    if (file) {
        int flag=1;
        print_options();
        char input;
        while(flag && (input=getchar())!='7'){
            switch (input){
                case '1':{

                    break;
                }
                case '2':{

                    break;
                }
                case '3':{

                    break;
                }
                case '4':{

                    break;
                }
                case '5':{

                    break;
                }
                case '6':{

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