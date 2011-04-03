//  ---------------------------------------------------------------------
//  This file is part of Brahe, a heterogenous library of mathematical
//  and scientific functions written in C.
//
//  Brahe may be licensed either under the GNU General Public License v3
//  or a closed license from the author. See below for more information.
//
//  brahe_test_gcflcm.c
//
//  Greatest Common Factor and Least Common Multiple
//
//  Copyright 2006, 2007, 2009 Scott Robert Ladd
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
    bool verbose = false;
    size_t errcnt = 0;
    
    if (argc > 1)
    {
        if (0 == strcmp(argv[1],"-v"))
            verbose = true;
    }
    
    errcnt += test_lcm(verbose);
    errcnt += test_gcf(verbose);
    
    if (verbose)
        fprintf(stderr,"found %d error(s)\n",errcnt);
    
    return errcnt;
}
