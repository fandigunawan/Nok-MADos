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


int ui_getnumber ( char *ptext, unsigned char max_length, unsigned char min_length );
void ui_gettext ( char *ptext, unsigned char max_length, char *output, unsigned char ui_type );
void ui_draw_scrolltext ( char *ptext );
unsigned char ui_dialog_box ( char *ptext, char **buttons );

#define UI_ALIGN_LEFT   0x00
#define UI_ALIGN_RIGHT  0x01
#define UI_ALIGN_CENTER 0x02

#define UI_TYPE_UPPERCASE 0x01
#define UI_TYPE_LOWERCASE 0x02
#define UI_TYPE_NUMBER    0x04
#define UI_TYPE_HEX       0x08
#define UI_TYPE_TEXT      UI_TYPE_LOWERCASE | UI_TYPE_UPPERCASE
#define UI_TYPE_ALL       UI_TYPE_LOWERCASE | UI_TYPE_UPPERCASE | UI_TYPE_NUMBER
//#define UI_TYPE_HEX   UI_TYPE_NUMBER | UI_TYPE_UPPERCASE 
