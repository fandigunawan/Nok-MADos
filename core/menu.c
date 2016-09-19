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
#include <hw/lcd.h>
#include <core/menu.h>

#define MENU_DIR_NONE   0
#define MENU_DIR_PREV   1
#define MENU_DIR_NEXT   2
#define MENU_DIR_FADU   3
#define MENU_DIR_FADL   4


int
menu_findnext_mp ( menupoint * menu )
{
    int i;
    int sum = 1;

    if ( menu[0].num == 0 )
        return 1;
    for ( i = 0; i < menu[0].num; i++ )
        sum += menu_findnext_mp ( &menu[sum] );
    return sum;

}

void
menu_newprint ( menupoint * menu, unsigned char *helper, int pos, int first )
{
    int i;
    int state = 0;
    char buf[16];
    unsigned long last;

    lcd_clr (  );
    const unsigned char slid[] = {
        0x41, 0x41, 0x3E
    };
    bitmap_t bmp_slider = { 3, 7, slid };
    unsigned int eq = lib_mod ( lib_div ( 24, menu[0].num - 1 ), 24 );
    lcd_draw_line ( 81, 9, 81, 40, 1 );
    lcd_draw_bitmap ( 81, ( ( pos ) * eq ) + 9, &bmp_slider );
    sprintf ( buf, "%d", eq );
    // lcd_render_text( 0, 0, buf, 1);



    lcd_set_font ( 0 );
    lcd_fontsettings ( FONT_SIZED );

    // lcd_draw_text( 84 -  getwidth( "Select" )/ 2, 40, "Select", 1 );
    lcd_set_font ( 2 );
    lcd_render_text ( ( 84 - lcd_get_text_width ( "Select" ) ) / 2, 40, "Select", 1 );
    //lcd_render_text ( 84 - lcd_get_text_width("Select") / 2, 40,"Select", 1);
    //lcd_set_font ( 0 );
    sprintf ( buf, "%d", pos + 1 );
    lcd_render_text_ml ( 83, 0, buf, 1, AL_RIGHT );
    lcd_set_font ( 0 );


    switch ( menu[0].type & 0x0F )
    {
        case MENU_T_BMAP:      //Menu with BMP
            if ( menu[helper[pos]].bmp )
                lcd_draw_bitmap ( -1, 23, menu[helper[pos]].bmp );
            lcd_set_font ( 3 );
            if ( menu[helper[pos]].text )
                //  lcd_set_font ( 2 );
                lcd_render_text ( ( 84 - lcd_get_text_width ( menu[helper[pos]].text ) ) / 2, 8, menu[helper[pos]].text, 1 );
            //  lcd_render_text ( 39 - 4 * strlen ( menu[helper[pos]].text ), 8, menu[helper[pos]].text, 1 );
            lcd_set_font ( 0 );
            break;
        case MENU_T_FIELD:     //Menu
            if ( menu[0].text )
            {
                memset ( buf, 0, 16 );
                memcpy ( buf, menu[0].text, 10 );
                i = 41 - 3 * strlen ( buf );
                lcd_render_text ( i, 0, buf, 1 );
                lcd_draw_line ( 0, 4, i - 6, 4, 1 );
                lcd_draw_line ( 81 - i + 4, 4, 70, 4, 1 );
            }

            lcd_set_font ( 2 );
            if ( menu[helper[pos]].text )
                lcd_render_text_ml ( 0, 10, menu[helper[pos]].text, 1, 0 );
            if ( menu[helper[pos]].function )
                ( *menu[helper[pos]].function ) ( MENU_REDRAW, 0 );
            lcd_set_font ( 0 );
            break;
        case MENU_T_STATE:     //Menu with on/off
            if ( menu[helper[pos]].text )
                lcd_render_text_ml ( 0, 10, menu[helper[pos]].text, 1, 0 );
            if ( menu[helper[pos]].function )
            {
                state = ( *menu[helper[pos]].function ) ( MENU_GETSTATE, 0 );
                if ( state )
                    menu_disp ( "On" );
                else
                    menu_disp ( "Off" );
            }
            else
                menu_disp ( "ERR" );
            break;
        case MENU_T_LIST:
            last = kpd_getlast (  );
            if ( menu[0].text )
            {
                memset ( buf, 0, 16 );
                memcpy ( buf, menu[0].text, 10 );
                i = 41 - 3 * strlen ( buf );
                lcd_render_text ( i, 0, buf, 1 );
                lcd_draw_line ( 0, 4, i - 6, 4, 1 );
                lcd_draw_line ( 81 - i + 4, 4, 70, 4, 1 );
            }

            lcd_draw_rect ( 0, ( pos - first + 1 ) * 10, 78, ( ( pos - first + 1 ) + 1 ) * 10 - 1, 1 );

            static int vpos = 0;

            i = 0;
            while ( i < menu[0].num && i < 3 )
            {

                lcd_set_font ( 2 );
#ifndef PC
                if ( lcd_get_text_width ( menu[helper[lib_mod ( i + first, menu[0].num )]].text ) > 75 && i == ( pos - first ) )
                {
                    char str[13];
                    while ( kpd_getlast (  ) == last )
                    {
                        lcd_draw_rect ( 0, ( pos - first + 1 ) * 10, 78, ( ( pos - first + 1 ) + 1 ) * 10 - 1, 1 );
                        if ( vpos >= strlen ( menu[helper[lib_mod ( i + first, menu[0].num )]].text ) - 12 )
                            vpos = 0;
                        memcpy ( str, ( unsigned char * ) ( ( unsigned long ) ( menu[helper[lib_mod ( i + first, menu[0].num )]].text ) + vpos++ ), 12 );
                        //str[12] = '\n';     // kr: this fixed char number could be a problem, if we change font - not important ;)
                        str[12] = 0x00;
/*
                        if ( i == 0 )
                            lcd_render_text ( 2, ( 11 * ( i + 1 ) ), str, 2 );
                        if ( i == 1 )
                            lcd_render_text ( 2, ( 11 * ( i + 1 ) ) - 1, str, 2 );
                        if ( i == 2 )
                            lcd_render_text ( 2, ( 11 * ( i + 1 ) ) - 2, str, 2 );
*/

                        lcd_render_text ( 2, ( 11 * ( i + 1 ) ) - i, str, 2 );
                        lcd_to_screen (  );
                        if ( kpd_getkey (  ) != 0xFF )
                            break;
                        if ( vpos == 0 )
                            kmsleep ( 1350 );
                        else
                            kmsleep ( 350 );
                    }
                    i++;
                    lcd_set_font ( 0 );
                }
                else
#endif
                {
                    lcd_set_font ( 2 );
                    if ( lcd_get_text_width ( menu[helper[lib_mod ( i + first, menu[0].num )]].text ) > 75 )
                    {
                        char unsel[13];
                        memcpy ( unsel, ( unsigned char * ) ( ( unsigned long ) ( ( menu[helper[lib_mod ( i + first, menu[0].num )]].text ) ) ), 12 );

// kr: why using "if" everywhere ? maybe " - lib_mod( i , 3 ) " is better ?!
// g3: yep, its much better :) you dont even need lib_mod if i see right.. just "- i"
//     also in the blocks above it could be changed..
// kr: ok, i changed it.... :)

/*
                        if ( i == 0 )
                        {
                            lcd_render_text ( 2, ( 11 * ( i + 1 ) ), unsel, 2 );
                            lcd_render_text ( 2 + lcd_get_text_width ( unsel ), 11 * ( i + 1 ), "...", 2 );
                        }
                        if ( i == 1 )
                        {
                            lcd_render_text ( 2, ( 11 * ( i + 1 ) ) - 1, unsel, 2 );
                            lcd_render_text ( 2 + lcd_get_text_width ( unsel ), ( 11 * ( i + 1 ) ) - 1, "...", 2 );
                        }
                        if ( i == 2 )
                        {
                            lcd_render_text ( 2, ( 11 * ( i + 1 ) ) - 2, unsel, 2 );
                            lcd_render_text ( 2 + lcd_get_text_width ( unsel ), ( 11 * ( i + 1 ) ) - 2, "...", 2 );
                        }
*/
                        lcd_render_text ( 2, ( 11 * ( i + 1 ) ) - i, unsel, 2 );
                        lcd_render_text ( 2 + lcd_get_text_width ( unsel ), ( 11 * ( i + 1 ) ) - i, "...", 2 );
                        i++;
                    }
                    if ( lcd_get_text_width ( menu[helper[lib_mod ( i + first, menu[0].num )]].text ) < 75 )
                    {
/*
                        if ( i == 0 )
                            lcd_render_text ( 2, ( 11 * ( i + 1 ) ), menu[helper[lib_mod ( i + first, menu[0].num )]].text, 2 );
                        if ( i == 1 )
                            lcd_render_text ( 2, ( 11 * ( i + 1 ) ) - 1, menu[helper[lib_mod ( i + first, menu[0].num )]].text, 2 );
                        if ( i == 2 )
                            lcd_render_text ( 2, ( 11 * ( i + 1 ) ) - 2, menu[helper[lib_mod ( i + first, menu[0].num )]].text, 2 );
*/
                        lcd_render_text ( 2, ( 11 * ( i + 1 ) ) - i, menu[helper[lib_mod ( i + first, menu[0].num )]].text, 2 );
                        i++;

                    }
                }
            }
            lcd_set_font ( 0 );
        default:
            break;
    }
    lcd_to_screen (  );
    lcd_fontsettings ( FONT_SYSTEM );
}

int
menu_disp ( unsigned char *text )
{
    lcd_fontsettings ( FONT_SIZED );
    lcd_set_font ( 0 );
    lcd_render_text_ml ( 80, 38, text, 1, AL_BOTTOM | AL_RIGHT );
    lcd_to_screen (  );
    lcd_fontsettings ( FONT_SYSTEM );
    lcd_set_font ( 0 );
}


void
dropdown_print ( char **entries, int pos, int first )
{
    int i, height, num = 0;

    while ( entries[num] )
        num++;
    height = MIN ( num, 3 );

    lcd_draw_rect ( 12, 12, 84 - 12, 12 + 8 * height + 1, 1 );
    lcd_draw_rect ( 13, 13, 84 - 13, 12 + 8 * height, 0 );
    for ( i = 0; i < height; i++ )
        lcd_render_text ( 14, 13 + 8 * i, entries[lib_mod ( first + i, num )], 1 );
    lcd_draw_rect ( 13, 13 + 8 * ( pos - first ), 84 - 13, 13 + 7 + 8 * ( pos - first ), 2 );
    lcd_to_screen (  );
}


int
menu_dropdown ( char **entries, int pos )
{
    int ignoresleep = 0;
    int num = 0, first = MAX ( 0, pos - 1 );
    unsigned char key, prevkey = 0xFF;

    while ( entries[num] )
        num++;

    while ( first + 2 >= num && first )
        first--;

    while ( 1 )
    {
        dropdown_print ( entries, pos, first );
        if ( !ignoresleep )
            kpd_wait_release_x ( 1000 );
        else
            kpd_wait_release_x ( 300 );
        ignoresleep = 0;
        kmsleep ( 200 );
        key = kpd_getkey (  );
        if ( key != 0xFF && key == prevkey )
            ignoresleep = 1;
        prevkey = key;

        switch ( key )
        {
            case KPD_UPARROW:
                if ( pos )
                    pos--;
                else
                    pos = num - 1;
                break;
            case KPD_DWNARROW:
                if ( pos == num - 1 )
                    pos = 0;
                else
                    pos++;
                break;
            case KPD_SOFTBTN1:
                return ( pos );
                break;
            case KPD_CANCEL:
                return ( -1 );
                break;
            default:
                break;
        }
        if ( pos < first )
            first = pos;
        else if ( pos > first + 2 )
            first = pos - 2;

    }                           //while

}


int
menu_show ( menupoint * menu )
{
    int first = 0, pos = 0, i, done = 0, ignoresleep = 0;
    unsigned char *helper;
    unsigned char key, j, prevkey = 0xFF;
    int mode = kpd_getmode (  );

    kpd_mode ( KPD_BUFFERED );

    if ( menu[0].type && menu[0].num )
    {
        helper = ( unsigned char * ) malloc ( menu[0].num );
        helper[0] = 1;
        for ( i = 1; i < menu[0].num; i++ )
            helper[i] = helper[i - 1] + menu_findnext_mp ( &menu[helper[i - 1]] );

        while ( !done )
        {
            menu_newprint ( menu, helper, pos, first );
            if ( !ignoresleep )
                kpd_wait_release_x ( 1000 );
            else
                kpd_wait_release_x ( 300 );
            ignoresleep = 0;
            kmsleep ( 200 );
            key = kpd_getkey (  );
            if ( key != 0xFF && key == prevkey )
                ignoresleep = 1;
            prevkey = key;

            if ( key > 0 && key < 10 )
            {
                if ( key <= menu[0].num )
                {
                    pos = key - 1;
                    key = KPD_SOFTBTN1;
                    menu_newprint ( menu, helper, pos, first );
                    usleep ( 200000 );
                }
            }
            switch ( key )
            {
                case KPD_UPARROW:
                    if ( menu[helper[pos]].function )
                        ( *menu[helper[pos]].function ) ( MENU_UNDRAW, 0 );
                    if ( pos )
                        pos--;
                    else
                        pos = menu[0].num - 1;
                    if ( menu[helper[pos]].function )
                        ( *menu[helper[pos]].function ) ( MENU_DRAW, 0 );
                    break;
                case KPD_DWNARROW:
                    if ( menu[helper[pos]].function )
                        ( *menu[helper[pos]].function ) ( MENU_UNDRAW, 0 );
                    if ( pos == menu[0].num - 1 )
                        pos = 0;
                    else
                        pos++;
                    if ( menu[helper[pos]].function )
                        ( *menu[helper[pos]].function ) ( MENU_DRAW, 0 );
                    break;
                case KPD_SOFTBTN1:
                    if ( menu_show ( &menu[helper[pos]] ) == MENU_EXIT )
                    {
                        kpd_mode ( mode );
                        return MENU_EXIT;
                    }
                    if ( menu[helper[pos]].type & MENU_T_EXIT )
                    {
                        kpd_mode ( mode );
                        return 0;
                    }
                    break;
                case KPD_CANCEL:
                    done = 1;
                    break;
                case 0xFF:
                    break;
                default:
                    break;
            }
            if ( pos < first )
                first = pos;
            else if ( pos > first + 2 )
                first = pos - 2;


        }                       //while

        kpd_mode ( mode );
        free ( helper );
        return 0;
    }
    else
    {
        kpd_wait_release (  );
        usleep ( 1000 );
        kpd_wait_release (  );  // kr: hm, is it really needed ?
        kpd_mode ( mode );
        if ( menu[0].function )
            return ( ( *menu[0].function ) ( MENU_SELECT, 0 ) );
        else
            return 0;
    }


}


unsigned char
menu_main ( char **entries, int presel )
{
    int sel = presel;
    int num = 0;
    int done = 0;
    int first = 0;
    int offset = 0;
    int dir = MENU_DIR_NONE;
    unsigned char key = 0xFF;
    int scrspd[] = { 0, 0, 0, 1, 1, 3, 3, 5, 8 };

    kpd_mode ( KPD_UNBUFFERED );
    while ( entries[num] )
        num++;

    menu_print ( entries, num, sel, first, 0, 0, 0 );
    while ( !done )
    {

        kpd_wait_release_x ( 300 );
        do
        {
            key = kpd_getkey (  );
        }
        while ( key == 0xFF );

        lib_rand ( key );

        switch ( key )
        {
            case KPD_UPARROW:
                if ( sel )
                {
                    sel--;
                    dir = MENU_DIR_PREV;
                }
                else
                {
                    sel = num - 1;
                    dir = MENU_DIR_FADL;
                }
                break;
            case KPD_DWNARROW:
                if ( sel < num - 1 )
                {
                    sel++;
                    dir = MENU_DIR_NEXT;
                }
                else
                {
                    sel = 0;
                    dir = MENU_DIR_FADU;
                }
                break;
            case KPD_SOFTBTN1:
                return sel;
                break;
            case KPD_CANCEL:
                return 0xFF;
                break;
            default:
                if ( key == 0x00 )
                {
                    if ( num >= 0x0A )
                        sel = 0x0A - 1;
                }
                else if ( key < 0x0A && num >= key )
                    sel = key - 1;
                break;
        }

        switch ( dir )
        {
            case MENU_DIR_PREV:
                for ( offset = 8; offset >= 0; offset-- )
                {
                    menu_print ( entries, num, sel, first, scrspd[offset], 0, 0 );
                    usleep ( 10000 );
                }
                break;
            case MENU_DIR_NEXT:
                for ( offset = 8; offset >= 0; offset-- )
                {
                    menu_print ( entries, num, sel, first, -scrspd[offset], 0, 0 );
                    usleep ( 10000 );
                }
                break;
            case MENU_DIR_FADU:
                for ( offset = 8; offset >= 0; offset-- )
                {
                    menu_print ( entries, num, sel, first, 0, 0, -scrspd[offset] );
                    usleep ( 10000 );
                }
                break;
            case MENU_DIR_FADL:
                for ( offset = 8; offset >= 0; offset-- )
                {
                    menu_print ( entries, num, sel, first, 0, scrspd[offset], 0 );
                    usleep ( 10000 );
                }
                break;
            case MENU_DIR_NONE:
                menu_print ( entries, num, sel, first, 0, 0, 0 );
                break;
            default:
                break;
        }
        dir = MENU_DIR_NONE;
    }

    kpd_mode ( KPD_BUFFERED );
    return sel;
}

void
menu_print ( char **entries, int num, int presel, int first, int baroffs, int bars, int bare )
{
    int pos = first;

    lcd_clr (  );
    lcd_draw_rect ( 0, ( presel - first ) * 8 + baroffs + bars, 83, ( presel + 1 ) * 8 + baroffs + bare - 1, 1 );
    while ( pos < num && pos - first < 5 )
    {
        lcd_render_text ( 0, ( pos - first ) * 8, entries[pos], 2 );
        pos++;
    }
    lcd_to_screen (  );
}

void
menu_draw_header ( unsigned char *text, unsigned int number )
{
    unsigned char buf[16];
    unsigned int i;
    lcd_render_text ( 0, 0, "                      ", 1 );  // kr: don't think that the blank spaces clear the area
    memset ( buf, 0, 16 );
    memcpy ( buf, text, 10 );
    i = 41 - 3 * strlen ( buf );
    lcd_render_text ( i, 0, buf, 1 );
    lcd_draw_line ( 0, 4, i - 6, 4, 1 );
    if ( number > 0 )
    {
        sprintf ( buf, "%d", number );
        lcd_render_text_ml ( 83, 0, buf, 1, AL_RIGHT );
        lcd_draw_line ( 81 - i + 4, 4, 73, 4, 1 );
    }
    else
        lcd_draw_line ( 81 - i + 4, 4, 84, 4, 1 );
    lcd_to_screen (  );
}
