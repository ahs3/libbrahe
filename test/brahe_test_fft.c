//  ---------------------------------------------------------------------
//  This file is part of Brahe, a heterogenous library of mathematical
//  and scientific functions written in C.
//
//  Brahe may be licensed either under the GNU General Public License v3
//  or a closed license from the author. See below for more information.
//
//  brahe_test_fft.c
//
//  Greatest Common Factor and Least Common Multiple
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
