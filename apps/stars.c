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

#ifndef LOADER
#include "hw/lcd.h"
#include "hw/kpd.h"
#include "core/lib.h"
#include <core/softfloat.h>
#include "apps/stars.h"
#include "hw/ccont.h"

#define MAX_STARS 30
#define MAX_STARFIELD 100

typedef struct
{
    float32 x;
    float32 y;
    float32 z;
}
starfield_t;

unsigned char *img_stars[] = {
    "X",

    "XX" "XX",

    //" XX "
    //"XXXX"
    //"XXXX"
    //" XX ",
    " X " "XXX" " X ",
    NULL
};

const int img_stars_x[3] = {
    1,
    2,
    3,
};

const int img_stars_y[3] = {
    1,
    2,
    3,
};

void
stars_main ( void )
{
    star_t stars[MAX_STARS + 1];
    int i;

    kpd_wait_release (  );

    for ( i = 0; i < MAX_STARS; i++ )
    {
        stars[i].x = lib_mod ( lib_rand ( 5 ), 84 * 4 );
        stars[i].y = lib_mod ( lib_rand ( 5 ), 48 * 4 );
        stars[i].ebene = lib_mod ( lib_rand ( 5 ), 3 );
    }

    while ( kpd_getkey (  ) == 0xff )
    {
        lcd_clr (  );
        lcd_fill ( 0xff );
        for ( i = 0; i < MAX_STARS; i++ )
        {
            stars[i].x += stars[i].ebene + 1;

            if ( stars[i].x >= 84 * 4 )
            {
                stars[i].x = 0;
                stars[i].y = lib_mod ( lib_rand ( 5 ), 48 * 4 );
                stars[i].ebene = lib_mod ( lib_rand ( 5 ), 3 );
            }

            //lcd_set_pixel ( stars[i].x / 4, stars[i].y / 4, 1 );
            lcd_render_bitmap ( stars[i].x / 4, stars[i].y / 4, img_stars_x[stars[i].ebene], img_stars_y[stars[i].ebene], img_stars[stars[i].ebene], 0 );
        }
        lcd_to_screen (  );
        usleep ( 100000 );
    }


}

int
_3Dto2D ( float32 x, float32 y, float32 z, unsigned char *sx, unsigned char *sy )
{
    float32 eye_z;
    if ( !float32_to_int32 ( z ) )
        return 1;

    eye_z = int32_to_float32 ( 60 );

    *sx = float32_to_int32 ( float32_add ( int32_to_float32 ( 42 ), float32_div ( float32_mul ( x, eye_z ), float32_add ( z, eye_z ) ) ) );
    *sy = float32_to_int32 ( float32_sub ( int32_to_float32 ( 24 ), float32_div ( float32_mul ( y, eye_z ), float32_add ( z, eye_z ) ) ) );
        /**a = eye.x + x * eye.z / (z + eye.z) ;
        *b = eye.y - y * eye.z / (z + eye.z) ;*/

    return 0;

}

/* floats not really needed here, but should be a practicle example and test and could be extended */
void
starfield_main ( void )
{
    starfield_t stars[MAX_STARFIELD + 1];
    int i;
    unsigned char x, y;

    kpd_wait_release (  );
    for ( i = 0; i < MAX_STARFIELD; i++ )
    {
        stars[i].x = int32_to_float32 ( ( lib_mod ( lib_rand ( i ), 2 ) ? -1 : 1 ) * lib_mod ( lib_rand ( i ), 50 ) );
        stars[i].y = int32_to_float32 ( ( lib_mod ( lib_rand ( i ), 2 ) ? -1 : 1 ) * lib_mod ( lib_rand ( i ), 50 ) );
        stars[i].z = int32_to_float32 ( lib_mod ( lib_rand ( i ), 100 ) );
    }

    while ( kpd_getkey (  ) == 0xFF )
    {
        lcd_clr (  );
        lcd_fill ( 0xFF );
        for ( i = 0; i < MAX_STARFIELD; i++ )
        {
            if ( float32_to_int32 ( stars[i].z ) <= 0 )
            {
                stars[i].x = int32_to_float32 ( ( lib_mod ( lib_rand ( i ), 2 ) ? -1 : 1 ) * lib_mod ( lib_rand ( i ), 50 ) );
                stars[i].y = int32_to_float32 ( ( lib_mod ( lib_rand ( i ), 2 ) ? -1 : 1 ) * lib_mod ( lib_rand ( i ), 50 ) );
                stars[i].z = int32_to_float32 ( 100 );
            }
            else
                stars[i].z = float32_sub ( stars[i].z, int32_to_float32 ( 5 ) );
            _3Dto2D ( stars[i].x, stars[i].y, stars[i].z, &x, &y );
            lcd_set_pixel ( x, y, 0 );
        }
        lcd_to_screen (  );
        //usleep ( 1000 );
        //damn, is the CPU slow :( what about 3D games now ?! maybe without floats :(
    }
}

#endif
