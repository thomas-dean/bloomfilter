#include <stdio.h>
#include <sys/time.h>

#include "bloom.h"

#define BLOOM_SIZE 100000000
#define ERROR_RATE 1e-6

int main(void)
{
    int i;
    struct timeval t0, t1;
    struct bloom bloom;

    if (bloom_init(&bloom, BLOOM_SIZE, ERROR_RATE) != 0) {
        fprintf(stderr, "Failed to initialize bloom filter.\n");
        return 1;
    }

    /* Insert timing */
    gettimeofday(&t0, NULL);
    for (i = 0; i < BLOOM_SIZE; ++i) {
        bloom_add(&bloom, &i, sizeof(int));
    }
    gettimeofday(&t1, NULL);
    printf("Inserted %d elements in %.5g seconds\n", i, t1.tv_sec - t0.tv_sec + 1E-6 * (t1.tv_usec - t0.tv_usec));

    /* Query timing */
    gettimeofday(&t0, NULL);
    for (i = 0; i < BLOOM_SIZE; ++i) {
        bloom_check(&bloom, &i, sizeof(int));
    }
    gettimeofday(&t1, NULL);
    printf("Queried %d elements in %.5g seconds\n", i, t1.tv_sec - t0.tv_sec + 1E-6 * (t1.tv_usec - t0.tv_usec));

    bloom_free(&bloom);

    return 0;
}
