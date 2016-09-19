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

int io_tmp;



volatile inline unsigned char
io_read ( unsigned long io )
{
    unsigned char val;
#ifdef ARM
    asm volatile ( "ldrb  %0, [%1,#0x00]":"=r" ( val ):"r" ( io ) );
#endif
    return val;
}

volatile inline unsigned short
io_read_word ( unsigned long io )
{
    unsigned short val;
#ifdef ARM
    asm volatile ( "ldrh  %0, [%1,#0x00]":"=r" ( val ):"r" ( io ) );
#endif
    return val;
}

volatile inline unsigned int
io_read_dword ( unsigned long io )
{
    unsigned int val;
#ifdef ARM
    asm volatile ( "ldr  %0, [%1,#0x00]":"=r" ( val ):"r" ( io ) );
#endif
    return val;
}

volatile inline void
io_set ( unsigned long io, unsigned char val )
{
#ifdef ARM
    asm volatile ( "strb  %0, [%1,#0x00]"::"r" ( val ), "r" ( io ) );
#endif
    return;
}

volatile inline void
io_set_word ( unsigned long io, unsigned short val )
{
#ifdef ARM
    asm volatile ( "strh  %0, [%1,#0x00]"::"r" ( val ), "r" ( io ) );
#endif
    return;
}

volatile inline void
io_set_dword ( unsigned long io, unsigned int val )
{
#ifdef ARM
    asm volatile ( "str  %0, [%1,#0x00]"::"r" ( val ), "r" ( io ) );
#endif
    return;
}

volatile inline void
io_wait ( unsigned long io, unsigned long bit )
{
#ifdef ARM
    unsigned int wait = 0x000FFFFF;
    while ( wait-- && !( io_read ( io ) & bit ) )
        asm volatile ( "nop" );
#endif
}

volatile inline void
io_set_bit ( unsigned long io, unsigned long mask )
{
#ifdef ARM
    asm volatile ( "push { r3 }\nldrb  r3, [%0,#0x00]\norr  r3, %1\nstrb  r3, [%0,#0x00]\npop { r3 }"::"r" ( io ), "r" ( mask ) );

#endif
    return;
}

volatile inline void
io_clr_bit ( unsigned long io, unsigned long mask )
{
#ifdef ARM
    asm volatile ( "push { r3 }\nldrb  r3, [%0,#0x00]\norr  r3, %1\neor  r3, %1\nstrb  r3, [%0,#0x00]\npop { r3 }"::"r" ( io ), "r" ( mask ) );

#endif
    return;
}
