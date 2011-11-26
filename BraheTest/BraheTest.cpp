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
    not be appropriate or desirable. In such cases, contact the Itzam copyright holder to
    arrange your purchase of an appropriate license.

    The author can be contacted at:

          scott.ladd@coyotegulch.com
          scott.ladd@gmail.com
          http:www.coyotegulch.com
*/

#include "stdafx.h"
#include "../src/mathtools.h"
#include "../src/prng.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fft_test()
{
    brahe_wave_factor_t factors [] =
    {
        {  100.0, 20.0 },
        {   50.0, 40.0 },
        {    5.0, 100.0 }
    };

    // banner
    printf("\n<<<<------------------>>>>\n");
    printf("<<<<---- FFT Test ---->>>>\n");
    printf("<<<<------------------>>>>\n");

    // generate a sinusoid
    printf("generating sinusoid...\n");
    double * signal = brahe_make_sinusoid(factors, 3, 1024);

    // perform an fft on the sinusoid
    printf("computing FFT...\n");
    double * fft = brahe_simple_fft(signal, 1024);

    // see if the fft has peaks in the right places
    // these indexes will be WRONG if the length of the signal changes!
    if ((fft[  0] <  1.0)
    &&  (fft[  5] > 20.0)
    &&  (fft[  8] <  4.0)
    &&  (fft[ 10] > 36.0)
    &&  (fft[ 42] <  0.6)
    &&  (fft[102] > 75.0)
    &&  (fft[511] <  0.3))
        printf("Good data... success!\n");
    else
        printf("FFT produced wrong data -- ERROR\n");

    // cleanup
    free(fft);
    free(signal);
}

void pretty_test()
{
    int64_t x[] = { 0, -1, 2, 11, 500, 97, -10263, 1768372193, 0xA1B2C3D4E5F6, 1223372036854775808 };
    char * c;
    char * t;

    // banner
    printf("\n<<<<------------------------->>>>\n");
    printf("<<<<---- Pretty Integers ---->>>>\n");
    printf("<<<<------------------------->>>>\n");

    for (int i = 0; i < 10; ++i)
    {
        c = brahe_pretty_int(x[i], BRAHE_PRETTY_COMMA);
        t = brahe_pretty_int(x[i], BRAHE_PRETTY_TEXT);

        printf("\n%ld\n%s\n%s\n",x[i], c, t);

        free(t);
        free(c);
    }
}

void trig_test()
{
    int i;
    double a [] = { 1.0, 1.33333333333333333, 1.5 };

    // banner
    printf("\n<<<<-------------------->>>>\n");
    printf("<<<<---- Extra Trig ---->>>>\n");
    printf("<<<<-------------------->>>>\n");

    for (i = 0; i < 3; ++i)
    {
        printf("atanh(tanh(%11.8f)) = %11.8f\n",  a[i], brahe_atanh(tanh(a[i])));
        printf("atanh(tanh(%11.8f)) = %11.8f\n", -a[i], brahe_atanh(tanh(-a[i])));
        printf("asinh(sinh(%11.8f)) = %11.8f\n",  a[i], brahe_asinh(sinh(a[i])));
        printf("asinh(sinh(%11.8f)) = %11.8f\n", -a[i], brahe_asinh(sinh(-a[i])));
        printf("acosh(cosh(%11.8f)) = %11.8f\n",  a[i], brahe_acosh(cosh(a[i])));
        printf("acosh(cosh(%11.8f)) = %11.8f\n", -a[i], brahe_acosh(cosh(-a[i])));
    }
}

void lcm_test()
{
    // test data
    static const size_t TEST_SIZE = 7;

    static const uint64_t test_set1[] =
    {
        0, 1, 4, 25, 72,  36, 12
    };

    static const uint64_t test_set2[] =
    {
        0, 4, 6, 30, 90, 125, 15
    };

    static const uint64_t expected[] =
    {
        0, 4, 12, 150, 360, 4500, 60
    };

    // counts errors
    size_t i, errcnt = 0;
    uint64_t result;

    // banner
    printf("\n<<<<------------------------------->>>>\n");
    printf("<<<<---- Least Common Multiple ---->>>>\n");
    printf("<<<<------------------------------->>>>\n");

    for (i = 0; i < TEST_SIZE; ++i)
    {
        result = brahe_lcm(test_set1[i],test_set2[i]);

        printf("lcm(%lu,%lu) = %lu (should be %lu)\n",
                (unsigned long)test_set1[i],
                (unsigned long)test_set2[i],
                (unsigned long)result,
                (unsigned long)expected[i]);

        if (result != expected[i])
            ++errcnt;
    }
}

void gcf_test()
{
    // test data
    static const size_t TEST_SIZE = 6;

    static const uint64_t test_set1[] =
    {
        0, 1, 156, 24, 28, 644
    };

    static const uint64_t test_set2[] =
    {
        0, 4, 112, 36, 35, 805
    };

    static const uint64_t expected[] =
    {
        0, 1, 4, 12, 7, 161
    };

    // counts errors
    size_t i, errcnt = 0;
    uint64_t result;

    // banner
    printf("\n<<<<-------------------------------->>>>\n");
    printf("<<<<---- Greatest Common Fcator ---->>>>\n");
    printf("<<<<-------------------------------->>>>\n");

    for (i = 0; i < TEST_SIZE; ++i)
    {
        result = brahe_gcf(test_set1[i],test_set2[i]);

        printf("gcf(%lu,%lu) = %lu (should be %lu)\n",
                (unsigned long)test_set1[i],
                (unsigned long)test_set2[i],
                (unsigned long)result,
                (unsigned long)expected[i]);

        if (result != expected[i])
            ++errcnt;
    }
}

#define PRNG_TEST_SIZE 100000000
#define NUM_BUCKETS 13

double test_prng(brahe_prng_type_t prng_type)
{
    uint32_t total, dummy;
    size_t i;
    double n, l, s;
    int counts[NUM_BUCKETS];
    brahe_prng_state_t prng_state;
    clock_t start, stop;

    // banner
    printf("\n<<<<------------------------>>>>\n");
    printf("<<<<---- Random Numbers ---->>>>\n");
    printf("<<<<------------------------>>>>\n");

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

    for (i = 0; i < PRNG_TEST_SIZE; ++i)
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

    for (i = 0; i < PRNG_TEST_SIZE; ++i)
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

    for (i = 0; i < PRNG_TEST_SIZE; ++i)
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

    for (i = 0; i < PRNG_TEST_SIZE; ++i)
    {
        n = brahe_prng_real53(&prng_state);

        if (n < s) s = n;
        if (n > l) l = n;
    }

    printf("    largest = %15.14f\n   smallest = %15.14f\n", l, s);

    //  check ranges
    for (i = 0; i < NUM_BUCKETS; ++i)
        counts[i] = 0;

    for (i = 0; i < PRNG_TEST_SIZE; ++i)
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
    start = clock();

    // test generation speed
    for (i = 0; i < PRNG_TEST_SIZE; ++i)
        dummy = brahe_prng_next(&prng_state);

    // calculate run time
    stop = clock();

    // free resources
    brahe_prng_free(&prng_state);

    // done
    return (double)(stop - start) / (double)CLOCKS_PER_SEC;
}

int _tmain(int argc, _TCHAR* argv[])
{
    fft_test();
    pretty_test();
    trig_test();
    lcm_test();
    gcf_test();

    double mtwister_time = test_prng(BRAHE_PRNG_MARSENNE_TWISTER);
    double kissrng_time  = test_prng(BRAHE_PRNG_KISS);
    double mwc1038_time  = test_prng(BRAHE_PRNG_MWC1038);
    double cmwc4096_time = test_prng(BRAHE_PRNG_CMWC4096);
    double isaac_time    = test_prng(BRAHE_PRNG_ISAAC);

    printf("\nALGORITHM TIMING (random numbers / second)\n\n");
    printf("  Marsenne Twister = %5.2f (%10.0f/sec)\n", mtwister_time, ((double)PRNG_TEST_SIZE / mtwister_time));
    printf("              KISS = %5.2f (%10.0f/sec)\n", kissrng_time,  ((double)PRNG_TEST_SIZE / kissrng_time));
    printf("           MWC1038 = %5.2f (%10.0f/sec)\n", mwc1038_time,  ((double)PRNG_TEST_SIZE / mwc1038_time));
    printf("          CMWC4096 = %5.2f (%10.0f/sec)\n", cmwc4096_time, ((double)PRNG_TEST_SIZE / cmwc4096_time));
    printf("             ISAAC = %5.2f (%10.0f/sec)\n", isaac_time,    ((double)PRNG_TEST_SIZE / isaac_time));

	return 0;
}
