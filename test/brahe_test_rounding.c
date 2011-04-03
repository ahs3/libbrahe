//  ---------------------------------------------------------------------
//  This file is part of Brahe, a heterogenous library of mathematical
//  and scientific functions written in C.
//
//  Brahe may be licensed either under the GNU General Public License v3
//  or a closed license from the author. See below for more information.
//
//  brahe_test_rounding.c
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

#include "../src/mathtools.h"

#include <stdio.h>

int main(int argc, char * argv[])
{
    const double pi = 3.14159265358979;
    const double e  = 27182.8182845905;
    const double c  = 299792.4562;

    printf("tonearest(pi)    = %15.8f (should be      3.00000000)\n", brahe_round_nearest(pi));
    printf("tonearest(-pi)   = %15.8f (should be     -3.00000000)\n", brahe_round_nearest(-pi));
    printf("tonearest(e)     = %15.8f (should be  27183.00000000)\n", brahe_round_nearest(e));
    printf("tonearest(-e)    = %15.8f (should be -27183.00000000)\n", brahe_round_nearest(-e));
    printf("tonearest(6.5)   = %15.8f (should be      6.00000000)\n", brahe_round_nearest(6.5));
    printf("tonearest(-6.5)  = %15.8f (should be     -6.00000000)\n", brahe_round_nearest(-6.5));
    printf("tonearest(17.5)  = %15.8f (should be     18.00000000)\n", brahe_round_nearest(17.5));
    printf("tonearest(-17.5) = %15.8f (should be    -18.00000000)\n\n", brahe_round_nearest(-17.5));

    printf("sigdig(pi,5)     = %15.8f (should be      3.14160000)\n", brahe_sigdig(pi,5));
    printf("sigdig(-pi,8)    = %15.8f (should be      3.14159270)\n", brahe_sigdig(-pi,8));
    printf("sigdig(e,5)      = %15.8f (should be  30000.00000000)\n", brahe_sigdig(e,1));
    printf("sigdig(-e,5)     = %15.8f (should be -27180.00000000)\n", brahe_sigdig(-e,4));
    printf("sigdig(c,1)      = %15.8f (should be 300000.00000000)\n", brahe_sigdig(c,1));
    printf("sigdig(c,2)      = %15.8f (should be 300000.00000000)\n", brahe_sigdig(c,2));
    printf("sigdig(c,3)      = %15.8f (should be 300000.00000000)\n", brahe_sigdig(c,3));
    printf("sigdig(c,4)      = %15.8f (should be 299800.00000000)\n", brahe_sigdig(c,4));
    printf("sigdig(c,5)      = %15.8f (should be 299790.00000000)\n", brahe_sigdig(c,5));
    printf("sigdig(c,6)      = %15.8f (should be 299792.00000000)\n", brahe_sigdig(c,6));
    printf("sigdig(c,7)      = %15.8f (should be 299792.50000000)\n", brahe_sigdig(c,7));
    printf("sigdig(c,8)      = %15.8f (should be 299792.46000000)\n", brahe_sigdig(c,8));
    printf("sigdig(c,9)      = %15.8f (should be 299792.45600000)\n", brahe_sigdig(c,9));
    printf("sigdig(c,10)     = %15.8f (should be 299792.45620000)\n", brahe_sigdig(c,10));
    printf("sigdig(6.5,2)    = %15.8f (should be      6.50000000)\n", brahe_sigdig(6.5,2));
    printf("sigdig(-6.5,2)   = %15.8f (should be     -6.50000000)\n", brahe_sigdig(-6.5,2));
    printf("sigdig(17.5,2)   = %15.8f (should be     18.00000000)\n", brahe_sigdig(17.5,2));
    printf("sigdig(-17.5,2)  = %15.8f (should be    -18.00000000)\n", brahe_sigdig(-17.5,2));

    return 0;
}
