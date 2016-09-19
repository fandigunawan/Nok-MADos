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

// Reversi_KI.h
//
// Part of PAI
//
// containing function for computer move

#define SIZE_X	8
#define SIZE_Y	8

int possible_turns ( int gamefield[SIZE_X][SIZE_Y], int player );
int turn_execute ( int gamefield[SIZE_X][SIZE_Y], int player, int pos_x, int pos_y );
int turn_valid ( int gamefield[SIZE_X][SIZE_Y], int player, int pos_x, int pos_y, int check );

int
computer_turn ( int gamefield[SIZE_X][SIZE_Y], int player )
{
    int i, j, ci, cj;
    if ( possible_turns ( gamefield, player ) == 0 )
    {
        return 0;               // = False
    }
    int look_ahead[SIZE_X][SIZE_Y];
    int min_x = 0;
    int min_y = 0;
    int min = SIZE_X * SIZE_Y;

    for ( i = 0; i < SIZE_X; i++ )
    {
        for ( j = 0; j < SIZE_Y; j++ )
        {
            // reset field
            for ( ci = 0; ci < SIZE_X; ci++ )
            {
                for ( cj = 0; cj < SIZE_Y; cj++ )
                {
                    look_ahead[ci][cj] = gamefield[ci][cj];
                }
            }                   // copy all to lookahead

            if ( turn_valid ( look_ahead, player, i, j, 0 ) )
            {
                turn_execute ( look_ahead, player, i, j );
                if ( possible_turns ( look_ahead, -( player - 2 ) + 1 ) < min ) // wenn züge von gegner minimal!!
                {
                    min = possible_turns ( look_ahead, -( player - 2 ) + 1 );
                    min_x = i;
                    min_y = j;
                }
            }
        }
    }
    turn_execute ( gamefield, player, min_x, min_y );
    return 1;                   // = true
}

int
computer_turn2 ( int gamefield[SIZE_X][SIZE_Y], int player )
{
    int i, j, ci, cj;
    if ( possible_turns ( gamefield, player ) == 0 )
    {
        return 0;               // = False
    }
    int look_ahead[SIZE_X][SIZE_Y];
    int min_x = 0;
    int min_y = 0;
    int min = SIZE_X * SIZE_Y;
    int max, max2 = 0;

    for ( i = 0; i < SIZE_Y; i++ )
    {
        for ( j = 0; j < SIZE_Y; j++ )
        {
            // reset field
            for ( ci = 0; ci < SIZE_X; ci++ )
            {
                for ( cj = 0; cj < SIZE_Y; cj++ )
                {
                    look_ahead[ci][cj] = gamefield[ci][cj];
                }
            }
            max = turn_valid ( look_ahead, player, i, j, 0 );
            if ( max > max2 )   // 2 und 3,  
            {
                max2 = max;
                turn_execute ( look_ahead, player, i, j );
                min_x = i;
                min_y = j;
            }

        }
    }
    turn_execute ( gamefield, player, min_x, min_y );

}
