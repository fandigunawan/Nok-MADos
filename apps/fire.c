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


#include <core/lib.h>
#include <apps/fire.h>
#include <hw/kpd.h>


#define XSIZ 84
#define YSIZ 48
#define MAXTABLE (256*5)
#define MA 5
#define END (bitmap + XSIZ * YSIZ)
#define min(x,y) ((x)<(y)?(x):(y))

#ifndef LOADER

static unsigned char bitmap[XSIZ * YSIZ * 2];
static unsigned int table[MAXTABLE];
static int loop;
static int sloop;
static int height;




static void
fire_gentable ( void )
{
    unsigned int i, p2;
    int minus = 3;

    if ( minus == 0 )
        minus = 1;
    for ( i = 0; i < MAXTABLE; i++ )
    {
        if ( i > minus )
        {
            p2 = lib_div ( ( i - minus ), 5 );
            table[i] = p2;
        }
        else
            table[i] = 0;
    }
}

static void
fire_calc ( void )
{
    unsigned char *p;
    unsigned char val;
    int i = 0;

    for ( p = bitmap; p <= END; p += 1 )
    {
        val = table[( *( p + XSIZ - 1 ) + *( p + XSIZ + 1 ) + *( p + XSIZ ) ) + ( *( p + 2 * XSIZ - 1 ) + *( p + 2 * XSIZ + 1 ) )];
        *p = val;
    }
}

void
fire_draw ( void )
{
    unsigned int i, last1, i1, i2;
    register unsigned char *p;

    height++;
    loop--;

    if ( loop < 0 )
        loop = lib_mod ( lib_rand ( height ), 3 ), sloop++;

    i1 = 1;
    i2 = 4 * XSIZ + 1;

    for ( p = END - 2 * XSIZ; p < END; p++ )
    {
        i1 += 4;
        i2 -= 4;
        last1 = lib_mod ( lib_rand ( height ), min ( i1, min ( i2, height ) ) );
        i = lib_mod ( lib_rand ( last1 ), 6 );
        for ( ; p < END && i != 0; p++ )
        {
            i--;
            i1 += 4;
            i2 -= 4;
            *p = last1;
            last1 += lib_mod ( lib_rand ( last1 ), 6 ) - 2;
            *( p + XSIZ ) = last1;
            last1 += lib_mod ( lib_rand ( last1 ), 6 ) - 2;
        }
        *( p + 2 * XSIZ ) = last1;
        last1 += lib_mod ( lib_rand ( last1 ), 6 ) - 2;
    }

    i = 0;
    fire_calc (  );

    lcd_render_bitmap ( 0, 0, 84, 48, bitmap, 3 );
    lcd_to_screen (  );
}

int
fire_main ( int doloop )
{
    int i = 0;


    loop = 0;
    sloop = 0;
    height = 0;
    lcd_clr (  );

    fire_gentable (  );
    memset ( bitmap, 0x00, XSIZ * YSIZ * 2 );

    kpd_wait_release (  );
    while ( doloop && kpd_getkey (  ) == 0xFF )
    {
        fire_draw (  );
    }
}

#endif
