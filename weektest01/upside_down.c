//z5271698

#include <stdio.h>

int main(void) {
    double num1, num2, num3;
    printf("Please enter three numbers: ");    
    scanf("%lf %lf %lf", &num1, &num2, &num3);
    
    if(num1 < num2 && num2 < num3) {
        printf("up\n");
    } else if(num1 > num2 && num2 > num3) {
        printf("down\n");
    } else {
        printf("neither\n");
    }
}
