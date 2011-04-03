//  ---------------------------------------------------------------------
//  This file is part of Brahe, a heterogenous library of mathematical
//  and scientific functions written in C.
//
//  Brahe may be licensed either under the GNU General Public License v3
//  or a closed license from the author. See below for more information.
//
//  gcflcm.c
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

#include "mathtools.h"

// lowest common denominator
uint64_t brahe_lcm(const uint64_t x, const uint64_t y)
{
    uint64_t result = 0;

    if (x == y)
        result = x;
    else
        if (x < y)
            result = (y / brahe_gcf(x,y)) * x;
        else
            result = (x / brahe_gcf(y,x)) * y;

    return result;
}

// greatest common multiple
uint64_t brahe_gcf(uint64_t x, uint64_t y)
{
    uint64_t temp;

    while (y != 0)
    {
        temp = x % y;
        x = y;
        y = temp;
    }

    return x;
}
