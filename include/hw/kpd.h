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


void kpd_init ( void );
void kpd_int_handler ( void );
unsigned char kpd_getkey ( void );
unsigned char kpd_get_second_key ( void );
unsigned char kpd_get_third_key ( void );
unsigned int kpd_getlast ( void );
unsigned char kpd_readkey ( void );
void kpd_wait_release_x ( int ms );
void kpd_wait_release ( void );
void kpd_wait_keypress_x ( int ms );
void kpd_wait_keypress ( void );
void kpd_buffer_clr ( void );
void kpd_mode ( unsigned char mode );

#define KPD_BUFSIZE    0x20

#define KPD_UPARROW    0x16
#define KPD_DWNARROW   0x13
#define KPD_CANCEL     0x21
#define KPD_SOFTBTN1   0x20
#define KPD_OFF        0x30

#define KPD_BUFFERED   0x00
#define KPD_UNBUFFERED 0x01
