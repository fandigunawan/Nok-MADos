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
Matrix screensaver
created by Dr.Hackstable
*/
#include <hw/kpd.h>
#include <hw/lcd.h>
#include <hw/ccont.h>
#include <hw/buzzer.h>
#include <hw/vibra.h>
#include <core/lib.h>

#define SIZE_X	16              // * 5 = 80
#define SIZE_Y	8               // * 6 = 64


int matrix[SIZE_X][SIZE_Y] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
};

int code[8][5] = {
    {9, 15, 9, 9, 9},           //M
    {7, 13, 7, 5, 5},           //A
    {15, 10, 2, 2, 2},          //T
    {6, 5, 5, 6, 5},            //R
    {0, 2, 2, 2, 2},            //I
    {9, 9, 6, 9, 9},            //X
    {0, 0, 0, 0, 0},            //Random
    {0, 0, 0, 0, 0}
};                              //

int randcol, speed = 2, inverted = 0;

void
rotate_matrix ( int matrix[SIZE_X][SIZE_Y], int col )
{
    int buffer, y = 0, z;

    buffer = matrix[col][SIZE_Y - 1];
    if ( buffer == 0 )
        buffer = 9;
    else if ( buffer == 9 )
        buffer = 0;             // REverse
    z = SIZE_Y - 1;
    for ( y = ( SIZE_Y - 2 ); y >= 0; y-- )
    {
        matrix[col][z] = matrix[col][y];
        z--;
    }                           // rotate y down
    matrix[col][0] = buffer;
}

void
random_col ( int matrix[SIZE_X][SIZE_Y], int col )
{
    int y, rnd = lib_mod ( lib_rand ( SIZE_Y ), SIZE_Y - 1 );

    for ( y = 0; y < SIZE_Y; y++ )
    {
        if ( y == rnd )
            matrix[col][y] = 1;
        else if ( y == ( rnd + 1 ) )
            matrix[col][y] = 2;
        else if ( y > ( rnd + 1 ) )
            matrix[col][y] = 0;
        else
            matrix[col][y] = 9;
    }
}

void
move_matrix ( int matrix[SIZE_X][SIZE_Y] )
{
    int col, newrand, buffer;
    for ( col = 0; col < SIZE_X; col++ )
    {
        if ( matrix[col][0] == 3 )
        {
            matrix[randcol][0] = 3;
            matrix[randcol][6] = 1;
            matrix[randcol][7] = 2;
            random_col ( matrix, col );
            do
            {
                newrand = lib_mod ( lib_rand ( 100 ), SIZE_X );
            }
            while ( newrand == randcol );
            randcol = newrand;
            return;
        }
        if ( ( matrix[col][0] >= 4 ) && ( matrix[col][0] <= 8 ) )
        {
            matrix[randcol][0] = matrix[col][0];
            matrix[col][0] = 9;
            return;
        }
    }
}

void
random_code ( int code[6][5] )
{
    int cnt;
    for ( cnt = 0; cnt < 5; cnt++ )
        code[6][cnt] = lib_mod ( lib_rand ( 15 ), 15 );
}

void
draw_sign ( int code[6][5], int c, int x, int y )
{
    int gy;
    for ( gy = 0; gy < 5; gy++ )
    {
        if ( code[c][gy] & 8 )
            lcd_set_pixel ( x + 1, y + gy + 1, 1 );
        else
            lcd_set_pixel ( x + 1, y + gy + 1, 0 );
        if ( code[c][gy] & 4 )
            lcd_set_pixel ( x + 2, y + gy + 1, 1 );
        else
            lcd_set_pixel ( x + 2, y + gy + 1, 0 );
        if ( code[c][gy] & 2 )
            lcd_set_pixel ( x + 3, y + gy + 1, 1 );
        else
            lcd_set_pixel ( x + 3, y + gy + 1, 0 );
        if ( code[c][gy] & 1 )
            lcd_set_pixel ( x + 4, y + gy + 1, 1 );
        else
            lcd_set_pixel ( x + 4, y + gy + 1, 0 );
    };
}

// generates the menu for the apples
void
draw_matrix ( int matrix[SIZE_X][SIZE_Y] )
{
    int x, y, j, i, laby = 0;
    int gx, gy, cx, cy;

    for ( gy = 0; gy < SIZE_Y; gy++ )
    {
        for ( gx = 0; gx < SIZE_X; gx++ )
        {
            switch ( matrix[gx][gy] )
            {
                case 1:
                    x = 5 * gx;
                    y = 6 * gy;
                    random_code ( code );
                    draw_sign ( code, 6, x, y );
                    break;

                case 2:
                    x = 5 * gx;
                    y = 6 * gy;
                    random_code ( code );
                    draw_sign ( code, 6, x, y );
                    break;
                case 3:
                    x = 5 * gx;
                    y = 6 * gy;
                    draw_sign ( code, 0, x, y );    //M
                    break;
                case 4:
                    x = 5 * gx;
                    y = 6 * gy;
                    draw_sign ( code, 1, x, y );    //A
                    break;
                case 5:
                    x = 5 * gx;
                    y = 6 * gy;
                    draw_sign ( code, 2, x, y );    //T
                    break;
                case 6:
                    x = 5 * gx;
                    y = 6 * gy;
                    draw_sign ( code, 3, x, y );    //R
                    break;
                case 7:
                    x = 5 * gx;
                    y = 6 * gy;
                    draw_sign ( code, 4, x, y );    //I
                    break;
                case 8:
                    x = 5 * gx;
                    y = 6 * gy;
                    draw_sign ( code, 5, x, y );    //X
                    break;
                case 9:
                    x = 5 * gx;
                    y = 6 * gy;
                    draw_sign ( code, 7, x, y );    // delete sign
                    break;
                default:
                    break;
            };
        };
    };
    lcd_to_screen (  );
}

void
matrix_start ( void )
{
    int num, x, y, rot, col;
    unsigned char k;
    lcd_clr (  );
    do
    {
        randcol = lib_mod ( lib_rand ( SIZE_X ), SIZE_X );
    }
    while ( randcol == 6 );

    for ( y = 0; y < SIZE_Y; y++ )
        matrix[0][y] = y + 1;
    for ( col = 1; col < SIZE_X; col++ )
        random_col ( matrix, col );
    kpd_wait_release (  );
    while ( kpd_getkey (  ) == 0xff )
    {
        if ( inverted == 1 )
            lcd_set_mode ( LCD_MODE_INVERSE );
        for ( rot = 0; rot < SIZE_X; rot++ )
            rotate_matrix ( matrix, rot );
        move_matrix ( matrix );
        draw_matrix ( matrix );
        kpd_wait_release (  );
        usleep ( ( 300000 - speed * 20000 ) );
    }
    lcd_set_mode ( LCD_MODE_NORMAL );
}

matrix_mode ( void )
{
    unsigned char k;
    char *labymenu[] = { "normal   ", "inverted  ", "*back*", NULL };

    while ( 1 )
    {
        k = menu_main ( labymenu, inverted );
        kpd_wait_release (  );
        if ( k == 0xff )
            break;
        k++;
        if ( k == 0x3 )
            break;
        switch ( k )
        {
            case 0x1:
                inverted = 0;
                k = 0xff;
                break;
            case 0x2:
                inverted = 1;
                k = 0xff;
                break;
            default:
                break;
        }
        if ( k == 0xff )
            break;
        usleep ( 20000 );
    }

}

matrix_speed ( void )
{
    unsigned char k;

    while ( 1 )
    {
        lcd_clr (  );
        lcd_render_text ( 0, 0 * 8 + 1, "  select", 1 );
        lcd_render_text ( 0, 1 * 8 + 1, "  speed", 1 );
        lcd_draw_line ( 13, 22, 67, 22, 1 );    //1 waag
        lcd_draw_line ( 13, 30, 67, 30, 1 );    //2 waag
        lcd_draw_line ( 13, 22, 13, 30, 1 );    //1 senk
        lcd_draw_line ( 67, 22, 67, 30, 1 );    //2 senk
        for ( k = 0; k <= 4; k++ )
            lcd_draw_line ( 15, 24 + k, 20 + 5 * speed, 24 + k, 1 );
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
                if ( speed != 0 )
                    speed--;
                kpd_wait_release (  );
                break;
            case KPD_UPARROW:
                if ( speed < 9 )
                    speed++;
                kpd_wait_release (  );
                break;
            default:
                break;
        }
        usleep ( 20000 );
    }

}

// the matrix main menu
void
matrix_main ( void )
{
    char *matrixmenu[] = { "1- start", "2- speed", "3- mode", "4- *back*", NULL };
    unsigned char key;

    while ( 1 )
    {
        key = menu_main ( matrixmenu, 0 );
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
//              lcd_type_text_2 ( 0, 3*8, 3, "starting", 1 );
                matrix_start (  );
                kpd_wait_release (  );
                break;
            case 0x2:
                matrix_speed (  );  // speed
                kpd_wait_release (  );
                break;
            case 0x3:
                matrix_mode (  );   // change inverted mode
                kpd_wait_release (  );
                break;
            default:
                break;
        }
    }
}
