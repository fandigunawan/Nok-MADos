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



#define FLASH_STATUS_WSMS 0x80
#define FLASH_STATUS_ESS  0x40
#define FLASH_STATUS_ES   0x20
#define FLASH_STATUS_PS   0x10
#define FLASH_STATUS_VPPS 0x08
#define FLASH_STATUS_PSS  0x04
#define FLASH_STATUS_DPS  0x02
#define FLASH_STATUS_R    0x01



void flash_vpp ( unsigned int state );
unsigned int flash_get_ident ( int id );
unsigned char flash_erase ( void *dest );
unsigned char flash_write_ram ( void *dest, void *src, unsigned int length );
unsigned char flash_write ( void *dest, void *src, unsigned int length );
