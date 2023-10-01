//z5271698 LIU Zhaoyan

#include <stdio.h>

int main(void) {
    
    int dieSide;
    printf("Enter the number of sides on your dice: ");
    scanf("%d", &dieSide);
    
    int dieRoll;
    printf("Enter the number of dice being rolled: "); 
    scanf("%d", &dieRoll);
    
    int range = dieRoll * dieSide;
    double av_value = (range + dieRoll) / 2.0;
    
    if (dieRoll > 0 && dieSide > 0) { 
        printf("Your dice range is %d to %d.\n", dieRoll, range);
        printf("The average value is %lf\n", av_value);
    } else { 
        printf("These dice will not produce a range.\n");
    }
    
    return 0;
}
    
    
 
