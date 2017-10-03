#ifndef _BLOOM_H
#define _BLOOM_H

#include <inttypes.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/hash.h>

/*
 * Structure to keep track of a bloom filter.
 *
 * Should be allocated by the caller and initialized by the bloom_init
 * function. It can then be used as the first parameter to the functions below.
 */
struct bloom {
    uint_fast32_t bits;          /* Number of bits in the bloom filter buffer */
    uint_fast16_t hashes;        /* Number of hashes used per element added */
    uint8_t *bf;                 /* Location of the underlying bit field */
    uint8_t initialized;         /* 1 if the bloom is ready for use, 0 otherwise */
    uint8_t _padding[7];         /* Padding to align struct to 64 bits */
};

/*
 * bloom_init: initialize a bloom filter.
 *
 * Parameters:
 *   bloom: The allocated but uninitialized bloom filter struct
 *   entries: The expected number of elements that will be added
 *   fp_rate: The desired upper bound on the false positive rate
 *
 * Returns:
 *   0 -> Success
 *   1 -> Failure
 */
int bloom_init(struct bloom *bloom, uint64_t entries, double fp_rate);

/*
 * bloom_add: add an item to a bloom filter.
 *
 * Parameters:
 *   bloom: The allocated and initialized bloom filter struct
 *   element: A non-null pointer to the data that should be added
 *   len: The length of element
 *
 * Returns:
 *    0 - element was not present and was added
 *    1 - element (or a collision) had already been added previously
 *   -1 - bloom not initialized
 */
int bloom_add(struct bloom *bloom, const void *element, size_t len);

/*
 * bloom_check: check if an item is in the bloom filter.
 *
 * Parameters:
 *   bloom: The allocated and initialized bloom filter struct
 *   element: A non-null pointer to the data that should be checked
 *   len: The length of element
 *
 * Returns:
 *    0 - element is not present
 *    1 - element is present (or a collision)
 *   -1 - bloom not initialized
 */
int bloom_check(struct bloom *bloom, const void *element, size_t len);

/*
 * bloom_free: deallocate the resources used by a bloom filter
 *
 * The bloom filter can be reinitialized with bloom_init
 *
 * Parameters:
 *   bloom: The allocated and initialized bloom filter struct which should be
 *          freed
 *
 * Returns:
 *   None
 */
void bloom_free(struct bloom *bloom);

#endif /* _BLOOM_H */
