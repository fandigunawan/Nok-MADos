/**
 * Generic I/O functions
 * wumpus <blacksphere@goliath.darktech.org> 2003
 */

#include <nlib/typedef.h>
#include <nlib/nokio.h>

/**
 * Table for initial CTRL I/O values.
 */
static uint8 ctrlio_base[] = {
    /*
     * 0x70 - 0x73 
     */
    0x00, 0x02, 0xA0, 0x63,     /* 0x73 0x6B for 3310 */
    /*
     * 0xB0 - 0xB3 
     */
    0xFF, 0xFD, 0x5F, 0x00
};

/**
 * Most basic I/O initialisations.
 */
void
IO_initialize (  )
{
    int x;
    /*
     * CTRL I/O 
     */
    for ( x = 0; x < 4; x++ )
    {
        _io[0x70 + x] = ctrlio_base[x + 0];
        _io[0xB0 + x] = ctrlio_base[x + 4];
    }
}


void
usleep ( uint micros )
{
    while ( micros > 0 )
    {
        asm ( "nop" );
        asm ( "nop" );
        micros--;
    }
}

/**
 * Set or clear bits in an I/O register.
 *
 * @param register [0x00-0xFF] I/O register to alter.
 * @param bit      [0x00,0x01,0x02...] Bits to set or clear.
 * @param mode     0=clear, 1=set
 */
void
IO_setBit ( uint reg, uint bit, uint mode )
{
    /*
     * todo disable interrupts 
     */
    if ( mode )
        _io[reg] |= bit;
    else
        _io[reg] &= ~bit;
    /*
     * todo enable interrupts 
     */
}
