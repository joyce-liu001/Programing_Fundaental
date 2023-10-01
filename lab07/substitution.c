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
    if (character >= 'a' && character <= 'z') {
        int c1 = character - 'a';
        return array[c1];     
    } else if (character >= 'A' && character <= 'Z') {
        int c2 = character - 'A';
        int alphabetPosition = array[c2] - 'a';
        return 'A' + alphabetPosition;
    } 
    return character; 
}


"""int character = getchar();
    while (character != EOF) {
        int new_character = delete(character);
        putchar(new_character);
        character = getchar();
    }"""

"""
int delete(int character) {
    if (character != 'a' && character != 'e' && character != 'i' &&
		character != 'o' && character != 'u' && character != 'A' &&
		character != 'E' && character != 'I' && character != 'O' &&
		character != 'U') {
        return character;        
    }
	return 0;
}"""