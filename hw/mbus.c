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

/**
* MADos MBUS serial functions
* :Wumpus: 2003
*/
#include <hw/io.h>
#include <hw/mbus.h>
#include <hw/int.h>
// MADos:
// IO_PUP_CTRL
// IO_MBUS_CTRL
// IO_MBUS_STATUS
// IO_MBUS_BYTE
//  _io_read (addr)
//  _io_set (addr, value)
// _io_set_bit ( IO_MBUS_STATUS, 0x80 );
// _io_clr_bit ( ... )

// int_fiq_set_handler(unsigned int num, unsigned int handler )

volatile int mbus_curmode;
volatile unsigned char *mbus_txdbuffer;
volatile int mbus_txdptr, mbus_txdsize;
volatile int mbus_rxdhead, mbus_rxdtail, mbus_rxdcount; /* receive buffer */
volatile unsigned char mbus_rxdbuffer[MBUS_QUEUESIZE];

volatile int mbus_ints;
unsigned int mbus_wakeup = 0xFF;

extern unsigned char tid_mbus;

/** 
 * Initialize MBUS hardware
 * Speed is one of MBUS_SPEED_xxx
 * Starts in MBUS_RECEIVE state.
 */
void
mbus_init ( int speed )
{
    int rval;
#ifdef PC
    return;
#endif
    /*
     * Set initial values 
     */
    _io_set ( IO_PUP_CTRL, 0x08 );  /* note: stops vibra and buzzer */
    _io_set ( IO_MBUS_CTRL, 0x00 );
    _io_set ( IO_MBUS_STATUS, 0xD0 );

    /*
     * Clear bit 6(0x40) of PUPControl 
     */
    _io_clr_bit ( IO_PUP_CTRL, 0x40 );

    /*
     * MBUSControl1 := 0x80 
     */
    _io_set ( IO_MBUS_CTRL, 0x80 );

    /*
     * Wait until MBUSControl1 bit 7 is clear. 
     */
    while ( ( _io_read ( IO_MBUS_CTRL ) & 0x80 ) ) ;

    /*
     * Clear bit 3 of PUPControl 
     */
    _io_clr_bit ( IO_PUP_CTRL, 0x08 );

    /*
     * Set bit 0-2 of PUPControl to desired baudrate 
     */
    _io_set ( IO_PUP_CTRL, ( _io_read ( IO_PUP_CTRL ) & 0xF8 ) | ( speed & 0x07 ) );

    /*
     * Set bit 3 of PUPControl 
     */
    _io_set_bit ( IO_PUP_CTRL, 0x08 );

    /*
     * Enable FIQ 2 and disable FIQ 3 
     */
    //int_fiq_set_handler(FIQ_MBUSRX, &mbus_int_handler);
    /*
     * Set bit 2 and 3 of MBUSControl1 
     */
    _io_set_bit ( IO_MBUS_CTRL, 0x0C );
    /*
     * Read MBUSData (clear read state) 
     */
    rval = _io_read ( IO_MBUS_BYTE );
    /*
     * Set bit 0-2 of MBUSControl2 
     */
    _io_set_bit ( IO_MBUS_STATUS, 0x07 );
    /*
     * Set bit 6 of MBUSControl1 
     */
    _io_set_bit ( IO_MBUS_CTRL, 0x40 );
}

/** Set MBus mode to transmit or receive or stop (resync)
    Make sure there is a byte in the transmit buffer before starting transmit 
    Lame ASCII art state diagram:
       /---------------
      \/      |        \
    |----|  |----|  |----|	STOP = MBUS_STOP
    |STOP|  |TXD |  |RXD |	TXD  = MBUS_TRANSMIT
    |----|  |----|  |----|	RXD  = MBUS_RECEIVE
      \       /\ \     /\
       \------/   \    /
        \          \  /
         \-----------/
    Allowed: 
      STOP -> TXD
      STOP -> RXD
      TXD  -> RXD
*/
void
mbus_mode ( int mode )
{
    int temp;
    /*
     * Clear read status 
     */
    temp = _io_read ( IO_MBUS_BYTE );
    switch ( mode )
    {
        case MBUS_STOP:
            _io_clr_bit ( IO_MBUS_CTRL, MBUS_CTRL_TXD );
            _io_clr_bit ( IO_MBUS_CTRL, MBUS_CTRL_RXD );
            break;
        case MBUS_TRANSMIT:
            _io_set_bit ( IO_MBUS_CTRL, MBUS_CTRL_TXD );
            _io_clr_bit ( IO_MBUS_CTRL, MBUS_CTRL_RXD );
            break;
        case MBUS_RECEIVE:
            _io_clr_bit ( IO_MBUS_CTRL, MBUS_CTRL_TXD );
            _io_set_bit ( IO_MBUS_CTRL, MBUS_CTRL_RXD );
            break;
    }
    /*
     * Bitcount reset 
     */
    _io_set_bit ( IO_MBUS_STATUS, MBUS_STATUS_BITCNT );
    mbus_curmode = mode;
}


/**
 * Interrupt driven MBUS handler
 */
static void
mbus_int_handler ( void )
{
    /*
     * Hi, I'm an interrupt handler
     */
    //int_fiq_disable(FIQ_MBUSTIM);
    int status = _io_read ( IO_MBUS_STATUS );
    int_fiq_reset ( FIQ_MBUSRX );
    if ( ( mbus_curmode == MBUS_TRANSMIT ) && ( status & MBUS_STATUS_TXDRDY ) )
    {
        /*
         * status send ready 
         */
        if ( mbus_txdptr < mbus_txdsize )
        {
            /*
             * byte available to send 
             */
            _io_set ( IO_MBUS_BYTE, mbus_txdbuffer[mbus_txdptr++] );
        }
        else
        {
            /*
             * TODO: confirm success, wakeup 
             * transmit thread
             */
            if ( mbus_wakeup != 0xFF )
                sched_wakeup ( mbus_wakeup );
            mbus_wakeup = 0xFF;
        }
    }
    if ( ( mbus_curmode == MBUS_RECEIVE ) && ( status & MBUS_STATUS_RXDRDY ) )
    {
        if ( ( status & MBUS_STATUS_BITCNT ) != 0 )
        {
            /*
             * Error. Reset and resynchronize receiver. 
             */
            mbus_mode ( MBUS_RECEIVE );
        }
        else
        {
            if ( mbus_rxdcount < MBUS_QUEUESIZE )
            {
                mbus_rxdbuffer[mbus_rxdhead++] = _io_read ( IO_MBUS_BYTE );
                if ( mbus_rxdhead == MBUS_QUEUESIZE )
                    mbus_rxdhead = 0;
                mbus_rxdcount++;
                /*
                 * TODO: notify there is something in queue 
                 */
            }
            else
            {
                /*
                 * TODO: queue overflow 
                 */
            }
        }
    }
    mbus_ints++;
    //int_fiq_enable(FIQ_MBUSTIM);
}

static void
mbus_timer_handler ( void )
{
    /*
     * FIQ3 handler 
     */
    /*
     * int tmp = _io_read(IO_MBUS_BYTE); 
     * _io_set_bit(IO_MBUS_STATUS, MBUS_STATUS_BITCNT);
     * _io_set_bit(IO_MBUS_CTRL, MBUS_CTRL_RXD);
     * _io_clr_bit(IO_MBUS_CTRL, MBUS_CTRL_TXD);
     */
    /*
     * start transmission? 
     */
}

/**
 * Initialize MBUS driver
 */
void
mbus_start ( int speed )
{
    /*
     * Initialize hardware 
     */
    mbus_init ( speed );

    /*
     * Initialize data 
     */
    mbus_curmode = MBUS_RECEIVE;

    mbus_txdbuffer = 0;
    mbus_txdptr = mbus_txdsize = 0;
    mbus_rxdhead = mbus_rxdtail = mbus_rxdcount = 0;

    /*
     * Enable FIQ 2 handler 
     */
    int_fiq_set_handler ( FIQ_MBUSRX, &mbus_int_handler );
    //int_fiq_set_handler(FIQ_MBUSTIM, &mbus_timer_handler);
}

/**
 * Transmit a block of data over MBUS line. Blocks.
 * *SHOULD* block.
 */
int
mbus_transmit ( unsigned char *data, int size )
{
#ifdef PC
    return 1;
#endif
    return 1;

/*    lcd_clr ();
    lcd_render_text ( 0, 0, "TRenter", 1 );
    lcd_screen_to_io ();*/
/*    
    int_block (  );
    if ( !int_isenabled (  ) || int_isactive (  ) )
    {
//	lcd_render_text ( 0, 8, "TRenter exit", 1 );
//	lcd_screen_to_io ();
        int_unblock (  );
        //return size;
    }
    */
/*    lcd_render_text ( 0, 8, "TRenter succ", 1 );
    lcd_screen_to_io ();*/
    /*
     * TODO: protect with mutex and make threadsafe 
     */
    int_fiq_disable ( FIQ_MBUSRX );
    /*
     * Initialize data structures 
     */
    mbus_txdbuffer = data;
    mbus_txdptr = 0;
    mbus_txdsize = size;


    /*
     * Send first byte 
     */
    // mbus_mode(MBUS_STOP); (makes mess of beginning, we should use
    // FIQ3 for delay probably)

    _io_set ( IO_MBUS_BYTE, mbus_txdbuffer[mbus_txdptr++] );
    mbus_mode ( MBUS_TRANSMIT );

    /*
     * Go... 
     */
    mbus_wakeup = sched_get_current (  );
    int_fiq_enable ( FIQ_MBUSRX );

    /*
     * TODO: block until done
     * We'd need a kind of semaphore for this
     * HACK
     *
     * g3: i think sleep and let wake up would also do
     */

//    while ( mbus_txdptr < mbus_txdsize );

    sched_enter_sleep ( 0xFF, lib_get_time (  ) + ( size * 100 ) ); // 100 ms per char is enough?

//    int_unblock (  );

    if ( mbus_txdptr < mbus_txdsize )
    {
        lcd_render_text ( 0, 16, "0x01 mbus fail", 1 );
        lcd_screen_to_io (  );
        sleep ( 1 );
        return 0;
    }
    return size;
}

/**
 * Receive a block of data over the MBUS line.
 * Returns 0 if no data available. (blocking nyi)
 */
int
mbus_receive ( unsigned char *address, int size )
{
    int retval = 0;
    int_fiq_disable ( FIQ_MBUSRX );
    if ( size > mbus_rxdcount )
        size = mbus_rxdcount;
    retval = size;
    while ( size > 0 )
    {
        *address = mbus_rxdbuffer[mbus_rxdtail];
        mbus_rxdtail++;
        if ( mbus_rxdtail == MBUS_QUEUESIZE )
            mbus_rxdtail = 0;
        address++;
        size--;
    }
    /*
     * decrease number of bytes in queue 
     */
    mbus_rxdcount -= retval;
    int_fiq_enable ( FIQ_MBUSRX );
    return retval;
}


int
mbus_addbuf ( unsigned char *buf, int size )
{
#ifdef PC
    return 0;
#endif
    return 0;
    if ( tid_mbus != 0xFF )
    {
        if ( size )
            return ipc_add ( tid_mbus, buf, size );
        else
            return ipc_add ( tid_mbus, buf, strlen ( buf ) );
    }
    else
    {
        if ( size )
            return mbus_transmit ( buf, size );
        else
            return mbus_transmit ( buf, strlen ( buf ) );
    }
    return 0;
}


int
mbus_print ( unsigned char *text )
{
    mbus_addbuf ( text, 0 );
}
