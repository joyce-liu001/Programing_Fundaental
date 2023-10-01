//
// DO NOT CHANGE THIS FILE
//
// You do not submit this file. This file is not marked.
// If you think you need to change this file you have
// misunderstood the assignment - ask in the course forum.
//
// Assignment 2 20T2 COMP1511: Castle Defense
// realm.h
//
// You must not change this file.
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Remove an extraneous todo comment from development.
// Version 1.1.0: Fix incorrect element of specification in apply_damage.
// Version 1.2.0: Some implementations may not need to free names.
// Version 1.3.0: Rename 'name_above' to 'prev_name' to match realm.c
// Version 1.4.0: Reword the advance_enemies and new_tower function to clarify.

// Constants

#define MAX_NAME_LENGTH 64
#define STARTING_CASTLE_HP 100
#define INVALID_INPUT (-1)

#define TRUE (1 == 1)
#define FALSE (!TRUE)

// Types

typedef struct realm *Realm;
typedef struct location *Location;
typedef struct enemy *Enemy;

#define TYPE_LAND 0
#define TYPE_TOWER 1
#define TYPE_CASTLE 2

typedef int Buff;

#define BUFF_ENEMY_HP 0
#define BUFF_TOWER_POWER 1
#define BUFF_TOWER_USES 2

#define BUFF_ENEMY_HP_CHAR 'h'
#define BUFF_TOWER_POWER_CHAR 'p'
#define BUFF_TOWER_USES_CHAR 'u'

typedef int Effect;

#define EFFECT_NONE 0
#define EFFECT_PORTAL 1
#define EFFECT_ICE 2

#define EFFECT_NONE_CHAR 'n'
#define EFFECT_PORTAL_CHAR 'p'
#define EFFECT_ICE_CHAR 'i'

#define ERROR_NOT_IMPLEMENTED -127
#define ERROR_NO_LOCATION -1
#define ERROR_INVALID_STAT -2
#define SUCCESS 0

// Create a new Realm and return a pointer to it.
// The pointer is to a malloced piece of memory, and it is the caller's
// responsibility to call 'free_realm' to free that memory.
Realm new_realm(void);

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add a new location to the realm.
// Given the name of a new location, and a realm to insert it into,
// insert a new location node just above the Lair.
// Return the number of locations in total.
int add_location(Realm realm, char *name);

// Print out the realm.
//
// print_realm will be given a realm, and will print out that realm.
// You should use the functions given in the starter code to print it
// out, instead of calling printf yourself.
//
// Command: p
void print_realm(Realm realm);

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add a new tower to the realm.
//
// You should:
//  - Find the Location called prev_name.
//  - If one does not exist, return ERROR_NO_LOCATION
//  - Ensure that the stats you have been given for Power and Uses are not below 1.
//    If they are, return ERROR_INVALID_STAT.
//  - Place a new tower, with the given stats, directly below the tower 'prev_name'.
//  - Return SUCCESS to indicate success.
//
// Command: t <prev_name> <name> <power> <uses>
int new_tower(Realm realm, char *prev_name, char *name, int power, int uses);

// Add an enemy to the realm.
//
// Given a realm, the name of a Location, and stats about a new enemy,
// you should add an enemy with those stats to the Location.
//
// If that Location does not exist, you should return ERROR_NO_LOCATION.
//
// You may assume that the enemy being added will preserve the alphabetical order
// of the list of Enemies at that Location. This means that if you have
// an enemy named "Bill", you could add an enemy named "Bob" or "Zargox_The_Destroyer",
// but not named "Alice".
//
// Command: e <location_name> <name> <hp>
int new_enemy(Realm realm, char *location_name, char *name, int hp);

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////


// Destroy the realm, and free any associated memory.
//
// This function should free:
// - Each Enemy, and its name (if necessary)
// - Each Location, and its name (if necessary)
// - The Realm struct.
// - Any other memory you have malloced in the Realm.
//
// Note that you may not need to free the name of the Enemy or Location,
// depending on your implementation
void destroy_realm(Realm realm);

// Advance enemies towards the castle.
//
// advance_enemies will go through the realm, moving each enemy to the
// Location in front.
//
// Should any enemies go beyond the castle, they should be removed from
// the realm, and destroyed.
//
// At the end of this function, the Lair should have no enemies (i.e.
// the Lair's `enemies` pointer should be NULL).
//
// If you are completing Stage 5, effects may change the way this function works.
// They may cause the enemies pointer at the Lair to be non-NULL, or could change
// how enemies move.
// This function should return the number of enemies that moved beyond the
// castle.
//
// Command: n
int advance_enemies(Realm realm);

// Apply damage to the enemies at each tower from that tower.
//
// Go through each Location in the realm, and if the Location is a Tower:
// - Go through each Enemy at that Tower, and reduce it's HP by the
//    Tower's power.  If an enemy's HP is below zero, remove it from the
//    list of Enemies at that Location.
// - Reduce that Tower's number of uses left by 1.
// - If that Tower now has no uses, convert it into a Land.
//    It should no longer have any effect on passing enemies.
//
// The Castle should also lose defense equal to the combined health of
// the enemies there. Note that the Castle's defense going below 0 should
// not cause any special behaviour -- the Castle can have negative defense.
//
// This function should return the number of enemies damaged this way.
//
// This .h file previously, incorrectly said you should return the damage
// level of the castle; this has now been fixed.
//
// Command: d
int apply_damage(Realm realm);

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

// Stage 4 and 5 Functions use "search terms", which are described
// in detail in the assignment specification webpage.

// Apply the specified buff to the relevant towers or enemies.
//
// This function has three behaviours depending on the argument `buff`:
// If buff == BUFF_TOWER_USES or buff == BUFF_TOWER_POWER, then:
//  - Find all the towers in the Realm with a name that matches the search
//    described by search_name. You should then increase either the number
//    of uses remaining or the power of each of those towers by the
//    specified amount.
//  - This amount may be negative. If a tower would drop below 0 uses or
//    0 power because of this, you should convert it to a land (as if
//    it had run out of uses after the apply_damage function).
// If buff == BUFF_ENEMY_HP, then:
//  - Find all enemies in the Realm with a name that matches the search
//    described by search_name. You should then increase each of their
//    HP by the specified amount.
//  - This amount can be negative. If a negative amount would cause an
//    enemy to drop below zero HP, it dies (as if had been killed after
//    the apply_damage function).
//
// This function should return the number of relevant towers or enemies
// that match the search_term.
//
// Command: b <search_term> <buff_type> <amount>
int apply_buff(Realm realm, char *search_term, Buff buff, int amount);

////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

// Apply the specified effect to each tower whose name matches the
// specified search term.
//
// Given a realm, and a search term, find each Tower in the realm with
// a name matching that search term. Each Tower matching the term gets
// the special effect described by `effect` (losing any other effects
// it had).
//
// if effect == EFFECT_NONE: the tower has no effects.
//    All towers start in this state.
//
// if effect == EFFECT_ICE: the tower is now an ice tower.
//    Only enemies with as much HP as the tower's power may
//    swim through this tower's ice. Because of that, enemies
//    with power less than the tower's HP cannot advance, and are
//    stuck at the location below.
//
// if effect == EFFECT_PORTAL: this tower is now a portal.
//   if, after moving all enemies, there are enemies at a portal
//   tower, all those enemies are moved back to the Lair. Those
//   towers then change to having no effect.
//
// This function should then return the number of towers that matched
// the search term.
//
// A reminder: enemies are always sorted by name order. You should
// ensure these effects preserve that order.
//
// Command: f <search_term> <effect_type>
int apply_effect(Realm realm, char *search_term, Effect effect);
