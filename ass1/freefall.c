// Author:Zhaoyan LIU (z5271698) 
// Date: 10-07-2020
// UNSW Freefall assignment.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 15
#define EMPTY 0
#define STONE 1
#define MARCHING 2
#define WIN 100
#define LOSE 200
#define SIZE2 150
#define MOVE_PLAYER 1
#define FIRE_LASER 2
#define SHIFT_DOWN 3
#define VERTICAL_FLIP 4
#define GRAVITY_STORM 5
#define LEFT 1
#define RIGHT -1
#define TO_LEFT 1
#define TO_TOP_LEFT 2
#define TO_TOP_RIGHT 3
#define TO_RIGHT 4

void scanBlocks(int map[SIZE][SIZE], int secondMap[SIZE2][SIZE], int lineNum);
void fireLaser (int map[SIZE][SIZE], int playerX);
void printMap(int map[SIZE][SIZE], int playerX);
void moveDownAboveBlocks(int map[SIZE][SIZE], int secondMap[SIZE2][SIZE]);
void swapNums(int *a, int *b);
void verticalFlip(int map[SIZE][SIZE]);
void tntBlocks(int map[SIZE][SIZE], int i, int j, int TNT);
void shiftDownMarchingBlock(int map[SIZE][SIZE], int n);
void secondShift(int leftCounter, int rightCounter, int map[SIZE][SIZE], int n, 
int lineCounter, int moveDown);
void shiftLeft(int map[SIZE][SIZE]);
void shiftRight(int map[SIZE][SIZE]);
void shiftTopRight(int map[SIZE][SIZE]);
void secondTopRight(int map[SIZE][SIZE], int rowCounter, int colCounter);
void shiftTopLeft(int map[SIZE][SIZE]);
void secondTopLeft (int map[SIZE][SIZE], int colCounter, int rowCounter);
int checkWin(int map[SIZE][SIZE]);
int checkLose(int map[SIZE][SIZE]);


int main (void) {
    // Th  is  fveferline creates our 2D array called "map" and sets all
    // of the blocks in the map to EMPTY.
    int map[SIZE][SIZE] = {EMPTY};
    
    // Creates 2D array called "secondMap" and sets all blocks are EMPTY
    // which is a array above the map.
    int secondMap[SIZE2][SIZE] = {EMPTY};
    
    // This line creates out playerX variable. The player starts in the
    // middle of the map, at position 7.
    int playerX = SIZE / 2;
    
    // Set variables let the vertical flip and gravity storm command 
    // can only work once.
    // And count number of times shift down command.
    int com3 = 0;
    int com4 = 0;
    int com5 = 0;    
    
    printf("How many lines of stone? ");
    //  Scan in the number of lines of blocks.
    int lineNum;
    scanf("%d", &lineNum);

    printf("Enter lines of stone:\n");
    //  Scan in the lines of blocks.    
    scanBlocks(map, secondMap, lineNum);
    printMap(map, playerX);
    
        
    // Scan in commands until EOF.
    int command; 
    while (scanf("%d", &command) != EOF) {// Scan commands.        
        if (command == MOVE_PLAYER) {
            // A command to move the player to the left or right on the screen.
            int direction;
            scanf("%d", &direction);
            if (direction == LEFT) {// Moving to left.2
                playerX++;
            } else if (direction == RIGHT) {// Moving to right.
                playerX--;
            } 
            printMap(map, playerX);
        } else if (command == FIRE_LASER) {// Fire laser command.
            fireLaser(map, playerX);
            
            // Check whether game win or not.
            if (checkWin(map) == WIN) {
                printf("Game Won!\n");
                return 0;
            }             
        } else if (command == SHIFT_DOWN) {// Shift down commond
            
            // Check whether the game is lose or not.
            if (checkLose(map) == LOSE) {
                printMap(map, playerX);
                printf("Game Lost!\n");
                return 0;
            }
            // Counter when the shift down command.
            com3++; 
           
            // Shift Everything Down and move the marching blocks.
            shiftDownMarchingBlock(map, com3);          
                
            // Move down the blocks on the above map.
            moveDownAboveBlocks(map, secondMap);  
            printMap(map, playerX);                                   
        } else if (command == VERTICAL_FLIP) {// Vertical flip command.
            if (com4 == 0) {// Vertical flip can only work once.
                verticalFlip(map);
                com4++;
            }    
            printMap(map, playerX);            
        } else if (command == GRAVITY_STORM) { // Gravity Storm Command.
            int direction;
            scanf("%d", &direction);
            if (direction == TO_LEFT && com5 == 0) {
                // Gravity storm to the left.
                shiftLeft(map);
            } else if (direction == TO_TOP_LEFT && com5 == 0) {
                // Gravity storm to the top-left.
                shiftTopLeft(map);
            } else if (direction == TO_TOP_RIGHT && com5 == 0) {
                // Gravity storm to the top-right.
                shiftTopRight(map);              
            } else if (direction == TO_RIGHT && com5 == 0) {
                // Gravity storm to the right.
                shiftRight(map);               
            } 
            printMap(map, playerX);
            com5++; 
        }        
    }
    return 0;
}


// Scan the blocks in map.
void scanBlocks(int map[SIZE][SIZE], int secondMap[SIZE2][SIZE], int lineNum) {
    int row, column, length, value;
    int lineCounter = 0; 
    while (lineCounter < lineNum) {
        scanf("%d %d %d %d", &row, &column, &length, &value);
        int lengthCounter = 1;      
        if (row >= 0) {
            while (lengthCounter <= length && row < SIZE && (column >= 0 && 
            column < SIZE) && length <= SIZE) { // Cannot go out of arraybounds.
                // Placing the blocks.
                map[row][column] = value;
                column++;
                lengthCounter++;
            }      
        } // Storage the blocks in secondMap when row is negative.
        else if (row < 0) {
            while (lengthCounter <= length && (column >= 0 && column < SIZE) 
            && length <= SIZE && row > -SIZE2) {
                int y = abs(row) - 1;
                secondMap[y][column] = value;
                column++;
                lengthCounter++;
            }           
        }
        lineCounter++;
    }   
}


// Print out the contents of the map array. Then print out the player line
// which will depends on the playerX variable.
void printMap(int map[SIZE][SIZE], int playerX) {
    // Print values from the map array.
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            printf("%d ", map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }    
    
    // Print the player line.
    i = 0;
    while (i < playerX) {
        printf("  ");
        i++;
    }
    printf("P\n");
}


// The laser will destroy at most 3 stones above the player.
// When destroy TNT block, the blocks around the TNT disappear.
void fireLaser (int map[SIZE][SIZE], int playerX) {
    int destroyCounter = 1;
    int tntCounter = 0;
    int lineCounter = SIZE - 1;           
    while (lineCounter >= 0 && destroyCounter <= 3 && tntCounter == 0) {   
        // Find the blocks.
        if (map[lineCounter][playerX] == STONE || map[lineCounter][playerX] == 
        MARCHING) {
            // Eliminate the stone and marching blocks.
            destroyCounter++;                    
            map[lineCounter][playerX] = EMPTY;
        } 
        
        //If the value is in the range 3-9, the block is a TNT block.
        else if (map[lineCounter][playerX] >= 3 && map[lineCounter][playerX] 
        <= 9) {
            int TNT = map[lineCounter][playerX];// Radius of TNT.
            tntBlocks(map, lineCounter, playerX, TNT);
            tntCounter++;
        }
        lineCounter--;
    } 
    printMap(map, playerX);                               
}


// Check if the the map doesn't have any STONE, the game won.
int checkWin(int map[SIZE][SIZE]) {
    int lineCounter = 0;
    while (lineCounter < SIZE) {
        int colCounter = 0;
        while (colCounter < SIZE) {
            if (map[lineCounter][colCounter] != EMPTY) {
                return 0;
            }
            colCounter++;
        }
        lineCounter++;
    }
    return WIN;
}


// Check if there is any STONE on the last row, the game lose.
int checkLose(int map[SIZE][SIZE]) {
    int lastRow = SIZE - 1;
    int colCounter = 0;
    while (colCounter < SIZE - 1) {
        if (map[lastRow][colCounter] != EMPTY) {
            return LOSE;
        }
        colCounter++;
    }
    return 0;
}

// Move up the blocks in the secondMap until they are in first row.
// Then the first row in secondMap become the first row in map.
void moveDownAboveBlocks(int map[SIZE][SIZE], int secondMap[SIZE2][SIZE]) {
    int colCounter = 0;            
    while (colCounter < SIZE) {// First row in secondMap move to map.
        map[0][colCounter] = secondMap[0][colCounter];
        secondMap[0][colCounter] = EMPTY;
        colCounter++;
    }
    
    // Move up blocks in secondMap.
    int rowCounter = 0;                       
    while (rowCounter < SIZE2 - 1) {// NextLine < SIZE2.
        colCounter = 0;
        while (colCounter < SIZE) {                     
            secondMap[rowCounter][colCounter] =
            secondMap[rowCounter + 1][colCounter];   
            colCounter++;
        }
        rowCounter++;
    }           
}


// Swap the values of the integers that the pointers a and b aim at.
void swapNums(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Verical flip command.
// Flip the entire map vertically.
void verticalFlip(int map[SIZE][SIZE]) {
    int lineCounter = 0;
    int midSize = (SIZE - 1) / 2;
    while (lineCounter < midSize) {
        int verLine = SIZE - 1 - lineCounter;
        int colCounter = 0;
        while (colCounter < SIZE) {
            swapNums(&map[lineCounter][colCounter], 
            &map[verLine][colCounter]);
            colCounter++;
        }
        lineCounter++;
    }
}

// Remove the stones around the TNT.
void tntBlocks(int map[SIZE][SIZE], int i, int j, int TNT) {
    int rowCounter = 0;
    while (rowCounter < SIZE) {
        int colCounter = 0;
        while (colCounter < SIZE) {
            int distance = sqrt (pow ((rowCounter - i), 2) + 
            pow ((colCounter - j), 2));
            if (distance < TNT) {
                map[rowCounter][colCounter] = EMPTY;
            }
            colCounter++;
        }
        rowCounter++;
    }
}

// This function move the blocks when command = 3.
void shiftDownMarchingBlock(int map[SIZE][SIZE], int n) {
    int lineCounter = SIZE - 2;
    while (lineCounter >= 0) {
        int rightCounter = SIZE - 1; // Count column from right to left.
        int leftCounter = 0; // Count column from left to right.
        int moveDown = lineCounter + 1;
        while (leftCounter < SIZE && rightCounter >= 0) {
            secondShift (leftCounter, rightCounter, map, n, lineCounter, 
            moveDown);
            rightCounter--;
            leftCounter++;
        }
        lineCounter--;
    }
}


// Shift blocks down and move the marching block down, left, right.
void secondShift (int leftCounter, int rightCounter, int map[SIZE][SIZE], 
int n, int lineCounter, int moveDown) {
    int moveLeft = leftCounter - 1;
    int moveRight = rightCounter + 1;
    if (map[lineCounter][leftCounter] != EMPTY && (n % 4 == 1 || n % 4 == 3)) {
        // Everthing move down.              
        map[moveDown][leftCounter] = map[lineCounter][leftCounter];
        map[lineCounter][leftCounter] = EMPTY;  
    } else if (n % 4 == 0) {             
        if (map[lineCounter][leftCounter] == MARCHING && moveLeft >= 0) {
            // The marching blocks move left.
            map[lineCounter][moveLeft] = MARCHING;
            map[lineCounter][leftCounter] = EMPTY;
        } else if (map[lineCounter][leftCounter] != MARCHING && 
        map[moveDown][leftCounter] == EMPTY) {// Move stones and TNT down.
            map[moveDown][leftCounter] = map[lineCounter][leftCounter];
            map[lineCounter][leftCounter] = EMPTY;   
        } else if (map[lineCounter][leftCounter] != MARCHING && 
        map[moveDown][leftCounter] == MARCHING) {
            // Stone and TNT are eliminated by marching blocks.
            map[lineCounter][leftCounter] = EMPTY;  
        }               
    } else if (n % 4 == 2) {           
        if (map[lineCounter][rightCounter] == MARCHING && moveRight < SIZE) {
            // Move marching blocks right.
            map[lineCounter][moveRight] = MARCHING;
            map[lineCounter][rightCounter] = EMPTY;
        } else if (map[lineCounter][rightCounter] != MARCHING && 
        map[moveDown][rightCounter] == EMPTY) {
            // Move TNT and stones down
            map[moveDown][rightCounter] = map[lineCounter][rightCounter];
            map[lineCounter][rightCounter] = EMPTY; 
        } else if (map[lineCounter][rightCounter] != MARCHING && 
        map[moveDown][rightCounter] == MARCHING) {
            // Stone and TNT are eliminated by marching blocks.
            map[lineCounter][rightCounter] = EMPTY;  
        }
    }
}

// If the direction argument is 1, the gravity storm is towards the left.
// All blocks fall towards the left until they hit an edge or another block.
void shiftLeft(int map[SIZE][SIZE]) {
    int rowCounter = 0;
    while (rowCounter < SIZE) {
        int colCounter = 0;
        int moveLeft = 0;
        while (colCounter < SIZE) {
            if (map[rowCounter][colCounter] != EMPTY && colCounter != moveLeft) 
            {                
                map[rowCounter][moveLeft] = map[rowCounter][colCounter];
                map[rowCounter][colCounter] = EMPTY;
                moveLeft++; 
            } else if (map[rowCounter][colCounter] != EMPTY && 
            colCounter == moveLeft) {
                moveLeft++;
            }     
            colCounter++;        
        }
        rowCounter++;
    }    
}

// If the direction argument is 4, the gravity storm is towards the right.
// All blocks fall towards the right until they hit an edge or another block.
void shiftRight(int map[SIZE][SIZE]) {
    int rowCounter = 0;
    while (rowCounter < SIZE) {
        int colCounter = SIZE - 1;
        int moveRight = SIZE - 1;
        while (colCounter >= 0) {
            if (map[rowCounter][colCounter] != EMPTY && colCounter != 
            moveRight) 
            {                
                map[rowCounter][moveRight] = map[rowCounter][colCounter];
                map[rowCounter][colCounter] = EMPTY;
                moveRight--; 
            } else if (map[rowCounter][colCounter] != EMPTY && colCounter == 
            moveRight) {
                moveRight--;
            }     
            colCounter--;        
        }
        rowCounter++;
    }       
}

// If the direction argument is 2, the gravity storm is towards the top-left.
// All blocks fall towards the top-left until they hit an edge or another block.
void shiftTopLeft (int map[SIZE][SIZE]) {
    int rowCounter = 0;
    while (rowCounter < SIZE) {
        int colCounter = 0;        
        while (colCounter < SIZE) {
            secondTopLeft(map, rowCounter, colCounter);
            colCounter++;        
        }
        rowCounter++;
    }       
}

// Move everthing to top left.
void secondTopLeft (int map[SIZE][SIZE], int rowCounter, int colCounter) {
    int moveUp = rowCounter - 1;
    int moveLeft = colCounter - 1;            
    if (map[rowCounter][colCounter] != EMPTY && colCounter > 0 && 
    rowCounter > 0) {           
        while (moveUp >= 0 && moveLeft >= 0 && map[moveUp][moveLeft] == EMPTY) {
            map[moveUp][moveLeft] = map[moveUp + 1][moveLeft + 1];
            map[moveUp + 1][moveLeft + 1] = EMPTY;
            moveUp--;
            moveLeft--;                   
        }
    } 
}

// If the direction argument is 3, the gravity storm is towards the top-right.
// All blocks fall towards the top-right 
// until they hit an edge or another block.
void shiftTopRight (int map[SIZE][SIZE]) {
    int rowCounter = 0;
    while (rowCounter < SIZE) {
        int colCounter = SIZE - 1;        
        while (colCounter >= 0) {
            secondTopRight(map, colCounter, rowCounter);
            colCounter--;        
        }
        rowCounter++;
    }       
}

// Move everthing to top right.
void secondTopRight (int map[SIZE][SIZE], int colCounter, int rowCounter) {
    int moveUp = rowCounter - 1;
    int moveRight = colCounter + 1;            
    if (map[rowCounter][colCounter] != EMPTY && colCounter < SIZE - 1 
    && rowCounter > 0) {           
        while (moveUp >= 0 && moveRight <= SIZE - 1 && map[moveUp][moveRight] 
        == EMPTY) {
            map[moveUp][moveRight] = map[moveUp + 1][moveRight - 1];
            map[moveUp + 1][moveRight - 1] = EMPTY;
            moveUp--;
            moveRight++;                   
        }
    } 
}



