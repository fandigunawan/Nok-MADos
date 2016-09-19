 /*
  * 
  * MADos, a free OS for N* handsets  
  * Copyright (C) 2003/2004 MADos Core Developer Team  
  * 
  * This library is free software; you can redistribute it and/or  
  * modify it under the terms of the GNU Lesser General Public  
  * License as published by the Free Software Foundation; either  
  * version 2.1 of the License, or (at your option) any later version.  
  * 
  * This library is distributed in the hope that it will be useful,  
  * but WITHOUT ANY WARRANTY; without even the implied warranty of  
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU  
  * Lesser General Public License for more details.  
  * 
  * You should have received a copy of the GNU Lesser General Public  
  * License along with this library; if not, write to the Free Software  
  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA  
  * 
  * contact http://64.246.26.121/forum/forumdisplay.php?f=99  
  * 
  */

#ifndef PC

#include <core/lib.h>
#include <core/stdio.h>

int
vsnprintf ( char *buf, size_t size, const char *fmt, va_list args )
{
    int len;
    unsigned long long num;
    int i, base;
    char *str, *end, c;
    const char *s;

    int flags;                  /* flags to number() */

    int field_width;            /* width of output field */
    int precision;              /* min. # of digits for integers; max
                                 * number of chars for from string */
    int qualifier;              /* 'h', 'l', or 'L' for integer fields */
    /*
     * 'z' support added 23/7/1999 S.H.    
     */
    /*
     * 'z' changed to 'Z' --davidm 1/25/99 
     */

    str = buf;
    end = buf + size - 1;

    if ( end < buf - 1 )
    {
        end = ( ( void * ) -1 );
        size = end - buf + 1;
    }

    for ( ; *fmt; ++fmt )
    {
        if ( *fmt != '%' )
        {
            if ( str <= end )
                *str = *fmt;
            ++str;
            continue;
        }

        /*
         * process flags 
         */
        flags = 0;
      repeat:
        ++fmt;                  /* this also skips first '%' */
        switch ( *fmt )
        {
            case '-':
                flags |= LEFT;
                goto repeat;
            case '+':
                flags |= PLUS;
                goto repeat;
            case ' ':
                flags |= SPACE;
                goto repeat;
            case '#':
                flags |= SPECIAL;
                goto repeat;
            case '0':
                flags |= ZEROPAD;
                goto repeat;
        }

        /*
         * get field width 
         */
        field_width = -1;
        if ( isdigit ( *fmt ) )
            field_width = skip_atoi ( &fmt );
        else if ( *fmt == '*' )
        {
            ++fmt;
            /*
             * it's the next argument 
             */
            field_width = va_arg ( args, int );
            if ( field_width < 0 )
            {
                field_width = -field_width;
                flags |= LEFT;
            }
        }

        /*
         * get the precision 
         */
        precision = -1;
        if ( *fmt == '.' )
        {
            ++fmt;
            if ( isdigit ( *fmt ) )
                precision = skip_atoi ( &fmt );
            else if ( *fmt == '*' )
            {
                ++fmt;
                /*
                 * it's the next argument 
                 */
                precision = va_arg ( args, int );
            }
            if ( precision < 0 )
                precision = 0;
        }

        /*
         * get the conversion qualifier 
         */
        qualifier = -1;
        if ( *fmt == 'h' || *fmt == 'l' || *fmt == 'L' || *fmt == 'Z' )
        {
            qualifier = *fmt;
            ++fmt;
            if ( qualifier == 'l' && *fmt == 'l' )
            {
                qualifier = 'L';
                ++fmt;
            }
        }

        /*
         * default base 
         */
        base = 10;

        switch ( *fmt )
        {
            case 'c':
                if ( !( flags & LEFT ) )
                {
                    while ( --field_width > 0 )
                    {
                        if ( str <= end )
                            *str = ' ';
                        ++str;
                    }
                }
                c = ( unsigned char ) va_arg ( args, int );
                if ( str <= end )
                    *str = c;
                ++str;
                while ( --field_width > 0 )
                {
                    if ( str <= end )
                        *str = ' ';
                    ++str;
                }
                continue;

            case 's':
                s = va_arg ( args, char * );
                if ( !s )
                    s = "<NULL>";

                len = strnlen ( s, precision );

                if ( !( flags & LEFT ) )
                {
                    while ( len < field_width-- )
                    {
                        if ( str <= end )
                            *str = ' ';
                        ++str;
                    }
                }
                for ( i = 0; i < len; ++i )
                {
                    if ( str <= end )
                        *str = *s;
                    ++str;
                    ++s;
                }
                while ( len < field_width-- )
                {
                    if ( str <= end )
                        *str = ' ';
                    ++str;
                }
                continue;

            case 'p':
                if ( field_width == -1 )
                {
                    field_width = 2 * sizeof ( void * );
                    flags |= ZEROPAD;
                }
                str = number ( str, end, ( unsigned long ) va_arg ( args, void * ), 16, field_width, precision, flags );
                continue;


            case 'n':
                /*
                 * FIXME:
                 * * What does C99 say about the overflow case here? 
                 */
                if ( qualifier == 'l' )
                {
                    long *ip = va_arg ( args, long * );
                    *ip = ( str - buf );
                }
                else if ( qualifier == 'Z' )
                {
                    size_t *ip = va_arg ( args, size_t * );
                    *ip = ( str - buf );
                }
                else
                {
                    int *ip = va_arg ( args, int * );
                    *ip = ( str - buf );
                }
                continue;

            case '%':
                if ( str <= end )
                    *str = '%';
                ++str;
                continue;

                /*
                 * integer number formats - set up the flags and "break" 
                 */
            case 'o':
                base = 8;
                break;

            case 'X':
                flags |= LARGE;
            case 'x':
                base = 16;
                break;

            case 'd':
            case 'i':
                flags |= SIGN;
            case 'u':
                break;

            default:
                if ( str <= end )
                    *str = '%';
                ++str;
                if ( *fmt )
                {
                    if ( str <= end )
                        *str = *fmt;
                    ++str;
                }
                else
                {
                    --fmt;
                }
                continue;
        }
        if ( qualifier == 'L' )
            num = va_arg ( args, long long );
        else if ( qualifier == 'l' )
        {
            num = va_arg ( args, unsigned long );
            if ( flags & SIGN )
                num = ( signed long ) num;
        }
        else if ( qualifier == 'Z' )
        {
            num = va_arg ( args, size_t );
        }
        else if ( qualifier == 'h' )
        {
            num = ( unsigned short ) va_arg ( args, int );
            if ( flags & SIGN )
                num = ( signed short ) num;
        }
        else
        {
            num = va_arg ( args, unsigned int );
            if ( flags & SIGN )
                num = ( signed int ) num;
        }
        str = number ( str, end, num, base, field_width, precision, flags );
    }
    if ( str <= end )
        *str = '\0';
    else if ( size > 0 )
        /*
         * don't write out a null byte if the buf size is zero 
         */
        *end = '\0';
    /*
     * the trailing null byte doesn't count towards the total
     * * ++str;
     */
    return str - buf;
}

static char *
number ( char *buf, char *end, long long num, int base, int size, int precision, int type )
{
    char c, sign, tmp[66];
    const char *digits;
    const char small_digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    const char large_digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;

    digits = ( type & LARGE ) ? large_digits : small_digits;
    if ( type & LEFT )
        type &= ~ZEROPAD;
    if ( base < 2 || base > 36 )
        return 0;
    c = ( type & ZEROPAD ) ? '0' : ' ';
    sign = 0;
    if ( type & SIGN )
    {
        if ( num < 0 )
        {
            sign = '-';
            num = -num;
            size--;
        }
        else if ( type & PLUS )
        {
            sign = '+';
            size--;
        }
        else if ( type & SPACE )
        {
            sign = ' ';
            size--;
        }
    }
    if ( type & SPECIAL )
    {
        if ( base == 16 )
            size -= 2;
        else if ( base == 8 )
            size--;
    }
    i = 0;
    if ( num == 0 )
        tmp[i++] = '0';
    else
        while ( num != 0 )
            tmp[i++] = digits[do_div ( num, base )];
    if ( i > precision )
        precision = i;
    size -= precision;
    if ( !( type & ( ZEROPAD + LEFT ) ) )
    {
        while ( size-- > 0 )
        {
            if ( buf <= end )
                *buf = ' ';
            ++buf;
        }
    }
    if ( sign )
    {
        if ( buf <= end )
            *buf = sign;
        ++buf;
    }
    if ( type & SPECIAL )
    {
        if ( base == 8 )
        {
            if ( buf <= end )
                *buf = '0';
            ++buf;
        }
        else if ( base == 16 )
        {
            if ( buf <= end )
                *buf = '0';
            ++buf;
            if ( buf <= end )
                *buf = digits[33];
            ++buf;
        }
    }
    if ( !( type & LEFT ) )
    {
        while ( size-- > 0 )
        {
            if ( buf <= end )
                *buf = c;
            ++buf;
        }
    }
    while ( i < precision-- )
    {
        if ( buf <= end )
            *buf = '0';
        ++buf;
    }
    while ( i-- > 0 )
    {
        if ( buf <= end )
            *buf = tmp[i];
        ++buf;
    }
    while ( size-- > 0 )
    {
        if ( buf <= end )
            *buf = ' ';
        ++buf;
    }
    return buf;
}

size_t
strnlen ( const char *s, size_t count )
{
    const char *sc;

    for ( sc = s; count-- && *sc != '\0'; ++sc )
        /*
         * nothing 
         */ ;
    return sc - s;
}

static int
skip_atoi ( const char **s )
{
    int i = 0;

    while ( isdigit ( **s ) )
        i = i * 10 + *( ( *s )++ ) - '0';
    return i;
}


int
sprintf ( char *__restrict buf, const char *__restrict format, ... )
{
    va_list arg;
    int rv;

    va_start ( arg, format );
    rv = vsnprintf ( buf, 0xFFFFFFFFUL, format, arg );
    va_end ( arg );

    return rv;
}

#endif
