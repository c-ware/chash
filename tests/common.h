#ifndef CWARE_LIBCHASH_COMMON_H
#define CWARE_LIBCHASH_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../src/chash.h"

#define STRING_TABLE_HEAP                   1
#define STRING_TABLE_BUCKET                 struct StringBucket
#define STRING_TABLE_FREE_KEY(key)
#define STRING_TABLE_HASH(key, hash)        chash_string_hash(key, hash)
#define STRING_TABLE_FREE_VALUE(value)      NULL
#define STRING_TABLE_COMPARE(cmp_a, cmp_b)  chash_string_compare(cmp_a, cmp_b)
#define STRING_TABLE_INIT(bucket, _key, _value) \
    chash_default_init(bucket, _key, _value)

#define STRING_STABLE_HEAP                   0
#define STRING_STABLE_BUCKET                 struct StringBucket
#define STRING_STABLE_FREE_KEY(key)
#define STRING_STABLE_HASH(key, hash)        chash_string_hash(key, hash)
#define STRING_STABLE_FREE_VALUE(value)      NULL
#define STRING_STABLE_COMPARE(cmp_a, cmp_b)  chash_string_compare(cmp_a, cmp_b)
#define STRING_STABLE_INIT(bucket, _key, _value) \
    chash_default_init(bucket, _key, _value)

#define INTPTR_TABLE_HEAP                   1
#define INTPTR_TABLE_BUCKET                 struct IntPtrBucket
#define INTPTR_TABLE_FREE_KEY(key)
#define INTPTR_TABLE_HASH(key, hash)        ((unsigned long) (key))
#define INTPTR_TABLE_FREE_VALUE(value)      NULL
#define INTPTR_TABLE_COMPARE(cmp_a, cmp_b)  (cmp_a == cmp_b)
#define INTPTR_TABLE_INIT(bucket, _key, _value) \
    chash_default_init(bucket, _key, _value)

struct StringBucket {
    char *key;
    int value;
    int state;
};

struct StringHashtable {
    int length;
    int capacity;
    struct StringBucket *buckets;
};

struct IntPtrBucket {
    int *key;
    int value;
    int state;
};

struct IntPtrHashtable {
    int length;
    int capacity;
    struct IntPtrBucket *buckets;
};

void read(struct StringHashtable table) {
    CHASH_COUNTER_TYPE index = 0;

    for(index = 0; index < table.capacity; index++) {
        if(table.buckets[index].state != CHASH_FILLED) {
            printf("%i NULL: 0\n", index);

            continue;
        }

        printf("%i %s: %i\n", index, table.buckets[index].key, table.buckets[index].value);
    }
}

#endif
