//
// DO NOT CHANGE THIS FILE
//
// You do not submit this file. This file is not marked.
// If you think you need to change this file you have
// misunderstood the assignment - ask in the course forum.
//
// Assignment 2 20T2 COMP1511: Castle Defense
// main.c
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Fix typos, and print error message when 
//                trying to create invalid enemy.
// Version 1.1.0: Add nicer error messages for long inputs.
// Version 1.1.1: Move validity checks to after we scan strings.
// Version 1.1.2: File now says 20T2, rather than 19T2.
//
// This file allows you to interactively test the functions you
// implement in realm.c

#define MAX_COMMAND_LENGTH 512

#define MAX_NAME_ARRAY_SIZE (MAX_NAME_LENGTH + 1)
#define MAX_INVALID_NAME_ARRAY_SIZE (MAX_NAME_LENGTH*8 + 1)

// Commands

#define COMMAND_HELP '?'
#define COMMAND_QUIT 'q'
#define COMMAND_PRINT_STATE 'p'
#define COMMAND_GAME_TICK 'n'
#define COMMAND_APPLY_DAMAGE 'd'
#define COMMAND_APPLY_BUFF 'b'
#define COMMAND_APPLY_EFFECT 'f'
#define COMMAND_NEW_ENEMY 'e'
#define COMMAND_NEW_TOWER 't'
#define COMMAND_COMMENT '/'

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "realm.h"

Realm scan_realm(void);
int valid_name(char *name);
int valid_fgets_name(char *name);
void do_help(void);
void do_print_state(Realm realm);
void do_apply_buff(Realm realm, char *command);
void do_apply_effect(Realm realm, char *command);
void do_new_enemy(Realm realm, char *command);
void do_advance_enemies(Realm realm);
void do_apply_damage(Realm realm);
void do_new_tower(Realm realm, char *command);

int main(void) {
    printf("Welcome, brave and noble engineer.\n");
    printf(
        "Describe the realm below. Locations may not contain spaces.\n"
        "When you are done, enter an empty line: \n"
    );
    Realm realm = scan_realm();
    printf("\nWell done, now you may enter commands: \n");

    int exit = 0;
    while (!exit) {
        char command[MAX_COMMAND_LENGTH] = "";

        printf("\nEnter Command: ");

        char *result = fgets(command, MAX_COMMAND_LENGTH, stdin);
        char command_char = command[0];

        if (result == NULL) {
            printf("Ctrl+D Pressed, quitting.\n");
            exit = 1;
        } else if (command_char == COMMAND_QUIT) {
            exit = 1;
        } else if (command_char == COMMAND_PRINT_STATE) {
            do_print_state(realm);
        } else if (command_char == COMMAND_GAME_TICK) {
            do_advance_enemies(realm);
        } else if (command_char == COMMAND_APPLY_DAMAGE) {
            do_apply_damage(realm);
        } else if (command_char == COMMAND_APPLY_BUFF) {
            do_apply_buff(realm, command);
        } else if (command_char == COMMAND_APPLY_EFFECT) {
            do_apply_effect(realm, command);
        } else if (command_char == COMMAND_NEW_ENEMY) {
            do_new_enemy(realm, command);
        } else if (command_char == COMMAND_NEW_TOWER) {
            do_new_tower(realm, command);
        } else if (command_char == COMMAND_COMMENT) {
            continue;
        } else /* (COMMAND_HELP) */ {
            do_help();
        }
    }

    destroy_realm(realm);

    printf("Goodbye, brave and noble engineer.\n");
}

Realm scan_realm(void) {
    Realm realm = new_realm();
    int stop = 0;
    int num_places = 2;

    while (!stop) {
        char name[MAX_NAME_ARRAY_SIZE];
        char *did_scan = fgets(name, MAX_NAME_ARRAY_SIZE, stdin);


        if (did_scan == NULL) {
            printf(
                "You will never recieve an EOF when scanning in locations, "
                "what you do if this happens is up to you!\n"
            );
            exit(1);
        }

        if (!valid_fgets_name(name)) {
            printf(
                "You will never recieve a name string longer than"
                "MAX_NAME_LENGTH - 1 (%d).\n"
                "Giving a string this long may cause other functions"
                "to fail - what you do if this happens is up to you\n",
                MAX_NAME_LENGTH - 1
            );
            exit(1);
        }

        if (strchr(name, ' ') != NULL) {
            printf(
                "Place Names will never contain a space! "
                "You do not need to handle this error in your code."
            );
            exit(1);
        }

        // Replace the newline with a null terminator.
        // We know that there's a newline because valid_fgets_name
        // returned true.
        name[strlen(name) - 1] = '\0';

        if (name[0] == '\0') {
            stop = 1;
        } else {
            num_places = add_location(realm, name);
        }
    }

    printf("There are %d locations in your realm.\n", num_places);
    return realm;
}

// Checks whether the user entered more than MAX_NAME_LENGTH characters.
//
// fgets will read in at most size - 1 characters, including the newline (if
// there is a newline before it reads size - 1 characters), so we can just check
// whether a newline occured in the string at all.
//
// If we don't find a newline, then the user typed in too many characters, and
// so the name is invalid.
int valid_fgets_name(char *name) {

    int i = 0;
    while (i < MAX_NAME_ARRAY_SIZE && name[i] != '\0' && name[i] != '\n') {
        i++;
    }

    int valid = TRUE;

    // If we didn't find a newline, then the user typed in more than
    // MAX_NAME_LENGTH chars (so fgets couldn't read them all into the array),
    // and thus the name is not valid.
    if (name[i] != '\n') {
        valid = FALSE;
    }

    return valid;
}

int valid_name(char *name) {
    return (strlen(name) < MAX_NAME_LENGTH);
}

void do_help(void) {
    printf(""
        "============================[ Help ]============================\n"
    );

    printf(""
        "  %c\n"
        "     Show this Help Screen\n",
        COMMAND_HELP
    );
    printf(""
        "  %c\n"
        "     Quit Program\n",
        COMMAND_QUIT
    );
    printf(""
        "  %c\n"
        "     Print the current layout of the realm\n",
        COMMAND_PRINT_STATE
    );
    printf(""
        "\n  %c <after_location> <name> <power> <uses>\n"
        "     Create new tower after the specified location.\n",
        COMMAND_NEW_TOWER
    );
    printf(""
        "  %c\n"
        "     Advance Game State\n",
        COMMAND_GAME_TICK
    );
    printf(""
        "  %c\n"
        "     Apply Damage\n",
        COMMAND_APPLY_DAMAGE
    );
    printf(
        "\n  %c <after_location> <name> <hp>\n"
        "    Create new enemy after the specified location.\n",
        COMMAND_NEW_ENEMY
    );
    printf(
        "\n  %c <search_term> <buff_type> <amount>\n"
        "    (buff_type: enemy: '%c' for HP, tower: '%c' for power, '%c' for uses)\n"
        "    Apply the specified buff with specified amount, to all enemies (for HP) "
        "or towers (for power/uses) with prefix search_term\n",
        COMMAND_APPLY_BUFF,
        BUFF_ENEMY_HP_CHAR, BUFF_TOWER_POWER_CHAR, BUFF_TOWER_USES_CHAR
    );
    printf(
        "\n  %c <search_term> <effect_type>\n"
       "     (effect_type: '%c' for none, '%c' for portal, '%c' for ice)\n"
        "    Give all towers matching `search_term` the specified effect "
        "(replacing their old one, if any)\n",
        COMMAND_APPLY_EFFECT,
        EFFECT_NONE_CHAR, EFFECT_PORTAL_CHAR, EFFECT_ICE_CHAR
    );
}

void do_print_state(Realm realm){
    print_realm(realm);
}

void do_apply_buff(Realm realm, char *command) {
    char ignored_char, buff_type_char;
    char search_term[MAX_INVALID_NAME_ARRAY_SIZE];
    int amount;
    Buff buff_type = INVALID_INPUT;
    int num_scanned = sscanf(
        command, "%c %s %c %d",
        &ignored_char, search_term,
        &buff_type_char, &amount
    );
    if (num_scanned == 4) {
        if (!valid_name(search_term)) {
            printf(
                "The search term you entered was too long!\n"
                "You will never recieve a term like this.\n"
                "You do not need to handle this case.\n"
            );
            return;
        }
        if (buff_type_char == BUFF_ENEMY_HP_CHAR) {
            buff_type = BUFF_ENEMY_HP;
        } else if (buff_type_char == BUFF_TOWER_USES_CHAR) {
            buff_type = BUFF_TOWER_USES;
        } else if (buff_type_char == BUFF_TOWER_POWER_CHAR) {
            buff_type = BUFF_TOWER_POWER;
        }

        if (buff_type == INVALID_INPUT) {
            printf("Invalid Buff Type!\n");
        } else {
            int matches = apply_buff(realm, search_term, buff_type, amount);
            if (buff_type == BUFF_ENEMY_HP && matches != 1) {
                printf("%d enemies have been buffed!\n", matches);
            } else if (buff_type == BUFF_ENEMY_HP && matches == 1) {
                printf("%d enemy has been buffed!\n", matches);
            } else {
                printf("%d tower(s) have been buffed!\n", matches);
            }
        }
    } else {
        printf("Invalid command!\n");
    }

}

void do_apply_effect(Realm realm, char *command) {
    char ignored_char, effect_type_char;
    char search_term[MAX_INVALID_NAME_ARRAY_SIZE];
    Effect effect_type = INVALID_INPUT;

    int num_scanned = sscanf(
        command, "%c %64s %c",
        &ignored_char, search_term,
        &effect_type_char
    );

    if (num_scanned == 3) {
        if (!valid_name(search_term)) {
            printf(
                "The search term you entered was too long!\n"
                "You will never recieve a term like this.\n"
                "You do not need to handle this case.\n"
            );
            return;
        }
        if (effect_type_char == EFFECT_NONE_CHAR) {
            effect_type = EFFECT_NONE;
        } else if (effect_type_char == EFFECT_PORTAL_CHAR) {
            effect_type = EFFECT_PORTAL;
        } else if (effect_type_char == EFFECT_ICE_CHAR) {
            effect_type = EFFECT_ICE;
        }

        if (effect_type == INVALID_INPUT) {
            printf("Invalid Effect Type!\n");
        } else {
            int matches = apply_effect(realm, search_term, effect_type);
            printf("%d tower(s) had their effect set!\n", matches);
        }
    } else {
        printf("Invalid command!\n");
    }

}

void do_new_enemy(Realm realm, char *command) {
    char ignored_char;
    char place[MAX_INVALID_NAME_ARRAY_SIZE] = "";
    char name[MAX_INVALID_NAME_ARRAY_SIZE] = "";
    int hp;

    int num_scanned = sscanf(
        command, "%c %s %s %d",
        &ignored_char, place, name,
        &hp
    ); 

    if (num_scanned == 4) {
        if (!valid_name(place)) {
            printf(
                "The place name you entered is too long.\n"
                "You can expect you will never get an input this long.\n"
            );
            return;
        }
        if (!valid_name(name)) {
            printf(
                "The enemy name you entered is too long.\n"
                "You can expect you will never get an input this long.\n"
            );
            return;
        }
        int result = new_enemy(realm, place, name, hp);
        if (result == ERROR_NO_LOCATION) {
            printf("Could not find tower %s!\n", place);
        } else if (result == ERROR_INVALID_STAT) {
            printf("The stats of this enemy are invalid!\n");

        }
    } else {
        printf("Invalid command!\n");
    }
}

void do_advance_enemies(Realm realm) {
    int castle_enemies = advance_enemies(realm);
    printf("The enemies advance! %d made it past the Castle!\n", castle_enemies);
}

void do_apply_damage(Realm realm) {
    int removed_enemies = apply_damage(realm);
    if (removed_enemies != 1) {
        printf(
            "The towers attack the enemies of the Realm... %d were hit!\n",
            removed_enemies
        );
    } else {
        printf(
            "The towers attack the enemies of the Realm... %d was hit!\n",
            removed_enemies
        );

    }
}

void do_new_tower(Realm realm, char *command) {
    char ignored_char;
    char below_name[MAX_INVALID_NAME_ARRAY_SIZE];
    char name[MAX_INVALID_NAME_ARRAY_SIZE];
    int power, uses;

    int num_scanned = sscanf(
        command, "%c %s %s %d %d",
        &ignored_char, below_name, name,
        &power, &uses
    );
    
    if (num_scanned == 5) {
        if (!valid_name(below_name)) {
            printf(
                "The previous tower name you entered is too long.\n"
                "You can expect you will never get an input this long.\n"
            );
            return;
        } else if (!valid_name(name)) {
            printf(
                "The new tower name you entered is too long.\n"
                "You can expect you will never get an input this long.\n"
            );
            return;
        }

        int result = new_tower(realm, below_name, name, power, uses);
        if (result == ERROR_NO_LOCATION) {
            printf("Could not find tower %s!\n", below_name);
        } else if (result == ERROR_INVALID_STAT) {
            printf("Could not create a tower with those stats.\n");
        }
    } else {
        printf("Invalid command!\n");
    }
}
