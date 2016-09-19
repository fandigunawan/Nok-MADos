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

//initialize vibra
void
vibra_init ( void )
{
    _io_set ( IO_PUP_CTRL, _io_read ( IO_PUP_CTRL ) | 0x10 );
}

//sets the frequency of vibra - allowed decimal values: 0 - 31
void
vibra_setfreq ( unsigned char freq )
{
    _io_set ( IO_PUP_VIB, ( _io_read ( IO_PUP_VIB ) & 0xe0 ) | ( freq & 0x1f ) );
}

//sets the vibra mode - allowed values: 0(off) - 3
void
vibra_setmode ( unsigned char mode )
{
    _io_set ( IO_PUP_VIB, ( _io_read ( IO_PUP_VIB ) & 0x9f ) | ( ( mode << 5 ) & 0x60 ) );
}
