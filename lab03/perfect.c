//z5271698

#include <stdio.h>


int main(void) {
    
    int num;
    printf("Enter number: ");
    scanf("%d", &num);
    printf("The factors of %d are:\n", num);
    
    int factor = 1;
    int sum = 0;
    
    while (factor <= num) {
        int counter = num % factor;
        if (counter == 0) {
            printf("%d\n", factor);
            sum = sum + factor;
        }
        factor = factor + 1;
    }
    printf("Sum of factors = %d\n", sum);
    
    if (sum - num == num) {
        printf("%d is a perfect number\n", num);
    } else {
        printf("%d is not a perfect number\n", num);
    }
}
