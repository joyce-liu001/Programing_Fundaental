//z5271698

#include <stdio.h>

int main(void) {
   
    int size;
    printf("Enter size: ");
    scanf("%d", &size);
    
    int line = 0;
    
    while (line < size) {
        
        int note = 0;
        
        while (note < size) {
            if (note == line || note == size - line - 1) {
                printf("*");
            } else {
                printf("-");
            }
            note = note + 1;
        }   
        printf("\n");
        line = line + 1;
    }
    
}    
