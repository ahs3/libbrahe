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
#include <stdlib.h>

brahe_wave_factor_t factors [] =
{
    {  100.0, 20.0 },
    {   50.0, 40.0 },
    {    5.0, 100.0 }
};

static const int TEST_SIZE2 = 1024;

int main(int argc, char * argv[])
{
    // generate a sinusoid
    printf("generating sinusoid...\n");
    double * signal = brahe_make_sinusoid(factors, 3, TEST_SIZE2);

    // perform an fft on the sinusoid
    printf("computing FFT...\n");
    double * fft = brahe_simple_fft(signal, TEST_SIZE2);

#if defined(FFT_DUMP)
    for (int n = 0; n < (TEST_SIZE2 / 2); ++n)
        printf("%05d: %6.2f\n",n,brahe_sigdig(fft[n],5));
#endif

    // see if the fft has peaks in the right places
    // these indexes will be WRONG if the length of the signal changes!
    if ((fft[  0] <  1.0)
    &&  (fft[  5] > 20.0)
    &&  (fft[  8] <  4.0)
    &&  (fft[ 10] > 36.0)
    &&  (fft[ 42] <  0.6)
    &&  (fft[102] > 75.0)
    &&  (fft[511] <  0.3))
        printf("Good data... success!\n");
    else
        printf("FFT produced wrong data -- ERROR\n");

    // cleanup
    free(fft);
    free(signal);
}
