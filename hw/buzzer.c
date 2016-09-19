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
#include <hw/snd.h>
#include <hw/io.h>
#include <hw/kpd.h>
#include <hw/buzzer.h>
#include <core/sched.h>

static int buzzer_sndpos = 0;
static int buzzer_sndcont = 0;
static int buzzer_sndsize = 0;
const unsigned char *buzzer_sndblock = NULL;
//unsigned int sleep_time = 110;

/*extern unsigned char tid_charger;
extern unsigned char tid_lcd;*/


// initialize buzzer
void
buzzer_init ( void )
{
    buzzer_sndcont = 0;
    //sleep_time = 110;
    _io_set ( IO_PUP_CTRL, _io_read ( IO_PUP_CTRL ) | 0x20 );
}

// sets volume of buzzer 0x00 - 0xff
void
buzzer_setvol ( unsigned char volume )
{
    _io_set ( IO_PUP_BUZ_V, volume );
}

// sets the frequency of the buzzer in Hz 
void
buzzer_setfreq ( unsigned short freq )
{
    unsigned short bfreq = 0;

    bfreq = lib_div ( 13000000, freq );

    _io_set ( IO_PUP_BUZ_FH, bfreq >> 8 );
    _io_set ( IO_PUP_BUZ_FL, bfreq & 0xFF );
}

// plays a soundfile until its end or an keypress
void
buzzer_snd_play ( const unsigned char *buf, int size )
{
    int pos = 0;
    unsigned char data = 0 /*, bufb[16] */ ;
    unsigned int time_1, time_2;
    unsigned int sleep_time = 50;

/*    sched_set_parm ( tid_charger, SCHED_PARM_STOP );
    sched_set_parm ( tid_lcd, SCHED_PARM_STOP );*/


//#define BUZ_INT

#ifdef BUZ_INT

    if ( buzzer_sndcont )
        return;
//  usleep ( 500000 );
#endif
    buzzer_setfreq ( 25000 );
#ifndef BUZ_INT
    sched_set_parm ( 0xFF, SCHED_PARM_MASTER );

    /*
     * time_1 = lib_get_time (  );
     * time_2 = time_1 + 500;
     */
    do
    {
        buzzer_setvol ( buf[pos] );

        usleep ( sleep_time );
        // reset wdt about every 0.5 second
        if ( !( pos % 4096 ) )
        {
            /*
             * if ( pos > 1 )
             * time_2 = lib_get_time (  );
             * 
             * sleep_time = lib_div ( 55000, time_2 - time_1 );
             * //sprintf ( bufb, "%d \00", time_2 - time_1 );
             * time_1 = time_2;
             */

            //lcd_clr ();
/*
	lcd_draw_rect ( 0, 0, 8*3, 8, 0 );
	lcd_render_text ( 0, 0, bufb, 1 );
	lcd_to_screen ( );
*/
            if ( kpd_getkey (  ) != 0xFF )
                pos = size;
        }

    }
    while ( ++pos < size );
    buzzer_setvol ( 0x00 );
    buzzer_setfreq ( 0 );
#else

    buzzer_sndblock = buf;
    buzzer_sndsize = size;
    buzzer_sndpos = 0;
    buzzer_sndcont = 1;
#endif

    sched_set_parm ( 0xFF, SCHED_PARM_RUN );
/*    sched_set_parm ( tid_lcd, parms_lcd );
    sched_set_parm ( tid_charger, parms_charger );*/

}


void
buzzer_snd_next ( void )
{
#ifdef BUZ_INT
    if ( !buzzer_sndcont )
        return;

    buzzer_setvol ( buzzer_sndblock[buzzer_sndpos] );
    if ( ++buzzer_sndpos >= buzzer_sndsize )
    {
        buzzer_setvol ( 0x00 );
        buzzer_setfreq ( 0 );
        buzzer_sndcont = 0;
    }
#endif
}


int
buzzer_snd_active ( void )
{
    return buzzer_sndcont;
}

void
buzzer_play_tones ( buzzer_tones_t * tone_info )
{

    unsigned int i = 0, tmp_freq;
    unsigned char c, auto_pause_toggle = 0, key = 0xFF;
    char dur, break_int = tone_info->interrupt[0];

    if ( tone_info->break_on_keypress )
        key = kpd_getkey (  );

    while ( tone_info->tone_list[i] && key == 0xFF && tone_info->interrupt[0] == break_int )
    {
        if ( tone_info->break_on_keypress )
            key = kpd_getkey (  );
        switch ( tone_info->tone_list[i] )
        {
            case 'd':
                tmp_freq = 200 * 9 / 8;
                break;
            case 'e':
                tmp_freq = 200 * 5 / 4;
                break;
            case 'f':
                tmp_freq = 200 * 4 / 3;
                break;
            case 'g':
                tmp_freq = 200 * 3 / 2;
                break;
            case 'a':
                tmp_freq = 200 * 5 / 3;
                break;
            case 'h':
                tmp_freq = 200 * 15 / 8;
                break;
            default:           // using for tone c also
                tmp_freq = 200;
                break;
        }

        for ( c = 1; c < ( tone_info->octave_fixed ? tone_info->octave_fixed : tone_info->octave_list[i] ); c++ )
            tmp_freq *= 2;

        if ( tone_info->tone_list[i] != 'p' && !auto_pause_toggle )
        {
            buzzer_setvol ( tone_info->volume );
            buzzer_setfreq ( tmp_freq );
        }

        if ( tone_info->duration_fixed )
            dur = tone_info->duration_fixed;
        else
            dur = tone_info->duration_list[i];

        if ( tone_info->pause_fixed && auto_pause_toggle )
            dur = tone_info->pause_fixed;

        usleep ( dur * 100000 );

        if ( tone_info->tone_list[i] != 'p' && !auto_pause_toggle )
            buzzer_setvol ( 0 );

        if ( auto_pause_toggle == 0 && tone_info->pause_fixed )
            auto_pause_toggle = 1;
        else
            auto_pause_toggle = 0;

        if ( !auto_pause_toggle )
            i++;

    }
}
