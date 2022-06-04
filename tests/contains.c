#include "common.h"

int main(void) {
    int contains = -5;
    struct StringHashtable *hashtable = chash_init(hashtable, STRING_TABLE);

    contains = chash_contains(hashtable, "foo", contains, STRING_TABLE);
    assert(contains == 0);

    chash_assign(hashtable, "foo", 1, STRING_TABLE);

    contains = chash_contains(hashtable, "foo", contains, STRING_TABLE);
    assert(contains == 1);

    contains = chash_contains(hashtable, "bar", contains, STRING_TABLE);
    assert(contains == 0);

    chash_free(hashtable, STRING_TABLE);

    return 0;
}
