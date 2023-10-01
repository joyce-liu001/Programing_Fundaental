// z5271698

#include <stdio.h>
#include <assert.h>

#define MAX 1000

int find_part (int array[MAX], int i, int size);

int main(void) {
    int counter_part = 0;
    
    int size = 0;
    int number;
    int array[MAX];   
    while (scanf("%d", &number) != EOF) {
        array[size] = number;
        size++;    
    }
    
    int i = 0;
    while (i < size) {
        if (array[i] > 0 && find_part(array, i, size) == 1) {
            counter_part++;       
        }                          
        i++;
    }     
    
    printf("%d\n", counter_part);
}

int find_part (int array[MAX], int i, int size) {
    int j = i;
    while (j < size) {
        if (array[i] == -array[j]) {
            return 0;
        }
                        
        j++;
    } 
    
    return 1;  
}
