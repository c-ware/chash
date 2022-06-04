#include "common.h"

int main(void) {
    int value = 0;
    struct StringHashtable *hashtable = chash_init(hashtable, STRING_TABLE);

    assert(hashtable->length == 0);
    assert(hashtable->capacity == CHASH_INITIAL_SIZE);

    /* Basic assignment */
    chash_assign(hashtable, "foo", 3, STRING_TABLE);
    assert(hashtable->length == 1);
    assert(hashtable->capacity == CHASH_INITIAL_SIZE);

    chash_assign(hashtable, "bar", 1, STRING_TABLE);
    assert(hashtable->length == 2);
    assert(hashtable->capacity == CHASH_INITIAL_SIZE);

    chash_assign(hashtable, "baz", 2, STRING_TABLE);
    assert(hashtable->length == 3);
    assert(hashtable->capacity == CHASH_INITIAL_SIZE);

    /* Make sure the keys exist */
    value = chash_lookup(hashtable, "baz", value, STRING_TABLE);
    assert(value == 2);

    value = chash_lookup(hashtable, "bar", value, STRING_TABLE);
    assert(value == 1);

    value = chash_lookup(hashtable, "foo", value, STRING_TABLE);
    assert(value == 3);

    /* Replacing keys */
    chash_assign(hashtable, "foo", 2, STRING_TABLE);
    assert(hashtable->length == 3);
    assert(hashtable->capacity == CHASH_INITIAL_SIZE);

    value = chash_lookup(hashtable, "baz", value, STRING_TABLE);
    assert(value == 2);
    assert(hashtable->capacity == CHASH_INITIAL_SIZE);

    value = chash_lookup(hashtable, "bar", value, STRING_TABLE);
    assert(value == 1);
    assert(hashtable->capacity == CHASH_INITIAL_SIZE);

    value = chash_lookup(hashtable, "foo", value, STRING_TABLE);
    assert(value == 2);
    assert(hashtable->capacity == CHASH_INITIAL_SIZE);

    /* Make sure more items can be added */
    chash_assign(hashtable, "tuna", 4, STRING_TABLE);
    assert(hashtable->length == 4);
    assert(hashtable->capacity == CHASH_INITIAL_SIZE);

    chash_assign(hashtable, "spam", 5, STRING_TABLE);
    assert(hashtable->length == 5);
    assert(hashtable->capacity == CHASH_INITIAL_SIZE);

    chash_assign(hashtable, "thud", 5, STRING_TABLE);
    assert(hashtable->length == 6);
    assert(hashtable->capacity == CHASH_INITIAL_SIZE);

    chash_assign(hashtable, "quz", 6, STRING_TABLE);
    assert(hashtable->length == 7);

    chash_assign(hashtable, "foobar", 7, STRING_TABLE);
    assert(hashtable->length == 8);
    assert(hashtable->capacity == CHASH_INITIAL_SIZE);

    /* Should trigger a resize */
    chash_assign(hashtable, "tuna", 7, STRING_TABLE);
    assert(hashtable->length == 8);
    assert(hashtable->capacity == CHASH_INITIAL_SIZE + 3);

    /* Previous keys should not be in the same places */
    value = chash_lookup(hashtable, "foo", value, STRING_TABLE);
    assert(value == 2);

    value = chash_lookup(hashtable, "baz", value, STRING_TABLE);
    assert(value == 2);

    value = chash_lookup(hashtable, "foobar", value, STRING_TABLE);
    assert(value == 7);

    value = chash_lookup(hashtable, "spam", value, STRING_TABLE);
    assert(value == 5);

    chash_free(hashtable, STRING_TABLE);

    return EXIT_SUCCESS;
}
