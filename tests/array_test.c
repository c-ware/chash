/*
 * Tests the creation of a bucket with array keys using the
 * initializer macro.
*/

#include "common.h"

#define CHRARR_TABLE_HEAP                   1
#define CHRARR_TABLE_BUCKET                 struct ChrArrBucket
#define CHRARR_TABLE_FREE_KEY(key)
#define CHRARR_TABLE_HASH(key, hash)        chash_string_hash(key, hash)
#define CHRARR_TABLE_FREE_VALUE(value)      NULL
#define CHRARR_TABLE_COMPARE(cmp_a, cmp_b)  chash_string_compare(cmp_a, cmp_b)
#define CHRARR_TABLE_INIT(bucket, _key, _value)   strcpy((bucket).key, _key); \
                                                  (bucket).value = _value;

struct ChrArrBucket {
    char key[32];
    int value;
    int state;
};

struct ChrArrHashtable {
    int length;
    int capacity;
    struct ChrArrBucket *buckets;
};

int main(void) {
    int key = 0;
    char key_a[32] = "foo bar baz";
    char key_b[32] = "tuna spam thud";
    struct ChrArrHashtable *new_hashtable = chash_init(new_hashtable,
                                                       CHRARR_TABLE);

    chash_assign(new_hashtable, key_a, 1, CHRARR_TABLE);
    chash_assign(new_hashtable, key_b, 2, CHRARR_TABLE);

    chash_lookup(new_hashtable, key_a, key, CHRARR_TABLE);
    assert(key == 1);

    chash_lookup(new_hashtable, key_b, key, CHRARR_TABLE);
    assert(key == 2);

    chash_free(new_hashtable, CHRARR_TABLE);

    return EXIT_SUCCESS;
}
