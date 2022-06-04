#include "common.h"

int main(void) {
    struct StringBucket buckets[3] = {0};
    struct StringHashtable hashtable = chash_init_stack(&hashtable, buckets, 3,
                                                        STRING_STABLE);

    assert(chash_is_full(&hashtable, STRING_STABLE) == 0);

    chash_assign(&hashtable, "foo", 1, STRING_STABLE);
    assert(chash_is_full(&hashtable, STRING_STABLE) == 0);

    chash_assign(&hashtable, "bar", 2, STRING_STABLE);
    assert(chash_is_full(&hashtable, STRING_STABLE) == 0);

    /* Duplicate names do not cause an extra full hashtable */
    chash_assign(&hashtable, "bar", 2, STRING_STABLE);
    assert(chash_is_full(&hashtable, STRING_STABLE) == 0);

    chash_assign(&hashtable, "bar", 3, STRING_STABLE);
    assert(chash_is_full(&hashtable, STRING_STABLE) == 0);

    chash_assign(&hashtable, "baz", 1, STRING_STABLE);
    assert(chash_is_full(&hashtable, STRING_STABLE) == 1);

    chash_free(&hashtable, STRING_STABLE);

    return EXIT_SUCCESS;
}
