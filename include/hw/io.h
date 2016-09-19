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

#include <hw/ioports.h>

volatile inline unsigned char io_read ( unsigned long io );
volatile inline unsigned short io_read_word ( unsigned long io );
volatile inline unsigned int io_read_dword ( unsigned long io );
volatile inline void io_set ( unsigned long io, unsigned char val );
volatile inline void io_set_word ( unsigned long io, unsigned short val );
volatile inline void io_set_dword ( unsigned long io, unsigned int val );
volatile inline void io_wait ( unsigned long io, unsigned long bit );
volatile inline void io_set_bit ( unsigned long io, unsigned long mask );
volatile inline void io_clr_bit ( unsigned long io, unsigned long mask );

extern volatile unsigned short _dsp[];
extern volatile unsigned char _io[];
extern volatile unsigned short _dspif[];
extern volatile unsigned char _mcuif[];


#ifdef XX
#define _io_clr_bit(p,v)  ((*(volatile unsigned char *)  &_io[p]) &= (~v))
#define _io_set_bit(p,v)  ((*(volatile unsigned char *)  &_io[p]) |= (v))
#define _io_set(p,v)      ((*(volatile unsigned char *)  &_io[p])  = (v))
#define _io_read(p)        (*(volatile unsigned char *)  &_io[p])
#define _io_read_word(p)   (*(volatile unsigned short *) &_io[p])
#define _io_set_word(p,v) ((*(volatile unsigned short *) &_io[p])  = (v))
#define _io_wait(p,v)     io_wait (0x00020000+p,v)
#else
#define _io_clr_bit(p,v)  io_clr_bit(0x00020000+p,v)
#define _io_set_bit(p,v)  io_set_bit(0x00020000+p,v)
#define _io_set(p,v)      io_set(0x00020000+p,v)
#define _io_read(p)       io_read(0x00020000+p)
#define _io_read_word(p)  io_read_word(0x00020000+p)
#define _io_set_word(p,v) io_set_word(0x00020000+p,v)
#define _io_wait(p,v)     io_wait (0x00020000+p,v)
#endif

#ifdef ARM
// (g3gg0) THIS IS NOT CORRECT 
//#define _io_wait(p,v)     while ( _io_read(p)&v != v ) usleep(1); 
#else
#undef _io_wait
#define _io_wait(p,v)
#endif
