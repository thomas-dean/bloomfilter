libbloom
========

A cache efficient, thread safe bloom filter library written in C.

Buliding
--------

Requirements:

* Linux / Unix Operating System
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
