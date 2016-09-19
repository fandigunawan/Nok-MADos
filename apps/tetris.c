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
#include <hw/kpd.h>
#include <hw/lcd.h>
#include <core/lib.h>
#include <hw/ccont.h>
#include <apps/tetris.h>
#include <hw/buzzer.h>
#include <apps/tetris_sound.h>
#include <core/menu.h>
#include <core/sched.h>


//********************************************* DEFS
//*********************************************

#define UWIDTH          10
#define UHEIGHT         15

#define VUNIT           3       /* ver unit */
#define HUNIT		3           /* hor unit */
#define NORM_OFFSET	1           /* x offset for blocks */
#define NEXT_HEIGHT	(VUNIT*5)   /* Height for next block */

#define WHITE		0
#define BLACK		1



static int beep = 1;
static int beginlev = 0;
static int blockdesign = 0;
static char timings[] = { 6, 6, 5, 5, 4, 4, 4, 3, 3, 3 };
static char blockbmp[3][9] = { {1, 1, 1, 1, 0, 1, 1, 1, 1}, {1, 0, 1, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1} };

int gameover;
int shape_no;                   /* the dripping shape */
int xpos, ypos, rot;            /* x, y, rotation of shape_no */
int score;                      /* current score */
int rows;                       /* number of rows deleted */
int next_no;                    /* next shape */
int next_rot;                   /* rotation of next shape */
//char  *name;          /* username */
//int   score_position;     /* position of this game in the hiscore tab */
unsigned char total_shapes;     /* number of used shapes (7 normal) (10 extra) */
unsigned char sndthread;

unsigned char grid[UWIDTH][UHEIGHT];

struct shape_table
{
    int table[4][4];
    int width;
    int height;
    int offset;
    int pointv[4];
    //char    color;
}
shape[10];

struct shape
{
    int shape;
    int rot;
    int width;
    int height;
    int offset;
    int pointv;
    //char    color;
    int was_shown;
    int was_shadowed;
};

//********************************************* MAIN
//*********************************************

void
tetris_main ( void )
{
    kpd_mode ( KPD_UNBUFFERED );
    tetris_define_shapes (  );

    char *tetrismenu[] = { "1- tetris", "2- blocks", "3- design", "4- *back*", NULL };
    unsigned char key;
    total_shapes = 7;

    while ( 1 )
    {
        key = menu_main ( tetrismenu, 0 );
        kpd_wait_release (  );
        if ( key == 0xff )
            break;
        key++;
        if ( key == 0x4 )
            break;
        switch ( key )
        {
            case 0x1:
                tetris_init_game (  );
                tetris_loop (  );
                kpd_wait_release (  );
                break;
            case 0x2:
                tetris_chg_shapes (  );
                kpd_wait_release (  );
                break;
            case 0x3:
                tetris_chg_design (  );
                kpd_wait_release (  );
                break;
            default:
                break;
        }
    }
}

void
tetris_chg_shapes ( void )
{
    unsigned char k;
    char *shapemenu[] = { "7 blocks", "10 blocks", "*back*", NULL };

    while ( 1 )
    {
        k = menu_main ( shapemenu, 0 );
        kpd_wait_release (  );
        if ( k == 0xff )
            break;
        k++;
        if ( k == 0x3 )
            break;
        switch ( k )
        {
            case 0x1:
                total_shapes = 7;
                k = 0xff;
                break;
            case 0x2:
                total_shapes = 10;
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
tetris_chg_design ( void )
{
    unsigned char k;
    char *shapemenu[] = { "Design 1", "Design 2", "*back*", NULL };

    while ( 1 )
    {
        k = menu_main ( shapemenu, 0 );
        kpd_wait_release (  );
        if ( k == 0xff )
            break;
        k++;
        if ( k == 0x3 )
            break;
        switch ( k )
        {
            case 0x1:
                blockdesign = 0;
                k = 0xff;
                break;
            case 0x2:
                blockdesign = 1;
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
tetris_init_game ( void )
{
    int i, j;

    //score_position = -1;
    rows = score = shape_no = rot = xpos = ypos = 0;
    for ( i = 0; i < UWIDTH; i++ )
        for ( j = 0; j < UHEIGHT; j++ )
            grid[i][j] = 0;
    tetris_create_shape (  );   /* Set up 1st shape */
    tetris_create_shape (  );   /* Set up next shape */

    lcd_clr (  );
    lcd_draw_rect ( 0, 0, ( UWIDTH + 2 ) * HUNIT - 1, ( UHEIGHT + 1 ) * VUNIT - 1, BLACK );
    lcd_draw_rect ( HUNIT, 0, ( UWIDTH + 1 ) * HUNIT - 1, UHEIGHT * VUNIT - 1, WHITE );
    tetris_show_score (  );
    tetris_show_next (  );
}


void
tetris_sound_thread ( void )
{
    buzzer_snd_play ( tetris_snd_line, sizeof ( tetris_snd_line ) );
    return;
}


void
tetris_loop ( void )
{
    unsigned char j, key, dlyloop = 0;

    gameover = 0;

    while ( !gameover )
    {
        usleep ( 50000 );
        dlyloop++;
        j = kpd_getkey (  );
        if ( j == key )
            key = 0xFF;
        else
            key = j;
        if ( key == KPD_CANCEL )
            break;
        switch ( key )
        {
            case 0x0:
                kpd_wait_release (  );
                lcd_draw_rect ( 42, 20 - 8, 42 + 5 * 8, 20, WHITE );
                lcd_render_text ( 42, 20 - 8, "pause", BLACK );
                lcd_to_screen (  );
                kpd_wait_keypress (  );
                lcd_draw_rect ( 42, 20 - 8, 42 + 5 * 8, 20, WHITE );
                lcd_to_screen (  );
                kpd_wait_release (  );
                break;
            case 0x5:
            case 0x8:
                tetris_fast_proc (  );
                break;
            case 0x1:
            case 0x4:
                tetris_left_proc (  );
                break;
            case 0x3:
            case 0x6:
                tetris_right_proc (  );
                break;
            case 0x2:
            case KPD_DWNARROW:
                tetris_anti_proc (  );
                break;
            default:
                break;
        }
        if ( dlyloop == timings[tetris_level (  )] )
        {
            dlyloop = 0;
            tetris_drop_block (  );
        }

    }
    //sched_remove ( sndthread );
}


void
tetris_drop_block ( void )
{
    int orows;

    if ( tetris_block_can_drop ( shape_no, xpos, ypos, rot ) )
        tetris_print_shape ( shape_no, xpos + NORM_OFFSET, ypos++, rot, WHITE );
    else
    {
        if ( ypos < 0 )
            tetris_end_game (  );
        else
        {
            orows = rows;
            score += shape[shape_no].pointv[rot];
            tetris_store_shape ( shape_no, xpos, ypos, rot );
            tetris_remove_full_lines ( ypos );
            tetris_create_shape (  );
            tetris_show_score (  );
            tetris_show_next (  );
            if ( orows != rows )
                buzzer_snd_play ( tetris_snd_line, sizeof ( tetris_snd_line ) );
            //sndthread = sched_add ( ( unsigned int ) tetris_sound_thread, 1, SCHED_PARM_RUN );
        }
    }
    tetris_print_shape ( shape_no, xpos + NORM_OFFSET, ypos, rot, BLACK );
}

void
tetris_show_score ( void )
{
    char score_buf[6], level_buf[3], rows_buf[4];

    lib_dtoa ( score_buf, score, 5, 0 );
    lib_dtoa ( level_buf, beginlev + 1 + lib_div ( rows, 10 ), 2, 0 );
    lib_dtoa ( rows_buf, rows, 3, 0 );

    lcd_draw_rect ( 42, 20 + 0 * 8, 42 + 5 * 8, 20 + 1 * 8, WHITE );
    lcd_draw_rect ( 42, 20 + 1 * 8, 42 + 5 * 8, 20 + 2 * 8, WHITE );
    lcd_draw_rect ( 42 + 4, 20 + 2 * 8, 42 + 4 + 4 * 8, 20 + 3 * 8, WHITE );

    if ( score == 0 )
    {
        lcd_render_text ( 42, 20 + 0 * 8, "score", 1 );
        lcd_render_text ( 42, 20 + 1 * 8, "level", 1 );
        lcd_render_text ( 42 + 4, 20 + 2 * 8, "rows", 1 );
    }
    else
    {
        lcd_render_text ( 42, 20 + 0 * 8, score_buf, BLACK );
        lcd_render_text ( 50 + 4, 20 + 1 * 8, level_buf, BLACK );
        lcd_render_text ( 50, 20 + 2 * 8, rows_buf, BLACK );
    }
}

void
tetris_end_game ( void )
{
    gameover = 1;
    kpd_wait_release (  );
    lcd_draw_rect ( 4, 20, 80, 28, WHITE );
    lcd_render_text ( 5, 20, "Game Over!", BLACK );
    lcd_to_screen (  );
    kpd_wait_release (  );
    buzzer_snd_play ( tetris_snd_gameover, sizeof ( tetris_snd_gameover ) );
    kpd_wait_release (  );
}

void
tetris_left_proc ( void )
{
    if ( tetris_block_can_left ( shape_no, xpos, ypos, rot ) )
    {
        tetris_print_shape ( shape_no, xpos + NORM_OFFSET, ypos, rot, WHITE );
        xpos--;
        tetris_print_shape ( shape_no, xpos + NORM_OFFSET, ypos, rot, BLACK );
    }
}

void
tetris_right_proc ( void )
{
    if ( tetris_block_can_right ( shape_no, xpos, ypos, rot ) )
    {
        tetris_print_shape ( shape_no, xpos + NORM_OFFSET, ypos, rot, WHITE );
        xpos++;
        tetris_print_shape ( shape_no, xpos + NORM_OFFSET, ypos, rot, BLACK );
    }
}

void
tetris_anti_proc ( void )
{
    int newrot;

    newrot = lib_mod ( ( rot + 3 ), 4 );
    if ( tetris_check_rot ( shape_no, xpos, ypos, newrot ) )
    {
        tetris_print_shape ( shape_no, xpos + NORM_OFFSET, ypos, rot, WHITE );
        rot = newrot;
        tetris_print_shape ( shape_no, xpos + NORM_OFFSET, ypos, rot, BLACK );
    }
}

void
tetris_clock_proc ( void )
{
    int newrot;

    newrot = lib_mod ( ( rot + 1 ), 4 );
    if ( tetris_check_rot ( shape_no, xpos, ypos, newrot ) )
    {
        tetris_print_shape ( shape_no, xpos + NORM_OFFSET, ypos, rot, WHITE );
        rot = newrot;
        tetris_print_shape ( shape_no, xpos + NORM_OFFSET, ypos, rot, BLACK );
    }
}

void
tetris_fast_proc ( void )
{
    while ( tetris_block_can_drop ( shape_no, xpos, ypos, rot ) && kpd_getkey (  ) != 0xFF )
    {
        tetris_print_shape ( shape_no, xpos + NORM_OFFSET, ypos, rot, WHITE );
        ypos++;
        tetris_print_shape ( shape_no, xpos + NORM_OFFSET, ypos, rot, BLACK );
        usleep ( 50000 );
    }
}


/*	Drawing primitives
 */
void
tetris_show_next ( void )
{
    //lcd_draw_rect ( 38, 2, 52, 16, BLACK );
    lcd_draw_rect ( 39, 3, 51, 15, WHITE );
    tetris_print_shape ( next_no, 13, 1, next_rot, BLACK );
}

void
tetris_print_shape ( int shape_no, int x, int y, int rot, int col )
{
    int x1, x2, x3, x4, y1;
    int t0, t1, t2, t3;

    t0 = shape[shape_no].table[0][rot]; /* Bit map of 1st Row */
    t1 = shape[shape_no].table[1][rot]; /* Bit map of 2nd Row */
    t2 = shape[shape_no].table[2][rot]; /* Bit map of 3rd Row */
    t3 = shape[shape_no].table[3][rot]; /* Bit map of 4th Row */

    x1 = x;                     /* Position of 1st column of block grid */
    x2 = x1 + 1;                /* Position of 2nd column of block grid */
    x3 = x2 + 1;                /* Position of 3rd column of block grid */
    x4 = x3 + 1;                /* Position of 4th column of block grid */
    y1 = y;                     /* Position of 1st row of block grid    */

    if ( y > -1 )
    {
        if ( t0 & 8 )
            tetris_set1pixel ( x1, y1, col );
        if ( t0 & 4 )
            tetris_set1pixel ( x2, y1, col );
        if ( t0 & 2 )
            tetris_set1pixel ( x3, y1, col );
        if ( t0 & 1 )
            tetris_set1pixel ( x4, y1, col );
    }
    y1 += 1;                    /* Position of next row */
    if ( y > -2 )
    {
        if ( t1 & 8 )
            tetris_set1pixel ( x1, y1, col );
        if ( t1 & 4 )
            tetris_set1pixel ( x2, y1, col );
        if ( t1 & 2 )
            tetris_set1pixel ( x3, y1, col );
        if ( t1 & 1 )
            tetris_set1pixel ( x4, y1, col );
    }
    y1 += 1;                    /* Position of next row */
    if ( y > -3 )
    {
        if ( t2 & 8 )
            tetris_set1pixel ( x1, y1, col );
        if ( t2 & 4 )
            tetris_set1pixel ( x2, y1, col );
        if ( t2 & 2 )
            tetris_set1pixel ( x3, y1, col );
        if ( t2 & 1 )
            tetris_set1pixel ( x4, y1, col );
    }
    y1 += 1;                    /* Position of next row */
    if ( y > -4 )
    {
        if ( t3 & 8 )
            tetris_set1pixel ( x1, y1, col );
        if ( t3 & 4 )
            tetris_set1pixel ( x2, y1, col );
        if ( t3 & 2 )
            tetris_set1pixel ( x3, y1, col );
        if ( t3 & 1 )
            tetris_set1pixel ( x4, y1, col );
    }
    lcd_to_screen (  );
}

/*	LCD routines
 */


void
tetris_set1pixel ( int x, int y, int col )
{
    int i, j;
    if ( col == BLACK )
        for ( i = 0; i < 3; i++ )
            for ( j = 0; j < 3; j++ )
                lcd_set_pixel ( x * HUNIT + j, y * VUNIT + i, blockbmp[blockdesign][3 * i + j] );
    else
        lcd_draw_rect ( x * HUNIT, y * VUNIT, x * HUNIT + 2, y * VUNIT + 2, WHITE );
}


void
tetris_print_all_blocks ( void )
{
    int i, j;

    lcd_draw_rect ( HUNIT, 0, ( UWIDTH + 1 ) * HUNIT - 1, UHEIGHT * VUNIT - 1, WHITE );
    for ( i = 0; i < UHEIGHT; i++ )
        for ( j = 0; j < UWIDTH; j++ )
            if ( grid[j][i] )
                tetris_set1pixel ( j + NORM_OFFSET, i, BLACK );

}

//********************************************* SHAPE
//*********************************************

void
tetris_define_shapes ( void )
{

    /*
     * begin shape 0 definition, four rotations 
     */

    shape[0].table[0][0] = 0;
    shape[0].table[1][0] = 15;  /* #### */
    shape[0].table[2][0] = 0;
    shape[0].table[3][0] = 0;
    shape[0].pointv[0] = 5;

    shape[0].table[0][1] = 4;   /*  #   */
    shape[0].table[1][1] = 4;   /*  #   */
    shape[0].table[2][1] = 4;   /*  #   */
    shape[0].table[3][1] = 4;   /*  #   */
    shape[0].pointv[1] = 8;

    shape[0].table[0][2] = 0;
    shape[0].table[1][2] = 15;  /* #### */
    shape[0].table[2][2] = 0;
    shape[0].table[3][2] = 0;
    shape[0].pointv[2] = 5;

    shape[0].table[0][3] = 4;   /*  #    */
    shape[0].table[1][3] = 4;   /*  #    */
    shape[0].table[2][3] = 4;   /*  #    */
    shape[0].table[3][3] = 4;   /*  #    */
    shape[0].pointv[3] = 8;

    shape[0].width = 4;
    shape[0].height = 1;
    shape[0].offset = 153;
    //shape[0].color = RED;

    /*
     * begin shape 1 definition, four rotations 
     */

    shape[1].table[0][0] = 12;  /* ##   */
    shape[1].table[1][0] = 12;  /* ##   */
    shape[1].table[2][0] = 0;   /*      */
    shape[1].table[3][0] = 0;   /*      */
    shape[1].pointv[0] = 6;

    shape[1].table[0][1] = 12;  /* ##   */
    shape[1].table[1][1] = 12;  /* ##   */
    shape[1].table[2][1] = 0;   /*      */
    shape[1].table[3][1] = 0;   /*      */
    shape[1].pointv[1] = 6;

    shape[1].table[0][2] = 12;  /* ##   */
    shape[1].table[1][2] = 12;  /* ##   */
    shape[1].table[2][2] = 0;   /*      */
    shape[1].table[3][2] = 0;   /*      */
    shape[1].pointv[2] = 6;

    shape[1].table[0][3] = 12;  /* ##   */
    shape[1].table[1][3] = 12;  /* ##   */
    shape[1].table[2][3] = 0;   /*      */
    shape[1].table[3][3] = 0;   /*      */
    shape[1].pointv[3] = 6;

    shape[1].width = 2;
    shape[1].height = 2;
    shape[1].offset = 0;
    //shape[1].color = ORANGE;

    /*
     * begin shape 2 definition, four rotations 
     */

    shape[2].table[0][0] = 4;   /*  #  */
    shape[2].table[1][0] = 14;  /* ### */
    shape[2].table[2][0] = 0;   /*     */
    shape[2].table[3][0] = 0;   /*     */
    shape[2].pointv[0] = 5;

    shape[2].table[0][1] = 4;   /*  #  */
    shape[2].table[1][1] = 6;   /*  ## */
    shape[2].table[2][1] = 4;   /*  #  */
    shape[2].table[3][1] = 0;   /*     */
    shape[2].pointv[1] = 5;

    shape[2].table[0][2] = 0;   /*     */
    shape[2].table[1][2] = 14;  /* ### */
    shape[2].table[2][2] = 4;   /*  #  */
    shape[2].table[3][2] = 0;   /*     */
    shape[2].pointv[2] = 6;

    shape[2].table[0][3] = 4;   /*  #  */
    shape[2].table[1][3] = 12;  /* ##  */
    shape[2].table[2][3] = 4;   /*  #  */
    shape[2].table[3][3] = 0;   /*     */
    shape[2].pointv[3] = 5;

    shape[2].width = 3;
    shape[2].height = 2;
    shape[2].offset = 24;
    //shape[2].color = YELLOW;

    /*
     * begin shape 3 definition, four rotations 
     */

    shape[3].table[0][0] = 12;  /* ##  */
    shape[3].table[1][0] = 6;   /*  ## */
    shape[3].table[2][0] = 0;   /*     */
    shape[3].table[3][0] = 0;   /*     */
    shape[3].pointv[0] = 6;

    shape[3].table[0][1] = 4;   /*  #  */
    shape[3].table[1][1] = 12;  /* ##  */
    shape[3].table[2][1] = 8;   /* #   */
    shape[3].table[3][1] = 0;   /*     */
    shape[3].pointv[1] = 7;

    shape[3].table[0][2] = 12;  /* ##  */
    shape[3].table[1][2] = 6;   /*  ## */
    shape[3].table[2][2] = 0;   /*     */
    shape[3].table[3][2] = 0;   /*     */
    shape[3].pointv[2] = 6;

    shape[3].table[0][3] = 4;   /*  #  */
    shape[3].table[1][3] = 12;  /* ##  */
    shape[3].table[2][3] = 8;   /* #   */
    shape[3].table[3][3] = 0;   /*     */
    shape[3].pointv[3] = 7;

    shape[3].width = 3;
    shape[3].height = 2;
    shape[3].offset = 0;
    //shape[3].color = GREEN;

    /*
     * begin shape 4 definition, four rotations 
     */

    shape[4].table[0][0] = 6;   /*  ## */
    shape[4].table[1][0] = 12;  /* ##  */
    shape[4].table[2][0] = 0;   /*     */
    shape[4].table[3][0] = 0;   /*     */
    shape[4].pointv[0] = 6;

    shape[4].table[0][1] = 8;   /* #   */
    shape[4].table[1][1] = 12;  /* ##  */
    shape[4].table[2][1] = 4;   /*  #  */
    shape[4].table[3][1] = 0;   /*     */
    shape[4].pointv[1] = 7;

    shape[4].table[0][2] = 6;   /*  ## */
    shape[4].table[1][2] = 12;  /* ##  */
    shape[4].table[2][2] = 0;   /*     */
    shape[4].table[3][2] = 0;   /*     */
    shape[4].pointv[2] = 6;

    shape[4].table[0][3] = 8;   /* #   */
    shape[4].table[1][3] = 12;  /* ##  */
    shape[4].table[2][3] = 4;   /*  #  */
    shape[4].table[3][3] = 0;   /*     */
    shape[4].pointv[3] = 7;

    shape[4].width = 3;
    shape[4].height = 2;
    shape[4].offset = 0;
    //shape[4].color = BLUE;

    /*
     * begin shape 5 definition, four rotations 
     */

    shape[5].table[0][0] = 2;   /*   # */
    shape[5].table[1][0] = 14;  /* ### */
    shape[5].table[2][0] = 0;   /*     */
    shape[5].table[3][0] = 0;   /*     */
    shape[5].pointv[0] = 6;

    shape[5].table[0][1] = 8;   /* #   */
    shape[5].table[1][1] = 8;   /* #   */
    shape[5].table[2][1] = 12;  /* ##  */
    shape[5].table[3][1] = 0;   /*     */
    shape[5].pointv[1] = 7;

    shape[5].table[0][2] = 14;  /* ### */
    shape[5].table[1][2] = 8;   /* #   */
    shape[5].table[2][2] = 0;   /*     */
    shape[5].table[3][2] = 0;   /*     */
    shape[5].pointv[2] = 6;

    shape[5].table[0][3] = 12;  /* ##  */
    shape[5].table[1][3] = 4;   /*  #  */
    shape[5].table[2][3] = 4;   /*  #  */
    shape[5].table[3][3] = 0;   /*     */
    shape[5].pointv[3] = 7;

    shape[5].width = 3;
    shape[5].height = 2;
    shape[5].offset = 0;
    //shape[5].color = CYAN;

    /*
     * begin shape 6 definition, four rotations 
     */

    shape[6].table[0][0] = 14;  /* ### */
    shape[6].table[1][0] = 2;   /*   # */
    shape[6].table[2][0] = 0;   /*     */
    shape[6].table[3][0] = 0;   /*     */
    shape[6].pointv[0] = 6;

    shape[6].table[0][1] = 4;   /*  #  */
    shape[6].table[1][1] = 4;   /*  #  */
    shape[6].table[2][1] = 12;  /* ##  */
    shape[6].table[3][1] = 0;   /*     */
    shape[6].pointv[1] = 7;

    shape[6].table[0][2] = 8;   /* #   */
    shape[6].table[1][2] = 14;  /* ### */
    shape[6].table[2][2] = 0;   /*     */
    shape[6].table[3][2] = 0;   /*     */
    shape[6].pointv[2] = 6;

    shape[6].table[0][3] = 12;  /* ##  */
    shape[6].table[1][3] = 8;   /* #   */
    shape[6].table[2][3] = 8;   /* #   */
    shape[6].table[3][3] = 0;   /*     */
    shape[6].pointv[3] = 7;

    shape[6].width = 3;
    shape[6].height = 2;
    shape[6].offset = 0;
    //shape[6].color = VIOLET;

    /*
     * begin shape 7 definition, four rotations 
     */

    shape[7].table[0][0] = 8;   /* #   */
    shape[7].table[1][0] = 0;   /*     */
    shape[7].table[2][0] = 0;   /*     */
    shape[7].table[3][0] = 0;   /*     */
    shape[7].pointv[0] = 2;

    shape[7].table[0][1] = 8;   /* #   */
    shape[7].table[1][1] = 0;   /*     */
    shape[7].table[2][1] = 0;   /*     */
    shape[7].table[3][1] = 0;   /*     */
    shape[7].pointv[1] = 2;

    shape[7].table[0][2] = 8;   /* #   */
    shape[7].table[1][2] = 0;   /*     */
    shape[7].table[2][2] = 0;   /*     */
    shape[7].table[3][2] = 0;   /*     */
    shape[7].pointv[2] = 2;

    shape[7].table[0][3] = 8;   /* #   */
    shape[7].table[1][3] = 0;   /*     */
    shape[7].table[2][3] = 0;   /*     */
    shape[7].table[3][3] = 0;   /*     */
    shape[7].pointv[3] = 2;

    shape[7].width = 1;
    shape[7].height = 1;
    shape[7].offset = 0;
    //shape[7].color = VIOLET;

    /*
     * begin shape 8 definition, four rotations 
     */

    shape[8].table[0][0] = 12;  /* ## */
    shape[8].table[1][0] = 4;   /*  # */
    shape[8].table[2][0] = 0;   /*     */
    shape[8].table[3][0] = 0;   /*     */
    shape[8].pointv[0] = 4;

    shape[8].table[0][1] = 4;   /*  #  */
    shape[8].table[1][1] = 12;  /* ##  */
    shape[8].table[2][1] = 0;   /*     */
    shape[8].table[3][1] = 0;   /*     */
    shape[8].pointv[1] = 3;

    shape[8].table[0][2] = 8;   /* #   */
    shape[8].table[1][2] = 12;  /* ##  */
    shape[8].table[2][2] = 0;   /*     */
    shape[8].table[3][2] = 0;   /*     */
    shape[8].pointv[2] = 3;

    shape[8].table[0][3] = 12;  /* ##  */
    shape[8].table[1][3] = 8;   /* #   */
    shape[8].table[2][3] = 0;   /*     */
    shape[8].table[3][3] = 0;   /*     */
    shape[8].pointv[3] = 4;

    shape[8].width = 2;
    shape[8].height = 2;
    shape[8].offset = 0;
    //shape[8].color = VIOLET;

    /*
     * begin shape 9 definition, four rotations 
     */

    shape[9].table[0][0] = 14;  /* ### */
    shape[9].table[1][0] = 0;   /*     */
    shape[9].table[2][0] = 0;   /*     */
    shape[9].table[3][0] = 0;   /*     */
    shape[9].pointv[0] = 5;

    shape[9].table[0][1] = 4;   /*  #  */
    shape[9].table[1][1] = 4;   /*  #  */
    shape[9].table[2][1] = 4;   /*  #  */
    shape[9].table[3][1] = 0;   /*     */
    shape[9].pointv[1] = 5;

    shape[9].table[0][2] = 14;  /* ### */
    shape[9].table[1][2] = 0;   /*     */
    shape[9].table[2][2] = 0;   /*     */
    shape[9].table[3][2] = 0;   /*     */
    shape[9].pointv[2] = 5;

    shape[9].table[0][3] = 4;   /*  #  */
    shape[9].table[1][3] = 4;   /*  #  */
    shape[9].table[2][3] = 4;   /*  #  */
    shape[9].table[3][3] = 0;   /*     */
    shape[9].pointv[3] = 5;

    shape[9].width = 3;
    shape[9].height = 1;
    shape[9].offset = 0;
    //shape[9].color = VIOLET;

}

void
tetris_store_shape ( int shape_no, int xpos, int ypos, int rot )
{
    int i;

    for ( i = 0; i < 4; i++ )
    {
        if ( shape[shape_no].table[i][rot] & 8 )
            grid[xpos][ypos + i] = 1;
        if ( shape[shape_no].table[i][rot] & 4 )
            grid[xpos + 1][ypos + i] = 1;
        if ( shape[shape_no].table[i][rot] & 2 )
            grid[xpos + 2][ypos + i] = 1;
        if ( shape[shape_no].table[i][rot] & 1 )
            grid[xpos + 3][ypos + i] = 1;
    }
}

void
tetris_create_shape ( void )
{
    shape_no = next_no;
    rot = next_rot;
    next_no = lib_mod ( lib_rand ( score * 123 ), total_shapes );
    next_rot = lib_mod ( lib_rand ( score * 234 ), 4 );
    xpos = ( UWIDTH >> 1 ) - 1;
    ypos = -4;
}

//********************************************* SUPPORT
//*********************************************

int
tetris_level ( void )
{
    int level;
    level = lib_div ( rows, 10 ) + beginlev;
    if ( level >= sizeof ( timings ) )
        level = sizeof ( timings ) - 1;
    return level;
}


int
tetris_block_can_drop ( int shape_no, int xpos, int ypos, int rot )
{
    int y1, c;

    c = 3;

    while ( ( c >= 0 ) && ( ( shape[shape_no].table[c][rot] & 8 ) == 0 ) )
        c--;
    y1 = ypos + c + 1;
    if ( ( c != -1 ) && ( y1 >= 0 ) )
        if ( ( y1 == UHEIGHT ) || ( grid[xpos][y1] != 0 ) )
            return ( 0 );

    c = 3;
    while ( ( c >= 0 ) && ( ( shape[shape_no].table[c][rot] & 4 ) == 0 ) )
        c--;
    y1 = ypos + c + 1;
    if ( ( c != -1 ) && ( y1 >= 0 ) )
        if ( ( y1 == UHEIGHT ) || ( grid[xpos + 1][y1] != 0 ) )
            return ( 0 );

    c = 3;
    while ( ( c >= 0 ) && ( ( shape[shape_no].table[c][rot] & 2 ) == 0 ) )
        c--;
    y1 = ypos + c + 1;
    if ( ( c != -1 ) && ( y1 >= 0 ) )
        if ( ( y1 == UHEIGHT ) || ( grid[xpos + 2][y1] != 0 ) )
            return ( 0 );

    c = 3;
    while ( ( c >= 0 ) && ( ( shape[shape_no].table[c][rot] & 1 ) == 0 ) )
        c--;
    y1 = ypos + c + 1;
    if ( ( c != -1 ) && ( y1 >= 0 ) )
        if ( ( y1 == UHEIGHT ) || ( grid[xpos + 3][y1] != 0 ) )
            return ( 0 );

    return 1;
}

int
tetris_block_can_left ( int shape_no, int xpos, int ypos, int rot )
{
    int x1, c;
    int y0, y1, y2, y3;
    int t0, t1, t2, t3;

    t0 = shape[shape_no].table[0][rot]; /* Bit map of 1st Row */
    t1 = shape[shape_no].table[1][rot]; /* Bit map of 2nd Row */
    t2 = shape[shape_no].table[2][rot]; /* Bit map of 3rd Row */
    t3 = shape[shape_no].table[3][rot]; /* Bit map of 4th Row */

    y0 = ypos;
    y1 = ypos + 1;
    y2 = ypos + 2;
    y3 = ypos + 3;

    c = 3;
    while ( ( c >= 0 ) && ( ( t0 & ( 1 << c ) ) == 0 ) )
        c--;
    x1 = xpos - 1 + ( 3 - c );
    if ( c != -1 )
        if ( ( x1 < 0 ) || ( ( y0 >= 0 ) && ( grid[x1][y0] != 0 ) ) )
            return ( 0 );

    c = 3;
    while ( ( c >= 0 ) && ( ( t1 & ( 1 << c ) ) == 0 ) )
        c--;
    x1 = xpos - 1 + ( 3 - c );
    if ( c != -1 )
        if ( ( x1 < 0 ) || ( ( y1 >= 0 ) && ( grid[x1][y1] != 0 ) ) )
            return ( 0 );

    c = 3;
    while ( ( c >= 0 ) && ( ( t2 & ( 1 << c ) ) == 0 ) )
        c--;
    x1 = xpos - 1 + ( 3 - c );
    if ( c != -1 )
        if ( ( x1 < 0 ) || ( ( y2 >= 0 ) && ( grid[x1][y2] != 0 ) ) )
            return ( 0 );

    c = 3;
    while ( ( c >= 0 ) && ( ( t3 & ( 1 << c ) ) == 0 ) )
        c--;
    x1 = xpos - 1 + ( 3 - c );
    if ( c != -1 )
        if ( ( x1 < 0 ) || ( ( y3 >= 0 ) && ( grid[x1][y3] != 0 ) ) )
            return ( 0 );

    return 1;
}

int
tetris_block_can_right ( int shape_no, int xpos, int ypos, int rot )
{
    int x1, c;
    int y0, y1, y2, y3;
    int t0, t1, t2, t3;

    t0 = shape[shape_no].table[0][rot]; /* Bit map of 1st Row */
    t1 = shape[shape_no].table[1][rot]; /* Bit map of 2nd Row */
    t2 = shape[shape_no].table[2][rot]; /* Bit map of 3rd Row */
    t3 = shape[shape_no].table[3][rot]; /* Bit map of 4th Row */

    y0 = ypos;
    y1 = ypos + 1;
    y2 = ypos + 2;
    y3 = ypos + 3;

    c = 0;
    while ( ( c < 4 ) && ( ( t0 & ( 1 << c ) ) == 0 ) )
        c++;
    x1 = xpos + 1 + ( 3 - c );
    if ( ( c != 4 ) && ( x1 >= 0 ) )
        if ( ( x1 == UWIDTH ) || ( ( y0 >= 0 ) && ( grid[x1][y0] != 0 ) ) )
            return ( 0 );

    c = 0;
    while ( ( c < 4 ) && ( ( t1 & ( 1 << c ) ) == 0 ) )
        c++;
    x1 = xpos + 1 + ( 3 - c );
    if ( ( c != 4 ) && ( x1 >= 0 ) )
        if ( ( x1 == UWIDTH ) || ( ( y1 >= 0 ) && ( grid[x1][y1] != 0 ) ) )
            return ( 0 );

    c = 0;
    while ( ( c < 4 ) && ( ( t2 & ( 1 << c ) ) == 0 ) )
        c++;
    x1 = xpos + 1 + ( 3 - c );
    if ( ( c != 4 ) && ( x1 >= 0 ) )
        if ( ( x1 == UWIDTH ) || ( ( y2 >= 0 ) && ( grid[x1][y2] != 0 ) ) )
            return ( 0 );

    c = 0;
    while ( ( c < 4 ) && ( ( t3 & ( 1 << c ) ) == 0 ) )
        c++;
    x1 = xpos + 1 + ( 3 - c );
    if ( ( c != 4 ) && ( x1 >= 0 ) )
        if ( ( x1 == UWIDTH ) || ( ( y3 >= 0 ) && ( grid[x1][y3] != 0 ) ) )
            return ( 0 );

    return 1;
}

void
tetris_remove_full_lines ( int y )
{
    int y1, y2, x;

    for ( y1 = y; y1 < y + 4 && y1 < UHEIGHT; y1++ )
    {
        for ( x = 0; x < UWIDTH; x++ )
            if ( grid[x][y1] == 0 )
                break;
        if ( x == UWIDTH )
        {
            for ( y2 = y1; y2 > 0; y2-- )
                for ( x = 0; x < UWIDTH; x++ )
                    grid[x][y2] = grid[x][y2 - 1];
            for ( x = 0; x < UWIDTH; x++ )
                grid[x][0] = 0;
            tetris_print_all_blocks (  );
            rows++;
        }
    }
}

int
tetris_check_rot ( int shape_no, int xpos, int ypos, int newrot )
{
    int i;
    int ti;                     /* Bit map of i'th row    */
    int yi;                     /* Y position on i'th row */
    int x0, x1, x2, x3;

    x0 = xpos;
    x1 = xpos + 1;
    x2 = xpos + 2;
    x3 = xpos + 3;
    yi = ypos;

    for ( i = 0; i < 4; yi++, i++ )
    {
        if ( ( yi ) >= 0 )
        {
            ti = shape[shape_no].table[i][newrot];
            if ( ti & 8 )
                if ( ( x0 < 0 ) || ( x0 >= UWIDTH ) || ( grid[x0][yi] == 1 ) )
                    return 0;
            if ( ti & 4 )
                if ( ( x1 < 0 ) || ( x1 >= UWIDTH ) || ( grid[x1][yi] == 1 ) )
                    return 0;
            if ( ti & 2 )
                if ( ( x2 < 0 ) || ( x2 >= UWIDTH ) || ( grid[x2][yi] == 1 ) )
                    return 0;
            if ( ti & 1 )
                if ( ( x3 < 0 ) || ( x3 >= UWIDTH ) || ( grid[x3][yi] == 1 ) )
                    return 0;
        }
    }
    return 1;
}

//*********************************************
//*********************************************

#endif
