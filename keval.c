#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "keval.h"

int init = 0;
struct kv_data *data;

int resize_struct_arrays(int amount) {
    int new_size = data->size + amount;

    if (new_size < 0) {
        return OUT_OF_BOUNDS_ERR;
    }

    //Release all memory from previous key and value array instances if size goes to zero.
    if (new_size == 0) {
        free(data->keys);
        free(data->values);
        data->keys = NULL;
        data->values = NULL;
        data->size = new_size;
        return new_size;
    }

    char** extended_keys = realloc(data->keys, ((long unsigned int)new_size)*sizeof(char*));
    char** extended_values = realloc(data->values, ((long unsigned int)new_size)*sizeof(char*));

    if (extended_keys == NULL && extended_values != NULL) {
        free(extended_values);
    }

    if (extended_values == NULL && extended_keys != NULL) {
        free(extended_keys);
    }

    if (extended_keys == NULL || extended_values == NULL) {
        return ALLOC_ERR;
    }

    data->keys = extended_keys;
    data->values = extended_values;

    //Init to NULL if arrays are expanded so kv_set_val_i doesn't accidentally 
    //free them when it's first setting a key
    if (amount > 0) {
        data->keys[new_size - 1] = NULL;
        data->values[new_size - 1] = NULL;
    }

    data->size = new_size;
    return new_size;
}

int kv_key_search(char* key) {
    int index = NOT_FOUND;
    int found = 0;
    if (key == NULL) {
        return index;
    }
    for (int i = 0; i < data->size; i++) {
        if (strcmp(key, data->keys[i]) == 0) {
            index = i;
            found++;
        }
        if (found > 1) {
            return DUPLICATE_DETECTED;
        }
    }
    return index;
}

struct kv_data* kv_spawn() {
    struct kv_data* tmp = malloc(sizeof(struct kv_data));
    if (tmp == NULL) {
        return NULL;
    }
    tmp->size = 0;
    tmp->keys = NULL;
    tmp->values = NULL;
    return tmp;
}

int kv_set_instance(struct kv_data* instance) {
    if (instance == NULL) {
        return NO_INIT;
    }
    data = instance;
    return FINE;
}


struct kv_data* kv_destroy(struct kv_data *instance) {
    if (instance == NULL) {
        return NULL;
    }
    for (int i = 0; i < instance->size; i++) {
        free(instance->values[i]);
        free(instance->keys[i]);
    }
    free(instance->values);
    free(instance->keys);
    instance->values = NULL;
    instance->keys = NULL;
    instance->size = 0;
    free(instance);
    instance = NULL;

    return NULL;
}

char* kv_get_key(int index) {
    if (data == NULL) {
        return NULL;
    }

    if (index < 0 || index >= data->size) {
        return NULL;
    }

    return data->keys[index];
}

char* kv_get_val_s(char* key) {
    if (data == NULL) {
        return NULL;
    }

    int index = kv_key_search(key);
    if (index < 0) {
        return NULL;
    }

    return kv_get_val_i(index);
}

char* kv_get_val_i(int key_index) {
    if (data == NULL) {
        return NULL;
    }

    if (key_index < 0 || key_index >= data->size) {
        return NULL;
    }

    return data->values[key_index];
}

int kv_add_key(char* key) {
    long unsigned int len = strlen(key);
    if (len <= 0) {
        return ALLOC_ERR;
    }

    if (kv_key_search(key) != NOT_FOUND) {
        return DUPLICATE_DETECTED;
    }

    char* tmp = malloc((len + 1)*sizeof(char));
    strcpy(tmp, key);

    int res = resize_struct_arrays(1);

    if (res == OUT_OF_BOUNDS_ERR || res == ALLOC_ERR ) {
        return res;
    }

    data->keys[data->size - 1] = tmp;
    return FINE;
}

int kv_set_val_i(int key_index, char* in) {
    if (data == NULL) {
        return NO_INIT;
    }

    if (key_index < 0 || key_index >= data->size) {
        return OUT_OF_BOUNDS_ERR;
    }

    //free memory if key is overwritten
    if (data->values[key_index] != NULL) {
        free(data->values[key_index]);
    }

    if (in == NULL) {
        return NULL_ERR;
    }

    char* val = malloc((strlen(in) + 1)*sizeof(char));
    strcpy(val, in);

    data->values[key_index] = val;
    return FINE;
}

int kv_set_val_s(char* key, char* val) {
    int index = kv_key_search(key);
    if (index < 0) {
        return index;
    }

    return kv_set_val_i(index, val);
}

int kv_remove_key_s(char* key) {
    int index = kv_key_search(key);
    if (index < 0) {
        return index;
    }
    
    return kv_remove_key_i(index);
}

int kv_remove_key_i(int index) {
    int res;

    if (data == NULL) {
        return NO_INIT;
    }

    if (index < 0 || index >= data->size) {
        return OUT_OF_BOUNDS_ERR;
    }


    //Release memory for char arrays only. to avoid gaps, reassignment will take place further down
    free(data->keys[index]);
    free(data->values[index]);
    //Set to NULL after freeing to ensure memory management checks go through
    data->keys[index] = NULL;
    data->values[index] = NULL;

    //set last array entry to now freed position, close gaps in key_value array
    if ((data->size - 1) > 0) {
        data->keys[index] = data->keys[data->size-1];
        data->values[index] = data->values[data->size-1];
    }
    
    //resize array to one smaller
    res = resize_struct_arrays(-1);

    if (res == ALLOC_ERR || res == OUT_OF_BOUNDS_ERR) {
        return res;
    }

    return FINE;
}

int kv_print_pair(int index) {
    if (data == NULL) {
        return NO_INIT;
    }

    if (index < 0 || index >= data->size) {
        return OUT_OF_BOUNDS_ERR;
    }
    
    char* key = kv_get_key(index);
    char* value = kv_get_val_i(index);

	long unsigned int strlen_key = strlen(key);
	long unsigned int strlen_val;
    if (value != NULL) {
        strlen_val = strlen(value);
    } else {
        strlen_val = 0;
    }
    long unsigned int new_length = strlen_key + strlen_val + 1;
    char out[new_length];
    out[0] = '\0';
    strncpy(out, key, strlen_key + 1);
    strncat(out, ": ", 3);
    if (value != NULL) {
        strncat(out, value, strlen_val + 1);
    }
    printf("%s\n", out);
    return FINE;
}
