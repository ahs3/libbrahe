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
