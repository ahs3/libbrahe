//  ---------------------------------------------------------------------
//  This file is part of Brahe, a heterogenous library of mathematical
//  and scientific functions written in C.
//
//  Brahe may be licensed either under the GNU General Public License v3
//  or a closed license from the author. See below for more information.
//
//  simplefft.c
//
//  A simple real-to-real FFT; this is not meant to compete with or
//	replace dedicated libraries such as FFTW.
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
#include <stdlib.h>
#include <string.h>

static int bitrev(const int j, const int nu)
{
    int j2;
    int j1 = j;
    int k = 0;

    for (int i = 1; i <= nu; i++)
    {
        j2 = j1 / 2;
        k = 2 * k + j1 - 2 * j2;
        j1 = j2;
    }

    return k;
}

// assumes that the length of x is a power of 2
double * brahe_simple_fft2(const double const * x, const int n)
{
    // n is a power of 2
    int nu = (int)(log(n) / log(2.0)); // BRAHE_LOG_2);
    int n2 = n / 2;
    int nu1 = nu - 1;
    
    double * xre = (double *)malloc(sizeof(double) * n);
    
    if (xre == NULL)
        return NULL;
    
    double * xim = (double *)malloc(sizeof(double) * n);
    
    if (xim == NULL)
    {
        free(xre);
        return NULL;
    }
    
    double * mag = (double *)malloc(sizeof(double) * n / 2);
    
    if (mag == NULL)
    {
        free(xre);
        free(xim);
        return NULL;
    }
    
    double tr, ti, p, arg, c, s;

    for (int i = 0; i < n; i++)
    {
        xre[i] = x[i];
        xim[i] = 0.0;
    }

    int k = 0;

    for (int l = 1; l <= nu; l++)
    {
        while (k < n)
        {
            for (int i = 1; i <= n2; i++)
            {
                p = bitrev(k >> nu1, nu);
                arg = 2.0 * BRAHE_PI * p / n;
                c = cos(arg);
                s = sin(arg);
                tr = xre[k + n2] * c + xim[k + n2] * s;
                ti = xim[k + n2] * c - xre[k + n2] * s;
                xre[k + n2] = xre[k] - tr;
                xim[k + n2] = xim[k] - ti;
                xre[k] += tr;
                xim[k] += ti;
                k++;
            }
            
            k += n2;
        }
        
        k = 0;
        nu1--;
        n2 = n2 / 2;
    }

    k = 0;
    int r;

    while (k < n)
    {
        r = bitrev(k,nu);

        if (r > k)
        {
            tr = xre[k];
            ti = xim[k];
            xre[k] = xre[r];
            xim[k] = xim[r];
            xre[r] = tr;
            xim[r] = ti;
        }

        k++;
    }

    mag[0] = sqrt(xre[0] * xre[0] + xim[0] * xim[0]) / n;

    for (int i = 1; i < n / 2; i++)
        mag[i] = 2 * sqrt(xre[i] * xre[i] + xim[i] * xim[i]) / n;

    free(xre);
    free(xim);

    return mag;
}

double * brahe_simple_fft(const double const * x, const int n)
{
    double * result = NULL;
    
    // create a source array that is a power of 2
    int n2 = brahe_sizepow2(n);
    
    if (n2 != n)
    {
        double * x2 = (double *)malloc(sizeof(double) * n2);
        
        if (x2 != NULL)
        {
            memcpy(x2,x,sizeof(double) * n);
            
            for (int i = n; i < n2; ++i)
                x2[i] = 0.0;
            
            result = brahe_simple_fft2(x2,n2);
            free(x2);
        }
    }
    else
        result = brahe_simple_fft2(x,n);

    return result;
}
