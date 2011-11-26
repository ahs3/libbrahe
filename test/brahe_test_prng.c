/*
    Brahe is a heterogenous collection of mathematical tools,  written in Standard C.

    Copyright 2011 Scott Robert Ladd. All rights reserved.

    Brahe is user-supported open source software. Its continued development is dependent
    on financial support from the community. You can provide funding by visiting the Brahe
    website at:

        http://www.coyotegulch.com

    You may license Brahe in one of two fashions:

    1) Simplified BSD License (FreeBSD License)

    Redistribution and use in source and binary forms, with or without modification, are
    permitted provided that the following conditions are met:

    1.  Redistributions of source code must retain the above copyright notice, this list of
        conditions and the following disclaimer.

    2.  Redistributions in binary form must reproduce the above copyright notice, this list
        of conditions and the following disclaimer in the documentation and/or other materials
        provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY SCOTT ROBERT LADD ``AS IS'' AND ANY EXPRESS OR IMPLIED
    WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
    FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SCOTT ROBERT LADD OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
    ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
    ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    The views and conclusions contained in the software and documentation are those of the
    authors and should not be interpreted as representing official policies, either expressed
    or implied, of Scott Robert Ladd.

    2) Closed-Source Proprietary License

    If your project is a closed-source or proprietary project, the Simplified BSD License may
    not be appropriate or desirable. In such cases, contact the Brahe copyright holder to
    arrange your purchase of an appropriate license.

    The author can be contacted at:

          scott.ladd@coyotegulch.com
          scott.ladd@gmail.com
          http:www.coyotegulch.com
*/

#include "../src/prng.h"

#include <stdio.h>
#include <time.h>

static const size_t TEST_SIZE = 100000000;
static const size_t NUM_BUCKETS = 13;

double test_prng(brahe_prng_type_t prng_type)
{
    uint32_t total, dummy;
    size_t i;
    double n, l, s;
    int counts[NUM_BUCKETS];
    brahe_prng_state_t prng_state;

    struct timespec start, stop;

    switch (prng_type)
    {
        case BRAHE_PRNG_MARSENNE_TWISTER:
            printf("\n>>>> MARSENNE TWISTER <<<<\n");
            break;

        case BRAHE_PRNG_KISS:
            printf("\n>>>> KISS <<<<\n");
            break;

        case BRAHE_PRNG_MWC1038:
            printf("\n>>>> MWC1038 <<<<\n");
            break;

        case BRAHE_PRNG_CMWC4096:
            printf("\n>>>> CMWC4096 <<<<\n");
            break;

        case BRAHE_PRNG_ISAAC:
            printf("\n>>>> ISAAC <<<<\n");
            break;
    }

   // create the generator
    brahe_prng_init(&prng_state,prng_type,BRAHE_UNKNOWN_SEED);

    //  each real function
    printf("\nrand_real1 - interval [0,1]\n");

    s = 1.1;
    l = -0.1;

    for (i = 0; i < TEST_SIZE; ++i)
    {
        n = brahe_prng_real1(&prng_state);

        if (n < s) s = n;
        if (n > l) l = n;
    }

    printf("    largest = %15.14f\n   smallest = %15.14f\n", l, s);

    //  each real function
    printf("\nrand_real2 - interval [0,1)\n");

    s = 1.1;
    l = -0.1;

    for (i = 0; i < TEST_SIZE; ++i)
    {
        n = brahe_prng_real2(&prng_state);

        if (n < s) s = n;
        if (n > l) l = n;
    }

    printf("    largest = %15.14f\n   smallest = %15.14f\n", l, s);

    //  each real function
    printf("\nrand_real3 - interval (0,1)\n");

    s = 1.1;
    l = -0.1;

    for (i = 0; i < TEST_SIZE; ++i)
    {
        n = brahe_prng_real3(&prng_state);

        if (n < s) s = n;
        if (n > l) l = n;
    }

    printf("    largest = %15.14f\n   smallest = %15.14f\n", l, s);

    //  each real function
    printf("\nrand_real53 - interval [0,1) - 53-bit precision\n");

    s = 1.1;
    l = -0.1;

    for (i = 0; i < TEST_SIZE; ++i)
    {
        n = brahe_prng_real53(&prng_state);

        if (n < s) s = n;
        if (n > l) l = n;
    }

    printf("    largest = %15.14f\n   smallest = %15.14f\n", l, s);

    //  check ranges
    for (i = 0; i < NUM_BUCKETS; ++i)
        counts[i] = 0;

    for (i = 0; i < TEST_SIZE; ++i)
        ++counts[brahe_prng_index(&prng_state,NUM_BUCKETS)];

    printf("\n");

    total = 0;

    for (i = 0; i < NUM_BUCKETS; ++i)
    {
        printf("counts %3d  = %10d\n", i, counts[i]);
        total += counts[i];
    }

    printf("      total = %10d\n", total);

    // get starting time
    clock_gettime(CLOCK_REALTIME,&start);

    // test generation speed
    for (i = 0; i < TEST_SIZE; ++i)
        dummy = brahe_prng_next(&prng_state);

    // calculate run time
    clock_gettime(CLOCK_REALTIME,&stop);

    // free resources
    brahe_prng_free(&prng_state);

    // done
    return ((stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / 1000000000.0);
}

int main()
{
    double mtwister_time = test_prng(BRAHE_PRNG_MARSENNE_TWISTER);
    double kissrng_time  = test_prng(BRAHE_PRNG_KISS);
    double mwc1038_time  = test_prng(BRAHE_PRNG_MWC1038);
    double cmwc4096_time = test_prng(BRAHE_PRNG_CMWC4096);
    double isaac_time    = test_prng(BRAHE_PRNG_ISAAC);

    printf("\nALGORITHM TIMING (random numbers / second)\n\n");
    printf("  Marsenne Twister = %5.2f (%10.0f/sec)\n", mtwister_time, ((double)TEST_SIZE / mtwister_time));
    printf("              KISS = %5.2f (%10.0f/sec)\n", kissrng_time,  ((double)TEST_SIZE / kissrng_time));
    printf("           MWC1038 = %5.2f (%10.0f/sec)\n", mwc1038_time,  ((double)TEST_SIZE / mwc1038_time));
    printf("          CMWC4096 = %5.2f (%10.0f/sec)\n", cmwc4096_time, ((double)TEST_SIZE / cmwc4096_time));
    printf("             ISAAC = %5.2f (%10.0f/sec)\n", isaac_time,    ((double)TEST_SIZE / isaac_time));

    return 0;
}

