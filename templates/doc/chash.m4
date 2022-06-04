## Macros used in the documentation generation.

define(`CHASH_HEADER', `
.TH "CWARE_MANUAL_NAME" "cware" "March 8th, 2022" "" \
    "C-Ware Manual"
')

## $1: the name of the macro
define(`CHASH_EXAMPLE_COMMENT', `
/*
.br
 * This example showcases how to use the
.B $1
macro.
.br
*/
')

## The information like struct definitions and
## $1: value of the heap definition
define(`CHASH_EXAMPLE_INFO', `
.TS
tab(;);
l l
.
#define STRING_TABLE_HEAP;$1
#define STRING_TABLE_BUCKET;struct StringBucket
#define STRING_TABLE_FREE_KEY(key);NULL
#define STRING_TABLE_HASH(key, hash);chash_string_hash(key, hash)
#define STRING_TABLE_FREE_VALUE(value);NULL
#define STRING_TABLE_COMPARE(cmp_a, cmp_b);chash_string_compare(cmp_a, cmp_b)
#define STRING_TABLE_INIT(bucket, _key, _value);\
chash_default_init(bucket, _key, _value)
.TE

struct StringBucket {
.br
    char *key;
.br
    int value;
.br
    int state;
.br
};

struct StringHashtable {
.br
    int length;
.br
    int capacity;
.br
    struct StringBucket *buckets;
.br
};
')

## Dump the inclusions used by the library
define(`CHASH_INCLUSIONS', `
.B #include <stdio.h>
.br
.B #include <stdlib.h>
.br
.B #include <string.h>
.br
.B #include <cware/chash/chash.h>
.br
')

## Format a parameter description
## $1: the name of the parameter
## $2: the description of the parameter
define(`CHASH_PARAMETER', `.I $1
will be $2
.br')

define(`CHASH_SEE_ALSO', `
.BR cware (cware),
.BR chash (cware)
')

## Error list macros

define(`CHASH_ERROR_LIST_START', `
This macro will print an error message to the stderr, and exit the program when
any of the following conditions are met:
.RS
')

## Define a possible error condition
## $1: the error condition
define(`CHASH_ERROR_COND', `
.IP \[bu] 0.4i
$1
.br
')

define(`CHASH_ERROR_LIST_END', `
.RE
')
