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

void snake_vibra_thread ( void );
void snake_sound_thread ( void );
void snake_chg_level ( void );
void snake_chg_laby ( void );
void snake_draw ( unsigned char *posx, unsigned char *posy, unsigned char *applez_x, unsigned char *applez_y );
unsigned char snake_check_apple ( unsigned char x, unsigned char y, unsigned char *applez_x, unsigned char *applez_y, unsigned char nocheck );
void snake_kill_apple ( unsigned char x, unsigned char y, unsigned char *applez_x, unsigned char *applez_y );
unsigned char snake_check_snake ( unsigned char x, unsigned char y, unsigned char *posx, unsigned char *posy, unsigned char nocheck );
void snake_generate_apple ( unsigned char *posx, unsigned char *posy, unsigned char *applez_x, unsigned char *applez_y );
void snake_game_over ( unsigned int points );
void snake_start ( void );
void snake_main ( void );
