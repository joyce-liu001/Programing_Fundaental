#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node* createNode(int newData, struct node *newNext);

int main(void) {
    struct node *firstnode = createNode(1, NULL);
    struct node *head = firstnode;
    struct node othernode;
    othernode.data = 2;
    othernode.next = head;
    head = &othernode;
}

struct node *createNode(int newData, struct node *newNext) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = newData;
    newNode->next = newNext;
    return newNode;
}
