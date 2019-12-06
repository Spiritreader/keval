#ifndef KEVAL_H_INCLUDED
#define KEVAL_H_INCLUDED

#define NULL_ERR -5
#define OUT_OF_BOUNDS_ERR -6
#define FINE 0
#define ALLOC_ERR -8
#define NO_INIT -9
#define ALREADY_INITIALIZED -10
#define NO_RESIZE_NEEDED -11
#define NOT_FOUND -12
#define DUPLICATE_DETECTED -13

struct kv_data {
    char** keys;
    char** values;
    int size;
};

/**
 * Initializes a keval data structure instance
 * @returns: Pointer to the initialized struct
 *
**/
struct kv_data* kv_spawn(void);


/**
 * Returns a value for a key given as string
 * @returns char pointer containing the key's value string or
 *          NULL if the key wasn't found in the structure
 * @error NULL if keval wasn't intialized
**/
char* kv_get_val_s(char* key, struct kv_data* data);

/**
 * Returns a value for a key given as integer
 * @returns char pointer containing the key's value string or
 *          NULL if a wrong index was entered
 * @error NULL if keval wasn't initialized
**/
char* kv_get_val_i(int val_index, struct kv_data* data);


/**
 * Returns a key string for a given index
 * @returns char pointer containing the key string or
 *          NULL if a wrong index was entered
 * @error NULL if keval wasn't initialized
**/
char* kv_get_key(int index, struct kv_data* data);

/**
 * Prints a key value pair string and writes it to out.
 * @returns FINE if successful.
 * @error NULL if keval wasn't initialized, OUT_OF_BOUNDS_ERR if index is out of range
 *
**/
int kv_print_pair(int index, struct kv_data* data);

/**
 * Adds a key to the array
 * @returns FINE if successful
 * @error ALLOC_ERR or OUT_OF_BOUNDS_ERR
**/
int kv_add_key(char* key, struct kv_data* data);

/**
 * Sets the value of a key to a char
 * @returns FINE if successful
 * @error NO_INIT if keval wasn't initialized, OUT_OF_BOUNDS and NULL_ERR if val is NULL
**/
int kv_set_val_i(int key_index, char* val, struct kv_data* data);

/**
 * Sets the value of a key to a char
 * @returns FINE if successful
 * @error NO_INIT if keval wasn't initialized,
            NOT_FOUND if key is not in struct
            and NULL_ERR if val is NULL
**/
int kv_set_val_s(char* key, char* val, struct kv_data* data);

/**
 * Removes a key from the struct given its key string
 * @returns FINE if successful
 * @error NOT_FOUND if key string isn't present
**/
int kv_remove_key_s(char* key, struct kv_data* data);

/**
 * Removes a key from the struct given its index
 * @returns FINE if successful
 * @error NO_INIT if keval wasn't initialized,
            NOT_FOUND if key is not in struct
**/
int kv_remove_key_i(int index, struct kv_data* data);

/**
 * Destroys the keval instance and frees all memory
 * @returns FINE if sucessful, NO_INIT if called without initing first.
**/
struct kv_data* kv_destroy(struct kv_data* instance);

/**
 * Gets an index value for a key string
 * @returns the index of the key string, DUPLICATE_DETECTED if duplicate
**/
int kv_key_search(char *key, struct kv_data* data);

/**
 * Retrieves the total amount of keys present in the data structure
 * @returns an integer containing the amount of keys in the struct
 **/
int kv_get_size(struct kv_data* data);


#endif // KEVAL_H_INCLUDED
