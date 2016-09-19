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

#include <hw/kpd.h>
#include <core/lib.h>
#include <apps/tictactoe.h>
#include <core/bitmap.h>

unsigned int box[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned int used[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned int turn = 1;
unsigned int selected = 1;
unsigned int cursposx[] = { 1, 1, 1, 14, 14, 14, 27, 27, 27 };
unsigned int cursposy[] = { 1, 16, 31, 1, 16, 31, 1, 16, 31 };
unsigned int filled = 0;
unsigned int type = 1;





// Tic Tac Toe game by SpaceImpact33 and Yomanda and Crux



//types
//1 player vers pc
//2 player1 verses player2

void
checkwinsx (  )
{
    while ( 1 )
    {
        if ( filled > 8 )
        {
            break;
        }

        if ( box[1 - 1] == 1 & box[2 - 1] == 1 & box[3 - 1] == 1 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_xwins );
            lcd_to_screen (  );
            sleep ( 5 );
            break;
        }
        if ( box[4 - 1] == 1 & box[5 - 1] == 1 & box[6 - 1] == 1 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_xwins );
            lcd_to_screen (  );
            sleep ( 5 );
            break;
        }
        if ( box[7 - 1] == 1 & box[8 - 1] == 1 & box[9 - 1] == 1 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_xwins );
            lcd_to_screen (  );
            sleep ( 5 );
            break;
        }
        if ( box[1 - 1] == 1 & box[4 - 1] == 1 & box[7 - 1] == 1 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_xwins );
            lcd_to_screen (  );
            sleep ( 5 );
            break;
        }
        if ( box[2 - 1] == 1 & box[5 - 1] == 1 & box[8 - 1] == 1 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_xwins );
            lcd_to_screen (  );
            sleep ( 5 );
            break;
        }
        if ( box[3 - 1] == 1 & box[6 - 1] == 1 & box[9 - 1] == 1 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_xwins );
            lcd_to_screen (  );
            sleep ( 5 );
            break;
        }
        if ( box[1 - 1] == 1 & box[5 - 1] == 1 & box[9 - 1] == 1 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_xwins );
            lcd_to_screen (  );
            sleep ( 5 );
            break;
        }
        if ( box[3 - 1] == 1 & box[5 - 1] == 1 & box[7 - 1] == 1 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_xwins );
            lcd_to_screen (  );
            sleep ( 5 );
            break;
        }
        break;
    }
}
void
checkwinso (  )
{
    while ( 1 )
    {
        if ( filled > 8 )
        {
            break;
        }
        if ( box[1 - 1] == 2 & box[2 - 1] == 2 & box[3 - 1] == 2 )
        {
            lcd_draw_bitmap ( -1, -1, &bmp_owins );
            lcd_to_screen (  );
            sleep ( 5 );
            break;
        }
        if ( box[4 - 1] == 2 & box[5 - 1] == 2 & box[6 - 1] == 2 )
        {
            lcd_draw_bitmap ( -1, -1, &bmp_owins );
            lcd_to_screen (  );
            sleep ( 5 );
            break;
        }
        if ( box[7 - 1] == 2 & box[8 - 1] == 2 & box[9 - 1] == 2 )
        {

            lcd_draw_bitmap ( -1, -1, &bmp_owins );
            lcd_to_screen (  );
            sleep ( 5 );
            break;
        }
        if ( box[1 - 1] == 2 & box[4 - 1] == 2 & box[7 - 1] == 2 )
        {
            lcd_draw_bitmap ( -1, -1, &bmp_owins );
            lcd_to_screen (  );
            sleep ( 5 );
            break;
        }

        if ( box[2 - 1] == 2 & box[5 - 1] == 2 & box[8 - 1] == 2 )
        {
            lcd_draw_bitmap ( -1, -1, &bmp_owins );
            lcd_to_screen (  );
            sleep ( 5 );
            break;
        }
        if ( box[3 - 1] == 2 & box[6 - 1] == 2 & box[9 - 1] == 2 )
        {
            lcd_draw_bitmap ( -1, -1, &bmp_owins );
            lcd_to_screen (  );
            sleep ( 5 );
            break;
        }
        if ( box[1 - 1] == 2 & box[5 - 1] == 2 & box[9 - 1] == 2 )
        {
            lcd_draw_bitmap ( -1, -1, &bmp_owins );
            lcd_to_screen (  );
            sleep ( 5 );
            break;
        }
        if ( box[3 - 1] == 2 & box[5 - 1] == 2 & box[7 - 1] == 2 )
        {
            lcd_draw_bitmap ( -1, -1, &bmp_owins );
            lcd_to_screen (  );
            sleep ( 5 );
            break;
        }
        break;
    }
}


unsigned int
winthreeinarow (  )
{
    unsigned int naught = 1;
    while ( 1 )
    {
        if ( filled > 8 )
        {
            break;
        }

        /// horeozontal checks

        //1 # #
        if ( box[1 - 1] == naught & box[3 - 1] == naught & box[2 - 1] == 0 )
        {
            return 2 - 1;
            break;
        }
        //1  ##
        if ( box[2 - 1] == naught & box[3 - 1] == naught & box[1 - 1] == 0 )
        {
            return 1 - 1;
            break;
        }
        // 1 ##
        if ( box[1 - 1] == naught & box[2 - 1] == naught & box[3 - 1] == 0 )
        {
            return 3 - 1;
            break;
        }
        //1 # #
        if ( box[1 - 1] == naught & box[3 - 1] == naught & box[2 - 1] == 0 )
        {
            return 2 - 1;
            break;
        }
        //**************line 2***************
        //2  ##
        if ( box[4 - 1] == naught & box[5 - 1] == naught & box[6 - 1] == 0 )
        {
            return 6 - 1;
            break;
        }
        // 2 ##
        if ( box[4 - 1] == naught & box[6 - 1] == naught & box[5 - 1] == 0 )
        {
            return 5 - 1;
            break;
        }
        if ( box[5 - 1] == naught & box[6 - 1] == naught & box[4 - 1] == 0 )
        {
            return 4 - 1;
            break;
        }
        //****************line 3****************
        //2  ##
        if ( box[7 - 1] == naught & box[8 - 1] == naught & box[9 - 1] == 0 )
        {
            return 9 - 1;
            break;
        }
        // 2 ##
        if ( box[7 - 1] == naught & box[9 - 1] == naught & box[8 - 1] == 0 )
        {
            return 8 - 1;
            break;
        }
        if ( box[8 - 1] == naught & box[9 - 1] == naught & box[7 - 1] == 0 )
        {
            return 7 - 1;
            break;
        }
///############### vert checks ##################
//******************* line 1 *****************
        //2  ##
        if ( box[1 - 1] == naught & box[4 - 1] == naught & box[7 - 1] == 0 )
        {
            return 7 - 1;
            break;
        }
        // 2 ##
        if ( box[1 - 1] == naught & box[7 - 1] == naught & box[4 - 1] == 0 )
        {
            return 4 - 1;
            break;
        }
        if ( box[4 - 1] == naught & box[7 - 1] == naught & box[1 - 1] == 0 )
        {
            return 1 - 1;
            break;
        }
//******************* line 2 *****************
        //2  ##
        if ( box[2 - 1] == naught & box[5 - 1] == naught & box[8 - 1] == 0 )
        {
            return 8 - 1;
            break;
        }
        // 2 ##
        if ( box[2 - 1] == naught & box[8 - 1] == naught & box[5 - 1] == 0 )
        {
            return 5 - 1;
            break;
        }
        if ( box[5 - 1] == naught & box[8 - 1] == naught & box[2 - 1] == 0 )
        {
            return 2 - 1;
            break;
        }
//******************* line 3 *****************
        //2  ##
        if ( box[3 - 1] == naught & box[6 - 1] == naught & box[9 - 1] == 0 )
        {
            return 9 - 1;
            break;
        }
        // 2 ##
        if ( box[3 - 1] == naught & box[9 - 1] == naught & box[6 - 1] == 0 )
        {
            return 6 - 1;
            break;
        }
        if ( box[6 - 1] == naught & box[9 - 1] == naught & box[3 - 1] == 0 )
        {
            return 3 - 1;
            break;
        }
//#################### diagonals #################
        // **************** diagonal1 ************
        //2  ##
        if ( box[1 - 1] == naught & box[5 - 1] == naught & box[9 - 1] == 0 )
        {
            return 9 - 1;
            break;
        }
        // 2 ##
        if ( box[5 - 1] == naught & box[9 - 1] == naught & box[1 - 1] == 0 )
        {
            return 1 - 1;
            break;
        }
        if ( box[1 - 1] == naught & box[9 - 1] == naught & box[5 - 1] == 0 )
        {
            return 5 - 1;
            break;
        }
// **************** diagonal2 ************
        //2  ##
        if ( box[3 - 1] == naught & box[5 - 1] == naught & box[7 - 1] == 0 )
        {
            return 7 - 1;
            break;
        }
        // 2 ##
        if ( box[7 - 1] == naught & box[5 - 1] == naught & box[3 - 1] == 0 )
        {
            return 3 - 1;
            break;
        }

        if ( box[3 - 1] == naught & box[7 - 1] == naught & box[5 - 1] == 0 )
        {
            return 5 - 1;
            break;
        }

//############ahhhh all done :) #############
        break;
    }

}


unsigned int
blocktoinarow (  )
{
    unsigned int naught = 2;
    while ( 1 )
    {
        if ( filled > 8 )
        {
            break;
        }

        /// horeozontal checks

        //1 # #
        if ( box[1 - 1] == naught & box[3 - 1] == naught & box[2 - 1] == 0 )
        {
            return 2 - 1;
            break;
        }
        //1  ##
        if ( box[2 - 1] == naught & box[3 - 1] == naught & box[1 - 1] == 0 )
        {
            return 1 - 1;
            break;
        }
        // 1 ##
        if ( box[1 - 1] == naught & box[2 - 1] == naught & box[3 - 1] == 0 )
        {
            return 3 - 1;
            break;
        }
        //1 # #
        if ( box[1 - 1] == naught & box[3 - 1] == naught & box[2 - 1] == 0 )
        {
            return 2 - 1;
            break;
        }
        //**************line 2***************
        //2  ##
        if ( box[4 - 1] == naught & box[5 - 1] == naught & box[6 - 1] == 0 )
        {
            return 6 - 1;
            break;
        }
        // 2 ##
        if ( box[4 - 1] == naught & box[6 - 1] == naught & box[5 - 1] == 0 )
        {
            return 5 - 1;
            break;
        }
        if ( box[5 - 1] == naught & box[6 - 1] == naught & box[4 - 1] == 0 )
        {
            return 4 - 1;
            break;
        }
        //****************line 3****************
        //2  ##
        if ( box[7 - 1] == naught & box[8 - 1] == naught & box[9 - 1] == 0 )
        {
            return 9 - 1;
            break;
        }
        // 2 ##
        if ( box[7 - 1] == naught & box[9 - 1] == naught & box[8 - 1] == 0 )
        {
            return 8 - 1;
            break;
        }
        if ( box[8 - 1] == naught & box[9 - 1] == naught & box[7 - 1] == 0 )
        {
            return 7 - 1;
            break;
        }
///############### vert checks ##################
//******************* line 1 *****************
        //2  ##
        if ( box[1 - 1] == naught & box[4 - 1] == naught & box[7 - 1] == 0 )
        {
            return 7 - 1;
            break;
        }
        // 2 ##
        if ( box[1 - 1] == naught & box[7 - 1] == naught & box[4 - 1] == 0 )
        {
            return 4 - 1;
            break;
        }
        if ( box[4 - 1] == naught & box[7 - 1] == naught & box[1 - 1] == 0 )
        {
            return 1 - 1;
            break;
        }
//******************* line 2 *****************
        //2  ##
        if ( box[2 - 1] == naught & box[5 - 1] == naught & box[8 - 1] == 0 )
        {
            return 8 - 1;
            break;
        }
        // 2 ##
        if ( box[2 - 1] == naught & box[8 - 1] == naught & box[5 - 1] == 0 )
        {
            return 5 - 1;
            break;
        }
        if ( box[5 - 1] == naught & box[8 - 1] == naught & box[2 - 1] == 0 )
        {
            return 2 - 1;
            break;
        }
//******************* line 3 *****************
        //2  ##
        if ( box[3 - 1] == naught & box[6 - 1] == naught & box[9 - 1] == 0 )
        {
            return 9 - 1;
            break;
        }
        // 2 ##
        if ( box[3 - 1] == naught & box[9 - 1] == naught & box[6 - 1] == 0 )
        {
            return 6 - 1;
            break;
        }
        if ( box[6 - 1] == naught & box[9 - 1] == naught & box[3 - 1] == 0 )
        {
            return 3 - 1;
            break;
        }
//#################### diagonals #################
        // **************** diagonal1 ************
        //2  ##
        if ( box[1 - 1] == naught & box[5 - 1] == naught & box[9 - 1] == 0 )
        {
            return 9 - 1;
            break;
        }
        // 2 ##
        if ( box[5 - 1] == naught & box[9 - 1] == naught & box[1 - 1] == 0 )
        {
            return 1 - 1;
            break;
        }
        if ( box[1 - 1] == naught & box[9 - 1] == naught & box[5 - 1] == 0 )
        {
            return 5 - 1;
            break;
        }
// **************** diagonal2 ************
        //2  ##
        if ( box[3 - 1] == naught & box[5 - 1] == naught & box[7 - 1] == 0 )
        {
            return 7 - 1;
            break;
        }
        // 2 ##
        if ( box[7 - 1] == naught & box[5 - 1] == naught & box[3 - 1] == 0 )
        {
            return 3 - 1;
            break;
        }

        if ( box[3 - 1] == naught & box[7 - 1] == naught & box[5 - 1] == 0 )
        {
            return 5 - 1;
            break;
        }

//############ahhhh all done :) #############
        break;
    }

}

void
select_ttt ( unsigned int xo )
{                               //function
    if ( filled < 9 )
    {                           //filled

        if ( turn == 1 )
        {                       //turn

            if ( used[selected - 1] == 0 )
            {                   //used
                turn = 2;
                used[selected - 1] = 1;
                if ( xo == 1 )
                {               //o
                    lcd_draw_bitmap ( cursposy[selected - 1], cursposx[selected - 1], &bmp_o );
                    box[selected - 1] = 2;
                }               //o
                if ( xo == 2 )
                {
                    lcd_draw_bitmap ( cursposy[selected - 1], cursposx[selected - 1], &bmp_x );
                    box[selected - 1] = 1;
                }
                used[selected - 1] = 1;
                selected = 0;
                lcd_to_screen (  );
                filled = filled + 1;
            }                   //used
            checkwinsx (  );
            checkwinso (  );
        }                       //turn

        if ( turn == 2 )
        {                       //turn

            if ( used[selected - 1] == 0 )
            {                   //used
                turn = 1;
                used[selected - 1] = 1;
                if ( xo == 1 )
                {               //o
                    lcd_draw_bitmap ( cursposy[selected - 1], cursposx[selected - 1], &bmp_o );
                    box[selected - 1] = 2;
                }               //o
                if ( xo == 2 )
                {
                    lcd_draw_bitmap ( cursposy[selected - 1], cursposx[selected - 1], &bmp_x );
                    box[selected - 1] = 1;
                }
                used[selected - 1] = 1;
                selected = 0;
                lcd_to_screen (  );
                filled = filled + 1;
            }                   //used
            checkwinsx (  );
            checkwinso (  );
        }                       //turn
    }                           //filled
}                               //function

unsigned int
pc_select (  )
{
    ksleep ( 10 );
    unsigned int elements = 10, x = 0, pos, block, win;
    unsigned char buf[10];
    block = blocktoinarow ( box, filled );
    win = winthreeinarow ( box, filled );
    while ( 1 )
    {
        if ( filled > 8 )
        {
            break;
        }
        if ( win > 1 )
        {
            if ( used[win] == 0 )
            {
                return ( win );
                break;
            }
        }
        if ( block < 1 )
        {
            pos = lib_mod ( lib_rand ( 10 ), elements ) - 1;

            if ( pos >= 0 & pos <= 9 )
            {
                if ( used[pos] == 0 )
                {
                    return ( pos );
                    break;
                }
            }
        }
        if ( used[block] == 0 )
        {
            return ( block );
            break;
        }
    }
}



void
ttt_main_1 (  )
{                               //function
    lcd_clr (  );
//   box = { 0,0,0,0,0,0,0,0,0,0 };
    box[0] = 0;
    box[1] = 0;
    box[2] = 0;
    box[3] = 0;
    box[4] = 0;
    box[5] = 0;
    box[6] = 0;
    box[7] = 0;
    box[8] = 0;

    used[0] = 0;
    used[1] = 0;
    used[2] = 0;
    used[3] = 0;
    used[4] = 0;
    used[5] = 0;
    used[6] = 0;
    used[7] = 0;
    used[8] = 0;
    // used = { 0,0,0,0,0,0,0,0,0,0 };
    turn = 1;
    selected = 1;
    unsigned char key = 0;
    // cursposx = { 1, 1, 1, 14, 14, 14, 27, 27, 27 };
    // cursposy = { 1, 16, 31, 1, 16, 31, 1, 16, 31 };
    filled = 0;
    lcd_draw_bitmap ( -1, -1, &bmp_tictactoe );
    lcd_to_screen (  );
    while ( 1 )
    {                           //while
        if ( turn == 2 )
        {                       //turn2
            selected = pc_select (  ) + 1;
            turn = 1;
            used[selected - 1] = 1;
            lcd_draw_bitmap ( cursposy[selected - 1], cursposx[selected - 1], &bmp_x );
            box[selected - 1] = 1;
            lcd_to_screen (  );
            used[selected - 1] = 1;
            selected = 0;
            filled = filled + 1;
        }                       //turn2
        checkwinsx (  );
        checkwinso (  );
        if ( turn == 1 )
        {                       //turn1
            kpd_wait_keypress (  );
            key = kpd_getkey (  );



            if ( key == KPD_CANCEL )
                break;
            switch ( key )
            {
                case 0x0:
                {

                }
                    break;
                case 0x1:
                    if ( used[1 - 1] == 0 )
                    {
                        selected = 1;
                        select_ttt ( 1 );
                    }
                    break;
                case 0x2:
                    if ( used[2 - 1] == 0 )
                    {
                        selected = 2;
                        select_ttt ( 1 );
                    }
                    break;
                case 0x3:
                    if ( used[3 - 1] == 0 )
                    {
                        selected = 3;
                        select_ttt ( 1 );
                    }
                    break;
                case 0x4:
                    if ( used[4 - 1] == 0 )
                    {
                        selected = 4;
                        select_ttt ( 1 );
                    }
                    break;
                case 0x5:
                    if ( used[5 - 1] == 0 )
                    {
                        selected = 5;
                        select_ttt ( 1 );
                    }
                    break;
                case 0x6:
                    if ( used[6 - 1] == 0 )
                    {
                        selected = 6;
                        select_ttt ( 1 );
                    }
                    break;
                case 0x7:
                    if ( used[7 - 1] == 0 )
                    {
                        selected = 7;
                        select_ttt ( 1 );
                    }
                    break;
                case 0x8:
                    if ( used[8 - 1] == 0 )
                    {
                        selected = 8;
                        select_ttt ( 1 );
                    }
                    break;
                case 0x9:
                    if ( used[9 - 1] == 0 )
                    {
                        selected = 9;
                        select_ttt ( 1 );
                    }
                    break;
                default:

                    break;
            }                   //case
        }                       //turn1

    }                           //while
}                               //function





void
ttt_main_2 (  )
{                               //function
    lcd_clr (  );
//   box = { 0,0,0,0,0,0,0,0,0,0 };
    box[0] = 0;
    box[1] = 0;
    box[2] = 0;
    box[3] = 0;
    box[4] = 0;
    box[5] = 0;
    box[6] = 0;
    box[7] = 0;
    box[8] = 0;

    used[0] = 0;
    used[1] = 0;
    used[2] = 0;
    used[3] = 0;
    used[4] = 0;
    used[5] = 0;
    used[6] = 0;
    used[7] = 0;
    used[8] = 0;
    // used = { 0,0,0,0,0,0,0,0,0,0 };
    turn = 1;
    selected = 1;
    unsigned char key = 0;
    // cursposx = { 1, 1, 1, 14, 14, 14, 27, 27, 27 };
    // cursposy = { 1, 16, 31, 1, 16, 31, 1, 16, 31 };
    filled = 0;
    lcd_draw_bitmap ( -1, -1, &bmp_tictactoe2 );
    lcd_to_screen (  );
    while ( 1 )
    {                           //while
        switch ( turn )
        {
            case 1:
                lcd_draw_bitmap ( 75, 12, &bmp_turn );
                lcd_draw_bitmap ( 75, 20, &bmp_turnclear );
                break;
            case 2:
                lcd_draw_bitmap ( 75, 12, &bmp_turnclear );
                lcd_draw_bitmap ( 75, 20, &bmp_turn );
                break;
        }
        if ( turn == 2 )
        {                       //turn2
            kpd_wait_keypress (  );
            key = kpd_getkey (  );



            if ( key == KPD_CANCEL )
                break;
            switch ( key )
            {
                case 0x0:
                {

                }
                    break;
                case 0x1:
                    if ( used[1 - 1] == 0 )
                    {
                        selected = 1;
                        select_ttt ( 1 );
                    }
                    break;
                case 0x2:
                    if ( used[2 - 1] == 0 )
                    {
                        selected = 2;
                        select_ttt ( 1 );
                    }
                    break;
                case 0x3:
                    if ( used[3 - 1] == 0 )
                    {
                        selected = 3;
                        select_ttt ( 1 );
                    }
                    break;
                case 0x4:
                    if ( used[4 - 1] == 0 )
                    {
                        selected = 4;
                        select_ttt ( 1 );
                    }
                    break;
                case 0x5:
                    if ( used[5 - 1] == 0 )
                    {
                        selected = 5;
                        select_ttt ( 1 );
                    }
                    break;
                case 0x6:
                    if ( used[6 - 1] == 0 )
                    {
                        selected = 6;
                        select_ttt ( 1 );
                    }
                    break;
                case 0x7:
                    if ( used[7 - 1] == 0 )
                    {
                        selected = 7;
                        select_ttt ( 1 );
                    }
                    break;
                case 0x8:
                    if ( used[8 - 1] == 0 )
                    {
                        selected = 8;
                        select_ttt ( 1 );
                    }
                    break;
                case 0x9:
                    if ( used[9 - 1] == 0 )
                    {
                        selected = 9;
                        select_ttt ( 1 );
                    }
                    break;
                default:

                    break;
            }                   //case
        }                       //turn2
        checkwinsx (  );
        checkwinso (  );
        switch ( turn )
        {
            case 1:
                lcd_draw_bitmap ( 75, 12, &bmp_turn );
                lcd_draw_bitmap ( 75, 20, &bmp_turnclear );
                break;
            case 2:
                lcd_draw_bitmap ( 75, 12, &bmp_turnclear );
                lcd_draw_bitmap ( 75, 20, &bmp_turn );
                break;
        }
        if ( turn == 1 )
        {                       //turn1
            kpd_wait_keypress (  );
            key = kpd_getkey (  );



            if ( key == KPD_CANCEL )
                break;
            switch ( key )
            {
                case 0x0:
                {

                }
                    break;
                case 0x1:
                    if ( used[1 - 1] == 0 )
                    {
                        selected = 1;
                        select_ttt ( 2 );
                    }
                    break;
                case 0x2:
                    if ( used[2 - 1] == 0 )
                    {
                        selected = 2;
                        select_ttt ( 2 );
                    }
                    break;
                case 0x3:
                    if ( used[3 - 1] == 0 )
                    {
                        selected = 3;
                        select_ttt ( 2 );
                    }
                    break;
                case 0x4:
                    if ( used[4 - 1] == 0 )
                    {
                        selected = 4;
                        select_ttt ( 2 );
                    }
                    break;
                case 0x5:
                    if ( used[5 - 1] == 0 )
                    {
                        selected = 5;
                        select_ttt ( 2 );
                    }
                    break;
                case 0x6:
                    if ( used[6 - 1] == 0 )
                    {
                        selected = 6;
                        select_ttt ( 2 );
                    }
                    break;
                case 0x7:
                    if ( used[7 - 1] == 0 )
                    {
                        selected = 7;
                        select_ttt ( 2 );
                    }
                    break;
                case 0x8:
                    if ( used[8 - 1] == 0 )
                    {
                        selected = 8;
                        select_ttt ( 2 );
                    }
                    break;
                case 0x9:
                    if ( used[9 - 1] == 0 )
                    {
                        selected = 9;
                        select_ttt ( 2 );
                    }
                    break;
                default:

                    break;
            }                   //case
            checkwinsx (  );
            checkwinso (  );
        }                       //turn1

    }                           //while
}                               //function






void
start_ttt (  )
{
    if ( type == 1 )
    {
        ttt_main_1 (  );
    }
    if ( type == 2 )
    {
        ttt_main_2 (  );
    }
}

void
ttt_type (  )
{
    char *tttmenu[] = { "1- P1 v's AI", "2- P1 v's P2", NULL };
    unsigned char key, k;


    while ( 1 )
    {
        key = menu_main ( tttmenu, 0 );
        kpd_wait_release (  );
        lib_rand ( key );
        if ( key == 0xff )
            break;
        key++;
        if ( key == 0x5 )
            break;
        switch ( key )
        {
            case 0x1:
                type = 1;
                k = 0xff;
                break;
            case 0x2:
                type = 2;
                k = 0xff;
                break;
            default:
                break;
        }
        if ( k == 0xff )
            break;
        usleep ( 50000 );
    }

}

void
ttt_main (  )
{
    char *tttmenu[] = { "1- Start", "2- Type", NULL };
    unsigned char key;


    while ( 1 )
    {
        key = menu_main ( tttmenu, 0 );
        kpd_wait_release (  );
        lib_rand ( key );
        if ( key == 0xff )
            break;
        key++;
        if ( key == 0x5 )
            break;
        switch ( key )
        {
            case 0x1:
                lcd_clr (  );
                start_ttt (  );
                break;
            case 0x2:
                ttt_type (  );
                break;
            default:
                break;
        }
    }

}

/*unsigned int pc_select ( unsigned int used[] )
{
unsigned int elements = 10, x = 0, pos ;
unsigned char buf[10];
	while ( 1 )
	{

	pos = lib_mod ( lib_rand ( 10 ), elements ) - 1;

if ( pos >= 0 & pos <= 9 )
{
  if (used[pos] == 0 )
{
	return ( pos );
    break;
}
}
	}
}

*/
