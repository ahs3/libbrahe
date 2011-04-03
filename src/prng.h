//  ---------------------------------------------------------------------
//  This file is part of Brahe, a heterogenous library of mathematical
//  and scientific functions written in C.
//
//  Brahe may be licensed either under the GNU General Public License v3
//  or a closed license from the author. See below for more information.
//
//  prng.h
//
//  Psuedorandom number generator definitions.
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

#if !defined(LIBBRAHE_PRNG_H)
#define LIBBRAHE_PRNG_H

#include "mathtools.h"

#if defined(__cplusplus)
extern "C" {
#endif

//! Defines types of prngs
typedef enum
{
    BRAHE_PRNG_MARSENNE_TWISTER = 0, //! Marsenne Twister (Matsumoto & Nishimura)
    BRAHE_PRNG_KISS,                 //! Keep is Simple, Stupid (Marsaglia)
    BRAHE_PRNG_CMWC4096,             //! CMWC4096 (Marsaglia)
    BRAHE_PRNG_MWC1038,              //! MWC1038 (Marsaglia)
    BRAHE_PRNG_ISAAC                 //! Indirect, Shift, Accumulate, Add, and Count (Jenkins)
} brahe_prng_type_t;

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
