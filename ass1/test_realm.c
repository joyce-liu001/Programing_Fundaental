// Assignment 2 20T2 COMP1511: Castle Defense
//
// This program was written by Zhaoyan LIU(z5271698)
// on 08-08-2020
//
// Version 1.0.0 (2020-07-20): Assignment released.
// Version 1.0.1 (2020-07-21): Add return value to main.
// Version 1.1.0 (2020-07-23): Add test_apply_buff to main.

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "realm.h"
#include "test_realm.h"
#include "capture.h"

////////////////////////////////////////////////////////////////////
//                        Function Protoypes                      //
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
//                         Helper Functions                       //
////////////////////////////////////////////////////////////////////

// Find the string 'needle' in 'haystack'
int string_contains(char *haystack, char *needle) {
    return strstr(haystack, needle) != NULL;
}

// NOTE: You should not declare any structs from realm.c here.
// Declaring structs from realm.c in this function is against the
// rules of the assignment. 

// Main function: this function will not be used in testing, you do not
// need to change it.
// If you want to write your own tests, add them in `extra_tests`.
int main(int argc, char *argv[]) {
    printf("\n================== Castle Defense Tests ==================\n");

    test_add_location();
    test_print_realm();
    test_new_enemy();
    test_new_tower();
    test_apply_damage();
    test_apply_buff();
    extra_tests();

    return 0;
}

// NOTE: These tests are explained in `test_realm.h`

void test_add_location(void) {
    printf("Test whether this add_location follows the spec: ");

    // Test 1: Does add_location's return value count the Castle & Lair?

    Realm test_realm = new_realm();
    
    int num_locations = add_location(test_realm, "Location");   
        
    if (num_locations != 3) {
        printf(DOES_NOT_FOLLOW_SPEC);
        // since we don't want to print FOLLOWS_SPEC at the end,
        // we just return to the main function here.
        return;
    } 

    // Test 2: Does add_location return the correct amount for lots of locations?   
 
    int counter = num_locations;
    char my_str[100];
    while (counter < 70) {        
        sprintf(my_str, "Location_%d", counter);
        num_locations = add_location(test_realm, my_str);
        counter++;        
    }
       
    if (num_locations != counter) {
        printf(DOES_NOT_FOLLOW_SPEC);       
        return;
    } 
    
    // Test 3: Does this function add correct amount for lots of locations?
     
    counter = num_locations;
    while (counter < 80) {        
        sprintf(my_str, "Location_%d", counter);
        num_locations = add_location(test_realm, my_str);
        counter++;        
    }
    
    // Except castle and lair.
    counter = counter - 2;
    num_locations = num_locations - 2;
    if (counter != num_locations) {
        printf(DOES_NOT_FOLLOW_SPEC);       
        return;  
    }
   
    printf(FOLLOWS_SPEC);
}

void test_print_realm(void) {
    printf("Test whether this print_realm follows the spec: ");

    // Test 1: Does print_realm show the Castle?

    Realm test_realm2 = new_realm();   

    char print_text[10000];
    CAPTURE(print_realm(test_realm2), print_text, 10000);

    if (!string_contains(print_text, "Castle")) {
        printf(DOES_NOT_FOLLOW_SPEC);
        // since we don't want to print FOLLOWS_SPEC at the end,
        // we just return to the main function here.
        return;
    }

    // Test 2: Does print_realm show the correct HP of the castle?
    
    // In test_realm2, there only has castle and lair, 
    // and only castle contain 100 HP.
    if (!string_contains(print_text, "100")) {
        printf(DOES_NOT_FOLLOW_SPEC);
        return;
    }
   

    // Test 3: Does print_realm show the Lair?
    
    if (!string_contains(print_text, "Lair")) {
        printf(DOES_NOT_FOLLOW_SPEC);
        return;   
    }

    printf(FOLLOWS_SPEC);
    
}

// Stage 2

void test_new_enemy(void) {
    printf("Test whether this new_enemy follows the spec: ");

    // Test 1: Does new_enemy work if you're adding to the Lair?

    Realm test_realm = new_realm();
    int enemy = new_enemy(test_realm, "Lair", "enemy", 2);
    
    char print_text[10000];
    CAPTURE(print_realm(test_realm), print_text, 10000);
    
    // Whether we can find the "enemy" in the realm or not?
    if (!string_contains(print_text, "enemy") && enemy != SUCCESS) {
        printf(DOES_NOT_FOLLOW_SPEC);
        return;
    }
    
   
    // Test 2: Can we add new_enemy whith hp < 1?
    
    int enemy2 = new_enemy(test_realm, "Lair", "enemy2", 0);
    
    if (enemy2 != ERROR_INVALID_STAT) {
        printf(DOES_NOT_FOLLOW_SPEC);
        return;
    }

    printf(FOLLOWS_SPEC);
}

void test_new_tower(void) {
    printf("Test whether this new_tower follows the spec: ");

    // Test 1: Does new_tower work if you're adding after another tower?
    
    Realm test_realm = new_realm();
    int tower = new_tower(test_realm, "Castle", "tower1", 2, 3);
    tower = new_tower(test_realm, "tower1", "tower2", 2, 3);
    
    char print_text[10000];
    CAPTURE(print_realm(test_realm), print_text, 10000);
    
    // Whether we can find the "tower2" in the realm or not?
    if (!string_contains(print_text, "tower2") && tower != SUCCESS) {
        printf(DOES_NOT_FOLLOW_SPEC);
        return;
    }
    

    // Test 2: Does new_tower work if you're adding a tower after 
    // where it doesn't exist?
    
    tower = new_tower(test_realm, "X", "tower3", 2, 3);
    if (tower != ERROR_NO_LOCATION) {
        printf(DOES_NOT_FOLLOW_SPEC);
        return;
    } 

    printf(FOLLOWS_SPEC);
}

// Stage 3 (2 marks)

void test_apply_damage(void) {
    printf("Test whether this apply_damage follows the spec: ");

    // Test 1: Does apply_damage actually destroy enemies?
    
    Realm test_realm = new_realm();
    int hp = 2;
    new_tower(test_realm, "Castle", "tower1", hp, 4);
    new_enemy(test_realm, "tower1", "Tom", hp);
    apply_damage(test_realm);
    
    char print_text[10000];
    CAPTURE(print_realm(test_realm), print_text, 10000);
    
    // Whether we can find enemy "Tom" or not?
    if (strstr(print_text, "Tom") != NULL) {
        printf(DOES_NOT_FOLLOW_SPEC);
        return;
    }


    // Test 2: Does apply_damage return the correct amount for damage enemy?   
    
    new_enemy(test_realm, "tower1", "Tow", hp);
    new_enemy(test_realm, "tower1", "Twm", hp);
    new_enemy(test_realm, "tower1", "Tee", hp);
    
    int damage = apply_damage(test_realm);
    if (damage != 3) {
        printf(DOES_NOT_FOLLOW_SPEC);
        return;
    }
    
    printf(FOLLOWS_SPEC);
}

// Stage 4 (1 marks)

void test_apply_buff(void) {
    printf("Test whether this apply_buff follows the spec: ");
    
    // Test 1: Does apply_buff return the correct amount towers 
    // for search_name we found?  
    
    Realm test_realm = new_realm();
    Buff buff_type = BUFF_TOWER_POWER;
    new_tower(test_realm, "Castle", "tower1", 2, 3);
    new_tower(test_realm, "Castle", "tower2", 2, 3);
    new_tower(test_realm, "Castle", "tOwer3", 2, 3);
    int search = apply_buff(test_realm, "tower[123]", buff_type, 1);
    
    
    // "tower1" and "tower2" should be found.
    if (search != 2) {
        printf(DOES_NOT_FOLLOW_SPEC);
        return;
    }

    
    // Test 2: Does apply_buff actually destroy enemies?
    
    int hp = 2;
    new_enemy(test_realm, "tower1", "Tom", hp);
    buff_type = BUFF_ENEMY_HP;
    apply_buff(test_realm, "Tom", buff_type, -2);
    
    char print_text[10000];
    CAPTURE(print_realm(test_realm), print_text, 10000);
    
    // We can find enemy "Tom" because Tom's cur_hp = 0. It should be destroied.
    if (strstr(print_text, "Tom") != NULL) {
        printf(DOES_NOT_FOLLOW_SPEC);
        return;
    }
    
    printf(FOLLOWS_SPEC);
}


void extra_tests(void) {
    // TODO: add extra tests, if you'd like to.
}
