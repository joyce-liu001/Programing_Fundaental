//z5271698
//Prints the first n digits of pi, where n is specified 
// by the user


#include <stdio.h>

#define MAX_DIGITS 10

int main(void) {
    int pi[MAX_DIGITS] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    printf("How many digits of pi would you like to print? ");
    //TODO: Insert your code here
    int i;
    scanf("%d", &i);
    
    int digits = 1;
    if (i == 0) {
        printf("\n");
    } else if (i == 1) {
        printf("3\n");
    } else {
        printf("3.");
        while (digits < i) {
            printf("%d", pi[digits]);
            digits++;
        }
        printf("\n");
    } 
    
    
    return 0;
}
