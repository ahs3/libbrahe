//  ---------------------------------------------------------------------
//  This file is part of Brahe, a heterogenous library of mathematical
//  and scientific functions written in C.
//
//  Brahe may be licensed either under the GNU General Public License v3
//  or a closed license from the author. See below for more information.
//
//  logtools.c
//
//  Logarithm utilities
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

// Logarithm to a specified base
double brahe_log2base(const double x, const double base)
{
    double result = NAN;
    
    if (x >= 1.0)
        result = log(x) / log(base);
    
    return result;
}

// Smallest power of 2 that includes a given value
int brahe_sizepow2(const int n)
{
    int n2 = 0;
    
    if (n > 0)
    {
        n2 = 1;
        while (true)
        {
            if (n <= n2)
                break;
            else
                n2 <<= 1;
        }
    }
    
    return n2;
}
