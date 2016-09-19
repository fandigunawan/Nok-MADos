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

#include "hw/lcd.h"
#include "hw/ccont.h"
#include "hw/kpd.h"
#include "hw/buzzer.h"
#include "core/lib.h"
#include "core/ui.h"

unsigned char ui_boxtype = 0;

void
ui_box ( unsigned char x, unsigned char y, unsigned char xd, unsigned char yd, unsigned char inverse_colors )
{
    lcd_draw_rect ( x, y, xd, yd, /*1 */ !inverse_colors );
    lcd_draw_rect ( x + 1, y + 1, xd - 1, yd - 1, /*0 */ inverse_colors );

    if ( ui_boxtype == 1 )
    {
        lcd_set_pixel ( x, y, /*0 */ inverse_colors );
        lcd_set_pixel ( xd, y, inverse_colors );
        lcd_set_pixel ( x, yd, inverse_colors );
        lcd_set_pixel ( xd, yd, inverse_colors );
    }
}

unsigned char
ui_disp_textbox ( unsigned char x, unsigned char y, unsigned char len, char *ptext, unsigned char align, unsigned char inverse_colors )
{
    unsigned char sx;
    unsigned char xd;
    unsigned char yd;
    unsigned char ofs;

    if ( inverse_colors )
        inverse_colors = 1;

    if ( !len )
        //sx = strlen ( ptext ) * 8;
        sx = lcd_get_text_width ( ptext );
    else
        sx = len * 8;

    if ( align == UI_ALIGN_RIGHT )
        //ofs = sx - ( strlen ( ptext ) * 8 );
        ofs = sx - lcd_get_text_width ( ptext );

    if ( align == UI_ALIGN_CENTER )
        ofs = ( sx - lcd_get_text_width ( ptext ) ) / 2;

    xd = x + sx + 1;
    yd = y + /*9 */ 10;

    ui_box ( x, y, xd, yd, inverse_colors );

    lcd_render_text ( x + 2 + ofs, y + 1, ptext, /*1 */ !inverse_colors );
    //lcd_to_screen (  );

    return sx + 1;
}

void
ui_set_boxtype ( unsigned char type )
{
    ui_boxtype = type;
}

int
ui_getnumber ( char *ptext, unsigned char max_length, unsigned char min_length )
{
    unsigned char key, lastkey = 0xff, start = 1, mul_level = 0, buf[16], buf2[1];
    signed char i, j;
    int return_nr = 0, stellenzahl;

    kpd_wait_release (  );

    do
    {
        key = kpd_getkey (  );
        //kpd_wait_release (  );

        if ( ( key != 0xff && key != lastkey ) || start == 1 )
        {

            start = 0;

            lcd_clr (  );
            lcd_render_text ( 0 * 8, 0 * 8, ptext, 1 );

            if ( key == KPD_SOFTBTN1 && mul_level <= min_length )
            {
                //buzzer_snd_play ( snd_error, sizeof (snd_error) );
                lcd_render_text ( 0x8, 2 * 8, "too short!", 1 );
                key = 0xff;
            }

            if ( key < 10 && mul_level > max_length )
            {
                //buzzer_snd_play ( snd_error, sizeof (snd_error) );
                lcd_render_text ( 0x8, 2 * 8, "too long!", 1 );
                key = 0xff;
            }

            if ( key < 10 )
            {
                buf[mul_level] = key;
                mul_level++;
            }

            if ( key == KPD_CANCEL && mul_level != 0 )
                mul_level--;
            else if ( key == KPD_CANCEL && mul_level == 0 )
                key = 0xEE;

            /*
             * lcd_draw_line ( 0, 4*8-2, 83, 4*8-2, 1); //line 1 hor
             * lcd_draw_line ( 0, 5*8+1, 83, 5*8+1, 1 ); //line 2 hor
             * lcd_draw_line ( 0, 4*8-2, 0, 5*8+1, 1 ); //line 1 ver
             * lcd_draw_line ( 83, 4*8-2, 83, 5*8+1, 1 ); //line 2 ver
             */

            ui_box ( 0, 4 * 8 - 2, 83, 5 * 8 + 1, 0 );


            for ( i = 0; i < mul_level; i++ )
            {
                buf2[0] = buf[i] + 0x30;
                lcd_render_text ( 82 - mul_level * 8 + i * 8, 4 * 8, buf2, 1 );
            }

            lcd_to_screen (  );
        }

        lastkey = key;

    }
    while ( key != KPD_SOFTBTN1 && key != 0xEE );

    for ( i = 0; i < mul_level; i++ )
    {
        stellenzahl = 1;
        for ( j = 1; j < mul_level; j++ )
            stellenzahl *= 10;

        return_nr += stellenzahl * buf[i];
    }

    if ( key != 0xEE )
        return return_nr;
    else
        return 0x7FFFFFFF;
}

unsigned char *img_types[] = {
    "  X  " " X X " "X   X" "XXXXX" "X   X" "X   X",

    "     " " XXX " "    X" " XXXX" "X   X" " XXXX",

    "  X  " " XX  " "X X  " "  X  " "  X  " " XXX ",

    "X   X" " X X " "  X  " " X X " "X   X" "     ",

    NULL
};

const int img_types_x = 5;
const int img_types_y = 6;

// the values for ui_gettext ...
const unsigned char ui_keys[] = {
    0x20, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x2E, 0x2C, 0x21, 0x3F, 0x2D, 0x2A,
    0x41, 0x42, 0x43, 0xFF, 0xFF, 0xFF,
    0x44, 0x45, 0x46, 0xFF, 0xFF, 0xFF,
    0x47, 0x48, 0x49, 0xFF, 0xFF, 0xFF,
    0x4A, 0x4B, 0x4C, 0xFF, 0xFF, 0xFF,
    0x4D, 0x4E, 0x4F, 0xFF, 0xFF, 0xFF,
    0x50, 0x51, 0x52, 0x53, 0xFF, 0xFF,
    0x54, 0x55, 0x56, 0xFF, 0xFF, 0xFF,
    0x57, 0x58, 0x59, 0x5A, 0xFF, 0xFF,

    0x20, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x2E, 0x2C, 0x21, 0x3F, 0x2D, 0x2A,
    0x61, 0x62, 0x63, 0xFF, 0xFF, 0xFF,
    0x64, 0x65, 0x66, 0xFF, 0xFF, 0xFF,
    0x67, 0x68, 0x69, 0xFF, 0xFF, 0xFF,
    0x6A, 0x6B, 0x6C, 0xFF, 0xFF, 0xFF,
    0x6D, 0x6E, 0x6F, 0xFF, 0xFF, 0xFF,
    0x70, 0x71, 0x72, 0x73, 0xFF, 0xFF,
    0x74, 0x75, 0x76, 0xFF, 0xFF, 0xFF,
    0x77, 0x78, 0x79, 0x7A, 0xFF, 0xFF,

    0x30, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x31, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x32, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x33, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x35, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x36, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x37, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x38, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x39, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

    0x30, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x31, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x32, 0x41, 0x42, 0x43, 0xFF, 0xFF,
    0x33, 0x44, 0x45, 0x46, 0xFF, 0xFF,
    0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x35, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x36, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x37, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x38, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x39, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
        //return values for the keys:
        //type 0 - key 1
        //type 0 - key 2
        //...
};

// ask the user for a text and puts it in output; ptext mustn't be longer than 9 chars
void
ui_gettext ( char *ptext, unsigned char max_length, char *output, unsigned char ui_type )
{

    //max_length++;

    unsigned int last_keypress_time = 0, actual_time, count_chars = 0, bufpos_for_printing = 0;
    unsigned char buf[max_length + 1], row_buf[31];
    unsigned char key, lastkey = 0xff, start = 1, type = 0, char_for_buf, last_digit, count_last_digits = 0, i, j, last_space_in_buf, row, reached_end =
        0, total_rows, cursor_in_row, printing_row, start_printing_in_row, line_x_len, chars_in_line /*, scrollbar_height, scrollbar_top */ ;
    int cur_pos = 0;

    memset ( buf, 0x00, ( unsigned long ) max_length );

    if ( ( ( 1 << type ) & ui_type ) != ( 1 << type ) )
    {
        do
        {
            type = lib_mod ( type + 1, 4 );
        }
        while ( ( ( 1 << type ) & ui_type ) != ( 1 << type ) );
    }


    kpd_wait_release (  );

    do
    {
        key = kpd_getkey (  );
        //kpd_wait_release (  );

        lcd_clr (  );
        lcd_render_text ( 0 * 8, 0 * 8, ptext, 1 );

        if ( key != 0xff && key != lastkey )
        {

            if ( key == 0x12 )
            {
                do
                {
                    type = lib_mod ( type + 1, 4 );
                }
                while ( ( ( 1 << type ) & ui_type ) != ( 1 << type ) );
            }

            if ( key == KPD_UPARROW && cur_pos > 0 )
                cur_pos--;
            if ( key == KPD_DWNARROW )
                cur_pos++;

            if ( key < 10 && count_chars < max_length )
            {

                if ( count_last_digits > 0 )
                {
                    // todo: cut the shit out :) add cool stuff...
                    if ( last_digit != key || ui_keys[type * 6 * 10 + last_digit * 6 + 1] == 0xff )
                    {
                        /*
                         * if ( last_buf_char_temp == 1 )
                         * {
                         * count_chars--;
                         * last_buf_char_temp = 0;
                         * }
                         */

                        //buf[count_chars] = ui_keys[type*6*10 + last_digit*6 + count_last_digits - 1];
                        count_chars++;
                        count_last_digits = 0;
                        cur_pos++;
                        // insert a new char
                        memmove ( buf + cur_pos + 1, buf + cur_pos, strlen ( buf + cur_pos ) + 1 );
                    }
                    /*
                     * else
                     * {
                     * buf[count_chars] = ui_keys[type*6*10 + last_digit*6 + count_last_digits - 1];
                     * //count_chars++;
                     * //last_buf_char_temp = 1;
                     * }
                     */

                    //last_digit = key;
                }
                else
                    // insert a new char
                    memmove ( buf + cur_pos + 1, buf + cur_pos, strlen ( buf + cur_pos ) + 1 );

                last_digit = key;

                if ( ui_keys[type * 6 * 10 + last_digit * 6 + count_last_digits] == 0xff || count_last_digits > 5 )
                    count_last_digits = 0;

                buf[cur_pos] = ui_keys[type * 6 * 10 + last_digit * 6 + count_last_digits];
                count_last_digits++;

                last_keypress_time = lib_get_time (  );
            }
            else
            {
                if ( last_digit != 0xff && count_last_digits > 0 )
                    count_chars++;
                last_digit = 0xff;
                count_last_digits = 0;
            }

            if ( key == KPD_CANCEL )
            {
                if ( count_chars == 0 )
                    key = 0xEE;
                else
                {
                    memmove ( buf + cur_pos, buf + cur_pos + 1, strlen ( buf + cur_pos ) );
                    count_chars--;
                    buf[count_chars] = 0x00;
                }
            }

            // todo: further key comparisions needed ... scroll etc. *g*

        }

        if ( lib_abs ( lib_get_time (  ) - last_keypress_time ) > 1000 && count_last_digits > 0 )
        {
            buf[cur_pos] = ui_keys[type * 6 * 10 + last_digit * 6 + count_last_digits - 1];
            cur_pos++;
            count_chars++;
            count_last_digits = 0;
        }

        if ( lib_get_time (  ) % 1024 > 512 )
            lcd_set_cursor ( 1 );
        else
            lcd_set_cursor ( 0 );


        if ( cur_pos > -1 )
        {
            if ( cur_pos > strlen ( buf ) )
                cur_pos = strlen ( buf );
            // insert the cursor char 0xFF
            memmove ( buf + cur_pos + 1, buf + cur_pos, strlen ( buf + cur_pos ) + 1 );
            buf[cur_pos] = 0xFF;
        }

//        lcd_render_text ( 0*8, 1*8, buf, 1 );

        printing_row = 1;
        total_rows = 0;
        cursor_in_row = 0;
        start_printing_in_row = 0;
        j = 0;

        while ( j < 2 )
        {
            reached_end = 0;
            row = 0;
            bufpos_for_printing = 0;

            while ( reached_end == 0 )
            {
                last_space_in_buf = 0xff;
                chars_in_line = 0;
                line_x_len = 0;
                for ( i = bufpos_for_printing; i < max_length + 1; i++ )
                {
                    if ( buf[i] == 0x00 )
                    {
                        reached_end = 1;
                        break;
                    }
                    if ( buf[i] == 0x20 )
                        last_space_in_buf = i - bufpos_for_printing;
                    if ( buf[i] == 0xff )
                        cursor_in_row = row;
                    /*
                     * if ( i > bufpos_for_printing + 9 && cursor_in_row != row )
                     * break;
                     * if ( i > bufpos_for_printing + 10 && cursor_in_row == row )
                     * break;
                     */

                    if ( line_x_len + lcd_get_char_width ( buf[i + 1] ) > 81 && buf[i + 1] )
                        break;

                    line_x_len += lcd_get_char_width ( buf[i] );
                    chars_in_line++;

                }
                if ( bufpos_for_printing >= max_length )
                    reached_end = 1;

                if ( j == 1 && printing_row < 6 && row >= start_printing_in_row )
                {
                    memset ( row_buf, 0x00, 30 );
                    if ( reached_end == 0 )
                    {
                        if ( last_space_in_buf == 0xff )
                            /*
                             * if ( cursor_in_row == row )
                             * memcpy ( row_buf, buf + bufpos_for_printing, 11 );
                             * else
                             * memcpy ( row_buf, buf + bufpos_for_printing, 10 );
                             */

                            memcpy ( row_buf, buf + bufpos_for_printing, chars_in_line );

                        else
                            memcpy ( row_buf, buf + bufpos_for_printing, last_space_in_buf );

                        lcd_render_text ( 0 * 8, printing_row * 8, row_buf, 1 );
                    }
                    else
                        lcd_render_text ( 0 * 8, printing_row * 8, buf + bufpos_for_printing, 1 );

                    printing_row++;
                }

                row++;

                if ( reached_end == 0 )
                {
                    if ( last_space_in_buf == 0xff )
                        bufpos_for_printing += chars_in_line /*10 */ ;
                    else
                        bufpos_for_printing += last_space_in_buf + 1;
                }
            }

            //if ( j == 1 ) break;

            j++;
            total_rows = row;
            if ( cursor_in_row > 3 )
                start_printing_in_row = cursor_in_row - 3;
            //start_printing_in_row = 0;
        }

        /*
         * if ( total_rows < 5 )
         * total_rows = 5;
         * scrollbar_height = lib_div ( 200, total_rows );
         * //laenge des balken 40 / (total rows / 5)
         * //scrollbar_height = 20;
         * 
         * scrollbar_top = 8 + ( lib_div ( start_printing_in_row, 5 ) * scrollbar_height );
         * //oberster punkt 8 + ( start_printing_in_row / 5 ) * laege des balken
         * //unterster punkt oberster_punkt + laenge des balken..
         * //scrollbar_top = 8;
         * 
         * lcd_draw_rect ( 81, scrollbar_top, 83, scrollbar_top + scrollbar_height, 1 );
         * // todo:  scroll function *g* - done ? - now a nice graph at the right side is needed
         */

        lcd_draw_rect (  /*75 */ 82, lib_div ( 40 * start_printing_in_row, total_rows ) + 8, 83, lib_div ( 240, total_rows ) + lib_div ( 40 * start_printing_in_row, total_rows ) + 8 );

        lcd_render_bitmap ( 75, 1, img_types_x, img_types_y, img_types[type], 1 );
        lcd_to_screen (  );

        lastkey = key;


        if ( cur_pos > -1 )
            // and remove the cursor again
            memmove ( buf + cur_pos, buf + cur_pos + 1, strlen ( buf + cur_pos + 1 ) + 1 );

    }
    while ( key != KPD_SOFTBTN1 && key != 0xEE );

    memcpy ( output, buf, count_chars );

}

void
ui_draw_scrolltext ( char *ptext )
{
    unsigned char key, last_key, reached_end = 0, row_start = 0, last_space_in_buf, total_row = 8, printing_row, line_x_len, chars_in_line, scroll_delay;
    char row_buf[31];
    unsigned int y_pos = 0, loop_time = lib_get_time (  ), i, bufpos_for_printing, strlen_buffer;

    // FONT_DYNAMIC test
    //lcd_set_font ( FONT_DYNAMIC );

    kpd_wait_release (  );
    strlen_buffer = strlen ( ptext ) + 1;
    /*
     * scroll_delay = 75;
     */

    do
    {
        key = kpd_getkey (  );
        lcd_clr (  );

        if (  /*last_key != key */ loop_time + /*scroll_delay */ 75 < lib_get_time (  ) )
        {

            if ( key == last_key && ( key == KPD_UPARROW || key == KPD_DWNARROW ) )
                /*
                 * if ( scroll_delay > 10 )
                 * scroll_delay--;
                 * else
                 * scroll_delay = 75;
                 */
                /*
                 * if ( key == KPD_UPARROW && row_start > 0 )
                 * row_start--;
                 * if ( key == KPD_DWNARROW && row_start + 7 < total_row )
                 * row_start++;
                 */

                if ( key == KPD_UPARROW && y_pos > 0 )
                    y_pos--;
            if ( key == KPD_DWNARROW && y_pos / 8 + 6 < total_row )
                y_pos++;

            loop_time = lib_get_time (  );
        }
/*
		memset ( row_buf, 0x00, 30 );
		sprintf ( row_buf, "%d\n%d\n%d\n%d", y_pos, total_row, 0, 0 );
		lcd_render_text_ml ( 10, 0, row_buf, 1 ,AL_CENTER);
		lcd_to_screen ( );
		usleep ( 100 );

	//lcd_render_text ( 0, -3, "test bla", 1 );
*/

        row_start = y_pos / 8;

        bufpos_for_printing = 0;
        printing_row = 0;
        total_row = 0;
        reached_end = 0;

        while ( reached_end == 0 )
        {

            last_space_in_buf = 0xff;
            chars_in_line = 0;
            line_x_len = 0;
            for ( i = bufpos_for_printing; i < strlen_buffer; i++ )
            {
                if ( ptext[i] == 0x00 )
                {
                    reached_end = 1;
                    break;
                }

                if ( ptext[i] == 0x20 )
                    last_space_in_buf = i - bufpos_for_printing;

                if ( line_x_len + lcd_get_char_width ( ptext[i + 1] ) > /*60 *//*74 */ 81 && ptext[i + 1] )
                    break;

                line_x_len += lcd_get_char_width ( ptext[i] );
                chars_in_line++;

                /*
                 * if ( i > bufpos_for_printing + 9 )
                 * break;
                 */

            }

            if ( printing_row < 7 && total_row >= row_start )
            {
                memset ( row_buf, 0x00, 30 );
                if ( reached_end == 0 )
                {
                    if ( last_space_in_buf == 0xff )
                        memcpy ( row_buf, ptext + bufpos_for_printing, chars_in_line /*10 */  );
                    else
                        memcpy ( row_buf, ptext + bufpos_for_printing, last_space_in_buf );

                    lcd_render_text ( 0 * 8, printing_row * 8 - ( y_pos % 8 ), row_buf, 1 );
                }
                else
                    lcd_render_text ( 0 * 8, printing_row * 8 - ( y_pos % 8 ), ptext + bufpos_for_printing, 1 );

                /*
                 * memset ( row_buf, 0x00, 30 );
                 * sprintf ( row_buf, "%d", line_x_len );
                 * lcd_render_text ( 65, printing_row * 8 - ( y_pos % 8 ), row_buf, 1 );
                 */

                printing_row++;
            }

            total_row++;

            if ( reached_end == 0 )
            {
                if ( last_space_in_buf == 0xff )
                    bufpos_for_printing += chars_in_line /*10 */ ;
                else
                    bufpos_for_printing += last_space_in_buf + 1;
            }

        }

        //lcd_draw_rect ( /*75*/ 82, lib_div ( row_start, 6 ) * lib_div ( 48, lib_div ( total_row, 6 ) ), /*76*/ 83,  lib_div ( 48, lib_div ( total_row, 6 ) ) + lib_div ( row_start, 6 ) * lib_div ( 48, lib_div ( total_row, 6 ) ) );
        lcd_draw_rect ( 82, lib_div ( 48 * row_start, total_row ), 83, lib_div ( 288, total_row ) + lib_div ( 48 * row_start, total_row ) );

        /*
         * memset ( row_buf, 0x00, 30 );
         * sprintf ( row_buf, "%d\n%d", total_row, row_start );
         * lcd_render_text_ml ( 67, 0, row_buf, 1 , AL_RIGHT);
         */

        lcd_to_screen (  );

        //last_key = key;



    }
    while ( key != KPD_SOFTBTN1 && key != KPD_CANCEL );

    //key = kpd_getkey (  );

    //lcd_set_font ( 0 );

}

// returns selected button by pressing SOFTBTN1, returns 0xFF by pressing CANCEL
unsigned char
ui_dialog_box ( char *ptext, char **buttons )
{

    unsigned char key, elements = 0, selected = 0, c, d, /*size_of_boxes, */ button_line_buf[2];

    while ( buttons[elements] )
        elements++;

    kpd_wait_release (  );

    do
    {

        lcd_clr (  );
        lcd_to_screen (  );
        lcd_render_text ( ( 84 - lcd_get_text_width ( ptext ) ) / 2, 0, ptext, 1 );
        //more line text in the middle of screen, eventually scrolling...

        // more lines
        //size_of_boxes = 0;
        d = 0;
        memset ( button_line_buf, 0, 2 );
        for ( c = 0; c < elements; c++ )
        {
            key = lcd_get_text_width ( buttons[c] ) + 3;
            if ( button_line_buf[d] + key > 83 )
            {
                button_line_buf[d] = ( 84 - button_line_buf[d] ) / 2;
                if ( !d )
                    d++;
                else
                {
                    lcd_clr (  );
                    lcd_render_text ( 0, 0, "too much btns!", 1 );
                }
            }
            button_line_buf[d] += key;

            //size_of_boxes += lcd_get_text_width ( buttons[c] ) + 3;
        }
        button_line_buf[d] = ( 84 - button_line_buf[d] ) / 2;

        //size_of_boxes = ( 84 - size_of_boxes ) / 2;
        d = 0;
        //size_of_boxes = button_line_buf[d];
        for ( c = 0; c < elements; c++ )
        {
            if ( button_line_buf[d] + lcd_get_text_width ( buttons[c] ) + 3 > 83 && !d )
            {
                d++;
                //size_of_boxes = 0;
            }

            button_line_buf[d] += ui_disp_textbox ( button_line_buf[d], 27 + d * /*11 */ 12, 0, buttons[c], UI_ALIGN_CENTER, c == selected ? 1 : 0 ) + 2;
        }

        lcd_to_screen (  );

        kpd_wait_release (  );
        kpd_wait_keypress (  );
        key = kpd_getkey (  );

        if ( key == KPD_UPARROW )
            selected = lib_mod ( selected + 1, elements );

        if ( key == KPD_DWNARROW )
            selected = lib_mod ( ( selected == 0 ? elements : selected ) - 1, elements );


    }
    while ( key != KPD_SOFTBTN1 && key != KPD_CANCEL );

    return key == KPD_SOFTBTN1 ? selected : 0xFF;

/*	lcd_clr ( );
	lcd_render_text ( ( 84 - lcd_get_text_width ( ptext ) ) / 2, 0, ptext, 1 );
	ui_disp_textbox ( 0, 30, 0, ptext_button1, UI_ALIGN_CENTER, 0 );
	lcd_to_screen ();
	sleep ( 4 );

	lcd_clr ( );
	lcd_render_text ( ( 84 - lcd_get_text_width ( ptext ) ) / 2, 0, ptext, 1 );
	ui_disp_textbox ( 0, 30, 0, ptext_button1, UI_ALIGN_CENTER, 1 );
	lcd_to_screen ();
	sleep ( 4 );*/

}
