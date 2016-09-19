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

int lib_rand ( int seed );
void lib_init_rand ( int seed );
//long modsi3 ( unsigned long numerator, unsigned long denominator ); //damn left this, because : apps/dct3algo_ARM.o: In function `dct3algo_reverse_bytes': 
long __umodsi3 ( unsigned long numerator, unsigned long denominator );
long __modsi3 ( unsigned long numerator, unsigned long denominator );
//long divsi3 ( unsigned long numerator, unsigned long denominator );
long __udivsi3 ( unsigned long numerator, unsigned long denominator );
long __divsi3 ( unsigned long numerator, unsigned long denominator );
//float32 __divsi3 ( float32 numerator, float32 denominator );
unsigned int inline usleep ( unsigned int delay );
unsigned int volatile sleep ( unsigned int delay );
unsigned int volatile sleep2 ( unsigned int delay );
unsigned int ksleep ( unsigned int delay );
unsigned int kmsleep ( unsigned int delay );
void lib_hexconv ( char *buf, int val );
void lib_phexconv ( char *buf, int *val );
void lib_dtoa ( char *buf, unsigned int val, unsigned int max_length, unsigned char no_leading_zero );
unsigned int lib_get_time ( void );
int lib_abs ( int fullint );
long int atol ( const char *nptr );


#ifndef PC
unsigned int strlen ( const char *s );
char *strcpy ( char *dest, const char *src );
int strcmp ( const char *str1, const char *str2 );
void *memset ( void *s, int c, unsigned long len );
int strncmp ( const char *str1, const char *str2, unsigned long n );
void *memcpy ( void *d, const void *s, unsigned long n );
int memcmp ( const void *s1, const void *s2, unsigned long n );
#endif

#define lib_div __divsi3
#define lib_mod __modsi3


#define NULL (void*)0x00000000

//float big-endian
#define PI 0x40490FDB

#define MIN(a,b) a>b?b:a
#define MAX(a,b) a>b?a:b

#ifndef PC
void *malloc ( unsigned int _size );
void free ( void *ptr );
void malloc_init ( void );

typedef struct
{
    unsigned short offset;
    unsigned short size;
    unsigned char used;
}
malloc_pointer;

#define M_FREE 0
#define M_USED 1
#define M_OLD  2

#if defined (LOADER) || defined (PHONE_5110)
#define MALLOC_BUF_SIZE (1*256)
#define MALLOC_NUM_BUFS (64)
#else
#define MALLOC_BUF_SIZE (64*1024)
#define MALLOC_NUM_BUFS (512)
#endif

#endif
