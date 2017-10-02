#include "bloom.h"

/*
 * Bloom filter implementation. See bloom.h for API information.
 */

int bloom_init(struct bloom *bloom, double fp_rate)
{
    return 0;
}

int bloom_add(struct bloom *bloom, const void *element, size_t len)
{
    return 0;
}

int bloom_check(struct bloom *bloom, const void *element, size_t len)
{
    return 0;
}

void bloom_free(struct bloom *bloom)
{
}
