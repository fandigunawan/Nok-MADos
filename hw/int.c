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
#include <hw/io.h>
#include <hw/int.h>
#include <hw/buzzer.h>

unsigned long int_fiq_routines[0x09];
unsigned long int_irq_routines[0x09];
unsigned char int_critical;
unsigned int int_fiq_count[0x09];
unsigned int int_irq_count[0x09];
int int_active = 1;
int int_enabled = 1;
int int_blocked = 0;
int int_disables = 0;

// enables interrupts... and setup everything related
void
int_init ( void )
{
    int i = 0;

    int_critical = 1;
    int_blocked = 0;
    int_disables = 0;
    int_disable (  );

    for ( i = 0; i < 0x0A; i++ )
    {
        int_fiq_routines[i] = 0x00000000;
        int_irq_routines[i] = 0x00000000;
        int_fiq_count[i] = 0;
        int_irq_count[i] = 0;
    }
    _io_set ( IO_CTSI_FIQL, 0xFF ); // reset pending FIQs
    _io_set ( IO_CTSI_IRQL, 0xFF ); // and IRQs
    _io_set ( IO_CTSI_FIQM, 0x08 ); // pass all FIQs except FIQ3
    _io_set ( IO_CTSI_IRQM, 0x00 ); // and IRQs

    ccont_enable_int (  );

    int_enable (  );
    int_critical = 0;
    int_active = 0;
}

int
int_get_fiq_count ( int num )
{
    return int_fiq_count[num];
}

int
int_get_irq_count ( int num )
{
    return int_irq_count[num];
}

int
int_isblocked ( void )
{
    return int_blocked;
}

int
int_isenabled ( void )
{
    return int_enabled;
}

int
int_isactive ( void )
{
    return int_active;
}

int
int_block ( void )
{
    int_blocked++;
    return 0;
}

int
int_unblock ( void )
{
    if ( int_blocked )
        int_blocked--;
    return 0;
}

int
int_state ( void )
{
    return int_critical ? 0 : 1;
}

void
int_disable ( void )
{
    int_disables++;

    int_enabled = 0;
    int_critical = 1;
    _io_set ( IO_CTSI_ICR, CTSI_ICR_IRQD | CTSI_ICR_FIQD );
}

void
int_enable ( void )
{
    if ( int_disables > 1 )
    {
        int_disables--;
//  return;
    }
    int_disables = 0;
    _io_set ( IO_CTSI_ICR, CTSI_ICR_IRQE | CTSI_ICR_FIQE );

    int_enabled = 1;
    timer_advance (  );
    int_critical = 0;

}

void
int_fiq_enable ( unsigned int num )
{
    if ( num < 8 )
        _io_clr_bit ( IO_CTSI_FIQM, 1 << num );
    else
        _io_clr_bit ( IO_PUP_FIQ8, PUP_FIQ8_MSK );
}

void
int_fiq_disable ( unsigned int num )
{
    if ( num < 8 )
        _io_set_bit ( IO_CTSI_FIQM, 1 << num );
    else
        _io_set_bit ( IO_PUP_FIQ8, PUP_FIQ8_MSK );
}

void
int_fiq_reset ( unsigned int num )
{
    if ( num < 8 )
        _io_set_bit ( IO_CTSI_FIQL, 1 << num );
    else
        _io_set_bit ( IO_PUP_FIQ8, PUP_FIQ8_ACT );
}

void
int_irq_enable ( unsigned int num )
{
    if ( num < 8 )
        _io_clr_bit ( IO_CTSI_IRQM, 1 << num );
    else
        _io_clr_bit ( IO_CTSI_ICR, CTSI_ICR_IRQ8M );
}

void
int_irq_disable ( unsigned int num )
{
    if ( num < 8 )
        _io_set_bit ( IO_CTSI_IRQM, 1 << num );
    else
        _io_set_bit ( IO_CTSI_ICR, CTSI_ICR_IRQ8M );
}

void
int_irq_reset ( unsigned int num )
{
    if ( num < 8 )
        _io_set_bit ( IO_CTSI_IRQL, 1 << num );
}

void
int_fiq_set_handler ( unsigned int num, unsigned int handler )
{
    int_fiq_routines[num] = handler;
    int_fiq_enable ( num );
}

void
int_irq_set_handler ( unsigned int num, unsigned int handler )
{
    int_irq_routines[num] = handler;
    int_irq_enable ( num );
}

unsigned int
int_fiq_get_handler ( unsigned int num )
{
    return int_fiq_routines[num];
}
unsigned int
int_irq_get_handler ( unsigned int num )
{
    return int_irq_routines[num];
}


// this handler is called when a int happens
int
int_handler ( int addr )
{
    int i = 0;
    unsigned int fiq;
    unsigned int irq;
    /**********************************************
    WARNING WARNING WARNING WARNING WARNING WARNING
    ***********************************************
    HARDCODED EVIL HACK (FIQ2)  :
    */
    unsigned int fiq_no_clear = ( 1 << 2 ); /* Don't clear FIQ2 */
    unsigned int irq_no_clear = 0;

    unsigned char buf[32];

//
// for testing. ... .. . .. . .  ..
//

//    if ( int_critical )
//  return;

//
//
//

    int_critical = 1;
    int_active = 1;

    fiq = _io_read ( IO_CTSI_FIQL );
    irq = _io_read ( IO_CTSI_IRQL );

    if ( _io_read ( IO_PUP_FIQ8 ) & PUP_FIQ8_ACT )
        fiq |= 0x0100;
/*
    lcd_clr ();
    lcd_to_screen ();
//    usleep ( 500000 );
    lcd_clr ();
    lcd_render_text ( 0, 0*8, "got  an", 1 );
    lcd_render_text ( 0, 1*8, "  int", 1 );
    lcd_render_text ( 0, 2*8, "F:", 1 );
    lcd_render_text ( 0, 3*8, "I:", 1 );
    lcd_render_text ( 0, 4*8, "C:", 1 );
    lib_hexconv ( buf, fiq );
    lcd_render_text ( 3*7, 2*8, buf, 1 );
    lib_hexconv ( buf, irq );
    lcd_render_text ( 3*7, 3*8, buf, 1 );
    lib_hexconv ( buf, ccont_get_int() );
    lcd_render_text ( 3*7, 4*8, buf, 1 );
    lcd_to_screen ();
//    usleep ( 500000 );

*/
    for ( i = 0; i < 0x0A; i++ )
    {
        if ( fiq & ( 1 << i ) && int_fiq_routines[i] )
        {
            int_fiq_count[i]++;
            lib_call_func ( int_fiq_routines[i] | 1 );
        }
        if ( irq & ( 1 << i ) && int_irq_routines[i] )
        {
            int_irq_count[i]++;
            lib_call_func ( int_irq_routines[i] | 1 );
        }
    }
/*    
    if ( fiq & 0x10 )
    {
	// have to split up this code in evaltimer and setnewtimer
	// now the tasks are switched on every int... not just timer
	//
//	i = io_read_word ( 0x00020010 );
//	io_set_word ( 0x00020012, (i + (buzzer_snd_active()?0x02:0x100)) % 0x10000 );
	buzzer_snd_next ( );
    }
*/
    /*
     * Those lines must not be cleared, as they are cleared in the handler 
     * (HACK -- should be return value of handler?) 
     */
    fiq &= ~fiq_no_clear;
    irq &= ~irq_no_clear;

    if ( fiq & 0x0100 )
        _io_set_bit ( IO_PUP_FIQ8, PUP_FIQ8_ACT );

    _io_set ( IO_CTSI_FIQL, fiq );
    _io_set ( IO_CTSI_IRQL, irq );

    int_critical = 0;
    int_active = 0;


    return 0;
}
