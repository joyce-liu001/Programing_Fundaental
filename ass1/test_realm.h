//
// DO NOT CHANGE THIS FILE
//
// You do not submit this file. This file is not marked.
// If you think you need to change this file you have
// misunderstood the assignment - ask in the course forum.
//
// Assignment 2 20T2 COMP1511: Castle Defense
// test_realm.h
//
// You must not change this file.
//
// Version 1.0.0: Release
// Version 1.1.0: Add test_apply_buff
// Version 1.1.1: Reword summaries for clarity.

#define FOLLOWS_SPEC "Follows Spec.\n"
#define DOES_NOT_FOLLOW_SPEC "Does Not Follow Spec.\n"

//////////////////////////////////////////////////////
// This is a helper function that lets you test if one
// string occurs in another string.
//
// For example:
// `string_contains("hello", "hi")` returns 0
// `string_contains("hello", "lo")` returns 1
int string_contains(char *haystack, char *needle);

///////////////////////////////////////////////////////////
// Test whether add_location does the right things.
//
// When calling this function, the add_location function may
// be broken. All other functions are implemented as normal.
// This function prints out a summary of what it's testing, and then
// should either print the `FOLLOWS_SPEC` #define, or the
// `DOES_NOT_FOLLOW_SPEC` #define, depending on whether the
// tested function behaves as it should, or does not do what the
// spec says it should.
//
// For full marks in this function, you should test at least
// two other ways the `add_location` function could fail.
// One test has already been provided to you, which you may
// keep or modify. You have also been given one specific
// property to test; and this property is checked by the
// autotests.
//
// You should only need if statements and the functions in
// `realm.h` to test it, though you may use any C language
// features you have learned. You do not need to free memory.
void test_add_location(void);


///////////////////////////////////////////////////////////
// Test whether print_realm does the right thing.
//
// When calling this function, the print_realm function may
// be broken. All other functions are implemented as normal.
// This function prints out a summary of what it's testing, and then
// should either print the `FOLLOWS_SPEC` #define, or the
// `DOES_NOT_FOLLOW_SPEC` #define, depending on whether the
// tested function behaves as it should, or does not do what the
// spec says it should.
//
// For full marks in this function, you should test at least
// two other ways the `add_location` function could fail.
// One test has already been provided to you, which you may
// keep or modify. You have also been given one specific
// property to test; and this property is checked by the
// autotests.
//
// You should only need if statements, the CAPTURE macro function,
// and the functions in `realm.h` to test it, though you may use
// any C language features you have learned. You do not need to free memory.
void test_print_realm(void);


///////////////////////////////////////////////////////////
// Test whether new_enemy does the right thing.
//
// When calling this function, the new_enemy function may
// be broken. All other functions are implemented as normal.
// This function prints out a summary of what it's testing, and then
// should either print the `FOLLOWS_SPEC` #define, or the
// `DOES_NOT_FOLLOW_SPEC` #define, depending on whether the
// tested function behaves as it should, or does not do what the
// spec says it should.
//
// For full marks in this function, you should test at least
// two ways the `new_enemy` function could fail. You have been
// given one specific property to test; and this property is
// checked by the autotests.
//
// You should only need if statements, the CAPTURE macro function,
// and the functions in `realm.h` to test it, though you may use
// any C language features you have learned. You do not need to free memory.
void test_new_enemy(void);


///////////////////////////////////////////////////////////
// Test whether new_tower does the right thing.
//
// When calling this function, the new_tower function may
// be broken. All other functions are implemented as normal.
// This function prints out a summary of what it's testing, and then
// should either print the `FOLLOWS_SPEC` #define, or the
// `DOES_NOT_FOLLOW_SPEC` #define, depending on whether the
// tested function behaves as it should, or does not do what the
// spec says it should.
//
// For full marks in this function, you should test at least
// two ways the `new_tower` function could fail. You have been
// given one specific property to test; and this property is
// checked by the autotests.
//
// You should only need if statements, the CAPTURE macro function,
// and the functions in `realm.h` to test it, though you may use
// any C language features you have learned. You do not need to free memory.
void test_new_tower(void);


///////////////////////////////////////////////////////////
// Test whether apply_damage does the right thing.
//
// When calling this function, the apply_damage function may
// be broken. All other functions are implemented as normal.
// This function prints out a summary of what it's testing, and then
// should either print the `FOLLOWS_SPEC` #define, or the
// `DOES_NOT_FOLLOW_SPEC` #define, depending on whether the
// tested function behaves as it should, or does not do what the
// spec says it should.
//
// For full marks in this function, you should test at least
// two ways the `apply_damage` function could fail. You have been
// given one specific property to test; and this property is
// checked by the autotests.
//
// You should only need if statements, the CAPTURE macro function,
// and the functions in `realm.h` to test it, though you may use
// any C language features you have learned. You do not need to free memory.
void test_apply_damage(void);


///////////////////////////////////////////////////////////
// Test whether apply_buff prints the right thing.
//
// When calling this function, the apply_buff function may
// be broken. All other functions are implemented as normal.
// This function prints out a summary of what it's testing, and then
// should either print the `FOLLOWS_SPEC` #define, or the
// `DOES_NOT_FOLLOW_SPEC` #define, depending on whether the
// tested function behaves as it should, or does not do what the
// spec says it should.
//
// For full marks in this function, you should test at least
// two ways the `apply_buff` function could fail.
//
// You should only need if statements, the CAPTURE macro function,
// and the functions in `realm.h` to test it, though you may use
// any C language features you have learned. You do not need to free memory.
void test_apply_buff(void);


///////////////////////////////////////////////////////////
// Add any extra tests you'd like to write here!
void extra_tests(void);
