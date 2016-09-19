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
#include <hw/lcd.h>
#include <core/lib.h>
#include <hw/ccont.h>
#include <apps/snake.h>
#include <hw/buzzer.h>
#include <hw/vibra.h>
#include <apps/snd_snake.h>
#include <core/sched.h>

// defines the max length of the snake
#define SNAKE_MAX_LENGTH    0xF0
// defines the max apples on screen simultanous
#define SNAKE_MAX_APPLE    0x0A


#ifndef LOADER

unsigned char level = 0;
unsigned char laby = 0;
unsigned char apples = 1;
unsigned char apple_state = 0;
int apple_state_timer = 0;

//unsigned char snake_vibra_thread_id;
//unsigned char snake_sound_thread_id;

unsigned char snake_sound = 0;
unsigned char snake_vibra = 0;

// loop counts for the different skills
unsigned char dly[] = { 25, 20, 15, 10, 8, 7, 5, 3, 2, 0 };

/*int img_apple_x = 6;
int img_apple_y = 4;
unsigned char *img_apple =
"  XX  "
" XXXX "
" XXXX "
"  XX  ";

int img_head_x = 8;
int img_head_y = 6;
unsigned char *img_head  =
"  XXXX  "
" X XX X "
" XXXXXX "
" XXXXXX "
"  X  X  "
"   XX   ";*/

// the 4 labyrinths you can choose from
const unsigned char labyrinth[4][24][42] = {
    {
     "##########################################",
     "#                                        #",
     "#                                        #",
     "#                                        #",
     "#     ############                       #",
     "#                #                       #",
     "#                #                       #",
     "#                #########################",
     "#                #                       #",
     "#                #                       #",
     "#                #                       #",
     "#                        ######          #",
     "#                        #    #          #",
     "#            #############    #          #",
     "#           #                 #          #",
     "#          #                  #          #",
     "#         #                   #          #",
     "#        #                    #          #",
     "#       #                     #          #",
     "#       #                     #          #",
     "#                             #          #",
     "#                             #          #",
     "#                             #          #",
     "##########################################",
     },

    {
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                  ##########              ",
     "                           #              ",
     "                           #              ",
     "                           #              ",
     "                    ########              ",
     "                    #                     ",
     "                    #                     ",
     "                    #                     ",
     "                    #                     ",
     "                                          ",
     "                    #                     ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     },

    {
     "                                          ",
     "                  #                       ",
     "                  #                       ",
     "                  #                       ",
     "     ##########################           ",
     "                           #              ",
     "                           #              ",
     "            ##########     #              ",
     "    #                      ####           ",
     "    #                                     ",
     "    #                                     ",
     "    #                                     ",
     "    #                                     ",
     "    #                                     ",
     "    #################            #        ",
     "                                 #        ",
     "            #                    #        ",
     "     ########                    #        ",
     "                                 #        ",
     "       ###########################        ",
     "                                 #        ",
     "                                 #        ",
     "                                 #        ",
     "                                          ",
     },



    {
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     },
};

void
snake_vibra_thread ( void )
{

    while ( snake_vibra != 2 )
    {

        if ( snake_vibra == 1 )
        {
            vibra_setmode ( 2 );
            vibra_setfreq ( 20 );

            usleep ( 500000 );

            vibra_setmode ( 0 );
            vibra_setfreq ( 0 );

            if ( snake_vibra != 2 )
                snake_vibra = 0;
        }

        usleep ( 70000 );

    }

    //sched_threadend (  );
    return;
}

void
snake_sound_thread ( void )
{

    while ( snake_sound != 2 )
    {

        if ( snake_sound == 1 )
        {
            buzzer_snd_play ( snd_snake, sizeof ( snd_snake ) );

            if ( snake_sound != 2 )
                snake_sound = 0;
        }

        usleep ( 70000 );

    }

    //sched_threadend (  );
    return;
}

// generates a menu to change the skill/speed
void
snake_chg_level ( void )
{
    unsigned char k;

    while ( 1 )
    {
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8 + 1, "  select", 1 );
        lcd_render_text ( 0, 1 * 8 + 1, "  skill", 1 );
        lcd_draw_line ( 13, 22, 67, 22, 1 );    //1 waag
        lcd_draw_line ( 13, 30, 67, 30, 1 );    //2 waag
        lcd_draw_line ( 13, 22, 13, 30, 1 );    //1 senk
        lcd_draw_line ( 67, 22, 67, 30, 1 );    //2 senk
        for ( k = 0; k <= 4; k++ )
            lcd_draw_line ( 15, 24 + k, 20 + 5 * level, 24 + k, 1 );
        lcd_to_screen (  );
        k = kpd_getkey (  );
        while ( k == 0xff )
        {
            k = kpd_getkey (  );
        }
        if ( ( k == KPD_CANCEL ) || ( k == KPD_SOFTBTN1 ) )
            break;
        switch ( k )
        {
            case KPD_DWNARROW:
                if ( level != 0 )
                    level--;
                kpd_wait_release (  );
                break;
            case KPD_UPARROW:
                if ( level < 9 )
                    level++;
                kpd_wait_release (  );
                break;
            default:
                break;
        }
        usleep ( 50000 );
    }

}

// generates the menu for the apples
void
snake_chg_apples ( void )
{
    unsigned char k, buf[1];

    while ( 1 )
    {
        lcd_clr (  );
        lcd_render_text ( 0, 5, "  apples", 1 );
        lcd_draw_line ( 36, 20, 48, 20, 1 );    //hori 1
        lcd_draw_line ( 36, 32, 48, 32, 1 );    // "   2
        lcd_draw_line ( 36, 20, 36, 32, 1 );    //vert 1
        lcd_draw_line ( 48, 20, 48, 32, 1 );    //vert 2
        buf[0] = apples + 0x30;
        lcd_render_text ( 39, 23, buf, 1 );
        lcd_to_screen (  );

        k = kpd_getkey (  );
        while ( k == 0xff )
        {
            k = kpd_getkey (  );
        }

        if ( ( k == KPD_CANCEL ) || ( k == KPD_SOFTBTN1 ) )
            break;
        if ( ( k > 0 ) && ( k <= 9 ) )
            apples = k;
        switch ( k )
        {
            case KPD_DWNARROW:
                if ( apples > 1 )
                    apples--;
                break;
            case KPD_UPARROW:
                if ( apples < 9 )
                    apples++;
                break;
            default:
                break;
        }
        kpd_wait_release (  );
        usleep ( 50000 );
    }
}

// generates the menu for the different labyrinths
void
snake_chg_laby ( void )
{
    unsigned char k;
    char *labymenu[] = { "type 1    ", "type 2    ", "type 3    ", "type 4    ", "*back*", NULL };

    while ( 1 )
    {
        k = menu_main ( labymenu, laby );
        kpd_wait_release (  );
        if ( k == 0xff )
            break;
        k++;
        if ( k == 0x5 )
            break;
        switch ( k )
        {
            case 0x1:
                laby = 0;
                k = 0xff;
                break;
            case 0x2:
                laby = 1;
                k = 0xff;
                break;
            case 0x3:
                laby = 2;
                k = 0xff;
                break;
            case 0x4:
                laby = 3;
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

// draws apples, walls and the snake to screen
void
snake_draw ( unsigned char *posx, unsigned char *posy, unsigned char *applez_x, unsigned char *applez_y )
{
    unsigned char i;
    unsigned char x;
    unsigned char y;

    lcd_clr (  );

    for ( i = 0; i <= SNAKE_MAX_APPLE; i++ )
    {
        if ( applez_x[i] != 0xff )
        {
            //lcd_render_bitmap ( applez_x[i] - img_apple_x>>1, applez_y[i] - img_apple_y>>1, img_apple_x, img_apple_y, img_apple, 1 );
            if ( apple_state != 3 )
                lcd_set_pixel ( applez_x[i], applez_y[i], 1 );
            if ( apple_state != 2 )
                lcd_set_pixel ( applez_x[i] + 1, applez_y[i], 1 );
            if ( apple_state != 1 )
                lcd_set_pixel ( applez_x[i], applez_y[i] + 1, 1 );
            if ( apple_state != 0 )
                lcd_set_pixel ( applez_x[i] + 1, applez_y[i] + 1, 1 );

            //if ( apple_state_timer > 700 )
            //{
            //  apple_state_timer = 0;
            //}
        }

    }

    if ( apple_state_timer > 30 )
    {
        if ( apple_state != 4 )
            apple_state++;
        else
            apple_state = 0;

        apple_state_timer = 0;
    }

    for ( i = 0; i <= SNAKE_MAX_LENGTH; i++ )
    {
        if ( posx[i] != 0xff )
        {
            //lcd_render_bitmap ( posx[i] - img_head_x>>1, posy[i] - img_head_y>>1, img_head_x, img_head_y, img_head, 1 );
            lcd_set_pixel ( posx[i], posy[i], 1 );
            lcd_set_pixel ( posx[i] + 1, posy[i], 1 );
            lcd_set_pixel ( posx[i], posy[i] + 1, 1 );
            lcd_set_pixel ( posx[i] + 1, posy[i] + 1, 1 );
        }

    }

    if ( laby < 4 )
    {
        for ( y = 0; y < 24; y++ )
            for ( x = 0; x < 42; x++ )
                if ( labyrinth[laby][y][x] > 0x20 )
                {
                    lcd_set_pixel ( x * 2, y * 2, 1 );
                    lcd_set_pixel ( x * 2 + 1, y * 2, 1 );
                    lcd_set_pixel ( x * 2, y * 2 + 1, 1 );
                    lcd_set_pixel ( x * 2 + 1, y * 2 + 1, 1 );
                }
    }

    lcd_to_screen (  );
}

// examines whether a point collides with an apple
unsigned char
snake_check_apple ( unsigned char x, unsigned char y, unsigned char *applez_x, unsigned char *applez_y, unsigned char nocheck )
{
    unsigned char i, ret = 0;

    for ( i = 0; i <= SNAKE_MAX_APPLE; i++ )
    {
        if ( ( applez_x[i] == x ) && ( applez_y[i] == y ) && ( nocheck != i ) )
            ret++;
    }

    return ret;

}

// kills an apple
void
snake_kill_apple ( unsigned char x, unsigned char y, unsigned char *applez_x, unsigned char *applez_y )
{
    unsigned char i;

    for ( i = 0; i <= SNAKE_MAX_APPLE; i++ )
    {
        if ( ( applez_x[i] == x ) && ( applez_y[i] == y ) )
        {
            applez_x[i] = 0xff;
            applez_y[i] = 0xff;
            break;
        }
    }
}

// examines whether a point collides with a part of the snake
unsigned char
snake_check_snake ( unsigned char x, unsigned char y, unsigned char *posx, unsigned char *posy, unsigned char nocheck )
{
    unsigned char i, ret = 0;

    for ( i = 0; i <= SNAKE_MAX_LENGTH; i++ )
    {
        if ( ( posx[i] == x ) && ( posy[i] == y ) && ( nocheck != i ) )
            ret++;
    }

    return ret;

}

// examines whether a point collides with the wall
unsigned char
snake_check_wall ( unsigned char x, unsigned char y )
{

    if ( labyrinth[laby][y][x] == '#' )
        return 1;

    return 0;

}

// generates an apple at an unused position on screen
void
snake_generate_apple ( unsigned char *posx, unsigned char *posy, unsigned char *applez_x, unsigned char *applez_y )
{
    unsigned char i, j, k, x, y, f;

    f = 0;
    for ( i = 0; i <= SNAKE_MAX_APPLE; i++ )
    {
        if ( applez_x[i] == 0xff )
        {
            f = 1;
            break;
        }
    }

    if ( f == 1 )
        while ( 1 )
        {

            x = lib_mod ( lib_rand ( i * 1395 ), 82 );
            y = lib_mod ( lib_rand ( x * 2589 ), 46 );

            if ( lib_mod ( x, 2 ) != 0 )
                x++;
            if ( lib_mod ( y, 2 ) != 0 )
                y++;


            f = snake_check_snake ( x, y, posx, posy, 0xff );
            k = snake_check_apple ( x, y, applez_x, applez_y, 0xff );
            j = snake_check_wall ( x / 2, y / 2 );

            if ( ( f == 0 ) && ( k == 0 ) && ( j == 0 ) )
            {
                applez_x[i] = x;
                applez_y[i] = y;
                break;
            }

            /*
             * f = 0;
             * for ( k = 0; k <= SNAKE_MAX_LENGTH; k++)
             * {
             * if ( ( x == posx[k] )  ( y == posy[k] ) ) f = 1;
             * }
             * 
             * for ( k = 0; k <= SNAKE_MAX_APPLE; k++)
             * {
             * if ( ( x == applez_x[k] )  ( y == applez_y[k] ) ) f = 1;
             * }
             * 
             * if ( f == 0 ) break; 
             */
        }

}

// called at the end, if the snake collides with itself or a wall
void
snake_game_over ( unsigned int points )
{
    char buf[8];
    //vibra_setmode ( 0 );
    //vibra_setfreq ( 0 );
    //snake_vibra = 2;
    //snake_sound = 2;
    kpd_wait_release (  );
    lcd_draw_rect ( 0, 20, 74, 28, 0 );
    lcd_render_text ( 2, 20, "Game Over", 1 );
    lcd_to_screen (  );
    buzzer_snd_play ( snd_gameover, sizeof ( snd_gameover ) );
    kpd_wait_release (  );
    kpd_wait_keypress (  );
    //sleep ( 2 );
    lcd_clr (  );
    lcd_render_text ( 0, 0 * 8, "Your", 1 );
    lcd_render_text ( 0, 1 * 8, "score:", 1 );
    lib_dtoa ( buf, points, 7, 1 );
    lcd_render_text ( 0, 3 * 8, buf, 1 );
    //lib_hexconv ( buf, points );
    //lcd_render_text ( 2 * 8, 3 * 8, buf, 1 );
    lcd_to_screen (  );
    kpd_wait_release (  );
    //ksleep ( 10 );
    kpd_wait_keypress (  );
    kpd_wait_release (  );

}

// initializes and run snake until abort/end
void
snake_start ( void )
{

    unsigned char *ringbuffer_posx, *ringbuffer_posy, *applez_x, *applez_y, aktuelle_pos = 0, direction = 0, length = 4,    //starting length only numbers possible to divide by 2 without rest :-) - fixed...
        i, j, key;
    unsigned int points = 0;

    ringbuffer_posx = ( unsigned char * ) malloc ( SNAKE_MAX_LENGTH + 1 );
    ringbuffer_posy = ( unsigned char * ) malloc ( SNAKE_MAX_LENGTH + 1 );
    applez_x = ( unsigned char * ) malloc ( SNAKE_MAX_APPLE + 1 );
    applez_y = ( unsigned char * ) malloc ( SNAKE_MAX_APPLE + 1 );

    snake_sound = 0;
    snake_vibra = 0;

    i = sched_add ( ( unsigned int ) snake_vibra_thread, 1, SCHED_PARM_RUN );
    i = sched_add ( ( unsigned int ) snake_sound_thread, 1, SCHED_PARM_RUN );

    for ( i = 0; i <= SNAKE_MAX_LENGTH; i++ )
    {
        ringbuffer_posx[i] = 0xff;
        ringbuffer_posy[i] = 0xff;
    }

    for ( i = 0; i <= SNAKE_MAX_APPLE; i++ )
    {
        applez_x[i] = 0xff;
        applez_y[i] = 0xff;
    }

    for ( i = 21; i <= ( 20 + length ); i++ )
    {
        ringbuffer_posx[aktuelle_pos] = i;
        ringbuffer_posy[aktuelle_pos] = 24;
        aktuelle_pos++;
    }

    aktuelle_pos--;

    for ( i = 1; i <= apples; i++ )
        snake_generate_apple ( ringbuffer_posx, ringbuffer_posy, applez_x, applez_y );

    key = kpd_getkey (  );      //this fixes the bug, when starting snake again, after canceled a game with C before

    while ( 1 )
    {
        for ( i = 0; i <= dly[level]; i++ )
        {
            usleep ( 10000 );
            j = kpd_getkey (  );
            if ( j != 0xff )
                key = j;
        }

        if ( dly[level] > 0 )
            apple_state_timer += dly[level];
        else
            apple_state_timer++;

        lib_rand ( key + aktuelle_pos + apple_state_timer );
        //vibra_setmode ( 0 );
        //vibra_setfreq ( 0 );

        if ( key == KPD_CANCEL )
            break;
        switch ( key )
        {
            case 0x0:
                kpd_wait_release (  );
                lcd_draw_rect ( 2 * 8, 2 * 8, 10 * 8, 3 * 8, 0 );
                lcd_render_text ( 2 * 8, 2 * 8, "-paused-", 1 );
                lcd_to_screen (  );
                kpd_wait_keypress (  );
                kpd_wait_release (  );
                key = 0xFF;
                break;
            case 0x2:
                if ( direction != 3 )
                    direction = 1;
                break;
            case 0x4:
                if ( direction != 0 )
                    direction = 2;
                break;
            case 0x6:
                if ( direction != 2 )
                    direction = 0;
                break;
            case 0x8:
                if ( direction != 1 )
                    direction = 3;
                break;
            default:
                break;
        }

        aktuelle_pos++;
        if ( aktuelle_pos == ( SNAKE_MAX_LENGTH + 1 ) )
        {
            aktuelle_pos = 0;
            i = SNAKE_MAX_LENGTH;
        }
        else if ( aktuelle_pos == 0 )
            i = SNAKE_MAX_LENGTH;
        else
            i = aktuelle_pos - 1;

        switch ( direction )
        {
            case 0:
                ringbuffer_posy[aktuelle_pos] = ringbuffer_posy[i];
                ringbuffer_posx[aktuelle_pos] = ringbuffer_posx[i] + 2;
                break;
            case 1:
                if ( ringbuffer_posy[i] != 0 )
                    ringbuffer_posy[aktuelle_pos] = ringbuffer_posy[i] - 2;
                else
                    ringbuffer_posy[aktuelle_pos] = 46;
                ringbuffer_posx[aktuelle_pos] = ringbuffer_posx[i];
                break;
            case 2:
                ringbuffer_posy[aktuelle_pos] = ringbuffer_posy[i];
                if ( ringbuffer_posx[i] != 0 )
                    ringbuffer_posx[aktuelle_pos] = ringbuffer_posx[i] - 2;
                else
                    ringbuffer_posx[aktuelle_pos] = 82;
                break;
            case 3:
                ringbuffer_posy[aktuelle_pos] = ringbuffer_posy[i] + 2;
                ringbuffer_posx[aktuelle_pos] = ringbuffer_posx[i];
                break;
        }

        if ( ringbuffer_posx[aktuelle_pos] == 84 )
            ringbuffer_posx[aktuelle_pos] = 0;
        if ( ringbuffer_posy[aktuelle_pos] == 48 )
            ringbuffer_posy[aktuelle_pos] = 0;

        if ( aktuelle_pos >= length )
        {
            ringbuffer_posx[aktuelle_pos - length] = 0xff;
            ringbuffer_posy[aktuelle_pos - length] = 0xff;
        }
        else
        {
            ringbuffer_posx[( SNAKE_MAX_LENGTH + 1 ) + ( aktuelle_pos - length )] = 0xff;
            ringbuffer_posy[( SNAKE_MAX_LENGTH + 1 ) + ( aktuelle_pos - length )] = 0xff;
        }

        snake_draw ( ringbuffer_posx, ringbuffer_posy, applez_x, applez_y );


        if ( snake_check_apple ( ringbuffer_posx[aktuelle_pos], ringbuffer_posy[aktuelle_pos], applez_x, applez_y, 0xff ) == 1 )
        {
            snake_kill_apple ( ringbuffer_posx[aktuelle_pos], ringbuffer_posy[aktuelle_pos], applez_x, applez_y );
            points += ( level + 1 );
            length++;

            //i = sched_add ( ( unsigned int ) snake_vibra_thread, 1, SCHED_PARM_RUN );
            //i = sched_add ( ( unsigned int ) snake_sound_thread, 1, SCHED_PARM_RUN );
            snake_sound = 1;
            snake_vibra = 1;
            //vibra_setmode ( 2 );
            //vibra_setfreq ( 20 );
            snake_generate_apple ( ringbuffer_posx, ringbuffer_posy, applez_x, applez_y );
            //buzzer_snd_play ( snd_snake, sizeof ( snd_snake ) );

        }
        else if ( snake_check_snake ( ringbuffer_posx[aktuelle_pos], ringbuffer_posy[aktuelle_pos], ringbuffer_posx, ringbuffer_posy, aktuelle_pos ) == 1 )
        {
            snake_game_over ( points );
            break;
        }

        if ( snake_check_wall ( ringbuffer_posx[aktuelle_pos] / 2, ringbuffer_posy[aktuelle_pos] / 2 ) )
        {
            snake_game_over ( points );
            break;
        }

        if ( length == SNAKE_MAX_LENGTH )
            break;

    }
    free ( ringbuffer_posx );
    free ( ringbuffer_posy );
    free ( applez_x );
    free ( applez_y );
    snake_vibra = 2;
    snake_sound = 2;
}

// the snake main menu - calls all other snake functions
void
snake_main ( void )
{
    char *snakemenu[] = { "1- snake", "2- skill", "3- laby.", "4- apples", "5- *back*", NULL };
    unsigned char key;
    level = 0;
    laby = 0;
    apples = 1;
    apple_state = 0;
    apple_state_timer = 0;

    while ( 1 )
    {
        key = menu_main ( snakemenu, 0 );
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
//              lcd_type_text_2 ( 0, 3*8, 3, "starting", 1 );
                lcd_type_text_2 ( 0, 3 * 8, 3, "ready...", 1 );
                kpd_wait_release (  );
                snake_start (  );
                kpd_wait_release (  );
                break;
            case 0x2:
                snake_chg_level (  );
                kpd_wait_release (  );
                break;
            case 0x3:
                snake_chg_laby (  );
                kpd_wait_release (  );
                break;
            case 0x4:
                snake_chg_apples (  );
                kpd_wait_release (  );
                break;
            default:
                break;
        }
    }
}

#endif
