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


#include <hw/lcd.h>
#include <hw/kpd.h>
#include <hw/flash.h>
#include <core/menu.h>
#include <core/fs.h>
#include <core/lib.h>
//  #define LCD_BUFLEN    (84*48)/8
//extern unsigned char lcd_buf[LCD_BUFLEN];

MENU_CALLBACK ( screenshot_show )
{
    int len = 0;
    unsigned char *buf = NULL;
    FILE *f = NULL;
    MENU_ONLY_SELECT;

    len = lcd_get_bufsize (  );
    buf = ( unsigned char * ) malloc ( len );
    f = fs_fopen ( "screenshot.bin", "r" );
    if ( !f )
        return 0;

    if ( fs_fread ( buf, 1, len, f ) != len )
        return 0;
    fs_fclose ( f );
    lcd_clr (  );
    lcd_to_screen (  );
    memcpy ( ( void * ) lcd_get_buf (  ), buf, lcd_get_bufsize (  ) );
    free ( buf );
    lcd_to_screen (  );
    ksleep ( 5 );

}

void
screenshot_capture ( void )
{
    int len = 0;
    unsigned char *buf = NULL;
    FILE *f = NULL;


    len = lcd_get_bufsize (  );
    buf = ( unsigned char * ) malloc ( len );
    memcpy ( buf, ( void * ) lcd_get_buf (  ), len );
    lcd_clr (  );
    lcd_type_text_2 ( 0, 0 * 8, 3, "  Screenshot", 1 );
    lcd_render_text ( 0, 2 * 8, "- open  -", 1 );
    lcd_to_screen_hw (  );
    f = fs_fopen ( "screenshot.bin", "w" );
    if ( !f )
        return;
    lcd_render_text ( 0, 2 * 8, "- open  -", 0 );
    lcd_to_screen_hw (  );
    lcd_render_text ( 0, 2 * 8, "- write -", 1 );
    lcd_to_screen_hw (  );
    if ( fs_fwrite ( buf, 1, len, f ) != len )
    {
        fs_fclose ( f );
        lcd_type_text_2 ( 0, 4 * 8, 3, "Format FS", 1 );
        lcd_type_text_2 ( 0, 5 * 8, 3, "please", 1 );
    }
    free ( buf );
    lcd_render_text ( 0, 2 * 8, "- write -", 0 );
    fs_fclose ( f );
    lcd_render_text ( 0, 2 * 8, "-  done -", 1 );
    lcd_to_screen_hw (  );
    ksleep ( 1 );

}
