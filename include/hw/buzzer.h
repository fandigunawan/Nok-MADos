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

typedef struct
{
    char *tone_list;            // "cpdpcpdpepfpgpaphp" // 'p' - pause
    char *duration_list;        // 1, 2, 4, ...         // n * 100ms
    char *octave_list;          // 1, 2, 3 ...          // c1 = 200 Hz, c2 = 400 Hz, c3 = 800 Hz
    unsigned char volume;       // 0x00 - 0xFF
    char duration_fixed;        // if set, duration_list is ignored
    char octave_fixed;          // if set, octave_list is ignored
    char pause_fixed;           // if set, after every tone from tone_list a pause is insert. tone_list without 'p'.
    char *interrupt;            // pointer to 1 byte. if changed, buzzer_play_tones breaks
    char break_on_keypress;     // if set to 1, buzzer_play_tones breaks on keypress
}
buzzer_tones_t;

void buzzer_init ( void );
void buzzer_setvol ( unsigned char volume );
void buzzer_setfreq ( unsigned short freq );
void buzzer_play_tones ( buzzer_tones_t * tone_info );
