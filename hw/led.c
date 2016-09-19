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

#include <hw/phoneinfo.h>

#include <hw/io.h>
#include <hw/int.h>


void
led_set ( int enable )
{
    if ( enable )
    {
        switch ( mados_info[mados_phone].led )
        {
            case 0:
                _io_set_bit ( IO_UIF_CTRL3, UIF_CTRL3_LED );
                if ( mados_info[mados_phone].kpd_led )
                {
                    _io_set_bit ( IO_PUP_DIR, PUP_GENIO_DISP );
                    _io_set_bit ( IO_PUP_GENIO, PUP_GENIO_DISP );
                }
                break;
            case 1:
                _io_set_bit ( IO_UIF_CTRL3, UIF_CTRL3_LED2 );
                break;
            case 2:
                _io_set_bit ( IO_PUP_DIR, PUP_GENIO_LED );
                _io_set_bit ( IO_PUP_GENIO, PUP_GENIO_LED );
                break;
        }
    }
    else
    {
        switch ( mados_info[mados_phone].led )
        {
            case 0:
                _io_clr_bit ( IO_UIF_CTRL3, UIF_CTRL3_LED );
                if ( mados_info[mados_phone].kpd_led )
                {
                    _io_set_bit ( IO_PUP_DIR, PUP_GENIO_DISP );
                    _io_clr_bit ( IO_PUP_GENIO, PUP_GENIO_DISP );
                }
                break;
            case 1:
                _io_clr_bit ( IO_UIF_CTRL3, UIF_CTRL3_LED2 );
                break;
            case 2:
                _io_set_bit ( IO_PUP_DIR, PUP_GENIO_LED );
                _io_clr_bit ( IO_PUP_GENIO, PUP_GENIO_LED );
                break;
        }
    }
    return;
}

// speed 0-7:    0 - fast, 7 - slow
void
led_fade_out ( int speed )
{
    int i;
    int j;
    int spd;

    if ( !speed )
    {
        led_set ( 0 );
        return;
    }

    speed %= 8;
    spd = 1 << ( 8 - speed );

    int_disable (  );

    j = 4096;
    while ( j )
    {
        i = 4096 - j;
        led_set ( 1 );
        usleep ( j );
        led_set ( 0 );
        usleep ( i );
        j -= spd;
    }

    int_enable (  );

    return;
}

// speed 0-7:    0 - fast, 7 - slow
void
led_fade_in ( int speed )
{
    int i;
    int j;
    int spd;

    if ( !speed )
    {
        led_set ( 1 );
        return;
    }

    speed %= 8;
    spd = 1 << ( 8 - speed );

    j = 4096;
    while ( j )
    {
        i = 4096 - j;
        led_set ( 0 );
        usleep ( j );
        led_set ( 1 );
        usleep ( i );
        j -= spd;
    }
    return;
}
