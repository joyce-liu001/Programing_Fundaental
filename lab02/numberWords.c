//z5271698

#include <stdio.h>

int main(void) {
    int yourNumber;
    printf("Please enter an integer: ");
    scanf("%d", &yourNumber);
      
    if (1 > yourNumber) { 
        printf("You entered a number less than one.\n");
    } else if (5 < yourNumber) { 
        printf("You entered a number greater than five.\n");
    } else if (1 == yourNumber) {
        printf("You entered one.\n");
    } else if (2 == yourNumber) {
        printf("You entered two.\n");
    } else if (3 == yourNumber) {
        printf("You entered three.\n");
    } else if (4 == yourNumber) {
        printf("You entered four.\n");
    } else {
        printf("You entered five.\n");
    }
    
    return 0;
}

