#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// Helper functions just used by this C file to clean up our code
// Using static means they can't get linked into other files

static int system_convert(System *);
static void system_simulate_process_time(System *);
static int system_store_resources(System *);

/**
 * Creates a new `System` object.
 *
 * Allocates memory for a new `System` and initializes its fields.
 * The `name` is dynamically allocated.
 *
 * @param[out] system          Pointer to the `System*` to be allocated and initialized.
 * @param[in]  name            Name of the system (the string is copied).
 * @param[in]  consumed        `ResourceAmount` representing the resource consumed.
 * @param[in]  produced        `ResourceAmount` representing the resource produced.
 * @param[in]  processing_time Processing time in milliseconds.
 * @param[in]  event_queue     Pointer to the `EventQueue` for event handling.
 */
void system_create(System **system, const char *name, ResourceAmount consumed, ResourceAmount produced, int processing_time, EventQueue *event_queue) {
    //checking if system and name are null pointers
    if (system == NULL || name == NULL) {
        fprintf(stderr, "Error system and name are null pointers in system_create\n");
        return;
    }

    // Allocate memory for a new System
    *system = (System *)malloc(sizeof(System));
    //checking if this system pointer is null
    if (*system == NULL) {
        fprintf(stderr, "Allocation for System failed\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the systems name field 
    (*system)->name = malloc(strlen(name) + 1);
    if ((*system)->name == NULL) {
        fprintf(stderr, "Error: Memory allocation for System name failed\n");
        free(*system);
        exit(EXIT_FAILURE);
    }
    //Copy the name argument into memory
    strcpy((*system)->name, name);

    //Initialize the data wihting the System struct
    (*system)->consumed = consumed;
    (*system)->produced = produced;
    (*system)->processing_time = processing_time;
    (*system)->status = STANDARD;
    (*system)->event_queue = event_queue;

    //set initial amount_store to zero
    (*system)->amount_stored = 0;

}

/**
 * Destroys a `System` object.
 *
 * Frees all memory associated with the `System`.
 *
 * @param[in,out] system  Pointer to the `System` to be destroyed.
 */
void system_destroy(System *system) {
    //check if system pointer is a null pointer
    if (system == NULL) {
        fprintf(stderr, "Error syetem is a null pointer in system_destroy\n");
        return;
    } 
    // Free names memory
    if (system->name != NULL) {
        free(system->name);
    }
    // Free the systems memory
    free(system); 
}


/**
 * Runs the main loop for a `System`.
 *
 * This function manages the lifecycle of a system, including resource conversion,
 * processing time simulation, and resource storage. It generates events based on
 * the success or failure of these operations.
 *
 * @param[in,out] system  Pointer to the `System` to run.
 */
void system_run(System *system) {
    Event event;
    int result_status;
    
    if (system->amount_stored == 0) {
        // Need to convert resources (consume and process)
        result_status = system_convert(system);

        if (result_status != STATUS_OK) {
            // Report that resources were out / insufficient
            event_init(&event, system, system->consumed.resource, result_status, PRIORITY_HIGH, system->consumed.resource->amount);
            event_queue_push(system->event_queue, &event);    
            // Sleep to prevent looping too frequently and spamming with events
            usleep(SYSTEM_WAIT_TIME * 1000);          
        }
    }

    if (system->amount_stored  > 0) {
        // Attempt to store the produced resources
        result_status = system_store_resources(system);

        if (result_status != STATUS_OK) {
            event_init(&event, system, system->produced.resource, result_status, PRIORITY_LOW, system->produced.resource->amount);
            event_queue_push(system->event_queue, &event);
            // Sleep to prevent looping too frequently and spamming with events
            usleep(SYSTEM_WAIT_TIME * 1000);
        }
    }
}

/**
 * Converts resources in a `System`.
 *
 * Handles the consumption of required resources and simulates processing time.
 * Updates the amount of produced resources based on the system's configuration.
 *
 * @param[in,out] system           Pointer to the `System` performing the conversion.
 * @param[out]    amount_produced  Pointer to the integer tracking the amount of produced resources.
 * @return                         `STATUS_OK` if successful, or an error status code.
 */
static int system_convert(System *system) {
    int status;
    Resource *consumed_resource = system->consumed.resource;
    int amount_consumed = system->consumed.amount;

    // We can always convert without consuming anything
    if (consumed_resource == NULL) {
        status = STATUS_OK;
    } else {
        //lock
        sem_wait(&system->consumed.resource->mutex);

        // Attempt to consume the required resources
        if (consumed_resource->amount >= amount_consumed) {
            consumed_resource->amount -= amount_consumed;
            status = STATUS_OK;
        } else {
            status = (consumed_resource->amount == 0) ? STATUS_EMPTY : STATUS_INSUFFICIENT;
        }
        //unlocking
        sem_post(&system->consumed.resource->mutex);
    }

    if (status == STATUS_OK) {
        system_simulate_process_time(system);

        if (system->produced.resource != NULL) {
            system->amount_stored += system->produced.amount;
        }
        else {
            system->amount_stored = 0;
        }
    }
    return status;
}

/**
 * Simulates the processing time for a `System`.
 *
 * Adjusts the processing time based on the system's current status (e.g., SLOW, FAST)
 * and sleeps for the adjusted time to simulate processing.
 *
 * @param[in] system  Pointer to the `System` whose processing time is being simulated.
 */
static void system_simulate_process_time(System *system) {
    int adjusted_processing_time;

    // Adjust based on the current system status modifier
    switch (system->status) {
        case SLOW:
            adjusted_processing_time = system->processing_time * 2;
            break;
        case FAST:
            adjusted_processing_time = system->processing_time / 2;
            break;
        default:
            adjusted_processing_time = system->processing_time;
    }

    // Sleep for the required time
    usleep(adjusted_processing_time * 1000);
}

/**
 * Stores produced resources in a `System`.
 *
 * Attempts to add the produced resources to the corresponding resource's amount,
 * considering the maximum capacity. Updates the `produced_resource_count` to reflect
 * any leftover resources that couldn't be stored.
 *
 * @param[in,out] system                   Pointer to the `System` storing resources.
 * @param[in,out] produced_resource_count  Pointer to the integer value of how many resources need to be stored, updated with the amount that could not be stored.
 * @return                                 `STATUS_OK` if all resources were stored, or `STATUS_CAPACITY` if not all could be stored.
 */
static int system_store_resources(System *system) {
    Resource *produced_resource = system->produced.resource;
    int available_space, amount_to_store;

    // We can always proceed if there's nothing to store
    if (produced_resource == NULL || system->amount_stored == 0) {
        system->amount_stored = 0;
        return STATUS_OK;
    }
    //locking 
   sem_wait(&system->produced.resource->mutex);

    amount_to_store = system->amount_stored;
    // Calculate available space
    available_space = produced_resource->max_capacity - produced_resource->amount;

    if (available_space >= amount_to_store) {
        // Store all produced resources
        produced_resource->amount += amount_to_store;
        system->amount_stored = 0;
    } else if (available_space > 0) {
        // Store as much as possible
        produced_resource->amount += available_space;
        system->amount_stored = amount_to_store - available_space;
    }

    //unlocking
    sem_post(&system->produced.resource->mutex);

    if (system->amount_stored != 0) {
        return STATUS_CAPACITY;
    }


    return STATUS_OK;
}
/**
 * Initializes the `SystemArray`.
 *
 * Allocates memory for the array of `System*` pointers of capacity 1 and sets up initial values.
 *
 * @param[out] array  Pointer to the `SystemArray` to initialize.
 */
void system_array_init(SystemArray *array) {
        //checking if array ius a null pointer if so return
        if (array == NULL) {
        fprintf(stderr, "Error, array is a null pointer in system_array_init\n");
        return;
    }

    // Allocate memory for the array of System*
    array->systems = (System **)malloc(sizeof(System *) * 1);
    if (array->systems == NULL) {
        fprintf(stderr, "Allocatiing memoery for the arrays systems failed\n");
        exit(EXIT_FAILURE);
    }

    // Setting capacitiy of array to 1 
    array->capacity = 1;
    // initializing size of array since it is in the SystemArray struct
    array->size = 0;
}

/**
 * Cleans up the `SystemArray` by destroying all systems and freeing memory.
 *
 * Iterates through the array, cleaning any memory for each System pointed to by the array.
 *
 * @param[in,out] array  Pointer to the `SystemArray` to clean.
 */
void system_array_clean(SystemArray *array) {
    //checking if array is null in system_array_clean
    if (array == NULL) {
        fprintf(stderr, "Error array is a null pointer in system_array_clean\n");
        return;
    }

    // Go through the array and destroy each System
    for (int i = 0; i < array->size; i++) {
        //if a system object pointed to by the array isnt null destroy it
        if (array->systems[i] != NULL) {
            system_destroy(array->systems[i]);
        }
    }

    // Free the memoery associated with the array of System pointers
    free(array->systems);
    // initializing capacity and size of array since it is in the SystemArray struct
    array->capacity = 0;
    array->size = 0;
}

/**
 * Adds a `System` to the `SystemArray`, resizing if necessary (doubling the size).
 *
 * Resizes the array when the capacity is reached and adds the new `System`.
 * Use of realloc is NOT permitted.
 *
 * @param[in,out] array   Pointer to the `SystemArray`.
 * @param[in]     system  Pointer to the `System` to add.
 */
void system_array_add(SystemArray *array, System *system) {
    //checking if array and system pointers are null in system_array_add
    if (array == NULL || system == NULL) {
        fprintf(stderr, "Error array and system are null pointers in system_array_add\n");
        return;
    }

    // Check if the capacity is insuffecient 
    if (array->size >= array->capacity) {
        int new_capacity = array->capacity * 2; 
        //checking if capacity if 0
        if (new_capacity == 0) {
            new_capacity = 1; 
        }
        
        System **new_systems = (System **)malloc(sizeof(System *) * new_capacity);
        //check if it is a null pointers
        if (new_systems == NULL) {
            fprintf(stderr, "Allocation failed while resizing SystemArray\n");
            exit(EXIT_FAILURE); 
        }

        //Existing elements are copied to the new array
        for (int i = 0; i < array->size; i++) {
            new_systems[i] = array->systems[i];
        }

        // Free the old array
        free(array->systems);

        // Update the array to use the new systems and capacity
        array->systems = new_systems;
        array->capacity = new_capacity;
    }
    // Adding Systems to the end of the array and increasing the size of the array
    array->systems[array->size] = system;
    array->size++; 

}

void *system_thread(void *arg){
    //Makes System acccessible to thread function
    System *system = (System *)arg;
        //checking if system is null
        if (system == NULL) {
            fprintf(stderr, "Error system is a null pointer in system_thread\n");
            return NULL;
        }
        //passing and calling system_run() in a loop
        while (system->status != TERMINATE) {
            system_run(system);
        }
    pthread_exit(NULL);
}