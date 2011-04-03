//  ---------------------------------------------------------------------
//  This file is part of Brahe, a heterogenous library of mathematical
//  and scientific functions written in C.
//
//  Brahe may be licensed either under the GNU General Public License v3
//  or a closed license from the author. See below for more information.
//
//  brahe_test_prng.c
//
//  Greatest Common Factor and Least Common Multiple
//
//  Copyright 2006, 2007, 2009 Scott Robert Ladd
//  ---------------------------------------------------------------------
//
//  Brahe is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  ---------------------------------------------------------------------
//  Closed-source licenses are available from the author at reasonable
//  prices.
//  ---------------------------------------------------------------------
//  
//  For more information on this software package, please visit
//  Scott's web site, Coyote Gulch Productions, at:
//
//      http://www.coyotegulch.com

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
#if defined(_MSC_VER)
    int counts[13];
#else
    int counts[NUM_BUCKETS];
#endif
    brahe_prng_state_t prng_state;

#if defined(_MSC_VER)
    clock_t start, stop;
#else
    struct timespec start, stop;
#endif

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
#if defined(_MSC_VER)
    start = clock();
#else
    clock_gettime(CLOCK_REALTIME,&start);
#endif

    // test generation speed
    for (i = 0; i < TEST_SIZE; ++i)
        dummy = brahe_prng_next(&prng_state);

    // calculate run time
#if defined(_MSC_VER)
    stop = clock();
#else
    clock_gettime(CLOCK_REALTIME,&stop);
#endif

    printf("start = %d, stop = %d\n",start,stop);

    // free resources
    brahe_prng_free(&prng_state);

    // done
#if defined(_MSC_VER)
    return (double)(stop - start) / (double)CLOCKS_PER_SEC;
#else
    return ((stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / 1000000000.0);
#endif
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

