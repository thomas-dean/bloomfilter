#include <assert.h>
#include <stdio.h>

#include "bloom.h"

#define BLOOM_SIZE 10000

static int simple_test(void);

static int simple_test(void)
{
    struct bloom bloom;

    assert(bloom_init(&bloom, BLOOM_SIZE, -1) == 1);                   /* Should fail */
    assert(bloom_add(&bloom, "Hello world!", 12) == -1);   /* Should fail */
    assert(bloom_check(&bloom, "Hello world!", 12) == -1); /* Should fail */
    assert(bloom_init(&bloom, BLOOM_SIZE, 0.01) == 0);
    assert(bloom_check(&bloom, "Hello world!", 12) == 0);
    assert(bloom_add(&bloom, "Hello world!", 12) == 0);
    assert(bloom_add(&bloom, "Hello world!", 12) == 1);
    assert(bloom_check(&bloom, "Hello world!", 12) == 1);
    bloom_free(&bloom);
    assert(bloom_add(&bloom, "Hello world!", 12) == -1);   /* Should fail */
    assert(bloom_check(&bloom, "Hello world!", 12) == -1); /* Should fail */
    assert(bloom_init(&bloom, BLOOM_SIZE, 1.00) == 1);                 /* Should fail */
    assert(bloom_init(&bloom, BLOOM_SIZE, 0.00) == 1);                 /* Should fail */
    assert(bloom_init(&bloom, BLOOM_SIZE, 0.50) == 0);                 /* Can reinitialize */
    bloom_free(&bloom);

    return 0;
}

int main(void)
{
    int rv;

    printf("----------- Running simple test ------------\n");
    rv = simple_test();
    printf("--------- Done running simple test ---------\n");

    return rv;
}
