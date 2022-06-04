/*
 * Tests the macros using struct values.
*/

#include "common.h"

#define PLAYER_T_HEAP                   1
#define PLAYER_T_BUCKET                 struct PlayerBucket
#define PLAYER_T_FREE_KEY(key)
#define PLAYER_T_HASH(key, hash)        key.level + key.damage + key.defense
#define PLAYER_T_FREE_VALUE(value)      NULL
#define PLAYER_T_COMPARE(cmp_a, cmp_b)  cmp_a.level == cmp_b.level &&   \
                                        cmp_a.damage == cmp_b.damage && \
                                        cmp_a.defense == cmp_b.defense
#define PLAYER_T_INIT(bucket, _key, _value) chash_default_init(bucket, _key, \
                                                               _value)

struct Player {
    int level;
    int damage;
    int defense;
};

struct PlayerBucket {
    struct Player key;
    char *value;
    int state;
};

struct PlayerTable {
    int length;
    int capacity;
    struct PlayerBucket *buckets;
};

int main(void) {
    int contains = -1;
    char *value = NULL;
    struct Player player_a = {10, 15, 3};
    struct Player player_b = {5, 3, 1};
    struct Player player_c = {8, 5, 9};
    struct Player player_d = {9, 13, 6};
    struct Player player_e = {1, 13, 6};
    struct Player player_f = {6, 3, 0};
    struct PlayerTable *hashtable = chash_init(hashtable, PLAYER_T);

    /* Add some values */
    chash_assign(hashtable, player_a, "a", PLAYER_T);
    chash_assign(hashtable, player_b, "b", PLAYER_T);
    chash_assign(hashtable, player_c, "c", PLAYER_T);
    chash_assign(hashtable, player_d, "d", PLAYER_T);

    assert(hashtable->length == 4);

    /* player_d should exist */
    contains = chash_contains(hashtable, player_a, contains, PLAYER_T);
    assert(contains == 1);

    /* player_e should NOT exist */
    contains = chash_contains(hashtable, player_e, contains, PLAYER_T);
    assert(contains == 0);

    /* Look up the value assigned to player c */
    value = chash_lookup(hashtable, player_c, value, PLAYER_T);
    assert(strcmp(value, "c") == 0);

    /* player_b and player_d should (indirectly) collide */    
    assert(hashtable->buckets[9].key.level == 5);
    assert(hashtable->buckets[0].key.level == 9);

    /* Removing player_b will make its slot a tombstone, which should be
     * passed over by the lookup macro when looking for player_d. */
    chash_delete(hashtable, player_b, PLAYER_T);
    value = chash_lookup(hashtable, player_d, value, PLAYER_T);
    assert(strcmp(value, "d") == 0);

    /* player_b should not be able to be found; even if its a tombstone */
    contains = -1;
    contains = chash_contains(hashtable, player_b, contains, PLAYER_T);
    assert(contains == 0);

    /* Now that player_b is deleted and is a tombstone, it should be
     * overwritable */
    chash_assign(hashtable, player_f, "f", PLAYER_T);
    assert(hashtable->buckets[9].key.level == 6);
    assert(hashtable->buckets[0].key.level == 9);

    /* player_b still should not be able to be found */
    contains = -1;
    contains = chash_contains(hashtable, player_b, contains, PLAYER_T);
    assert(contains == 0);

    /* But player_f should */
    contains = -1;
    contains = chash_contains(hashtable, player_f, contains, PLAYER_T);
    assert(contains == 1);

    chash_free(hashtable, PLAYER_T);

    return EXIT_SUCCESS;
}
