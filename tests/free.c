#include "common.h"

int main(void) {
    struct StringHashtable *hashtable = chash_init(hashtable, STRING_TABLE);

    chash_assign(hashtable, "foo", 1, STRING_TABLE);
    chash_assign(hashtable, "bar", 1, STRING_TABLE);
    chash_assign(hashtable, "baz", 1, STRING_TABLE);

    chash_free(hashtable, STRING_TABLE);

    return 0;
}
