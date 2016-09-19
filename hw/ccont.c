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


#include <hw/mbus.h>
#include <hw/io.h>
#include <hw/int.h>
#include <hw/ccont.h>
#include <core/sched.h>
#include <core/lib.h>


unsigned char values[0x10];

void
ccont_reboot ( void )
{

#ifdef ARM
    _io_set_bit ( IO_CTSI_RST, 0x04 );
#if 0
    int ( *reset ) ( void ) = ( void * ) 0x00200040;
    reset (  );
#endif

#endif
}


void ccont_int_handler ( void );

// initialize CCONT
void
ccont_init ( void )
{
    unsigned char i;

    for ( i = 0; i < 0x10; i++ )
        values[i] = 0;

    ccont_write ( 0x00, 0x00 );
    ccont_write ( 0x01, 0x00 );
    ccont_write ( 0x03, 0x0B );
    usleep ( 5000 );
    ccont_write ( 0x04, 0x20 );
    ccont_write ( 0x05, 0x20 );
    ccont_write ( 0x06, 0x54 );
    ccont_write ( 0x07, 0x00 );

    ccont_write ( 0x0F, 0xFF );
/*
    ccont_write ( 0x0F, 0x00 );
    int_irq_set_handler ( 0x03, ccont_int_handler );
    int_irq_set_handler ( 0x02, ccont_int_handler );
*/
}

int
ccont_get_bi ( void )
{
    int val = 0;

    val = ccont_read_adval ( 0x03 );

    return val;
}

int
ccont_get_ub ( void )
{
    int val = 0;

    val = ccont_read_adval ( 0x02 );

    // add offset 22
    val += 22;
    // now multiply with 0.00625V * 1000 to get mV
    val *= 25;
    val /= 4;

    return val;
}

int
ccont_get_uc ( void )
{
    int val = 0;

    val = ccont_read_adval ( 0x05 );

    // now multiply with 16.131 to get mV
    val *= 16131;
    val = lib_div ( val, 1000 );


    return val;
}

int
ccont_get_ic ( void )
{
    int val = 0;

    val = ccont_read_adval ( 0x07 );

    // now multiply with 1.893 to get mA
    val *= 1893;
    val = lib_div ( val, 1000 );


    return val;
}

// test CCONT connectivity
int
ccont_test ( void )
{
    if ( ccont_read ( 0x03 ) & 0xFC != 0xB0 )
        return 1;
    return 0;
}

// write a byte to CCONT register
void
ccont_write ( unsigned char reg, unsigned char byte )
{
    int_disable (  );
    _io_set ( GENSIO_CFG, 0x20 | 0x05 );
    _io_wait ( GENSIO_STATUS, GENSIO_RDY_WR | GENSIO_RDY_TR );
    _io_set ( GENSIO_CC_WR, reg << 3 );
    _io_set ( GENSIO_CC_WR, byte );
    if ( reg < 0x10 )
        values[reg] = byte;
    int_enable (  );
}

// read a byte from CCONT register
unsigned char
ccont_read ( unsigned char reg )
{
    unsigned char r;

    int_disable (  );
    if ( reg < 0x02 )
    {
        int_enable (  );
        return values[reg];
    }
    _io_set ( GENSIO_CFG, 0x20 | 0x05 );
    _io_wait ( GENSIO_STATUS, GENSIO_RDY_WR | GENSIO_RDY_TR );
    _io_set ( GENSIO_CC_WR, ( reg << 3 ) | 0x04 );
    _io_wait ( GENSIO_STATUS, GENSIO_RDY_RD );
    r = _io_read ( GENSIO_CC_RD );
    int_enable (  );

    return r;
}

// reset the watchdog timer (CCONT/ASIC)
void
ccont_reset_wdt ( void )
{
//    int_disable (  );
    _io_set ( IO_CTSI_WDT, 0x31 );
    ccont_write ( 0x05, 0x31 );
//    int_enable (  );
//    ccont_set_chargemode ( 0xFF );
}





// disable the watchdog timer (doesnt work for CCONT yet)
void
ccont_disable_wdt ( void )
{
    _io_set ( IO_CTSI_WDT, 0xFF );
//    ccont_set_charger ( 1 );
    ccont_write ( 0x05, 0x3F );
}

// poweroff the phone NOW
void
ccont_poweroff ( void )
{
    _io_set ( IO_CTSI_WDT, 0x00 );
    ccont_write ( 0x05, 0x00 );
#ifdef PC
    exit ( 0 );
#endif
}

// set the charger power (0x00-0xFF)
// could kill your battery
void
ccont_set_chargemode ( unsigned char speed )
{
    ccont_write ( 0x01, speed );
}

// enable or disable charger
void
ccont_set_charger ( int state )
{
    unsigned char val;

    val = ccont_read ( 0x00 ) & 0x7F;
    val |= ( state ? 0x80 : 0x00 );

    ccont_write ( 0x00, val );
}

// enable AD capturing
void
ccont_set_adcap ( int state )
{
    unsigned char val;

    if ( values[0x00] & 0x08 == state << 3 )
        return;

    val = ccont_read ( 0x00 ) & 0xF7;
    val |= ( state ? 1 << 3 : 0x00 );

    ccont_write ( 0x00, val );
}

// select the source AD converter
void
ccont_set_adsrc ( int src )
{
    unsigned char val;

    if ( values[0x00] & 0x70 == src << 4 )
        return;
    val = ccont_read ( 0x00 ) & 0x8F;
    val |= ( src & 0x07 ) << 4;

    ccont_write ( 0x00, val );
}

// read an ADval from the selected converter
unsigned int
ccont_get_adval ( void )
{
    unsigned int adval;

    adval = ccont_read ( 0x02 );
    adval |= ( ccont_read ( 0x03 ) & 0x03 ) << 8;

    return adval;
}

// read an ADval from specified converter
unsigned int
ccont_read_adval ( int src )
{
    unsigned int val = 0;

    ccont_set_adsrc ( src );
    ccont_set_adcap ( 1 );
    val = ccont_get_adval (  );

    return val;
}

// time functions
unsigned char
ccont_get_sec ( void )
{
    return ccont_read ( 0x07 ) & 0x3F;
}

void
ccont_set_sec ( unsigned char c )
{
    ccont_write ( 0x07, c & 0x3F );
}

unsigned char
ccont_get_min ( void )
{
    return ccont_read ( 0x08 ) & 0x3F;
}

void
ccont_set_min ( unsigned char c )
{
    ccont_write ( 0x08, c & 0x3F );
}

unsigned char
ccont_get_hr ( void )
{
    return ccont_read ( 0x09 ) & 0x1F;
}

void
ccont_set_hr ( unsigned char c )
{
    ccont_write ( 0x09, c & 0x1F );
}

unsigned char
ccont_get_day ( void )
{
    return ccont_read ( 0x0A ) & 0x3F;
}

void
ccont_set_day ( unsigned char c )
{
    ccont_write ( 0x0A, c & 0x3F );
}

// access the wakeup registers
unsigned char
ccont_get_wkupmin ( void )
{
    return ccont_read ( 0x0B ) & 0x3F;
}

void
ccont_set_wkupmin ( unsigned char c )
{
    ccont_write ( 0x0B, c & 0x3F );
}

unsigned char
ccont_get_wkuphr ( void )
{
    return ccont_read ( 0x0C ) & 0x1F;
}

void
ccont_set_wkuphr ( unsigned char c )
{
    ccont_write ( 0x0C, c & 0x1F );
}

// sets the SIM voltage
void
ccont_set_simvsel ( int state )
{
    if ( state == CCONT_VSEL_5V )
        ccont_write ( 0x00, ( ccont_read ( 0x00 ) & 0xFB ) | 0x04 );
    else
        ccont_write ( 0x00, ccont_read ( 0x00 ) & 0xFB );

    return;
}

void
ccont_enable_int ( void )
{
    ccont_write ( 0x0F, 0x00 );
}

unsigned char
ccont_get_int ( void )
{
    unsigned char ret;

    ret = ccont_read ( 0x0E );
    ccont_write ( 0x0E, ret & 0xF8 );

    return ret;
}

void
ccont_int_handler ( void )
{
    char buf[64];

/*    
    lcd_clr ();
    lcd_screen_to_io ();
    usleep ( 500000 );
    lcd_clr ();
    lcd_render_text ( 0, 0*8, "got  an", 1 );
    lcd_render_text ( 0, 1*8, "  int", 1 );
    sprintf ( buf, "%i", ccont_get_int() );
    lcd_render_text ( 0, 3*8, buf, 1 );
    lcd_screen_to_io ();
    usleep ( 500000 );
*/
//    sprintf ( buf, "CCONT:   Got INT %i", ccont_get_int() );
//    mbus_print ( buf );
}
