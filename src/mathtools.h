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

#if !defined(LIBBRAHE_MATHTOOLS_H)
#define LIBBRAHE_MATHTOOLS_H

#include <stddef.h>
#include <math.h>
#include <limits.h>
#include <float.h>

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(_MSC_VER)
#pragma warning (disable: 4244 4267 4996)
#if !defined(__cplusplus)
typedef char bool;
static const int true  = 1;
static const int false = 0;
#endif
typedef unsigned __int64 uint64_t;
typedef __int64          int64_t;
typedef unsigned __int32 uint32_t;
typedef __int32          int32_t;
typedef unsigned __int16 uint16_t;
typedef __int16          int16_t;
typedef unsigned __int8  uint8_t;
typedef __int8           int8_t;
#else
// ISO C standard compilers
#include <stdbool.h>
#include <stdint.h>
#endif

//-----------------------------------------------------------------------------
// Rounding
//-----------------------------------------------------------------------------

//! Round to nearest value
/*!
    Rounds a value to nearest integer, rounding to even for exact fractions of 0.5.
*/
double brahe_round_nearest(const double x);

//! Set number of significant digits in a floating-point value
/*!
    Returns the given value rounded for the number of specified decimal
    digits of precision.
    \param x - Original value to be rounded
    \param n - Number of significant digits
    \return The value <i>x</i> rounded to <i>n</i> digits of precision
*/
double brahe_sigdig(const double x, const uint16_t n);

//-----------------------------------------------------------------------------
// Lowest Common Multple (LCM) and Lowest Common Denominator (GCD)
//-----------------------------------------------------------------------------

//! Lowest common multiple
/*!
    Calculates the lowest common multiple for two values.
    \param x first value
    \param y second value
    \return The lowest common multiple for <i>x</i> and <i>y</i>
*/
uint64_t brahe_lcm(const uint64_t x, const uint64_t y);

//! Greatest common factor (denominator)
/*!
    Calculates the greatest common factor for two values.
    \param x first value
    \param y second value
    \return The greatest common factor for <i>x</i> and <i>y</i>
*/
uint64_t brahe_gcf(uint64_t x, uint64_t y);

//-----------------------------------------------------------------------------
// Logarithms
//-----------------------------------------------------------------------------

//! Logarithm to a specified base
/*!
    Calculates the base-n logarithm for a given value. If a range
    error occurs, the return value equals NaN.
    \param x value for which logarithm is required
    \param base lagarithm base
    \return logarithm of <i>x</i> to base <i>base</i>; NAN on range error
*/
double brahe_log2base(const double x, const double base);

//! Smallest power of 2 that includes a given value
/*!
    Returns the smallest power of 2 that includes n in its range
    \param n number that must be less than the result
    \return the lowest power of 2 that is greater than <i>n</i>, or
*/
int brahe_sizepow2(const int n);

//-----------------------------------------------------------------------------
// Statistical functions
//-----------------------------------------------------------------------------

//! Formats for pretty-printing integers
typedef enum brahe_pretty_format_t
{
    //! english text (nine thousand, two hundred eleven)
    BRAHE_PRETTY_TEXT,
    //! comma delimited, (1,234,567,890)
    BRAHE_PRETTY_COMMA
}
brahe_pretty_format;

//! Turn a 64-bit integer into a pretty string
/*!
    Returns a nicely formatted strong for a given 64-bit integer.
    \param n number to be formatted
    \param fmt specifies format, as text or comma-delimited
    \return an allocated string containing the generated text
 */
char * brahe_pretty_int(int64_t n, brahe_pretty_format fmt);

//-----------------------------------------------------------------------------
// Statistical functions
//-----------------------------------------------------------------------------

//! Structure containing statistical values calculate from a double array
typedef struct brahe_statistics_t
{
    //! minimum value from array
    double min;
    //! maximum value
    double max;
    //! mean (average)
    double mean;
    //! variance
    double variance;
    //! standard deviation
    double sigma;
}
brahe_statistics;

//! statistics for array of double
/*!
    Calculate several common statistics for an array of doubles.
    \param data array of double values
    \param n number of elements in data
    \return statistics for data
 */
brahe_statistics brahe_get_statistics(double * data, size_t n);

//! Moving average
/*!
    Computes the moving average for an array. The returned buffer
    must be freed by the calling code.
    \param data array of double values to be averaged
    \param n number of elements in data
    \param distance number elements to average before and after an element in <i>data</i>
    \return an allocated <i>n</i>-length array containing the moving average of corresponding elements in <i>data</i>
*/
double * brahe_moving_average(const double * data, const int n, const int distance);

//-----------------------------------------------------------------------------
// Digital Signal Processing
//-----------------------------------------------------------------------------

//! Simple real-to-real fft (arbitrary length)
/*!
     A simple real-to-real FFT for arbitrary-length data. This is not intended
     to replace dedicated libraries such as FFTW. The caller is responsible
     for freeing the memory used by the array returned by this function.
     /param data input array
     /param n length of data
     /return an allocated array containing the real FFT of data
*/
double * brahe_simple_fft(const double * data, const int n);

//! Simple real-to-real fft (power of 2 length)
/*!
     A simple real-to-real FFT for power of 2-length data. This is not intended
     to replace dedicated libraries such as FFTW. The caller is responsible
     for freeing the memory used by the array returned by this function.
     /param data input array
     /param n length of data
     /return an allocated array containing the real FFT of data
*/
double * brahe_simple_fft2(const double * data, const int n);

//! Sine wave definition
/*!
     Defines the characteristics of a sine wave.
*/
typedef struct
{
    //! wavelength
    double wavelength;
    //! arbitrary wave amplitude
    double amplitude;
}
brahe_wave_factor_t;

//! Sine wave based artificial signal generator.
/*!
    Generates an array of doubles by combining sine waves. The primary
    purpose is to produce an artificial signal with known properties,
    for testing signal analysis applications. The caller is responsible
    for freeing the memory used by the array returned by this function.
    \param factors defines properties of the sine waves to be combined
    \param factor_n number of elements in factors
    \param array_n number of elements in the output array
    \return an allocated array containg values generated from the given factors
*/
double * brahe_make_sinusoid(const brahe_wave_factor_t * factors, const size_t factor_n, const size_t array_n);

//! Apply noise to a signal
/*!
    Adds a percentage of noise to a signal. If "noise" is set to 0.1 (for example)
    each value will be adjust to between 90% and 110% of its original value. This
    function changes the existing values in the array.
    \param a array containing signal data
    \param n number of samples in signal
    \param noise percentage of noise
*/
void brahe_add_noise(double * a, const size_t n, double noise);

//-----------------------------------------------------------------------------
// Trigonometry
//-----------------------------------------------------------------------------
//! Hyperbolic arcsine
/*!
    Calculates sinh<sup>-1</sup>.
    \param x a value
    \return inverse hyperbolic sine of <i>x</i>
*/
double brahe_asinh(const double x);

//! Hyperbolic arccosine
/*!
    Calculates cosh<sup>-1</sup>.
    \param x a value
    \return inverse hyperbolic cosine of <i>x</i>
*/
double brahe_acosh(const double x);

//! Hyperbolic arctangent
/*!
    Calculates tanh<sup>-1</sup>.
    \param x a value
    \return inverse hyperbolic tangent of <i>x</i>
*/
double brahe_atanh(const double x);

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------

//! e (natural logarithm base
#define BRAHE_E               2.71828182845904523536028747135

//! log_2 (e)
#define BRAHE_LOG2_E          1.44269504088896340735992468100

//! log_10 (e)
#define BRAHE_LOG10_E         0.43429448190325182765112891892

//! sqrt(2)
#define BRAHE_SQRT_2          1.41421356237309504880168872421

//! sqrt(1/2)
#define BRAHE_SQRT_HALF       0.70710678118654752440084436210

//! sqrt(3)
#define BRAHE_SQRT_3          1.73205080756887729352744634151

//! pi  (180 deg)
#define BRAHE_PI              3.14159265358979323846264338328

//! tau (2 * pi)
#define BRAHE_TAU             6.28318530717958647692528676656

//! pi/2 (90 deg)
#define BRAHE_PI_DIV_2        1.57079632679489661923132169164

//! pi/3 (60 deg)
#define BRAHE_PI_DIV_3        1.04719755119659774615421446109

//! pi/4 (45 deg)
#define BRAHE_PI_DIV_4        0.78539816339744830961566084582

//! pi/6 (30 deg)
#define BRAHE_PI_DIV_6        0.52359877559829887307710723055

//! pi/9 (20 deg)
#define BRAHE_PI_DIV_9        0.34906585039886591538473815370

//! pi / 12 (15 deg)
#define BRAHE_PI_DIV_12       0.26179938779914943653855361527

//! pi / 18 (10 deg)
#define BRAHE_PI_DIV_18       0.17453292519943295769236907685

//! pi / 36 (5 deg)
#define BRAHE_PI_DIV_36       0.08726646259971647884618453842

//! degrees per radian
#define BRAHE_DEG_PER_RAD     57.2957795130823208767981548141

//! radians per degree
#define BRAHE_RAD_PER_DEG     0.01745329251994329576923690768

//! sqrt(pi)
#define BRAHE_SQRT_PI         1.77245385090551602729816748334

//! 2/sqrt(pi)
#define BRAHE_TWO_DIV_SQRT_PI 1.12837916709551257389615890312

//! 1/pi
#define BRAHE_ONE_DIV_PI      0.31830988618379067153776752675

//! 2/pi
#define BRAHE_TWO_DIV_PI      0.63661977236758134307553505349

//! ln(10)
#define BRAHE_LN_10           2.30258509299404568401799145468

//! ln(2)
#define BRAHE_LN_2            0.69314718055994530941723212146

//! log(2)
#define BRAHE_LOG_2           0.30102999566398119521373889472

//! ln(pi)
#define BRAHE_LN_PI           1.14472988584940017414342735135

//! Euler constant
#define BRAHE_EULER           0.57721566490153286060651209008

#if defined(__cplusplus)
}
#endif

#endif
