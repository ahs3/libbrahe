//  ---------------------------------------------------------------------
//  This file is part of Brahe, a heterogenous library of mathematical
//  and scientific functions written in C.
//
//  Brahe may be licensed either under the GNU General Public License v3
//  or a closed license from the author. See below for more information.
//
//  brahe_test_trig.c
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
    int i;
    double a [] = { 1.0, 1.33333333333333333, 1.5 };

    for (i = 0; i < 3; ++i)
    {
        printf("atanh(tanh(%11.8f)) = %11.8f\n",  a[i], brahe_atanh(tanh(a[i])));
        printf("atanh(tanh(%11.8f)) = %11.8f\n", -a[i], brahe_atanh(tanh(-a[i])));
        printf("asinh(sinh(%11.8f)) = %11.8f\n",  a[i], brahe_asinh(sinh(a[i])));
        printf("asinh(sinh(%11.8f)) = %11.8f\n", -a[i], brahe_asinh(sinh(-a[i])));
        printf("acosh(cosh(%11.8f)) = %11.8f\n",  a[i], brahe_acosh(cosh(a[i])));
        printf("acosh(cosh(%11.8f)) = %11.8f\n", -a[i], brahe_acosh(cosh(-a[i])));
    }

    return 0;
}
