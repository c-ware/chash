/*
 * An extreme test of chash that is immune to CPU caching from successive runs.
*/

/*
#define LIMIT   10000000
#define CHASH_RESIZE(size) \
   ((size) * 2.0)
*/

/* #define CHASH_LOAD_THRESHOLD 0.1 */

#include "common.h"
#include <time.h>

/* NOTE NOTE NOTE NOTE -- you need to edit this macro! */
#define LIMIT 50000

/* Since we're going for the fastest possible speed, globals are used. */
struct StringHashtable* stress_table;
int i = 0;
int value = -1;

/* Test data */
char** strings;

/* Valid characters for random strings */
char charset[] = "0123456789"
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/* Make a random string */
void rand_str(char* dest, size_t length) {
    while(length-- > 0) {
        size_t pos = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *dest++ = charset[pos];
    }
    *dest = '\0';
}


int main(void) {
    clock_t start, halfway, end;
    char* key;

    /* Size memory */
    printf("Sizing memory\n");
    strings = malloc(sizeof(char*) * LIMIT);

    for(i = 0; i < LIMIT; i++) {
        strings[i] = malloc(16);
    }
   
    srand(time(NULL)); 
    /* Generate the test data. */
    printf("Generating strings\n");

    for(i = 0; i < LIMIT; i++) {
        rand_str(strings[i], 16);
    }

    printf("Execution begins\n");


    /* Start time marker */
    start = clock();
    printf("Init hashtable\n");
    
    /* Generate the hashtable */
    stress_table = chash_init(stress_table, STRING_TABLE);
    printf("Add strings\n");

    /* Add each string */
    for(i = 0; i < LIMIT; i++) {
        chash_assign(stress_table, strings[i], i, STRING_TABLE);
    }

    /* Done with fill time marker */
    halfway = clock();
    
    /* Correct length? */
    printf("Length is now %d\n", stress_table->length);
    printf("Length should be %d\n", LIMIT);

    /* Verify each string is inside the hashtable, and they have the
     * correct value */
    for(i = 0; i < LIMIT; i++) {
        value = chash_lookup(stress_table, strings[i], value, STRING_TABLE);
        if(value != i) {
            printf("Duplicate found - %d\n", i);
        }
    }

    /* Print it out -- disabled
    for(i = 0; i < stress_table->capacity; i++) {
        if(stress_table->buckets[i].state != CHASH_FILLED) {
            printf("%i - EMPTY\n", i);
            continue;
        }
        printf("%i - %s - %i\n", i, stress_table->buckets[i].key, stress_table->buckets[i].value);
    }
    */

    chash_free(stress_table, STRING_TABLE);

    /* Measure and calculate the runtime */
    end = clock();
    printf("Fill time: %f\n", ((double)(halfway - start) / CLOCKS_PER_SEC));
    printf("Read time: %f\n", ((double)(end - halfway) / CLOCKS_PER_SEC));
    printf("Total time: %f\n", ((double)(end - start) / CLOCKS_PER_SEC));
    

    /* Release memory */
    for(i = 0; i < LIMIT; i++) {
        free(strings[i]);
    }
    free(strings);


    /* Leave */
    printf("Strike any key to continue...\n");
    fgetc(stdin);

    return EXIT_SUCCESS;
}
