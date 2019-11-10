# Keval

Simple C library for a key value data structure

## Getting Started

Clone project, copy keval.c and keval.c wherever you want.

### Prerequisites

Any C compiler, run preferrably on Linux.

## Important notes

keval's indices are **unstable**! When removing a key from the data structure the last key in the array will be assigned in its place.

## Examples:

### Creating an instance and setting it as active

Calling `kv_spawn` will create a new instance of keval.
You will also have to set it as your active instance in order to use the functions to manipulate the structure. It is currently **not** thread safe!

```C
struct kv_data *data = kv_spawn();
kv_set_instance(data);
```

### Adding keys and values

Adding elements to the data structure is as simple as using the build in functions. It will not allow duplicate keys, but doesn't use hashing as it is designed for a small amount of keys only. As such, adding a key will be O(n).

```C
char key_test[] = "I_am_a_key";
char value_test[] = "123";
kv_add_key(key_test);
// You can set a value using its string O(n)
kv_set_val_s(key_test, value_test));
// or you can set a value using its index
kv_set_val_i(0, value_test);
```

### Retrieving values

It's as simple as adding them! Just call the retrieval function

```C
//with the key string
char *result_s = kv_get_val_s(key_test);
//with an index
char *result_i = kv_get_val_i(0);
```

### Retrieving keys

You can get a key string by its index like this:

```C
char *key = kv_get_key(0);
```

You can also search for a key's index. Just pass the key.
```C
int index = kv_key_search(key_test);
```


### Removing a key

As easy as it gets!

```C
//with an index
kv_remove_key_i(0);
//with the key string
kv_remove_key_s(key_test);
```

### Printing a pair for debugging your program

You can also call a function that prints a key value pair to console in case you need to find out what's being used without writing your own function for it.

```C
kv_print_pair(0)
```

Output if `key = "I_am_a_key"` and `value = "123"`
```
I_am_a_key: 123
```

### Destroying an instance

Destroying a keval instance will free all memory allocated, so you don't have to worry about anything.

Simply call the destructor like this

```C
data = kv_destroy(data);
```


### For more documentation and return values please see the inline doc or `keval.h`

## Running the tests

Main.c provides a quick example and some tests on how to use the data structure.

## People involved

* **Spiritreader** - *Author* - [Profile](https://github.com/Spiritreader)
* **FunnyPocketBook** - *Testing* - [Profile](https://github.com/FunnyPocketBook)
* **GordoGato81** - *Testing*

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Achievements

* Seems to be memory leak free according to valgrind and our limited testing.
* keval.h and keval.c are 100% klausified™.
