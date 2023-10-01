//z5271698

#include <stdio.h>

int main (void) {
    int firstInt;
    int secondInt;
    printf("Please enter two integers: ");
    scanf("%d %d", &firstInt, &secondInt);
    
    int result = firstInt + secondInt;
    printf("%d + %d = %d \n", firstInt, secondInt, result);
    return 0;
}

