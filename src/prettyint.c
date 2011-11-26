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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* strings used in text output */

static char digit[] =
{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

static char * ones[] =
{
     "", "one", "two", "three", "four", "five",
     "six", "seven", "eight", "nine", "ten",
     "eleven", "twelve", "thirteen", "fourteen", "fifteen",
     "sixteen", "seventeen", "eighteen", "nineteen"
};

static char * tens[] =
{
     "twenty", "thirty", "forty", "fifty",
     "sixty", "seventy", "eighty", "ninety"
};

static char * powers[] =
{
     "thousand", "million", "billion", "trillion", "quadrillion", "quintillion", "sextillion"
};

/* Creates a new string by combining two others */
static char * strapp(char * front, const char * back)
{
    char * result = NULL;

    if (front == NULL)
    {
        if (back != NULL)
            result = strdup(back);
    }
    else
    {
        result = (char *)malloc(strlen(front) + strlen(back) + 1);
        sprintf(result,"%s%s", front, back);
        free(front);
    }

    return result;
}

static int64_t intpow10(int64_t p)
{
    int64_t res;
    for (res = 1; p--; res *= 10) ;
    return res;
}

static int64_t intlog10(int64_t l)
{
    int p;
    for (p = 18; !(l / intpow10(p)); --p) ;
    return p;
}

static char * format_text(int64_t n)
{
    int64_t temp;     /* value used to hold temporary values */
    int64_t place;    /* which place we're at */
    int64_t hundreds; /* the amount in the current place */
    char * buffer = NULL;

    /* if the input is 0, the format is always the same */
    if (n == 0)
    {
        buffer = strapp(buffer,"zero");
        return buffer;
    }

    /* if n is negative, say so, and get n's positive value */
    if (n < 0)
    {
        buffer = strapp(buffer,"negative ");
        n = -n;
    }

    /* find the highest 'place' in the number */
    place = intlog10(n) / 3L;

    while (place >= 0)
    {
        /* find the "hundreds" amount of the current place */
        temp = intpow10(place * 3L);
        hundreds = n / temp;

        /* if it's not zero */
        if (hundreds)
        {
            /* subtract the place amount from n */
            n -= temp * hundreds;

            /* get the digits in the hundreds place */
            temp = hundreds / 100;

            /* if there are hundreds, add their test to the buffer */
            if (temp)
            {
                hundreds -= temp * 100;
                buffer = strapp(buffer,ones[(int)temp]);
                buffer = strapp(buffer," hundred");
            }

            /* if hundreds still has a value */
            if (hundreds)
            {
                if (temp)
                    buffer = strapp(buffer," ");

                if (hundreds < 20)
                    /* use specific names like 'one' or 'eleven' */
                    buffer = strapp(buffer,ones[(int)hundreds]);
                else
                {
                    temp = hundreds / 10;

                    /* if a number in the 'tens' spot */
                    if (temp)
                    {
                        hundreds -= temp * 10;
                        buffer = strapp(buffer,tens[(int)temp-2]);
                    }

                    /* if a number in the 'ones' spot */
                    if (hundreds)
                    {
                        buffer = strapp(buffer,"-");
                        buffer = strapp(buffer,ones[(int)hundreds]);
                    }
                }
            }

            /* if this place is a thousand or more, display the place name */
            if (place)
            {
                buffer = strapp(buffer," ");
                buffer = strapp(buffer,powers[(int)place-1]);

                /* if n still has value, put a comma */
                if (n)
                    buffer = strapp(buffer,", ");
            }
        }

        /* go to the next decimal place */
        --place;
    }

    return buffer;
}

#define NEEDED64 26

static char * format_comma(int64_t n)
{
    int64_t x, t, p;

    char * result = (char *)malloc(NEEDED64);
    char * r = result;

    memset(result,0,NEEDED64);

    /* if n is 0, the format is fixed */
    if (n == 0)
    {
        *r++ = '0';
        *r = 0;
        return result;
    }

    if (n < 0)
    {
        /* put a negative sign in the r */
        *r++ = '-';

        /* get the positive value of n */
        n = -n;
    }

    /* loop thru each decimal place in n */
    for (p = intlog10(n); p >= 0; --p)
    {
        x = intpow10(p);

        /* get the value of the current digit */
        t = n / x;

        /* remove the digit being displayed from n */
        n -= t * x;

        /* insert the proper digit */
        *r++ = digit[(int)t];

        /* place a comma after every third digit */
        if (!(p % 3) && p)
            *r++ = ',';
    }

    *r = 0;

    return result;
}

/*      Formats a int32_t integer into a strings
            comma delimited -- 1,234,567,890
            english text    -- nine thousand, two hundred eleven
        Returns a string that must be free'd by caller
 */

char * brahe_pretty_int(int64_t n, brahe_pretty_format fmt)
{
    char * str = NULL;

    switch (fmt)
    {
        case BRAHE_PRETTY_TEXT: /* U.S. english text */
            str = format_text(n);
            break;

        case BRAHE_PRETTY_COMMA: /* comma delimited */
            str = format_comma(n);
            break;

        default :
            return 0;
    };

    return str;
}
