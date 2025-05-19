#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Resource functions */

/**
 * Creates a new `Resource` object.
 *
 * Allocates memory for a new `Resource` and initializes its fields.
 * The `name` is dynamically allocated.
 *
 * @param[out] resource      Pointer to the `Resource*` to be allocated and initialized.
 * @param[in]  name          Name of the resource (the string is copied).
 * @param[in]  amount        Initial amount of the resource.
 * @param[in]  max_capacity  Maximum capacity of the resource.
 */
void resource_create(Resource **resource, const char *name, int amount, int max_capacity) {
    //error check for any null pointers and use fprint since it prints our errors if so return
    if (resource == NULL || name == NULL) {
        fprintf(stderr, "Error, Nresource or name is a null pointers in resource_create.\n");
        return;
    }
    // Allocate memory for the Resource
    *resource = (Resource *)malloc(sizeof(Resource));

    //error checking for null pointers(error)
    if (*resource == NULL) {
        fprintf(stderr, "Allocating memory for the Resource struct failed.\n");
        exit(EXIT_FAILURE);
    }

    // Allocating memory for the name field 
    (*resource)->name = malloc(strlen(name) + 1);
    //error checking for new value
    if ((*resource)->name == NULL) {
        fprintf(stderr, "Allocating memory for Resource name failed.\n");
        free(*resource);
        exit(EXIT_FAILURE);
    }
    //Copy the name argument into memory
    strcpy((*resource)->name, name);

    // Initialize other fields
    (*resource)->amount = amount;
    (*resource)->max_capacity = max_capacity;

    // Initialize the semaphore
    sem_init(&(*resource)->mutex, 0, 1);
}
/**
 * Destroys a `Resource` object.
 *
 * Frees all memory associated with the `Resource`.
 *
 * @param[in,out] resource  Pointer to the `Resource` to be destroyed.
 */
void resource_destroy(Resource *resource) {
    //check if pointer is null if so return
     if (resource == NULL) {
        fprintf(stderr, "Error, resource is a null pointer in resource_destroy.\n");
        return;
    }
    //detsroying semaphore
    sem_destroy(&resource->mutex);
    
    // Free names memory since dynamically allocated mmemory for name in create
    free(resource->name);
    // Free the resource itself
    free(resource);
}
//2.3 possibly add something

/* ResourceAmount functions */

/**
 * Initializes a `ResourceAmount` structure.
 *
 * Associates a `Resource` with a specific `amount`.
 *
 * @param[out] resource_amount  Pointer to the `ResourceAmount` to initialize.
 * @param[in]  resource         Pointer to the `Resource`.
 * @param[in]  amount           The amount associated with the `Resource`.
 */
void resource_amount_init(ResourceAmount *resource_amount, Resource *resource, int amount) {
    resource_amount->resource = resource;
    resource_amount->amount = amount;
}

/**
 * Initializes the `ResourceArray`.
 *
 * Allocates memory for the array of `Resource*` pointers and sets initial values.
 *
 * @param[out] array  Pointer to the `ResourceArray` to initialize.
 */
void resource_array_init(ResourceArray *array) {
        //checking if null pointer if so return
        if (array == NULL) {
        fprintf(stderr, "Error, array is a null pointer in resource_array_init\n");
        return;
    }

    // Allocate memory for the array of Resource*
    array->resources = (Resource **)malloc(sizeof(Resource *) * 1);
    if (array->resources == NULL) {
        fprintf(stderr, "Allocatiing memoery for the arrays resources failed\n");
        exit(EXIT_FAILURE);
    }

    // Setting capacitiy of array to 1 
    array->capacity = 1;
    // initializing size of array since it is in the ResourceArray struct
    array->size = 0;
}

/**
 * Cleans up the `ResourceArray` by destroying all resources and freeing memory.
 *
 * Iterates through the array, calls `resource_destroy` on each `Resource`,
 * and frees the array memory.
 *
 * @param[in,out] array  Pointer to the `ResourceArray` to clean.
 */
void resource_array_clean(ResourceArray *array) {
    //checking if array is null in resource_array_clean
    if (array == NULL) {
        fprintf(stderr, "Error array is a null pointer in resource_array_clean\n");
        return;
    }

    // Go through the array and destroy each Resource
    for (int i = 0; i < array->size; i++) {
        sem_destroy(&array->resources[i]->mutex);
        free(array->resources[i]->name);
        free(array->resources[i]);
    }

    // Free the memoery associated with the array of Resource pointers
    free(array->resources);
    // initializing capacity and size of array since it is in the ResourceArray struct
    array->capacity = 0;
    array->size = 0;
}
/**
 * Adds a `Resource` to the `ResourceArray`, resizing if necessary (doubling the size).
 *
 * Resizes the array when the capacity is reached and adds the new `Resource`.
 * Use of realloc is NOT permitted.
 * 
 * @param[in,out] array     Pointer to the `ResourceArray`.
 * @param[in]     resource  Pointer to the `Resource` to add.
 */
void resource_array_add(ResourceArray *array, Resource *resource) {
    //checking if array and resource pointers are null in resource_array_add
    if (array == NULL || resource == NULL) {
        fprintf(stderr, "Error array and resoure are null pointers in resource_array_add\n");
        return;
    }

    // Check if the capacity is insuffecient 
    if (array->size >= array->capacity) {
        int new_capacity = array->capacity * 2; 
        //checking if capacity if 0
        if (new_capacity == 0) {
            new_capacity = 1; 
        }
        
        Resource **new_resources = (Resource **)malloc(sizeof(Resource *) * new_capacity);
        //check if it is a null pointers
        if (new_resources == NULL) {
            fprintf(stderr, "Allocation failed while resizing ResourceArray\n");
            exit(EXIT_FAILURE); 
        }

        //Existing elements are copied to the new array
        for (int i = 0; i < array->size; i++) {
            new_resources[i] = array->resources[i];
        }

        // Free the old array
        free(array->resources);

        // Update the array to use the new resources and capacity
        array->resources = new_resources;
        array->capacity = new_capacity;
    }
    // Adding Resource to the end of the array and increasing the size of the array
    array->resources[array->size] = resource;
    array->size++; 
}