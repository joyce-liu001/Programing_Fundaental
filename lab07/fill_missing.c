// z5271698
#include <stdio.h>
#define MAX 10000

int main(void) {
    int number[MAX] = {0};
    int i = 0;
    while (scanf("%d\n", &number[i]) != EOF) { 
        i++; 
    }
    
    int biggest = 0;
    int x = 0;
    while (x <= i) {
        if (number[x] > biggest) {
            biggest = number[x];
        }
        x++;
    }  
    
    int n = 1;
    while (n <= biggest) {
        int counter = 0;
        while (counter <= i && n != number[counter]) {
            counter++;
        }
        if (counter == i+1) {
            printf("%d ", n);
        }
        n++;
    }
    printf("\n");     
}

