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


#include <hw/phoneinfo.h>
#include <hw/io.h>
//
// GENSIO and other IO init 
// so i named it genIO init ;)
//

/**
 * Table for initial CTRL I/O values.
 */
static const unsigned char ctrlio_base[3][22] = {
    {0x70, 0x00, 0x71, 0x02, 0x72, 0xA0, 0x73, 0x63,
     0xB0, 0xFF, 0xB1, 0xFD, 0xB2, 0x5F, 0xB3, 0x00,
     0xAF, 0x60, 0x6F, 0x04, 0xEF, 0x00},
    {0x70, 0x00, 0x71, 0x02, 0x72, 0x20, 0x73, 0x2B,
     0xB0, 0xFF, 0xB1, 0xFD, 0xB2, 0xFF, 0xB3, 0x00,
     0xAF, 0x64, 0x6F, 0x00, 0xEF, 0x00},
    // 6210:
    {0x70, 0x00, 0x71, 0x02, 0x72, 0x21, 0x73, 0x23,
     0xB0, 0xFF, 0xB1, 0xFD, 0xB2, 0xDE, 0xB3, 0x10,
     0xAF, 0x00, 0x6F, 0x05, 0xEF, 0x00}
};

/**
 * Most basic I/O initialisations.
 */
void
genio_init ( void )
{
    int x;

#ifndef PHONE_5110
    for ( x = 0; x < 11; x++ )
        _io_set ( ctrlio_base[mados_info[mados_phone].genio][2 * x], ctrlio_base[mados_info[mados_phone].genio][( 2 * x ) + 1] );


    // before converting to new _io method, we have to decode this sequence ;)
    // dont know how to name them    

    io_set ( 0x000200AD, 0x00 );
    io_set ( 0x000200ED, 0x00 );
    io_set ( 0x000200AE, 0xA0 );
    io_set ( 0x000200EE, 0x00 );
#endif

    _io_set_bit ( IO_CTSI_CTRL, CTSI_CTL_GC | CTSI_CTL_UU );

    io_set ( 0x00020024, 0x19 );    // CCUT, LCD LED and CHARLIM as output

//    io_set ( 0x00020072, 0xA0 );  // LCD Reset and another unkown port as output
//    io_set ( 0x000200B2, 0xFF );  // as nokia does it
//    io_set ( 0x00020073, 0x6B );  // BUTTON_CTRL, CHAR_CTRL, MMAP, KBD LED and Vpp as output
//    io_set ( 0x000200B3, 0x00 );  // as nokia does it

}
