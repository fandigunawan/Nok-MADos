/**
 * CCont routines
 */
#include <nlib/typedef.h>
#include <nlib/nokio.h>
#include <nlib/gensio.h>
#include <nlib/ccont.h>


char ccont_cache[CCONT_REGS];
/**
 * Write to CCont register
 *
 * Parameters: 
 * Reg has the form
 * 0xHHLL   HH register ID   
 *          LL mask
 * For example, 0x01FF is "all bits of register 0x01"
 *              0x8000(CCONT_WRITECACHE) is "Write cache only"
 * @tested
 */
void
IO_CContWrite ( uint reg, uint value )
{
    uint mask = reg & 0xFF, x;
    uint cacheonly = reg & CCONT_WRITECACHE;
    reg = ( reg >> 8 ) & 0x1F;

    /*
     * Zero mask would mean infinity loop and no operation - bye 
     */
    if ( mask == 0 )
        return;

    /*
     * Shift value its rightful place in the byte 
     */
    for ( x = mask; !( x & 1 ); x >>= 1 )
        value <<= 1;
    /*
     * Apply stored value and cache it 
     */
    ccont_cache[reg] = value | ( ccont_cache[reg] & ( ~mask ) );
    if ( !cacheonly )
    {
        /*
         * Do real write, if approciate 
         */
        IO_gensioStart (  );
        /*
         * Send command byte 
         */
        IO_gensioWait ( 0x03 );
        _io[IO_CCONT_WRITE] = ( reg << 3 );
        /*
         * Send data byte 
         */
        IO_gensioWait ( 0x03 );
        _io[IO_CCONT_WRITE] = value;
        //IO_flasherSendByte(value);
    }
}

/**
 * Read from CCont register
 *
 * Reg has the form
 * 0xHHLL   HH register ID   
 *          LL mask
 * For example, 0x01FF is "all bits of register 0x01"
 *              0x8000(CCONT_READCACHE) is "read from cache only"
 * @tested
 */
int
IO_CContRead ( uint reg )
{
    uint mask = reg & 0xFF, x;
    uint readcache = reg & CCONT_WRITECACHE;
    reg = ( reg >> 8 ) & 0x1F;
    if ( mask == 0 )
        return 0x00;

    int value;
    if ( readcache )
    {
        value = ccont_cache[reg];
    }
    else
    {
        /*
         * Read CCont hardware 
         */
        IO_gensioStart (  );

        /*
         * Send command byte 
         */
        IO_gensioWait ( 0x03 );
        _io[IO_CCONT_WRITE] = ( reg << 3 ) | 0x04;

        /*
         * Read data byte 
         */
        IO_gensioWait ( 0x04 );
        value = _io[IO_CCONT_READ];
    }
    /*
     * Cache new value 
     */
    //if(!nocache)
    //IO_CContWrite((reg<<8)|0x8000, value); 

    /*
     * Clip to mask and shift value to lowest bit position 
     */
    value &= mask;
    for ( x = mask; !( x & 1 ); x >>= 1 )
        value >>= 1;
    return value;
}

/**
 * Read CCont A/D converter
 *
 * In: n is 0..7
 * Out: 0x000..0x3FF
 * @tested
 */
uint
IO_CContADRead ( int n )
{
    /*
     * Enable AD converters, and select number 'n' 
     */
    IO_CContWrite ( 0x0078, ( n << 1 ) | 0x01 );
    uint low = IO_CContRead ( 0x02FF );
    uint high = IO_CContRead ( 0x0303 );
    return ( high << 8 ) | low;
}

/**
 * Initialize the CCont peripihal
 */
void
IO_CContInitialize (  )
{
    /*
     * Write initial values 
     */
    IO_CContWrite ( 0x00FF, 0x00 ); //0
    IO_CContWrite ( 0x01FF, 0x00 ); //1
    IO_CContWrite ( 0x03FF, 0x0B ); //3
    usleep ( 2000 );
    IO_CContWrite ( 0x04FF, 0x20 ); //5
    IO_CContWrite ( 0x05FF, 0x20 ); //6
    IO_CContWrite ( 0x06FF, 0x54 ); //7
    IO_CContWrite ( 0x07FF, 0x00 ); //8

    /*
     * Pre cache values 
     */
    IO_CContRead ( 0x0AFF );
    IO_CContRead ( 0x0BFF );
    IO_CContRead ( 0x0CFF );
    IO_CContRead ( 0x0DFF );
    IO_CContRead ( 0x0FFF );
}
