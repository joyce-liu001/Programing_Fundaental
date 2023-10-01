//z5271698


#include <stdio.h>

#include <stdlib.h>

int main(void) {
    int num1;
    int num2;
    scanf("%d %d", &num1, &num2);
    
    int num3 = abs (num1 * num2);
    
    if(num3 == 0) {
        printf("zero\n");
    } else {
        printf("%d\n", num3);
    }
}

