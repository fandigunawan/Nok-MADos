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

#ifndef WMX_MBUS
#define WMX_MBUS

#define MBUS_STOP	0
#define MBUS_TRANSMIT 	1
#define MBUS_RECEIVE 	2

#define MBUS_SPEED_9600		0
#define MBUS_SPEED_19200	1
#define MBUS_SPEED_57600	3
#define MBUS_SPEED_115200	4

/** Initialize mbus */
void mbus_init ( int speed );

/** Set MBus mode to transmit or receive 
    Make sure there is a byte in the transmit buffer before starting transmit 
*/
void mbus_mode ( int mode );    /* MBUS_... */

/**
 * Initialize MBUS driver and hardware
 */
void mbus_start ( int speed );

/* TEST */
#define MBUS_QUEUESIZE 256

/**
 * Transmit a block of data over MBUS line. Blocks.
 */
int mbus_transmit ( unsigned char *data, int size );

int mbus_receive ( unsigned char *address, int size );

#endif
