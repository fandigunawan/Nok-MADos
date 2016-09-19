#include <nlib/typedef.h>
#include <nlib/nokio.h>
#include <nlib/flashdbg.h>
#include <nlib/dsp.h>

/**
 * Initialize gensio
 */
void
IO_gensioInitialize (  )
{
    /*
     * Phase 1 
     */
    _io[0xAF] = 0x60;
    _io[0x6F] = 0x04;
    _io[0xEF] = 0x00;

    /*
     * Phase 2 
     */
    _io[IO_CLOCKS] |= CLOCK_GENSIO;

    _io[0xAD] = 0xCF;
    _io[0xED] = 0x20;
    _io[0xAE] = 0x20;
    _io[0xEE] = 0x80;
}

/**
 * Wait for gensio status bits.
 */
void
IO_gensioWait ( uint bits )
{
    while ( !( _io[IO_LCD_STATUS] & bits ) ) ;
}

/**
 * GenSIO control send
 */
void
IO_gensioSend ( uint xxx )
{
    IO_gensioWait ( 0x02 );
    _io[IO_GENSIO_CTRL] = xxx;
}

/**
 * This is used before CCont and LCD serial operations.
 */
void
IO_gensioStart (  )
{
    /*
     * 0010 0101 
     */
    IO_gensioSend ( 0x25 );
    //IO_gensioSend(0x05); /* 00110111 3456 */
    //IO_gensioSend(0x37); /* 00110111 3456 */
    //IO_gensioSend(0x35); /* 00110101 3168 */
    //IO_gensioSend(0x30); /* 00110000 2448 */
    //IO_gensioSend(0x2F); /* 00101111 2305 */
    //IO_gensioSend(0x2E); /* 00101110 2160 */
    //IO_gensioSend(0x2D); /* 00101101 2016 */
    //IO_gensioSend(0x2C); /* 00101100 1872 */
    //IO_gensioSend(0x2B); /* 00101011 1728 */
    //IO_gensioSend(0x2A); /* 00101010 1584 */
    //IO_gensioSend(0x29); /* 00101001 1440 */
    //IO_gensioSend(0x28); /* 00101000 1296 */
    //IO_gensioSend(0x27); /* 00100111 1153 */
    //IO_gensioSend(0x25); /* 00100101 981 */
    //IO_gensioSend(0x24); /* 00100100 981 */
    //IO_gensioSend(0x23); /* 00100011  */
}
