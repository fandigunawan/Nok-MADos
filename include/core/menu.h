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

#ifndef __MENU_H
#define __MENU_H

#include <hw/lcd.h>

#define MENU_CALLBACK(p)       int p ( int cmd, int val )
#define MENU_ONLY_SELECT       if ( cmd != MENU_SELECT ) return 0;
#define MENU_SCROLL_INIT(dly)  static int scroll_dly = dly, scroll_pos = 0, scroll_cnt = dly, scroll_dir = 0;\
	       unsigned char *scroll_str = NULL, *scroll_buf = NULL;
#define MENU_SCROLL_RESET      scroll_pos = 0;\
			       scroll_cnt = scroll_dly;
#define MENU_SCROLL(p)  scroll_buf = (unsigned char *) malloc ( strlen ( p ) + 10 );\
		sprintf ( scroll_buf, "  %s  ", p );\
		if ( strlen ( scroll_buf )>= 13 )\
		{\
		    scroll_str = (unsigned char*) malloc ( 20 );\
        	    if ( (scroll_pos >= strlen ( scroll_buf ) - 13 && !scroll_dir) || (!scroll_pos && scroll_dir) )\
		    {\
			if ( scroll_dir )\
			    scroll_dir = 0;\
			else\
			    scroll_dir = 1;\
		    }\
		    memcpy ( scroll_str, ( unsigned char * ) ( ( unsigned long ) ( scroll_buf ) + scroll_pos ), 13 );\
        	    scroll_str[13] = '\n';\
        	    scroll_str[14] = 0x00;\
		    if ( !(scroll_cnt--) )\
		    {\
			scroll_cnt = scroll_dly;\
			if ( !scroll_dir )\
			    scroll_pos++;\
			else \
			    scroll_pos--;\
		    }\
            	    menu_disp ( scroll_str );\
		    free ( scroll_str );\
		}\
		else\
            	    menu_disp ( scroll_buf );\
		free ( scroll_buf );\


#define MENU_SELECT   0x00
#define MENU_DRAW     0x01
#define MENU_REDRAW   0x02
#define MENU_UNDRAW   0x03
#define MENU_GETSTATE 0x04

#define MENU_EXIT     0x08

#define MENU_T_BMAP   0x01
#define MENU_T_LIST   0x02
#define MENU_T_STATE  0x03
#define MENU_T_FIELD  0x04

#define MENU_T_EXIT   0x40


typedef struct
{
    unsigned char type;
    unsigned char num;
    int ( *function ) ( int cmd, int val );
    bitmap_t *bmp;
    unsigned char *text;
}
menupoint;

int menu_show ( menupoint * menu );

unsigned char menu_main ( char **entries, int presel );
void menu_print ( char **entries, int num, int presel, int first, int baroffs, int bars, int bare );

#endif
