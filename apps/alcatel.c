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
#include <apps/alcatel.h>

#ifndef LOADER

// Alcatel code list by Crux

int alcatel_phonetype = 0;

MENU_CALLBACK ( alcatel_type )
{
    char *entries[] = { "HD1/HE1", "BE1/BE3", "BE4/BE5/BFx", NULL };
    int t;

    switch ( cmd )
    {
        case MENU_SELECT:
            t = menu_dropdown ( entries, alcatel_phonetype );
            if ( t > -1 )
                alcatel_phonetype = t;
            break;
        case MENU_REDRAW:
        case MENU_DRAW:
            menu_disp ( entries[alcatel_phonetype] );
            break;
        default:
            break;
    }

}

MENU_CALLBACK ( alcatel_inst )
{
    MENU_ONLY_SELECT;

    ui_draw_scrolltext ( "Check model under the battery of your alcatel. Select phone model and see the code. Press * and 787292 at same time and then enter the code." );

}

MENU_CALLBACK ( alcatel_code )
{
    MENU_ONLY_SELECT;

    if ( alcatel_phonetype == 0 )
    {
        ui_draw_scrolltext ( "25228353" );
    }

    if ( alcatel_phonetype == 1 )
    {
        ui_draw_scrolltext ( "25228352" );
    }

    if ( alcatel_phonetype == 2 )
    {
        ui_draw_scrolltext ( "83227423" );
    }

}

#endif
