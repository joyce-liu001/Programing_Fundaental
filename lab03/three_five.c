//5271698

#include <stdio.h>
#define NUM3 3
#define NUM5 5


int main(void) {
    int value_number; 
    printf("Enter number: ");
    scanf("%d", &value_number);
   
    int counter = 1;
   
    while (counter < value_number) { 
        int mod1 = counter % NUM3;
        int mod2 = counter % NUM5;
       
        if (mod1 == 0 || mod2 == 0) {
            printf("%d\n", counter); 
        }
          
        counter = counter + 1;
    }

}
