//z5271698

#include <stdio.h>

int main(void) {
   
    int size;
    printf("Enter size: ");
    scanf("%d", &size);
    
    printf("*\n");
    printf("**\n");
    printf("* *\n");
    
    int line = 4;
    
    while (line < size) {
        printf("*");
        int note = 1;
        while (note <= line - 2) {           
            printf(" ");
            note = note + 1;
        }   
        
        printf("*");
        printf("\n");
        line = line + 1;
    }
    int x = 1;
    while (x <= size) {
        printf("*");
        x = x + 1;
    }
    printf("\n");
}    
