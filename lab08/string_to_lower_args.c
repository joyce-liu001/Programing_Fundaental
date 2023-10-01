// Zhaoyan LIU (z5271698)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
void new(char *array);

int main(int argc, char *argv[]) {
    int i = 1;
    char array[MAX] = "";
    while (argv[i] != NULL) {
        strcpy(array,argv[i]);
        new(array);
        printf("%s ", array);
        i++;
    }
    printf("\n");
    return 0;
}


void new(char *array) {
    int i = 0;
    while (array[i] != '\0') {
        if (array[i] >= 'A' && array[i] <= 'Z') {
            array[i] = array[i] - 'A' + 'a';
        } 
        i++;
    }
    
}
