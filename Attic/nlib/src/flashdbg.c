/**
 * Nokia Flasher functions
 * wumpus <gnufnork@hetdigitalegat.nl> 2003
 */

#include <nlib/typedef.h>
#include <nlib/nokio.h>
#include <nlib/flashdbg.h>
#include <nlib/interrupt.h>

/**
 * Simple clocked serial -- Receive byte
 */
uint
IO_flashdbgReceiveByte (  )
{
    while ( !( _io[IO_MBUS_STATUS] & 0x20 ) ) ;
    return _io[IO_MBUS_BYTE];
}

/**
 * Simple clocked serial -- Send byte
 */
void
IO_flashdbgSendByte ( uint dat )
{
    int x;
    for ( x = 8; x > 0; x-- )
    {
        /*
         * wait SCL low 
         */
        while ( ( _io[IO_MBUS_STATUS] & 0x40 ) ) ;
        _io[IO_MBUS_STATUS] = dat << 7;
        /*
         * wait SCL high 
         */
        while ( !( _io[IO_MBUS_STATUS] & 0x40 ) ) ;
        dat >>= 1;
    }
}

/**
 * Simple clocked serial -- Set SDA (for host signalling/notification)
 */
void
IO_flashdbgSetSDA ( int state )
{
    IO_setBit ( IO_MBUS_STATUS, 0x80, state );
}

void
IO_flashdbgSendPacket ( uint8 * packet, uint length )
{
    IO_globalInterruptEnable ( 0 );

    IO_flashdbgSetSDA ( 0x80 );
    IO_flashdbgSendByte ( length );
    while ( length )
    {
        IO_flashdbgSendByte ( *packet );
        packet++;
        length--;
    }
    IO_flashdbgSetSDA ( 0x00 );

    IO_globalInterruptEnable ( 1 );
}

void
IO_flashdbg ( uint code, uint8 * param, uint length )
{
    uint8 spacket[4 + length];
    int x;
    *( uint32 * ) & spacket[0] = code;
    for ( x = 0; x < length; x++ )
    {
        spacket[x + 4] = param[x];
    }
    IO_flashdbgSendPacket ( spacket, sizeof ( spacket ) );
}
