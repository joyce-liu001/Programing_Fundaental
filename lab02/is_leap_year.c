//z5271698 Zhaoyan LIU

#include <stdio.h>

int main(void) {

    int yearNumber;
    printf("Enter year: ");
    scanf("%d", &yearNumber);
    int firstResult = yearNumber % 100;
    int secondResult = yearNumber % 400;
    int thirdResult = yearNumber % 4;

    
    if (firstResult == 0 && secondResult != 0) {
        printf("%d is not a leap year.\n", yearNumber);
    } else if (firstResult == 0 && secondResult == 0) {
        printf("%d is a leap year.\n", yearNumber);
    } else if (thirdResult == 0) {
        printf("%d is a leap year.\n", yearNumber);
    } else {
        printf("%d is not a leap year.\n", yearNumber);
    }
    
    return 0;
}
