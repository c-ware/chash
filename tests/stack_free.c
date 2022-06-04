#include "stack_common.h"

int main(void) {
    struct StringBucket buckets[10] = {0};
    struct StringHashtable hashtable = chash_init_stack(&hashtable, buckets,
                                                        10, STRING_TABLE);

    chash_assign(&hashtable, "foo", 1, STRING_TABLE);
    chash_assign(&hashtable, "bar", 1, STRING_TABLE);
    chash_assign(&hashtable, "baz", 1, STRING_TABLE);

    chash_free(&hashtable, STRING_TABLE);
    assert(hashtable.capacity == -1);
    assert(hashtable.length == 0);

    return 0;
}
