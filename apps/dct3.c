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
#include <apps/dct3.h>

#ifndef LOADER
/*
int dct3_phonetype = 0;
int dct3_version = 2;
*/
unsigned char dct3_phoneimei[32] = "350005203385342";
unsigned char dct3_phoneprov[32] = "26201";
//unsigned char *dct3_serial[] = { /* V1 */ "\x03\x02\x08\x02\x00", /* V2 */ "\x03\x03\x08\x02\x00", /* V3 */ "\x03\x03\x05\x05\x02", /* Gn */ "\x4D\x0F\xF9\xE8\x97", /* Go */ "\x03\x02\x08\x01\x09" };
/*
MENU_CALLBACK ( dct3_type )
{
    char *entries[] = { "ASIC v2", "ASIC v5", "ASIC v7", NULL };
    int t;

    switch ( cmd )
    {
        case MENU_SELECT:
            t = menu_dropdown ( entries, dct3_phonetype );
            if ( t > -1 )
                dct3_phonetype = t;
            break;
        case MENU_REDRAW:
        case MENU_DRAW:
            menu_disp ( entries[dct3_phonetype] );
            break;
        default:
            break;
    }

}


MENU_CALLBACK ( dct3_selversion )
{
    char *entries[] = { "v1", "v2", "v3", "Grif new", "Grif old", NULL };
    int t;

    switch ( cmd )
    {
        case MENU_SELECT:
            t = menu_dropdown ( entries, dct3_version );
            if ( t > -1 )
                dct3_version = t;
            break;
        case MENU_REDRAW:
        case MENU_DRAW:
            menu_disp ( entries[dct3_version] );
            break;
        default:
            break;
    }

}
*/

MENU_CALLBACK ( dct3_imei )
{
    MENU_SCROLL_INIT ( 2 );
//    static int pos = 0;
//    static int cnt = 2;
//    static int dir = 0;
//    char str[20];
//    char buf[64];

    switch ( cmd )
    {
        case MENU_SELECT:
            memset ( dct3_phoneimei, 0x00, 32 );
            ui_gettext ( "enter IMEI", 15, dct3_phoneimei, UI_TYPE_NUMBER );
            break;
        case MENU_REDRAW:
            if ( dct3_phoneimei )
            {
                MENU_SCROLL ( dct3_phoneimei );
/*		sprintf ( buf, "  %s  ", dct3_phoneimei );
		if ( strlen ( buf )>= 13 )
		{
        	    if ( (pos >= strlen ( buf ) - 13 && !dir) || (!pos && dir) )
		    {
			if ( dir )
			    dir = 0;
			else
			    dir = 1;
		    }
		    memcpy ( str, ( unsigned char * ) ( ( unsigned long ) ( buf ) + pos ), 13 );
        	    str[13] = '\n';
        	    str[14] = 0x00;
		    if ( !(cnt--) )
		    {
			cnt = 2;
			if ( !dir )
			    pos++;
			else 
			    pos--;
		    }
            	    menu_disp ( str );
		}
		else
            	    menu_disp ( buf );*/
            }
            break;
        case MENU_DRAW:
            MENU_SCROLL_RESET;
//      pos = 0;
//      cnt = 2;
            break;
        default:
            break;
    }
}

MENU_CALLBACK ( dct3_prov )
{
    switch ( cmd )
    {
        case MENU_SELECT:
            memset ( dct3_phoneprov, 0x00, 32 );
            ui_gettext ( "enter Provider", 5, dct3_phoneprov, UI_TYPE_HEX );
            break;
        case MENU_REDRAW:
        case MENU_DRAW:
            if ( dct3_phoneprov )
                menu_disp ( dct3_phoneprov );
            break;
        default:
            break;
    }
}

MENU_CALLBACK ( dct3_calc )
{
    unsigned char *message;
    unsigned char *code;
    int i = 0;

    MENU_ONLY_SELECT;

    lcd_clr (  );

    for ( i = 84; i >= 0; i-- )
    {
        lcd_render_text ( i, 20, "[Nok5Rev]", 1 );
        lcd_to_screen_hw (  );
        usleep ( 50000 );
        lcd_render_text ( i, 20, "[Nok5Rev]", 0 );
    }
    usleep ( 500000 );
    lcd_render_text ( 0, 20, "[Nok5Rev]", 1 );
    lcd_render_text ( 64, 20, "thx", 1 );
    lcd_to_screen_hw (  );
    usleep ( 500000 );
    lcd_render_text ( 64, 20, "thx", 0 );
    lcd_to_screen_hw (  );
    usleep ( 500000 );


    code = ( char * ) malloc ( 32 );
    message = ( char * ) malloc ( 256 );
    memset ( code, 0, 32 );
    memset ( message, 0, 256 );

    dct3algo_main ( dct3_phoneimei, dct3_phoneprov, code );
    strcat ( message, code );   // skip the first zero
    strcat ( message, " " );

    ui_draw_scrolltext ( message );
    free ( code );
    free ( message );
}

#endif
