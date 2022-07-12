/*
 * A word counter, which reads space-delimited words through stdin,
 * and counts how many times that word appears in the stdin.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../src/chash.h"

/* This macro will tell chash whether or not this hashtable will be
 * like itself and its contents are allocated on the heap, or the
 * stack. This is used so accidentally free()'s do not attempt to
 * release a hashtable that is allocated on the stack, but has keys
 * that are on the heap, which need to be freed, for example.
 *
 * If this macro is 0, then it is assumed the hashtable structure should
 * not be resized, and should not have its underlying contents field,
 * and the structure itself, released from memory. This, however,
 * does not prevent the releasing of the actual individual keys and
 * values of the hashtable. To control that, either define the
 * key and value release macros with free-logic, or leave them empty--
 * but defined, to not do any releasing of a key or value. */
#define SI_TABLE_HEAP                   1

/* This macro will tell chash what the underlying type of bucket
 * to use for this hashtable The FULL type signature must be provided,
 * as chash will not make any assumptions of the structure of the type,
 * like for example whether its type-defed, just a structure, etc. */
#define SI_TABLE_BUCKET                 struct SIBucket

/* This macro is pretty straight forward. It is just how you tell
 * chash how to free a key in a bucket. If the key is, for example,
 * on the stack, you can specify something that will just be a no-op,
 * like NULL, or literally just nothing. All that matters is that the
 * macro is defined. */
#define SI_TABLE_FREE_KEY(key)

/*
 * This macro will tell chash how to hash the key-- converting
 * it into an integer. The final hash should be written into the
 * hash parameter. The internal hash variable is always defined
 * as 0, as well. This prevents the need to do something like:
 *                                                        |
 * #define MY_HASH(key, hash) \                           |
 *     0; <-----------------------------------------------|
 *                            \
 *     do {                   \
 *          // hash key       \
 *     } while(0)
 * 
 * To initialize the hash with a 'default' value.
*/
#define SI_TABLE_HASH(key, hash)        chash_string_hash(key, hash)

/* This macro is pretty straight forward. It is just how you tell
 * chash how to free a value in a bucket. If the value is, for example,
 * on the stack, you can specify something that will just be a no-op,
 * like NULL, or literally just nothing. All that matters is that the
 * macro is defined. */
#define SI_TABLE_FREE_VALUE(value)      NULL

/* This is used for telling chash how to compare two keys
 * in a hashtable. Used in situations where there is a
 * collision. This macro should evaluate to an integer.
 * Strings should be compared using strcmp, so for example,
 * the chash_string_compare builtin will evaluate to this
 * in an if statement when preprocessed:
 *
 * if((strcmp(cmp_a, cmp_b) == 0) == 1) {
 *  ...
 * }
*/
#define SI_TABLE_COMPARE(cmp_a, cmp_b)  chash_string_compare(cmp_a, cmp_b)

/* This is most likely the to be the hardest to understand 
 * property of a hashtable. Essentially, this macro describes
 * how to 'initialize' a bucket. Think of it as the 'default
 * structure' of any bucket.
 *
 * _key is the key to initialize the bucket with
 * _value is the value to initialize the bucket with
 *
 * Most of the time, the programmer is unlikely to need to
 * initialize a bucket in any "abnormal" way, so chash
 * provides a function which just does assignment of the
 * keys and values with literally no change whatsoever. */
#define SI_TABLE_INIT(bucket, _key, _value) \
    chash_default_init(bucket, _key, _value)

/*
 * String-integer bucket
*/
struct SIBucket {
    char *key;
    int value;
    int state;
};

/*
 * String-integer hashtable
*/
struct SITable {
    int length;
    int capacity;
    struct SIBucket *buckets;
};

int main(void) {
    /* First off, let's initialize the hashtable. */
    struct SITable *word_counts = chash_init(word_counts, SI_TABLE);

    /* Release the hashtable */
    chash_free(word_counts, SI_TABLE);

    return EXIT_SUCCESS;
}
