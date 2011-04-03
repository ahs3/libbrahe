//  ---------------------------------------------------------------------
//  This file is part of Brahe, a heterogenous library of mathematical
//  and scientific functions written in C.
//
//  Brahe may be licensed either under the GNU General Public License v3
//  or a closed license from the author. See below for more information.
//
//  rounding.c
//
//  Rounding and significant digit functions
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
