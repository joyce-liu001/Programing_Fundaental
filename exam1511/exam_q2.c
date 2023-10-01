// z5271698

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// Do not change these #defines, or your program will fail the autotests!
#define NOT_IN_LIST -42

struct node {
    struct node *next;
    int          data;
};

// first_match_position should return the location of the first
// occurence of 'search_for' in the linked list, or NOT_IN_LIST
// if the linked list does not contain 'search_for'.
int first_match_position(struct node *head, int search_for) {
    int position = 1;
    while (head != NULL) {
        if (head->data == search_for) {
            return position;
        }
        position++;
        head = head->next;
    }
    
    
    return NOT_IN_LIST;
}


////////////////////////////////////////////////////////////////////////
//               DO NOT CHANGE THE CODE BELOW                         //
////////////////////////////////////////////////////////////////////////

int first_match_position(struct node *head, int search_for);
struct node *strings_to_list(int len, char *strings[]);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(int argc, char *argv[]) {
    // create linked list from command line arguments
    int search_for = atoi(argv[1]);
    struct node *head = strings_to_list(argc - 2, &argv[2]);

    // If you're getting an error here,
    // you have returned an uninitialized value
    int location = first_match_position(head, search_for);
    if (location == NOT_IN_LIST) {
        printf("Did not find %d in the list!\n", search_for);
    } else {
        printf("The location of %d in the list is: %d\n", search_for, location);
    }

    return 0;
}

// DO NOT CHANGE THIS FUNCTION
// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    for (int i = len - 1; i >= 0; i = i - 1) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
    }
    return head;
}

