// z5271698
#include <stdio.h>
#include <stdlib.h>


#define MAX 256

int main(void) {
    char array[MAX];
    fgets(array, MAX, stdin);    
    int n;
    scanf("%d", &n);
    printf("The character in position %d is '%c'\n", n, array[n]);
    return 0;
}


