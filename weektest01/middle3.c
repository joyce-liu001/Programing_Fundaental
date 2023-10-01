//z5271698

#include <stdio.h>

int main(void) {
    int num1;
    int num2;
    int num3;
    
    printf("Enter integer: ");
    scanf("%d\n", &num1);
    printf("Enter integer: ");
    scanf("%d\n", &num2);
    printf("Enter integer: ");
    scanf("%d\n", &num3);

    if (num1 <= num2 && num2 <= num3) {
        printf("Middle: %d\n", num2);
    } else if (num3 <= num2 && num2 <= num1) {
         printf("Middle: %d\n", num2);
    } else if (num2 <= num1 && num1 <= num3) {
         printf("Middle: %d\n", num1);
    } else if (num3 <= num1 && num1 <= num2) {
        printf("Middle: %d\n", num1);
    } else if (num1 <= num3 && num3 <= num2) {
         printf("Middle: %d\n", num3);
    } else if (num2 <= num3 && num3 <= num1) {
        printf("Middle: %d\n", num3);
    }
}
