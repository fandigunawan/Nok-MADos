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


#include <hw/io.h>
#include <hw/int.h>
#include <hw/timer.h>
#include <hw/buzzer.h>
#include <core/lib.h>

static unsigned int timer_time;
static unsigned int timer_ints;

void
timer_init ( void )
{
    timer_time = 0;
    timer_ints = 0;
//    _io_set_word ( 0x04, 0x7FFF );
    timer_set_div ( 0 );
    int_fiq_set_handler ( 0x04, timer_int_handler_prog );
    int_fiq_set_handler ( 0x05, timer_int_handler_time );
    timer_enable (  );
}

void
timer_disable ( void )
{
    _io_clr_bit ( IO_PUP_FIQ8, 0x01 );  // am i silly?!?!?! why FIQ8 ?!
    _io_set_bit ( IO_PUP_FIQ8, 0x04 );  // alzheimer?!
}

void
timer_enable ( void )
{
    _io_set_bit ( IO_PUP_FIQ8, 0x01 );
    _io_clr_bit ( IO_PUP_FIQ8, 0x04 );
}

void
timer_set_div ( unsigned char div )
{
    _io_set ( IO_CTSI_TMR0D, div );
}

void
timer_advance ( void )
{
    _io_set_word ( IO_CTSI_TMR0T, ( ( _io_read_word ( IO_CTSI_TMR0 ) + 0x200 ) % 0x10000 ) );
}

void
timer_force ( void )
{
    _io_set_word ( IO_CTSI_TMR0T, ( _io_read_word ( IO_CTSI_TMR0 ) + 1 ) % 0x10000 );
}

void
timer_int_handler_prog ( void )
{
    timer_advance (  );
//    buzzer_snd_next ( );
}

void
timer_int_handler_time ( void )
{
#if defined (EMBED) || defined (FULLEMBED)
    timer_time += 2048;
#else
    timer_time += 0x7FFF;
#endif
    timer_ints++;
}

unsigned int
timer_get_raw_time ( void )
{
    return _io_read_word ( IO_CTSI_TMR1 );
}

unsigned int
timer_get_time ( void )
{
    unsigned int time1, time2;

    do
    {
        time1 = _io_read_word ( IO_CTSI_TMR1 );
        time2 = _io_read_word ( IO_CTSI_TMR1 );
    }
    while ( time1 != time2 );

    return timer_time + time2;
}

unsigned int
timer_get_ints ( void )
{
    return timer_ints;
}
