# chash
A highly portable implementation of a type safe hashtable for the C programming
language.

## How It Works
The implementation of chash is quite different from what most might consider
to be a proper implementation of a data structure in plain C. Unlike languages
such as Rust and Go, C lacks logic for proper type-safe generics. If somebody
wants to achieve type safe data structures in C, (or rather, as close as we
can get), they must resort to two main solutions.

- Using macros to inline code, since macro arguments are not type checked
- Using macros to generate functions for each operation.

Both of these are pretty OK solutions in my eyes. However, that being said, 
while both of these tactics have pros and cons, I feel like making the macros
themselves be the operations is the best solution in the long run.

While the idea of using macros for data structures is far from a new concept,
chash, as well as all of the other data structure implementations in C-Ware,
use something I call namespacing to store important information about each
hashtable.

A cool feature of the C preprocessor is the ability to join two tokens into a
single token with the `##` operator. The C-Ware data structures make heavy use
of this, as it allows us to store information like the internal types of a
hashtable, user-defined operations like hashing and freeing, and more inside of
individual macros. This is done by assigning a prefix to a macro function or
constant name, then the property name. This allows any given operation to have
access to important information about the internals of the hashtable at compile
time, without the programmer having to have a bunch of annoying extra parameters
to each macro operation.

As an example of the above, let's say you had a hashtable which stored buckets
that had a string as a key, and an integer as a value. Let's also say you
wanted to initialize the hashtable, too.

```c
#define SITABLE_BUCKET  struct SIBucket

struct SIBucket {
    char *key;
    int value;
    int state;
};

struct SITable {
    int length;
    int capacity;
    struct SIBucket *buckets;
};

int main(void) {
    struct SITable *new_hashtable = chash_init(new_hashtable, SITABLE);

    return 0;
}
```

To initialize the hashtable, we give `chash_init` the namespace of this hashtable,
which allows it to, among other things, lookup the type of the hashtable to know
how many bytes it must allocate for the buckets field. For more of a practical
example of how to use chash, as well as an example of all the properties that
you must define for a hashtable to be used, see the `examples/` directory.

## What Does This Support?
You might recall me mentioning that this implementation is *highly portable.*
When I say highly portable, I mean it supports all of these operating systems.

#### Linux
- Arch Linux
- Debian
- Linux Mint

#### BSDs
- NetBSD
- FreeBSD
- OpenBSD
- DragonflyBSD

#### Random UNIXes I have for some reason
