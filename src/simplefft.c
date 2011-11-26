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
#include <stdlib.h>
#include <string.h>

static int bitrev(const int j, const int nu)
{
    int j2;
    int j1 = j;
    int k = 0;
    int i;

    for (i = 1; i <= nu; i++)
    {
        j2 = j1 / 2;
        k = 2 * k + j1 - 2 * j2;
        j1 = j2;
    }

    return k;
}

// assumes that the length of x is a power of 2
double * brahe_simple_fft2(const double * x, const int n)
{
    int i, l, r;
    int k = 0;
    int nu = (int)(log((double)n) / log(2.0)); // BRAHE_LOG_2);
    int n2 = n / 2;
    int nu1 = nu - 1;
    double * xre = (double *)malloc(sizeof(double) * n);
    double * xim = (double *)malloc(sizeof(double) * n);
    double * mag = (double *)malloc(sizeof(double) * n / 2);
    double tr, ti, p, arg, c, s;

    if ((xre == NULL) || (xim == NULL) || (mag == NULL))
        return NULL;

    for (i = 0; i < n; i++)
    {
        xre[i] = x[i];
        xim[i] = 0.0;
    }

    for (l = 1; l <= nu; l++)
    {
        while (k < n)
        {
            for (i = 1; i <= n2; i++)
            {
                p = bitrev(k >> nu1, nu);
                arg = BRAHE_TAU * p / n;
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

    for (i = 1; i < n / 2; i++)
        mag[i] = 2 * sqrt(xre[i] * xre[i] + xim[i] * xim[i]) / n;

    free(xre);
    free(xim);

    return mag;
}

double * brahe_simple_fft(const double * x, const int n)
{
    int i;
    double * result = NULL;

    // create a source array that is a power of 2
    int n2 = brahe_sizepow2(n);

    if (n2 != n)
    {
        double * x2 = (double *)malloc(sizeof(double) * n2);

        if (x2 != NULL)
        {
            memcpy(x2,x,sizeof(double) * n);

            for (i = n; i < n2; ++i)
                x2[i] = 0.0;

            result = brahe_simple_fft2(x2,n2);
            free(x2);
        }
    }
    else
        result = brahe_simple_fft2(x,n);

    return result;
}
