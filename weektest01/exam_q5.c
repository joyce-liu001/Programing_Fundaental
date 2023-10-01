#include <stdio.h>
#include <string.h>

#define SIZE 1024

int check_common(char input[SIZE], char arg[SIZE]);

int main(int argc , char *argv[]) {
    char input[SIZE] = "";
    fgets(input, SIZE, stdin); 
    //printf("%s", input); 
    for (int i = 1; i < argc; i++) {
        char array[SIZE] = "";
        strcpy(array,argv[i]);
        check_common(input, array);
        //printf("%s\n", array);
    }
    return 0;
}

int check_common(char input[SIZE], char arg[SIZE]) {
    int i = 0;
    while (input[i] != '\0' && arg[i] != '\0') {
        if (input[i] == arg[i]) {
            printf("%d %s\n", i, arg);
            return 0;
        }
        i++;
    }
    return 0;
}

