// Assignment 2 20T2 COMP1511: Castle Defense
//
// This program was written by Zhaoyan LIU (z5271698)
// on 08-08-2020
//
// Version 1.0.0 (2020-07-20): Assignment released.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "realm.h"

#define NO_RESULT 1
#define RESULT 0
#define DIED 0 
#define USELESS 0

///////////////////////////////////////////////////////////////////////

// `struct realm` represents a realm, which represents the state of the
// entire program. It is mainly used to point to a linked list of 
// locations, though you may want to add other fields to it.
//
// You may need to add fields to struct realm.
struct realm {
    struct location *castle;
    struct location *lair;
};


// `struct location` represents a location, which could be a land,
// a tower, or a castle. Each of those places has a different type
// of information that this struct will need to store.
//
// You will need to add fields to struct location.
struct location {
    
    char name[MAX_NAME_LENGTH];
    struct enemy *enemies;
    struct location *next;
    int type;
    
    // Only tower has power, effect and uses.
    // When type = castle, power will be the defense.
    int power;
    int uses;
    int effect;

};


// `struct enemy` represents an enemy, which will move through the
// realm (to each location). Towers can deal damage to it, and
// it can deal damage to the Castle.
//
// You will need to add fields to struct enemy.
struct enemy {
    char name[MAX_NAME_LENGTH];
    int cur_hp;
    int max_hp;
    struct enemy *next;
};



///////////////////////////////////////////////////////////////////////

// Function prototypes for helper functions
static Location new_location(char *name);
static void print_tower(char *name, int power, int uses, Effect effect);
static void print_land(char *name);
static void print_castle(char *name, int defense);
static void print_enemy(char *name, int cur_hp, int max_hp);


// Add prototypes for any extra functions you create here.
static int search(char *name, char *search_name);
static int character_class(char *name, char *search_name, int counter, 
int nameCount);
static void move_next(Realm realm, Location position, Location pre_position);
static void move_to_lair(Realm realm, Location position);
static int buff_on_enemy(Realm realm, Location position, char *search_term, int amount, int number);



///////////////////////////////////////////////////////////////////////

// You need to implement the following 9 functions.
// In other words, write code to make the function work as described 
// in realm.h.

// Create a new realm, and return a pointer to it.
// Realm only contains castle and lair at first. And connect them.
Realm new_realm(void) {
    
    // Create realm with malloc.
    struct realm *realm = malloc(sizeof(struct realm));
    realm->castle = new_location("Castle");
    realm->castle->type = TYPE_CASTLE;
    realm->castle->power = STARTING_CASTLE_HP;
    
    realm->lair = new_location("Lair");
    
    // Connect castle and lair.
    if (realm->castle != NULL && realm->lair != NULL) {
        realm->castle->next = realm->lair;
    }

    return realm;
}


// Return a new location created with malloc.
static Location new_location(char *name) {
        
    // Create a location
    struct location *newLocation = malloc(sizeof(struct location));
    
    strcpy(newLocation->name, name);
    newLocation->next = NULL; 
    newLocation->enemies = NULL;
    newLocation->type = TYPE_LAND;
    
    // Land doesn't need this information，we still need give the stats.
    newLocation->power = 0;
    newLocation->uses = 0;
    newLocation->effect= EFFECT_NONE;
   
    return newLocation;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add a new location before lair to the realm, and return the total number of
// locations in the realm.
int add_location(Realm realm, char *name) {
     
    struct location *prev = NULL;
    struct location *position = realm->castle;    
    while (position != realm->lair) {
        // Find position before lair.          
        prev = position;
        position = position->next;
    } 

    // Insert a new location in the position.
    struct location *insertLocation = new_location(name);
    insertLocation->next = position;
    prev->next = insertLocation;
    
    // Count realm's locations.
    int counter = 0;
    struct location *countLocation = realm->castle;
    while (countLocation != NULL) {       
        counter++;
        countLocation = countLocation->next;
    }  
      
    return counter; 
}


// Print out the realm.
void print_realm(Realm realm) {
    
    struct location *position = realm->castle;   
    
    while (position != NULL) {        
        
        // Print every location.
        if (position->type == TYPE_CASTLE) {
            print_castle(realm->castle->name, realm->castle->power);
        } else if (position->type == TYPE_TOWER) {
            print_tower(position->name, position->power, position->uses, 
            position->effect);
        } else if (position->type == TYPE_LAND) {       
            print_land(position->name); 
        }
        
        // Print every enemy at this location. 
        Enemy enemy = position->enemies;            
        while (enemy != NULL) {
            print_enemy(enemy->name, enemy->cur_hp, enemy->max_hp); 
            enemy = enemy->next;
        } 
        
        position = position->next;
    }       
}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add an enemy to the realm.
int new_enemy(Realm realm, char *location_name, char *name, int hp) {

    // Find location called location_name.
    Location position = realm->castle;    
    while (position != NULL && strcmp(location_name, position->name) != 0) {
        position = position->next;   
    }
        
    if (position == NULL) {
        // When the location called location_name does not exist.
        return ERROR_NO_LOCATION;
    }
    
    if (hp <= DIED) {
        // Ensure that the stats you have been given for HP must greater than 0.
        return ERROR_INVALID_STAT;
    }
    
    
    // Only receive enemies in sorted order, 
    // and will never receive the same enemy name twice.
    Enemy enemy = position->enemies;
    while (enemy != NULL && strcmp(enemy->name, name) < 0) {               
        enemy = enemy->next;        
    }
    
    if (enemy != NULL) {
        printf("Enemy Names were provided out of order!\n"); 
        printf("This will not happen. You do not need to handle this.\n");
        return NO_RESULT;
    }
    
   
    // Create a newEnemy with malloc.
    struct enemy *newEnemy = malloc(sizeof(struct enemy));
    strcpy(newEnemy->name, name);
    newEnemy->cur_hp = hp;
    newEnemy->max_hp = hp;
    newEnemy->next = NULL;    
    
    if (position->enemies == NULL) {
        // There is no enemy on the position, 
        // insert newEnemy in to position->enemies.
        position->enemies = newEnemy;      
    
    } else {
        Enemy lastEnemy = position->enemies;
                
        while (lastEnemy->next != NULL) {
            // Find the last enemy in the position.
            lastEnemy = lastEnemy->next;
        }
        
        // Insert enemy after the last enemy at this position.     
        lastEnemy->next = newEnemy;            
    } 
        
    return SUCCESS;   
}



// Add a new tower to the realm.
int new_tower(Realm realm, char *prev_name, char *name, int power, int uses) {
    
    // Power and uses must greater than 1.
    if (power <= USELESS || uses <= USELESS) {
        return ERROR_INVALID_STAT;
    }
    
    // Find prev_name position.
    struct location *position = realm->castle;    
    while (position != NULL && strcmp(position->name, prev_name)) {
        position = position->next;          
    }
    
    if (position == NULL) { 
        // No position called prev_name.
        return ERROR_NO_LOCATION;
    }
    
    // Follow the sample solution, we cannot add tower after the lair.
    if (prev_name == realm->lair->name) {
        printf("You will never be asked to add a tower below the Lair.\n");
        printf("You do not need to handle this case.");
        return NO_RESULT;
    }
    
    // Create a tower with malloc.
    struct location *addTower = malloc(sizeof(struct location));
    strcpy(addTower->name, name);
    addTower->power = power;
    addTower->uses = uses;
    addTower->next = NULL;
    addTower->type = TYPE_TOWER;
    addTower->effect = EFFECT_NONE;
    addTower->enemies = NULL;
       
    // Insert tower after position.
    addTower->next = position->next;
    position->next = addTower;
        
    return SUCCESS;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

// Destroy the realm, and free any associated memory.
void destroy_realm(Realm realm) {
    Location position = realm->castle;   
    Location head =  realm->castle;
    
    while (position != NULL) {        
        Enemy enemy = position->enemies;   
        
        // Free enemies at position.
        while (enemy != NULL) {          
            position->enemies = enemy->next;
            free (enemy);
            enemy = position->enemies;
        } 
        
        // Free locations.      
        head = position->next;
        free(position);
        position = head;
    }
    
    // Free realm.
    free(realm);
}

// Advance enemies towards the castle.
int advance_enemies(Realm realm) {
    
    // Count number of enemies will be removed.
    int counter = 0;
    
    Location position = realm->castle;
    Location pre = NULL;
    Enemy enemy = NULL;
    
    while (position != NULL) {
        
        if (position == realm->castle) {
            // When position = castle, free enemies at castle.
            while (position->enemies != NULL) {       
                enemy = position->enemies;
                position->enemies = position->enemies->next;
                free(enemy);
                counter++;
            }
            
        } else { // Move all enemies from this position to pre.
            if (position->enemies != NULL) {
                enemy = position->enemies;
                pre->enemies = enemy;
                position->enemies = NULL;
            }
        }
        
        pre = position;
        position = position->next;
    }  
    
    // Apply the effect.
    position = realm->castle;
    pre = NULL;
    while (position != NULL) {
                      
        if (position->type == TYPE_TOWER && position->effect == EFFECT_ICE) {
            // We already move all the enemies to previous position.
            // We need to return the enemy (which hp < pre->power) 
            // that used to belong to Ice Tower.          
            move_next(realm, position, pre); 
        
        } else if (position->type == TYPE_TOWER && position->effect == 
        EFFECT_PORTAL) { // Apply portal effect.
            if (position->enemies != NULL) {
                // Move all enemies at this tower 
                // (which effect is EFFECT_PORTAL) to lair.
                move_to_lair(realm, position);
                position->effect = EFFECT_NONE;
            }
        }
        
        pre = position;
        position = position->next;
    }
    
    return counter;
}

// Apply damage from the enemies at each tower to that tower.
int apply_damage(Realm realm) {
    
    Location position = realm->castle;
    Enemy enemy = position->enemies;
    
    // Count the number of enemies be damaged.
    int damage = 0;
      
    // The Castle's defense to decrease by the sum 
    // of the HP of enemy at the Castle.
    int sum = 0;
    while (enemy != NULL) {
        sum = sum + enemy->cur_hp;
        enemy = enemy->next;
    }     
    position->power = position->power - sum;
    
    // Move position to castle next.
    position = position->next;
        
    while (position != NULL) {
        enemy = position->enemies;
        if (position->type == TYPE_TOWER && position->enemies != NULL) {    
            position->uses--;
            
            // Damage the enemies.
            while (enemy != NULL) {
                enemy->cur_hp = enemy->cur_hp - position->power;
                damage++;                
                enemy = enemy->next;
            }            
        } 
        
        // Remove the enemies which hp <= 0.
        enemy = position->enemies;
        Enemy pre_enemy = NULL;
        while (enemy != NULL) {
            
            // When the enemy is the first enemy at position.
            if (enemy->cur_hp <= DIED && enemy == position->enemies) {
                position->enemies = enemy->next;
                free(enemy);
                enemy = position->enemies;
            }
            
            // When the enemy not the first enemy at position.               
            else if (enemy->cur_hp <= DIED && enemy != position->enemies) {
                pre_enemy->next = enemy->next;
                free(enemy);
                enemy = pre_enemy->next;               
            } 
            
            else { // Enemy's hp > 0.
                pre_enemy = enemy;
                enemy = enemy->next;
            }
        }
            
        // If that Tower now has no uses remaining, convert it into a Land.
        if (position->uses <= USELESS) {
            position->type = TYPE_LAND;
        }
           
        position = position->next;
    }
        
    return damage;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

// Apply the specified buff to the relevant towers or enemies.
int apply_buff(Realm realm, char *search_term, Buff buff, int amount){
        
    // Count number of search_name we found.
    int number = 0;
    Location position = realm->castle;
    
    if (buff == BUFF_ENEMY_HP || buff == BUFF_ENEMY_HP_CHAR) {      
        number = buff_on_enemy(realm, position, search_term, amount, number);
    
    } else if (buff == BUFF_TOWER_POWER || buff == BUFF_TOWER_POWER_CHAR) {
        
        // Find all towers in the Realm with a name that matches 
        // the search described by search_name.
        while (position != NULL) {
            
            if (search(position->name, search_term) == RESULT && 
            position->type == TYPE_TOWER) {
                // Increase each of their power by the specified amount.
                position->power = position->power + amount;
                number++;   
            }
            
            // If tower to drop below 1 power, it should be converted to a land.
            if (position->power < 1 && position->type == TYPE_TOWER) {
                position->type = TYPE_LAND;           
            }
            
            position = position->next;
        }
    
    } else if (buff == BUFF_TOWER_USES || buff == BUFF_TOWER_USES_CHAR) {
        
        // Find all towers in the Realm with a name that matches 
        // the search described by search_name. 
        while (position != NULL) {
            if (search(position->name, search_term) == RESULT && 
            position->type == TYPE_TOWER) {
                // Increase each of their uses by the specified amount.
                position->uses = position->uses + amount;
                number++;   
            }
            
            // If tower to drop below 1 use, it should be converted to a land.
            if (position->uses <= USELESS && position->type == TYPE_TOWER) {
                position->type = TYPE_LAND;           
            }
            
            position = position->next;
        }                       
    }
        
    return number;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

// Apply the specified effect to each tower whose name matches the
// specified search term.
int apply_effect(Realm realm, char *search_term, Effect effect) {
    
    // Count number of search_name we found.
    int number = 0;
    Location position = realm->castle;
    
    if (effect == EFFECT_NONE) {
        // Find all towers in the Realm with a name that matches 
        // the search described by search_name.
        while (position != NULL) {
            
            if (search(position->name, search_term) == RESULT && 
            position->type == TYPE_TOWER) {               
                position->effect = EFFECT_NONE;             
                number++;   
            }
                
            position = position->next;          
        } 
         
    } else if (effect == EFFECT_ICE) {
        
        // Find all towers in the Realm with a name that matches 
        // the search described by search_name.
        while (position != NULL) {
            
            if (search(position->name, search_term) == RESULT && 
            position->type == TYPE_TOWER) {               
                position->effect = EFFECT_ICE;             
                number++;   
            }
                
            position = position->next;          
        } 
            
    } else if (effect == EFFECT_PORTAL) {
        
        // Find all towers in the Realm with a name that matches 
        // the search described by search_name. 
        while (position != NULL) {                      
            if (search(position->name, search_term) == RESULT && 
            position->type == TYPE_TOWER) {
                position->effect = EFFECT_PORTAL;        
                number++;   
            }
            position = position->next;
        }
                       
    }
        
    return number;
}

////////////////////////////////////////////////////////////////////////

// Add definitions for your own functions below.
// Make them static to limit their scope to this file.

// Find all enemy matches the search search_name, and increase hp by amount.
// Destroy enemy when its hp <= 0.
int buff_on_enemy(Realm realm, Location position, char *search_term, int 
amount, int number) {
    while (position != NULL) {           
        Enemy enemy = position->enemies;           
        Enemy pre_enemy = position->enemies;           
            
        while (enemy != NULL) {
            if (search(enemy->name, search_term) == RESULT) {
                // Increase each of their HP by the specified amount.    
                enemy->cur_hp = enemy->cur_hp + amount;
                number++; 
            }  
                    
            // If an Enemy to drop to zero or less HP, it dies.
            if (enemy->cur_hp <= DIED && enemy == position->enemies) {
                position->enemies = enemy->next;
                free(enemy);
                enemy = position->enemies;                    
            } else if (enemy->cur_hp <= DIED && enemy != position->enemies) {
                pre_enemy->next = enemy->next;
                free(enemy);
                enemy = pre_enemy->next;               
            } else {                                      
                pre_enemy = enemy;
                enemy = enemy->next;
            }          
        }
            
        position = position->next;        
    }
    return number;
}



// Move pre_position's enemies to position the enemy's 
// cur_hp < position's power.
// And position->effect is EFFECT_ICE.
void move_next(Realm realm, Location position, Location pre_position) {
    
    // Find the pre_position's enemies which cur_hp is less than 
    // position's power and move it to the position's enemies.     
    Enemy less = pre_position->enemies;
    Enemy pre_less = NULL;
    while (less != NULL) {
        
        // The enemy 'less' is the first enemy at pre_position.
        if (less->cur_hp < position->power && pre_less == NULL) {
            
            // Create a insert_enemy with malloc, this enemy contains all 
            // information about less.
            Enemy insert_enemy = malloc(sizeof(struct enemy));
            strcpy(insert_enemy->name, less->name);
            insert_enemy->next = NULL;
            insert_enemy->cur_hp = less->cur_hp;
            insert_enemy->max_hp = less->max_hp;
                       
            // Find enemy which name is greater than less->name, 
            // then insert insert_enemy before this enemy.
            Enemy enemy = position->enemies;
            Enemy pre_enemy = NULL;                  
            while (enemy != NULL && strcmp(less->name, enemy->name) > 0) {
                pre_enemy = enemy;
                enemy = enemy->next;
            }          
            
            if (pre_enemy == NULL) { // We insert at the start of enemy list.
                position->enemies = insert_enemy;  
                insert_enemy->next = enemy;
            } else { 
                pre_enemy->next = insert_enemy;
                insert_enemy->next = enemy;
            }
            
            pre_position->enemies = less->next;
            free(less);
            less = pre_position->enemies; 
        }
        
        // The enemy 'less' in not the first enemy at pre_location.         
        else if (less->cur_hp < position->power && pre_less != NULL) {
           
            // Create a insert_enemy with malloc, this enemy contains all 
            // information about less.
            Enemy insert_enemy = malloc(sizeof(struct enemy));
            strcpy(insert_enemy->name, less->name);
            insert_enemy->next = NULL;
            insert_enemy->cur_hp = less->cur_hp;
            insert_enemy->max_hp = less->max_hp;
            
            // Find enemy which name is greater than less->name,
            // then put inser_enemy before enemy.
            Enemy enemy = position->enemies;
            Enemy pre_enemy = NULL;                      
            while (enemy != NULL && strcmp(less->name, enemy->name) > 0) {
                pre_enemy = enemy;
                enemy = enemy->next;
            }          
            
            if (pre_enemy == NULL) { // We insert at the start of enemy list.
                position->enemies = insert_enemy;
                insert_enemy->next = enemy;  
            } else {
                pre_enemy->next = insert_enemy;
                insert_enemy->next = enemy;
            }
                      
            pre_less->next = less->next;
            free(less);
            less = pre_less->next;
        
        } else {
            pre_less = less;
            less = less->next;
        }
    }
    
} 



// When the tower's effect is EFFECT_PORTAL, 
// we move all enemies at this tower to the lair.
void move_to_lair(Realm realm, Location position) {
    Enemy enemy = position->enemies;
    while (enemy != NULL) {
        
        // Create a insert_enemy with malloc, this enemy contains all 
        // information about enemy at this tower.
        Enemy insert_enemy = malloc(sizeof(struct enemy));
        strcpy(insert_enemy->name, enemy->name);
        insert_enemy->next = NULL;
        insert_enemy->cur_hp = enemy->cur_hp;
        insert_enemy->max_hp = enemy->max_hp;
            
        // Find lair_enemy which name is greater than enemy->name,
        // then insert inser_enemy before lair_enemy.
        Enemy lair_enemy = realm->lair->enemies;
        Enemy pre_enemy = NULL;
        while (lair_enemy != NULL && strcmp(enemy->name, lair_enemy->name) > 0) 
        {
            pre_enemy = lair_enemy;
            lair_enemy = lair_enemy->next;
        }          
            
        if (pre_enemy == NULL) { // We insert at the start.
            realm->lair->enemies = insert_enemy;
            insert_enemy->next = lair_enemy;  
        } else {
            pre_enemy->next = insert_enemy;
            insert_enemy->next = lair_enemy;
        }
        
        position->enemies = enemy->next;  
        free(enemy);
        enemy = position->enemies;       
    }    
}



// Check if in search_name is match the name.
int search(char *name, char *search_name) {
    int counter = 0;
    int nameCount = 0;
    
    while (name[nameCount] != '\0' && search_name[counter] != '\0') {           
        
        // Character in name did not matche character in search_name.
        if (name[nameCount] != search_name[counter] && search_name[counter] 
        != '[') {
            return NO_RESULT;
        }
        
        // Compare the name[nameCount] and character in '['']' in search_name.
        else if (search_name[counter] == '[') {
            counter++;
            
            if (character_class(name, search_name, counter, nameCount) 
            == NO_RESULT) {
                return NO_RESULT;
            } 
                     
            while (search_name[counter] != ']') {
                counter++;
            }          
        }  
            
        counter++;
        nameCount++; 
    }  
    
    // The search use prefix match which is one where the word starts 
    // with the search term.
    if (search_name[counter] != '\0') {
        return NO_RESULT;
    }
    
    return RESULT;
}



// Check whether the name[nameCount] is in the character class [] 
// of search_name or not.
int character_class(char *name, char *search_name, int counter, int nameCount) {
    
    while (search_name[counter] != ']') {
        
        if (name[nameCount] == search_name[counter]) {
            // name[nameCount] is match one of the character in character class.
            return RESULT;       
        }
        
        if (search_name[counter] == '-') {
            // Whether name[nameCount] match a character between 
            // search_name[first] and search_name[last]. 
            int first = search_name[counter - 1];
            int last = search_name[counter + 1];
            if (name[nameCount] >= first && name[nameCount] <= last) {
                return RESULT;
            }
            
            counter++;
        }
                
        counter++;
    }
       
    return NO_RESULT;   
}

////////////////////////////////////////////////////////////////////////
//                    Provided print functions                        //
//         NOTE: YOU SHOULD NOT MODIFY THE FOLLOWING FUNCTIONS        //
////////////////////////////////////////////////////////////////////////

void print_tower(char *name, int power, int uses, int effect) {
    printf(" ^ %32s [pow: %3d | uses: %3d]", name, power, uses);
    if (effect == EFFECT_NONE) printf(" {%c}", EFFECT_NONE_CHAR);
    if (effect == EFFECT_PORTAL) printf(" {%c}", EFFECT_PORTAL_CHAR);
    if (effect == EFFECT_ICE) printf(" {%c}", EFFECT_ICE_CHAR);
    printf("\n");
}

void print_land(char *name) {
    printf(" ^ %32s [____________________]\n", name);
}

void print_castle(char *name, int defense) {
    printf(" ^ %32s [Castle Defenses: %3d]\n", name, defense);
}

void print_enemy(char *name, int cur_hp, int max_hp) {
    printf(" ^ %40s [hp: %d/%d]\n", name, cur_hp, max_hp);
}

////////////////////////////////////////////////////////////////////////
//               End of provided print functions                      //
////////////////////////////////////////////////////////////////////////




