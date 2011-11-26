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
