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
#include <hw/int.h>
#include <hw/io.h>
#include <hw/ioports.h>
#include <hw/sim.h>
#include <hw/mbus.h>
#include <hw/lcd.h>
#include <hw/kpd.h>

short sim_resetted = 0;
unsigned char *sim_recv_buf = NULL;
unsigned int sim_recv_bytes = 0;

volatile void
sim_initcontrol ( void )
{
    _io_set ( SIMI_UART_INT, 0xff );

    int_fiq_disable ( FIQ_SIMUART );
    int_fiq_disable ( FIQ_SIMCARDDETX );
    int_fiq_reset ( FIQ_SIMUART );
    int_fiq_reset ( FIQ_SIMCARDDETX );

    _io_set ( SIMI_CLK_CTRL, 0x03 );

    _io_set_bit ( IO_CTSI_CTRL, 0x20 );

    _io_set ( SIMI_RXD_FL, 0x18 );
    _io_set ( SIMI_RXD_FL, 0x12 );
    _io_set ( SIMI_RXD_FL, 0x06 );
    _io_set ( SIMI_TXD_FL, 0x1A );
    _io_set ( SIMI_TXD_FL, 0x10 );
    _io_set ( SIMI_TXD_FL, 0x04 );
    _io_set ( SIMI_CTRL, 0x32 );
}

volatile void
sim_reset ( void )
{
    unsigned char temp;

    temp = _io_read ( SIMI_RXD );
    usleep ( 1000 );

    _io_set ( SIMI_CTRL, _io_read ( SIMI_CTRL ) | 0x01 );

    usleep ( 1000 );

    _io_set ( SIMI_CTRL, _io_read ( SIMI_CTRL ) | 0x80 );

    _io_set ( SIMI_TXD_LWM, 0x60 );
    sim_resetted = 1;
}

void
sim_setcontrol ( void )
{
    _io_set ( SIMI_CLK_CTRL, _io_read ( SIMI_CLK_CTRL ) & 0xfd );
    _io_set ( SIMI_CTRL, _io_read ( SIMI_CTRL ) & 0xef );
}

void
sim_int_handler ( void )
{
    int status;
    unsigned char uart_int;

    int_fiq_disable ( FIQ_SIMUART );

    uart_int = _io_read ( SIMI_UART_INT );
    int_fiq_reset ( FIQ_SIMUART );

    _io_set ( SIMI_UART_INT, uart_int );

    if ( !( uart_int >> 6 ) )
    {
        status = _io_read ( IO_MBUS_STATUS );
        if ( status & 0x10 )
            _io_set ( IO_MBUS_BYTE, 0x06 );
        mbus_mode ( MBUS_TRANSMIT );
    }

    if ( !( uart_int >> 5 ) )
    {
        status = _io_read ( IO_MBUS_STATUS );
        if ( status & 0x10 )
            _io_set ( IO_MBUS_BYTE, 0x05 );
        mbus_mode ( MBUS_TRANSMIT );
    }

    if ( !( uart_int >> 7 ) )
    {
        //Receive data
        sim_receive ( sim_recv_buf );
    }

    if ( !( uart_int >> 2 ) )
    {
        status = _io_read ( IO_MBUS_STATUS );
        if ( status & 0x10 )
            _io_set ( IO_MBUS_BYTE, 0x02 );
        mbus_mode ( MBUS_TRANSMIT );
    }

    if ( !( uart_int >> 8 ) )
    {
        status = _io_read ( IO_MBUS_STATUS );
        if ( status & 0x10 )
            _io_set ( IO_MBUS_BYTE, 0x08 );
        mbus_mode ( MBUS_TRANSMIT );

    }
    int_fiq_enable ( FIQ_SIMUART );
}

void
sim_transmit ( unsigned char *data, short num )
{
    short i;

    _io_set ( SIMI_TXD_LWM, 0x66 );
    _io_set ( SIMI_TXD_FL, 0x04 );

    for ( i = 0; i < num; i++ )
        _io_set ( SIMI_TXD, data[i] );

    _io_set ( SIMI_TXD_FL, 0x00 );
}

unsigned char
process_byte ( unsigned char rx_byte )
{
    if ( sim_resetted )
    {
        if ( rx_byte == 0x03 )
        {
            // Switch to ISO1177 inverse convention
            _io_set ( SIMI_CLK_CTRL, _io_read ( SIMI_CLK_CTRL ) | 0x0C );
            rx_byte = 0x3F;
        }
        sim_resetted = 0;
    }
    return ( rx_byte );
}

void
sim_receive ( unsigned char *data )
{
    short i;
    unsigned char rx_byte;

    _io_set ( SIMI_RXD_FL, 0x06 );

    i = _io_read ( SIMI_RXD_QUE );
    while ( i > 0 )
    {
        rx_byte = _io_read ( SIMI_RXD );
        data[sim_recv_bytes++] = process_byte ( rx_byte );
        i--;
    }
}

void
sim_init ( void )
{
    if ( sim_recv_buf )
        free ( sim_recv_buf );
    sim_recv_buf = malloc ( 200 );
    int_fiq_set_handler ( FIQ_SIMUART, sim_int_handler );
}

unsigned char *
sim_get_buf ( void )
{
    return sim_recv_buf;
}

unsigned int
sim_get_buflen ( void )
{
    return sim_recv_bytes;
}

void
sim_clr_buf ( void )
{
    memset ( sim_recv_buf, 0x00, 200 );
    sim_recv_bytes = 0;
}
