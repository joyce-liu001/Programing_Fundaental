// z5271698

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


#define MAX_LINE 10
#define MAX_CHA 256


int main(int argc, char *argv[]) {
    // you can always assume you will have exactly one command line argument.
    assert(argc == 2);
    char arv[MAX_CHA];
    strcpy(arv, argv[1]);
    
    char c[MAX_CHA];
    char similar[MAX_CHA] = {0};  
    int smallest = MAX_CHA;
    int l = 1;
    // Loop until there are no more characters to scan.
    while (fgets(c, MAX_CHA, stdin) && l <= MAX_LINE) {
        int i = 0;
        int difference = 0;
        while (c[i] != '\0' && c[i] != '\n') {
            if (c[i] != arv[i]) {
                if (c[i] >= 'a' && c[i] <= 'z' && (c[i] - 'a' + 'A') 
                == arv[i]) {
                    difference = difference + 0;                  
                } else if (c[i] >= 'A' && c[i] <= 'Z' && (c[i] - 'A' + 'a') 
                == arv[i]) {
                    difference = difference + 0;
                } else {
                    difference++;
                }
            }
            
            i++;
        }           
        
        if (smallest > difference) {
            smallest = difference;
            strcpy(similar, c);
        }
               
        l++;               
    }
    
    printf("%d %s\n", smallest, similar);
      
    return 0;
}
    
 
