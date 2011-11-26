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

#if !defined(LIBBRAHE_PRNG_H)
#define LIBBRAHE_PRNG_H

#include "mathtools.h"

#if defined(__cplusplus)
extern "C" {
#endif

//! Defines types of prngs
typedef enum
{
    //! Marsenne Twister (Matsumoto & Nishimura)
    BRAHE_PRNG_MARSENNE_TWISTER = 0,
    //! Keep is Simple, Stupid (Marsaglia)
    BRAHE_PRNG_KISS,
    //! CMWC4096 (Marsaglia)
    BRAHE_PRNG_CMWC4096,
    //! MWC1038 (Marsaglia)
    BRAHE_PRNG_MWC1038,
    //! Indirect, Shift, Accumulate, Add, and Count (Jenkins)
    BRAHE_PRNG_ISAAC
} brahe_prng_type_t;

//! Contains state variables for a PRNG
typedef struct
{
    brahe_prng_type_t m_type;  // the algorithm we're using
    uint32_t          m_seed;  // "seed" that defines the sequence
    void *            m_data1; // array or table
    void *	          m_data2; // additional array or table
    size_t            m_i;     // only used by some algorithms
    size_t            m_a;     // only used by some algorithms
    size_t            m_b;     // only used by some algorithms
    size_t            m_c;     // only used by some algorithms
} brahe_prng_state_t;

static uint32_t BRAHE_UNKNOWN_SEED = 0;

//! Initialize a psuedo-random number generator (PRNG)
/*!
    Initializes a psuedo-random number generator using a specified algorithm.
    \param prng_state Object to be initialized for a specific algorithm
    \param type Algorithm to be used for this PRNG
    \param seed Initialization seed
    \return <i>true</i> if successful, <i>false</i> if failed
*/
bool brahe_prng_init(brahe_prng_state_t * prng_state, const brahe_prng_type_t type, const uint32_t seed);

//! Free resources used by PRNG
/*!
    Frees the resources used by a PRNG
    \param prng_state Object containing the state of a PRNG
    \return <i>true</i> if successful, <i>false</i> if failed
*/
void brahe_prng_free(brahe_prng_state_t * prng_state);

//!  Get the next integer
/*!
    Returns the next uint32_t in sequence.
    \param prng_state Object containing the state of a PRNG
    \return A pseudorandom uint32_t value
*/
uint32_t brahe_prng_next(brahe_prng_state_t * prng_state);

//! Get the next integer in the range [lo,hi]
/*!
    Returns the next int_value between lo and hi, inclusive.
    \param prng_state Object containing the state of a PRNG
    \param lo - Minimum value of result
    \param hi - Maximum value of result
    \return A pseudorandom uint32_t value
*/
uint32_t brahe_prng_range(brahe_prng_state_t * prng_state, const uint32_t lo, const uint32_t hi);

//! Get the next random value as a size_t index
/*!
    Returns the next value as a size_t "index" in the range [0,length).
    \param prng_state Object containing the state of a PRNG
    \param length - Maximum value of result
    \return A pseudorandom size_t value
*/
size_t brahe_prng_index(brahe_prng_state_t * prng_state, const size_t length);

//! Get the next number in the range [0,1]
/*!
    Returns the next real number in the range [0,1], i.e., a number
    greater than or equal to 0 and less than or equal to 1.
    Provides 32-bit precision.
    \param prng_state Object containing the state of a PRNG
    \return A pseudorandom double value
*/
double brahe_prng_real1(brahe_prng_state_t * prng_state);

//! Get the next number in the range [0,1)
/*!
    Returns the next real number in the range [0,1), i.e., a number
    greater than or equal to 0 and less than 1.
    Provides 32-bit precision.
    \param prng_state Object containing the state of a PRNG
    \return A pseudorandom double value
*/
double brahe_prng_real2(brahe_prng_state_t * prng_state);

//! Get the next number in the range (0,1)
/*!
    Returns the next real number in the range (0,1), i.e., a number
    greater than 0 and less than 1.
    Provides 32-bit precision.
    \param prng_state Object containing the state of a PRNG
    \return A pseudorandom double value
*/
double brahe_prng_real3(brahe_prng_state_t * prng_state);

//! Get the next number in the range [0,1)
/*!
    Returns the next real number in the range [0,1), i.e., a number
    greater than or equal to 0 and less than 1.
    Provides 53-bit precision.
    \param prng_state Object containing the state of a PRNG
    \return A pseudorandom double value
*/
double brahe_prng_real53(brahe_prng_state_t * prng_state);

#if defined(__cplusplus)
}
#endif

#endif
