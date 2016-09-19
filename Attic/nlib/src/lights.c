#include <nlib/typedef.h>
#include <nlib/nokio.h>
#include <nlib/lights.h>

/**
 * Switch LEDs on front
 *
 * In: 0	Leds off
 *     1	LCD leds on 
 *     2	KEY leds on
 *     3	KEY and LCD leds on
 */
void
IO_setLights ( int state )
{
    /*
     * Set display led state 
     */
    IO_setBit ( IO_CTRL3, CTRL3_DISPLAYLEDS, state & 1 );
    /*
     * Enable key leds as Output 
     */
    IO_setBit ( IO_GENIO_RW, 0x08, 1 );
    /*
     * Set key led state 
     */
    IO_setBit ( IO_GENIO_D, 0x08, state & 2 );
}
