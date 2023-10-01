// z5271698
#include <stdio.h>
#include <stdlib.h>


#define MAX 28

int sub(int character, char array[MAX]);
int main(void) {
    char array[MAX];
    fgets(array, MAX, stdin);    
    int character = getchar();
    while (character != EOF) {
        int new_character = sub(character, array);
        putchar(new_character);
        character = getchar();
    }
    return 0;
}

int sub(int character, char array[MAX]) {
    int i = 0;
    int n = 0;
    if (character >= 'a' && character <= 'z') {
        while (i < MAX) {
            if (character == array[i]) {
                n = i;
            }
            i++;
        } 
        return 'a' + n;     
    } else if (character >= 'A' && character <= 'Z') {
        int upper = character - 'A';
        int lower = 'a' + upper;
        while (i < MAX) {
            if (lower == array[i]) {
                n = i;
            }
            i++;
        } 
        return 'A' + n;
    } 
    return character; 
}
