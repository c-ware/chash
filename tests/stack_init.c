#include "stack_common.h"

int main(void) {
    struct StringBucket buckets[10] = {0};
    struct StringHashtable hashtable = chash_init_stack(&hashtable, buckets, 10, STRING_TABLE);

    assert(hashtable.length == 0);
    assert(hashtable.capacity == 10);
    assert(hashtable.buckets == buckets);

    return EXIT_SUCCESS;
}
