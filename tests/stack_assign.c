#include "stack_common.h"

int main(void) {
    struct StringBucket buckets[10] = {0};
    struct StringHashtable hashtable = chash_init_stack(&hashtable, buckets, 10, STRING_TABLE);

    assert(hashtable.length == 0);

    /* Basic assignment */
    chash_assign(&hashtable, "foo", 3, STRING_TABLE);
    assert(hashtable.length == 1);

    chash_assign(&hashtable, "bar", 1, STRING_TABLE);
    assert(hashtable.length == 2);

    chash_assign(&hashtable, "baz", 2, STRING_TABLE);
    assert(hashtable.length == 3);

    assert(strcmp(hashtable.buckets[2].key, "baz") == 0);
    assert(hashtable.buckets[2].value == 2);

    assert(strcmp(hashtable.buckets[4].key, "bar") == 0);
    assert(hashtable.buckets[4].value == 1);

    assert(strcmp(hashtable.buckets[9].key, "foo") == 0);
    assert(hashtable.buckets[9].value == 3);

    /* Replacing keys */
    chash_assign(&hashtable, "foo", 2, STRING_TABLE);
    assert(hashtable.length == 3);

    assert(strcmp(hashtable.buckets[2].key, "baz") == 0);
    assert(hashtable.buckets[2].value == 2);

    assert(strcmp(hashtable.buckets[4].key, "bar") == 0);
    assert(hashtable.buckets[4].value == 1);

    assert(strcmp(hashtable.buckets[9].key, "foo") == 0);
    assert(hashtable.buckets[9].value == 2);

    /* Make sure more items can be added */
    chash_assign(&hashtable, "tuna", 4, STRING_TABLE);
    assert(hashtable.length == 4);

    chash_assign(&hashtable, "spam", 5, STRING_TABLE);
    assert(hashtable.length == 5);

    chash_assign(&hashtable, "thud", 5, STRING_TABLE);
    assert(hashtable.length == 6);

    return EXIT_SUCCESS;
}
