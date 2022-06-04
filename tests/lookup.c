#include "common.h"

int main(void) {
    int value = -1;
    struct StringHashtable *hashtable = NULL;

    hashtable = chash_init(hashtable, STRING_TABLE);

    chash_assign(hashtable, "foo", 0, STRING_TABLE);
    chash_assign(hashtable, "bar", 1, STRING_TABLE);
    chash_assign(hashtable, "baz", 2, STRING_TABLE);

    value = chash_lookup(hashtable, "bar", value, STRING_TABLE);
    assert(value == 1);

    value = chash_lookup(hashtable, "foo", value, STRING_TABLE);
    assert(value == 0);

    value = chash_lookup(hashtable, "baz", value, STRING_TABLE);
    assert(value == 2);

    chash_free(hashtable, STRING_TABLE);

    return EXIT_SUCCESS;
}
