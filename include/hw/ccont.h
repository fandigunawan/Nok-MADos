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


void ccont_init ( void );
int ccont_test ( void );
void ccont_write ( unsigned char reg, unsigned char byte );
unsigned char ccont_read ( unsigned char reg );
void ccont_reset_wdt ( void );
void ccont_disable_wdt ( void );
void ccont_poweroff ( void );
void ccont_set_chargemode ( unsigned char speed );
void ccont_set_charger ( int state );
void ccont_set_adcap ( int state );
void ccont_set_adsrc ( int src );
unsigned int ccont_get_adval ( void );
unsigned int ccont_read_adval ( int src );
unsigned char ccont_get_min ( void );
unsigned char ccont_get_hr ( void );
unsigned char ccont_get_day ( void );

#define CCONT_VSEL_3V 0
#define CCONT_VSEL_5V 1
