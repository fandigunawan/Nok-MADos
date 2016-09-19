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

void tetris_main ( void );
void tetris_sound_thread ( void );
void tetris_chg_shapes ( void );
void tetris_chg_design ( void );
void tetris_init_game ( void );
void tetris_loop ( void );
void tetris_drop_block ( void );
void tetris_show_score ( void );
void tetris_end_game ( void );
void tetris_left_proc ( void );
void tetris_right_proc ( void );
void tetris_anti_proc ( void );
void tetris_clock_proc ( void );
void tetris_fast_proc ( void );
void tetris_show_next ( void );
void tetris_print_shape ( int shape_no, int x, int y, int rot, int col );
void tetris_set1pixel ( int x, int y, int col );
void tetris_print_all_blocks ( void );


void tetris_define_shapes ( void );
void tetris_store_shape ( int shape_no, int xpos, int ypos, int rot );
void tetris_create_shape ( void );
int tetris_level ( void );
int tetris_block_can_drop ( int shape_no, int xpos, int ypos, int rot );
int tetris_block_can_left ( int shape_no, int xpos, int ypos, int rot );
int tetris_block_can_right ( int shape_no, int xpos, int ypos, int rot );
void tetris_remove_full_lines ( int y );
int tetris_check_rot ( int shape_no, int xpos, int ypos, int newrot );
