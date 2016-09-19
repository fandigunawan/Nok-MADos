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
#include <hw/int.h>
#include <hw/flash.h>

unsigned char tempcode[128];


// enable Vpp on flash, needed for flashing
void
flash_vpp ( unsigned int state )
{
    if ( state )
    {
        switch ( mados_info[mados_phone].flashvpp )
        {
            case 0:
                _io_set_bit ( IO_UIF_CTRL3, UIF_CTRL3_VPP );
                break;
            case 1:
                _io_set_bit ( IO_UIF_CTRL2, UIF_CTRL2_VPP1 | UIF_CTRL2_VPP2 );
                break;
        }
    }
    else
    {
        switch ( mados_info[mados_phone].flashvpp )
        {
            case 0:
                _io_clr_bit ( IO_UIF_CTRL3, UIF_CTRL3_VPP );
                break;
            case 1:
                _io_clr_bit ( IO_UIF_CTRL2, UIF_CTRL2_VPP1 | UIF_CTRL2_VPP2 );
                break;
        }
    }
//    usleep ( 50000 );
    return;
}

// code block to read flash identification
unsigned int
flash_read_ident ( void )
{
#ifdef ARM
    asm volatile
        ( "\n   pop  { r0 }\n    push { lr }\n    push { r1, r2, r3, r4, r5, r6, r7 } \n    mov  r1, #0x20\n    lsl  r1, r1, #0x10\n    lsl  r0, r0, #0x01\n    add  r0, r1, r0\n    mov  r2, #0x90\n    mov  r3, #0xFF\n    strh r2, [r1, #0x00]\n    ldrh r2, [r1, #0x00]\n    cmp  r2, #0x20\n    bne  cont\n    \n    @ f*ing ST flashes....\n    @ need to get initialized\n    @ the above read returned 0x20 from the \n    @ first byte in flash, NOT the manuf id\n    \n    ldr  r4, .val1\n    mov  r5, #0xAA\n    strh r5, [r0, r4]\n    \n    ldr  r4, .val2\n    mov  r5, #0x55\n    strh r5, [r0, r4]\n\n    ldr  r4, .val1\n    mov  r5, #0x90\n    strh r5, [r0, r4]\n    \ncont:\n    ldrh r2, [r0, #0x00]\n    strh r3, [r1, #0x00]\n    mov  r0, r2\n    \n    pop  { r1, r2, r3, r4, r5, r6, r7 } \n    pop  { pc }\n    nop\n    \n.val1:\n    .word 0x0000aaaa\n.val2:\n    .word 0x00005554\n    " );
#endif
}

// the same for erasing
unsigned int
flash_clear_block ( void )
{
#ifdef ARM
    asm volatile
        ( "\n    pop  { r0 }\n    push { lr }\n    push { r1, r2, r3, r4, r5, r6, r7 } \n    mov  r1, #0x20\n    lsl  r1, r1, #0x10\n    \n    mov  r2, #0x50\n    strh r2, [r1, #0x00]\n    mov  r2, #0x20\n    strh r2, [r0, #0x00]\n    mov  r2, #0xD0\n    strh r2, [r0, #0x00]\n\n    mov  r3, #0x80\n@    mov  r1, #0x70\nwait:\n@    strh r1, [r1, #0x00]\n    ldrh r2, [r1, #0x00]\n    mov  r4, r2\n    and  r4, r4, r3\n    cmp  r4, #0x00\n    beq  wait\n\n    mov  r0, r2\n    \n    mov  r2, #0x50\n    strh r2, [r1, #0x00]\n    mov  r2, #0xFF\n    strh r2, [r1, #0x00]\n    \n    pop  { r1, r2, r3, r4, r5, r6, r7 } \n    pop  { pc }\n    nop\n    \n    " );
#endif
}

// and for flashing
unsigned int
flash_write_block ( void )
{
#ifdef ARM
    asm volatile
        ( "\n    pop  { r0, r1, r2 }\n    push { lr }\n    push { r1, r2, r3, r4, r5, r6, r7 } \n    \n    mov  r3, #0x20\n    lsl  r3, r3, #0x10\n    \nloop:\n    cmp  r2, #0x00\n    beq  end\n    \n    mov  r4, #0x50\n    strh r4, [r3, #0x00]\n    mov  r4, #0x40\n    strh r4, [r3, #0x00]\n\n    ldrh r4, [r1, #0x00]\n    strh r4, [r0, #0x00]\n    add  r0, #0x02\n    add  r1, #0x02\n    sub  r2, #0x02\n\n    mov  r5, #0x80\npwait:\n    ldrh r6, [r3, #0x00]\n    mov  r4, r6\n    and  r4, r4, r5\n    cmp  r4, #0x00\n    beq  pwait\n    b loop\n\nend:\n    mov  r0, r6\n    \n    mov  r4, #0x50\n    strh r4, [r3, #0x00]\n    mov  r4, #0xFF\n    strh r4, [r3, #0x00]\n    \n    pop  { r1, r2, r3, r4, r5, r6, r7 } \n    pop  { pc }\n    nop\n    \n    " );
#endif
}

// reads identification bytes (id->0,1 or 5 see datasheet)
unsigned int
flash_get_ident ( int id )
{
    unsigned int ret = 0;
    unsigned int ( *code ) ( void ) = ( unsigned int ( * )( void ) ) tempcode + 1;

    memcpy ( tempcode - 1, flash_read_ident - 1, 0x80 );

    int_disable (  );
#ifdef ARM
    asm volatile ( "push { %2 }\nmov lr, pc\n bx %1\n mov %0, r0":"=r" ( ret ):"r" ( code ), "r" ( id ) );
#endif
    int_enable (  );

    return ret;
}

// erases the block of the given address
unsigned char
flash_erase ( void *dest )
{
    unsigned int ret = 0;
    unsigned int ( *code ) ( void ) = ( unsigned int ( * )( void ) ) tempcode + 1;

    memcpy ( tempcode - 1, flash_clear_block - 1, 0x80 );

    int_disable (  );
    flash_vpp ( 1 );
#ifdef ARM
    asm volatile ( "push { %2 }\nmov lr, pc\n bx %1\n mov %0, r0":"=r" ( ret ):"r" ( code ), "r" ( dest ) );
#endif
    flash_vpp ( 0 );
    int_enable (  );

    return ret;
}

// writes the given RAM block to flash
unsigned char
flash_write_ram ( void *dest, void *src, unsigned int length )
{
    unsigned char ret = 0;
    unsigned int ( *code ) ( void ) = ( unsigned int ( * )( void ) ) tempcode + 1;

    memcpy ( tempcode - 1, flash_write_block - 1, 0x80 );

    if ( length & 1 )
        return 0;

    int_disable (  );
    flash_vpp ( 1 );
#ifdef ARM
    asm volatile ( "push { %4 }\npush { %3 }\npush { %2 }\nmov lr, pc\n bx %1\n mov %0, r0":"=r" ( ret ):"r" ( code ), "r" ( dest ), "r" ( src ), "r" ( length ) );
#endif
    flash_vpp ( 0 );
    int_enable (  );

    return ret;
}

// flashes the given block
unsigned char
flash_write ( void *dest, void *src, unsigned int length )
{
    unsigned char ret = 0;
    unsigned char *buf = 0;

    if ( ( unsigned int ) src > 0x00200000 && ( unsigned int ) src < 0x00400000 )
    {
        //
        // copy to ram here and flash partially
        //
        // flashing from flash addresses not possible yet
        buf = ( unsigned char * ) malloc ( length );
        if ( !buf )
            return 0xFF;
        memcpy ( buf, src, length );
        ret = flash_write_ram ( dest, buf, length );
        free ( buf );
        return ret;
    }
    else
        return flash_write_ram ( dest, src, length );

}
