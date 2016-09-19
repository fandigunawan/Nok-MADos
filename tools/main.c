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

#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/io.h>

#define LPT_BASE    0x378
#define LPT_DATA    (LPT_BASE)
#define LPT_STATUS  (LPT_BASE+1)
#define LPT_CONTROL (LPT_BASE+2)

#define LPT_BIDI    0x20

#define XBUS_MBUS   0x01
#define XBUS_VPP1   0x02
#define XBUS_FBUSRX 0x04
#define XBUS_VPP2   0x08
#define XBUS_BTEMP  0x10

#define XBUS_FBUSTX 0x80


int delay = 0;
int verbose = 1;
int debug = 0;

int
delay_read ( void )
{
    int i = delay;
    int foo = 0;

    while ( i-- )
        foo = get_sda (  );

    return foo;
}

int
get_sda (  )
{
    return inb ( LPT_STATUS ) & XBUS_FBUSTX;
}

int
set_sda ( int state )
{
    if ( state )
        outb ( XBUS_VPP1 | XBUS_VPP2 | XBUS_FBUSTX, LPT_DATA );
    else
        outb ( XBUS_VPP1 | XBUS_VPP2, LPT_DATA );
}

int
set_scl ( int state )
{
    if ( state )
        outb ( XBUS_VPP1 | XBUS_VPP2 | XBUS_MBUS, LPT_DATA );
    else
        outb ( XBUS_VPP1 | XBUS_VPP2, LPT_DATA );

}

int
wait_sync (  )
{
    unsigned char byte = 0;
    int i = 0;
    int max = 0;

    while ( byte != 0x55 )
    {
        if ( byte & 1 )
        {
//      printf ( "waiting for low\n" );
            i = 0;
            set_scl ( 1 );
            while ( get_sda (  ) )
                i++;
//      printf ( "i: %i\n", i );
            if ( i > max )
                max = i;
        }
        else
        {
            if ( byte )
            {
//      printf ( "waiting for high\n" );
                i = 0;
                set_scl ( 1 );
                while ( !get_sda (  ) )
                    i++;
//      printf ( "i: %i\n", i );
                if ( i > max )
                    max = i;
            }
            else
            {
                set_scl ( 1 );
                usleep ( 10000 );
            }
        }

        set_scl ( 0 );
        byte <<= 1;
        if ( get_sda (  ) )
            byte |= 1;


        usleep ( 10000 );
    }

    byte = 0;
    while ( byte != 0xAA )
    {
        if ( byte & 1 )
        {
//      printf ( "waiting for low\n" );
            i = 0;
            set_scl ( 1 );
            while ( get_sda (  ) )
                i++;
//      printf ( "i: %i\n", i );
            if ( i > max )
                max = i;
        }
        else
        {
            if ( byte )
            {
//      printf ( "waiting for high\n" );
                i = 0;
                set_scl ( 1 );
                while ( !get_sda (  ) )
                    i++;
//      printf ( "i: %i\n", i );
                if ( i > max )
                    max = i;
            }
            else
            {
                set_scl ( 1 );
                usleep ( 10000 );
            }
        }

        set_scl ( 0 );
        byte <<= 1;
        if ( get_sda (  ) )
            byte |= 1;
        usleep ( 1000 );
    }

//    printf ( "delay max: %i\n", max );
    delay = max * 1.1;
    if ( verbose > 3 )
        printf ( " - calibrated delay loop: %i\n", delay );
    return 1;
}

unsigned char
get_byte (  )
{
    unsigned char byte = 0;
    int pos = 0;

    while ( pos < 8 )
    {
        set_scl ( 1 );
        delay_read (  );
        set_scl ( 0 );
        byte <<= 1;
        if ( get_sda (  ) )
            byte |= 1;
        delay_read (  );
        pos++;
    }
    return byte;
}

int
send_byte ( unsigned char b )
{
    int pos = 0;

    while ( pos < 8 )
    {
        if ( debug > 3 )
            printf ( "Wait for SDA High, then %ssetting SCL\n", ( b & 0x80 ) ? "re" : "" );
        while ( !get_sda (  ) ) ;
        if ( b & 0x80 )
            set_scl ( 0 );
        else
            set_scl ( 1 );
        if ( debug > 3 )
            printf ( "Wait for SDA Low\n" );
        while ( get_sda (  ) ) ;
        b <<= 1;
        pos++;
    }
//    set_scl ( 0 );
}

int
get_block (  )
{
    int len;
    int i = 0;
    int pos = 0;
    int first = 0;
    unsigned char buf[1024];

    wait_sync (  );
    len = get_byte (  );
    if ( get_byte (  ) == 1 )
        verbose = 0;
    else
        verbose = 3;

//    if ( verbose > 2 )
//  printf ( " - bytes: %02X\n", len );


    while ( pos < len )
        buf[pos++] = get_byte (  );


    if ( buf[len - 1] == 0x00 )
        printf ( " - text:  %s\n", buf );
    pos = 0;

    if ( verbose > 2 )
    {
        while ( pos < len )
        {
            if ( !first++ )
                printf ( " - data:  " );
            else
                printf ( "        " );
            for ( i = 0; i < 16; i++ )
            {
                if ( pos < len )
                    printf ( "%02X ", buf[pos++] );
            }
            printf ( "\n" );
        }
    }
//    printf ( "\n" );
}

void
sched_on ( void )
{
    struct sched_param param;

    param.sched_priority = 99;
    if ( sched_setscheduler ( getpid (  ), SCHED_FIFO, &param ) ) ;
//        printf ( "cannot set scheduling policy\n" );
}

void
sched_off ( void )
{
    struct sched_param param;

    param.sched_priority = 00;
    if ( sched_setscheduler ( getpid (  ), SCHED_FIFO, &param ) ) ;
//        printf ( "cannot set scheduling policy\n" );
    sched_yield (  );
}


int
cmd_delay ( int delay )
{
    sched_on (  );
    if ( debug )
        printf ( "sending 0xAA\n" );
    send_byte ( 0xAA );
    if ( debug )
        printf ( "sending 0x55\n" );
    send_byte ( 0x55 );

    send_byte ( 0x03 );
    send_byte ( 0x02 );
    send_byte ( ( delay >> 8 ) & 0xFF );
    send_byte ( delay & 0xFF );
    sched_off (  );
}

int
cmd_set ( int addr, unsigned char val )
{
    sched_on (  );
    if ( debug )
        printf ( "sending 0xAA\n" );
    send_byte ( 0xAA );
    if ( debug )
        printf ( "sending 0x55\n" );
    send_byte ( 0x55 );

    send_byte ( 0x06 );
    send_byte ( 0x01 );
    send_byte ( ( addr >> 24 ) & 0xFF );
    send_byte ( ( addr >> 16 ) & 0xFF );
    send_byte ( ( addr >> 8 ) & 0xFF );
    send_byte ( addr & 0xFF );
    send_byte ( val );
    sched_off (  );

}

int
cmd_get ( int addr, int bytes )
{
    sched_on (  );
    if ( debug )
        printf ( "sending 0xAA\n" );
    send_byte ( 0xAA );
    if ( debug )
        printf ( "sending 0x55\n" );
    send_byte ( 0x55 );

    send_byte ( 0x09 );
    send_byte ( 0x00 );
    send_byte ( ( addr >> 24 ) & 0xFF );
    send_byte ( ( addr >> 16 ) & 0xFF );
    send_byte ( ( addr >> 8 ) & 0xFF );
    send_byte ( addr & 0xFF );

    send_byte ( ( bytes >> 24 ) & 0xFF );
    send_byte ( ( bytes >> 16 ) & 0xFF );
    send_byte ( ( bytes >> 8 ) & 0xFF );
    send_byte ( bytes & 0xFF );
    sched_off (  );

}

main (  )
{
    int i;
    int j;
    int done = 0;
    int addr, val;
    int get_addr;
    int get_len;
    int set_addr;
    int set_data;
    int delay;
    char buf[32];

    printf ( "\n" );
    printf ( " X-Bus/Flashdebug client for PC\n" );
    printf ( "\n" );
    printf ( "\n" );

    ioperm ( LPT_BASE, 3, 1 );

    outb ( 0x00, LPT_DATA );
    outb ( 0x00, LPT_STATUS );
    outb ( 0x00, LPT_CONTROL );

    set_scl ( 1 );

    if ( get_sda (  ) )
    {
        printf ( " - cable problem, please remove battery and startup phone again\n" );
        printf ( " - the phone MUST NOT make a noise when connecting the flasher cable\n" );
        while ( get_sda (  ) ) ;
        sleep ( 2 );
        printf ( " - cable OK\n\n" );
    }

    while ( !done )
    {
        set_scl ( 1 );
        printf ( "enter command :  " );
        fflush ( stdout );
        if ( read ( 0, &buf, 31 ) == -1 )
            exit ( 0 );
        if ( !strncasecmp ( buf, "quit", 4 ) )
            done = 1;
        else if ( !strncasecmp ( buf, "get ", 4 ) )
        {
            if ( sscanf ( buf, "get %X %i", &get_addr, &get_len ) != 2 )
                printf ( "Syntax: get <(hex)addr> <(dec)bytes>\n" );
            else
            {
                printf ( "Getting %i bytes at 0x%08X\n", get_len, get_addr );
                cmd_get ( get_addr, get_len );
            }
        }
        else if ( !strncasecmp ( buf, "set ", 4 ) )
        {
            if ( sscanf ( buf, "set %X %X", &set_addr, &set_data ) != 2 )
                printf ( "Syntax: set <(hex)addr> <(hex)byte>\n" );
            else
            {
                printf ( "Setting 0x%08X to 0x%02X\n", set_addr, set_data );
                cmd_set ( set_addr, set_data );
            }
        }
        else if ( !strncasecmp ( buf, "delay ", 6 ) )
        {
            if ( sscanf ( buf, "delay %i", &delay ) != 1 )
                printf ( "Syntax: delay <(int)delay>\n" );
            else
            {
                printf ( "Setting delay to %i\n", delay );
                cmd_delay ( delay );
            }
        }
        else if ( !strncasecmp ( buf, "debug ", 6 ) )
        {
            if ( sscanf ( buf, "debug %i", &debug ) != 1 )
                printf ( "Syntax: debug <(int)debug>\n" );
            else
                printf ( "Setting debug level to %i\n", debug );
        }
        else
        {
            printf ( "Invalid command\nAvailable commands: get, set, delay, debug, quit\n" );
        }

    }
/*
    for ( ;; )
    {
        if ( get_sda (  ) )
        {
            printf ( " - cable problem, please remove battery and startup phone again\n" );
            printf ( " - the phone MUST NOT make a noise when connecting the flasher cable\n" );
            while ( get_sda (  ) ) ;
            sleep ( 2 );
            printf ( " - cable OK\n\n" );
        }
#if 0


//                                  printf ( "sending 0x55\n" );
//                                  send_byte ( 0x55 );
//                                  printf ( "sending 0xAA\n" );
//                                  send_byte ( 0xAA );

        while ( 1 )
        {
            printf ( "enter addr:value :\n  " );
            if ( read ( 0, &buf, 5 ) == -1 )
                exit ( 0 );
            if ( sscanf ( buf, "%02X:%02X", &addr, &val ) == 2 )
            {
                printf ( "sending 0x55\n" );
                send_byte ( 0x55 );
                printf ( "sending 0xAA\n" );
                send_byte ( 0xAA );
                send_byte ( addr );
                send_byte ( val );
            }
        }

        while ( 1 )
        {
            printf ( "SDA High\n" );
            set_sda ( 1 );
            for ( j = 0; j < 8; j++ )
            {
                set_scl ( i++ % 2 );
                usleep ( 200000 );
            }
            printf ( "SDA Low\n" );
            set_sda ( 0 );
            for ( j = 0; j < 8; j++ )
            {
                set_scl ( i++ % 2 );
                usleep ( 200000 );
            }
        }
#endif
        get_block (  );

    }
    */
}
