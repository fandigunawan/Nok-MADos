#include <nlib/typedef.h>
#include <nlib/nokio.h>
#include <nlib/ptimer.h>

/**
 * 0 programmable timer
 * 1 sleep timer
 */
int
IO_getTimestamp ( int type )
{
    int time1, time2;
    int port;
    if ( type == 0 )
        port = IO_TIMESTAMP;
    else
        port = 0x4;
    do
    {
        time1 = ioreadw ( port );
        time2 = ioreadw ( port );
    }
    while ( time1 != time2 );
    return time1;
}

void
IO_delay ( int wait )
{
    int begin = IO_getTimestamp ( 0 );
    int diff;
    do
    {
        diff = ( IO_getTimestamp ( 0 ) - begin ) & 0xFFFF;
    }
    while ( diff < wait );
}
