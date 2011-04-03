//  ---------------------------------------------------------------------
//  This file is part of Brahe, a heterogenous library of mathematical
//  and scientific functions written in C.
//
//  Brahe may be licensed either under the GNU General Public License v3
//  or a closed license from the author. See below for more information.
//
//  sinusoid.c
//
//  Tools for generating complex wave patterns by combining multiple sine
//  waves.
//
//  Copyright 2009 Scott Robert Ladd
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
#include <string.h>

double * brahe_make_sinusoid(const brahe_wave_factor_t const * factors, const int factor_n, const int array_n)
{
    double * result = (double *)malloc(sizeof(double) * array_n);
    
    if (result != NULL)
    {
        double * f = (double *)malloc(sizeof(double) * factor_n);
        double * a = (double *)malloc(sizeof(double) * factor_n);

        for (int n = 0; n < factor_n; ++n)
        {
            f[n] = BRAHE_PI / factors[n].hertz;
            a[n] = 0.0;
        }

        for (int i = 0; i < array_n; ++i)
        {
            for (int n = 0; n < factor_n; ++n)
            {
                result[i] += sin(a[n]) * factors[n].amplitude;
                a[n] += f[n];
            }
        }
    }

    return result;
}
