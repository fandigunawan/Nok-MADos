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


#define FIQ_COUNT	9
#define IRQ_COUNT	9

/* Constants for "type" */


/* Interrupt IDs */
#define IRQ_KEYBOARD	0
#define IRQ_CCONTINT	2
#define IRQ_SLEEP	3
#define IRQ_DSP		4

#define FIQ_MDIRCV	0
#define FIQ_MDISND	1
#define FIQ_MBUSRX	2
#define FIQ_MBUSTIM	3           /* triggers 423.1 times per second */
#define FIQ_PTIMER	4
#define FIQ_SIMUART	6
#define FIQ_SIMCARDDETX	7



void irq_init ( void );
void int_disable ( void );
void int_enable ( void );
