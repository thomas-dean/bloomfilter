libbloom
========

A cache efficient, thread safe bloom filter library written in C.

Usage
-----

libbloom shares the same API as that of [the other
libbloom](https://github.com/jvirkki/libbloom). However, this is subject to
change since the library is undergoing early development.

### Example Usage

```c
#include "bloom.h"

struct bloom bloom;

char mystring[] = "Hello, world!";
char myotherstring[] = "Goodbye, world!";
int mynumber = 42;

bloom_init(&bloom, 10000, 1e-6); /* Initialize the bloom filter */

/* Add some stuff to the bloom filter */
bloom_add(&bloom, mystring, sizeof(mystring));
bloom_add(&bloom, myotherstring, sizeof(myotherstring));
bloom_add(&bloom, mynumber, sizeof(mynumber));

/* Check if something is in the bloom filter */
if (bloom_check(&bloom, myotherstring, sizeof(myotherstring))) {
    printf("\"%s\" is in the bloom filter!\n", myotherstring);
}

/* Release the resources used by the bloom filter */
bloom_free(&bloom);
```

Buliding
--------

Requirements:

* FreeBSD Operating System (version 6.1 or above)
* cmake version 3.8 or greater

Build steps:

    $ git clone https://github.com/thomas-dean/bloomfilter bloomfilter
    $ cd bloomfilter
    $ mkdir build && cd build
    $ cmake ..
    $ make

After running the above commands you should find the libbloom library at
`build/src/libbloom.a`.

Running tests
-------------

In order to run the tests, follow the steps above for building the library. Then
run the `runUnitTests` binary found at `build/test/runUnitTests`
