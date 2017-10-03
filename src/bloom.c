#include "bloom.h"

/*
 * Bloom filter implementation. See bloom.h for API information.
 */

int bloom_init(struct bloom *bloom, uint64_t entries, double fp_rate)
{
    double num, denom, bpe, dentries;
    uint64_t bytes;

    bloom->initialized = 0;
    if (fp_rate >= 1 || fp_rate <= 0) {
        return 1;
    }

    /*
     * Initialization code inspired by:
     * https://github.com/jvirkki/libbloom/blob/master/bloom.c#L95
     */
    num = log(fp_rate);
    denom = 0.480453013918201; // ln(2)^2
    bpe = -(num / denom);

    dentries = (double)entries;
    bloom->bits = (uint_fast32_t)(dentries * bpe);

    if (bloom->bits % 8) {
        bytes = (bloom->bits / 8) + 1;
    } else {
        bytes = bloom->bits / 8;
    }

    bloom->hashes = (uint_fast16_t)ceil(0.693147180559945 * bpe); // ln(2)
    if ((bloom->bf = calloc(bytes, sizeof(uint8_t))) == NULL) {
        return 1;
    }
    bloom->initialized = 1;
    return 0;
}

int bloom_add(struct bloom *bloom, const void *element, size_t len)
{
    uint64_t hits;
    uint32_t a, b, x, i;

    if (!bloom->initialized) {
        return -1;
    }

    hits = 0;
    /*
     * Note we are using the FreeBSD kernel hash32_buf function. All of these
     * hash functions return 32-bit values. This is currently not an issue since
     * we are indexing into a bit array which will probably not be large enough
     * to warnent generating a larger hash
     */
    a = hash32_buf(element, len, HASHINIT);
    b = hash32_buf(element, len, a);
    for (i = 0; i < bloom->hashes; i++) {
        x = (a + i * b) % bloom->bits;
        if (__sync_fetch_and_or(bloom->bf + (x >> 3), x & 7)) {
            hits++;
        }
    }

    if (hits == bloom->hashes) {
        return 1;
    }
    return 0;
}

int bloom_check(struct bloom *bloom, const void *element, size_t len)
{
    uint64_t hits;
    uint32_t a, b, x, i;

    if (!bloom->initialized) {
        return -1;
    }

    hits = 0;
    /* See bloom_add for comment on hash functions used */
    a = hash32_buf(element, len, HASHINIT);
    b = hash32_buf(element, len, a);
    for (i = 0; i < bloom->hashes; i++) {
        x = (a + i * b) % bloom->bits;
        if (*(bloom->bf + (x >> 3)) & (x & 7)) {
            hits++;
        } else {
            return 0;
        }
    }

    if (hits == bloom->hashes) {
        return 1;
    }
    return 0;
}

void bloom_free(struct bloom *bloom)
{
    if (bloom->initialized) {
        free(bloom->bf);
    }
    bloom->initialized = 0;
}
