// Lab Exercise week2 
//Don't Be So Negative!
//z5271698

#include <stdio.h>
int main(void) {
    //read a number
    int firstNumber;
    scanf("%d", &firstNumber);
    
    if (firstNumber < 0) { 
        printf("Don't be so negative!\n");
    } else if (firstNumber > 0) { 
        printf("You have entered a positive number.\n");
    } else {
        printf("You have entered zero.\n");
    }
    
    return 0;
}
