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

#ifndef LOADER
#include "hw/lcd.h"
#include "hw/kpd.h"
#include "hw/ccont.h"
#include "core/lib.h"
#include "apps/bomberman.h"

#define MAX_STRENGHT 2
#define MAX_BOMBS 3


const unsigned char maps[1][24][24] = {
    {
     "FFFFFFFFFFFFFFFFFFFFFFFF",
     "F                      F",
     "F  FFFFFFFFFFFFFF      F",
     "F      P        F      F",
     "F       FFFFFFF F      F",
     "F       F     FFF      F",
     "F                      F",
     "F   FFFFFFFFFF         F",
     "F       F        f     F",
     "F       F              F",
     "F       FFFF           F",
     "F                      F",
     "F                      F",
     "F                      F",
     "F    ffffff    F       F",
     "F              F       F",
     "F              F       F",
     "F              F       F",
     "F    FFFFF  FFFF       F",
     "F      F    F          F",
     "F      F    F  F       F",
     "F      F    FFFF       F",
     "F                      F",
     "FFFFFFFFFFFFFFFFFFFFFFFF",
     },
};

unsigned char *player_bmp = "  XX  " " X  X " "X    X" "X XX X" " X  X " "  XX  ";

unsigned char *fixed_wall_bmp = " XXXX " "XXXXXX" "XXXXXX" "XXXXXX" "XXXXXX" " XXXX ";

unsigned char *breakable_wall_bmp = "X X X " " X X X" "X X X " " X X X" "X X X " " X X X";

unsigned char *bomb_bmp = "    XX" "  XX  " " XXXX " "XXXXXX" " XXXX " "  XX  ";

unsigned char *fire_1_bmp = "   X  " " X  X " " X X  " " X  X " " XXXX " "   X  ";


void
bomberman_main ( void )
{

    bomberman_start (  );

}

void
bomberman_get_player_start ( unsigned char map, signed int *total_x, signed int *total_y )
{
    unsigned char x, y;

    for ( x = 0; x < 24; x++ )
    {
        for ( y = 0; y < 24; y++ )
        {
            if ( maps[map][y][x] == 'P' )
            {
                *total_x = x * 6;
                *total_y = y * 6;
            }
        }
    }

    return;
}

bomberman_totalxy_to_mapxy ( signed int total_x, signed int total_y, signed char *map_x, signed char *map_y )
{
    unsigned char x, y;

    x = lib_div ( total_x, 6 );
    y = lib_div ( total_y, 6 );

/*	if ( lib_mod ( total_x, 6 ) > 2 && total_x >= 0 ) x++;
	if ( lib_mod ( total_y, 6 ) > 2 && total_y >= 0 ) y++;

	if ( lib_mod ( total_x, 6 ) > 2 && total_x < 0 ) x--;
	if ( lib_mod ( total_y, 6 ) > 2 && total_y < 0 ) y--;*/

    *map_x = x;
    *map_y = y;

    return;
}

// return: 0 no wall or out of map; 1 wall; 2 breakable wall;
unsigned char
bomberman_check_wall_mapxy ( unsigned char map, signed char map_x, signed char map_y )
{

    unsigned char x, y;

    if ( map_x < 0 || map_y < 0 || map_x > 23 || map_y > 23 )
        return 0;

    /*
     * for ( x = 0; x < 24; x++ )
     * {
     * for ( y = 0; y < 24; y++ )
     * {
     */
    if ( maps[map][map_y][map_x] == 'F' )
        return 1;
    if ( maps[map][map_y][map_x] == 'f' )
        return 2;
    /*
     * }
     * }
     */

    return 0;

}

// return: 0 no bomb, 1 bomb
unsigned char
bomberman_check_bomb_mapxy ( signed char map_x, signed char map_y, bomberman_bomb_t * bombs )
{

    unsigned char c;

    for ( c = 0; c < MAX_BOMBS; c++ )
    {
        if ( bombs[c].map_x == map_x && bombs[c].map_y == map_y && bombs[c].bomb_used == 1 )
            return 1;
    }

    return 0;

}

// return: 0 no fire, 1 fire
unsigned char
bomberman_check_fire_mapxy ( signed char map_x, signed char map_y, bomberman_fire_t * fires )
{

    unsigned char c;

    for ( c = 0; c < MAX_BOMBS * ( MAX_STRENGHT * 4 + 1 ); c++ )
    {
        if ( fires[c].map_x == map_x && fires[c].map_y == map_y && fires[c].state != 0 )
            return 1;
    }

    return 0;

}

void
bomberman_calculate_new_player_pos ( unsigned char map, unsigned char key, bomberman_player_t * player, bomberman_bomb_t * bombs )
{

    signed int x = player->total_x;
    signed int y = player->total_y;

    signed char map_x, map_y;

    if ( lib_abs ( lib_get_time (  ) - player->time_last_movement ) < 50 )
        return;

    //bomberman_totalxy_to_mapxy ( x, y, &map_x, &map_y );

    switch ( key )
    {
        case 0x2:
            /*
             * if ( bomberman_check_wall_mapxy ( map, map_x, map_y ) == 0 )
             */ y--;
            break;
        case 0x4:
            /*
             * if ( bomberman_check_wall_mapxy ( map, map_x, map_y ) == 0 )
             */ x--;
            break;
        case 0x6:
            /*
             * if ( bomberman_check_wall_mapxy ( map, map_x+1, map_y ) == 0 )
             */ x++;
            break;
        case 0x8:
            /*
             * if ( bomberman_check_wall_mapxy ( map, map_x, map_y+1 ) == 0 )
             */ y++;
            break;
        default:
            break;
    }

    bomberman_totalxy_to_mapxy ( x, y, &map_x, &map_y );

    if ( bomberman_check_wall_mapxy ( map, map_x, map_y ) == 0 /*&& bomberman_check_bomb_mapxy ( map_x, map_y, bombs ) == 0 */  )
    {

        //check map_x, map_y  - bombs, walls done - fire needed

        player->time_last_movement = lib_get_time (  );
        player->total_x = x;    // later map_x * 6 <- ne doch net
        player->total_y = y;    // --- " ---

    }

    return;

}

void
bomberman_draw ( unsigned char map, bomberman_player_t * player, bomberman_bomb_t * bombs, bomberman_fire_t * fires )
{
    signed char first_map_x_to_draw, first_map_y_to_draw, player_map_x, player_map_y, x, y, a_pos_map_x, a_pos_map_y, x_offset, y_offset;
    unsigned char buf[10], c;

    //bomberman_totalxy_to_mapxy ( player->total_x, player->total_y, &player_map_x, &player_map_y );
    //bomberman_totalxy_to_mapxy ( player->total_x - 4*6, player->total_y - 4*6, &first_map_x_to_draw, &first_map_y_to_draw );

    player_map_x = lib_div ( player->total_x, 6 );
    player_map_y = lib_div ( player->total_y, 6 );

    x_offset = lib_mod ( player->total_x, 6 );
    y_offset = lib_mod ( player->total_y, 6 );

    first_map_x_to_draw = player_map_x - 4;
    first_map_y_to_draw = player_map_y - 4;

    /*
     * if ( player_x > 3 ) first_map_x_to_draw = player_x - 3;
     * else first_map_x_to_draw = player_x;
     * if ( player_y > 3 ) first_map_y_to_draw = player_y - 3;
     * else first_map_y_to_draw = player_y;
     */

    /*
     * first_map_x_to_draw = 2;
     * first_map_y_to_draw = 2;
     */

    lcd_clr (  );

    /*
     * lib_dtoa ( buf, player_map_x, 3, 0 );
     * lcd_render_text ( 0, 0, buf, 1 );
     * lib_dtoa ( buf, player_map_y, 3, 0 );
     * lcd_render_text ( 0, 8, buf, 1 );
     */

    for ( x = 0; x < 9; x++ )
    {
        for ( y = 0; y < 9; y++ )
        {
            a_pos_map_x = first_map_x_to_draw + x;
            a_pos_map_y = first_map_y_to_draw + y;

            /*
             * if ( maps[map][a_pos_map_y][a_pos_map_x] == 'F' && a_pos_map_x > -1 && a_pos_map_y > -1 && a_pos_map_x < 24 && a_pos_map_y < 24 )
             * lcd_render_bitmap ( x*6, y*6, 6, 6, fixed_wall_bmp, 1 );
             */

            // drawing walls
            switch ( bomberman_check_wall_mapxy ( map, a_pos_map_x, a_pos_map_y ) )
            {

                case 0x0:
                    break;
                case 0x1:
                    lcd_render_bitmap ( x * 6 - x_offset, y * 6 - y_offset, 6, 6, fixed_wall_bmp, 1 );
                    break;
                case 0x2:
                    lcd_render_bitmap ( x * 6 - x_offset, y * 6 - y_offset, 6, 6, breakable_wall_bmp, 1 );
                    break;
                default:
                    break;
            }

            // drawing bombs
            for ( c = 0; c < MAX_BOMBS; c++ )
            {
                if ( bombs[c].bomb_used == 1 && bombs[c].map_x == a_pos_map_x && bombs[c].map_y == a_pos_map_y )
                    lcd_render_bitmap ( x * 6 - x_offset, y * 6 - y_offset, 6, 6, bomb_bmp, 1 );
            }

            // drawing fires
            for ( c = 0; c < MAX_BOMBS * ( MAX_STRENGHT * 4 + 1 ); c++ )
            {
                if ( fires[c].state != 0 && fires[c].map_x == a_pos_map_x && fires[c].map_y == a_pos_map_y )
                    lcd_render_bitmap ( x * 6 - x_offset, y * 6 - y_offset, 6, 6, fire_1_bmp, 1 );
            }

            /*
             * if ( maps[map][a_pos_map_y][a_pos_map_x] == 'F')
             * lcd_render_bitmap ( x*6, y*6, 6, 6, fixed_wall_bmp, 1 );
             */

            if ( ( player_map_x == a_pos_map_x ) && ( player_map_y == a_pos_map_y ) )
                lcd_render_bitmap ( x * 6, y * 6, 6, 6, player_bmp, 1 );
        }
    }

    lcd_draw_rect ( 8 * 6, 0, 8 * 6 + 2, 47, 1 );

    // lcd_render_bitmap ( player->total_x - first_map_x_to_draw * 6, player->total_y - first_map_y_to_draw * 6, 6, 6, player_bmp, 1 );
    //lcd_render_bitmap ( player_map_x - first_map_x_to_draw * 6, player_map_y - first_map_y_to_draw * 6, 6, 6, player_bmp, 1 );
    //wieder ersetzen durhc player_map_x - ne doch auch net - mal schaun

    lcd_to_screen (  );

    return;
}

void
bomberman_add_new_fires ( unsigned char map, signed char map_x, signed char map_y, bomberman_player_t * player, bomberman_bomb_t * bombs, bomberman_fire_t * fires )
{
    unsigned char c, fires_added = 0, fires_to_add = MAX_STRENGHT * 4, direction = 0;
    signed char map_x_2_check, map_y_2_check;
    unsigned int i = 0, time_now = lib_get_time (  );

    /*
     * while ( fires_added < fires_to_add )
     * {
     * if ( fires[i].state == 0 )
     * {
     * fires[i].state = 1;
     * 
     * }
     */

    for ( direction = 0; direction < 5; direction++ )
    {

        map_x_2_check = map_x;
        map_y_2_check = map_y;

        for ( c = 0; c < MAX_STRENGHT; c++ )
        {
            while ( fires[i].state != 0 )
                i++;

            switch ( direction )
            {
                case 0x0:      //up
                    map_y_2_check--;
                    break;
                case 0x1:      //left
                    map_x_2_check--;
                    break;
                case 0x2:      //down
                    map_x_2_check++;
                    break;

                case 0x3:      //rigth
                    map_y_2_check++;
                    break;
                case 0x4:      //middle
                    break;
            }

            // bomberman_check_bomb_mapxy ( map_x_2_check, map_y_2_check, bombs ) == 0 check than add
            if ( bomberman_check_wall_mapxy ( map, map_x_2_check, map_y_2_check ) == 0 && bomberman_check_fire_mapxy ( map_x_2_check, map_y_2_check, fires ) == 0 )
            {
                fires[i].state = 1;
                fires[i].map_x = map_x_2_check;
                fires[i].map_y = map_y_2_check;
                fires[i].time_last_state_chg = time_now;

            }
            else
                break;

            //if (
            //check all here, 

        }

    }


    return;
}

void
bomberman_calculate_fires ( bomberman_fire_t * fires )
{
    unsigned int i, time_now;

    time_now = lib_get_time (  );

    for ( i = 0; i < MAX_BOMBS * ( MAX_STRENGHT * 4 + 1 ); i++ )
    {
        if ( lib_abs ( time_now - fires[i].time_last_state_chg ) > 330 && fires[i].state != 0 )
        {
            if ( fires[i].state < 10 )
                fires[i].state++;
            else
                fires[i].state = 0;
        }
    }

    return;

}

void
bomberman_calculate_bombs ( unsigned char map, unsigned char key, bomberman_player_t * player, bomberman_bomb_t * bombs, bomberman_fire_t * fires )
{

    unsigned char c;
    char player_map_x, player_map_y;

    unsigned int time_now = lib_get_time (  );

    bomberman_totalxy_to_mapxy ( player->total_x, player->total_y, &player_map_x, &player_map_y );

    if ( key == 0x5 )
    {
        for ( c = 0; c < MAX_BOMBS; c++ )
        {
            if ( bombs[c].bomb_used == 0 && bomberman_check_bomb_mapxy ( player_map_x, player_map_y, bombs ) == 0 )
            {
                //if ( bomberman_check_bomb_mapxy ( player_map_x, player_map_y, bombs ) == 0 )
                //{
                bombs[c].map_x = player_map_x;
                bombs[c].map_y = player_map_y;
                bombs[c].time_bomb_layed = time_now;
                bombs[c].bomb_used = 1;
                break;
                //}
            }
        }
    }

    for ( c = 0; c < MAX_BOMBS; c++ )
    {
        if ( ( lib_abs ( time_now - bombs[c].time_bomb_layed ) > 3000 && bombs[c].bomb_used == 1 ) || bomberman_check_fire_mapxy ( bombs[c].map_x, bombs[c].map_y, fires ) == 1 )
        {
            bombs[c].bomb_used = 0;
            bomberman_add_new_fires ( map, bombs[c].map_x, bombs[c].map_y, player, bombs, fires );

        }

        /*
         * if ( bomberman_check_fire_mapxy ( bombs[c].map_x, bombs[c].map_y, fires ) == 1 )
         * {
         * bombs[c].bomb_used = 0;
         * bomberman_add_new_fires ( map, bombs[c].map_x, bombs[c].map_y, player, bombs, fires );
         * 
         * }
         */
    }

    return;

}

void
bomberman_start ( void )
{

    unsigned char key, i;

    bomberman_player_t player;
    bomberman_bomb_t bombs[MAX_BOMBS];

    bomberman_fire_t fires[MAX_BOMBS * ( MAX_STRENGHT * 4 + 1 )];

    /*
     * bombs[0].bomb_used = 0;
     * bombs[1].bomb_used = 0;
     * bombs[2].bomb_used = 0;
     */

    for ( i = 0; i < MAX_BOMBS; i++ )
    {
        bombs[i].bomb_used = 0;
    }

    for ( i = 0; i < MAX_BOMBS * ( MAX_STRENGHT * 4 + 1 ); i++ )
    {
        fires[i].state = 0;
    }

    bomberman_screen_t screen;  // not really needed

    kpd_wait_release (  );


    player.time_last_movement = lib_get_time (  );
    player.bombs = 3;

    bomberman_get_player_start ( 0, &player.total_x, &player.total_y );
    screen.total_x = player.total_x - 4 * 6;
    screen.total_y = player.total_y - 4 * 6;

    do
    {

        key = kpd_getkey (  );

        bomberman_calculate_new_player_pos ( 0, key, &player, bombs );
        bomberman_calculate_bombs ( 0, key, &player, bombs, fires );
        bomberman_calculate_fires ( fires );

        // checking routines... monster, fire etc.
        // calc monsters, fires ...

        bomberman_draw ( 0, &player, bombs, fires );

    }
    while ( key != KPD_CANCEL );

    kpd_wait_release (  );

}

#endif
