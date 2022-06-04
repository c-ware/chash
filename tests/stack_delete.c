#include "stack_common.h"

int main(void) {
    int exists = -5;
    struct StringBucket buckets[10] = {0};
    struct StringHashtable hashtable = chash_init_stack(&hashtable, buckets,
                                                        10, STRING_TABLE);

    chash_assign(&hashtable, "foo", 1, STRING_TABLE);
    chash_assign(&hashtable, "bar", 1, STRING_TABLE);
    chash_assign(&hashtable, "baz", 1, STRING_TABLE);

    assert(hashtable.length == 3);

    chash_delete(&hashtable, "bar", STRING_TABLE);
    exists = chash_contains(&hashtable, "bar", exists, STRING_TABLE);
    assert(hashtable.length == 2);
    assert(exists == 0);
    exists = -5;

    chash_delete(&hashtable, "baz", STRING_TABLE);
    exists = chash_contains(&hashtable, "baz", exists, STRING_TABLE);
    assert(hashtable.length == 1);
    assert(exists == 0);
    exists = -5;

    chash_delete(&hashtable, "foo", STRING_TABLE);
    exists = chash_contains(&hashtable, "foo", exists, STRING_TABLE);
    assert(hashtable.length == 0);
    assert(exists == 0);
    exists = -5;

    chash_free(&hashtable, STRING_TABLE);

    return 0;
}
