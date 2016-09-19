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

#ifndef _ARM_INC
#define _ARM_INC

//#define DEBUG_PTT_OFF

#define SETTINGS_START_ADDRESS  ((u8*)0x38000)

#define MS_100                  20  // 100 ms

#define DIR_RX                  0
#define DIR_TX                  1

#define BEEP_SUBSYSTEM          1
#define ST2_SUBSYSTEM           2
#define MS_SUBSYSTEM            4
#define PRG_SUBSYSTEM           8

#define RCMD_PA_ON              1
#define RCMD_PA_OFF             2
#define RCMD_PTT_ON             3
#define RCMD_PTT_OFF            4
#define RCMD_DISP_ACQUIRE       5
#define RCMD_DISP_RELEASE       6
#define RCMD_DISP_SYM           7
#define RCMD_DISP_CLR           8
#define RCMD_CH_SET             9

#define RSTATUS_PA              1
#define RSTATUS_PTT             2
#define RSTATUS_DISP            3

s16 rstatus ( s16 cmd );
void rcmd ( int cmd, int subsystem, char *p );
void out_sym ( uchar n );

void codec_init ( void );
void codec_set_direction ( int dir );

void delay ( unsigned int n );
void delay_1 ( unsigned int n );
void delay_2 ( unsigned int n );
void delay_3 ( unsigned int n );
void delay_4 ( unsigned int n );
void delay_5 ( unsigned int n );
void delay_6 ( unsigned int n );
void delay_7 ( unsigned int n );
void delay_8 ( unsigned int n );
void delay_9 ( unsigned int n );
void delay_10 ( unsigned int n );
void delay_11 ( unsigned int n );
void delay_12 ( unsigned int n );
void delay_13 ( unsigned int n );
void delay_14 ( unsigned int n );
void delay_15 ( unsigned int n );
void delay_16 ( unsigned int n );
void delay_17 ( unsigned int n );
void delay_18 ( unsigned int n );
void delay_19 ( unsigned int n );
void delay_20 ( unsigned int n );
void delay_21 ( unsigned int n );
void delay_22 ( unsigned int n );
void delay_23 ( unsigned int n );
void delay_24 ( unsigned int n );
void delay_25 ( unsigned int n );
void delay_26 ( unsigned int n );
void delay_27 ( unsigned int n );
void delay_28 ( unsigned int n );
void delay_29 ( unsigned int n );
void delay_30 ( unsigned int n );
void delay_ms ( unsigned int n );
void fatal_error ( void );

extern const char buttons_translate_tbl[16];

void radio_transmit_task ( void );
int radio_get_new_event ( void );
void radio_tmr_task ( void );

#endif //_ARM_INC
