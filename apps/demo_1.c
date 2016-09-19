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

#include <core/ipc.h>
#include <core/lib.h>
//#include <core/ui.h>
#include <core/sched.h>
//#include <core/menu.h>
//#include <hw/led.h>
//#include <hw/timer.h>
#include <hw/lcd.h>
//#include <hw/io.h>
#include <hw/kpd.h>
//#include <hw/flash.h>
//#include <hw/ccont.h>
#include <hw/vibra.h>
//#include <hw/mbus.h>
//#include <hw/int.h>
//#include <apps/matrix.h>
//#include <apps/charger.h>
//#include <apps/tetris.h>
//#include <apps/bomberman.h>
//#include <apps/othello.h>
//#include <apps/dct4.h>
//#include <apps/fire.h>
//#include <apps/stars.h>
//#include <core/bitmap.h>
//#include <apps/txtreader.h>
//#include <apps/st55gd55.h>
//#include <apps/lgunlock.h>
//#include <apps/hangman.h>
//#include <apps/alcatel.h>
//#include <apps/samsung.h>
//#include <apps/meas.h>
#include <apps/demo_1.h>
#include <hw/buzzer.h>

//#define LCD_BUFLEN    (84*48)/8
//extern unsigned char lcd_buf[LCD_BUFLEN];

//unsigned char buzzer_end;

void
demo_1_main ( void )
{
    int i, i1, i2;
    unsigned char c, c1, c2, c3, sndthread, secondthread, end = 0;
    const char *text = "have fun";
    unsigned char *lcd_buf_backup = NULL;
    unsigned char *lcd_buf = NULL;

    //unsigned char *lcd_rand_fill = NULL;

    unsigned int pend;

    //lcd_rand_fill = ( unsigned char * ) malloc ( 84*48 );
    //memset ( lcd_rand_fill, 0, 84*48 );

    lcd_buf_backup = ( unsigned char * ) malloc ( lcd_get_bufsize (  ) );
    lcd_buf = ( void * ) lcd_get_buf (  );
    //end[0] = 0;

    sndthread = sched_add ( ( unsigned int ) demo_1_sndthread, 1, SCHED_PARM_RUN );
/*    secondthread = sched_add ( ( unsigned int ) demo_1_2ndmainthread, 1, SCHED_PARM_RUN );
    ipc_assign_data ( sndthread, 1 );
    ipc_assign_data ( secondthread, 2 );
*/

//    buzzer_end = 0;

    kpd_wait_release (  );

    usleep ( 500000 );          // wait until ipc_assign_data is done

    pend = ( unsigned int ) &end;
    ipc_add ( sndthread, ( unsigned char * ) &pend, 4 );

    for ( c = 83; c != 0; c-- )
    {
        if ( kpd_getkey (  ) != 0xFF )
        {
            end = 1;
            usleep ( 500000 );
            return;
        }
        lcd_draw_rect ( c, 0, 83, 47, 1 );
        lcd_to_screen (  );
        usleep ( 40000 );
    }

//    ipc_add ( sndthread, "\x01", 1 );

    for ( i = 42; i >= 0; i-- )
    {
        if ( kpd_getkey (  ) != 0xFF )
        {
            end = 1;
            usleep ( 500000 );
            return;
        }
        lcd_fill ( 0xFF );
        lcd_draw_rect ( i, 0, 83 - i, 47, 0 );
        lcd_render_text ( ( 84 - lcd_get_text_width ( "welcome to" ) ) / 2, 20 - i, "welcome to", 1 );
        lcd_render_text ( ( 84 - lcd_get_text_width ( "MADos" ) ) / 2, 29 - i, "MADos", 1 );
        lcd_to_screen (  );
        usleep ( 75000 );
    }

    usleep ( 500000 );

//    ipc_add ( sndthread, "\x00", 1 );

    for ( i = 0; i < 84 * 48; i++ )
    {
        if ( kpd_getkey (  ) != 0xFF )
        {
            end = 1;
            usleep ( 500000 );
            return;
        }

        c2 = 1;
        do
        {
            c = lib_mod ( lib_rand ( i ), 84 );
            c1 = lib_mod ( lib_rand ( i ), 48 );
            c2++;
        }
        while ( lcd_get_pixel ( c, c1 ) == 1 && c2 < 24 );

        if ( c2 > 1 )
            c2 /= 2;

        lcd_draw_rect ( c, c1, c + c2, c1 + c2, 1 );
        lcd_to_screen (  );
        i2 = 0;
        for ( i1 = 0; i1 < lcd_get_bufsize (  ); i1++ )
            if ( lcd_buf[i1] != 0xFF )
                i2++;

        if ( !i2 )
            break;
        if ( i2 < 7 )
            lcd_fill ( 0xFF );

        usleep ( 1000 * c2 );
    }

    c2 = ( 84 - lcd_get_text_width ( text ) ) / 2;
    for ( c = 0; c <= strlen ( text ); c++ )
    {
        memcpy ( lcd_buf_backup, lcd_buf, lcd_get_bufsize (  ) );
        for ( c1 = 0; c1 <= 25; c1++ )
        {
            if ( kpd_getkey (  ) != 0xFF )
            {
                end = 1;
                usleep ( 500000 );
                return;
            }
            memcpy ( lcd_buf, lcd_buf_backup, lcd_get_bufsize (  ) );
            lcd_render_char_x ( c2, lib_mod ( c, 2 ) ? c1 : ( 47 - c1 ), text[c], 2 );
            lcd_to_screen (  );
            usleep ( 35000 );
        }
        c2 += lcd_get_char_width ( text[c] );
    }

    for ( c = 0; c < 48; c++ )
    {
        if ( kpd_getkey (  ) != 0xFF )
        {
            end = 1;
            usleep ( 500000 );
            return;
        }
        for ( c1 = 0; c1 < 28; c1++ )
        {
            if ( lib_mod ( c1, 2 ) )
                lcd_draw_rect ( c1 * 3, 0, c1 * 3 + 2, c, 0 );
            else
                lcd_draw_rect ( c1 * 3, 47 - c, c1 * 3 + 2, 47, 0 );
        }
        lcd_to_screen (  );
        usleep ( 60000 );
    }

    for ( c = 0; c < 84 + 20; c++ )
    {
        if ( kpd_getkey (  ) != 0xFF )
        {
            end = 1;
            usleep ( 500000 );
            return;
        }
        lcd_draw_line ( c, 0, c - 20, 47, 1 );
        lcd_to_screen (  );
        usleep ( 20000 );
    }

    for ( c = 0; c < 47; c++ )
    {
        if ( kpd_getkey (  ) != 0xFF )
        {
            end = 1;
            usleep ( 500000 );
            return;
        }
        lcd_clr (  );
        lcd_render_text ( ( 84 - lcd_get_text_width ( "g3gg0" ) ) / 2, 12 - 23 + ( c / 2 ), "g3gg0", 1 );
        lcd_render_text ( ( 84 - lcd_get_text_width ( "krisha" ) ) / 2 + 47 - c, 20, "krisha", 1 );
        lcd_render_text ( ( 84 - lcd_get_text_width ( "chief359" ) ) / 2, 28 + 23 - ( c / 2 ), "chief359", 1 );
        lcd_draw_rect ( 0, 0, 83, 23 - c / 2, 1 );  //up
        lcd_draw_rect ( 0, 24 + c / 2, 83, 47, 1 ); //down
        lcd_draw_rect ( 0, 0, 41 - c, 47, 1 );  //left
        lcd_draw_rect ( 41 + c, 0, 83, 47, 1 ); //right
        lcd_to_screen (  );
        usleep ( 55000 );
    }

    for ( c1 = c; c1; c1-- )
    {
        if ( kpd_getkey (  ) != 0xFF )
        {
            end = 1;
            usleep ( 500000 );
            return;
        }
        lcd_clr (  );
        lcd_render_text ( ( 84 - lcd_get_text_width ( "g3gg0" ) ) / 2, 12 - 23 + ( c1 / 2 ), "g3gg0", 1 );
        lcd_render_text ( ( 84 - lcd_get_text_width ( "krisha" ) ) / 2 + 47 - c1, 20, "krisha", 1 );
        lcd_render_text ( ( 84 - lcd_get_text_width ( "chief359" ) ) / 2, 28 + 23 - ( c1 / 2 ), "chief359", 1 );
        lcd_to_screen (  );
        usleep ( 30000 );
    }

    for ( c = 0; c < 47; c++ )
    {
        if ( kpd_getkey (  ) != 0xFF )
        {
            end = 1;
            usleep ( 500000 );
            return;
        }
        lcd_clr (  );
        lcd_render_text ( ( 84 - lcd_get_text_width ( "wumpus" ) ) / 2, 12 - 23 + ( c / 2 ), "wumpus", 1 );
        lcd_render_text ( ( 84 - lcd_get_text_width ( "Crux" ) ) / 2 + 47 - c, 20, "Crux", 1 );
        lcd_render_text ( ( 84 - lcd_get_text_width ( "M547" ) ) / 2, 28 + 23 - ( c / 2 ), "M547", 1 );
        lcd_to_screen (  );
        usleep ( 55000 );
    }

    for ( c = 84 + 20; c; c-- )
    {
        if ( kpd_getkey (  ) != 0xFF )
        {
            end = 1;
            usleep ( 500000 );
            return;
        }
        lcd_draw_line ( c, 0, c - 20, 47, 1 );
        lcd_to_screen (  );
        usleep ( 20000 );
    }

    // let's end buzzer playing ;)
    end = 1;
//    buzzer_end = 1;
    //don't like this global variables... want to do it with ipc :p

    lcd_type_text_2 ( ( 84 - lcd_get_text_width ( "the end..." ) ) / 2, 20, 1, "the end...", 0 );

    //free ( lcd_rand_fill );

    kpd_wait_keypress (  );

    return;



}

void
demo_1_sndthread ( void )
{
    char *song = NULL;
    char *dur = NULL;
    char *oct = NULL;
    int c;

//    char buf[10]; //debug only

//    unsigned char *buzzer_interrupt = NULL;

    unsigned int p_buz_int = 0;

    buzzer_tones_t tone_info;

    unsigned char got_it = 0;
    unsigned char *ptr;
    int len;

    ipc_assign_data ( 0xFF, 4 );

//    buzzer_interrupt = ( unsigned char * ) malloc ( 4 );

    song = ( char * ) malloc ( 500 );
    dur = ( char * ) malloc ( 500 );
    oct = ( char * ) malloc ( 500 );

    while ( !got_it )
    {
        if ( ipc_poll (  ) )
        {
            ptr = ipc_read ( &len );
            if ( len == 4 )
            {
                memcpy ( &p_buz_int, ptr, 4 );

                /*
                 * switch ( ptr[0] )
                 * {
                 * case 0x0:
                 * end = 1;
                 * break;
                 * case 0x1:
                 * buzzer_play_tones ( &tone_info );
                 * break;
                 * }
                 */
                got_it = 1;
            }
            ipc_flush (  );
        }
        usleep ( 3000 );
    }

    //debug only:
/*
    while ( 1 )
    {
        lcd_draw_rect ( 0, 0, 83, 24, 0 );
        sprintf ( buf, "ptr: %08X\0", &ptr );
        lcd_render_text ( 0, 0, buf, 1 );
        sprintf ( buf, "b: %08X\0", &buzzer_interrupt );
        lcd_render_text ( 0, 8, buf, 1 );
        sprintf ( buf, "ptr: %02X%02X%02X%02X\0", ptr[0], ptr[1], ptr[2], ptr[3] );
        lcd_render_text ( 0, 16, buf, 1 );
        sprintf ( buf, "b: %02X%02X%02X%02X\0", buzzer_interrupt[0],buzzer_interrupt[1],buzzer_interrupt[2],buzzer_interrupt[3] );
        lcd_render_text ( 0, 24, buf, 1 );
        lcd_to_screen ();
    }
*/

    for ( c = 0; c < 500; c++ )
    {
        song[c] = lib_mod ( lib_rand ( c * 3 ), 6 ) + 'c';
        dur[c] = lib_mod ( lib_rand ( c ), 4 ) + 1;
        oct[c] = lib_mod ( lib_rand ( c ), 2 );
    }

    tone_info.tone_list = song;
    tone_info.duration_list = dur;
    tone_info.octave_list = oct;
    tone_info.volume = 20;
    tone_info.duration_fixed = 0;
    tone_info.octave_fixed = 0;
    tone_info.pause_fixed = 1;
    tone_info.break_on_keypress = 0;
    tone_info.interrupt = ( char * ) p_buz_int;

    buzzer_play_tones ( &tone_info );

//    free ( buzzer_interrupt );
    free ( song );
    free ( dur );
    free ( oct );

    return;

}

/*
// this should be a vibra thread, but i didn't add vibra yet
void
demo_1_2ndmainthread ( void )
{
    unsigned char *ptr;
    int len;

    return;
}
*/
