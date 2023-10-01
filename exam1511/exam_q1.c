// z5271698
#include <stdio.h>

// Return the number of increasing pairs in the array.
int count_increasing(int size, int array[size][2]) {
    int increase = 0;
    int line = 0;
    while (line < size) {
        if (array[line][0] < array[line][1]) {
            increase++;
        }
        line++;
    }
    
    return increase;
}

// This is a simple main function which could be used
// to test your count_increasing function.
// It will not be marked.
// Only your count_increasing function will be marked.

#define TEST_ARRAY_SIZE 5

int main(void) {
    int test_array[TEST_ARRAY_SIZE][2] = {{16, 7}, {8, 12}, {13, -9}, {-3, 12}, {1, 1}};

    int result = count_increasing(TEST_ARRAY_SIZE, test_array);
    printf("%d\n", result);

    return 0;
}
