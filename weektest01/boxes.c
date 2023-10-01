//z5271698

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int num;
    printf("How many boxes: ");
    scanf("%d", &num);
    
    int row = 1;
    int mid = (4 *num - 1) / 2 + 1;
    while ( row <= 4 * num - 1) {
        int col = 1;
        if (row % 2 == 0) {
            while (col <= 4 * num - 1) {
                if (col % 2 == 0)  {
                    printf("0");
                } else if (col <= mid + abs(row - mid) && col >= mid - abs(row - mid)) {
                    printf("0");
                } else {
                    printf("1");
                } 
                col++;
            }
        } else if (row % 2 == 1) {
            while (col <= 4 * num - 1) {
                if (col % 2 == 1) {
                    printf("1");
                } else if (col <= mid + abs(row - mid) && col >= mid - abs(row - mid)) {
                    printf("1");
                } else {
                    printf("0");
                }
                col++;
            }
        }
        printf("\n");
        row++;
    }

}
