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
#include <hw/kpd.h>
#include <core/menu.h>
#include <core/ui.h>
#include <hw/lcd.h>

unsigned char pp_col = 1;
unsigned char pp_style = 0;
unsigned char quit = 0;

MENU_CALLBACK ( picpaint_style_px )
{
    MENU_ONLY_SELECT;
    pp_style = 0;
    return MENU_EXIT;
}

MENU_CALLBACK ( picpaint_style_line )
{
    MENU_ONLY_SELECT;
    pp_style = 1;
    return MENU_EXIT;
}

MENU_CALLBACK ( picpaint_style_rect )
{
    MENU_ONLY_SELECT;
    pp_style = 2;
    return MENU_EXIT;
}

MENU_CALLBACK ( picpaint_col_bl )
{
    MENU_ONLY_SELECT;
    pp_col = 1;
    return MENU_EXIT;
}

MENU_CALLBACK ( picpaint_col_wh )
{
    MENU_ONLY_SELECT;
    pp_col = 0;
    return MENU_EXIT;
}

MENU_CALLBACK ( picpaint_col_in )
{
    MENU_ONLY_SELECT;
    pp_col = 2;
    return MENU_EXIT;
}

MENU_CALLBACK ( picpaint_show_screen )
{
    MENU_ONLY_SELECT;
    return MENU_EXIT;
}

MENU_CALLBACK ( picpaint_safe_pic )
{
    MENU_ONLY_SELECT;
    return MENU_EXIT;
}

MENU_CALLBACK ( picpaint_safe_screen )
{
    MENU_ONLY_SELECT;
    return MENU_EXIT;
}

MENU_CALLBACK ( picpaint_help )
{
    MENU_ONLY_SELECT;
    ui_draw_scrolltext ( "Use PicPaint to create custom pics. MenuKey brings up this menu. Keys 2, 4, 6, 8 are arrowkeys and move your cursor." );
}

MENU_CALLBACK ( picpaint_quit )
{
    MENU_ONLY_SELECT;
    quit = 1;
    return MENU_EXIT;
}

void
picpaint_main ( void )
{

    unsigned char cursor_x = 84 / 2;
    unsigned char cursor_y = 48 / 2;

    unsigned char pos_x_start = 84 / 2;
    unsigned char pos_y_start = 48 / 2;

    unsigned char to_pic = 1;

    unsigned char key;

    unsigned char *lcd_buf_backup = NULL;
    unsigned char *lcd_buf = NULL;

    lcd_buf_backup = ( unsigned char * ) malloc ( lcd_get_bufsize (  ) );
    lcd_buf = ( void * ) lcd_get_buf (  );

    menupoint menu[] = {
        {MENU_T_LIST, 6, NULL, NULL, "Menu"},
        {MENU_T_LIST, 3, NULL, NULL, "Style"},
        {0, 0, picpaint_style_px, NULL, "Pixel"},
        {0, 0, picpaint_style_line, NULL, "Line"},
        {0, 0, picpaint_style_rect, NULL, "Rectangle"},
        {MENU_T_LIST, 3, NULL, NULL, "Color"},
        {0, 0, picpaint_col_bl, NULL, "Black"},
        {0, 0, picpaint_col_wh, NULL, "White"},
        {0, 0, picpaint_col_in, NULL, "Invert"},
        {0, 0, picpaint_show_screen, NULL, "Show Pic"},
        {0, 0, picpaint_safe_screen, NULL, "Safe Pic"},
        {0, 0, picpaint_help, NULL, "Help"},
        {0, 0, picpaint_quit, NULL, "Quit"},
        {MENU_T_LIST, 0, NULL, NULL, NULL}
    };

    quit = 0;
    pp_col = 1;
    pp_style = 0;


    kpd_wait_release (  );
    lcd_clr (  );
    // initialize a blank screen

    // save pic-screen
    memcpy ( lcd_buf_backup, lcd_buf, lcd_get_bufsize (  ) );

    do
    {

        kpd_wait_release (  );
        key = kpd_getkey (  );
        switch ( key )
        {
            case KPD_SOFTBTN1:
                menu_show ( menu );
                break;
            case 2:
                if ( cursor_x )
                    cursor_x--;
                break;
            case 4:
                if ( cursor_y )
                    cursor_y--;
                break;
            case 5:
                /*
                 * if ( to_pic )
                 * if ( !pp_style )
                 * lcd_set_pixel
                 */
                break;
            case 6:
                if ( cursor_y < 47 )
                    cursor_y++;
                break;
            case 8:
                if ( cursor_x < 83 )
                    cursor_x++;
                break;
            case 0xFF:
            default:
                break;
        }

        memcpy ( lcd_buf, lcd_buf_backup, lcd_get_bufsize (  ) );

        switch ( pp_style )
        {
            case 0:            //px
                lcd_draw_line ( cursor_x - 2, cursor_y, cursor_x + 2, cursor_y, 2 );
                lcd_draw_line ( cursor_x, cursor_y - 2, cursor_x, cursor_y + 2, 2 );
                break;
            case 1:            //line
                lcd_draw_line ( pos_x_start, pos_y_start, cursor_x, cursor_y, 2 );
                break;
            case 2:            //rect
                lcd_draw_rect ( pos_x_start, pos_y_start, cursor_x, cursor_y, 2 );
                break;
            default:
                break;
        }

        lcd_to_screen (  );

    }
    while ( !quit );

}
