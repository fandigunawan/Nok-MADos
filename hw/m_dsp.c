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
#include <core/lib.h>
#include <hw/flash.h>
#include <hw/dsp.h>
//#include <../nlib/src/dsp.c>

//
//  thanxx to alexd who sent me this code :)
//
// just some test code - see dsp_test
const unsigned short dsp_boot_table[] = {
    0x7706, 0x0000, 0x7707, 0x6900,
    0x771d, 0xFFA8, 0x7718, 0x0079,
    0x7728, 0x2000, 0x7758, 0x3146,
    0xf070, 0xea60, 0xf495, 0x7712,
    0x0800, 0x7713, 0x0801, 0xe501,
    0xf7bd, 0xf6bd, 0xf073, 0x0f14
};


const unsigned short dsp_code_readmem[] = {
    0x7706, 0x0000, 0x7707, 0x6900,
    0x771d, 0xffa8, 0x7718, 0x0079,
    0x7728, 0x2000, 0x7758, 0x3146,
    0xf070, 0xea60, 0xf495, 0x7713,
    0xff00, 0x7712, 0x0800, 0xecff,
    0xe598, 0xf7bd, 0xf6bd, 0xf073,
    0x0f15
};

/* initialize DSP io's
void dsp_init ( void )
{
    dsp_setmem ( DSP_MEM_SHARED );
#ifdef ARM
    dsp_clear_ram ( );
#endif
}*/

// set DSP shmem shared or host-only
void
dsp_setmem ( unsigned int mode )
{
    io_set_bit ( 0x00030000, 0x02 );
    if ( mode == DSP_MEM_SHARED )
        io_clr_bit ( 0x00030000, 0x02 );
}

// generates a DSP int
void
dsp_genint (  )
{
    io_set_bit ( 0x00030000, 0x04 );
}

// resets the DSP (then it boots)
void
dsp_reset ( void )
{
    io_clr_bit ( 0x00020002, 0x01 );
    usleep ( 10 );
    io_set_bit ( 0x00020002, 0x01 );
    usleep ( 10000 );
}


// upload code to the DSP shared mem
void
dsp_upload ( unsigned int block, const unsigned short *src, unsigned int len )
{
    int pos = 0;
    unsigned int addr = 0;

    if ( block + 2 * len <= 0x0FFF )
    {
        for ( addr = 0x00010000 + block; pos < len; addr += 2, pos++ )
            io_set_word ( addr, src[pos] );
    }
    return;
}


// clears DSP ram
void
dsp_clear_ram ( void )
{
    memset ( ( void * ) 0x00010000, 0x00, 0xFFF );
}

// boots the DSP with given code block
void
dsp_bootstrap ( const unsigned short *block, unsigned int len )
{
    dsp_upload ( 0x0E00, block, len );
    dsp_reset (  );
}

// test the DSP through the 1st two shmem words
int
dsp_test ( void )
{
    unsigned short *addr1 = ( unsigned short * ) 0x00010000;
    unsigned short *addr2 = ( unsigned short * ) 0x00010002;

    *addr1 = 0xffff;
    *addr2 = 0x0000;

    if ( *addr1 != 0xFFFF || *addr2 != 0x0000 )
        return 1;

    *addr1 = 0x5555;
    *addr2 = 0xaaaa;

    if ( *addr1 != 0x5555 || *addr2 != 0xaaaa )
        return 2;

    *addr1 = 0xaaaa;
    *addr2 = 0x5555;

    if ( *addr1 != 0xaaaa || *addr2 != 0x5555 )
        return 3;


    *addr1 = 0xffff;
    *addr2 = 0x0000;
    dsp_bootstrap ( dsp_boot_table, sizeof ( dsp_boot_table ) / 2 );

    if ( *addr1 != 0xFFFF || *addr2 != 0xFFFF )
        return 4;

    *addr2 = 0x0000;
    *addr1 = 0x5555;
    dsp_bootstrap ( dsp_boot_table, sizeof ( dsp_boot_table ) / 2 );

    if ( *addr1 != 0x5555 || *addr2 != 0x5555 )
        return 5;

    *addr2 = 0x0000;
    *addr1 = 0xaaaa;
    dsp_bootstrap ( dsp_boot_table, sizeof ( dsp_boot_table ) / 2 );

    if ( *addr1 != 0xaaaa || *addr2 != 0xaaaa )
        return 6;

    return 0;
}



void
dsp_readmem ( void )
{
    int i = 0;

    flash_vpp ( 1 );


    i = flash_erase ( 0x00210000 );
    if ( i & FLASH_STATUS_ES )
        lcd_type_text_2 ( 0, 0 * 8, 3, "erase err", 1 );
    if ( i & FLASH_STATUS_VPPS )
        lcd_type_text_2 ( 0, 1 * 8, 3, "VPP low", 1 );
    dsp_bootstrap ( dsp_code_readmem, sizeof ( dsp_code_readmem ) / 2 );
    sleep ( 1 );

    i = flash_write_ram ( 0x00210000, 0x00010000, 0x10000 );
    if ( i & FLASH_STATUS_ES )
        lcd_type_text_2 ( 0, 0 * 8, 3, "erase err", 1 );
    if ( i & FLASH_STATUS_VPPS )
        lcd_type_text_2 ( 0, 1 * 8, 3, "VPP low", 1 );
}





void
dsp_init (  )
{

    //IRQ4 handling doesn't work yet 
    //IO_globalInterruptEnable(1);     
    DSP_initialize (  );
    DSP_startup (  );

    //IO_setInterruptHandler(IRQ_KEYBOARD, test_k);
//  IO_setInterruptEnable(IRQ_KEYBOARD, 1);
    /*
     * Enable interrupt for column 0-4 
     */
    //_io[IO_KEY_IRQC] &= 0xE0;

    /*
     * Enable all rows 
     */
//  _io[IO_KEY_ROW_SET] = 0x1F;
//  _io[IO_KEY_ROW_CLR] = ~0x1F;    

}
