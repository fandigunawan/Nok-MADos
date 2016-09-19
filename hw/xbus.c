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
#include <hw/xbus.h>

int delay = 100;
int xbus_enabled = 0;

void
xbus_enable ( void )
{
    xbus_enabled = 1;
}

int
xbus_isenabled ( void )
{
    return xbus_enabled;
}

void
xbus_disable ( void )
{
#ifdef PC
    sleep ( 10 );
#endif
    xbus_enabled = 0;
}


void
xbus_init ( void )
{
    io_set ( 0x00020015, io_read ( 0x00020015 ) & 0xF8 );
    io_set ( 0x00020015, io_read ( 0x00020015 ) & 0xBF );
    io_set ( 0x00020015, io_read ( 0x00020015 ) & 0xF7 );
    io_set ( 0x00020015, io_read ( ( 0x00020015 ) & 0xF7 ) | ( 1 << 3 ) );
//    io_set ( 0x00020018, 0x03 );
//    io_set ( 0x00020019, 0x40 );

}

/**
 * Simple clocked serial -- Set SDA (for host signalling/notification)
 */
void
xbus_set_sda ( int state )
{
    if ( state )
        _io_set_bit ( IO_MBUS_STATUS, 0x80 );
    else
        _io_clr_bit ( IO_MBUS_STATUS, 0x80 );
}

unsigned char
xbus_get_scl ( void )
{
    if ( _io_read ( IO_MBUS_STATUS ) & 0x40 )
        return 1;
    return 0;
}

unsigned char
xbus_get_sda ( void )
{
    if ( _io_read ( IO_MBUS_STATUS ) & 0x80 )
        return 1;
    return 0;
}


/**
 * Simple clocked serial -- Receive byte
 */
unsigned int
xbus_receive_byte (  )
{
    while ( !( _io[IO_MBUS_STATUS] & 0x20 ) ) ;
    return _io[IO_MBUS_BYTE];
}

/**
 * Simple clocked serial -- Send byte
 */
void
xbus_send_byte ( unsigned int dat )
{
    unsigned char val;
    int x;

#ifdef PC
    printf ( " %02X", dat );
    return;
#endif

    for ( x = 8; x > 0; x-- )
    {
        /*
         * wait SCL low 
         */
        while ( xbus_get_scl (  ) ) ;
        val = 1 << ( x - 1 );
        if ( ( dat & val ) == val )
            xbus_set_sda ( 1 );
        else
            xbus_set_sda ( 0 );
        /*
         * wait SCL high 
         */
        while ( !xbus_get_scl (  ) ) ;
    }
}


void
xbus_send_packet ( unsigned char *packet, unsigned int length )
{
    int type = 0;

    if ( !xbus_enabled )
        return;


    if ( !length )
    {
        length = strlen ( packet ) + 1;
        type = 1;
    }

    int_disable (  );

#ifdef PC
//    printf ( " - bytes %i\n  - ", length );
#else
    xbus_send_byte ( 0x55 );
    xbus_send_byte ( 0xAA );
    xbus_send_byte ( length );
    xbus_send_byte ( type );
#endif

#ifdef PC
    if ( type == 1 )
        printf ( " - text:  %s", packet );
    else
    {
//  printf ( " - bytes: %i\n - data: ", length );
        printf ( " - data: " );
#endif
        while ( length )
        {
            xbus_send_byte ( *packet );
            packet++;
            length--;
        }
#ifdef PC
    }
    printf ( "\n" );
#endif
    xbus_set_sda ( 0 );
    int_enable (  );

}

void
xbus_dbg ( unsigned int code, unsigned char *param, unsigned int length )
{
    unsigned char spacket[128];
    int x;

    if ( length > 124 )
        return;

    *( unsigned int * ) &spacket[0] = code;

    for ( x = 0; x < length; x++ )
        spacket[x + 4] = param[x];

    xbus_send_packet ( spacket, length + 4 );
}

inline void
xbus_delay_read ( void )
{
    int i = delay;

    while ( i-- )
        usleep ( 1000 );
}

int
xbus_wait_sync (  )
{
    unsigned char byte = 0;
    int i = 0;
    int max = 0;
    int wait = 100;

//    xbus_set_sda ( 1 );
//    while ( !xbus_get_scl () && wait-- )
//  usleep ( 1000 );
//    if ( !wait )
//  return 0;


    while ( byte != 0xAA )
    {
        if ( byte & 1 )
        {
            i = 0;
            xbus_set_sda ( 1 );
            while ( xbus_get_scl (  ) )
            {
                usleep ( 1000 );
                i++;
            }
            if ( i > max )
                max = i;
        }
        else
        {
            if ( byte )
            {
                i = 0;
                xbus_set_sda ( 1 );
                while ( !xbus_get_scl (  ) )
                {
                    usleep ( 1000 );
                    i++;
                }
                if ( i > max )
                    max = i;
            }
            else
            {
                xbus_set_sda ( 1 );
                usleep ( 50000 );
            }
        }

        xbus_set_sda ( 0 );
        byte <<= 1;
        if ( xbus_get_scl (  ) )
            byte |= 1;


        usleep ( 50000 );
    }

    byte = 0;
    while ( byte != 0x55 )
    {
        if ( byte & 1 )
        {
            i = 0;
            xbus_set_sda ( 1 );
            while ( xbus_get_scl (  ) )
            {
                usleep ( 1000 );
                i++;
            }
            if ( i > max )
                max = i;
        }
        else
        {
            if ( byte )
            {
                i = 0;
                xbus_set_sda ( 1 );
                while ( !xbus_get_scl (  ) )
                {
                    usleep ( 1000 );
                    i++;
                }
                if ( i > max )
                    max = i;
            }
            else
            {
                xbus_set_sda ( 1 );
                usleep ( 50000 );
            }
        }

        xbus_set_sda ( 0 );
        byte <<= 1;
        if ( xbus_get_scl (  ) )
            byte |= 1;
        usleep ( 50000 );
    }

    xbus_set_sda ( 0 );

    delay = max * 5;
    return 1;
}

unsigned char
xbus_get_byte (  )
{
    unsigned char byte = 0;
    int pos = 0;

    while ( pos < 8 )
    {
        xbus_set_sda ( 1 );
        xbus_delay_read (  );
        xbus_set_sda ( 0 );
        byte <<= 1;
        if ( xbus_get_scl (  ) )
            byte |= 1;
        xbus_delay_read (  );
        pos++;
    }
    xbus_set_sda ( 0 );
    return byte;
}

void
xbus_test ( void )
{
    int bytes = 0;
    int pos = 0;
    unsigned char msg[16];
    unsigned char buf[32];

    while ( 1 )
    {

        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8, "Sync Start", 1 );
        lcd_to_screen (  );

        if ( !xbus_wait_sync (  ) )
            return;

        lcd_clr (  );
        sprintf ( msg, "%i ms", delay );
        lcd_render_text ( 0, 0 * 8, msg, 1 );
//    lcd_render_text ( 0, 0 * 8, "Sync done", 1 );
        lcd_to_screen (  );

        bytes = xbus_get_byte (  );
        sprintf ( msg, "%i bytes", bytes );
        lcd_render_text ( 0, 1 * 8, msg, 1 );
        lcd_to_screen (  );
        pos = 0;
        while ( pos < bytes )
        {
            lcd_clr (  );
            sprintf ( msg, "%i ms", delay );
            lcd_render_text ( 0, 0 * 8, msg, 1 );
            sprintf ( msg, "%i bytes", bytes );
            lcd_render_text ( 0, 1 * 8, msg, 1 );
            lcd_to_screen (  );
            xbus_delay_read (  );
            buf[pos] = xbus_get_byte (  );
            pos++;
        }

        lcd_render_text ( 0, 2 * 8, "read done", 1 );

        switch ( buf[0] )
        {
            case 0x00:
                lcd_render_text ( 0, 3 * 8, "cmd_get", 1 );
                break;
            case 0x01:
                lcd_render_text ( 0, 3 * 8, "cmd_set", 1 );
                break;
            case 0x02:
                lcd_render_text ( 0, 3 * 8, "cmd_delay", 1 );
                delay = buf[1] << 8 + buf[2];
                break;
            default:
                lcd_render_text ( 0, 3 * 8, "UNKNOWN", 1 );
                break;
        }
        lcd_to_screen (  );
        sleep ( 2 );
    }
}


void
xbus_read_test ( void )
{
    int packnum = 0;
    unsigned char byte = 0;
    unsigned char buf[16];

    while ( packnum < 100000 )
    {
        byte = xbus_get_byte (  );
        packnum++;
        if ( byte != 0xDD )
        {
            delay++;
            packnum = 0;
        }
        lcd_clr (  );
        lib_hexconv ( buf, byte );
        lcd_render_text ( 0, 0 * 8, "byte:", 1 );
        lcd_render_text ( 0, 1 * 8, buf, 1 );
        lib_dtoa ( buf, packnum, 5, 0 );
        lcd_render_text ( 0, 2 * 8, "packet:", 1 );
        lcd_render_text ( 0, 3 * 8, buf, 1 );
        lib_dtoa ( buf, delay, 5, 0 );
        lcd_render_text ( 0, 4 * 8, "delay:", 1 );
        lcd_render_text ( 0, 5 * 8, buf, 1 );
        lcd_to_screen (  );
    }
}
