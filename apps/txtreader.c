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

#include <hw/kpd.h>
#include <hw/lcd.h>
#include <core/menu.h>
#include <core/lib.h>
#include <apps/txtreader.h>
#include <core/bitmap.h>

#ifndef LOADER

unsigned char stringg[] =
    "\x00 anke se nn mi va proprio lopment environment for creating own demos or even games and applications for a 3310/3330 phone like krisha and i made. therein is everything u need to compile your own flash... (compiler, editor, tools) the code is plain C and no, you can NOT inject this code into nokia software with this package...  ;)  thanx to N-GAGE for the webspace... http://geggo.j2me-world.de/MADos.exe http://geggo.j2me-world.de/MADos.zip  how to proceed: - run MADos.exe and decompress to D:\\ - run cygwin_d.reg - now run the .bat in the cygwin dir  you should see the bash shell... try to run mc a norton commander clone.. with this tool you can edit your C code with syntax hilghlighting if u want to decompress it to C:\\ u have to run the cygwin_c.reg AND edit the .bat to fit the pathes  then decompress MADos.zip in your home directory and have phun to compile, you have to run the compile script  if you cannot manage the installation, then you are probably not the right one for this development environment, sorry.... if you have some problems with cygwin, please contact a friend who knows a little about linux.. he will know how to help! my mailbox is surely not the right place to ask about things like that!  pw is: pic16f87    have phun!   ";

MENU_CALLBACK ( main_txtreader )
{
    unsigned char *curr_pos, *prev_pos, *tmp, key;
    MENU_ONLY_SELECT;


    lcd_set_font ( FONT_DYNAMIC );
    curr_pos = stringg + 1;
    prev_pos = stringg + sizeof ( stringg ) - 2;
    curr_pos = txtreader_print ( curr_pos, 0 );
    while ( 1 )
    {


        kpd_wait_release_x ( 200 );
        do
        {
            key = kpd_getkey (  );
        }
        while ( key == 0xFF );

        switch ( key )
        {
            case KPD_UPARROW:
                curr_pos = prev_pos + 1;
                if ( !( prev_pos = txtreader_print ( prev_pos, 1 ) ) )
                    prev_pos = stringg + sizeof ( stringg ) - 2;
                break;

            case KPD_DWNARROW:
                prev_pos = curr_pos - 1;
                if ( !( curr_pos = txtreader_print ( curr_pos, 0 ) ) )
                    curr_pos = stringg + 1;
                break;

            case KPD_CANCEL:
                return;
                break;

            case KPD_SOFTBTN1:
                //menu_show ( txt_mainmenu );
                break;
        }


    }
}

unsigned char *
txtreader_print ( unsigned char *pos, const unsigned char direction )
{
    unsigned char k, *buf;

    lcd_clr (  );
    buf = ( unsigned char * ) malloc ( 24 );

    if ( !direction )
    {
        for ( k = 0; k < 5; k++ )
        {
            unsigned char xpos = 0;

            while ( *pos && xpos <= 79 )
            {
                if ( xpos == 0 && *pos == 0x20 ) ;
                else if ( *pos == 0x20 )
                    xpos += 3;
                else
                    xpos += lcd_render_char_x ( xpos, k * 8 - 1, *pos, 1 );
                pos++;
            }

        }
    }
    else
    {
        for ( k = 5; k > 0; k-- )
        {
            unsigned char xpos = 0, j = 0;

            memset ( buf, 0, 24 );
            while ( *pos && xpos <= 79 )
            {
                buf[j++] = *pos;

                if ( *pos == 0x20 )
                    xpos += 3;
                else
                    xpos += lcd_get_char_width ( *pos );
                pos--;
            }
            if ( buf[j] == 0x20 )
            {
                buf[j] = *pos++;
            }
            xpos = 0;
            //strrev( buf );
            //lcd_render_text ( 0, (k - 1) * 8 , (unsigned char*) strrev( buf ), 1 );
            while ( *buf )
            {
                if ( *buf == 0x20 )
                    xpos += 3;
                else
                    xpos += lcd_render_char_x ( xpos, ( k - 1 ) * 8 - 1, *buf, 1 );
                buf++;
            }

        }
    }
    lcd_render_text ( 42 - 3 * sizeof ( "Options" ), 40, "Options", 1 );
    lcd_to_screen (  );
    free ( buf );
    if ( *pos )
        return pos;
    else
        return 0;
}

#endif
