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


#define NONE 0x01
#define FIXED_WALL 0x02
#define BREAK_ABLE_WALL 0x03
#define STRONG_BREAK_ABLE_WALL 0x04

#define FIRE_1 0x11
#define FIRE_2 0x12
#define FIRE_3 0x13
#define FIRE_4 0x14
#define FIRE_5 0x15

#define PLAYER_START 0x21
#define MONSTER_1_START 0x22
#define MONSTER_2_START 0x23
#define MONSTER_3_START 0x24
#define MONSTER_4_START 0x25
// don't know if we need this define stuff :)

typedef struct
{
    signed int total_x;
    signed int total_y;         //maybe map_coord will be better or use it to smooth all :)
    unsigned int time_last_movement;
    unsigned char bombs;
    unsigned char bomb_strenght;
    unsigned char lives;
}
bomberman_player_t;

typedef struct
{
    signed int total_x;
    signed int total_y;
    signed char map_x;
    signed char map_y;
    // still have to decide, which to take...
}
bomberman_screen_t;
// still have to decide whether to use screen_t

typedef struct
{
    signed int total_x;
    signed int total_y;
    unsigned int time_last_movement;
    unsigned char direction;
}
bomberman_monster_t;

typedef struct
{
    signed char map_x;
    signed char map_y;
    unsigned char state;        // 0 unused, 1 - x bmps
    unsigned int time_last_state_chg;
}
bomberman_fire_t;

typedef struct
{
    signed char map_x;
    signed char map_y;
    unsigned char bomb_used;
    unsigned int time_bomb_layed;
}
bomberman_bomb_t;



void bomberman_main ( void );
//void bomberman_get_player_start ( unsigned char map, unsigned int *total_x, unsigned int *total_y );
//void bomberman_totalxy_to_mapxy ( unsigned int total_x, unsigned int total_y, unsigned char *map_x, unsigned char *map_y );
//void bomberman_calculate_new_player_pos ( unsigned char map, unsigned char key, bomberman_player_t *player );
//void bomberman_draw ( unsigned char map, bomberman_player_t *player );
void bomberman_start ( void );
