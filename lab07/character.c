#include <stdio.h>


int main(void) {
    int c1 = 'a' + ('a' + 100 ) % 'z'; 
    
    putchar(c1);

    return 0;
}
