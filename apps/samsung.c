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
#include <apps/samsung.h>

#ifndef LOADER

// Samsung code list by Crux and GsmCyber (last update - 08/07/05)

int samsung_phonetype = 0;

MENU_CALLBACK ( samsung_type )
{
    char *entries[] = { "Universal", "600", "2100", "A300", "A400", "A800", "C100", "C225", "D500", "E400", "E500", "E700", "E715", "E820", "M100", "N105", "P400", "Q105", "R210", "R220", "R225", "S100", "S105", "S300", "S300M", "S307", "S500", "T200", "T500", "V200", "X100", "X100A", "X450", "X600", NULL };
    int t;

    switch ( cmd )
    {
        case MENU_SELECT:
            t = menu_dropdown ( entries, samsung_phonetype );
            if ( t > -1 )
                samsung_phonetype = t;
            break;
        case MENU_REDRAW:
        case MENU_DRAW:
            menu_disp ( entries[samsung_phonetype] );
            break;
        default:
            break;
    }

}


MENU_CALLBACK ( samsung_code )
{
    MENU_ONLY_SELECT;

    if ( samsung_phonetype == 0 )
    {
        ui_draw_scrolltext ( "TEMPORARY UNLOCK: Put a non-accepted SIM Card and turn it on. Type *#9998*3323#. Press Exit. You will get a new menu. Select Malloc Fail. or In newer phones: #*7337# " );
    }

    if ( samsung_phonetype == 1 )
    {
        ui_draw_scrolltext ( "*2767*3855# or *2767*2878#" );
    }

    if ( samsung_phonetype == 2 )
    {
        ui_draw_scrolltext ( "*2767*3855# or *2767*2878#" );
    }

    if ( samsung_phonetype == 3 )
    {
        ui_draw_scrolltext ( "*2767*637# or *2767*688#" );
    }

    if ( samsung_phonetype == 4 )
    {
        ui_draw_scrolltext ( "*2767*637# or *2767*688#" );
    }

    if ( samsung_phonetype == 5 )
    {
        ui_draw_scrolltext ( "*2767*637# or *2767*688#" );
    }

    if ( samsung_phonetype == 6 )
    {
        ui_draw_scrolltext ( "*2767*688# or *#9998*627837793# or Put a non-accepted SIM Card and turn it on. Type *#9998*3323#. Press Exit. Choose menu #7. After phone reboots go to menu 4.2.4 and chose 4 and 6" );
    }

    if ( samsung_phonetype == 7 )
    {
        ui_draw_scrolltext ( "*2767*688(IMEI)# After phone reboots type *0141# and hit the Call button. Turn off and insert another SIM Card. Turn on. The code is 00000000." );
    }

    if ( samsung_phonetype == 8 )
    {
        ui_draw_scrolltext ( "In newer phones: #*7337# or *2767*3855#" );
    }

    if ( samsung_phonetype == 9 )
    {
        ui_draw_scrolltext ( "*2767*688# or In newer phones: #*7337# " );
    }

    if ( samsung_phonetype == 10 )
    {
        ui_draw_scrolltext ( "*2767*688# or In newer phones: #*7337#" );
    }

    if ( samsung_phonetype == 11 )
    {
        ui_draw_scrolltext ( "*2767*688# or In newer phones: #*7337#" );
    }

    if ( samsung_phonetype == 12 )
    {
        ui_draw_scrolltext ( "Turn off the phone. Put a non-accepted SIM Card and turn it on. Type *#9998*3323#. Press Exit. Choose menu #7. After phone reboots type *0141# and hit the Call button. Turn off and insert another SIM Card. Turn on. The code is 00000000. or In newer phones: #*7337#" );
    }

    if ( samsung_phonetype == 13 )
    {
        ui_draw_scrolltext ( "*2767*3855#" );
    }

    if ( samsung_phonetype == 14 )
    {
        ui_draw_scrolltext ( "Type *#9998*627837793#. Then type *#9998*737#. Press >/[] (Play Stop) until phone shows NCK/SPCK number. Press Exit. Type #0111*CODE# (Code is the last 8 digits of the NCK/SPCK)" );
    }

    if ( samsung_phonetype == 15 )
    {
        ui_draw_scrolltext ( "Put a non-accepted SIM Card and turn it on. Type *#9998*3323#. Press Exit. You will get a new menu. Select Malloc Fail. In the new menu press 7 8 9 " );
    }

    if ( samsung_phonetype == 16 )
    {
        ui_draw_scrolltext ( "*2767*3855# or *2767*688# or *2767*927# or In newer phones: #*7337#" );
    }

    if ( samsung_phonetype == 17 )
    {
        ui_draw_scrolltext ( "1. Insert the SIM that your phone says is the Wrong SIM into the phone. A message saying Wrong SIM Card should appear on the screen. You can only make SOS calls at this point. 2. Enter in the phone *#9998*627837793# and wait until the error message (Wrong Code) dissapears 3. Enter in the phone *#9998*3323# 4. You will now see the option Exit on the bottom side of the phone. Hit the soft key above it to exit. 5. Press the 7 key on the key pad. Your phone will now reboot. (Turn off & turn on automatically.) 6. After the phone turns back on it will be unlocked to the SIM card already in the phone (the one that was the Wrong SIM). This is just a temporary unlock. 7. To finish unlocking the phone do the following steps: Enter *0141# and press the green CALL button as if you were calling the above number. A small box saying Personalized will now appear. 8. Turn off your phone take off the battery, insert a different SIM card (not the one called the Wrong SIM) 9. When you turn on the phone it will ask you for a SIM unlock code. Type in 00000000 or 8 zeros. 10. Press OK and now your phone is unlocked to all networks." );
    }

    if ( samsung_phonetype == 18 )
    {
        ui_draw_scrolltext ( "*2767*3855# or *2767*2878#" );
    }

    if ( samsung_phonetype == 19 )
    {
        ui_draw_scrolltext ( "Remove SIM, turn ON the phone and press *2767*2878#" );
    }

    if ( samsung_phonetype == 20 )
    {
        ui_draw_scrolltext ( "*2767*2878#" );
    }

    if ( samsung_phonetype == 21 )
    {
        ui_draw_scrolltext ( "*2767*7822573738# or In newer phones: #*7337#" );
    }

    if ( samsung_phonetype == 22 )
    {
        ui_draw_scrolltext ( "Remove SIM Card. Enter *2767*7822573738# and after phone reboots, enter #0111*00000000# or In newer phones: #*7337#" );
    }

    if ( samsung_phonetype == 23 )
    {
        ui_draw_scrolltext ( "*2767*7822573738#" );
    }

    if ( samsung_phonetype == 24 )
    {
        ui_draw_scrolltext ( "Put a non-accepted SIM Card and turn it on. Type *#9998*3323#. Press Exit. You will get a new menu. Select Malloc Fail. In the new menu press 7 8 9 " );
    }

    if ( samsung_phonetype == 25 )
    {
        ui_draw_scrolltext ( "Turn off the phone. Put a non-accepted SIM Card and turn it on. Type *#9998*3323#. Press Exit. Choose menu #7. After phone reboots type *0141# and hit the Call button. Turn off and insert another SIM Card. Turn on. The code is 00000000. or In newer phones: #*7337# " );
    }

    if ( samsung_phonetype == 26 )
    {
        ui_draw_scrolltext ( "*2767*3855# or *2767*688# or *2767*927#  or *#7465625#  or In newer phones: #*7337# " );
    }

    if ( samsung_phonetype == 27 )
    {
        ui_draw_scrolltext ( "#*7337#" );
    }

    if ( samsung_phonetype == 28 )
    {
        ui_draw_scrolltext ( "#*7337#" );
    }

    if ( samsung_phonetype == 29 )
    {
        ui_draw_scrolltext ( "*2767*7822573738#" );
    }

    if ( samsung_phonetype == 30 )
    {
        ui_draw_scrolltext ( "Turn off the phone. Put a non-accepted SIM Card and turn it on. Type *#9998*3323#. Press Exit. Choose menu #7. After phone reboots type *0141# and hit the Call button. Turn off and insert another SIM Card. Turn on. The code is 00000000. or In newer phones: #*7337# or *2767*688#" );
    }

    if ( samsung_phonetype == 31 )
    {
        ui_draw_scrolltext ( "*2767*3377#" );
    }

    if ( samsung_phonetype == 32 )
    {
        ui_draw_scrolltext ( "1. Insert the wrong sim card into the phone, a message saying wrong sim card should appear on the screen. You can only make SOS calls at this point. 2. Enter in the phone *#9998*3323# 3. You will now see the option Exit on the left side of the phone. Hit the left soft key to exit. 4. Press the 7 key on the key pad. Your phone will now reboot. (Turn off & turn on automatically.) 5. After the phone turns back on it will be unlocked to your sim card in the phone. To finish unlocking the phone do the following steps. 6. Enter *0141# 7. Then hit the call button as if you were calling the above number. A small box saying Personalized will now appear. 8. Turn off your phone take off the battery, insert a different sim card than the one that was previously in the phone. 9. When you turn on the phone it will ask you for a SIM unlock code this number is 00000000 or 8 zeros. 10. Press OK & now your phone is unlocked to all networks." );
    }

    if ( samsung_phonetype == 33 )
    {
        ui_draw_scrolltext ( "*2767*3377# or Turn off the phone. Put a non-accepted SIM Card and turn it on. Type *#9998*3323#. Press Exit. Choose menu #7. After phone reboots type *0141# and hit the Call button. Turn off and insert another SIM Card. Turn on. The code is 00000000. or In newer phones: #*7337#" );
    }

}

#endif
