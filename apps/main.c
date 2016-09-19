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

#define __MADOS_MAIN_C__
//#include "snd_nightwish.h"
//#include "vangelis.h"
//#include "snd_boom.h"
//#include "apps/nightwish.h"
//#include "snd_ev_hello.h"
//#include "snd_hardcore.h"
//#include "snd_offspring.h"
#include <core/ipc.h>
#include <core/lib.h>
#include <core/fs.h>
#include <core/ui.h>
#include <core/sched.h>
#include <core/menu.h>
#include <hw/led.h>
#include <hw/timer.h>
#include <hw/lcd.h>
#include <hw/io.h>
#include <hw/kpd.h>
#include <hw/sim.h>
#include <hw/flash.h>
#include <hw/ccont.h>
#include <hw/vibra.h>
#include <hw/mbus.h>
#include <hw/int.h>
#include <hw/buzzer.h>
#include <apps/matrix.h>
#include <apps/charger.h>
#include <apps/tetris.h>
#include <apps/bomberman.h>
#include <apps/othello.h>
#include <apps/dct3.h>
#include <apps/dct4.h>
#include <apps/fire.h>
#include <apps/stars.h>
#include <core/bitmap.h>
#include <apps/screenshot.h>
#include <apps/txtreader.h>
#include <apps/st55gd55.h>
#include <apps/lgunlock.h>
#include <apps/hangman.h>
#include <apps/alcatel.h>
#include <apps/samsung.h>
#include <apps/meas.h>
#include <apps/demo_1.h>
#include <apps/tictactoe.h>
#include <core/softfloat.h>
#include <apps/picpaint.h>
#include <apps/gallery.h>
#include <apps/provider.h>
#include <apps/arcanoid.h>
#include <apps/madmedia.h>
#include <hw/phoneinfo.h>
#include <apps/engine3d.h>
#include <core/huffman.h>
#include <apps/f1.h>
#include <apps/sony_cmd_c1.h>
//#include <apps/dct2sec.h>
//#include <apps/dct2.h>
#include <apps/vitel.h>

#define NORMAL 0
#define CHARGE 1

#define FLASH_TEST_BASE 0x00300000


unsigned char tid_mbus = 0xFF;
unsigned char tid_lcd = 0xFF;
unsigned char tid_xbus;
unsigned char tid_charger;
unsigned char tid_ani;
extern unsigned int hard_calibrated;
unsigned char startup = NORMAL;
unsigned char mados_phone;


int thread_state = 0;

#define DEBUG(x)    if ( startup == NORMAL )\
		    {\
			lcd_clr();\
			lcd_render_text ( 0, 0, x, 1 );\
			lcd_to_screen_hw ();\
		    }

const phone_info_t mados_info[] = {
    {"3310 old", 0, 0, 0, 0, 0, 0, 48, 84, 0x44, 0},
    {"3310 new", 0, 0, 1, 0, 0, 0, 48, 84, 0x44, 0},
    {"3330 old", 0, 0, 0, 0, 0, 0, 48, 84, 0x44, 0},
    {"3330 new", 0, 0, 1, 0, 0, 0, 48, 84, 0x44, 0},
    {"8210", 1, 1, 1, 0, 0, 0, 48, 84, 0x44, 0},
    {"3410", 0, 0, 0, 1, 0, 0, 64, 96, 0x44, 0},    // spec sais lcd size 96x63
    {"3350", 0, 0, 0, 1, 0, 0, 64, 96, 0x44, 0},    // unsure about LCD size
    {"6210", 2, 2, 1, 0, 1, 1, 64, 96, 0x0, 1}, // actual size probably 96x60
    {"2100", 1, 1, 1, 0, 0, 0, 44, 96, 0x44, 0},
    {"5110", 0, 0, 0, 0, 2, 2, 48, 84, 0x44, 0}
};

MENU_CALLBACK ( main_txtreader );

#define SIM_DUMP(buf,text) \
{\
    char xtmp[30];\
    int xi;\
    lcd_clr (  );\
    lcd_render_text ( 0, 0, text, 1 );\
    for ( xi=0; xi<sim_get_buflen(); xi++ )\
    {\
	sprintf ( xtmp, "%02X", buf[xi] );\
	lcd_render_text ( xi*16, 8, xtmp, 1 );\
    }\
    sprintf ( xtmp, "%i bytes", sim_get_buflen (  ) );\
    lcd_render_text ( 0, 32, xtmp, 1 );\
    lcd_to_screen (  );\
    kpd_wait_release (  );\
    kpd_wait_keypress (  );\
    kpd_wait_release (  );\
    sim_clr_buf (  );\
}

MENU_CALLBACK ( main_read_prov )
{
    MENU_ONLY_SELECT;
    int len = 0;
    unsigned char tmp[8];
    unsigned char pin[8];
    unsigned char *buf = ( unsigned char * ) sim_get_buf (  );
    unsigned char *text = ( unsigned char * ) malloc ( 128 );
    unsigned char msg_res[] = { 0xa0, 0xc0, 0x00, 0x00, 0x18 }; //get response
    unsigned char msg0[7] = { 0xa0, 0xa4, 0x00, 0x00, 0x02, 0x3f, 0x00 };   //select 3f00 MF
    unsigned char msg1[7] = { 0xa0, 0xa4, 0x00, 0x00, 0x02, 0x7f, 0x21 };   //select 7f20 DFgsm
    unsigned char msg2[7] = { 0xa0, 0xa4, 0x00, 0x00, 0x02, 0x6f, 0x46 };   //select 6f46 EFSPN
    unsigned char msg3[5] = { 0xa0, 0xb0, 0x00, 0x00, 0x11 };   //read binary

    memcpy ( tmp, msg_res, 5 );

    // clean last results
    sim_transmit ( tmp, 5 );
    sim_clr_buf (  );

    sim_transmit ( msg0, 7 );
    usleep ( 30000 );
    SIM_DUMP ( buf, "select 3F00" );

    sim_transmit ( tmp, 5 );
    usleep ( 30000 );
    SIM_DUMP ( buf, "Response 3F00" );

    sim_transmit ( msg1, 7 );
    usleep ( 30000 );
    SIM_DUMP ( buf, "select 7F20" );

    sim_transmit ( tmp, 5 );
    usleep ( 30000 );
    SIM_DUMP ( buf, "Response 7F20" );

    sim_transmit ( msg2, 7 );
    usleep ( 30000 );
    SIM_DUMP ( buf, "select 6F46" );

    sim_transmit ( tmp, 5 );
    usleep ( 30000 );
    SIM_DUMP ( buf, "Response 6F46" );

    sim_transmit ( msg3, 5 );
    usleep ( 30000 );
    SIM_DUMP ( buf, "Read Binary" );

//    tmp[5] = 0x13;
    sim_transmit ( tmp, 5 );
    usleep ( 30000 );
    SIM_DUMP ( buf, "Response Read" );

    sim_transmit ( tmp, 5 );
    usleep ( 30000 );
    SIM_DUMP ( buf, "test-Response" );

    free ( text );
}

MENU_CALLBACK ( main_init_pin )
{
    MENU_ONLY_SELECT;
    int len = 0;
    unsigned char pin[8];
    unsigned char *buf = ( unsigned char * ) sim_get_buf (  );
    unsigned char *msg = ( unsigned char * ) malloc ( 13 );
    unsigned char *text = ( unsigned char * ) malloc ( 128 );
    unsigned char msg_pin[] = { 0xa0, 0x20, 0x00, 0x01, 0x08 }; // verify CHV
    unsigned char msg_res[] = { 0xa0, 0xc0, 0x00, 0x00, 0x0f }; //get response

    ui_gettext ( "Enter PIN", 8, pin, UI_TYPE_NUMBER );
    len = strlen ( pin );
    memset ( msg, 0xFF, 13 );
    memcpy ( msg, msg_pin, 5 );
    memcpy ( &( msg[5] ), pin, len );

    sim_clr_buf (  );

/*
    if you are sure that yo want to kill your SIM
    then you are allowed to uncomment this highly experimental code

    sim_transmit ( msg, 13 );
    usleep ( 30000 );
//    sim_clr_buf (  );
    sim_transmit ( msg_res, 5 );
    usleep ( 30000 );
*/

    lcd_clr (  );
    sprintf ( text, "%02X%02X%02X%02X%02X", buf[0], buf[1], buf[2], buf[3], buf[4] );
    lcd_render_text ( 0, 0, text, 1 );
    sprintf ( text, "%02X%02X%02X%02X%02X", buf[5], buf[6], buf[7], buf[8], buf[9] );
    lcd_render_text ( 0, 8, text, 1 );
    sprintf ( text, "%02X%02X%02X%02X%02X", buf[10], buf[11], buf[12], buf[13], buf[14] );
    lcd_render_text ( 0, 16, text, 1 );
    sprintf ( text, "%02X%02X%02X%02X%02X", buf[15], buf[16], buf[17], buf[18], buf[19] );
    lcd_render_text ( 0, 24, text, 1 );
    sprintf ( text, "%i bytes", sim_get_buflen (  ) );
    lcd_render_text ( 0, 32, text, 1 );
    lcd_to_screen (  );
    kpd_wait_release (  );
    kpd_wait_keypress (  );
    kpd_wait_release (  );
    sim_clr_buf (  );

    free ( msg );
    free ( text );
}


MENU_CALLBACK ( main_init_sim )
{
    MENU_ONLY_SELECT;
    unsigned char *buf = ( unsigned char * ) sim_get_buf (  );
    unsigned char *text = ( unsigned char * ) malloc ( 128 );

    sim_clr_buf (  );
    sim_initcontrol (  );
    ccont_set_simvsel ( CCONT_VSEL_3V );
    sim_initcontrol (  );
    sim_reset (  );
    usleep ( 80000 );

    sim_setcontrol (  );

    lcd_clr (  );
    sprintf ( text, "%02X%02X%02X%02X%02X", buf[0], buf[1], buf[2], buf[3], buf[4] );
    lcd_render_text ( 0, 0, text, 1 );
    sprintf ( text, "%02X%02X%02X%02X%02X", buf[5], buf[6], buf[7], buf[8], buf[9] );
    lcd_render_text ( 0, 8, text, 1 );
    sprintf ( text, "%02X%02X%02X%02X%02X", buf[10], buf[11], buf[12], buf[13], buf[14] );
    lcd_render_text ( 0, 16, text, 1 );
    sprintf ( text, "%02X%02X%02X%02X%02X", buf[15], buf[16], buf[17], buf[18], buf[19] );
    lcd_render_text ( 0, 24, text, 1 );
    sprintf ( text, "%i bytes", sim_get_buflen (  ) );
    lcd_render_text ( 0, 32, text, 1 );
    lcd_to_screen (  );
    kpd_wait_keypress (  );
    kpd_wait_release (  );
    sim_clr_buf (  );

    free ( text );
}


MENU_CALLBACK ( main_sim )
{

    MENU_ONLY_SELECT;

    int status;
    int pos = 0;
    int done = 0;
    unsigned char key;
    unsigned char *buf = ( unsigned char * ) sim_get_buf (  );
    unsigned char *text = ( unsigned char * ) malloc ( 128 );
    unsigned char msg0[7] = { 0xa0, 0xa4, 0x00, 0x00, 0x02, 0x3f, 0x00 };   //select 3f00 MF
    unsigned char msg1[7] = { 0xa0, 0xa4, 0x00, 0x00, 0x02, 0x7f, 0x10 };   //select 7f10 DFtelecom
    unsigned char msg2[7] = { 0xa0, 0xa4, 0x00, 0x00, 0x02, 0x6f, 0x3c };   //select 6f3c EFsms
    unsigned char msg3[5] = { 0xa0, 0xb2, 0x00, 0x04, 0xb0 };   //read current record
    unsigned char msg4[5] = { 0xa0, 0xb2, 0x00, 0x03, 0xb0 };   //read previous record
    unsigned char msg5[5] = { 0xa0, 0xb2, 0x00, 0x02, 0xb0 };   //read next record
    unsigned char msg6[5] = { 0xa0, 0xc0, 0x00, 0x00, 0x0f };   //get response

    while ( !done )
    {
        key = kpd_getkey (  );
        switch ( key )
        {
            case KPD_CANCEL:
                done = 1;
                kpd_wait_release (  );
                break;
            case 1:
                sim_clr_buf (  );

/*		sim_initcontrol ();
		ccont_set_simvsel ( CCONT_VSEL_3V );
		sim_initcontrol ();
		sim_reset ();
		usleep(80000);
		sim_setcontrol ();
*/
                sim_transmit ( msg0, 7 );
                usleep ( 30000 );

                sim_transmit ( msg1, 7 );
                usleep ( 30000 );

                sim_transmit ( msg2, 7 );
                usleep ( 30000 );

                sim_transmit ( msg3, 5 );
                usleep ( 30000 );

                sim_transmit ( msg6, 5 );
                usleep ( 30000 );
                kpd_wait_release (  );
                break;
            case 2:
                sim_clr_buf (  );
                sim_transmit ( msg4, 5 );
                kpd_wait_release (  );
                break;
            case 3:
                sim_clr_buf (  );
                sim_transmit ( msg5, 5 );
                kpd_wait_release (  );
                break;
            case KPD_DWNARROW:
                if ( pos < 8 )
                    pos++;
                break;
            case KPD_UPARROW:
                if ( pos > 0 )
                    pos--;
                break;
            default:
                break;
        }
        lcd_clr (  );
        sprintf ( text, "%02X%02X%02X%02X%02X", buf[pos * 20 + 0], buf[pos * 20 + 1], buf[pos * 20 + 2], buf[pos * 20 + 3], buf[pos * 20 + 4] );
        lcd_render_text ( 0, 0, text, 1 );
        sprintf ( text, "%02X%02X%02X%02X%02X", buf[pos * 20 + 5], buf[pos * 20 + 6], buf[pos * 20 + 7], buf[pos * 20 + 8], buf[pos * 20 + 9] );
        lcd_render_text ( 0, 8, text, 1 );
        sprintf ( text, "%02X%02X%02X%02X%02X", buf[pos * 20 + 10], buf[pos * 20 + 11], buf[pos * 20 + 12], buf[pos * 20 + 13], buf[pos * 20 + 14] );
        lcd_render_text ( 0, 16, text, 1 );
        sprintf ( text, "%02X%02X%02X%02X%02X", buf[pos * 20 + 15], buf[pos * 20 + 16], buf[pos * 20 + 17], buf[pos * 20 + 18], buf[pos * 20 + 19] );
        lcd_render_text ( 0, 24, text, 1 );
        sprintf ( text, "%i bytes", sim_get_buflen (  ) );
        lcd_render_text ( 0, 32, text, 1 );
        lcd_to_screen (  );
    }
    free ( text );
}



MENU_CALLBACK ( main_ttt )
{
    MENU_ONLY_SELECT;
    ttt_main (  );
}

MENU_CALLBACK ( main_media )
{
    MENU_ONLY_SELECT;
    mediamain (  );
}



MENU_CALLBACK ( main_snake )
{
    MENU_ONLY_SELECT;
#ifndef EMBED
    snake_main (  );
#endif
}

MENU_CALLBACK ( main_othello )
{
    MENU_ONLY_SELECT;
#ifndef EMBED
    othello_main (  );
#endif
}

MENU_CALLBACK ( main_meas )
{
    MENU_ONLY_SELECT;
    meas_main (  );
}

MENU_CALLBACK ( main_picpaint )
{
    MENU_ONLY_SELECT;
    picpaint_main (  );         //not finished yet
}


MENU_CALLBACK ( main_tetris )
{
    MENU_ONLY_SELECT;
    tetris_main (  );
}

MENU_CALLBACK ( main_arcanoid )
{
    MENU_ONLY_SELECT;
    marc_main (  );
}


MENU_CALLBACK ( main_matrix )
{
    MENU_ONLY_SELECT;
    matrix_main (  );
}

MENU_CALLBACK ( main_bman )
{
    MENU_ONLY_SELECT;
#ifndef EMBED
    bomberman_main (  );
#endif
}

MENU_CALLBACK ( main_hangman )
{
    MENU_ONLY_SELECT;
    hangman_main (  );

}

MENU_CALLBACK ( main_stars )
{
    MENU_ONLY_SELECT;
#ifndef EMBED
    stars_main (  );
#endif
}

MENU_CALLBACK ( main_starfield )
{
    MENU_ONLY_SELECT;
#ifndef EMBED
    starfield_main (  );
#endif
}

MENU_CALLBACK ( main_fire )
{
    MENU_ONLY_SELECT;
#ifndef EMBED
    fire_main ( 1 );
#endif
}

MENU_CALLBACK ( main_contrast )
{
    int i = 0;
    int c = 0;
    int cold = 0;
    unsigned char key = 0;
    char text[32];

    MENU_ONLY_SELECT;

    kpd_wait_release (  );
    c = lcd_get_contrast (  );
    cold = lcd_get_contrast (  );
    while ( 1 )
    {
        sprintf ( text, "contrast 0x%02X", c );
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8 + 1, text, 1 );
        lcd_draw_line ( 10, 20, 76, 20, 1 );
        lcd_draw_line ( 10, 28, 76, 28, 1 );
        lcd_draw_line ( 10, 20, 10, 28, 1 );
        lcd_draw_line ( 76, 20, 76, 28, 1 );
        for ( i = 0; i <= 4; i++ )
            lcd_draw_line ( 12, 22 + i, 12 + 2 * ( c / 8 ), 22 + i, 1 );
        lcd_to_screen (  );
        lcd_set_contrast ( c );

        buzzer_setvol ( 0x0 );
        while ( ( key = kpd_getkey (  ) ) == 0xff ) ;


        if ( key == 0x14 )
        {
            lcd_set_contrast ( cold );
            break;
        }
        if ( key == KPD_SOFTBTN1 )
        {
            lcd_set_contrast ( c );
            break;
        }
        switch ( key )
        {
            case 0x13:
                if ( c != 0 )
                    c--;
                break;
            case 0x16:
                if ( c < 0xFE )
                    c++;
                break;
            default:
                break;
        }
        buzzer_setfreq ( 500 + ( c * 50 ) );
        buzzer_setvol ( 0x40 );

        usleep ( 50000 );

    }
}


MENU_CALLBACK ( main_vibra )
{
    int i = 0;
    int vibra = 0;
    unsigned char key = 0;

    MENU_ONLY_SELECT;

    vibra_setfreq ( 0 );
    vibra_setmode ( 2 );
    vibra = 0;
    while ( 1 )
    {
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8 + 1, "  vibra", 1 );
        lcd_draw_line ( 10, 20, 76, 20, 1 );
        lcd_draw_line ( 10, 28, 76, 28, 1 );
        lcd_draw_line ( 10, 20, 10, 28, 1 );
        lcd_draw_line ( 76, 20, 76, 28, 1 );
        for ( i = 0; i <= 4; i++ )
            lcd_draw_line ( 12, 22 + i, 12 + 2 * vibra, 22 + i, 1 );
        lcd_to_screen (  );
        vibra_setfreq ( vibra );
        key = kpd_getkey (  );
        while ( key == 0xff )
        {
            key = kpd_getkey (  );
        }
        if ( key == KPD_CANCEL )
            break;
        switch ( key )
        {
            case 0x13:
                if ( vibra != 0 )
                    vibra--;
                break;
            case 0x16:
                if ( vibra < 31 )
                    vibra++;
                break;
            default:
                break;
        }
        usleep ( 50000 );

    }
    vibra_setmode ( 0 );
    vibra_setfreq ( 0 );
}

MENU_CALLBACK ( main_dsp )
{
    int i = 0;
    int k = 0;
    int fail = 0;
    unsigned char buf[32];

    MENU_ONLY_SELECT;

    for ( i = 0; i < 0x1F8; i++ )
    {
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8 + 1, "DSP test", 1 );
        lcd_draw_line ( 10, 20, 76, 20, 1 );
        lcd_draw_line ( 10, 28, 76, 28, 1 );
        lcd_draw_line ( 10, 20, 10, 28, 1 );
        lcd_draw_line ( 76, 20, 76, 28, 1 );
        for ( k = 0; k <= 4; k++ )
            lcd_draw_line ( 12, 22 + k, 12 + ( i >> 3 ), 22 + k, 1 );
        lcd_to_screen (  );
        k = dsp_test (  );
        if ( k )
        {
            lcd_type_text_2 ( 0, 1 * 8, 3, "DSP fail", 1 );
            lib_hexconv ( buf, k );
            lcd_render_text ( 0, 2 * 8, buf, 1 );
            lib_hexconv ( buf, io_read_word ( 0x00010000 ) );
            lcd_render_text ( 0, 3 * 8, buf, 1 );
            lib_hexconv ( buf, io_read_word ( 0x00010002 ) );
            lcd_render_text ( 0, 4 * 8, buf, 1 );
            lcd_to_screen (  );
            sleep ( 5 );
            i = 0xFF;
            fail = 1;
        }
    }
    for ( i = 0; i < 0x1F8; i++ )
    {
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8 + 1, "CCONT test", 1 );
        lcd_draw_line ( 10, 20, 76, 20, 1 );
        lcd_draw_line ( 10, 28, 76, 28, 1 );
        lcd_draw_line ( 10, 20, 10, 28, 1 );
        lcd_draw_line ( 76, 20, 76, 28, 1 );
        for ( k = 0; k <= 4; k++ )
            lcd_draw_line ( 12, 22 + k, 12 + ( i >> 3 ), 22 + k, 1 );
        lcd_to_screen (  );
        k = ccont_test (  );
        if ( k )
        {
            lcd_type_text_2 ( 0, 1 * 8, 3, "CCONT fail", 1 );
            lcd_to_screen (  );
            sleep ( 5 );
            i = 0xFF;
            fail = 1;
        }
    }
    if ( fail )
    {
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8 + 1, " at least ", 1 );
        lcd_render_text ( 0, 1 * 8 + 1, " one test ", 1 );
        lcd_render_text ( 0, 2 * 8 + 1, "has failed", 1 );
        lcd_to_screen (  );
        ksleep ( 20 );
    }
}

MENU_CALLBACK ( main_charger )
{
    unsigned char *buf;
    unsigned char *buf2;
    int current = 0;

    MENU_ONLY_SELECT;

//    mbus_start ( MBUS_SPEED_57600 );


    buf = ( unsigned char * ) malloc ( 32 );
    buf2 = ( unsigned char * ) malloc ( 32 );
    while ( kpd_getkey (  ) != KPD_CANCEL )
    {

        mbus_start ( MBUS_SPEED_57600 );
//  mbus_addbuf ( "[success]", 9 );
        mbus_addbuf ( "\x0C", 1 );
        lcd_clr (  );
        mbus_addbuf ( "\x0C", 1 );

        sprintf ( buf, "%04i mV  Ubatt", charger_get_ub (  ) );
        mbus_addbuf ( buf, strlen ( buf ) );
        mbus_addbuf ( "\r\n", 2 );
        lcd_render_text ( 0, 0 * 8, buf, 1 );
        sprintf ( buf, "%04i mV  Unom", charger_get_un (  ) );
        mbus_addbuf ( buf, strlen ( buf ) );
        mbus_addbuf ( "\r\n", 2 );
        lcd_render_text ( 0, 1 * 8, buf, 1 );
        sprintf ( buf, "%04i mV  Ucharg", charger_get_uc (  ) );
        mbus_addbuf ( buf, strlen ( buf ) );
        mbus_addbuf ( "\r\n", 2 );
        lcd_render_text ( 0, 2 * 8, buf, 1 );
        sprintf ( buf, "%04i mA  Icharg", charger_get_ic (  ) );
        mbus_addbuf ( buf, strlen ( buf ) );
        mbus_addbuf ( "\r\n", 2 );
        lcd_render_text ( 0, 3 * 8, buf, 1 );

        sprintf ( buf, "" );
        switch ( charger_get_state (  ) )
        {
            case BATT_OVERLOAD:
                strcat ( buf, "OL " );
                break;
            case BATT_OVERDISCHARGED:
                strcat ( buf, "OD " );
                break;
            case BATT_SLOWCHARGE:
                strcat ( buf, "SC " );
                break;
            case BATT_CHARGE:
                strcat ( buf, "NC " );
                break;
            case BATT_DISCHARGE:
                strcat ( buf, "DC " );
                break;
            case BATT_CHECK:
                strcat ( buf, "CK " );
                break;
            case BATT_NORM:
                strcat ( buf, "NO " );
                break;
            case BATT_LOW:
                strcat ( buf, "LW " );
                break;
            default:
                strcat ( buf, "xx " );
                break;
        }
        switch ( charger_get_power (  ) )
        {
            case CHARGE_SLOW:
                strcat ( buf, "SC " );
                break;
            case CHARGE_FAST:
                strcat ( buf, "FC " );
                break;
            case CHARGE_CHECK:
                strcat ( buf, "CK " );
                break;
            case CHARGE_OFF:
                strcat ( buf, "OF " );
                break;
            default:
                strcat ( buf, "xx " );
                break;
        }
/*
	if ( kpd_getkey() == KPD_UPARROW )
	    current++;
	if ( kpd_getkey() == KPD_DWNARROW )
	    current--;
	charger_set_current ( current );
	charger_set_power ();
	sprintf ( buf2, "%i", current );
	strcat ( buf, buf2 );
*/
        sprintf ( buf2, "%s", charger_get_battname (  ) );
        strcat ( buf, buf2 );
        mbus_addbuf ( buf, strlen ( buf ) );
        mbus_addbuf ( "\r\n", 2 );
        lcd_render_text ( 0, 4 * 8, buf, 1 );
        sprintf ( buf, "d:%04i c:%04i", charger_get_discharge (  ), charger_get_maxcurrent (  ) );
        mbus_addbuf ( buf, strlen ( buf ) );
        mbus_addbuf ( "\r\n", 2 );
        mbus_addbuf ( "\r\n", 2 );
        lcd_render_text ( 0, 5 * 8, buf, 1 );
        lcd_to_screen (  );
        usleep ( 100000 );
    }
    free ( buf );
    free ( buf2 );
}

MENU_CALLBACK ( main_adval )
{
    unsigned char buf[256];

    MENU_ONLY_SELECT;

    charger_lock (  );
    while ( kpd_getkey (  ) == 0xFF )
    {
        lcd_clr (  );
        sprintf ( buf, "%i mV", ccont_get_ub (  ) );
        lcd_render_text ( 0, 0 * 8, buf, 1 );
        sprintf ( buf, "%i mV", ccont_get_uc (  ) );
        lcd_render_text ( 0, 1 * 8, buf, 1 );
        sprintf ( buf, "%i mA", ccont_get_ic (  ) );
        lcd_render_text ( 0, 2 * 8, buf, 1 );
        lib_hexconv ( buf, ccont_read_adval ( 0x04 ) );
        lcd_render_text ( 0, 3 * 8, buf, 1 );
        lib_hexconv ( buf, ccont_read_adval ( 0x03 ) );
        lcd_render_text ( 0, 4 * 8, buf, 1 );
        lcd_to_screen (  );
    }
    charger_unlock (  );
}

MENU_CALLBACK ( main_int )
{
    int i = 0;
    int mode = 0;
    int done = 0;
    unsigned char key;
    unsigned char buf[32];

    MENU_ONLY_SELECT;

    while ( !done )
    {
        key = kpd_getkey (  );
        if ( key != 0xFF )
        {
            switch ( key )
            {
                case KPD_DWNARROW:
                    if ( mode < 3 )
                        mode++;
                    kpd_wait_release (  );
                    break;
                case KPD_UPARROW:
                    if ( mode )
                        mode--;
                    kpd_wait_release (  );
                    break;
                case KPD_CANCEL:
                    done = 1;
                    kpd_wait_release (  );
                    break;
                default:
                    break;
            }
        }
        lcd_clr (  );
        switch ( mode )
        {
            case 0:
                lcd_render_text ( 0, 0 * 8, "FIQ 0-4", 1 );
                for ( i = 0; i < 0x05; i++ )
                {
                    sprintf ( buf, "%08X %i", int_fiq_get_handler ( i ), int_get_fiq_count ( i ) );
                    lcd_render_text ( 0, ( i + 1 ) * 8, buf, 1 );
                }
                break;
            case 1:
                lcd_render_text ( 0, 0 * 8, "FIQ 5-8", 1 );
                for ( i = 5; i < 0x09; i++ )
                {
                    sprintf ( buf, "%08X %i", int_fiq_get_handler ( i ), int_get_fiq_count ( i ) );
                    lcd_render_text ( 0, ( i - 4 ) * 8, buf, 1 );
                }
                break;
            case 2:
                lcd_render_text ( 0, 0 * 8, "IRQ 0-4", 1 );
                for ( i = 0; i < 0x05; i++ )
                {
                    sprintf ( buf, "%08X %i", int_irq_get_handler ( i ), int_get_irq_count ( i ) );
                    lcd_render_text ( 0, ( i + 1 ) * 8, buf, 1 );
                }
                break;
            case 3:
                lcd_render_text ( 0, 0 * 8, "IRQ 5-8", 1 );
                for ( i = 5; i < 0x09; i++ )
                {
                    sprintf ( buf, "%08X %i", int_irq_get_handler ( i ), int_get_irq_count ( i ) );
                    lcd_render_text ( 0, ( i - 4 ) * 8, buf, 1 );
                }
                break;
            default:
                break;
        }
        lcd_to_screen (  );
    }
}

MENU_CALLBACK ( main_mdi )
{
    unsigned char packet[32];
    unsigned short mdiPktTest[] = { 0x3001 };

    MENU_ONLY_SELECT;

    if ( mdi_poll_receive (  ) >= 0 )
    {
        /*
         * packet available 
         */
        mdi_receive ( packet );
        //IO_flashdbg(0x06000000, packet, packet[0]+2);
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8 + 1, "MDI", 1 );
        lcd_render_text ( 0, 1 * 8 + 1, "packet", 1 );
        lcd_render_text ( 0, 2 * 8 + 1, "received", 1 );
        lcd_to_screen (  );
        sleep ( 1 );
    }

    if ( mdi_send ( ( unsigned char * ) mdiPktTest ) )
    {
        //DSP_interrupt();
        dsp_genint (  );
        /*
         * Success 
         */
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8 + 1, "MDI", 1 );
        lcd_render_text ( 0, 1 * 8 + 1, "packet", 1 );
        lcd_render_text ( 0, 2 * 8 + 1, "sent", 1 );
        lcd_to_screen (  );
        sleep ( 1 );
    }
    else
    {
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8 + 1, "MDI", 1 );
        lcd_render_text ( 0, 1 * 8 + 1, "packet", 1 );
        lcd_render_text ( 0, 2 * 8 + 1, "failed", 1 );
        lcd_to_screen (  );
        sleep ( 1 );
    }
}

MENU_CALLBACK ( main_ui )
{
    char text[51];
    char *test_buttons[] = { "BTN1", "btn2", "B !", "hallo ?", "test", "x", NULL };
    int i = 0;

    MENU_ONLY_SELECT;

    memset ( text, 0x00, 50 );
    i = ui_getnumber ( "enter", 7, 3 );
    ui_gettext ( "type now!", sizeof ( text ), text, UI_TYPE_ALL );


    for ( i = 0; i > -16; i-- )
    {
        lcd_clr (  );
        lcd_render_text ( 0, i + 0, "You typed...", 1 );
        // prints only 1 line... but doens't matter
        lcd_render_text ( 0, i + 8, text, 1 );
        lcd_to_screen (  );
        usleep ( 100000 );
    }

    //ui_draw_scrolltext - test
    ui_draw_scrolltext ( "this is a test for the draw-scrolltext function ... if u see the text, the function runs well and you might be happy. happiness is a kind of shit, just like this phrase." );
    //sleep ( 2 );
    kpd_wait_release (  );
    i = ui_dialog_box ( "select !", test_buttons );
    kpd_wait_release (  );
    if ( i != 0xFF )
        sprintf ( text, "you selected button %d ! this button was labeled with %s .\x00", i, test_buttons[i] );
    else
        sprintf ( text, "you canceled, your selected button was NOT recognized!" );
    ui_draw_scrolltext ( text );
    kpd_wait_release (  );

}

MENU_CALLBACK ( main_buzzer )
{
    //char tone_list[] = "cdefgahpcpdpepfpgpaph";
    //char tone_dur[] = { 2, 3, 2, 3, 2, 3, 4, 5, 2, 1, 3, 4, 7, 3, 8, 1, 2, 6, 6, 5, 4, 0 };

    //char entchen[] = "cpdpepfpgpgpapapapapgpapapapapgpfpfpfpfpepepgpgpgpgpc";
    char entchen[] = "cdefggaaaagaaaagffffeeggggc";
    //char entchen_dauer[] = { 2, 1, 2, 1, 2, 1, 2, 1, 4, 1, 4, 1, 2, 1, 2, 1, 2, 1, 2, 1, 8, 1, 2, 1, 2, 1, 2, 1, 2, 1, 8, 1, 2, 1, 2, 1, 2, 1, 2, 1, 4, 1, 4, 1, 2, 1, 2, 1, 2, 1, 2, 1, 8, 0 };
    char entchen_dauer[] = { 2, 2, 2, 2, 4, 4, 2, 2, 2, 2, 8, 2, 2, 2, 2, 8, 2, 2, 2, 2, 4, 4, 2, 2, 2, 2, 8 };
    //unsigned char octave[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 };

    buzzer_tones_t tone_info;
    tone_info.tone_list = entchen;
    tone_info.duration_list = entchen_dauer;
    tone_info.octave_list = "\x00\x00";
    tone_info.volume = 20;
    tone_info.duration_fixed = 0;
    tone_info.octave_fixed = 1;
    tone_info.pause_fixed = 1;
    tone_info.interrupt = "\x00\x00";
    tone_info.break_on_keypress = 1;

    MENU_ONLY_SELECT;

    kpd_wait_release (  );

    buzzer_play_tones ( &tone_info );

    kpd_wait_release (  );

    //buzzer_snd_play ( track1, sizeof( track1 ) );
//  st55gd55_main ( );

}

MENU_CALLBACK ( main_demo_1 )
{

    MENU_ONLY_SELECT;

    kpd_wait_release (  );

    demo_1_main (  );

    kpd_wait_release (  );

}

MENU_CALLBACK ( main_keytest )
{

    char buf[16];

    MENU_ONLY_SELECT;

    while ( !( kpd_getkey (  ) == 1 && kpd_get_second_key (  ) == 2 ) )
    {
        lcd_clr (  );
        lcd_render_text ( ( 84 - lcd_get_text_width ( "key test" ) ) / 2, 0, "key test", 1 );
        sprintf ( buf, "key1 0x%02X\0", kpd_readkey (  ) );
        lcd_render_text ( ( 84 - lcd_get_text_width ( buf ) ) / 2, 8, buf, 1 );
        sprintf ( buf, "key2 0x%02X\0", kpd_get_second_key (  ) );
        lcd_render_text ( ( 84 - lcd_get_text_width ( buf ) ) / 2, 16, buf, 1 );
        sprintf ( buf, "key3 0x%02X\0", kpd_get_third_key (  ) );
        lcd_render_text ( ( 84 - lcd_get_text_width ( buf ) ) / 2, 24, buf, 1 );
        lcd_render_text ( ( 84 - lcd_get_text_width ( "1+2 quits" ) ) / 2, 32, "1+2 quits", 1 );
        lcd_to_screen_hw (  );
    }

    kpd_wait_release (  );

}

MENU_CALLBACK ( main_softfloattest )
{
/*    int one;
    int two;
    int sum;
    float test1 = 1.234;
    float test2 = 1.234;
    float32 testfloat = ( float ) 321.887;  //doesn't work - think because of big/little endian :(
    float32 f_one, f_two, f_sum;
    char buf[16];

    MENU_ONLY_SELECT;
    lcd_clr (  );
    test2++;
    lcd_clr (  );
    test1 += test2;
    lcd_clr (  );
    test1 += main_creditz (  );
    kpd_wait_release (  );
    test1 += test2;
    lcd_clr (  );

    lcd_render_text ( 0, 0, "-page1-", 1 );

    sprintf ( buf, "i2f2i: %d", float32_to_int32 ( test1 ) );
    sprintf ( buf, "i2f2i: %d", float32_to_int32 ( int32_to_float32 ( 1234 ) ) );
    lcd_render_text ( 0, 8, buf, 1 );   // should return 1234

    f_one = int32_to_float32 ( 50 );
    sprintf ( buf, "50*50: %d", float32_to_int32 ( float32_mul ( f_one, f_one ) ) );
    lcd_render_text ( 0, 16, buf, 1 );

    sprintf ( buf, "1234/87: %d", float32_to_int32 ( float32_div ( int32_to_float32 ( 1234 ), int32_to_float32 ( 87 ) ) ) );
    lcd_render_text ( 0, 24, buf, 1 );

    sprintf ( buf, "sqrt1000: %d", float32_to_int32 ( float32_sqrt ( int32_to_float32 ( 1000 ) ) ) );
    lcd_render_text ( 0, 32, buf, 1 );

    sprintf ( buf, "%d", float64_to_int32 ( float64_mul ( int32_to_float64 ( 1234 ), int32_to_float64 ( 321 ) ) ) );
    lcd_render_text ( 0, 40, buf, 1 );

    lcd_to_screen (  );

    kpd_wait_keypress (  );
    kpd_wait_release (  );

    lcd_clr (  );
    lcd_render_text ( 0, 0, "-page2-", 1 );

    //sprintf ( buf, "%d", float32_to_int32 ( testfloat ) ); //replaced temporarly for div test
    int blub = 3000;
    int blabb = 17;
    sprintf ( buf, "%d", blub / blabb );
    lcd_render_text ( 0, 8, buf, 1 );

    sprintf ( buf, "h: %04X", ( int ) testfloat );
    lcd_render_text ( 0, 16, buf, 1 );

    // PI test also
    sprintf ( buf, "sin: %d", float32_to_int32 ( float32_mul ( int32_to_float32 ( 100000 ), sine ( float32_div ( PI, int32_to_float32 ( 2 ) ) ) ) ) );
    lcd_render_text ( 0, 24, buf, 1 );  //should return sin ( 0,5pi ) * 100000 = 100000

    sprintf ( buf, "cos: %d", float32_to_int32 ( float32_mul ( int32_to_float32 ( 100000 ), cosine ( float32_mul ( PI, int32_to_float32 ( 2 ) ) ) ) ) );
    lcd_render_text ( 0, 32, buf, 1 );  //should return cos ( 2pi ) * 100000 = 100000

    lcd_to_screen (  );

    kpd_wait_keypress (  );
    kpd_wait_release (  );
*/
}

MENU_CALLBACK ( main_engine3d_cube )
{
    MENU_ONLY_SELECT;
    simple_cube_main (  );
}

MENU_CALLBACK ( main_huffman )
{
/*
//atol test
    char buf[16];
	const char *atoltest1 = "1235";
	const char *atoltest2 = "123577";
	const char *atoltest3 = "1235.12";
*/
    //unsigned char* huffman_decomp;
    MENU_ONLY_SELECT;
    /*
     * huffman_compressed h_enc_txt;
     * char* h_dec_txt;
     * 
     * h_enc_txt.uncompressed_size = 245;
     * h_enc_txt.compressed_size = sizeof ( huffman_testtext );
     * h_enc_txt.blockname = huffman_testtext;
     * 
     * //huffman_decompress ( h_enc_txt, h_dec_txt );
     * 
     * ui_draw_scrolltext ( h_dec_txt );
     * 
     * huffman_free ( h_dec_txt );
     */
    /*
     * //MADos won't startup, when compiled with #include <apps/huffman_testtext.h>
     * //in PC mode this works
     * const unsigned char huffman_testtext = { 0x01, 0x02, 0x03, 0x04, 0x00 }; //should be in huffman_testtext.h
     * 
     * huffman_decomp = (unsigned char*) malloc ( 245 );
     * 
     * Huffman_Uncompress ( (unsigned char*) huffman_testtext, huffman_decomp, sizeof ( huffman_testtext ), 245 );
     * 
     * ui_draw_scrolltext ( huffman_decomp );
     * 
     * free ( huffman_decomp );
     */

    //moved it into huffman.c :(
    kpd_wait_release (  );
/*	
//atol test
	lcd_clr ();
	
	sprintf ( buf, "atol1 %d", atol ( atoltest1 ) );
    lcd_render_text ( 0, 0, buf, 1 );
	
	sprintf ( buf, "atol2 %d", atol ( atoltest2 ) );
    lcd_render_text ( 0, 8, buf, 1 );
	
	sprintf ( buf, "atol3 %d", atol ( atoltest3 ) );
    lcd_render_text ( 0, 16, buf, 1 );
	
	lcd_to_screen (  );
	
	kpd_wait_keypress (  );
*/
    huffman_testtextdisplay (  );

}

int
main_creditz ( int cmd, int num )
{
    static int pos = 0;
    static int cnt = 0;
    const unsigned char *cred_str[] = { "       g3gg0, krisha, chief359, M457       ",
        "       wumpus, TechTron, kontact, c0sm4ky, Crux, SpaceImpact33, Yomanda, GsmCyber       ",
        "       Nok5Rev, NokDoc, digicroxx, ldril, vezz_developer, Al       "
    };
    char str[8];


    switch ( cmd )
    {
        case MENU_SELECT:
            lcd_clr (  );
            lcd_type_text_2 ( 0, 0 * 8 + 1, 5, " copyright", 1 );
            lcd_type_text_2 ( 0, 1 * 8 + 1, 5, " by g3gg0", 1 );
            lcd_type_text_2 ( 0, 2 * 8 + 1, 5, " & krisha", 1 );
            lcd_type_text_2 ( 0, 4 * 8 + 1, 5, "   thx 2", 1 );
            lcd_type_text_2 ( 0 + 4, 5 * 8 + 1, 5, "  wumpus", 1 );
            sleep ( 3 );
            break;
        case MENU_REDRAW:
            if ( pos >= strlen ( cred_str[num] ) - 6 )
                pos = 0;
            memcpy ( str, ( unsigned char * ) ( ( unsigned long ) ( cred_str[num] ) + pos++ ), 6 );
            str[6] = '\n';
            str[7] = 0x00;
            menu_disp ( str );
            break;
        case MENU_DRAW:
        case MENU_UNDRAW:
            pos = 0;
            break;
    }

}

MENU_CALLBACK ( main_cred_main )
{
    main_creditz ( cmd, 0 );
}

MENU_CALLBACK ( main_cred_help )
{
    main_creditz ( cmd, 1 );
}

MENU_CALLBACK ( main_cred_greetz )
{
    main_creditz ( cmd, 2 );
}

MENU_CALLBACK ( main_off )
{
    MENU_ONLY_SELECT;
    ccont_poweroff (  );
}

MENU_CALLBACK ( main_reboot )
{
    MENU_ONLY_SELECT;
    ccont_reboot (  );
}



MENU_CALLBACK ( main_fs_stat )
{
    int ret;
    switch ( cmd )
    {
        case MENU_REDRAW:
            ret = fs_check ( ( void * ) FS_BASE );
            if ( ret )
                menu_disp ( "Please format FS" );
            else
                menu_disp ( "File System ok" );
            break;
        case MENU_DRAW:
        case MENU_UNDRAW:
            break;
    }
}

MENU_CALLBACK ( main_format )
{
    int ret;
    char buf[32];
    //FILE *f;

    MENU_ONLY_SELECT;
#ifndef EMBED
#ifndef FULLEMBED
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "Format", 1 );
    lcd_to_screen (  );
    usleep ( 100000 );
    ret = fs_format ( ( void * ) FS_BASE );
    if ( ret )
    {
        sprintf ( buf, "%02i", ret );
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8, "Format error!", 1 );
        lcd_render_text ( 0, 1 * 8, buf, 1 );
        lcd_to_screen (  );
        ksleep ( 5 );
        return 0;
    }
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "Format Complete", 1 );
    lcd_to_screen (  );
    ksleep ( 5 );
#endif
#endif
}

MENU_CALLBACK ( main_fs )
{
    int ret;
    char buf[32];
    FILE *f;

    MENU_ONLY_SELECT;
#ifndef EMBED
#ifndef FULLEMBED
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "FS format", 1 );
    lcd_to_screen (  );
    usleep ( 100000 );
    ret = fs_format ( ( void * ) FS_BASE );
    if ( ret )
    {
        sprintf ( buf, "%02i", ret );
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8, "format err", 1 );
        lcd_render_text ( 0, 1 * 8, buf, 1 );
        lcd_to_screen (  );
        ksleep ( 5 );
        return 0;
    }

    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "FS check", 1 );
    lcd_to_screen (  );
    usleep ( 100000 );
    ret = fs_check ( ( void * ) FS_BASE );
    if ( ret )
    {
        sprintf ( buf, "%02i", ret );
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8, "check err", 1 );
        lcd_render_text ( 0, 1 * 8, buf, 1 );
        lcd_to_screen (  );
        ksleep ( 5 );
        return 0;
    }

    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "FS wopen", 1 );
    lcd_to_screen (  );
    usleep ( 100000 );
    f = fs_fopen ( "test.suxx", "w" );
    if ( !f )
    {
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8, "wopen err", 1 );
        lcd_to_screen (  );
        ksleep ( 5 );
        return 0;
    }

    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "FS write", 1 );
    lcd_to_screen (  );
    usleep ( 100000 );
    ret = fs_fwrite ( "-SUCCESS-", 1, 9, f );

    if ( !ret )
    {
        fs_fclose ( f );
        sprintf ( buf, "%02i", ret );
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8, "write err", 1 );
        lcd_render_text ( 0, 1 * 8, buf, 1 );
        lcd_to_screen (  );
        ksleep ( 5 );
        return 0;
    }

    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "FS wclose", 1 );
    lcd_to_screen (  );
    usleep ( 100000 );
    ret = fs_fclose ( f );

    if ( ret )
    {
        sprintf ( buf, "%02i", ret );
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8, "wclose err", 1 );
        lcd_render_text ( 0, 1 * 8, buf, 1 );
        lcd_to_screen (  );
        ksleep ( 5 );
        return 0;
    }

    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "FS ropen", 1 );
    lcd_to_screen (  );
    usleep ( 100000 );
    f = fs_fopen ( "test.suxx", "r" );
    if ( !f )
    {
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8, "ropen err", 1 );
        lcd_to_screen (  );
        ksleep ( 5 );
        return 0;
    }

    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "FS read", 1 );
    lcd_to_screen (  );
    usleep ( 100000 );
    ret = fs_fread ( buf, 1, 32, f );
    buf[31] = 0x00;
    if ( !ret )
    {
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8, "read err", 1 );
        lcd_to_screen (  );
        ksleep ( 5 );
        return 0;
    }

    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "FS rclose", 1 );
    lcd_to_screen (  );
    usleep ( 100000 );

    if ( fs_fclose ( f ) )
    {
//        sprintf ( buf, "%02i", ret );
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8, "rclose err", 1 );
//        lcd_render_text ( 0, 1 * 8, buf, 1 );
        lcd_to_screen (  );
        ksleep ( 5 );
        return 0;
    }

    fs_unlink ( "test.suxx" );

    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, buf, 1 );
    sprintf ( buf, "%02i bytes", ret );
    lcd_render_text ( 0, 1 * 8, buf, 1 );
    lcd_to_screen (  );
    ksleep ( 2 );

    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "f1", 1 );
    lcd_to_screen (  );
    f = fs_fopen ( "test1.suxx", "w" );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "f2", 1 );
    lcd_to_screen (  );
    ret = fs_fwrite ( "-1SUCCESS-", 1, 10, f );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "f3", 1 );
    lcd_to_screen (  );
    ret = fs_fclose ( f );

    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "f4", 1 );
    lcd_to_screen (  );
    f = fs_fopen ( "test2.suxx", "w" );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "f5", 1 );
    lcd_to_screen (  );
    ret = fs_fwrite ( "-xSUCCESS-", 1, 10, f );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "f6", 1 );
    lcd_to_screen (  );
    ret = fs_fclose ( f );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "f7", 1 );
    lcd_to_screen (  );

    f = fs_fopen ( "test1.suxx", "a" );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "f8", 1 );
    lcd_to_screen (  );
    ret = fs_fwrite ( "-2SUCCESS-", 1, 10, f );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "f9", 1 );
    lcd_to_screen (  );
    ret = fs_fclose ( f );

    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "fa", 1 );
    lcd_to_screen (  );
    f = fs_fopen ( "test2.suxx", "a" );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "fb", 1 );
    lcd_to_screen (  );
    ret = fs_fwrite ( "-xSUCCESS-", 1, 10, f );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "fc", 1 );
    lcd_to_screen (  );
    ret = fs_fclose ( f );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "fd", 1 );
    lcd_to_screen (  );

    f = fs_fopen ( "test1.suxx", "a" );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "fe", 1 );
    lcd_to_screen (  );
    ret = fs_fwrite ( "-3SUCCESS-", 1, 10, f );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "ff", 1 );
    lcd_to_screen (  );
    ret = fs_fclose ( f );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "fg", 1 );
    lcd_to_screen (  );

    f = fs_fopen ( "test1.suxx", "r" );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "fh", 1 );
    lcd_to_screen (  );
    ret = fs_fread ( buf, 1, 32, f );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "fi", 1 );
    lcd_to_screen (  );
    ret = fs_fclose ( f );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "fj", 1 );
    lcd_to_screen (  );

//    buf[31] = 0x00;

    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "FS success", 1 );
    lcd_to_screen (  );
    ksleep ( 5 );
#endif
#endif
}


MENU_CALLBACK ( main_flash )
{
    int i = 0;
    unsigned char buf[32];

    MENU_ONLY_SELECT;

#ifndef FULLEMBED
#ifndef EMBED
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "flash id:", 1 );
    lib_hexconv ( buf, ( flash_get_ident ( 0 ) & 0xFFFF ) << 16 | ( flash_get_ident ( 1 ) & 0xFFFF ) );
    lcd_render_text ( 0, 1 * 8, buf, 1 );
    lcd_to_screen (  );
    sleep ( 1 );


    lcd_clr (  );
    lcd_to_screen (  );
    lcd_type_text_2 ( 0, 1 * 8, 3, "erasing...", 1 );
    lcd_clr (  );
    i = flash_erase ( ( void * ) FLASH_TEST_BASE );
    if ( i & FLASH_STATUS_ES )
        lcd_type_text_2 ( 0, 0 * 8, 3, "erase err", 1 );
    if ( i & FLASH_STATUS_VPPS )
        lcd_type_text_2 ( 0, 1 * 8, 3, "VPP low", 1 );

    ksleep ( 1 );

    lcd_clr (  );
    lcd_to_screen (  );
    lcd_type_text_2 ( 0, 1 * 8, 3, "writing...", 1 );
    lcd_clr (  );
    i = flash_write ( ( void * ) FLASH_TEST_BASE, ( void * ) 0x00100000, 0x00010000 );
    if ( i & FLASH_STATUS_ES )
        lcd_type_text_2 ( 0, 0 * 8, 3, "erase err", 1 );
    if ( i & FLASH_STATUS_VPPS )
        lcd_type_text_2 ( 0, 1 * 8, 3, "VPP low", 1 );

    sleep ( 1 );


    lcd_type_text_2 ( 0, 1 * 8, 3, "done...", 1 );
    lcd_clr (  );
    lcd_to_screen (  );
    ksleep ( 1 );
#endif
#endif

}

MENU_CALLBACK ( main_xbus )
{
    int i = 0;
    unsigned char buf[32];

    MENU_ONLY_SELECT;

    xbus_test (  );
    return 0;

    xbus_init (  );
    xbus_set_sda ( 0 );
//      _io_set ( IO_MBUS_CTRL, 0x03 );
//      _io_set ( IO_MBUS_STATUS, 0x40 );

    while ( 1 )
    {
        lcd_clr (  );
        if ( xbus_get_scl (  ) )
            lcd_render_text ( 1, 0, "SCL High", 1 );
        else
            lcd_render_text ( 1, 0, "SCL Low", 1 );

        if ( xbus_get_sda (  ) )
            lcd_render_text ( 1, 8, "SDA High", 1 );
        else
            lcd_render_text ( 1, 8, "SDA Low", 1 );

        if ( kpd_getkey (  ) == 0xFF )
            xbus_set_sda ( 0 );
        else if ( kpd_getkey (  ) == 0x02 )
            xbus_test (  );
        else if ( kpd_getkey (  ) == 0x03 )
            xbus_read_test (  );
        else if ( kpd_getkey (  ) == 0x04 )
            _io_set ( IO_MBUS_CTRL, 0x03 );
        else if ( kpd_getkey (  ) == 0x05 )
            _io_set ( IO_MBUS_CTRL, 0x00 );
        else if ( kpd_getkey (  ) == 0x06 )
            _io_set ( IO_MBUS_STATUS, 0x40 );
        else if ( kpd_getkey (  ) == 0x07 )
            _io_set ( IO_MBUS_STATUS, 0x00 );
        else if ( kpd_getkey (  ) == 0x01 )
        {
            lcd_to_screen (  );
            if ( !ipc_add ( tid_xbus, "\xAA\xBB\xCC\xDD\x00\x10\x00\x00\x00\x00\x00\x20", 0x0C ) )
            {
                lcd_clr (  );
                lcd_render_text ( 1, 9, "IPC failed", 1 );
                lcd_to_screen (  );
            }
            usleep ( 500000 );
        }
        else
        {
            lcd_render_text ( 1, 9, "SDA High", 1 );
            xbus_set_sda ( 1 );
        }

        lcd_render_text ( 0, 2 * 8, "MBUS_STATUS:", 1 );
        lib_hexconv ( buf, _io_read ( IO_MBUS_CTRL ) );
        lcd_render_text ( 0, 3 * 8, buf, 1 );
        lib_hexconv ( buf, _io_read ( IO_MBUS_STATUS ) );
        lcd_render_text ( 0, 4 * 8, buf, 1 );
        lib_hexconv ( buf, _io_read ( IO_MBUS_BYTE ) );
        lcd_render_text ( 0, 5 * 8, buf, 1 );
        lcd_to_screen (  );
    }
}

// IO_PUP_CTRL
// IO_MBUS_CTRL
// IO_MBUS_STATUS
// IO_MBUS_BYTE
const unsigned char mbus_registers[4] = { 0, IO_PUP_CTRL, IO_MBUS_CTRL, IO_MBUS_STATUS };

MENU_CALLBACK ( main_mbus )
{
    int i = 0;
    int xfer = 0;
    int keyval;
    int status;
    int reg = 0;
    unsigned char buf[32];
    unsigned char curval;
    int mode;

    MENU_ONLY_SELECT;

    mbus_init ( MBUS_SPEED_9600 );
    mbus_mode ( MBUS_TRANSMIT );
    mode = MBUS_TRANSMIT;

    do
    {
        keyval = kpd_getkey (  );
        lcd_clr (  );
        if ( reg == 0 )
        {
            switch ( keyval )
            {
                case 0x02:
                    /*
                     * 2 -- transmit mode 
                     */
                    mode = MBUS_TRANSMIT;
                    /*
                     * mode is actually set after first byte 
                     */
                    mbus_mode ( MBUS_STOP );
                    xfer = 0;
                    break;
                case 0x03:
                    /*
                     * 3 -- receive mode 
                     */
                    mode = MBUS_RECEIVE;
                    mbus_mode ( MBUS_RECEIVE );
                    xfer = 0;
                    break;
                case 0x04:     /* PUP control */
                    reg = 1;
                    break;
                case 0x05:     /* MBUS control */
                    reg = 2;
                    break;
                case 0x06:     /* MBUS status */
                    reg = 3;
                    break;
            }

        }
        else if ( keyval >= 0 && keyval <= 7 )
        {
            /*
             * Bit toggle 
             */
            _io_set ( mbus_registers[reg], _io_read ( mbus_registers[reg] ) ^ ( 1 << keyval ) );
            reg = 0;
        }
        /*
         * render number of sent/received bytes 
         */
        lib_hexconv ( buf, xfer | ( reg << 16 ) );
        lcd_render_text ( 0, 0 * 8, buf, 1 );

        /*
         * Render current received/sent value 
         */
        lib_hexconv ( buf, curval );
        lcd_render_text ( 0, 1 * 8, buf, 1 );

        /*
         * mode 
         */
        if ( mode == MBUS_TRANSMIT )
            lcd_render_text ( 0, 2 * 8, "MBUS_TRANSMIT", 1 );
        else
            lcd_render_text ( 0, 2 * 8, "MBUS_RECEIVE", 1 );

        /*
         * send a byte 
         */
        if ( mode == MBUS_TRANSMIT )
        {
            status = _io_read ( IO_MBUS_STATUS );
            if ( status & 0x10 )
            {
                /*
                 * status byte transmit ready 
                 */
                _io_set ( IO_MBUS_BYTE, curval );
                xfer++;
            }
            curval++;
            if ( xfer == 1 )
                /*
                 * first byte sent 
                 */
                mbus_mode ( MBUS_TRANSMIT );
        }
        /*
         * receive a byte 
         */
        if ( mode == MBUS_RECEIVE )
        {
            status = _io_read ( IO_MBUS_STATUS );
            //if(_io_read(IO_MBUS_CTRL)&0x40) {
            /*
             * -- Read mode on -- always 
             */
            if ( ( status & 7 ) != 0 )
            {
                /*
                 * Error. Reset and resynchronize receiver. 
                 */
                mbus_mode ( MBUS_RECEIVE );
            }
            else if ( status & 0x20 )
            {
                /*
                 * status byte received 
                 */
                curval = _io_read ( IO_MBUS_BYTE );
                xfer++;
            }
            //}
        }
        /*
         * Render registers 
         */
        lib_hexconv ( buf, _io_read ( IO_PUP_CTRL ) );
        lcd_render_text ( 0, 3 * 8, buf, 1 );
        lib_hexconv ( buf, _io_read ( IO_MBUS_CTRL ) );
        lcd_render_text ( 0, 4 * 8, buf, 1 );
        lib_hexconv ( buf, _io_read ( IO_MBUS_STATUS ) );
        lcd_render_text ( 0, 5 * 8, buf, 1 );

        lcd_to_screen (  );
    }
    while ( keyval != KPD_CANCEL );
}

extern int mbus_ints, mbus_txdptr, mbus_rxdcount, mbus_txdsize;
MENU_CALLBACK ( main_mserial )
{
    int i = 0, x;
    int keyval;
    unsigned char buf[200];
    unsigned char line[80];
    int lineptr, n;
    char testje[] = "\r\nMADos serial prompt.\r\n" "What you say will be repeated back to you in hex codes.\r\n";
    char prompt[] = "\r\n# ";

    MENU_ONLY_SELECT;

//    mbus_start ( MBUS_SPEED_9600 );

    mbus_transmit ( testje, sizeof ( testje ) );
    mbus_transmit ( prompt, sizeof ( prompt ) );
    mbus_mode ( MBUS_RECEIVE );
    lineptr = 0;

    do
    {
        keyval = kpd_getkey (  );
        lcd_clr (  );

        lib_hexconv ( buf, lineptr );
        lcd_render_text ( 0, 0 * 8, buf, 1 );

        lib_hexconv ( buf, mbus_rxdcount );
        lcd_render_text ( 0, 1 * 8, buf, 1 );

        /*
         * Render registers 
         */
        lib_hexconv ( buf, _io_read ( IO_MBUS_CTRL ) );
        lcd_render_text ( 0, 3 * 8, buf, 1 );
        lib_hexconv ( buf, _io_read ( IO_MBUS_STATUS ) );
        lcd_render_text ( 0, 4 * 8, buf, 1 );
        lib_hexconv ( buf, mbus_ints );
        lcd_render_text ( 0, 5 * 8, buf, 1 );

        lcd_to_screen (  );

        n = mbus_receive ( &line[lineptr], sizeof ( line ) - lineptr );
        lineptr += n;
        if ( lineptr == sizeof ( line ) )
            /*
             * buffer overflow 
             */
            lineptr = 0;
        for ( i = 0; i < lineptr && line[i] != '\r'; i++ ) ;
        if ( i != lineptr )
        {
            /*
             * user entered line -- ECHO 
             */
            line[i] = 0;
            strcpy ( buf, "\r\n" );
            for ( x = 0; x < i; x++ )
            {
                sprintf ( &buf[x * 2 + 2], "%02X", line[x] );
            }
            strcpy ( &buf[i * 2 + 2], "\r\n" );
            usleep ( 100000 );  /* sleeps are ugly -- there is FIQ3 for this */
            mbus_transmit ( buf, strlen ( buf ) );
            usleep ( 100000 );
            mbus_transmit ( prompt, sizeof ( prompt ) );
            usleep ( 100000 );
            mbus_mode ( MBUS_RECEIVE );
            lineptr = 0;
        }
        usleep ( 250000 );
    }
    while ( keyval != KPD_CANCEL );
    int_fiq_disable ( FIQ_MBUSRX );
    int_fiq_disable ( FIQ_MBUSTIM );
}


MENU_CALLBACK ( main_xdebug )
{

    switch ( cmd )
    {
        case MENU_GETSTATE:
            return xbus_isenabled (  );
        case MENU_SELECT:
            if ( xbus_isenabled (  ) )
                xbus_disable (  );
            else
                xbus_enable (  );
            return 0;
        default:
            break;
    }
    return 0;

}

MENU_CALLBACK ( main_malloc )
{
    int i;
    char *string[100];

    MENU_ONLY_SELECT;

    lcd_clr (  );
    lcd_render_text ( 0, 0, "malloc test", 1 );
    for ( i = 0; i < 100; i++ )
        if ( ( string[i] = ( char * ) malloc ( ( lib_mod ( i, 10 ) + 2 ) * 8 ) ) == NULL )
            lcd_render_text ( 0, 8, "malloc failed", 1 );
    for ( i = 0; i < 100; i++ )
        free ( string[i] );
    lcd_render_text ( 0, 16, "malloc test 2", 1 );
    if ( ( string[0] = ( char * ) malloc ( 60 * 1024 ) ) == NULL )
        lcd_render_text ( 0, 24, "malloc failed", 1 );
    lcd_render_text ( 0, 32, "this must fail", 1 );
    if ( ( string[1] = ( char * ) malloc ( 10 * 1024 ) ) == NULL )
        lcd_render_text ( 0, 40, "malloc failed", 1 );
    free ( string[0] );
    free ( string[1] );
    lcd_to_screen (  );
    sleep ( 3 );
}


MENU_CALLBACK ( main_sprintf )
{
    char buf[255];
    int a = 17, b = 25;

    MENU_ONLY_SELECT;

    lcd_clr (  );
    sprintf ( buf, "79: %d, %#x\n11: %03d, %s%02x\n%d + %d = %d\n", 79, 79, 11, "0x", 11, a, b, a + b );
    lcd_render_text_ml ( 0, 0, buf, 1, 0 );
    lcd_to_screen (  );
    sleep ( 6 );
}


MENU_CALLBACK ( main_ani )
{
    char x, y;

    MENU_ONLY_SELECT;

//    xbus_enable ();

    lcd_clr (  );
    lcd_to_screen (  );
    xbus_send_packet ( "main_ani: starting ani", 0 );
    ani_play ( &ani_01, 10, 20, 200, 0, 0 );
    while ( kpd_getkey (  ) == 0xFF )
    {
        x = lib_mod ( lib_rand ( 0 ), 84 - ( int ) bitmap_get ( &ani_01, -2 ) );
        y = lib_mod ( lib_rand ( 0 ), 48 - ( int ) bitmap_get ( &ani_01, -3 ) );
        ksleep ( 1 );
        if ( !ani_play ( NULL, x, y, 200, 0, 0 ) )
            break;
    }
    ani_stop (  );

}


MENU_CALLBACK ( main_time )
{
    char buf[16];

    thread_state++;
    if ( thread_state > 10 )
    {
        buzzer_setvol ( 0x30 );
        buzzer_setfreq ( 10000 );
        sprintf ( buf, "* %d s", lib_div ( lib_get_time (  ), 1000 ) );
        ccont_reset_wdt (  );
    }
    else
    {
        sprintf ( buf, "%d s", lib_div ( lib_get_time (  ), 1000 ) );
    }
    menu_disp ( buf );
}


MENU_CALLBACK ( main_dropdown )
{
    static int j, i = 0;
    char *entries[] = { "One", "Two", "Three", "Four", "Five", NULL };

    switch ( cmd )
    {
        case MENU_SELECT:
            j = menu_dropdown ( entries, i );
            if ( j >= 0 )
                i = j;
            break;
        case MENU_REDRAW:
        case MENU_DRAW:
            menu_disp ( entries[i] );
            break;
        default:
            break;
    }

}

void
thread_ccont ( void )
{
    int i = 0;
    while ( 1 )
    {
        mbus_print ( "CCONT:   reset wdt\r\n" );
        ccont_reset_wdt (  );
        for ( i = 0; i < 10; i++ )
        {
            sleep ( 1 );
            thread_state = 0;
        }
    }
}


void
thread_lcd ( void )
{
    while ( 1 )
    {
        if ( lcd_changed )
            lcd_screen_to_io (  );
        usleep ( 40000 );
    }
}


void
thread_ipc ( void )
{
    unsigned char *ptr;

    ipc_assign_data ( 0xff, 0 );
    while ( 1 )
    {
        if ( ipc_poll (  ) )
        {
            lcd_clr (  );
            lcd_render_text ( 0, 0, "woooh!", 1 );
            lcd_to_screen (  );
            ptr = ipc_read ( ( void * ) NULL );
            lcd_render_text ( 0, 8, ptr, 1 );
            ipc_flush (  );
            lcd_to_screen (  );
            sleep ( 1 );
            lcd_clr (  );
            lcd_to_screen (  );

        }
        sleep ( 1 );
    }
}

void
thread_mbus ( void )
{
    unsigned char *ptr;
    int len = 0;

    ipc_assign_data ( 0xff, 3 );
    while ( 1 )
    {
        ptr = ipc_read ( &len );

        if ( !ptr )
            sleep ( 1000 );     // ouch....
        else
        {
            mbus_transmit ( ptr, len );
            ipc_flush (  );
        }
/*        if ( ipc_poll (  ) )
        {
            lcd_clr (  );
            lcd_render_text ( 0, 0, "woooh!", 1 );
            lcd_to_screen (  );
    	    sleep ( 1 );
        }
        sleep ( 1 );*/
    }
}

void
thread_xbus ( void )
{
    unsigned char *ptr;
    unsigned int len;

    ipc_assign_data ( 0xff, 1 );
    while ( 1 )
    {
        ptr = ipc_read ( &len );
        if ( len == 0x0C )
            xbus_dbg ( *( unsigned int * ) ( ptr + 0 ), *( unsigned int * ) ( ptr + 4 ), *( unsigned int * ) ( ptr + 8 ) );
        ipc_flush (  );
    }
}


void
thread_vibra ( void )
{
    vibra_init (  );
    while ( 1 )
    {
        sleep ( 4 );
        led_set ( 0 );
        usleep ( 100000 );
        led_set ( 1 );
    }
}


void
thread_led ( void )
{
    unsigned char state = 1;
    char buf[16];
    unsigned int last_keypress_time = kpd_getlast (  );

    while ( 1 )
    {
        if ( last_keypress_time != kpd_getlast (  ) )
        {
            last_keypress_time = kpd_getlast (  );
            if ( !state )
            {
                if ( startup == NORMAL )
                    led_fade_in ( 1 );
                mbus_print ( "LED:     on\r\n" );
            }
            state = 1;
        }

        if ( lib_get_time (  ) - last_keypress_time > 150000 )
        {
            if ( state )
            {
                led_fade_out ( 3 );
                mbus_print ( "LED:     off\r\n" );
            }
            state = 0;
        }
        usleep ( 100000 );
    }
}

void
thread_ani ( void )
{
    unsigned char *ptr;
    unsigned int len;
    short int delay = 125;
    int i, num;

    ani_t *ani;
    int temp;
    char x, y;
    short int loop;
    char buf[32];

    ipc_assign_data ( 0xff, 2 );
    while ( 1 )
    {
        usleep ( delay * 1000 );
        if ( ipc_poll (  ) )
        {
            xbus_send_packet ( "thread_ani: got data", 0 );
            ptr = ipc_read ( &len );
            if ( len >= 10 )
            {
//                xbus_send_packet ( ptr, 10 );

                memcpy ( &temp, &ptr[0], 4 );
                if ( temp )
                {
                    memcpy ( &ani, &ptr[0], 4 );
                    i = 0;
                    num = ( int ) bitmap_get ( ani, -1 );
                }
                x = ptr[4];
                y = ptr[5];

                sprintf ( buf, "thread_ani: %d %d", ptr[4], ptr[5] );   // debug
                xbus_send_packet ( buf, 0 );

                memcpy ( &delay, &ptr[6], 2 );
                memcpy ( &loop, &ptr[8], 2 );
            }
            ipc_flush (  );
        }

        if ( ani_playing )
        {
            lcd_draw_bitmap_x ( x, y, bitmap_get ( ani, i ), T_ANI_BUF );
            lcd_changed = 1;
            i++;
            if ( i == num )
            {
                i = 0;
                if ( --loop == 0 )
                    ani_playing = 0;
                else if ( loop < 0 )
                    loop = 0;
            }
        }
    }
}

void
thread_charger ( void )
{
    charger_main (  );
}

void
main2 ( void )
{
    int i = 0;
    char buf[1024];

    simple_cube_main (  );

    menupoint mymenu[] = {
////////////////////////////////////////////////    
        {MENU_T_BMAP, 5, NULL, NULL, "Menu"},
////////////////////////////////////////////////    
        {MENU_T_FIELD, 10, NULL, &bmp_Apps, "Apps"}
        ,
        {MENU_T_LIST, 8, NULL, NULL, "Unlocker"}
        ,
        {MENU_T_LIST, 3, NULL, NULL, "Nokia"}
        ,
        {MENU_T_LIST, 3, NULL, NULL, "DCT-3"}
        ,
        {0, 0, dct3_imei, NULL, "IMEI"}
        ,
        {0, 0, dct3_prov, NULL, "MCC+MNC/GID1"}
        ,
        {0, 0, dct3_calc, NULL, "Calc"}
        ,
        {MENU_T_FIELD, 5, NULL, NULL, "DCT-4"}
        ,
        {0, 0, dct4_selversion, NULL, "Calc Version"}
        ,
        {0, 0, dct4_imei, NULL, "IMEI"}
        ,
        {0, 0, dct4_prov, NULL, "MCC+MNC"}
        ,
        {0, 0, dct4_type, NULL, "Phone-Type"}
        ,
        {0, 0, dct4_calc, NULL, "Calc"}
        ,
        {MENU_T_FIELD, 3, NULL, NULL, "Network"}
        ,
        {0, 0, network_country, NULL, "Country/Area"}
        ,
        {0, 0, network_provider, NULL, "Provider"}
        ,
        {0, 0, network_mcc_mnc_gid1, NULL, "Codes"}
        ,
        {MENU_T_LIST, 1, NULL, NULL, "Panasonic"}
        ,
        {MENU_T_FIELD, 2, NULL, NULL, "GD55"}
        ,
        {0, 0, st55gd55_imei, NULL, "IMEI"}
        ,
        {0, 0, st55gd55_calc_gd55, NULL, "Calc"}
        ,
        {MENU_T_LIST, 2, NULL, NULL, "Siemens"}
        ,
        {MENU_T_FIELD, 2, NULL, NULL, "ST55"}
        ,
        {0, 0, st55gd55_imei, NULL, "IMEI"}
        ,
        {0, 0, st55gd55_calc_st55, NULL, "Calc"}
        ,
        {MENU_T_FIELD, 2, NULL, NULL, "CL50"}
        ,
        {0, 0, st55gd55_imei, NULL, "IMEI"}
        ,
        {0, 0, st55gd55_calc_cl50, NULL, "Calc"}
        ,
        {MENU_T_FIELD, 3, NULL, NULL, "LG"}
        ,
        {0, 0, lgunlock_type, NULL, "Phone-Model"}
        ,
        {0, 0, lgunlock_imei, NULL, "IMEI"}
        ,
        {0, 0, lgunlock_calc, NULL, "Calc"}
        ,
        {MENU_T_FIELD, 3, NULL, NULL, "Alcatel"}
        ,
        {0, 0, alcatel_type, NULL, "Phone-Model"}
        ,
        {0, 0, alcatel_inst, NULL, "Instructions"}
        ,
        {0, 0, alcatel_code, NULL, "Show code"}
        ,
        {MENU_T_FIELD, 2, NULL, NULL, "Samsung"}
        ,
        {0, 0, samsung_type, NULL, "Phone-Model"}
        ,
        {0, 0, samsung_code, NULL, "Show code"}
	,
	{MENU_T_FIELD, 1, NULL, NULL, "Sony"}
	,
	{MENU_T_FIELD, 2, NULL, NULL, "CMD C1"}
	,
	{0, 0, sony_imei, NULL, "IMEI"}
	,
	{0, 0, sony_calc, NULL, "Calc"}
	,
	{MENU_T_FIELD, 1, NULL, NULL, "Vitel"}
        ,
	{MENU_T_FIELD, 2, NULL, NULL, "TSM 3/4/5"}
	,
	{0, 0, vitel_imei, NULL, "IMEI"}
	,
	{0, 0, vitel_calc, NULL, "Calc"}
	,
        {0, 0, main_meas, NULL, "Scope"}
        ,
        {0, 0, main_matrix, NULL, "Matrix"}
        ,
        {MENU_T_LIST, 2, NULL, NULL, "Stars"}
        ,
        {0, 0, main_stars, NULL, "Stars"}
        ,
        {0, 0, main_starfield, NULL, "Stars 2"}
        ,
        {MENU_T_LIST, 1, NULL, NULL, "Screenshot"}
        ,
        {0, 0, screenshot_show, NULL, "Show Flash"}
        ,
        {0, 0, main_picpaint, NULL, "PicPaint"}
        ,
        {0, 0, main_fire, NULL, "Fire"}
        ,
        {MENU_T_FIELD, 3, NULL, NULL, "Gallery"}
        ,
        {0, 0, gallery_type, NULL, "Type"}
        ,
        {0, 0, gallery_imss, NULL, "Choose"}
        ,
        {0, 0, gallery_view, NULL, "View"}
        ,
        {0, 0, main_time, NULL, "Time\nsince start"}
        ,
        {0, 0, main_media, NULL, "MAD\nMEDIA"}
        ,

////////////////////////////////////////////////    
        {MENU_T_LIST, 6, NULL, &bmp_Game, "Games"},
        {0, 0, main_snake, NULL, "Snake III"},
        {0, 0, main_tetris, NULL, "Tetris"},
        {0, 0, main_hangman, NULL, "Hangman"},
        {0, 0, main_othello, NULL, "Othello"},
        {0, 0, main_arcanoid, NULL, "Arcanoid"},
        {MENU_T_LIST, 3, NULL, NULL, "Formula 1"},
        {0, 0, car_start, NULL, "Race"},
        {0, 0, car_map_chg, NULL, "Change Track"},
        {0, 0, car_info, NULL, "Instruction"},
//        {0, 0, main_ttt, NULL, "Tic Tac Toe" },
//        {0, 0, main_bman, NULL, "Bomberman"}
//        ,

////////////////////////////////////////////////    
        {MENU_T_LIST, 1, NULL, &bmp_Tests, "Tools"}
        ,
        {MENU_T_FIELD, 2, NULL, NULL, "File System"}
        ,
        {0, 0, main_format, NULL, "Format"}
        ,
        {0, 0, main_fs_stat, NULL, "Status"}
        ,

////////////////////////////////////////////////    
        {MENU_T_LIST, 26, NULL, &bmp_Tests, "Test"}
        ,
        {MENU_T_FIELD, 4, NULL, NULL, "SIM"}
        ,
        {0, 0, main_init_sim, NULL, "Init SIM"}
        ,
        {0, 0, main_init_pin, NULL, "Enter PIN"}
        ,
        {0, 0, main_read_prov, NULL, "Get Provider"}
        ,
        {0, 0, main_sim, NULL, "Read SMS"}
        ,
        {0, 0, main_charger, NULL, "Charger"}
        ,
        {0, 0, main_contrast, NULL, "Contrast"}
        ,
        {0, 0, main_vibra, NULL, "Vibra"}
        ,
        {0, 0, main_dsp, NULL, "DSP/CCONT"}
        ,
        {0, 0, main_flash, NULL, "Flash"}
        ,
        {0, 0, main_fs, NULL, "FS Test"}
        ,
        {0, 0, main_xbus, NULL, "XBus"}
        ,
        {0, 0, main_mbus, NULL, "MBus"}
        ,
        {0, 0, main_mserial, NULL, "M-Serial"}
        ,
        {0, 0, main_xdebug, NULL, "XBus Debug"}
        ,
        {0, 0, main_malloc, NULL, "malloc()"}
        ,
        {0, 0, main_sprintf, NULL, "sprintf()"}
        ,
        {0, 0, main_ani, NULL, "Animation"}
        ,
        {0, 0, main_adval, NULL, "AD-values"}
        ,
        {0, 0, main_int, NULL, "Interrupts"}
        ,
        {0, 0, main_mdi, NULL, "MDI"}
        ,
        {0, 0, main_ui, NULL, "UserInterface"}
        ,
        {0, 0, main_txtreader, NULL, "Text reader"}
        ,
        {0, 0, main_buzzer, NULL, "BuzzerTest"}
        ,
        {0, 0, main_demo_1, NULL, "Demo 1"}
        ,
        {0, 0, main_keytest, NULL, "keytest"}
        ,
        {0, 0, NULL, NULL, "This menu is a test to see if the menu text length mod works :)"}
        ,
        {0, 0, main_softfloattest, NULL, "float/sin"}
        ,
        {0, 0, main_engine3d_cube, NULL, "simple3Dcube"}
        ,
        {0, 0, main_huffman, NULL, "huffman comp."}
        ,
////////////////////////////////////////////////    
        {MENU_T_FIELD, 3, NULL, &bmp_Creditz, "Legals"},
        {0, 0, main_cred_main, NULL, "copyright"},
        {0, 0, main_cred_help, NULL, "help by"},
        {0, 0, main_cred_greetz, NULL, "greetz to"}
        ,
////////////////////////////////////////////////    

    };



//    main_keytest ( MENU_SELECT, 0 );

#ifndef PC

//    DEBUG ( "Sleep test" );
//    sleep ( 1 );
    DEBUG ( "Start Threads" );
    mbus_transmit ( "\x0C", 1 );

    sprintf ( buf, "Startup reason:        " );
    mbus_transmit ( buf, strlen ( buf ) );
    if ( _io_read ( 0x01 ) & 0x02 )
    {
        sprintf ( buf, "[Reset by Watchdog, 0x01-> %02X]\r\n", _io_read ( 0x01 ) );
        mbus_transmit ( buf, strlen ( buf ) );
    }
    else if ( _io_read ( 0x01 ) & 0x04 )
    {
        sprintf ( buf, "[Reset by Request, 0x01-> %02X]\r\n", _io_read ( 0x01 ) );
        mbus_transmit ( buf, strlen ( buf ) );
    }
    else
    {
        sprintf ( buf, "[Normal startup, 0x01-> %02X]\r\n", _io_read ( 0x01 ) );
        mbus_transmit ( buf, strlen ( buf ) );
    }

    DEBUG ( "Start LCD" );
    sprintf ( buf, "Start LCD thread:      " );
    mbus_transmit ( buf, strlen ( buf ) );
    tid_lcd = sched_add ( ( unsigned int ) thread_lcd, 1, SCHED_PARM_RUN );
    sprintf ( buf, "[done]\r\n" );
    mbus_transmit ( buf, strlen ( buf ) );

    DEBUG ( "Start LED" );
    sprintf ( buf, "Start LED thread:      " );
    mbus_transmit ( buf, strlen ( buf ) );
    i = sched_add ( ( unsigned int ) thread_led, 1, SCHED_PARM_STOP );
    sched_set_activation ( i, lib_get_time (  ) + 2000 );
    sprintf ( buf, "[done]\r\n" );
    mbus_transmit ( buf, strlen ( buf ) );

    sprintf ( buf, "Start CCONT thread:    " );
    mbus_transmit ( buf, strlen ( buf ) );
    i = sched_add ( ( unsigned int ) thread_ccont, 1, SCHED_PARM_STOP );
    sched_set_activation ( i, lib_get_time (  ) + 5000 );
    sprintf ( buf, "[done]\r\n" );
    mbus_transmit ( buf, strlen ( buf ) );

/*
    DEBUG ( "Start XBUS" );
    sprintf ( buf, "Start XBUS thread:     " );
    mbus_transmit ( buf, strlen(buf) );
    tid_xbus = sched_add ( ( unsigned int ) thread_xbus, 1, SCHED_PARM_RUN );
    sprintf ( buf, "[done]\r\n" );
    mbus_transmit ( buf, strlen(buf) );
*/

    DEBUG ( "Start ANI" );
    sprintf ( buf, "Start ANI thread:      " );
    mbus_transmit ( buf, strlen ( buf ) );
    tid_ani = sched_add ( ( unsigned int ) thread_ani, 1, SCHED_PARM_RUN );
    sprintf ( buf, "[done]\r\n" );
    mbus_transmit ( buf, strlen ( buf ) );

    DEBUG ( "Start CHRG" );
    sprintf ( buf, "Start CHRG thread:     " );
    mbus_transmit ( buf, strlen ( buf ) );
    tid_charger = sched_add ( ( unsigned int ) thread_charger, 1, SCHED_PARM_RUN );
    sprintf ( buf, "[done]\r\n" );
    mbus_transmit ( buf, strlen ( buf ) );

/*
    sprintf ( buf, "Start MBUS thread:     " );
    mbus_transmit ( buf, strlen ( buf ) );
    tid_mbus = sched_add ( ( unsigned int ) thread_mbus, 1, SCHED_PARM_RUN );
    sprintf ( buf, "[done]\r\n" );
    mbus_transmit ( buf, strlen ( buf ) );

    sprintf ( buf, "Test MBUS thread:      " );
    mbus_transmit ( buf, strlen ( buf ) );
    mbus_addbuf ( "[success]", 9 );
    usleep ( 50000 );
    sprintf ( buf, "\r\n" );
    mbus_transmit ( buf, strlen ( buf ) );
*/

#endif


//test only
//    char buf[16];
/*
    while ( kpd_getkey () != 1 && kpd_get_second_key () != 2 )
    {
        lcd_clr ( );
        lcd_render_text ( ( 84 - lcd_get_text_width ( "key test" ) ) / 2, 0, "key test", 1 );
        sprintf ( buf, "key1 0x%02X\0", kpd_getkey ( ) );
        lcd_render_text ( ( 84 - lcd_get_text_width ( buf ) ) / 2, 8, buf, 1 );
        sprintf ( buf, "key2 0x%02X\0", kpd_get_second_key ( ) );
        lcd_render_text ( ( 84 - lcd_get_text_width ( buf ) ) / 2, 16, buf, 1 );
        sprintf ( buf, "key3 0x%02X\0", kpd_get_third_key ( ) );
        lcd_render_text ( ( 84 - lcd_get_text_width ( buf ) ) / 2, 24, buf, 1 );
        lcd_render_text ( ( 84 - lcd_get_text_width ( "1+2 quits" ) ) / 2, 32, "1+2 quits", 1 );
        lcd_to_screen_hw ( );
    }

    kpd_wait_release ( );
*/

    while ( startup == CHARGE )
    {
        sleep ( 1 );
        charger_chargemode (  );
//  ani_play ( &ani_charge, 10, 5, 400, 0, 0 );
//  while ( 1 );
//        main_charger ( MENU_SELECT, 0 );
    }

    DEBUG ( "Show Logo" );
/*
    sprintf ( buf, "Show startup logo:     " );
    mbus_transmit ( buf, strlen ( buf ) );
    lcd_draw_bitmap ( 0x00, 0x00, &bmp_welcome );
    lcd_to_screen (  );
    kmsleep ( 500 );
    lcd_render_text ( 84 - lcd_get_text_width ( mados_info[mados_phone].name ), 0, mados_info[mados_phone].name, 1 );
    lcd_to_screen (  );
    kmsleep ( 500 );
    lcd_draw_bitmap ( 0x00, 0x00, &bmp_welcome );
    lcd_to_screen (  );
    kmsleep ( 500 );
    kpd_wait_release (  );
*/
    ani_play ( &ani_02, 0, 0, 100, 0, 0 );
    char intro1[] = "cdefga";
    char intro1_time[] = { 2, 2, 2, 2, 2, 2 };
    buzzer_tones_t tone_intro1;
    tone_intro1.tone_list = intro1;
    tone_intro1.duration_list = intro1_time;
    tone_intro1.octave_list = "\x00\x00";
    tone_intro1.volume = 20;    //lol
    tone_intro1.duration_fixed = 0;
    tone_intro1.octave_fixed = 1;
    tone_intro1.pause_fixed = 1;
    tone_intro1.interrupt = "\x00\x00";
    tone_intro1.break_on_keypress = 1;
    buzzer_play_tones ( &tone_intro1 );
    ani_stop (  );

    ani_play ( &ani_02_r, 0, 0, 100, 0, 0 );
    char intro[] = "bagfed";
    char intro_time[] = { 2, 2, 2, 2, 2, 2 };
    buzzer_tones_t tone_intro;
    tone_intro.tone_list = intro;
    tone_intro.duration_list = intro_time;
    tone_intro.octave_list = "\x00\x00";
    tone_intro.volume = 20;
    tone_intro.duration_fixed = 0;
    tone_intro.octave_fixed = 1;
    tone_intro.pause_fixed = 1;
    tone_intro.interrupt = "\x00\x00";
    tone_intro.break_on_keypress = 1;
    buzzer_play_tones ( &tone_intro );
    ani_stop (  );

    sprintf ( buf, "[done]\r\n" );
    mbus_transmit ( buf, strlen ( buf ) );

    while ( 1 )
        menu_show ( mymenu );

    return;
}


void
idle_thread ( void )
{
    sched_add ( ( unsigned int ) main2, 1, SCHED_PARM_RUN );

    while ( 1 ) ;
}

void
main_setphone ( int phone )
{
    mados_phone = phone;
}


int
main ( void )
{
    char buf[128];
    char key;
    int charger_try = 20;


#ifdef PHONE_3310_old
    mados_phone = NOKIA3310OLD;
#endif

#ifdef PHONE_3310_new
    mados_phone = NOKIA3310NEW;
#endif

#ifdef PHONE_3330_old
    mados_phone = NOKIA3330OLD;
#endif

#ifdef PHONE_3330_new
    mados_phone = NOKIA3330NEW;
#endif

#ifdef PHONE_8210
    mados_phone = NOKIA8210;
#endif

#ifdef PHONE_3410
    mados_phone = NOKIA3410;
#endif

#ifdef PHONE_3350
    mados_phone = NOKIA3350;
#endif

#ifdef PHONE_6210
    mados_phone = NOKIA6210;
#endif

#ifdef PHONE_2100
    mados_phone = NOKIA2100;
#endif

#ifdef PHONE_5110
    mados_phone = NOKIA5110;
#endif

#ifdef PHONE_AUTO
#ifndef TYPE_STANDALONE
#error 'invalid mode!'
#endif
    mados_phone = *( ( unsigned char * ) ( 0x00200002 ) );
#endif

/*
#ifndef PC
#ifndef EMBED
  restart:
    genio_init (  );            // before lcd
    kpd_io_init (  );
    sprintf ( buf, "Model %02X", mados_phone );

    usleep ( 100000 );
    key = kpd_readkey (  );
    sprintf ( buf, "current key %02X", key );
    if ( key != KPD_OFF && key != KPD_UPARROW )
    {
        if ( mados_phone == 1 )
        {
            mados_phone = 0;
            genio_init (  );
            goto go;
            ccont_init (  );
            ccont_poweroff (  );
            while ( 1 ) ;
        }
        else
            mados_phone++;
        goto restart;
    }
  go:
#else
*/

#ifdef PC
    printf ( "PC MODE, use key h to display short help\n" );
    sleep ( 1 );
#endif

    genio_init (  );
    kpd_io_init (  );

//#endif
//#endif
//    led_set ( 1 );
//    led_fade_in ( 9 );    // after POWER key check

    lib_init (  );

    lcd_clr (  );
    lcd_init (  );              // to see debug output
    lcd_to_screen_hw (  );
    DEBUG ( "LCD done" );
//sleep (1);
//    led_set ( 0 );
//sleep (10000);

    sched_init (  );            // first logical setup
    DEBUG ( "SCHED done" );
    int_init (  );              // 
    DEBUG ( "INT done" );
    ccont_init (  );
    DEBUG ( "CCONT done" );
#ifndef PHONE_5110
    timer_init (  );            // 
    DEBUG ( "TIMER done" );
#endif
    kpd_init (  );
    DEBUG ( "KPD done" );
#ifndef PC
#ifndef EMBED
#ifndef FULLEMBED

    if ( kpd_readkey (  ) != KPD_OFF )  // simple check, whether POWERKEY was pressed
    {
        while ( charger_try-- )
        {
            if ( charger_connected (  ) )
                startup = CHARGE;
            usleep ( 10000 );
        }
        if ( startup != CHARGE )
            ccont_poweroff (  );
    }
    else
    {
        led_set ( 1 );
//  led_fade_in ( 9 );
        led_fade_in ( 0 );
    }
    kpd_wait_release (  );
#endif
#endif
#endif
#ifndef PC
    mbus_start ( MBUS_SPEED_57600 );    // FIRST mbus, then vibra/buzzer
    DEBUG ( "MBUS done" );
#endif
    buzzer_init (  );
    DEBUG ( "BUZZER done" );
    vibra_init (  );
    DEBUG ( "VIBRA done" );

#ifndef PHONE_5110
    dsp_init (  );
    DEBUG ( "DSP done" );
#endif

    sim_init (  );

    lcd_fade_out ( 0 );
    lcd_clr (  );
    lcd_to_screen_hw (  );
    lcd_fade_in ( 0 );

    lib_init_hard (  );
    DEBUG ( "HARD done" );

#ifdef PC
    main2 (  );
#endif

    lib_init_rand ( 0x00 );
    lib_enable_sched (  );      // allow sleep to schedule
    DEBUG ( "ALL done" );

    sched_add ( ( unsigned int ) idle_thread, 1, SCHED_PARM_RUN );

    DEBUG ( "SCHED FAILED" );

#ifdef PHONE_5110
    DEBUG ( "NOT MORE YET" );
    while ( 1 )
        ccont_reset_wdt (  );
#endif
    while ( 1 ) ;

    return 0;
}
