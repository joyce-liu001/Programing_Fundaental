// z5271698

#include <stdio.h>
#include <stdlib.h>

#define MAX 2100

struct node {
    struct node *next;
    int color;
    int number;
};

void paint(struct node *head, int index, int pixels, int colr);
void newPro(struct node *head);
static struct node *new_Node(int n);
void add_node(struct node *head, int n);


int main(void) {
    // create a list   
    struct node *head = malloc(sizeof(struct node));
    head->next = NULL;
    head->color = 0;
    head->number = 0;
    
    int n = 1;
    while (n < MAX) {
        add_node(head, n);
        n++;
    }
    
   
    
    // paint color     
    int index;
    int pixels;
    int colr;
    while (scanf("%d %d %d", &index, &pixels, &colr) != EOF) {           
        paint(head,index, pixels, colr);
    } 
    
    
    // new program
    printf("-\n");
    newPro(head);
    
    // free all nodes
    struct node *pre = head;
    while (pre != NULL) {
        head = pre->next;
        free(pre);
        pre = head;
    }
    
}

static struct node *new_Node(int n) {
        
    // Create a node
    struct node *newNode = malloc(sizeof(struct node));    
    newNode->next = NULL; 
    newNode->number = n;
    newNode->color = 0;
    return newNode;
}



void add_node(struct node *head, int n) {
     
    struct node *position = head;    
    while (position->next != NULL) {
        // Find position.          
        position = position->next;
    } 
    
    // Insert a new node in the position.
    struct node *insertNode = new_Node(n);
    position->next = insertNode;
}


void newPro(struct node *head) {
    struct node *position = head;
    while (position != NULL) {
        
        if (position->color != 0) {
            int p = position->number; 
            int pixels = 0;
            int colr = position->color;
            while (position->color == colr && position != NULL) {
                pixels++;
                position = position->next;
            }                   
            printf("%d %d %d\n", p, pixels, colr);
            
        } else {
            position = position->next;
        }
    }
        
}

void paint(struct node *head, int index, int pixels, int colr) {
    struct node *find = head;    
    
    while (find->number != index && find != NULL) {
        find = find->next;       
    } 
    
    int counter = 1;
    while (counter <= pixels && find != NULL) {
        find->color = colr;
        find = find->next;
        counter++;
    }
}
