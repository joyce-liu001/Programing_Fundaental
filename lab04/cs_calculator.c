//z5271698 Zhaoyan LIU

#include <stdio.h>
#include <math.h>

int main(void) {
    int num1;
    printf("Enter instruction: ");
    while (scanf("%d", &num1) != EOF) {
        if(num1 == 1) {
          int num2;
          scanf("%d", &num2);
          printf("%d\n", num2 * num2);
        } if(num1 == 2) {
            int num2, num3;
            scanf("%d %d", &num2, &num3);
            int result = pow(num2, num3);
            printf("%d\n", result);
        }
      printf("Enter instruction: ");
    }
  return 0;
}
