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

#include <core/softfloat.h>
#include <core/sched.h>
#include <core/lib.h>
#include <hw/kpd.h>
#include <hw/timer.h>

#ifdef PC
#include <sys/time.h>
unsigned short _dsp[4096];
unsigned char _io[0x200];
unsigned short _dspif[0x10];
unsigned char _mcuif[0x10];
unsigned int lib_starttime;

unsigned int
usleep_hard ( unsigned int delay )
{
    return usleep ( delay );
}
#endif

unsigned int random_table[32];
unsigned int rand_pos = 0;
unsigned char lib_allow_sched = 0;
unsigned int hard_calibrated = 0;
extern unsigned char int_critical;

#ifdef ARM
unsigned char malloc_buf[MALLOC_BUF_SIZE];
malloc_pointer malloc_ptr[MALLOC_NUM_BUFS];
unsigned char malloc_locked;
#endif

void
lib_init_hard ( void )
{
#ifdef ARM
    calibrate_hard (  );
#endif
}

void
lib_init ( void )
{
    lib_allow_sched = 0;
#ifdef ARM
    malloc_init (  );
#endif
#ifdef PC
    lib_starttime = 0;
    lib_starttime = lib_get_time (  );
#endif
}

void
lib_enable_sched ( void )
{
#ifdef ARM
    lib_allow_sched = 1;
#endif
}

void
lib_disable_sched ( void )
{
    lib_allow_sched = 0;
}

static unsigned long
divmodsi4 ( int modwanted, unsigned long num, unsigned long den )
{
    long int bit = 1;
    long int res = 0;
    long prevden;


    while ( den < num && bit && !( den & ( 1L << 31 ) ) )
    {
        den <<= 1;
        bit <<= 1;
    }
    while ( bit )
    {
        if ( num >= den )
        {
            num -= den;
            res |= bit;
        }
        bit >>= 1;
        den >>= 1;
    }
    if ( modwanted )
        return num;
    return res;
}

inline long
modsi3 ( unsigned long numerator, unsigned long denominator )
{
    long ret;

    ret = divmodsi4 ( 1, numerator, denominator );
    return ret;
}


inline long
__modsi3 ( unsigned long numerator, unsigned long denominator )
{
    long ret;

    ret = divmodsi4 ( 1, numerator, denominator );
    return ret;
}

inline long
__umodsi3 ( unsigned long numerator, unsigned long denominator )
{
    long ret;

    ret = divmodsi4 ( 1, numerator, denominator );
    return ret;
}

/*
inline long
divsi3 ( unsigned long numerator, unsigned long denominator )
{
    long ret;

    ret = divmodsi4 ( 0, numerator, denominator );
    return ret;
}
*/

inline long
__divsi3 ( unsigned long numerator, unsigned long denominator )
{
    long ret;

    ret = divmodsi4 ( 0, numerator, denominator );
    return ret;
}

inline long
__udivsi3 ( unsigned long numerator, unsigned long denominator )
{
    long ret;

    ret = divmodsi4 ( 0, numerator, denominator );
    return ret;
}

/*
// not as easy as i thought
inline float32
__divsi3 ( float32 numerator, float32 denominator )
{
	return float32_div ( numerator, denominator );
}
*/



int
lib_rand ( int seed )
{
    seed += lib_get_time (  );
    rand_pos = lib_mod ( random_table[rand_pos] + seed, 32 );
    random_table[rand_pos] = ( random_table[rand_pos] ^ random_table[32 - rand_pos] + 11 * rand_pos ) & 0x7FFFFF;

    return random_table[rand_pos];
}

// thanks to Taylor and MacLaurin for these nice series :)
float32
sine ( float32 rad )
{
    char c, d, e, f;
    float32 sum, f1, f2;

    sum = int32_to_float32 ( 0 );

    c = 1;
    d = 1;

    e = 5;                      //precision maybe should be higher

    while ( e )
    {
        f = c;
        f1 = int32_to_float32 ( 1 );
        while ( f )
        {
            f1 = float32_mul ( f1, rad );
            f--;
        }

        f2 = int32_to_float32 ( 1 );
        for ( f = c; f > 0; f-- )
            f2 = float32_mul ( f2, int32_to_float32 ( ( int ) f ) );

        if ( d )
            sum = float32_add ( sum, float32_div ( f1, f2 ) );
        else
            sum = float32_sub ( sum, float32_div ( f1, f2 ) );

        c += 2;
        d = lib_mod ( d + 1, 2 );
        e--;
    }

    return sum;
}

float32
cosine ( float32 rad )
{
    char c, d, e, f;
    float32 sum, f1, f2;

    sum = int32_to_float32 ( 1 );

    c = 2;
    d = 0;

    e = 10;                     //precision - maybe should be higher

    while ( e )
    {
        f = c;
        f1 = int32_to_float32 ( 1 );
        while ( f )
        {
            f1 = float32_mul ( f1, rad );
            f--;
        }

        f2 = int32_to_float32 ( 1 );
        for ( f = c; f > 0; f-- )
            f2 = float32_mul ( f2, int32_to_float32 ( ( int ) f ) );

        if ( d )
            sum = float32_add ( sum, float32_div ( f1, f2 ) );
        else
            sum = float32_sub ( sum, float32_div ( f1, f2 ) );

        c += 2;
        d = lib_mod ( d + 1, 2 );
        e--;
    }

    return sum;
}

void
lib_init_rand ( int seed )
{
    int i = 0;

    random_table[i++] = 124;
    random_table[i++] = 1497523;
    random_table[i++] = 5239134;
    random_table[i++] = 12324946;
    random_table[i++] = 4248146;
    random_table[i++] = 726925;
    random_table[i++] = 89;
    random_table[i++] = 1991423;
    random_table[i++] = 9141729;
    random_table[i++] = 123523;
    random_table[i++] = 544427;
    random_table[i++] = 3244724;
    random_table[i++] = 643;
    random_table[i++] = 323429;
    random_table[i++] = 923121;
    random_table[i++] = 154;
    random_table[i++] = 847436;
    random_table[i++] = 5337667;
    random_table[i++] = 4989746;
    random_table[i++] = 3456846;
    random_table[i++] = 987655;
    random_table[i++] = 83;
    random_table[i++] = 123459;
    random_table[i++] = 9141729;
    random_table[i++] = 63;
    random_table[i++] = 963247;
    random_table[i++] = 6394804;
    random_table[i++] = 405;
    random_table[i++] = 32908990;
    random_table[i] = 104065;
}


#ifdef ARM
unsigned int
strlen ( const char *t )
{
    unsigned int len = 0;

    if ( !t )
        return 0;

    while ( *( t++ ) )
        len++;

    return len;
}

char *
strcpy ( char *d, const char *s )
{
    unsigned int len = strlen ( s );

    memcpy ( d, s, len + 1 );

    return d;
}

char *
strcat ( char *d, const char *s )
{
    return strcpy ( d + strlen ( d ), s );
}

char *
strrev ( char *str )
{
    char *p1, *p2;
    if ( !str || !*str )
        return str;
    for ( p1 = str, p2 = str + strlen ( str ) - 1; p2 > p1; ++p1, --p2 )
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}

int
strcmp ( const char *str1, const char *str2 )
{
    unsigned int i = 0;
/*    while ( *str1 == *str2 )
        if ( *str1++ == 0 )
            return 0;
    return 1;*/

    while ( str1[i] == str2[i] )
        if ( str1[i++] == 0x00 )
            return 0;

    return str1[i] - str2[i];
}

int
strncmp ( const char *str1, const char *str2, unsigned long n )
{
    unsigned int i = 0;

    while ( n-- && str1[i] == str2[i] )
        if ( str1[i++] == 0x00 )
            return 0;

    return str1[i] - str2[i];
}

int
memcmp ( const void *s1, const void *s2, unsigned long n )
{
    unsigned int i = 0;
    unsigned char *str1 = ( unsigned char * ) s1;
    unsigned char *str2 = ( unsigned char * ) s2;

    while ( n-- && str1[i] == str2[i] ) ;

    if ( !n )
        return 0;

    return str1[i] - str2[i];
}

unsigned int inline
usleep_hard ( unsigned int delay )
{
    int num = hard_calibrated;

    delay = lib_div ( num * delay, 10 );
    while ( delay-- )
        asm volatile ( "nop" );
}


int
calibrate_hard ( void )
{
    unsigned int target;
    int num = 0;
    int parm;

    parm = sched_get_parm ( 0xFF );
    sched_set_parm ( 0xFF, SCHED_PARM_MASTER );

    hard_calibrated = 0;

    do
    {
        hard_calibrated += 20;
        target = lib_get_time (  );
        usleep_hard ( 100000 );
        target = lib_get_time (  ) - target;
        if ( target < 80 )
            hard_calibrated *= lib_div ( 100, target );
    }
    while ( target < 100 );

    sched_set_parm ( 0xFF, parm );
}

unsigned int inline
usleep ( unsigned int delay )
{
    unsigned int dly = delay;
    unsigned int target;

    if ( sched_get_parm ( 0xFF ) & SCHED_PARM_MASTER )
        return usleep_hard ( lib_div ( delay, 1000 ) );

    if ( lib_allow_sched && !int_critical )
    {
        target = lib_get_time (  ) + lib_div ( delay, 1000 );
        if ( delay > 50000 )
            sched_enter_sleep ( 0xFF, target );

        while ( lib_get_time (  ) < target )
            asm volatile ( "nop" );
    }
    else
    {
        while ( dly-- )
            asm volatile ( "nop" );
    }

    return 0;
}

unsigned int volatile
sleep ( unsigned int delay )
{
    unsigned int dly;
    unsigned int target;

    if ( sched_get_parm ( 0xFF ) & SCHED_PARM_MASTER )
        return usleep_hard ( lib_div ( delay, 1000 ) );

    if ( lib_allow_sched && !int_critical )
    {
        target = lib_get_time (  ) + delay * 1000;
        sched_enter_sleep ( 0xFF, target );

        while ( lib_get_time (  ) < target )
            asm volatile ( "nop" );
    }
    else
    {
        dly = 400000 * delay;
        while ( dly-- )
            usleep ( 1 );
    }

    return 0;

}

void *
memcpy ( void *dest, const void *src, unsigned long count )
{

/* 
 * Copyright (C) 2002 Mark Debbage (Mark.Debbage@superh.com)
 *
 * This is a simplistic optimization of memcpy to increase the
 * granularity of access beyond one byte using aligned
 * loads and stores.
 */

    char *d = ( char * ) dest, *s = ( char * ) src;

    if ( count >= 32 )
    {
        int i = 8 - ( ( ( unsigned long ) d ) & 0x7 );

        if ( i != 8 )
            while ( i-- && count-- )
            {
                *d++ = *s++;
            }

        if ( ( ( ( ( unsigned long ) d ) & 0x7 ) == 0 ) && ( ( ( ( unsigned long ) s ) & 0x7 ) == 0 ) )
        {
            while ( count >= 32 )
            {
                unsigned long long t1, t2, t3, t4;
                t1 = *( unsigned long long * ) ( s );
                t2 = *( unsigned long long * ) ( s + 8 );
                t3 = *( unsigned long long * ) ( s + 16 );
                t4 = *( unsigned long long * ) ( s + 24 );
                *( unsigned long long * ) ( d ) = t1;
                *( unsigned long long * ) ( d + 8 ) = t2;
                *( unsigned long long * ) ( d + 16 ) = t3;
                *( unsigned long long * ) ( d + 24 ) = t4;
                d += 32;
                s += 32;
                count -= 32;
            }
            while ( count >= 8 )
            {
                *( unsigned long long * ) d = *( unsigned long long * ) s;
                d += 8;
                s += 8;
                count -= 8;
            }
        }

        if ( ( ( ( ( unsigned long ) d ) & 0x3 ) == 0 ) && ( ( ( ( unsigned long ) s ) & 0x3 ) == 0 ) )
        {
            while ( count >= 4 )
            {
                *( unsigned long * ) d = *( unsigned long * ) s;
                d += 4;
                s += 4;
                count -= 4;
            }
        }

        if ( ( ( ( ( unsigned long ) d ) & 0x1 ) == 0 ) && ( ( ( ( unsigned long ) s ) & 0x1 ) == 0 ) )
        {
            while ( count >= 2 )
            {
                *( unsigned short * ) d = *( unsigned short * ) s;
                d += 2;
                s += 2;
                count -= 2;
            }
        }
    }

    while ( count-- )
    {
        *d++ = *s++;
    }

    return d;
}

void *
memmove ( void *d, const void *s, unsigned long len )
{
    unsigned char buf[1024];

    if ( len > 1024 )
        return;

    memcpy ( buf, s, len );
    memcpy ( d, buf, len );
}

void *
memset ( void *s, int c, unsigned long n )
{
    while ( n-- )
        ( ( unsigned char * ) s )[n] = ( unsigned char ) c;

    return s;
}

#endif



void
lib_call_func ( unsigned int code )
{
#ifdef ARM
    asm volatile ( "push { R0-R7,LR }\nmov r1, pc\nadd r1, r1, #0x05\nmov lr, r1\n bx %0\npop { R0-R7 }\npop { R0 }\nmov LR, R0\n"::"r" ( code ) );
#endif
}

// use also for PC platform since theres no such function ;)
unsigned int
ksleep ( unsigned int delay )
{
    unsigned int target = lib_get_time (  ) + delay * 1000;

    kpd_mode ( KPD_UNBUFFERED );    // kr: backup current state & return it after sleep ?
    while ( lib_get_time (  ) < target && kpd_getkey (  ) == 0xFF ) ;

    return 0;
}

unsigned int volatile
sleep2 ( unsigned int delay )
{
    unsigned int dly;
    unsigned int target;

    if ( sched_get_parm ( 0xFF ) & SCHED_PARM_MASTER )
        return usleep_hard ( lib_div ( delay, 1000 ) );

    if ( lib_allow_sched && !int_critical )
    {
        target = lib_get_time (  ) + delay * 10;
        sched_enter_sleep ( 0xFF, target );

        while ( lib_get_time (  ) < target )
            asm volatile ( "nop" );
    }
    else
    {
        dly = 400000 * delay;
        while ( dly-- )
            usleep ( 1 );
    }

    return 0;

}

unsigned int
kmsleep ( unsigned int delay )
{
    unsigned int target = lib_get_time (  ) + delay;
    unsigned char buf[32];

    kpd_mode ( KPD_UNBUFFERED );
    while ( lib_get_time (  ) < target && kpd_getkey (  ) == 0xFF )
    {
/*	lcd_clr ();
	lib_hexconv ( buf, lib_get_time () );
	lcd_render_text ( 0, 0, buf, 1 );
	lib_hexconv ( buf, target );
	lcd_render_text ( 0, 8, buf, 1 );
	lib_hexconv ( buf, delay );
	lcd_render_text ( 0, 0x10, buf, 1 );
	lcd_to_screen ();*/
    }


    return 0;
}

void
lib_hexconv ( char *buf, int val )
{
    int i = 0;
    int pos = 0;

    while ( i < 8 )
        buf[pos++] = "0123456789ABCDEF"[( val >> ( ( 7 - i++ ) * 4 ) ) & 0x0F];

    buf[pos] = 0x00;

    return;
}

void
lib_phexconv ( char *buf, int *val )
{
    int i = 0;
    int pos = 0;

    while ( i < 8 )
        buf[pos++] = "0123456789ABCDEF"[( *val >> ( ( 7 - i++ ) * 4 ) ) & 0x0F];

    buf[pos] = 0x00;

    return;
}

// converts an unsigned integer to string
void
lib_dtoa ( char *buf, unsigned int val, unsigned int max_length, unsigned char no_leading_zero )
{
    int i;
    int pos = 0;
    unsigned int val_to_sub = 0;
    unsigned int stellenzahl = 1;
    //unsigned char leading_zero = 1;
    char c;

    for ( i = 0; i < max_length; i++ )
        stellenzahl *= 10;

    if ( val >= stellenzahl )
        val = stellenzahl - 1;
    stellenzahl = lib_div ( stellenzahl, 10 );

    for ( i = 0; i < max_length; i++ )
    {
        c = lib_div ( val - val_to_sub, stellenzahl );
        if ( c != 0 )
            no_leading_zero = 0;
        val_to_sub += stellenzahl * c;
        if ( no_leading_zero )
            buf[pos++] = 0x20;
        else
            buf[pos++] = c + 0x30;
        stellenzahl = lib_div ( stellenzahl, 10 );
    }

    buf[pos] = 0x00;

    return;

}

unsigned int
lib_get_time ( void )
{
#ifdef ARM
    return lib_div ( timer_get_time (  ) * 1000, 1057 );
#endif
#ifdef PC
    struct timeval tv;

    gettimeofday ( &tv, NULL );
    return ( ( ( tv.tv_sec * 1000 ) + lib_div ( tv.tv_usec, 1000 ) ) - lib_starttime );
#endif
}

int
lib_abs ( int fullint )
{
    if ( fullint < 0 )
        return ( fullint & 0x7FFFFFFF );
    else
        return fullint;
}

// converts string to a long integer
// allowed chars 0 - 9, other chars are unrecognized
long int
atol ( const char *nptr )
{
    unsigned int str_pos = 0;
    long int sum = 0;
    // ( [0] * 10 ) + [1] ) * 10 ) + [2] ) * 10 ... last + [n]

    while ( nptr[str_pos] )
    {
        if ( nptr[str_pos] >= '0' && nptr[str_pos] <= '9' )
            sum += nptr[str_pos] - '0';

        if ( nptr[str_pos + 1] >= '0' && nptr[str_pos + 1] <= '9' )
            sum *= 10;

        str_pos++;
    }

    return sum;
}

#ifndef PC

void *
malloc ( unsigned int _size )
{
    unsigned short size, oldsize;
    int i, j;

    if ( !_size || _size > MALLOC_BUF_SIZE )
        return ( NULL );
    while ( malloc_locked )
        asm volatile ( "nop" );
    malloc_locked = 1;

    _size += 7;                 // round up to full block
    size = _size >> 3;          // set block size

    for ( i = 0; i < MALLOC_NUM_BUFS; i++ )
        if ( malloc_ptr[i].used == M_FREE && malloc_ptr[i].size >= size )
            goto malloc_found;

    malloc_locked = 0;
    return ( NULL );            // no free block

  malloc_found:

    if ( malloc_ptr[i].size > size )    // more free space in this block
    {
        oldsize = malloc_ptr[i].size;   // make new block after this one
        malloc_ptr[i].size = size;

        for ( j = 0; j < MALLOC_NUM_BUFS; j++ ) // get free pointer
            if ( malloc_ptr[j].used == M_OLD )
                break;
        if ( j == MALLOC_NUM_BUFS )
        {
            malloc_locked = 0;
            return ( NULL );
        }                       // no free pointer

        malloc_ptr[j].offset = malloc_ptr[i].offset + size;
        malloc_ptr[j].size = oldsize - size;
        malloc_ptr[j].used = M_FREE;

    }

    malloc_ptr[i].used = M_USED;
    malloc_locked = 0;

    return ( ( void * ) ( &malloc_buf[8 * ( unsigned int ) ( malloc_ptr[i].offset )] ) );
}


void
malloc_init ( void )
{
    int i;

    malloc_locked = 1;
    malloc_ptr[0].offset = 0;
    malloc_ptr[0].size = ( unsigned short ) ( MALLOC_BUF_SIZE >> 3 );
    malloc_ptr[0].used = M_FREE;
    for ( i = 1; i < MALLOC_NUM_BUFS; i++ )
        malloc_ptr[i].used = M_OLD;

    malloc_locked = 0;
}

void
free ( void *ptr )
{
    int i, h, j;

    if ( ptr == NULL )
        return;

    malloc_locked = 1;

    for ( i = 0; i < MALLOC_NUM_BUFS; i++ ) // search block 
        if ( malloc_ptr[i].offset == ( unsigned short ) ( ( ( unsigned int ) ptr - ( unsigned int ) &malloc_buf[0] ) >> 3 ) )
            break;
    if ( i == MALLOC_NUM_BUFS || malloc_ptr[i].used != M_USED )
    {
        malloc_locked = 0;
        return;
    }

    malloc_ptr[i].used = M_FREE;

    for ( j = 0; j < MALLOC_NUM_BUFS; j++ )
        if ( malloc_ptr[j].offset == malloc_ptr[i].offset + malloc_ptr[i].size )
        {                       // append next
            if ( malloc_ptr[j].used == M_FREE )
            {
                malloc_ptr[j].used = M_OLD;
                malloc_ptr[i].size += malloc_ptr[j].size;
            }
            break;
        }

    for ( h = 0; h < MALLOC_NUM_BUFS; h++ )
        if ( malloc_ptr[h].offset + malloc_ptr[h].size == malloc_ptr[i].offset )
        {                       // append prev
            if ( malloc_ptr[h].used == M_FREE )
            {
                malloc_ptr[i].used = M_OLD;
                malloc_ptr[h].size += malloc_ptr[i].size;
            }
            break;
        }

    malloc_locked = 0;
    return;
}

#endif
