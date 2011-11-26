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
#include "prng.h"
#include <string.h>
#include <stdlib.h>

double * brahe_make_sinusoid(const brahe_wave_factor_t * factors, const size_t factor_n, const size_t array_n)
{
    size_t i, n;
    double * result = NULL;

    if ((array_n > 0) && (factor_n > 0) && (factors != NULL))
    {
        result = (double *)malloc(sizeof(double) * array_n);

        if (result != NULL)
        {
            double * f = (double *)malloc(sizeof(double) * factor_n);
            double * a = (double *)malloc(sizeof(double) * factor_n);

            for (n = 0; n < factor_n; ++n)
            {
                f[n] = BRAHE_PI / factors[n].wavelength;
                a[n] = 0.0;
            }

            for (i = 0; i < array_n; ++i)
            {
                for (n = 0; n < factor_n; ++n)
                {
                    result[i] += sin(a[n]) * factors[n].amplitude;
                    a[n] += f[n];
                }
            }
        }
    }

    return result;
}

void brahe_add_noise(double * a, const size_t n, double noise)
{
    size_t i;

    if ((n > 0) && (a != NULL) && (noise > 0.0))
    {
        brahe_prng_state_t prng;

        if (!brahe_prng_init(&prng,BRAHE_PRNG_KISS,BRAHE_UNKNOWN_SEED))
            return;

        for (i = 0; i < n; ++i)
        {
            double x = brahe_prng_real1(&prng) * noise;

            if (1 == brahe_prng_next(&prng) % 2)
                a[i] += x;
            else
                a[i] -= x;
        }
    }
}
