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
    not be appropriate or desirable. In such cases, contact the Brahe copyright holder to
    or implied, of Scott Robert Ladd.

    2) Closed-Source Proprietary License

    If your project is a closed-source or proprietary project, the Simplified BSD License may
    not be appropriate or desirable. In such cases, contact the Itzam copyright holder to
    arrange your purchase of an appropriate license.

    The author can be contacted at:

          scott.ladd@coyotegulch.com
          scott.ladd@gmail.com
          http:www.coyotegulch.com
*/

#include "../src/mathtools.h"

#include <stdio.h>
#include <string.h>

int test_lcm(bool verbose)
{
    // test data
    static const size_t TEST_SIZE = 7;

    static const uint64_t test_set1[] =
    {
        0, 1, 4, 25, 72,  36, 12
    };

    static const uint64_t test_set2[] =
    {
        0, 4, 6, 30, 90, 125, 15
    };

    static const uint64_t expected[] =
    {
        0, 4, 12, 150, 360, 4500, 60
    };

    // counts errors
    size_t i, errcnt = 0;
    uint64_t result;

    for (i = 0; i < TEST_SIZE; ++i)
    {
        result = brahe_lcm(test_set1[i],test_set2[i]);

        if (verbose)
            printf("lcm(%lu,%lu) = %lu (should be %lu)\n",
                    (unsigned long)test_set1[i],
                    (unsigned long)test_set2[i],
                    (unsigned long)result,
                    (unsigned long)expected[i]);

        if (result != expected[i])
            ++errcnt;
    }

    // return number of errors
    return errcnt;
}

int test_gcf(bool verbose)
{
    // test data
    static const size_t TEST_SIZE = 6;

    static const uint64_t test_set1[] =
    {
        0, 1, 156, 24, 28, 644
    };

    static const uint64_t test_set2[] =
    {
        0, 4, 112, 36, 35, 805
    };

    static const uint64_t expected[] =
    {
        0, 1, 4, 12, 7, 161
    };

    // counts errors
    size_t i, errcnt = 0;
    uint64_t result;

    for (i = 0; i < TEST_SIZE; ++i)
    {
        result = brahe_gcf(test_set1[i],test_set2[i]);

        if (verbose)
            printf("gcf(%lu,%lu) = %lu (should be %lu)\n",
                    (unsigned long)test_set1[i],
                    (unsigned long)test_set2[i],
                    (unsigned long)result,
                    (unsigned long)expected[i]);

        if (result != expected[i])
            ++errcnt;
    }

    // return number of errors
    return errcnt;
}

int main(int argc, char * argv[])
{
    size_t errcnt = 0;

    errcnt += test_lcm(true);
    errcnt += test_gcf(true);

    printf("found %d error(s)\n",errcnt);

    return errcnt;
}
