/**
 * LCD functions for Philips LCD
 * wumpus <blacksphere@goliath.darktech.org> 2003
 */
#include <nlib/typedef.h>
#include <nlib/nokio.h>
#include <nlib/gensio.h>
#include <nlib/lcd.h>

void
IO_LCDSendCmd ( uint cmd )
{
    IO_gensioWait ( 0x01 );
    _io[IO_LCD_CMD] = cmd;
}

void
IO_LCDSendData ( uint dat )
{
    IO_gensioWait ( 0x01 );
    _io[IO_LCD_DATA] = dat;
}

void
IO_LCDInitialize (  )
{
    int x, y;
    /*
     * LCD reset 
     */
    IO_gensioStart (  );

    /*
     * Reset 
     */
    IO_setBit ( 0x32, 0x20, 0 );
    IO_setBit ( 0x32, 0x20, 1 );

    IO_LCDSendCmd ( 0x24 );
    for ( x = 0; x < 6; x++ )
    {
        IO_LCDSendCmd ( 0x40 | x );
        IO_LCDSendCmd ( 0x80 );
        for ( y = 0; y < 84; y++ )
        {
            IO_LCDSendData ( 0x00 );
        }
    }
    //IO_LCDSendCmd(0x20);
    //IO_gensioStart();

    IO_LCDSendCmd ( 0x21 );     /* extended commands */
    IO_LCDSendCmd ( 0x04 | 0x01 );  /* TC */
    IO_LCDSendCmd ( 0x10 | 0x04 );  /* Bias system */
    IO_LCDSendCmd ( 0x80 | 0x40 );  /* VOP 0x40 */
    IO_LCDSendCmd ( 0x20 );     /* non extended commands */
    IO_LCDSendCmd ( 0x0C );     /* Normal operating mode (inverse) */
}

/* Set contrast */
void
IO_LCDSetContrast ( int vop )
{
    IO_LCDSendCmd ( 0x21 );     /* extended commands */
    IO_LCDSendCmd ( 0x80 | ( vop & 0x7F ) );    /* VOP */
    IO_LCDSendCmd ( 0x20 );     /* non extended commands */
}
