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
#include <core/ui.h>
#include <apps/lgunlock.h>

#ifndef LOADER

int lgunlock_phonetype = 0;
unsigned char lgunlock_phoneimei[32] = "350005203385342";

MENU_CALLBACK ( lgunlock_type )
{
    char *entries[] = { "510W/520", "B1200", "7010/7020", "1300", "G510", NULL };
    int t;

    switch ( cmd )
    {
        case MENU_SELECT:
            t = menu_dropdown ( entries, lgunlock_phonetype );
            if ( t > -1 )
                lgunlock_phonetype = t;
            break;
        case MENU_REDRAW:
        case MENU_DRAW:
            menu_disp ( entries[lgunlock_phonetype] );
            break;
        default:
            break;
    }

}

MENU_CALLBACK ( lgunlock_imei )
{
    MENU_SCROLL_INIT ( 2 );

    switch ( cmd )
    {
        case MENU_SELECT:
            memset ( lgunlock_phoneimei, 0x00, 32 );
            ui_gettext ( "enter IMEI", 15, lgunlock_phoneimei, UI_TYPE_NUMBER );
            break;
        case MENU_REDRAW:
            if ( lgunlock_phoneimei )
            {
                MENU_SCROLL ( lgunlock_phoneimei );
            }
            break;
        case MENU_DRAW:
            MENU_SCROLL_RESET;
            break;
        default:
            break;
    }
}

MENU_CALLBACK ( lgunlock_calc )
{
    unsigned char message[256];

    MENU_ONLY_SELECT;

    memset ( message, 0, 256 );

    lgunlock_algo ( lgunlock_phoneimei, lgunlock_phonetype, message );

    ui_draw_scrolltext ( message );
}

void
lgunlock_algo ( char *imei, unsigned char type, char *output )
{

    // thx to Crux for the information how to build Samsung LG unlock codes and the VB source!

    unsigned char c;

    for ( c = 0; c < 8; c++ )
    {
        output[c] = lgunlock_table_return ( type, c, imei[lib_mod ( c, lgunlock_table_return ( 0, 0, 0, 1 ) ) + lgunlock_table_return ( 0, 0, 0, 2 )] - 0x30, 0 );
    }

}
#endif
