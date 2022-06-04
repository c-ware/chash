#ifndef CWARE_LIBCHASH_STACK_COMMON_H
#define CWARE_LIBCHASH_STACK_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../src/chash.h"

#define STRING_TABLE_HEAP                   0
#define STRING_TABLE_BUCKET                 struct StringBucket
#define STRING_TABLE_FREE_KEY(key)
#define STRING_TABLE_HASH(key, hash)        chash_string_hash(key, hash)
#define STRING_TABLE_FREE_VALUE(value)
#define STRING_TABLE_COMPARE(cmp_a, cmp_b)  chash_string_compare(cmp_a, cmp_b)
#define STRING_TABLE_INIT(bucket, _key, _value) \
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

#endif
