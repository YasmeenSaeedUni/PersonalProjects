#include "defs.h"
#include <stdlib.h>
#include <stdio.h>

/* Event functions */

/**
 * Initializes an `Event` structure.
 *
 * Sets up an `Event` with the provided system, resource, status, priority, and amount.
 *
 * @param[out] event     Pointer to the `Event` to initialize.
 * @param[in]  system    Pointer to the `System` that generated the event.
 * @param[in]  resource  Pointer to the `Resource` associated with the event.
 * @param[in]  status    Status code representing the event type.
 * @param[in]  priority  Priority level of the event.
 * @param[in]  amount    Amount related to the event (e.g., resource amount).
 */
void event_init(Event *event, System *system, Resource *resource, int status, int priority, int amount) {
    event->system = system;
    event->resource = resource;
    event->status = status;
    event->priority = priority;
    event->amount = amount;
}

/* EventQueue functions */

/**
 * Initializes the `EventQueue`.
 *
 * Sets up the queue for use, initializing any necessary data (e.g., semaphores when threading).
 *
 * @param[out] queue  Pointer to the `EventQueue` to initialize.
 */
void event_queue_init(EventQueue *queue) {
    //checking if queue is a null pointer
    if (queue == NULL) {
        fprintf(stderr, "Error queue is a null pointer in event_queue_init\n");
        return;
    }
    //Initializing the head of Eventqueue to NULL
    queue->head = NULL; 
    //Initialize the size to 0 because size is also in the Eventqueue Struct
    queue->size = 0;    

    //Initialize semaphore
    sem_init(&queue->mutex, 0, 1);
}

/**
 * Cleans up the `EventQueue`.
 *
 * Frees any memory and resources associated with the `EventQueue`.
 * 
 * @param[in,out] queue  Pointer to the `EventQueue` to clean.
 */
void event_queue_clean(EventQueue *queue) {
    //checking if queue is a null pointer
    if (queue == NULL) {
        fprintf(stderr, "Error queue is a null pointer in event_queue_init\n");
        return;
    }
    //set the head of the queue to current node
    EventNode *current = queue->head;
    //if the currect node isnt null set 
    while (current != NULL) {
        //setting current node to temporary node
        EventNode *temp = current; 
        //move to next node and set that to new current
        current = current->next; 
        //free temporary node  
        free(temp);              
    }

    //Initializing the head of Eventqueue to NULL
    queue->head = NULL; 
    //Initialize the size to 0 because size is also in the Eventqueue Struct
    queue->size = 0; 
    //destroy
    sem_destroy(&queue->mutex); 
}

/**
 * Pushes an `Event` onto the `EventQueue`.
 *
 * Adds the event to the queue in a thread-safe manner, maintaining priority order (highest first).
 *
 * @param[in,out] queue  Pointer to the `EventQueue`.
 * @param[in]     event  Pointer to the `Event` to push onto the queue.
 */
void event_queue_push(EventQueue *queue, const Event *event) {
    //checking if queue and event are null pointers
    if (queue == NULL || event == NULL) {
        fprintf(stderr, "Error queue and event are null pointers in event_queue_push\n");
        return;
    }

    //lock
    sem_wait(&queue->mutex);

    // Dynamically allocating a new Event Node
    EventNode *new_node = (EventNode *)malloc(sizeof(EventNode));
    //check if the new node is null
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed for EventNode\n");
        exit(EXIT_FAILURE);
    }
    //initialize the new node
    new_node->event = *event; 
    new_node->next = NULL;

    // Check if the new node should be inserted at the front of the queue
    if (queue->head == NULL || queue->head->event.priority < event->priority) {
        //If the queue is empty or the new event has higher priority set it as the head of the queue
        new_node->next = queue->head;
        queue->head = new_node;
    } else {
        // Go through the queue to find the right position
        EventNode *current = queue->head;
        while (current->next != NULL && current->next->event.priority >= event->priority) {
            current = current->next;
        }
        // Insert the new node at right position
        new_node->next = current->next;
        current->next = new_node;
    }
    //increase the size of the queue since a new node was added
    queue->size++;  

    //unlocking
    sem_post(&queue->mutex);
}

/**
 * Pops an `Event` from the `EventQueue`.
 *
 * Removes the highest priority event from the queue in a thread-safe manner.
 *
 * @param[in,out] queue  Pointer to the `EventQueue`.
 * @param[out]    event  Pointer to the `Event` structure to store the popped event.
 * @return               Non-zero if an event was successfully popped; zero otherwise.
 */
int event_queue_pop(EventQueue *queue, Event *event) {
// Check if the queue or event pointer is a null pointer
    if (queue == NULL || event == NULL) {
        fprintf(stderr, "Error queue and event are null pointers in event_queue_pop\n");
        return 0;
    }
    //locking
    sem_wait(&queue->mutex);
    
    //checking if there are any events in queue
    if (queue->head == NULL) { 
        //unlocking    
        sem_post(&queue->mutex);
    return 0; 
    }
    
    // Remove the event at the head of  queue
    EventNode *temp = queue->head;      
    *event = temp->event;               
    queue->head = temp->next;           
    free(temp);                         
    // Since the event at head was removed decrease the size of the queue
    queue->size--; 
    //unlocking
    sem_post(&queue->mutex);
    return 1;
}