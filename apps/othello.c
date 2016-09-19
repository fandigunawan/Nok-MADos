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

/**
Othello Game
created by Dr.Hackstable
*/
#include <hw/kpd.h>
#include <hw/lcd.h>
#include <hw/ccont.h>
#include <hw/buzzer.h>
#include <hw/vibra.h>
#include <core/lib.h>
#include <apps/othello.h>
#include <apps/othello_KI.h>

//extern const unsigned char snd_gameover[] ;
//extern const unsigned char snd_snake[] ;
#define SIZE_X	8
#define SIZE_Y	8

int typ = 0;
int skill = 0;

int gamefield[SIZE_X][SIZE_Y] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 2, 0, 0, 0},
    {0, 0, 0, 2, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};                              // 1= Player 1(o); 2 = Player 2 (x); 3=Cursor

// generates the menu for the apples
void
draw_gamefield ( int gamefield[SIZE_X][SIZE_Y], int player )
{
    int x, y, j, i, laby = 0;
    int gx, gy, summe2A = 0, summe2B = 0, summe1A = 0, summe1B = 0;
    unsigned char status[4];

    lcd_clr (  );
    // Draw Outlines
    for ( i = 1; i <= 7; i++ )
    {
        x = 6 * i - 1;
        for ( y = 0; y < 47; y++ )
            lcd_set_pixel ( x, y, 1 );
    }
    for ( j = 1; j <= 7; j++ )
    {
        y = 6 * j - 1;
        for ( x = 0; x < 47; x++ )
            lcd_set_pixel ( x, y, 1 );
    }

    /*
     * for ( y = 0; y < 47; y++ )
     * lcd_set_pixel ( 48, y, 1 );
     * for ( y = 0; y < 47; y++ )
     * lcd_set_pixel ( 49, y, 1 );
     */
    lcd_draw_rect ( 48, 0, 49, 47, 1 );

    // Draw Gamefield            
    for ( gy = 0; gy < SIZE_Y; gy++ )
    {
        for ( gx = 0; gx < SIZE_X; gx++ )
        {
            switch ( gamefield[gx][gy] )
            {
                case 0:
                    break;
                case 1:
                    x = 6 * gx - 1;
                    y = 6 * gy - 1; // Draw for player 1
                    /*
                     * lcd_set_pixel ( x + 2, y + 2, 1 );
                     * lcd_set_pixel ( x + 3, y + 2, 1 );
                     * lcd_set_pixel ( x + 4, y + 2, 1 );
                     * lcd_set_pixel ( x + 2, y + 3, 1 );
                     * lcd_set_pixel ( x + 3, y + 3, 1 );
                     * lcd_set_pixel ( x + 4, y + 3, 1 );
                     * lcd_set_pixel ( x + 3, y + 4, 1 );
                     * lcd_set_pixel ( x + 2, y + 4, 1 );
                     * lcd_set_pixel ( x + 4, y + 4, 1 );
                     */
                    lcd_draw_rect ( x + 2, y + 2, x + 4, y + 4, 1 );
                    summe1B++;
                    if ( summe1B == 10 )
                    {
                        summe1B = 0;
                        summe1A++;
                    }
                    break;

                case 2:
                    x = 6 * gx - 1;
                    y = 6 * gy - 1;
                    lcd_set_pixel ( x + 2, y + 2, 1 );  // Draw for player 2
                    lcd_set_pixel ( x + 4, y + 2, 1 );
                    lcd_set_pixel ( x + 3, y + 3, 1 );
                    lcd_set_pixel ( x + 2, y + 4, 1 );
                    lcd_set_pixel ( x + 4, y + 4, 1 );
                    summe2B++;
                    if ( summe2B == 10 )
                    {
                        summe2B = 0;
                        summe2A++;
                    }
                    break;
                case 3:
                    x = 6 * gx - 1;
                    y = 6 * gy - 1;
                    lcd_set_pixel ( x + 1, y + 1, 1 );
                    lcd_set_pixel ( x + 3, y + 1, 1 );
                    lcd_set_pixel ( x + 5, y + 1, 1 );
                    lcd_set_pixel ( x + 2, y + 2, 1 );
                    lcd_set_pixel ( x + 4, y + 2, 1 );
                    lcd_set_pixel ( x + 1, y + 3, 1 );
                    lcd_set_pixel ( x + 3, y + 3, 1 );
                    lcd_set_pixel ( x + 5, y + 3, 1 );
                    lcd_set_pixel ( x + 2, y + 4, 1 );
                    lcd_set_pixel ( x + 4, y + 4, 1 );
                    lcd_set_pixel ( x + 1, y + 5, 1 );
                    lcd_set_pixel ( x + 3, y + 5, 1 );
                    lcd_set_pixel ( x + 5, y + 5, 1 );
                    break;
            };
        };
    };
    status[0] = 'o';
    status[1] = ':';
    status[2] = summe1A + 48;
    status[3] = summe1B + 48;
    lcd_render_text ( 53, 0, status, 1 );
    status[0] = 'x';
    status[1] = ':';
    status[2] = summe2A + 48;
    status[3] = summe2B + 48;
    lcd_render_text ( 53, 14, status, 1 );
    status[0] = 'p';
    status[1] = 'l';
    status[2] = ':';
    if ( player == 1 )
        status[3] = 'o';
    if ( player == 2 )
        status[3] = 'x';
    lcd_render_text ( 53, 35, status, 1 );
    lcd_to_screen (  );
}

int
possible_turns ( int gamefield[SIZE_X][SIZE_Y], int player )
{
    int mzug = 0, x, y;
    for ( y = 0; y < SIZE_Y; y++ )
    {
        for ( x = 0; x < SIZE_X; x++ )
        {
            if ( turn_valid ( gamefield, player, x, y, 1 ) )
                mzug++;
        };
    };
    return mzug;
}

int
winner ( int gamefield[SIZE_X][SIZE_Y] )
{
    int x, y, summe1 = 0, summe2 = 0;
    for ( y = 0; y < SIZE_Y; y++ )
    {
        for ( x = 0; x < SIZE_X; x++ )
        {
            switch ( gamefield[x][y] )
            {
                case 1:
                    summe1++;
                    break;
                case 2:
                    summe2++;
                    break;
                default:
                    break;
            };

        };
    };
    if ( summe1 == summe2 )
        return 0;
    else if ( summe1 > summe2 )
        return 1;
    else
        return 2;
}

int
turn_valid ( int gamefield[SIZE_X][SIZE_Y], int player, int pos_x, int pos_y, int check )
{
    int k, i, j, kisteps = 0, steps, x, y;
    // Process all possible directions
    int gegner = -( player - 2 ) + 1;

    if ( gamefield[pos_x][pos_y] != 0 )
    {
        return 0;               // = False not valid
    }

    for ( i = -1; i <= 1; i++ )
    {
        for ( j = -1; j <= 1; j++ )
        {

            // Check bounds and
            // Only process directions starting with an opponents stone
            x = pos_x + i;
            y = pos_y + j;

            if ( x >= 0 && x < SIZE_X && y >= 0 && y < SIZE_Y && gamefield[x][y] == gegner )
            {
                steps = 2;
                while ( ( pos_x + steps * i ) >= 0 && ( pos_y + steps * j ) >= 0 && ( pos_x + steps * i ) < SIZE_X && ( pos_y + steps * j ) < SIZE_Y )
                {
                    if ( gamefield[pos_x + steps * i][pos_y + steps * j] == player )
                    {
                        if ( check == 0 )
                        {
                            for ( k = 1; k < steps; k++ )
                                gamefield[pos_x + k * i][pos_y + k * j] = player;
                        }
                        kisteps = steps;
                        break;

                    }
                    if ( gamefield[pos_x + steps * i][pos_y + steps * j] == 0 )
                    {
                        break;
                    }
                    steps++;
                }
            }
        }
    }
    if ( kisteps >= 2 )
    {
        return kisteps;
    }
    else
        return 0;
}

int
turn_execute ( int gamefield[SIZE_X][SIZE_Y], int player, int pos_x, int pos_y )
{
    if ( turn_valid ( gamefield, player, pos_x, pos_y, 0 ) )
    {
        gamefield[pos_x][pos_y] = player;
        return 1;
    }
    else
        return 0;

}

void
othello_game_over ( void )
{
    vibra_setmode ( 0 );
    vibra_setfreq ( 0 );
    kpd_wait_release (  );
    lcd_clr (  );
    lcd_draw_rect ( 14, 20, 70, 28, 0 );
    //buzzer_snd_play ( snd_gameover, sizeof(snd_gameover) );
    lcd_to_screen (  );
    if ( winner ( gamefield ) == 0 )
    {
        lcd_type_text_2 ( 21, 17, 1, "Draw!", 1 );
    }
    if ( winner ( gamefield ) == 1 )
    {
        lcd_type_text_2 ( 2, 17, 1, "Player (o)", 1 );
        lcd_type_text_2 ( 21, 27, 1, "wins!", 1 );
    }
    if ( winner ( gamefield ) == 2 )
    {
        lcd_type_text_2 ( 2, 17, 1, "Player (x)", 1 );
        lcd_type_text_2 ( 21, 27, 1, "wins!", 1 );
    }
    kpd_wait_release (  );
    ksleep ( 5 );
    kpd_wait_release (  );
}

void
reset_gamefield ( void )
{
    int x, y;
    for ( x = 0; x < SIZE_X; x++ )
    {
        for ( y = 0; y < SIZE_Y; y++ )
        {
            gamefield[x][y] = 0;
        }
    }
    gamefield[3][3] = 1;
    gamefield[4][4] = 1;
    gamefield[3][4] = 2;
    gamefield[4][3] = 2;
}

// initializes and run snake until abort/end
void
othello_start ( void )
{
    int x = 3, y = 2, check = 0, finish = 0;
    unsigned char k, buf[1];
    int player = 1;
    draw_gamefield ( gamefield, player );
    while ( 1 )
    {
        k = kpd_getkey (  );
        //ccont_reset_wdt (  );
        while ( k == 0xff )
        {
            k = kpd_getkey (  );
            //ccont_reset_wdt (  );
        }

        if ( ( k == KPD_CANCEL ) || ( k == KPD_SOFTBTN1 ) )
        {
            if ( gamefield[x][y] == 3 )
                gamefield[x][y] = 0;
            break;
        }

        switch ( k )
        {
            case 0x2:
                check = 0;
                if ( gamefield[x][y] == 3 )
                    gamefield[x][y] = 0;
                do
                {
                    y = y - 1;
                    check++;
                    if ( check == SIZE_Y )
                    {
                        check = 0;
                        x = x + 1;
                    }
                    if ( !( y >= 0 && y < SIZE_Y ) )
                        y = y + SIZE_Y;
                }
                while ( gamefield[x][y] != 0 );
                gamefield[x][y] = 3;
                break;
            case 0x4:
                check = 0;
                if ( gamefield[x][y] == 3 )
                    gamefield[x][y] = 0;
                do
                {
                    x = x - 1;
                    check++;
                    if ( check == SIZE_X )
                    {
                        check = 0;
                        y = y + 1;
                    }
                    if ( !( x >= 0 && x < SIZE_X ) )
                        x = x + SIZE_X;
                }
                while ( gamefield[x][y] != 0 );
                gamefield[x][y] = 3;
                break;
            case 0x5:
                if ( gamefield[x][y] == 3 )
                    gamefield[x][y] = 0;

                if ( typ == 0 )
                {
                    if ( turn_execute ( gamefield, 1, x, y ) )
                    {
                        do
                        {
                            if ( skill == 0 )
                                computer_turn ( gamefield, 2 );
                            if ( skill == 1 )
                                computer_turn2 ( gamefield, 2 );
                        }
                        while ( possible_turns ( gamefield, 1 ) == 0 );
                    }
                }

                if ( typ == 1 )
                {
                    if ( turn_execute ( gamefield, player, x, y ) )
                    {
                        player = 1 - player + 2;
                    }
                }

                if ( typ == 2 )
                {
                    if ( computer_turn ( gamefield, player ) )
                    {
                        player = 1 - player + 2;
                        do
                        {
                            computer_turn2 ( gamefield, player );
                        }
                        while ( possible_turns ( gamefield, 1 - player + 2 ) == 0 );
                    }
                }
                break;
            case 0x6:
                check = 0;
                if ( gamefield[x][y] == 3 )
                    gamefield[x][y] = 0;
                do
                {
                    x = x + 1;
                    check++;
                    if ( check == SIZE_X )
                    {
                        check = 0;
                        y = y + 1;
                    }
                    if ( !( x >= 0 && x < SIZE_X ) )
                        x = x - SIZE_X;
                }
                while ( gamefield[x][y] != 0 );
                gamefield[x][y] = 3;
                break;
            case 0x8:
                check = 0;
                if ( gamefield[x][y] == 3 )
                    gamefield[x][y] = 0;
                do
                {
                    y = y + 1;
                    check++;
                    if ( check == SIZE_Y )
                    {
                        check = 0;
                        x = x + 1;
                    }
                    if ( !( y >= 0 && y < SIZE_Y ) )
                        y = y - SIZE_Y;
                }
                while ( gamefield[x][y] != 0 );
                gamefield[x][y] = 3;
                break;
            default:
                break;
        }
        draw_gamefield ( gamefield, player );
        if ( ( possible_turns ( gamefield, 1 ) == 0 ) || ( possible_turns ( gamefield, 2 ) == 0 ) )
        {
            for ( k = 47; k > 25; k-- )
            {
                lcd_draw_rect ( 25, 50, 47, 83, 1 );
                lcd_to_screen (  );
                usleep ( 100000 );
            }
            kpd_wait_keypress (  );
            othello_game_over (  );
            reset_gamefield (  );
        }
        kpd_wait_release (  );
        usleep ( 5000 );
    }
}

void
othello_typ ( void )
{
    unsigned char k;
    char *labymenu[] = { "U1 vs KI ", "U1 vs U2 ", "KI1 vs KI2 ", "*back*", NULL };

    while ( 1 )
    {
        k = menu_main ( labymenu, typ );
        kpd_wait_release (  );
        if ( k == 0xff )
            break;
        k++;
        if ( k == 0x4 )
            break;
        switch ( k )
        {
            case 0x1:
                typ = 0;
                reset_gamefield (  );
                k = 0xff;
                break;
            case 0x2:
                typ = 1;
                reset_gamefield (  );
                k = 0xff;
                break;
            case 0x3:
                typ = 2;
                reset_gamefield (  );
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
othello_skill ( void )
{
    unsigned char k;
    char *labymenu[] = { "1- easy    ", "2- normal    ", "3- *back*", NULL };

    while ( 1 )
    {
        k = menu_main ( labymenu, skill );
        kpd_wait_release (  );
        if ( k == 0xff )
            break;
        k++;
        if ( k == 0x3 )
            break;
        switch ( k )
        {
            case 0x1:
                skill = 0;
                reset_gamefield (  );
                k = 0xff;
                break;
            case 0x2:
                skill = 1;
                reset_gamefield (  );
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

// the othello main menu - calls all other snake functions
void
othello_main ( void )
{
    char *snakemenu[] = { "1- start", "2- typ", "3- skill", "4- *back*", NULL };
    unsigned char key;

    while ( 1 )
    {
        key = menu_main ( snakemenu, 0 );
        kpd_wait_release (  );
        lib_rand ( key );
        if ( key == 0xff )
            break;
        key++;
        if ( key == 0x4 )
            break;
        switch ( key )
        {
            case 0x1:
                lcd_clr (  );
//              lcd_type_text_2 ( 0, 3*8, 3, "starting", 1 );
                kpd_wait_release (  );
                othello_start (  );
                kpd_wait_release (  );
                break;
            case 0x2:
                othello_typ (  );
                kpd_wait_release (  );
                break;
            case 0x3:
                othello_skill (  );
                kpd_wait_release (  );
                break;
            default:
                break;
        }
    }
}
