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


#include <apps/charger.h>
#include <hw/mbus.h>
#include <hw/io.h>
#include <hw/kpd.h>
#include <hw/ioports.h>
#include <hw/ccont.h>
#include <core/menu.h>
#include <core/lib.h>
#include <core/sched.h>
#include <apps/meas.h>

#define ub ccont_get_ub()
#define uc ccont_get_uc()
#define ic ccont_get_ic()
#define bi ccont_get_bi()

extern unsigned char tid_charger;
extern unsigned char tid_lcd;

unsigned char meas_mode = 0;
unsigned char meas_run = 1;
unsigned int meas_sps = 1500;   // samples per second
unsigned int meas_mvpp = 500;   // mV per pixel
unsigned int meas_delay = 0;
unsigned int meas_triglevel = 0;
unsigned int meas_pretrig = 0;
unsigned int *meas_backbuf = NULL;

int meas_old_power;
int meas_parms_charger;
int meas_parms_lcd;
unsigned char meas_tid_lcd_old;
unsigned char meas_tid_charger_old;

int
meas_lock_all ( void )
{
    // lol freeze 'em
/*    
    meas_tid_lcd_old = tid_lcd;
    meas_tid_charger_old = tid_charger;
    
    meas_parms_charger = sched_get_parm ( tid_charger );
    meas_parms_lcd = sched_get_parm ( tid_lcd );

    sched_set_parm ( tid_charger, SCHED_PARM_STOP );
    sched_set_parm ( tid_lcd, SCHED_PARM_STOP );
*/
    sched_set_parm ( 0xFF, SCHED_PARM_MASTER );

    meas_old_power = charger_get_power (  );
    charger_set_current ( 0 );
    charger_set_power (  );

    int_disable (  );
/*
    tid_lcd = 0xFF;
    tid_charger = 0xFF;
*/
}

int
meas_unlock_all ( void )
{
    int_enable (  );
    charger_set_current ( meas_old_power );
    charger_set_power (  );

    sched_set_parm ( 0xFF, SCHED_PARM_RUN );
/*    
    tid_charger = meas_tid_charger_old;
    tid_lcd = meas_tid_lcd_old;

    sched_set_parm ( tid_lcd, meas_parms_lcd );
    sched_set_parm ( tid_charger, meas_parms_charger );
*/
}

int
meas_get_minmax ( unsigned int *buf, int buflen, unsigned int *min, unsigned int *max, unsigned int *avg )
{
    int i = 0;

    *max = 0;
    *min = 0xFFFFFFFF;
    for ( i = 0; i < buflen; i++ )
    {
        if ( buf[i] > *max )
            *max = buf[i];
        if ( buf[i] < *min )
            *min = buf[i];
    }

    return 0;
}

int
meas_get_duration ( unsigned int *buf, int buflen, unsigned int mid, unsigned int *dur, unsigned int *rel )
{
    unsigned int p1 = 0;
    unsigned int p2 = 0;
    unsigned int p3 = 0;
    unsigned int pos = 0;
    unsigned int tol = lib_div ( mid, 20 );

    // find the first raise above <mid> level 
    // but go <tol> further
    while ( pos < buflen && buf[pos] <= mid + tol )
    {
        if ( !p1 && buf[pos] >= mid )
            p1 = pos;
        pos++;
    }
    if ( !p1 && pos < buflen && buf[pos] >= mid )
        p1 = pos;

    // find drop until <mid> level
    while ( pos < buflen && buf[pos] >= mid - tol )
    {
        if ( !p2 && buf[pos] <= mid )
            p2 = pos;
        pos++;
    }
    if ( !p2 && pos < buflen && buf[pos] <= mid )
        p2 = pos;

    // find the second raise above <mid> level  
    while ( pos < buflen && buf[pos] <= mid + tol )
    {
        if ( !p3 && buf[pos] >= mid )
            p3 = pos;
        pos++;
    }
    if ( !p3 && pos < buflen && buf[pos] >= mid )
        p3 = pos;

    if ( !( pos < buflen ) )
        return 0;

    if ( !( p3 - p2 ) || !( p2 - p1 ) )
        return 0;

    *dur = p3 - p1;
    *rel = lib_div ( 100 * ( p2 - p1 ), *dur );
    if ( *rel < 50 )
        *rel = 50 + ( 50 - *rel );
    return 1;
}

MENU_CALLBACK ( meas_setmode_meter )
{
    MENU_ONLY_SELECT;
    meas_mode = 0;
    meas_delay = 0;
    return MENU_EXIT;
}

MENU_CALLBACK ( meas_quit )
{
    MENU_ONLY_SELECT;
    meas_mode = 0;
    meas_run = 0;
    return MENU_EXIT;
}

MENU_CALLBACK ( meas_setmode_scope )
{
    MENU_ONLY_SELECT;
    meas_mode = 1;
    meas_delay = 0;
    return MENU_EXIT;
}

MENU_CALLBACK ( meas_setmode_freq )
{
    MENU_ONLY_SELECT;
    meas_mode = 2;
    meas_delay = 0;
    return MENU_EXIT;
}

MENU_CALLBACK ( meas_setmode_calib )
{
    MENU_ONLY_SELECT;
    meas_mode = 3;
    meas_delay = 0;
    return MENU_EXIT;
}


MENU_CALLBACK ( meas_stat_max )
{
    unsigned int min;
    unsigned int max;
    unsigned int avg;
    int buflen = 200;
    char txt[32];

    if ( meas_mode == 0 )
        buflen = 84;

    meas_get_minmax ( meas_backbuf, buflen, &min, &max, &avg );
    sprintf ( txt, "%i mV", max );
    menu_disp ( txt );

    return 0;
}

MENU_CALLBACK ( meas_stat_min )
{
    unsigned int min;
    unsigned int max;
    unsigned int avg;
    int buflen = 200;
    char txt[32];

    if ( meas_mode == 0 )
        buflen = 84;

    meas_get_minmax ( meas_backbuf, buflen, &min, &max, &avg );
    sprintf ( txt, "%i mV", min );
    menu_disp ( txt );

    return 0;
}

MENU_CALLBACK ( meas_stat_avg )
{
    unsigned int min;
    unsigned int max;
    unsigned int avg = 0;
    int buflen = 200;
    char txt[32];

    if ( meas_mode == 0 )
        buflen = 84;

    meas_get_minmax ( meas_backbuf, buflen, &min, &max, &avg );
    sprintf ( txt, "%i mV", avg );
    menu_disp ( txt );

    return 0;
}

/*
 * TODO: Calibration routine
 *       run the measure loop 2000 times and calculate the time needed.
 *       then fit variable sps to reflect the number of values with are
 *       gathered within 1s of measurement
 */

int
meas_main ( void )
{
    int i = 0;
    int pos = 0;
    int ret = 0;
    unsigned int dur = 0;
    unsigned int rel = 0;
    unsigned int avg = 0;
    unsigned int min = 0;
    unsigned int max = 0;
    unsigned int mid = 0;
    unsigned char key = 0;
    char *txt = NULL;
    menupoint menu[] = {
        {MENU_T_LIST, 3, NULL, NULL, "Menu"},
        {MENU_T_LIST, 4, NULL, NULL, "Mode"},
        {0, 0, meas_setmode_meter, NULL, "Meter"},
        {0, 0, meas_setmode_scope, NULL, "Scope"},
        {0, 0, meas_setmode_freq, NULL, "Freq"},
        {0, 0, meas_setmode_calib, NULL, "Calib"},
        {MENU_T_FIELD, 3, NULL, NULL, "Statistic"},
        {0, 0, meas_stat_min, NULL, "Min mV"},
        {0, 0, meas_stat_max, NULL, "Max mV"},
        {0, 0, meas_stat_avg, NULL, "Avg mV"},
        {0, 0, meas_quit, NULL, "Quit"},
        {MENU_T_LIST, 0, NULL, NULL, NULL}
    };


    meas_backbuf = ( unsigned int * ) malloc ( 200 * sizeof ( unsigned int ) );
    if ( !meas_backbuf )
        return 0;

    for ( i = 0; i < 200; i++ )
        meas_backbuf[i] = 0;

    txt = ( char * ) malloc ( 32 );
    if ( !txt )
        return 0;


    meas_lock_all (  );

    i = 0;
    meas_run = 1;

    while ( meas_run )
    {
        switch ( meas_mode )
        {
            case 0:
                ccont_reset_wdt (  );
                lcd_clr (  );
                sprintf ( txt, "%05i mV", uc );
                lcd_render_text ( 24, 0, txt, 1 );
                meas_backbuf[84] = uc;
                for ( i = 0; i < 84; i++ )
                {
                    meas_backbuf[i] = meas_backbuf[i + 1];
                    lcd_set_pixel ( i, 47 - lib_div ( meas_backbuf[i], meas_mvpp ), 1 );
                }
                lcd_to_screen_hw (  );
                key = kpd_getkey (  );
                if ( key != 0xFF )
                {
                    if ( key == KPD_SOFTBTN1 )
                    {
                        meas_unlock_all (  );
                        menu_show ( menu );
                        meas_lock_all (  );
                    }
                }
                break;
            case 1:
                if ( i == 200 )
                {
                    ccont_reset_wdt (  );
                    lcd_clr (  );
                    pos = 0;
                    while ( meas_backbuf[pos] >= meas_triglevel && pos < 200 )
                        pos++;
                    while ( meas_backbuf[pos] <= meas_triglevel && pos < 200 )
                        pos++;
                    if ( pos >= 200 )
                        pos = 0;
                    for ( i = 0; i < 84; i++ )
                        lcd_set_pixel ( i, 47 - lib_div ( meas_backbuf[pos + i], meas_mvpp ), 1 );
                    for ( i = 0; i < 5; i++ )
                        lcd_set_pixel ( i, 47 - lib_div ( meas_triglevel, meas_mvpp ), 1 );

                    sprintf ( txt, "%ius %imV", meas_delay, meas_triglevel );
                    lcd_render_text ( 0, 0, txt, 1 );
                    lcd_to_screen_hw (  );
                    key = kpd_getkey (  );
                    if ( key != 0xFF )
                    {
                        switch ( key )
                        {
                            case KPD_SOFTBTN1:
                                meas_unlock_all (  );
                                menu_show ( menu );
                                meas_lock_all (  );
                                break;
                            case KPD_UPARROW:
                                if ( meas_delay < 1000000 )
                                    meas_delay++;
/*                            sprintf ( txt, "dly: %i us", meas_delay );
                            lcd_clr (  );
                            lcd_render_text ( 0, 0, txt, 1 );
                            lcd_to_screen_hw (  );
                            ccont_reset_wdt (  );
*/
                                key = kpd_getkey (  );
                                if ( key != 0xFF )
                                    usleep_hard ( 50000 );
                                break;
                            case KPD_DWNARROW:
                                if ( meas_delay )
                                    meas_delay--;
/*
                            sprintf ( txt, "dly: %i us", meas_delay );
                            lcd_clr (  );
                            lcd_render_text ( 0, 0, txt, 1 );
                            lcd_to_screen_hw (  );
                            ccont_reset_wdt (  );
*/
                                key = kpd_getkey (  );
                                if ( key != 0xFF )
                                    usleep_hard ( 50000 );
                                break;
                            case 1:
                                meas_triglevel += 500;
/*
                            sprintf ( txt, "trig: %i mV", meas_triglevel );
                            lcd_clr (  );
                            lcd_render_text ( 0, 0, txt, 1 );
                            lcd_to_screen_hw (  );
                            ccont_reset_wdt (  );
*/
                                key = kpd_getkey (  );
                                if ( key != 0xFF )
                                    usleep_hard ( 50000 );

                                break;
                            case 4:
                                meas_triglevel -= 500;
/*
                            sprintf ( txt, "trig: %i mV", meas_triglevel );
                            lcd_clr (  );
                            lcd_render_text ( 0, 0, txt, 1 );
                            lcd_to_screen_hw (  );
                            ccont_reset_wdt (  );
*/
                                key = kpd_getkey (  );
                                if ( key != 0xFF )
                                    usleep_hard ( 50000 );
                                break;
                            default:
                                if ( key < 0x10 )
                                    usleep_hard ( key * 150 );
                                break;
                        }
                    }
                    i = 0;
                }
                meas_backbuf[i++] = uc;
                if ( meas_delay )
                    usleep_hard ( meas_delay );
                break;
            case 2:
                if ( i == 200 )
                {
                    ccont_reset_wdt (  );
                    lcd_clr (  );

                    meas_get_minmax ( meas_backbuf, 200, &min, &max, &avg );
                    mid = ( min + max ) / 2;
                    meas_triglevel = mid;

                    meas_pretrig = 10;
                    pos = meas_pretrig;
                    while ( meas_backbuf[pos] >= meas_triglevel && pos < 200 )
                        pos++;
                    while ( meas_backbuf[pos] <= meas_triglevel && pos < 200 )
                        pos++;
                    if ( pos >= 200 )
                        pos = meas_pretrig;
                    pos -= meas_pretrig;

                    if ( meas_get_duration ( meas_backbuf + pos, 200 - pos, mid, &dur, &rel ) )
                    {
                        for ( i = 0; i < 84; i++ )
                            lcd_set_pixel ( i, 47 - lib_div ( meas_backbuf[pos + i], meas_mvpp ), 1 );
                        for ( i = 0; i <= meas_pretrig; i++ )
                            lcd_set_pixel ( i, 47 - lib_div ( meas_triglevel, meas_mvpp ), 1 );
                        for ( i = 0; i < lib_div ( mid, meas_mvpp ); i++ )
                            lcd_set_pixel ( meas_pretrig, 47 - i, 1 );
                        if ( dur < 84 )
                            for ( i = 0; i < lib_div ( mid, meas_mvpp ); i++ )
                                lcd_set_pixel ( meas_pretrig + dur, 47 - i, 1 );
                        for ( i = 0; i < 3; i++ )
                            lcd_set_pixel ( meas_pretrig + i, 47 - 4, 1 );
                        if ( dur < 84 )
                            for ( i = 0; i < 3; i++ )
                                lcd_set_pixel ( meas_pretrig + dur - i, 47 - 4, 1 );
                        sprintf ( txt, "%02i", lib_div ( dur * 66667, 100000 ) );
                        if ( dur < 2 * 84 )
                            lcd_render_text ( meas_pretrig + ( dur / 2 ) - 4, 40, txt, 1 );
                        else
                            lcd_render_text ( meas_pretrig + 10, 40, txt, 1 );
                        sprintf ( txt, "Freq: %i Hz", lib_div ( meas_sps, dur ) );
                        lcd_render_text ( 0, 0, txt, 1 );
                        sprintf ( txt, "Duty:  %i%%", rel );
                        lcd_render_text ( 0, 8, txt, 1 );
                    }
                    else
                    {
                        sprintf ( txt, "Freq: -- Hz" );
                        lcd_render_text ( 0, 0, txt, 1 );
                    }

                    lcd_to_screen_hw (  );

                    key = kpd_getkey (  );
                    if ( key != 0xFF )
                    {
                        if ( key == KPD_SOFTBTN1 )
                        {
                            meas_unlock_all (  );
                            menu_show ( menu );
                            meas_lock_all (  );
                        }
                    }
                    i = 0;
                }
                meas_backbuf[i++] = uc;
                if ( meas_delay )
                    usleep_hard ( meas_delay );
                break;
            case 3:
                if ( i == 200 )
                {
                    ccont_reset_wdt (  );
                    lcd_clr (  );

                    meas_get_minmax ( meas_backbuf, 200, &min, &max, &avg );
                    mid = ( min + max ) / 2;
                    meas_triglevel = mid;

                    meas_pretrig = 10;
                    pos = meas_pretrig;
                    while ( meas_backbuf[pos] >= meas_triglevel && pos < 200 )
                        pos++;
                    while ( meas_backbuf[pos] <= meas_triglevel && pos < 200 )
                        pos++;
                    if ( pos >= 200 )
                        pos = meas_pretrig;
                    pos -= meas_pretrig;

                    if ( meas_get_duration ( meas_backbuf + pos, 200 - pos, mid, &dur, &rel ) )
                    {
                        for ( i = 0; i < 84; i++ )
                            lcd_set_pixel ( i, 47 - lib_div ( meas_backbuf[pos + i], meas_mvpp ), 1 );
                        for ( i = 0; i <= meas_pretrig; i++ )
                            lcd_set_pixel ( i, 47 - lib_div ( meas_triglevel, meas_mvpp ), 1 );
                        for ( i = 0; i < lib_div ( mid, meas_mvpp ); i++ )
                            lcd_set_pixel ( meas_pretrig, 47 - i, 1 );
                        if ( dur < 84 )
                            for ( i = 0; i < lib_div ( mid, meas_mvpp ); i++ )
                                lcd_set_pixel ( meas_pretrig + dur, 47 - i, 1 );
                        for ( i = 0; i < 3; i++ )
                            lcd_set_pixel ( meas_pretrig + i, 47 - 4, 1 );
                        if ( dur < 84 )
                            for ( i = 0; i < 3; i++ )
                                lcd_set_pixel ( meas_pretrig + dur - i, 47 - 4, 1 );
                        sprintf ( txt, "%02i", lib_div ( dur * 66667, 100000 ) );
                        if ( dur < 2 * 84 )
                            lcd_render_text ( meas_pretrig + ( dur / 2 ) - 4, 40, txt, 1 );
                        else
                            lcd_render_text ( meas_pretrig + 10, 40, txt, 1 );
                        sprintf ( txt, "Freq: %i Hz", lib_div ( meas_sps, dur ) );
                        lcd_render_text ( 0, 0, txt, 1 );
                        sprintf ( txt, "SPS:  %i", meas_sps );
                        lcd_render_text ( 0, 8, txt, 1 );
                        if ( lib_div ( meas_sps, dur ) < 50 )
                            meas_sps++;
                        if ( lib_div ( meas_sps, dur ) > 50 )
                            meas_sps--;
                    }
                    else
                    {
                        sprintf ( txt, "Freq: -- Hz" );
                        lcd_render_text ( 0, 0, txt, 1 );
                    }

                    lcd_to_screen_hw (  );

                    key = kpd_getkey (  );
                    if ( key != 0xFF )
                    {
                        if ( key == KPD_SOFTBTN1 )
                        {
                            meas_unlock_all (  );
                            menu_show ( menu );
                            meas_lock_all (  );
                        }
                    }
                    i = 0;
                }
                meas_backbuf[i++] = uc;
                if ( meas_delay )
                    usleep_hard ( meas_delay );
                break;
            default:
                break;
        }
    }

    meas_unlock_all (  );
    free ( meas_backbuf );
    free ( txt );
    meas_backbuf = NULL;

}
