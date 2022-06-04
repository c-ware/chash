/*
 * Test adding variable addresses as keys
*/

#include "common.h"

int main(void) {
    int x = 0;
    int y = 1;
    int z = 2;
    int value = 0;
    int exists = -1;
    struct IntPtrHashtable *new_hashtable = chash_init(new_hashtable,
                                                       INTPTR_TABLE);
    chash_assign(new_hashtable, &x, 1, INTPTR_TABLE);
    chash_assign(new_hashtable, &y, 2, INTPTR_TABLE);
    chash_assign(new_hashtable, &z, 3, INTPTR_TABLE);

    /* Do they exist? */
    value = chash_lookup(new_hashtable, &x, value, INTPTR_TABLE);
    assert(value == 1);

    value = chash_lookup(new_hashtable, &y, value, INTPTR_TABLE);
    assert(value == 2);

    value = chash_lookup(new_hashtable, &z, value, INTPTR_TABLE);
    assert(value == 3);
    
    /* Delete &y */
    chash_delete(new_hashtable, &y, INTPTR_TABLE);

    exists = chash_contains(new_hashtable, &y, exists, INTPTR_TABLE);
    assert(exists == 0);

    chash_free(new_hashtable, INTPTR_TABLE);

    return EXIT_SUCCESS;
}
