//z5271698
#include <stdio.h>
#define MAX_NUMS 100


int main(void) {
    int number[MAX_NUMS] = {0};
    int i = 0;
    printf("Enter numbers forwards:\n");
    while (scanf("%d\n", &number[i]) != EOF) { 
        i++; 
    }

    printf("Reversed:\n");
    while (i > 0) {
        i--;
        printf("%d\n", number[i]);
    }
  
}
