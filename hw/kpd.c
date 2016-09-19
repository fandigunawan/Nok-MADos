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
#include <hw/kpd.h>
#include <hw/kpd_getkey_matrix.h>
#include <core/lib.h>
#include <core/menu.h>
#include <hw/lcd.h>
#include <hw/int.h>
#include <apps/demo_1.h>
#include <apps/screenshot.h>
#include <hw/flash.h>
#include <hw/ccont.h>
#ifndef ARM
#include <stdio.h>
#include <fcntl.h>
#endif

extern unsigned char startup;
#define NORMAL 0
#define CHARGE 1


/*#define DEBUG2(x, y)    if ( !debug_row ) lcd_clr();\
            sprintf(debug_buf, x, y);\
		    lcd_render_text ( 0, debug_row*8, debug_buf, 1 );\
		    lcd_to_screen_hw ();\
            debug_row++;\
            if ( debug_row == 6 ) debug_row = 0;\
            sleep(1);*/
//#define DEBUG2(x, y) usleep(1);

/*unsigned char debug_buf[32];
unsigned char debug_row = 0;*/

unsigned char kpd_buffer[KPD_BUFSIZE];
unsigned char kpd_buffer_last_char;
unsigned int kpd_buffer_locked;
unsigned int kpd_buffer_last_time;
unsigned int kpd_buffer_end;
unsigned int kpd_buffer_start;
unsigned int kpd_last_time;

unsigned char kpd_second_key = 0xFF;
unsigned char kpd_third_key = 0xFF;

//////SHORT KEY VARS/////
unsigned int laststar;
unsigned int skdelay = 5;
unsigned char skey = 0x10;
unsigned int skstatus = 1;

unsigned char power_menu_active = 0;

// initialized keypad and its IOs


MENU_CALLBACK ( pwr_off )
{
    MENU_ONLY_SELECT;
    ccont_poweroff (  );
}

MENU_CALLBACK ( pwr_reboot )
{
    MENU_ONLY_SELECT;
    ccont_reboot (  );
}

MENU_CALLBACK ( pwr_exit )
{
    MENU_ONLY_SELECT;
    return MENU_EXIT;
}

void
powermenu ( void )
{
    menupoint pwrmenu[] = {
        {MENU_T_LIST, 3, NULL, NULL, "Power"},
        {0, 0, pwr_reboot, NULL, "Reboot"},
        {0, 0, pwr_off, NULL, "Off"},
        {0, 0, pwr_exit, NULL, "Exit Menu"},
    };
    if ( !power_menu_active )   // allows only 1 powermenu - not powermenu in powermenu
    {
        power_menu_active = 1;
        menu_show ( pwrmenu );
        power_menu_active = 0;
    }

}






void
kpd_io_init ( void )
{
    switch ( mados_info[mados_phone].kpd )
    {
        case 0:
            _io_set ( IO_UIF_UNK_R, 0x1F );
            _io_set ( IO_UIF_UNK_C, 0x20 );
            _io_set ( IO_UIF_IM_R, 0x1F );
            _io_set ( IO_UIF_IM_C, 0x60 );
            _io_set ( IO_UIF_KPD_R, 0x00 );
            _io_set ( IO_UIF_KPD_C, 0x7F );
            _io_set ( IO_UIF_DIR_R, 0x1F );
            _io_set ( IO_UIF_DIR_C, 0x1F );
            _io_set ( IO_UIF_UNK, 0x1F );
            break;
        case 1:
            _io_set ( IO_UIF_UNK_R, 0x1E );
            _io_set ( IO_UIF_UNK_C, 0x20 );
            _io_set ( IO_UIF_IM_R, 0x1F );
            _io_set ( IO_UIF_IM_C, 0x60 );
            _io_set ( IO_UIF_KPD_R, 0x00 );
            _io_set ( IO_UIF_KPD_C, 0x3F );
            _io_set ( IO_UIF_DIR_R, 0x1E );
            _io_set ( IO_UIF_DIR_C, 0x1F );
            _io_set ( IO_UIF_UNK, 0x1F );
            break;
        case 2:
            _io_set ( IO_UIF_UNK_R, 0x1F );
            _io_set ( IO_UIF_UNK_C, 0x00 );
            _io_set ( IO_UIF_IM_R, 0x1F );
            _io_set ( IO_UIF_IM_C, 0x60 );
            _io_set ( IO_UIF_KPD_R, 0x00 );
            _io_set ( IO_UIF_KPD_C, 0x1F );
            _io_set ( IO_UIF_DIR_R, 0x1F );
            _io_set ( IO_UIF_DIR_C, 0x1F );
            _io_set ( IO_UIF_UNK, 0x1F );
        default:
            break;
    }
}

void
kpd_init ( void )
{
    kpd_io_init (  );

    kpd_buffer_locked = 1;
    kpd_last_time = 0;
    kpd_buffer_clr (  );
    int_irq_set_handler ( 0x00, kpd_int_handler );
#ifndef ARM
    int flags = fcntl ( 0, F_GETFL, 0 );
    fcntl ( 0, F_SETFL, flags | O_NONBLOCK );
    setvbuf ( stdin, ( char * ) NULL, _IONBF, 0 );

#endif
}


unsigned char
kpd_getmode ( void )
{
    return kpd_buffer_locked;
}

unsigned int
kpd_getlast ( void )
{
    return kpd_last_time;
}

unsigned int
kpd_buffer_getsize ( void )
{
    unsigned int size = 0;

    if ( kpd_buffer_start > kpd_buffer_end )
        size = KPD_BUFSIZE - ( kpd_buffer_start - kpd_buffer_end );
    else
        size = kpd_buffer_end - kpd_buffer_start;

    return size;
}

void
kpd_buffer_add ( unsigned char c )
{
    if ( kpd_buffer_getsize (  ) >= KPD_BUFSIZE - 1 || c == 0xFF )
        return;
    if ( c == kpd_buffer_last_char && lib_get_time (  ) - kpd_buffer_last_time < 100 )
        return;

    kpd_buffer_last_char = c;
    kpd_buffer_last_time = lib_get_time (  );
    kpd_buffer[kpd_buffer_end++] = c;
    kpd_buffer_end = lib_mod ( kpd_buffer_end, KPD_BUFSIZE );
}

unsigned char
kpd_buffer_get ( void )
{
    unsigned char c;

    if ( !kpd_buffer_getsize (  ) )
        return 0xFF;

    c = kpd_buffer[kpd_buffer_start];
    kpd_buffer[kpd_buffer_start++] = 0xFF;
    kpd_buffer_start = lib_mod ( kpd_buffer_start, KPD_BUFSIZE );

    return c;
}

void
kpd_buffer_clr ( void )
{
    memset ( kpd_buffer, 0xFF, KPD_BUFSIZE );
    kpd_buffer_last_char = 0x00;
    kpd_buffer_last_time = 0x00;
    kpd_buffer_end = 0x00;
    kpd_buffer_start = 0x00;
}

void
kpd_int_handler ( void )
{
    unsigned char c;

    kpd_last_time = lib_get_time (  );
    kpd_buffer_last_time = kpd_last_time;

    if ( !kpd_buffer_locked )
    {
        c = kpd_readkey (  );
//        if ( c == kpd_readkey (  ) ) ;
        kpd_buffer_add ( c );
//  lcd_draw_rect ( 0, 0, 10, 10, 1 );
//  lcd_to_screen_hw ();
    }
}

unsigned char
kpd_getkey ( void )
{
    unsigned char c;

    if ( kpd_buffer_locked )
    {
        c = kpd_readkey (  );
#ifndef ARM
        kpd_last_time = lib_get_time (  );
        kpd_buffer_last_time = kpd_last_time;
        return c;
#else
        if ( c == kpd_readkey (  ) )
        {
            if ( c == KPD_OFF )
            {
                if ( startup == CHARGE )
                    ccont_reboot (  );
                powermenu (  );
            }
            return c;
        }
        else
            return 0xFF;
#endif
    }
    else
        return kpd_buffer_get (  );
}

unsigned char
kpd_get_second_key ( void )
{
    // TODO: maybe buffering
    return kpd_second_key;
}

unsigned char
kpd_get_third_key ( void )
{
    // TODO: maybe buffering
    return kpd_third_key;
}

void
kpd_set_skstat ( unsigned int skval )
{
    skstatus = skval;
}


void
kpd_check_shortkey ( unsigned char r )
{

    ///////////////USAGE//////////////////
    // AND ADD A CALL TO YOUR FUNCTION  //
    //////////////////////////////////////
    if ( skstatus == 1 )
    {
//if ( lib_get_time ( ) - laststar  < skdelay )
//  {
        switch ( r )
        {
            case 0x0:
//key = 0
                break;
            case 0x1:
                screenshot_capture (  );
                break;

            case 0x2:
//key = 2
                break;
            case 0x3:
//key = 3
                demo_1_main (  );
                break;
            case 0x4:
//key = 4
                break;
            case 0x5:
//key = 5
                break;
            case 0x6:
//key = 6
                break;
            case 0x7:
//key = 7
                break;
            case 0x8:
//key = 8
                break;
            case 0x9:
//key = 9
                break;
            default:
                break;
        }
//  }
    }
}


// returns the currently pressed key
// kpd_get_second_key returns the higher value, kpd_get_third_key the highest value
unsigned char
kpd_readkey ( void )
{
#ifndef ARM
    char buf;

    if ( read ( 0, &buf, 1 ) == -1 )
        return 0xFF;
    if ( buf == 'a' )
        return KPD_UPARROW;
    if ( buf == 'y' )
        return KPD_DWNARROW;
    if ( buf == 'x' )
        return KPD_SOFTBTN1;
    if ( buf == 'c' )
        return KPD_CANCEL;
    if ( buf == 'q' )
        exit ( 0 );
    if ( buf == '#' )
        return 0x12;
    if ( buf == '*' )
        return 0x10;
    if ( buf == 'h' )
    {
        printf ( "possible keys:\n0-9\na, y - up/down\nx - SOFTBTN1\nc - CANCEL\n#, *\nh - this help\nq - exit\n" );
        sleep ( 2 );
    }
    if ( buf >= '0' && buf <= '9' )
        return buf - 0x30;
    return 0xFF;
#else
    //row: input
    //col: output

//DEBUG2("read key called", NULL);
    unsigned char col_before, col_return, cols, rows, c, anded_val, key_count = 0, keys[4], row_set, key1 = 0xFF, key2 = 0xFF;

    int_disable (  );
    _io_set ( IO_UIF_KPD_R, 0 );
    col_before = col_return = _io_read ( IO_UIF_KPD_C );
//DEBUG2("colbefore %02X", col_before);

    cols = 5;
    for ( c = 1; c != 0x20; c <<= 1 )
    {
        cols--;
        if ( !( c & col_before ) && key_count < 3 )
        {
//        DEBUG2("c is %02X NULL", c );

            row_set = 1;
            for ( rows = 5; rows; rows-- )
            {
//            DEBUG2("--set to %02X", 0x1f - row_set); 
                _io_set ( IO_UIF_KPD_R, 0x1f - row_set );
                col_return = _io_read ( IO_UIF_KPD_C );
//            DEBUG2("--returned %02X", col_return );
                anded_val = c & col_return;
//            DEBUG2("--c and ret %02X", anded_val); //<- dat is null
                //also muesste if hier greifen ?! lol, warum geht das nur mit test ??
                if ( !anded_val /*col_return & c == 0 */  && key_count < 3 )
                {
//                DEBUG2("---match %02X", rows );
                    keys[key_count++] = kpd_getkey_matrix[mados_info[mados_phone].kpd_matrix][( rows - 1 ) * 5 + cols];
                }

                row_set <<= 1;
            }


        }
    }

    _io_set ( IO_UIF_KPD_R, 0 );
    if ( _io_read ( IO_UIF_KPD_C ) != col_before )
        key_count = 0;

    int_enable (  );

    while ( key_count < 3 )
        keys[key_count++] = 0xFF;

    if ( keys[0] > keys[2] )
    {
        keys[3] = keys[0];
        keys[0] = keys[2];
        keys[2] = keys[3];
    }

    if ( keys[0] > keys[1] && keys[1] < keys[2] )
    {
        keys[3] = keys[0];
        keys[0] = keys[1];
        keys[1] = keys[3];
    }

    if ( keys[1] > keys[2] )
    {
        keys[3] = keys[1];
        keys[1] = keys[2];
        keys[2] = keys[3];
    }

    c = 1;
    for ( key_count = 0; key_count < 3; key_count++ )
        if ( keys[key_count] != kpd_off[mados_info[mados_phone].kpd_matrix][key_count] )
            c = 0;

    if ( c )
    {
        key_count = 0;
        while ( key_count < 3 )
            keys[key_count++] = 0xFF;
        //powermenu (  );
        keys[0] = KPD_OFF;
    }

    if ( keys[1] == skey )
    {
        kpd_check_shortkey ( keys[0] );
        key_count = 0;
        while ( key_count < 3 )
            keys[key_count++] = 0xFF;
    }
/*
if ( keys[0] == 0x30 )
{
powermenu();
 keys[0] = 0xFF;
}
*/
    kpd_second_key = keys[1];
    kpd_third_key = keys[2];

    return keys[0];

#endif
}

// waits >ms< ms for keypad release, then it exits
void
kpd_wait_release_x ( int ms )
{
#ifdef ARM
    int target = lib_get_time (  ) + ms;

    while ( kpd_readkey (  ) != 0xFF && ( !ms || lib_get_time (  ) < target ) ) ;
#endif
}



void
kpd_wait_release ( void )
{
    kpd_wait_release_x ( 0 );
}

// waits >ms< ms for keypad press, then it exits
void
kpd_wait_keypress_x ( int ms )
{
    int target = lib_get_time (  ) + ms;

    while ( kpd_readkey (  ) == 0xFF && ( !ms || lib_get_time (  ) < target ) ) ;
}


void
kpd_wait_keypress ( void )
{
    kpd_wait_keypress_x ( 0 );
}

void
kpd_mode ( unsigned char mode )
{
    if ( mode == KPD_UNBUFFERED )
        kpd_buffer_locked = 1;
    else
        kpd_buffer_locked = 0;

    kpd_buffer_clr (  );
}
