//  ---------------------------------------------------------------------
//  This file is part of Brahe, a heterogenous library of mathematical
//  and scientific functions written in C.
//
//  Brahe may be licensed either under the GNU General Public License v3
//  or a closed license from the author. See below for more information.
//
//  prng.c
//
//  Psuedorandom number generators
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

#include "prng.h"

#if !defined(_MSC_VER)
#include <unistd.h>
#include <fcntl.h>
#endif

#include <time.h>
#include <stdlib.h>

/*
    ORIGINAL ALGORITHM COPYRIGHT

    Copyright (C) 1997, 2002 Makoto Matsumoto and Takuji Nishimura.
    Any feedback is very welcome. For any question, comments, see
    http://www.math.keio.ac.jp/matumoto/emt.html or email
    matumoto@math.keio.ac.jp

    Much as this algorithm is popular, I find it slower than Marsaglia's
    multiply-with-carry generators (implemented below). Still, this is
    an excellent generator that provide a good alternative when testing
    with multiple PRNGs.
*/
static bool mtwister_init(brahe_prng_state_t * prng_state)
{
    static const size_t N = 624;
    bool result = false;

    if (prng_state != NULL)
    {
        // allocate space for values
        prng_state->m_data1 = malloc(sizeof(uint32_t) * N);

        if (prng_state->m_data1 != NULL)
        {
            // convenience pointer
            uint32_t * m = (uint32_t *)prng_state->m_data1;

            // Save seed for historical purpose
            m[0] = prng_state->m_seed;

            // Set the seed using values suggested by Matsumoto & Nishimura, using
            //   a generator by Knuth. See reference source for details.
            for (prng_state->m_i = 1; prng_state->m_i < N; ++prng_state->m_i)
                m[prng_state->m_i] = 1812433253UL * (m[prng_state->m_i - 1] ^ (m[prng_state->m_i - 1] >> 30)) + prng_state->m_i;

            result = true;
        }
    }

    return result;
}

static uint32_t mtwister_next(brahe_prng_state_t * prng_state)
{
    // Period parameters
    static const size_t N = 624;
    static const size_t M = 397;
    static const uint32_t UPPER_MASK = 0x80000000UL;
    static const uint32_t LOWER_MASK = 0x7fffffffUL;

    // what we compute
    uint32_t result = 0;

    // variable names match those in original example
    const uint32_t mag01[2] = { 0, 0x9908b0dfUL };
    size_t   kk;

    if ((prng_state != NULL) && (prng_state->m_data1 != NULL))
    {
        // convenience pointer
        uint32_t * m = (uint32_t *)prng_state->m_data1;

        // Generate N words at a time
        if (prng_state->m_i >= N)
        {
            for (kk=0; kk < N-M; kk++)
            {
                result = (m[kk] & UPPER_MASK) | (m[kk+1] & LOWER_MASK);
                m[kk] = m[kk + M] ^ (result >> 1) ^ mag01[result & 0x1];
            }

            for ( ; kk < N-1; kk++)
            {
                result = (m[kk] & UPPER_MASK) | (m[kk+1] & LOWER_MASK);
                m[kk] = m[kk+(M-N)] ^ (result >> 1) ^ mag01[result & 0x1];
            }

            result = (m[N-1] & UPPER_MASK) | (m[0]&LOWER_MASK);
            m[N-1] = m[M-1] ^ (result >> 1) ^ mag01[result & 0x1];

            prng_state->m_i = 0;
        }

        // Here is where we actually calculate the number with a series of transformations 
        result = m[prng_state->m_i++];

        result ^= (result >> 11);
        result ^= (result <<  7) & 0x9d2c5680UL;
        result ^= (result << 15) & 0xefc60000UL;
        result ^= (result >> 18);
    }

    return result;
}

/*
    The popular "Keep It Simple Stupid" psuedorandom number generator.
    It has a period of around 2^125, which is shorter than most other
    algorithms, but certainly adequate for many applications.

    http://groups.google.com/group/comp.soft-sys.math.mathematica/msg/95a94c3b2aa5f077
*/
static bool kiss_init(brahe_prng_state_t * prng_state)
{
    bool result = false;

    // Use Knuth's algorithms to set initial values from seed
    static const uint32_t K = 1812433253UL;

    if (prng_state != NULL)
    {
        // allocate space for values
        prng_state->m_data1 = malloc(sizeof(uint32_t) * 4);

        if (prng_state->m_data1 != NULL)
        {
            uint32_t * m = (uint32_t *)prng_state->m_data1;

            m[0] = K * (prng_state->m_seed ^ (prng_state->m_seed >> 30)) + 1;
            m[1] = K * (m[0] ^ (m[0] >> 30)) + 2;
            m[2] = K * (m[1] ^ (m[1] >> 30)) + 3;
            m[3] = K * (m[2] ^ (m[2] >> 30)) + 5;
            result = true;
        }
    }

    return result;
}

static uint32_t kiss_next(brahe_prng_state_t * prng_state)
{
    uint32_t result = 0;

    static const uint64_t A = 698769069ULL;
    uint64_t temp;

    if ((prng_state != NULL) && (prng_state->m_data1 != NULL))
    {
        uint32_t * m = (uint32_t *)prng_state->m_data1;

        m[1] = 69069 * m[1] + 12345;
        m[2] ^= ( m[2] << 13);
        m[2] ^= ( m[2] >> 17);
        m[2] ^= ( m[2] <<  5);

        temp = A * m[3] + m[0];
        m[0] = (temp >> 32);

        result = m[1] + m[2] + (m[3] = temp);
    }

    return result;
}

//  A common initialization function for all multiply-with-carry
//  generators.
static bool mwc_init(brahe_prng_state_t * prng_state, const size_t N)
{
    size_t i;
    bool result = false;

    if (prng_state != NULL)
    {
        // allocate space for values
        prng_state->m_data1 = malloc(sizeof(uint32_t) * N);

        if (prng_state->m_data1 != NULL)
        {
            // convenience pointer
            uint32_t * m = (uint32_t *)prng_state->m_data1;

            // Save seed for historical purpose
            m[0] = prng_state->m_seed;

            // Set the array using one of Knuth's generators
            for (i = 1; i < N; ++i)
                m[i] = 1812433253UL * (m[i - 1] ^ (m[i - 1] >> 30)) + i;

            prng_state->m_c = m[N-1] % 61137367UL;
            prng_state->m_i = N - 1;

            result = true;
        }
    }

    return result;
}

/*
    The mwc1038 functions implement a multiply-with-carry algorithm
    for psuedorandom number generation, as suggested by George
    Marsaglia in a posting found here:

    http://forums.wolfram.com/mathgroup/archive/2003/Jan/msg00355.html

    Marsaglia states that this algorithm has a "period 3056868392^33216-1,
    a mere 10^4005 times as long as that of the Mersenne twister, yet faster,
    far simpler, and seemingly at least as well-performing in tests
    of randomness."

    This is often my first choice, since it runs faster than the Marsenne
    Twister on 32- and 64-bit systems -- three times fastre on 32-bit
    Windows. On a 64-bit system, CMWC4096 is marginally faster.
*/
static uint32_t mwc1038_next(brahe_prng_state_t * prng_state)
{
    static const size_t   N = 1038;
    static const uint64_t A = 611373678ULL;

    uint64_t temp;
    uint32_t result = 0;

    if ((prng_state != NULL) && (prng_state->m_data1 != NULL))
    {
        // convenience pointer
        uint32_t * m  = (uint32_t *)prng_state->m_data1;

        // get next number in sequence
        temp = A * m[prng_state->m_i]+ prng_state->m_c;

        prng_state->m_c = (temp >> 32);

        if(--prng_state->m_i)
            result = m[prng_state->m_i] = temp;
        else
        {
            prng_state->m_i = N - 1;
            result  = m[0] = temp;
        }
    }

    return result;
}

/*
    The cmwc4096 functions implement a complimentary-multiply-with-carry
    algorithm for psuedorandom number generation, as suggested by George
    Marsaglia. CMWC4096 has a period of 2^131086, and Marsaglia's
    introuction of it can be found here:

    http://groups.google.com/group/comp.soft-sys.math.mathematica/msg/95a94c3b2aa5f077
*/
static uint32_t cmwc4096_next(brahe_prng_state_t * prng_state)
{
    static const uint64_t A = 18782ULL;
    static const uint32_t R = 0xfffffffeUL;

    uint64_t temp;
    uint32_t x;
    uint32_t result = 0;

    if ((prng_state != NULL) && (prng_state->m_data1 != NULL))
    {
        // convenience pointer
        uint32_t * m  = (uint32_t *)prng_state->m_data1;

        // get next number in sequence
        prng_state->m_i = (prng_state->m_i + 1) & 4095;
        temp = A * m[prng_state->m_i] + prng_state->m_c;
        prng_state->m_c = (temp >> 32);
        x = temp + prng_state->m_c;

        if(x < prng_state->m_c)
        {
            ++x;
            ++prng_state->m_c;
        }

        result = m[prng_state->m_i] = R - x;
    }

    return result;
}

/*
    ISAAC (Indirect, Shift, Accumulate, Add, and Count) is a fast
    cryptographic random number generator created by Bob Jenkins.
    It is cryptographically secure, unlike the other algorithms
    presented here. You can learn more at:

    http://burtleburtle.net/bob/rand/isaacafa.html
*/

static void isaac_next_batch(brahe_prng_state_t * prng_state)
{
    int i;
    uint32_t x, y;

    uint32_t * data1  = (uint32_t *)prng_state->m_data1;
    uint32_t * data2  = (uint32_t *)prng_state->m_data2;

    prng_state->m_c++;
    prng_state->m_b += prng_state->m_c;
    prng_state->m_i = 0;

    for (i = 0; i < 256; ++i)
    {
        x = data2[i];

        switch (i % 4)
        {
            case 0: prng_state->m_a ^= (prng_state->m_a << 13); break;
            case 1: prng_state->m_a ^= (prng_state->m_a >>  6); break;
            case 2: prng_state->m_a ^= (prng_state->m_a <<  2); break;
            case 3: prng_state->m_a ^= (prng_state->m_a >> 16); break;
        }

        prng_state->m_a = data2[(i + 128) % 256] + prng_state->m_a;
        y = data2[(x >> 2) % 256] + prng_state->m_a + prng_state->m_b;
        data2[i] = y;
        prng_state->m_b = data2[(y >> 10) % 256] + x;
        data1[i] = prng_state->m_b;
    }
}


#define isaac_mix(a,b,c,d,e,f,g,h) \
{ \
   a^=b<<11; d+=a; b+=c; \
   b^=c>>2;  e+=b; c+=d; \
   c^=d<<8;  f+=c; d+=e; \
   d^=e>>16; g+=d; e+=f; \
   e^=f<<10; h+=e; f+=g; \
   f^=g>>4;  a+=f; g+=h; \
   g^=h<<8;  b+=g; h+=a; \
   h^=a>>9;  c+=h; a+=b; \
}

static bool isaac_init(brahe_prng_state_t * prng_state)
{
    bool result = false;

    uint32_t a, b, c, d, e, f, g, h;
    int i;

    uint32_t * data1  = NULL;
    uint32_t * data2  = NULL;

    if (prng_state != NULL)
    {
        prng_state->m_a = 0;
        prng_state->m_b = 0;
        prng_state->m_c = 0;
        prng_state->m_i = 0;
            
        prng_state->m_data1 = malloc(sizeof(uint32_t) * 256);

        if (prng_state->m_data1 != NULL)
        {
            prng_state->m_data2 = malloc(sizeof(uint32_t) * 256);

            if (prng_state->m_data2 != NULL)
            {
                data1 = (uint32_t *)prng_state->m_data1;
                data2 = (uint32_t *)prng_state->m_data2;

                for (i = 0; i < 256; ++i)
                {
                    data1[i] = 0;
                    data2[i] = 0;
                }

                // with everything initialized, use the seed
                a = b = c = d = e = f = g = h = prng_state->m_seed;

                for (i = 0; i < 4; ++i)
                    isaac_mix(a,b,c,d,e,f,g,h);

                for (i = 0;  i < 256; i += 8)
                {
                    a += data1[i];
                    b += data1[i + 1];
                    c += data1[i + 2];
                    d += data1[i + 3];
                    e += data1[i + 4];
                    f += data1[i + 5];
                    g += data1[i + 6];
                    h += data1[i + 7];

                    isaac_mix(a,b,c,d,e,f,g,h);

                    data2[i]     = a;
                    data2[i + 1] = b;
                    data2[i + 2] = c;
                    data2[i + 3] = d;
                    data2[i + 4] = e;
                    data2[i + 5] = f;
                    data2[i + 6] = g;
                    data2[i + 7] = h;
                }

                for (i = 0;  i < 256; i += 8)
                {
                    a += data2[i];
                    b += data2[i + 1];
                    c += data2[i + 2];
                    d += data2[i + 3];
                    e += data2[i + 4];
                    f += data2[i + 5];
                    g += data2[i + 6];
                    h += data2[i + 7];

                    isaac_mix(a,b,c,d,e,f,g,h);

                    data2[i]     = a;
                    data2[i + 1] = b;
                    data2[i + 2] = c;
                    data2[i + 3] = d;
                    data2[i + 4] = e;
                    data2[i + 5] = f;
                    data2[i + 6] = g;
                    data2[i + 7] = h;
                }

                isaac_next_batch(prng_state);
            }
        }
    }

    return result;
}

static uint32_t isaac_next(brahe_prng_state_t * prng_state)
{
    uint32_t result = 0;

    uint32_t * data1 = (uint32_t *)prng_state->m_data1;

    if (prng_state != NULL)
    {
        result = data1[prng_state->m_i];

        if (prng_state->m_i < 255)
            ++prng_state->m_i;
        else
            isaac_next_batch(prng_state);
    }

    return result;
}

/*
    Generic functions used by all of the generators implemented above.
*/

// Initialize a psuedo-random number generator
bool brahe_prng_init(brahe_prng_state_t * prng_state, const brahe_prng_type_t type, const uint32_t seed)
{
    bool result = false;

    // set the seed
    if (prng_state != NULL)
    {
        if (seed > 0)
            prng_state->m_seed = seed;
        else
        {
#if defined(_MSC_VER)
            prng_state->m_seed = (uint32_t)time(NULL);
#else
            // first try to read /dev/urandom
            int fd = open("/dev/urandom", O_RDONLY);

            if (fd != -1)
            {
                uint32_t s = 0;
                
                int n = read(fd, &s, 4);
                close(fd);
                
                if (n != sizeof(uint32_t))
                    prng_state->m_seed = s;
            }
#endif
        }

        // initialize based on type
        prng_state->m_type = type;
        prng_state->m_data1 = NULL;
        prng_state->m_data2 = NULL;

        switch (prng_state->m_type)
        {
            case BRAHE_PRNG_MARSENNE_TWISTER:
                result = mtwister_init(prng_state);
                break;

            case BRAHE_PRNG_KISS:
                result = kiss_init(prng_state);
                break;

            case BRAHE_PRNG_MWC1038:
                result = mwc_init(prng_state,1038);
                break;

            case BRAHE_PRNG_CMWC4096:
                result = mwc_init(prng_state,4096);
                break;

            case BRAHE_PRNG_ISAAC:
                result = isaac_init(prng_state);
                break;
        }
    }

    return result;
}

// free resources
void brahe_prng_free(brahe_prng_state_t * prng_state)
{
    if (prng_state != NULL)
    {
        if (prng_state->m_data1 != NULL)
            free(prng_state->m_data1);

        if (prng_state->m_data2 != NULL)
            free(prng_state->m_data2);
    }
}

// Get the next integer
uint32_t brahe_prng_next(brahe_prng_state_t * prng_state)
{
    uint32_t result = 0;

    if ((prng_state != NULL) && (prng_state->m_data1 != NULL))
    {
        switch (prng_state->m_type)
        {
            case BRAHE_PRNG_MARSENNE_TWISTER:
                result = mtwister_next(prng_state);
                break;

            case BRAHE_PRNG_KISS:
                result = kiss_next(prng_state);
                break;

            case BRAHE_PRNG_MWC1038:
                result = mwc1038_next(prng_state);
                break;

            case BRAHE_PRNG_CMWC4096:
                result = cmwc4096_next(prng_state);
                break;

            case BRAHE_PRNG_ISAAC:
                result = isaac_next(prng_state);
                break;
        }
    }

    return result;
}

// Get the next integer in the range [lo,hi]
uint32_t brahe_prng_range(brahe_prng_state_t * prng_state, const uint32_t lo, const uint32_t hi)
{
    double range = hi - lo + 1.0;
    return lo + (uint32_t)(floor(range * brahe_prng_real2(prng_state)));
}

// Get the next random value as a size_t index
size_t brahe_prng_index(brahe_prng_state_t * prng_state, size_t length)
{
    return (size_t)((double)length * brahe_prng_real2(prng_state));
}

// Get the next number in the range [0,1]
double brahe_prng_real1(brahe_prng_state_t * prng_state)
{
    // privides a granularity of approx. 2.3E-10
    return (double)(brahe_prng_next(prng_state)) * (1.0 / 4294967295.0);
}

// Get the next number in the range [0,1)
double brahe_prng_real2(brahe_prng_state_t * prng_state)
{
    // privides a granularity of approx. 2.3E-10
    return (double)(brahe_prng_next(prng_state)) * (1.0 / 4294967296.0);
}

// Get the next number in the range (0,1)
double brahe_prng_real3(brahe_prng_state_t * prng_state)
{
    // privides a granularity of approx. 2.3E-10
    return (double)(((double)brahe_prng_next(prng_state) + 0.5) * (1.0 / 4294967296.0));
}

// Get the next number in the range [0,1), with 53-bit precision
double brahe_prng_real53(brahe_prng_state_t * prng_state)
{
    // privides a granularity of approx. 1.1E-16
    uint32_t a = brahe_prng_next(prng_state) >> 5;
    uint32_t b = brahe_prng_next(prng_state) >> 6;
    return (double)(a * 67108864.0 + b) * (1.0 / 9007199254740992.0);
}
