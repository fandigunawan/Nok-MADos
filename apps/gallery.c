
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

#include <core/lib.h>
#include <core/ui.h>
#include <apps/gallery.h>
#include <core/bitmap.h>
#include <hw/buzzer.h>

#ifndef LOADER

// Image/Sounds/Movies Gallery by GsmCyber (and others) =) X-Tina Aguilera rulezzz... (under construction)

int gallery_tipe = 0;

MENU_CALLBACK ( gallery_type )
{
    char *entries[] = { "Images", "Movies", "Sounds", NULL };
    int t;

    switch ( cmd )
    {
        case MENU_SELECT:
            t = menu_dropdown ( entries, gallery_tipe );
            if ( t > -1 )
                gallery_tipe = t;
            break;
        case MENU_REDRAW:
        case MENU_DRAW:
            menu_disp ( entries[gallery_tipe] );
            break;
        default:
            break;
    }

}

int gallery_object = 0;

MENU_CALLBACK ( gallery_imss )
{

    if ( gallery_tipe == 0 )
    {
        char *entries[] = { "MADos", "X-Tina 1", "X-Tina 2", "X-Tina 3", "Grrrrrr", "Bart", "Homer", "A. Jolie", "Wwooohhh", "Super Car", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, gallery_object );
                if ( t > -1 )
                    gallery_object = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[gallery_object] );
                break;
            default:
                break;
        }
    }

    if ( gallery_tipe == 1 )
    {
        char *entries[] = { "MADos", "Hands", "Calvin", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, gallery_object );
                if ( t > -1 )
                    gallery_object = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[gallery_object] );
                break;
            default:
                break;
        }
    }

    if ( gallery_tipe == 2 )
    {
        char *entries[] = { "MADos", "Pastor", "Happy Birthday", "Test", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, gallery_object );
                if ( t > -1 )
                    gallery_object = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[gallery_object] );
                break;
            default:
                break;
        }
    }
}

MENU_CALLBACK ( gallery_view )
{
    MENU_ONLY_SELECT;

    if ( gallery_tipe == 0 )
        if ( gallery_object == 0 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_welcome );
            lcd_to_screen (  );
            sleep ( 5 );
        }

    if ( gallery_tipe == 0 )
        if ( gallery_object == 1 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_aguilera1 );
            lcd_to_screen (  );
            sleep ( 5 );
        }

    if ( gallery_tipe == 0 )
        if ( gallery_object == 2 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_aguilera2 );
            lcd_to_screen (  );
            sleep ( 5 );
        }

    if ( gallery_tipe == 0 )
        if ( gallery_object == 3 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_aguilera3 );
            lcd_to_screen (  );
            sleep ( 5 );
        }

    if ( gallery_tipe == 0 )
        if ( gallery_object == 4 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_binladen );
            lcd_to_screen (  );
            sleep ( 5 );
        }


    if ( gallery_tipe == 0 )
        if ( gallery_object == 5 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_bart );
            lcd_to_screen (  );
            sleep ( 5 );
        }

    if ( gallery_tipe == 0 )
        if ( gallery_object == 6 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_homer );
            lcd_to_screen (  );
            sleep ( 5 );
        }

    if ( gallery_tipe == 0 )
        if ( gallery_object == 7 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_jolie );
            lcd_to_screen (  );
            sleep ( 5 );
        }

    if ( gallery_tipe == 0 )
        if ( gallery_object == 8 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_error );
            lcd_to_screen (  );
            sleep ( 5 );
        }

    if ( gallery_tipe == 0 )
        if ( gallery_object == 9 )
        {
            ksleep ( 2 );
            lcd_draw_bitmap ( -1, -1, &bmp_car );
            lcd_to_screen (  );
            sleep ( 5 );
        }

    if ( gallery_tipe == 1 )
        if ( gallery_object == 0 )
        {
            ksleep ( 2 );
            ani_play ( &ani_02, 0, 0, 100, 0, 0 );
            lcd_to_screen (  );
            sleep ( 2 );
            ani_stop (  );
        }

    if ( gallery_tipe == 1 )
        if ( gallery_object == 1 )
        {
            ksleep ( 2 );
            ani_play ( &ani_04, 0, 0, 200, 0, 0 );
            lcd_to_screen (  );
            sleep ( 2 );
            ani_stop (  );
        }

    if ( gallery_tipe == 1 )
        if ( gallery_object == 2 )
        {
            ksleep ( 2 );
            ani_play ( &ani_03, 0, 0, 300, 0, 0 );
            lcd_to_screen (  );
            sleep ( 3 );
            ani_stop (  );
        }

    if ( gallery_tipe == 2 )
        if ( gallery_object == 0 )
        {
            char entchen[] = "cdefggaaaagaaaagffffeeggggc"; //tone by krisha ... i think :p
            char entchen_dauer[] = { 2, 2, 2, 2, 4, 4, 2, 2, 2, 2, 8, 2, 2, 2, 2, 8, 2, 2, 2, 2, 4, 4, 2, 2, 2, 2, 8 };
            buzzer_tones_t tone_info;
            tone_info.tone_list = entchen;
            tone_info.duration_list = entchen_dauer;
            tone_info.octave_list = "\x00\x00";
            tone_info.volume = 20;
            tone_info.duration_fixed = 0;
            tone_info.octave_fixed = 1;
            tone_info.pause_fixed = 1;
            tone_info.interrupt = "\x00\x00";
            tone_info.break_on_keypress = 1;
            buzzer_play_tones ( &tone_info );
        }

    if ( gallery_tipe == 2 )
        if ( gallery_object == 1 )
        {
            char entchen[] = "cdefffcdcdddcgfeeecdefff";
            char entchen_dauer[] = { 2, 2, 2, 4, 4, 4, 2, 2, 2, 4, 4, 4, 2, 2, 2, 4, 4, 4, 2, 2, 2, 4, 4, 8 };
            buzzer_tones_t tone_pastor;
            tone_pastor.tone_list = entchen;
            tone_pastor.duration_list = entchen_dauer;
            tone_pastor.octave_list = "\x00\x00";
            tone_pastor.volume = 20;
            tone_pastor.duration_fixed = 0;
            tone_pastor.octave_fixed = 1;
            tone_pastor.pause_fixed = 1;
            tone_pastor.interrupt = "\x00\x00";
            tone_pastor.break_on_keypress = 1;
            buzzer_play_tones ( &tone_pastor );
        }

    if ( gallery_tipe == 2 )
        if ( gallery_object == 2 )
        {
            char entchen[] = "ccdcfeccdcgfcccafedbbafgf";
            char entchen_dauer[] = { 1, 1, 2, 2, 2, 3, 1, 1, 2, 2, 2, 3, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 3 };
            buzzer_tones_t tone_happy;
            tone_happy.tone_list = entchen;
            tone_happy.duration_list = entchen_dauer;
            tone_happy.octave_list = "\x00\x00";
            tone_happy.volume = 20;
            tone_happy.duration_fixed = 0;
            tone_happy.octave_fixed = 1;
            tone_happy.pause_fixed = 1;
            tone_happy.interrupt = "\x00\x00";
            tone_happy.break_on_keypress = 1;
            buzzer_play_tones ( &tone_happy );
        }

    if ( gallery_tipe == 2 )
        if ( gallery_object == 3 )
        {
            char entchen[] = "cdefgabppbagfedc";
            char entchen_dauer[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
            buzzer_tones_t tone_test;
            tone_test.tone_list = entchen;
            tone_test.duration_list = entchen_dauer;
            tone_test.octave_list = "\x00\x00";
            tone_test.volume = 20;
            tone_test.duration_fixed = 0;
            tone_test.octave_fixed = 1;
            tone_test.pause_fixed = 1;
            tone_test.interrupt = "\x00\x00";
            tone_test.break_on_keypress = 1;
            buzzer_play_tones ( &tone_test );
        }

}

#endif
