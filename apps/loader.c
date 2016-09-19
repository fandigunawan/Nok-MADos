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
#include <hw/led.h>
#include <hw/lcd.h>
#include <hw/kpd.h>
#include <core/sched.h>
#include <hw/ccont.h>
#include <core/menu.h>
#include <hw/vibra.h>
#include <apps/fire.h>
#include <hw/flash.h>


int mados_phone = 0;
int tid_ani = 0;


void
main2 ( void )
{
    int i = 0;
    int j = 1;
    int x = 0;
    int y = 0;
    int fail = 0;

    unsigned char key = 0;
    unsigned char k = 0;
    unsigned char vibra = 0;

    char buf[16];
    char *menu[] = { "1- tracks", "2- vibra", "3- creditz", "4- eXtra", "5- off", NULL };
    char *menu2[] = { "1- snake", "2- fire", "3- ADval", "4- Test", "5- *back*", NULL };
    char *trackmenu[] = { "1- track 1", "2- track 2", "3- track 3", "4- *back*", NULL };

//    usleep ( 100000 );
//    sched_add ( toggle, 1 );    

    while ( 1 )
    {
        lcd_fade_in ( 0 );
        lcd_clr (  );

//#define TEST
#ifdef TEST

        while ( 1 )
        {
            lcd_clr (  );
            lib_hexconv ( buf, io_read_word ( 0x00020004 ) );
            lcd_render_text ( 0, 1 * 8, buf, 1 );
            lib_hexconv ( buf, io_read_word ( 0x00020010 ) );
            lcd_render_text ( 0, 2 * 8, buf, 1 );
            lib_hexconv ( buf, io_read_word ( 0x00020012 ) );
            lcd_render_text ( 0, 3 * 8, buf, 1 );
            lcd_to_screen (  );
/*   if ( xbus_rxd () );
	    {
		lib_hexconv ( buf, xbus_read ( ) );
		lcd_render_text ( 0, 4*8, buf, 1 );
		lcd_to_screen ();
		sleep ( 1 );
		lcd_clr ();
		lcd_to_screen ();
	    }	*/
/*	    lcd_clr ();
	    lcd_render_bitmap ( x++, y++, 11, 7, testimg );
	    lcd_to_screen ();
	    usleep ( 100000 );
	    if ( x > 84 )
		x = 0;
	    if ( y > 48 )
		y = 0;*/
            ccont_reset_wdt (  );
        }
#endif
//#define TEST2
#ifdef TEST2

        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8, "flash id:", 1 );
        lib_hexconv ( buf, ( flash_get_ident ( 0 ) & 0xFFFF ) << 16 | ( flash_get_ident ( 1 ) & 0xFFFF ) );
        lcd_render_text ( 0, 1 * 8, buf, 1 );
        lcd_to_screen (  );
        sleep ( 1 );

        flash_vpp ( 1 );

        lcd_clr (  );
        lcd_to_screen (  );
        lcd_type_text_2 ( 0, 1 * 8, 3, "erasing...", 1 );
        lcd_clr (  );
        i = flash_erase ( 0x00200000 );
        if ( i & FLASH_STATUS_ES )
            lcd_type_text_2 ( 0, 0 * 8, 3, "erase err", 1 );
        if ( i & FLASH_STATUS_VPPS )
            lcd_type_text_2 ( 0, 1 * 8, 3, "VPP low", 1 );

        sleep ( 1 );

        lcd_clr (  );
        lcd_to_screen (  );
        lcd_type_text_2 ( 0, 1 * 8, 3, "writing...", 1 );
        lcd_clr (  );
        i = flash_write ( 0x00210000, 0x00100000, 0x10000 );
        if ( i & FLASH_STATUS_ES )
            lcd_type_text_2 ( 0, 0 * 8, 3, "erase err", 1 );
        if ( i & FLASH_STATUS_VPPS )
            lcd_type_text_2 ( 0, 1 * 8, 3, "VPP low", 1 );

        sleep ( 1 );


        lcd_type_text_2 ( 0, 1 * 8, 3, "done...", 1 );
        lcd_clr (  );
        lcd_to_screen (  );
        sleep ( 1 );


        i = dsp_test (  );
        if ( i )
        {
            lcd_type_text_2 ( 0, 1 * 8, 3, "DSP fail", 1 );
            lib_hexconv ( buf, i );
            lcd_render_text ( 0, 2 * 8, buf, 1 );
            lib_hexconv ( buf, io_read_word ( 0x00010000 ) );
            lcd_render_text ( 0, 3 * 8, buf, 1 );
            lib_hexconv ( buf, io_read_word ( 0x00010002 ) );
            lcd_render_text ( 0, 4 * 8, buf, 1 );
            lcd_to_screen (  );
            sleep ( 10 );
            lcd_clr (  );
            lcd_to_screen (  );
        }

        i = ccont_test (  );
        if ( i )
        {
            lcd_type_text_2 ( 0, 1 * 8, 3, "CCONT fail", 1 );
            sleep ( 10 );
            lcd_clr (  );
            lcd_to_screen (  );
        }
#endif

        lcd_clr (  );
        lcd_to_screen (  );
        lcd_render_text ( 0, 1 * 8, "DEMO", 1 );
        lcd_render_text ( 0, 2 * 8, "LOADER", 1 );
        lcd_to_screen (  );

        sleep ( 20 );

        while ( 1 )
        {
            ccont_reset_wdt (  );
        }
    }

    return;
}






int
main ( void )
{
    genio_init (  );
    kpd_io_init (  );
    led_fade_in ( 0 );
    lib_init (  );
    lcd_clr (  );
    lcd_init (  );
    lcd_to_screen (  );
    ccont_init (  );
    buzzer_init (  );
    //clock_speed ( 1 );
//    xbus_init ();
    kpd_init (  );
    vibra_init (  );
//    dsp_init ();
//    sched_init ();

    ccont_disable_wdt (  );

    lib_init_rand ( 0x00 );

    //sf_test_main ();

    buzzer_setvol ( 0x40 );
    buzzer_setfreq ( 1000 );


//    if ( kpd_getkey () == 0xff ) 
//  ccont_poweroff ();


//    lcd_fade_out ( 0 );    
//    lcd_clr ( );
    lcd_to_screen (  );
    led_fade_in ( 0 );
    lcd_fade_in ( 0 );


/*
  lcd_clr ( );
  lcd_type_text_2 ( 0, 0*8, 3, "Read DSP", 1 );
  lcd_type_text_2 ( 0, 0*8, 3, "done", 1 );    
  lcd_to_screen ();
*/

//  sleep ( 10 );

    main2 (  );

    while ( 1 )
    {
    }
    return 0;
}
