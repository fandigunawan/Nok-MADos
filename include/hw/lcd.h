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

#ifndef __LCD_H
#define __LCD_H


#define LCD_BUFLEN    (84*48)/8
typedef struct
{
    unsigned char x, y;
    const unsigned char *data;
}
bitmap_t;

#define ani_t bitmap_t*

typedef struct
{
    unsigned char const ( *data )[128][22];
    unsigned char *name;
    unsigned int ( *size )[128][2];
    unsigned char space;
    unsigned char w;
    unsigned char h;
}
font;

unsigned char *lcd_getbuf ( void );
unsigned int lcd_getbufsize ( void );
void volatile lcd_to_screen ( void );
void volatile lcd_screen_to_io ( void );
void volatile lcd_clr ( void );
void lcd_type_text ( int x, int y, int speed, unsigned char *text, int sc );
void lcd_type_text_2 ( int x, int y, int speed, unsigned char *text, int sc );
void volatile lcd_fill ( unsigned char c );
void volatile lcd_fill_2 ( unsigned char c, unsigned char d );
void inline lcd_wait_ready ( void );
void volatile lcd_write_data ( unsigned long byte );
void volatile lcd_write_cmd ( unsigned long byte );
void volatile lcd_genio_init ( void );
void volatile lcd_reset ( void );
void lcd_set_contrast ( unsigned char c );
/**
 * Set LCD mode
 * mode is one of LCD_MODE_BLANK, LCD_MODE_NORMAL, LCD_MODE_INVERSE, LCD_MODE_ALLON
 */
void lcd_set_mode ( int mode );
void lcd_fade_in ( int delay );
void lcd_fade_out ( int delay );
void volatile lcd_init ( void );
unsigned char volatile lcd_render_char ( int x, int y, unsigned char c, int sc );
unsigned char volatile lcd_get_char_width ( unsigned char c );
void lcd_render_text ( int x, int y, unsigned char *text, int sc );
void lcd_render_text_ml ( int x, int y, unsigned char *text, int sc, int align );
void lcd_render_bitmap ( int px, int py, int sx, int sy, unsigned char *b, int sc );
void lcd_set_pixel ( int x, int y, int sc );
void lcd_draw_line ( int x1, int y1, int x2, int y2, int sc );
void lcd_fontsettings ( int num );
void lcd_draw_bitmap ( int xpos, int ypos, bitmap_t * bitmap );
void lcd_draw_bitmap_x ( int xpos, int ypos, bitmap_t * bitmap, char target );

#define FONT_CONDENSED 0x80
#define FONT_DYNAMIC   0x40

#define FONT_SIZED 1
#define FONT_SYSTEM 0




#define AL_RIGHT 0x01
#define AL_CENTER 0x02
#define AL_BOTTOM 0x04

#define T_LCD_BUF  0
#define T_ANI_BUF  1
#define T_ANI_MASK 2

/** lcd_set_mode constants */
#define LCD_MODE_BLANK 		0x0
#define LCD_MODE_ALLON		0x1
#define LCD_MODE_NORMAL		0x4
#define LCD_MODE_INVERSE	0x5

#endif
