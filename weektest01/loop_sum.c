//z5271698

#include <stdio.h>


int main(void) {
    int n;
    printf("How many numbers: ");
    scanf("%d", &n);
    int number;
    int sum = 0;
    int i = 0;
    while (i < n) {
        scanf("%d\n", &number);
        sum = sum + number;
        i++;
    }


    printf("The sum is: %d\n", sum);
}
