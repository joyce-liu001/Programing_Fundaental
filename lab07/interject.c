// COMP1511 Week 7 Test: Interject
// This program was written by Zhaoyan LIU (z5271698)
// on 18-07-202
//
// This program adds interjections to strings.

#include <stdio.h>

#define MAX_SIZE 1002

// Modify str so that it contains interject at the given index.
void interject(char *str, char *interject, int index) {
    // Counte number of character in str
    int max = 0;
    while (str[max] != '\0') {
        max++;
    }
    
    // Counte number of character in interject.
    int x = 0;
    while (interject[x] != '\0') {
        x++;
    }
    
    char array[MAX_SIZE];
    int c = 0;
    while (c < max) {
        array[c] = str[c];
        c++;
    }
    
    
    int i = index;
    int n = 0;
    while (n < x) {
        str[i] = interject[n];
        n++;
        i++;
    }
    
    int counter = index;
    while (counter < max) {
        str[i] = array[counter];
        i++;
        counter++;
    } 
    str[i] = '\0';  
}


// This is a simple main function that you can use to test your interject
// function.
// It will not be marked - only your interject function will be marked.
//
// Note: the autotest does not call this main function!
// It calls your interject function directly.
// Any changes that you make to this function will not affect the autotests.

int main(void) {
    char str1[MAX_SIZE] = "Comp Science";
    printf("%s -> ", str1);
    interject(str1, "uter", 4);
    printf("%s\n", str1);

    char str2[MAX_SIZE] = "Beginnings";
    printf("%s -> ", str2);
    interject(str2, "New ", 0);
    printf("%s\n", str2);

    char str3[MAX_SIZE] = "The End!";
    printf("%s -> ", str3);
    interject(str3, " Is Nigh", 7);
    printf("%s\n", str3);

    char str4[MAX_SIZE] = "UNSW Other Unis";
    printf("%s -> ", str4);
    interject(str4, "> ", 5);
    printf("%s\n", str4);

    return 0;
}
