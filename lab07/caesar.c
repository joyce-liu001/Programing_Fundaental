// z5271698
#include <stdio.h>
#include <stdlib.h>

int encrypt(int character, int shift);
int main(void) {
    int shift; 
    scanf("%d", &shift);
    int character = getchar();
    while (character != EOF) {
        int new_character = encrypt(character,shift);
        putchar(new_character);
        character = getchar();
    }
    return 0;
}

int encrypt(int character, int shift) {
    int s = character + shift;
    int i = abs(shift) % 26;
    if (character >= 'a' && character <= 'z') {
        if (s <= 'z' && s >= 'a') {       
            return s;
        } else if (s > 'z') {             
            int move = character + i;
            if (move <= 'z') {
                return move;
            } else if (move > 'z') {
                int n = move - 'z';
                return 'a' + n - 1;
            }
        } else if (shift < 0) {
            int answer = character - 'a' - i;                               
            if (answer < 0) {
                return 'z' + answer + 1;
            } else if (answer >= 0) {
                return 'a' + answer;
            }
        }
    } else if (character >= 'A' && character <= 'Z') {
        if (s <= 'Z' && s >= 'A') {
            return s;  
        } else if (s > 'Z') {
           int move2 = character + i;
            if (move2 <= 'Z') {
                return move2;
            } else if (move2 > 'Z') {
                int n2 = move2 - 'Z';
                return 'A' + n2 - 1;
            }
        } else if (s < 'A') {
            int answer2 = character - 'A' - i;
            if (answer2 < 0) {
                return 'Z' + answer2 + 1;           
            } else if (answer2 >= 0) {
                return 'A' + answer2;
            }
        }    
    } 
    return character;
    
}
