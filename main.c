#include <stdio.h>
#include <stdlib.h>
#include "keval.h"

int main()
{
    char header[] = "GET /favicon.ico HTTP/1.1"
                "\nHost: localhost:8080"
                "\nConnection: keep-alive"
                "\nPragma: no-cache"
                "\nCache-Cont6rol: no-cache"
                "\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.87 Safari/537.36"
                "\nDNT: 1"
                "\nAccept: image/webp,image/apng,image/,/*;q=0.8"
                "\nSec-Fetch-Site: same-origin"
                "\nSec-Fetch-Mode: no-cors"
                "\nReferer: http://localhost:8080/"
                "\nAccept-Encoding: gzip, deflate, br"
                "\nAccept-Language: en-US,en;q=0.9,de;q=0.8"
                "\n"
                "\nzip, deflate, br"
                "\nAccept-Language: en-US,en;q=0.9,de;q=0.8";
    struct kv_data *data = kv_spawn();
    if (data == NULL) {
        return -1;
    }
    char joh[] = "Johannes";
    char lennard[] = "Lennard";
    char* test = malloc(5*sizeof(char));
    test[0] = '1';
    test[1] = '1';
    test[2] = '1';
    test[3] = '1';
    test[4] = '\0';
    kv_add_key(joh, data);
    kv_add_key(joh, data);
    kv_add_key(lennard, data);
    kv_set_val_s("Johannes", test, data);
    free(test);
    kv_set_val_s("Lennard", "short", data);
    kv_set_val_s("Lennard", "is configuring launch.json", data);
    kv_set_val_s("Johannes", "Peter", data);
    kv_print_pair(0, data);
    kv_remove_key_i(0, data);
    kv_remove_key_i(0, data);
    kv_remove_key_i(0, data);
    kv_print_pair(0, data);
    kv_add_key(joh, data);
    kv_set_val_s(joh, "Hi", data);
    data = kv_destroy(data);

    //new test
    struct kv_data *ary1 = kv_spawn();
    struct kv_data *ary2 = kv_spawn();
    kv_add_key(lennard, ary1);
    kv_add_key(joh, ary1);
    kv_set_val_s("Lennard", "short", ary1);
    kv_set_val_i(1, "Peter", ary1);
    kv_add_key(joh, ary2);
    kv_set_val_i(0, "Hans", ary2);
    kv_print_pair(1, ary2);
    kv_print_pair(0, ary1);
    ary2 = kv_destroy(ary2);
    kv_print_pair(0, ary2);
    ary1 = kv_destroy(ary1);
    return 0;
}
