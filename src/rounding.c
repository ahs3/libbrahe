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

#include "mathtools.h"

//  Rounds a value to nearest integer, rounding to even for exact fractions of 0.5.
double brahe_round_nearest(const double x)
{
    double result, fraction, dummy;

    fraction = fabs(modf(x,&result));

    if (fraction == 0.0)
        return result;

    if (fraction == 0.5)
    {
        if (modf(result / 2.0, &dummy) != 0.0)
        {
            if (x < 0.0)
                result -= 1.0;
            else
                result += 1.0;
        }
    }
    else
    {
        if (fraction > 0.5)
        {
            if (x < 0.0)
                result -= 1.0;
            else
                result += 1.0;
        }
    }

    return result;
}

//  Returns the given value rounded for the number of specified decimal digits of precision.
double brahe_sigdig(const double x, const uint16_t n)
{
    double scale_factor, result;

    // is asking for no digits, or more digits than in double, simply return x
    if ((n == 0) || (n > DBL_DIG))
        result = x;
    else
    {
        // find a factor of ten such that all significant digits will
        //    be in the integer part of the double
        scale_factor = pow(10.0,(double)((int)n - 1 - (int)floor(log10(fabs(x)))));

        // scale up, round, and scale down
        result = brahe_round_nearest(x * scale_factor) / scale_factor;
    }

    return result;
}
