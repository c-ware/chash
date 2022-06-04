#include "common.h"

int main(void) {
    struct StringBucket *bucket = NULL;
    struct StringHashtable *hashtable = NULL;

    hashtable = chash_init(hashtable, STRING_TABLE);

    chash_assign(hashtable, "foo", 0, STRING_TABLE);
    chash_assign(hashtable, "bar", 1, STRING_TABLE);
    chash_assign(hashtable, "baz", 2, STRING_TABLE);

    bucket = chash_lookup_bucket(hashtable, "bar", bucket, STRING_TABLE);
    assert(strcmp(bucket->key, "bar") == 0);
    assert(bucket->value == 1);

    bucket = chash_lookup_bucket(hashtable, "foo", bucket, STRING_TABLE);
    assert(strcmp(bucket->key, "foo") == 0);
    assert(bucket->value == 0);

    bucket = chash_lookup_bucket(hashtable, "baz", bucket, STRING_TABLE);
    assert(strcmp(bucket->key, "baz") == 0);
    assert(bucket->value == 2);

    chash_free(hashtable, STRING_TABLE);

    return EXIT_SUCCESS;
}
