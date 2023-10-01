// z5271698

#include <stdio.h>
#include <stdlib.h>

#define MAX_CHA 100
#define NO_RESULT 233
#define SUCCESS 12

struct station {
    struct station *next;
    int station_name;
    struct bus *buses;
};

struct bus { 
    int bus_name;
    struct bus *next;
};


int new_bus(struct station *head, int st, int bus);
int order (struct station *head);
void destroy(struct station *head);


int main(void) {
    // create station 1 2 3
    struct station *station1 =malloc(sizeof(struct station));
    struct station *station2 =malloc(sizeof(struct station));
    struct station *station3 =malloc(sizeof(struct station));
    
    station1->station_name = 1;
    station1->next = station2;
    station1->buses = NULL;
    station2->station_name = 2;
    station2->buses = NULL;
    station2->next = station3;
    station3->buses = NULL;
    station3->station_name = 3;
    station3->next = NULL;
    
    // add bus into list
    int bus;
    int st;
    while (scanf("%d %d", &st, &bus) != EOF) {    
        // find station
        new_bus(station1, st, bus);
    }
    
    // check whether bus arrive in ordered or not
    if (order(station1) == NO_RESULT) {
        printf("ERROR\n");
    }
    
    // free all
    destroy(station1);
}

void destroy(struct station *head) {  
    struct station *position = head;
    while (position != NULL) {        
        struct bus *bus = position->buses;   
        
        // Free buses at head.
        while (bus != NULL) {          
            position->buses = bus->next;
            free (bus);
            bus = position->buses;
        } 
        
        // Free stations.      
        head = position->next;
        free(position);
        position = head;
    }
    
}



int order (struct station *head) { 
    
    int size = 0;   
    struct station *position = head;
    struct bus *bp = position->buses;
    while (bp != NULL) {
        size++;
        bp = bp->next;
    }

    

    // station2
    struct bus *st1Bus = head->buses;
    position = position->next;
    bp = position->buses;
    int error = 0;
    while (bp != NULL && st1Bus != NULL) {
        if (st1Bus->bus_name != bp->bus_name) {
            error = bp->bus_name;
        }   
        st1Bus = st1Bus->next;                     
        bp = bp->next;
    }  
    if (st1Bus != NULL) {
        error = st1Bus->bus_name;
    } 
    
    
    // print bus in station3
    st1Bus = head->buses; // station1 buses
    position = position->next;
    bp = position->buses; 
    int busOder = 0;   
    while (bp != NULL && st1Bus != NULL) {
        if (st1Bus->bus_name != bp->bus_name || bp->bus_name == error) {
            return NO_RESULT;
        } else {
            printf("%d\n", bp->bus_name);
        } 
        busOder++;                      
        st1Bus = st1Bus->next;
        bp = bp->next;      
    }
    
    if (busOder != size || bp != NULL) {
        return NO_RESULT;
    }
    
    return SUCCESS;
}



int new_bus(struct station *head, int st, int busNum) {

    // Find station called station_name.
    struct station *position = head;   
    
    while (position != NULL && position->station_name != st) {
        position = position->next;   
    }
        
    if (position == NULL) {
        // When the location called location_name does not exist.
        return NO_RESULT;
    }
    
    
    
    // will never receive the same bus name twice.
    struct bus *bp = position->buses;   
    while (bp != NULL && bp->bus_name != busNum) {               
        bp = bp->next;        
    }
    
    if (bp != NULL) {
        return NO_RESULT;
    }
    
   
    // Create a newBus with malloc.
    struct bus *newBus = malloc(sizeof(struct bus));
    newBus->bus_name = busNum;
    newBus->next = NULL;    
    
    if (position->buses == NULL) {
        // There is no bus on the position, 
        // insert newBus in to position->buses.
        position->buses = newBus;      
    
    } else {
        struct bus *lastBus = position->buses;
                
        while (lastBus->next != NULL) {
            // Find the last bus in the position.
            lastBus = lastBus->next;
        }
        
        // Insert bus after the last bus at this position.     
        lastBus->next = newBus;            
    } 
            
    return SUCCESS;   
}



