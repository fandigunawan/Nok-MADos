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

#define _SCHED_

#include <core/lib.h>
#include <core/sched.h>
#include <hw/lcd.h>


sched_t sched;


unsigned int
sched_now ( void )
{
    if ( !sched.num_threads )
        return 1;

    // dont schedule when ints are disabled
    // normally not needed, but who knows ;)
//    if ( !int_state () )
//  return 1;

    if ( sched.next_act != 0xFFFFFFFF && lib_get_time (  ) >= sched.next_act )
        sched_activation (  );

    return 0;
}


void
sched_yield ( void )
{
    timer_force (  );
}


void
sched_init ( void )
{
    int i = 0;
    int j = 0;

    sched.cur_thread = 0;
    sched.force_thread = 0xFF;
    sched.num_threads = 0;
    sched.next_act = 0xFFFFFFFF;
    sched.time = 0;

    for ( i = 0; i < SCHED_THREADS; i++ )
    {
        sched.threads[i].remove = 0;
        sched.threads[i].id = i;
        sched.threads[i].used = 0;
        sched.threads[i].parms = 0;
        sched.threads[i].started = 0;
        for ( j = 0; j < SCHED_NUM_DATA; j++ )
            sched.threads[i].data[j] = NULL;
        for ( j = 0; j < 17; j++ )
            sched.threads[i].regs[j] = 0x00000000;
    }
}


void
sched_save ( unsigned char reg, unsigned int val )
{
    unsigned char buf[32];

    if ( sched.num_threads && sched.threads[sched.cur_thread].started )
        sched.threads[sched.cur_thread].regs[reg] = val;
    else
        sched.regs[reg] = val;

    if ( 0 && reg == 0x0F && sched.num_threads )
    {
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8, "save", 1 );
        lib_hexconv ( buf, sched.threads[sched.cur_thread].regs[15] );
        lcd_render_text ( 0, 1 * 8, buf, 1 );
        lcd_to_screen (  );
//  sleep ( 1 );
    }

}

unsigned int
sched_get ( unsigned char reg )
{
    unsigned int ret = 0;
    unsigned char buf[32];

    if ( sched.num_threads && sched.threads[sched.cur_thread].started )
        ret = sched.threads[sched.cur_thread].regs[reg];
    else
        ret = sched.regs[reg];

    if ( 0 && sched.cur_thread == 1 && reg == 0x0F && sched.num_threads )
    {
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8, "get PC", 1 );
        lib_hexconv ( buf, sched.threads[sched.cur_thread].regs[15] );
        lcd_render_text ( 0, 1 * 8, buf, 1 );
        lcd_to_screen (  );
        sleep ( 1 );
    }

    return ret;
}

void
sched_critical ( void )
{
    int_disable (  );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "CRITICAL", 1 );
    lcd_render_text ( 0, 1 * 8, "ERROR", 1 );
    lcd_to_screen_hw (  );
    while ( 1 )
        ccont_reset_wdt (  );
}

void
sched_next ( void )
{
    unsigned char buf[32];
    unsigned char steps = 0;

//    xbus_send_packet ( "sched_next: ENTER", 0 );

    if ( !sched.num_threads )
        return;

//    xbus_send_packet ( "sched_next: OKAY", 0 );
/*    lcd_clr ();
    lib_hexconv ( buf, sched.regs[12] );
    lcd_render_text ( 0, 1*8, buf, 1 );
    lib_hexconv ( buf, sched.regs[13] );
    lcd_render_text ( 0, 2*8, buf, 1 );
    lib_hexconv ( buf, sched.regs[14] );
    lcd_render_text ( 0, 3*8, buf, 1 );
    lib_hexconv ( buf, sched.regs[15] );
    lcd_render_text ( 0, 4*8, buf, 1 );
    lcd_to_screen ();
    sleep ( 2 );
    
*/


    if ( ( sched.threads[sched.cur_thread].parms & SCHED_PARM_MASTER ) == SCHED_PARM_MASTER )
        return;


    if ( sched.force_thread != 0xFF )
    {
//  xbus_send_packet ( "sched_next: FORCE", 0 );
        sched.cur_thread = sched.force_thread;
        sched.force_thread = 0xFF;
        sched.threads[sched.cur_thread].parms = SCHED_PARM_RUN;
        sched.threads[sched.cur_thread].act_time = 0xFFFFFFFF;
        sched_update_activation (  );
/*      lcd_clr ();
	lib_hexconv ( buf, sched.cur_thread );
        lcd_render_text ( 0, 0*8, "FORCE", 1 );
	lcd_render_text ( 0, 1*8, buf, 1 );
        lcd_to_screen ();
	sleep ( 1 );
        lcd_clr ();
        lcd_to_screen ();*/
    }
    else
    {
        do
        {
            if ( sched.threads[sched.cur_thread].remove )
                sched_delete ( sched.cur_thread );
            sched.cur_thread++;
            if ( steps++ > SCHED_THREADS )
            {
                //
                // all threads stopped??
                // call our 'idle' thread #0
                //
                sched.cur_thread = 0;
                if ( !sched.threads[sched.cur_thread].used )
                {
                    lcd_clr (  );
                    lcd_set_font ( 0 );
                    lcd_render_text ( 0, 0 * 8, "Idle thread", 1 );
                    lcd_render_text ( 1, 0 * 8, "Dead :(", 1 );
                    lcd_render_text ( 3, 0 * 8, "who was it?!", 1 );
                    lcd_to_screen_hw (  );
                    while ( 1 )
                        ccont_reset_wdt (  );
                }
                break;
            }

            sched.cur_thread %= SCHED_THREADS;
            // dont call the idle thread
            if ( sched.cur_thread == 0 )
                sched.cur_thread++;
        }
        while ( !sched.threads[sched.cur_thread].used || ( sched.threads[sched.cur_thread].parms & SCHED_PARM_RUN == SCHED_PARM_RUN ) );
    }

    // if not already done...    
    sched.threads[sched.cur_thread].started = 1;

}

void
sched_delete ( unsigned char num )
{
    int i = 0;

    sched.threads[num].remove = 0;
    sched.threads[num].used = 0;
    sched.threads[num].parms = SCHED_PARM_STOP;
    if ( sched.threads[num].data[SCHED_DATA_IPC] )
        ipc_release_data ( num );
    for ( i = 0; i < 16; i++ )
        sched.threads[num].regs[i] = 0x000000;
    for ( i = 0; i < SCHED_NUM_DATA; i++ )
        sched.threads[num].data[i] = NULL;
    sched.num_threads--;

    return;
}

void
sched_remove ( unsigned char num )
{
    if ( !sched.num_threads )
        return;

    if ( num == 0xFF )
        num = sched.cur_thread;

    if ( num == sched.cur_thread )
        sched.threads[num].remove = 1;
    else
    {
        int_disable (  );
        sched_delete ( num );
        int_enable (  );
    }
}


void
sched_threadend ( void )
{
    sched_remove ( 0xFF );

    // scheduled for removal... now waiting for die'ing
    // *snief* a very bad thing... dont wanna die!!
    while ( 1 ) ;
}

void
sched_update_activation ( void )
{
    int i;
    unsigned int time = 0xFFFFFFFF;

    for ( i = 0; i < SCHED_THREADS; i++ )
        if ( sched.threads[i].used )
            if ( sched.threads[i].act_time )
                time = MIN ( time, sched.threads[i].act_time );

    sched.next_act = time;
}

void
sched_activation ( void )
{
    int i;

    for ( i = 0; i < SCHED_THREADS; i++ )
        if ( sched.threads[i].used )
            if ( sched.threads[i].act_time == sched.next_act )
                sched.force_thread = i;

    sched_update_activation (  );
}

void
sched_set_activation ( unsigned char thread, unsigned int time )
{
    if ( thread == 0xFF )
        thread = sched.cur_thread;

    if ( sched.threads[thread].used )
        sched.threads[thread].act_time = time;

    sched_update_activation (  );

}

void
sched_wakeup ( unsigned char thread )
{
    sched_set_activation ( thread, lib_get_time (  ) );
    timer_force (  );
}

void
sched_set_parm ( unsigned char thread, unsigned char parm )
{
    if ( thread == 0xFF )
        thread = sched.cur_thread;

    if ( sched.threads[thread].used )
        sched.threads[thread].parms = parm;
/*        lcd_clr ();
	lcd_render_text ( 0, 0*8, "PARMSET", 1 );
	lcd_to_screen ();
	sleep ( 1 );*/

}

unsigned char
sched_get_parm ( unsigned char thread )
{
    if ( thread == 0xFF )
        thread = sched.cur_thread;

    if ( sched.threads[thread].used )
        return sched.threads[thread].parms;

}

void
sched_enter_sleep ( unsigned char thread, unsigned int time /* until */  )
{
    if ( thread == 0xFF )
        thread = sched.cur_thread;

    if ( sched.threads[thread].used )
    {
        int_disable (  );
        sched.threads[thread].act_time = time;
        sched.threads[thread].parms = SCHED_PARM_STOP;
        sched_update_activation (  );
        timer_advance (  );
        int_enable (  );
    }

}


unsigned char
sched_add ( unsigned int addr, unsigned int thumb, unsigned char parm )
{
    int i = 0;
    int j = 0;
    unsigned char buf[32];

#ifdef ARM
    if ( addr < 0x00100000 || addr >= 0x00400000 )
    {
        lcd_clr (  );
        lcd_render_text ( 0, 3 * 8, "INVALID", 1 );
        lcd_render_text ( 0, 4 * 8, "THREAD!", 1 );
        lcd_to_screen_hw (  );
        sleep ( 2 );
        return 0xFF;
    }
#endif

//    mbus_transmit ( "ADD: disable\r\n", 13 );
    int_disable (  );
    if ( sched.num_threads < SCHED_THREADS )
        for ( i = 0; i < SCHED_THREADS; i++ )
            if ( !sched.threads[i].used )
            {
                sched.threads[i].regs[13] = sched_stacks[i];
                sched.threads[i].regs[14] = ( unsigned int ) sched_threadend | 1;
                sched.threads[i].regs[15] = ( addr | ( thumb ? 1 : 0 ) ) + 4;
                sched.threads[i].regs[16] = 0x10 | ( thumb ? 0x20 : 0 );;
                for ( j = 0; j < SCHED_NUM_DATA; j++ )
                    sched.threads[i].data[j] = NULL;
                sched.threads[i].remove = 0;
                sched.threads[i].remove = 0;
                sched.threads[i].started = 0;
                sched.threads[i].act_time = 0;
                sched.threads[i].parms = parm;
                sched.threads[i].used = 1;
                sched.num_threads++;
/*
    lcd_clr ();
    lib_hexconv ( buf, sched.threads[i].regs[12] );
    lcd_render_text ( 0, 1*8, buf, 1 );
    lib_hexconv ( buf, sched.threads[i].regs[13] );
    lcd_render_text ( 0, 2*8, buf, 1 );
    lib_hexconv ( buf, sched.threads[i].regs[14] );
    lcd_render_text ( 0, 3*8, buf, 1 );
    lib_hexconv ( buf, sched.threads[i].regs[15] );
    lcd_render_text ( 0, 4*8, buf, 1 );
    lcd_to_screen ();
    sleep ( 2 );
*/
                int_enable (  );
//      mbus_transmit ( "ADD: enable1\r\n", 13 );
                return i;
            }

    // could not add a new thread ?!
    int_enable (  );
//    mbus_transmit ( "ADD: enable2\r\n", 13 );
    return 0xFF;
}

unsigned char *
sched_get_data ( unsigned char num, unsigned char val )
{
    if ( num == 0xFF )
        num = sched.cur_thread;

    return sched.threads[num].data[val % SCHED_NUM_DATA];
}

void
sched_set_data ( unsigned char num, unsigned char val, unsigned char *data )
{
    if ( num == 0xFF )
        num = sched.cur_thread;

    sched.threads[num].data[val % SCHED_NUM_DATA] = data;

    return;
}

unsigned char
sched_get_current ( void )
{
    return sched.cur_thread;
}
