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

// basic statistics for an array of double
brahe_statistics brahe_get_statistics(double * data, size_t n)
{
    size_t i;
    brahe_statistics stats;

    // calculate max, average, and minimum fitness for the population
    stats.max = DBL_MIN;
    stats.min = DBL_MAX;
    stats.mean = 0.0;
    stats.variance = 0.0;
    stats.sigma = 0.0;

    for (i = 0; i < n; ++i)
    {
        // do we have a new maximum?
        if (data[i] > stats.max)
            stats.max = data[i];

        // do we have a new minimum?
        if (data[i] < stats.min)
            stats.min = data[i];

        // accumulate for average
        stats.mean += data[i];
    }

    stats.mean /= (double)n;

    for (i = 0; i < n; ++i)
    {
        double diff = data[i] - stats.mean;
        stats.variance += (diff * diff);
    }

    stats.variance /= (double)(n - 1);

    // calculate 2 times the std. deviation (sigma)
    stats.sigma = sqrt(stats.variance);

    return stats;
}

// Moving average
double * brahe_moving_average(const double * data, const int n, const int distance)
{
    double * result = (double *)malloc(sizeof(double) * n);
    int i, x;
    int m = n - distance;

    for (i = 0; i < n; ++i)
    {
        double count = 0.0;

        for (x = i - distance; x <= i + distance; ++x)
        {
            if ((x >= 0) && (x <= m))
            {
                result[i] += data[x];
                count += 1.0;
            }
        }

        result[i] /= count;
    }

    return result;
}

