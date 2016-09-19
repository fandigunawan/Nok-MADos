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

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed char s8;
typedef signed short s16;
typedef signed long s32;


#define AR_SIZE(arr)   (sizeof(arr)/sizeof(arr[0]))

#define min(a, b)   (((a) < (b))? (a): (b))
#define max(a, b)   (((a) > (b))? (a): (b))

// Physical Chip Specific Addresses
#define ARM_API_MEM_START   (0x10000)
#define DSP_API_MEM_START   (0x0800)

// A helper macro to convert a DSP API address into an ARM API address.
// Note that DSP adresses are in words while ARM addresses are in bytes
#define MAP_DSP_TO_ARM(dsp_address)     (ARM_API_MEM_START + (dsp_address - DSP_API_MEM_START) * 2)

#define DSP_PRG_START_ADDR      ((volatile ushort*)MAP_DSP_TO_ARM(0x0f00))
#define DSP_READ_ADDR           ((volatile ushort*)MAP_DSP_TO_ARM(0x0e0f))

#define BIT_0       0x0001
#define BIT_1       0x0002
#define BIT_2       0x0004
#define BIT_3       0x0008
#define BIT_4       0x0010
#define BIT_5       0x0020
#define BIT_6       0x0040
#define BIT_7       0x0080
#define BIT_8       0x0100
#define BIT_9       0x0200
#define BIT_10      0x0400
#define BIT_11      0x0800
#define BIT_12      0x1000
#define BIT_13      0x2000
#define BIT_14      0x4000
#define BIT_15      0x8000

#include <apps/dspread.h>
#include <apps/dspcode.h>
#include <core/lib.h>

void
delay_ms ( uint n )
{
    int i;
    for ( i = 0; i < n; i++ )
        delay ( 475 );
}

void
fatal_error ( void )
{
    for ( ;; )
    {
    }
}

int nbig_cycles, nsmall_cycles;

void
delay_cycles_prepare ( int n )
{
    nbig_cycles = lib_div ( n, 24 );
    nsmall_cycles = lib_div ( n, 24 );
}

void
delay_cycles ( void )
{
    switch ( nsmall_cycles )
    {
        case 23:
            delay_23 ( nbig_cycles );
            break;
        case 22:
            delay_22 ( nbig_cycles );
            break;
        case 21:
            delay_21 ( nbig_cycles );
            break;
        case 20:
            delay_20 ( nbig_cycles );
            break;
        case 19:
            delay_19 ( nbig_cycles );
            break;
        case 18:
            delay_18 ( nbig_cycles );
            break;
        case 17:
            delay_17 ( nbig_cycles );
            break;
        case 16:
            delay_16 ( nbig_cycles );
            break;
        case 15:
            delay_15 ( nbig_cycles );
            break;
        case 14:
            delay_14 ( nbig_cycles );
            break;
        case 13:
            delay_13 ( nbig_cycles );
            break;
        case 12:
            delay_12 ( nbig_cycles );
            break;
        case 11:
            delay_11 ( nbig_cycles );
            break;
        case 10:
            delay_10 ( nbig_cycles );
            break;
        case 9:
            delay_9 ( nbig_cycles );
            break;
        case 8:
            delay_8 ( nbig_cycles );
            break;
        case 7:
            delay_7 ( nbig_cycles );
            break;
        case 6:
            delay_6 ( nbig_cycles );
            break;
        case 5:
            delay_5 ( nbig_cycles );
            break;
        case 4:
            delay_4 ( nbig_cycles );
            break;
        case 3:
            delay_3 ( nbig_cycles );
            break;
        case 2:
            delay_2 ( nbig_cycles );
            break;
        case 1:
            delay_1 ( nbig_cycles );
            break;
        case 0:
            delay ( nbig_cycles );
            break;
        default:
            fatal_error (  );
    }
}

int
dspread_main ( void )
{
    int i = 0;
    unsigned short *dest;
    volatile unsigned short *p;


    *( volatile char * ) 0x20002 = 0;
    delay ( 100 );

    p = DSP_PRG_START_ADDR;
    for ( i = 0; i < AR_SIZE ( dspread_boot_table ); i++ )
    {
        *p++ = dspread_boot_table[i];
    }

    p = DSP_READ_ADDR;
    dest = ( unsigned short * ) 0x00102000;
    for ( i = 0; i < 256; i++ )
        dest[i] = 0;
    *p = 0x5555;

    int cycles = 16 * 24 + 6;   // + 0x9000 * 4;
    for ( i = 0; i < 256; i++ )
    {
        delay_cycles_prepare ( cycles );
        *( volatile char * ) 0x20002 = 1;
        delay_cycles (  );
        *( volatile char * ) 0x20002 = 0;
        cycles += 1;
        *dest++ = *p;
    }

    for ( ;; )
    {
    }
}
