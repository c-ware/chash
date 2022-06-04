#include "common.h"

int main(void) {
    char *key = NULL;
    int index = 0;
    int value = 0;
    int sequence = 0;
    struct StringHashtable *hashtable = chash_init(hashtable, STRING_TABLE);

    chash_assign(hashtable, "foo", 1, STRING_TABLE);
    chash_assign(hashtable, "bar", 2, STRING_TABLE);
    chash_assign(hashtable, "baz", 3, STRING_TABLE);
    chash_assign(hashtable, "tuna bar", 4, STRING_TABLE);

    /* Iterate through the hashtable */
    chash_iter(hashtable, index, key, value) {
        chash_skip(hashtable, index);

        /* Make sure the proper keys are retrieved */
        if(sequence == 0) {
            assert(strcmp(key, "baz") == 0);
            assert(value == 3);
        } else if(sequence == 1) {
            assert(strcmp(key, "bar") == 0);
            assert(value == 2);
        } else if(sequence == 2) {
            assert(strcmp(key, "tuna bar") == 0);
            assert(value == 4);
        } else {
            assert(strcmp(key, "foo") == 0);
            assert(value == 1);
        }

        sequence++;
    }

    chash_free(hashtable, STRING_TABLE);

    return EXIT_SUCCESS;
}
