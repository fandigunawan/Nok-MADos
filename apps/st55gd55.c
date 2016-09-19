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
#include <apps/st55gd55.h>

#ifndef LOADER

unsigned char st55gd55_phoneimei[32] = "350005203385342";

void
st55gd55_calc ( unsigned char model )
{

    char *types[] = { "NCKKN", "NSCKN", "SPCKS", "CKCCK", "PCKKP", 0 };

    unsigned char complete_message[256];
    unsigned char buffer[10];
    unsigned char /*prefix_1 = 1, prefix_2 = 2, */ c, actual_type;
    memset ( complete_message, 0, 256 );

    for ( c = 0; c < 10; c++ )
    {
        // hope this is a nice algo too :P
        if ( model != 3 )
            actual_type = lib_div ( c, 2 );
        else
            actual_type = c;
        strcat ( complete_message, types[actual_type] );
        if ( lib_mod ( c, 2 ) == 1 && model != 3 )
            strcat ( complete_message, "-2" );
        strcat ( complete_message, "(**000" );
        if ( model != 3 )
            sprintf ( buffer, "%d%d*\00", lib_div ( c, 2 ) + 1, lib_mod ( c, 2 ) + 2 );
        else
        {
            if ( c != 4 )
                sprintf ( buffer, "%d2*\00", c + 1 );
            else
                sprintf ( buffer, "%d3*\00", c + 1 );
        }
        strcat ( complete_message, buffer );
        memset ( buffer, 0, 10 );
        st55gd55_algo ( st55gd55_phoneimei, types[actual_type], !lib_mod ( c, 2 ) + 1, model, buffer );
        strcat ( complete_message, buffer );
        strcat ( complete_message, "#) " );
        if ( model == 3 && c == 4 )
            break;
    }


    ui_draw_scrolltext ( complete_message );


}

MENU_CALLBACK ( st55gd55_imei )
{
    MENU_SCROLL_INIT ( 2 );

    switch ( cmd )
    {
        case MENU_SELECT:
            memset ( st55gd55_phoneimei, 0x00, 32 );
            ui_gettext ( "enter IMEI", 15, st55gd55_phoneimei, UI_TYPE_NUMBER );
            break;
        case MENU_REDRAW:
            if ( st55gd55_phoneimei )
            {
                MENU_SCROLL ( st55gd55_phoneimei );
            }
            break;
        case MENU_DRAW:
            MENU_SCROLL_RESET;
            break;
        default:
            break;
    }
}

MENU_CALLBACK ( st55gd55_calc_cl50 )
{
    MENU_ONLY_SELECT;
    st55gd55_calc ( 3 );
}

MENU_CALLBACK ( st55gd55_calc_st55 )
{
    MENU_ONLY_SELECT;
    st55gd55_calc ( 2 );
}

MENU_CALLBACK ( st55gd55_calc_gd55 )
{
    MENU_ONLY_SELECT;
    st55gd55_calc ( 1 );
}

void
st55gd55_algo ( char *IMEI, char *std, unsigned char code, unsigned char model, char *output )
{

/*
    Phone Code by IMEI
    For Panasonic GD55 & ST55

    Insert support for Siemens ST55 by SEN

    Reversing from PhoneLock Generator v 1.0 for Siemens GD50
    by SEN (aka sendel in www.siemen-club.ru)
    sendel2000@hotbox.ru
    (C)VIOLATORS group. 1995-2003
*/
/*
    Phone Code by IMEI
    For Siemens CL50

    Reversing from PhoneLock Generator v 1.0 for Siemens CL50
    by SEN (aka sendel in www.siemen-club.ru)
    sendel2000@hotbox.ru
    (C)VIOLATORS group. 1995-2003


    HELP ME!!! I want make it for ALL SIEMENS:)))
*/

/*
    ported to & merged together & fixed for MADos
    why have 2 similar algo's if it
    could be in one ?! :p
*/

    char IMEI_PATCH[17], IMEI74[17], IMEI9C[17];
    char IMEICC[37];

    char std1[4];
    static const char gd55[] = "VE1";
    static const char st55[] = "CE2";
    static const char cl50[] = "DG1";

    char dest[16];
    int b = 0;
    int i;


    switch ( model )
    {
        case 1:
            strcpy ( std1, gd55 );
            break;
        case 2:
            strcpy ( std1, st55 );
            break;
        case 3:
            strcpy ( std1, cl50 );
            break;
    }

    memset ( dest, 0, 16 );

    memset ( IMEICC, 0, 37 );

    strcpy ( dest, std1 );


    for ( i = 0; i < 8; i++ )
    {
        b += IMEI[i + 6];
        IMEI_PATCH[i] = IMEI[i + 6];
    }

    for ( i = 0; i < 8; i++ )
    {
        IMEI_PATCH[i + 8] = 0x64 - IMEI_PATCH[i];
    }

    IMEI_PATCH[16] = 0;


    switch ( lib_mod ( b, 3 ) )
    {
        default:
        case 0:
            for ( i = 0; i < 16; i++ )
            {
                IMEI74[i] = IMEI_PATCH[i];
            };
            break;

        case 1:
            for ( i = 0; i < 16; i++ )
            {
                IMEI74[15 - i] = IMEI_PATCH[i];
            };
            break;

        case 2:
            for ( i = 0; i < 16; i++ )
            {
                if ( !( lib_mod ( i, 2 ) ) )
                {
                    IMEI74[i] = IMEI_PATCH[i + 1];
                }
                else
                {
                    IMEI74[i] = IMEI_PATCH[i - 1];
                }
            };
            break;
    }


    strcat ( dest, std );
    if ( model != 3 )
    {
        strcat ( dest, std );
        strcat ( dest, std1 );
    }
    else
    {
        strcat ( dest, std1 );
        strcat ( dest, std );
    }


    for ( i = 0; i < 16; i++ )
    {
        IMEI9C[i] = lib_mod ( ( IMEI74[i] + dest[i] ), 100 );
    }

    IMEI74[16] = 0;
    IMEI9C[16] = 0;

    if ( model != 3 )
    {
        switch ( lib_mod ( b, 5 ) )
        {
            default:
            case 0:
                for ( i = 0; i < 8; i++ )
                    IMEICC[i] = lib_mod ( ( ( ( IMEI74[i * 2] & dest[i * 2] ) | IMEI9C[i * 2] ) & IMEI9C[i * 2] ), 10 );

                for ( i = 0; i < 8; i++ )
                    IMEICC[i + 8] = lib_mod ( ( ( ( IMEI74[i * 2 + 1] & dest[i * 2 + 1] ) | IMEI9C[i * 2 + 1] ) & IMEI9C[i * 2 + 1] ), 10 );
                break;
            case 1:
                for ( i = 0; i < 8; i++ )
                    IMEICC[i] = lib_mod ( ( IMEI74[i * 2] | dest[i * 2] | IMEI9C[i * 2] | IMEI9C[i * 2] ), 10 );

                for ( i = 0; i < 8; i++ )
                    IMEICC[i + 8] = lib_mod ( ( IMEI74[i * 2 + 1] | dest[i * 2 + 1] | IMEI9C[i * 2 + 1] | IMEI9C[i * 2 + 1] ), 10 );

                break;

            case 2:
                for ( i = 0; i < 8; i++ )
                    IMEICC[i] = lib_mod ( ( ( IMEI74[i * 2] | dest[i * 2] ) & IMEI9C[i * 2] | IMEI9C[i * 2] ), 10 );

                for ( i = 0; i < 8; i++ )
                    IMEICC[i + 8] = lib_mod ( ( ( IMEI74[i * 2 + 1] | dest[i * 2 + 1] ) & IMEI9C[i * 2 + 1] | IMEI9C[i * 2 + 1] ), 10 );
                break;

            case 3:
                for ( i = 0; i < 8; i++ )
                    IMEICC[i] = lib_mod ( ( ( IMEI74[i * 2] | dest[i * 2] | IMEI9C[i * 2] ) & IMEI9C[i * 2] ), 10 );

                for ( i = 0; i < 8; i++ )
                    IMEICC[i + 8] = lib_mod ( ( ( IMEI74[i * 2 + 1] | dest[i * 2 + 1] | IMEI9C[i * 2 + 1] ) & IMEI9C[i * 2 + 1] ), 10 );

                break;
            case 4:
                for ( i = 0; i < 8; i++ )
                    IMEICC[i] = lib_mod ( ( ( IMEI74[i * 2] & dest[i * 2] ) | IMEI9C[i * 2] | IMEI9C[i * 2] ), 10 );

                for ( i = 0; i < 8; i++ )
                    IMEICC[i + 8] = lib_mod ( ( ( IMEI74[i * 2 + 1] & dest[i * 2 + 1] ) | IMEI9C[i * 2 + 1] | IMEI9C[i * 2 + 1] ), 10 );
        }
    }
    else
    {
        switch ( lib_mod ( b, 10 ) )
        {
            case 1:
                for ( i = 0; i < 8; i++ )
                {
                    IMEICC[i] = lib_mod ( IMEI74[i * 2] | dest[i * 2] | IMEI9C[i * 2] | IMEI9C[i * 2], 10 );
                }
                break;
            case 2:
                for ( i = 0; i < 8; i++ )
                {
                    IMEICC[i] = lib_mod ( IMEI74[( i * 2 ) + 1] | dest[( i * 2 ) + 1] | IMEI9C[( i * 2 ) + 1] | IMEI9C[( i * 2 ) + 1], 10 );
                }
                break;
            case 3:
                for ( i = 0; i < 8; i++ )
                {
                    IMEICC[i] = lib_mod ( ( IMEI74[i * 2] | dest[i * 2] ) & IMEI9C[i * 2] | IMEI9C[i * 2], 10 );
                }
                break;
            case 4:
                for ( i = 0; i < 8; i++ )
                {
                    IMEICC[i] = lib_mod ( ( IMEI74[( i * 2 ) + 1] | dest[( i * 2 ) + 1] ) & IMEI9C[( i * 2 ) + 1] | IMEI9C[( i * 2 ) + 1], 10 );
                }
                break;
            case 5:
                for ( i = 0; i < 8; i++ )
                {
                    IMEICC[i] = lib_mod ( ( IMEI74[i * 2] | dest[i * 2] | IMEI9C[i * 2] ) & IMEI9C[i * 2], 10 );
                }
                break;
            case 6:
                for ( i = 0; i < 8; i++ )
                {
                    IMEICC[i] = lib_mod ( ( IMEI74[( i * 2 ) + 1] | dest[( i * 2 ) + 1] | IMEI9C[( i * 2 ) + 1] ) & IMEI9C[( i * 2 ) + 1], 10 );
                }
                break;
            case 7:
                for ( i = 0; i < 8; i++ )
                {
                    IMEICC[i] = lib_mod ( ( IMEI74[i * 2] & dest[i * 2] ) | IMEI9C[i * 2] | IMEI9C[i * 2], 10 );
                }
                break;
            case 8:
                for ( i = 0; i < 8; i++ )
                {
                    IMEICC[i] = lib_mod ( ( IMEI74[( i * 2 ) + 1] ) & dest[( i * 2 ) + 1] | IMEI9C[( i * 2 ) + 1] | IMEI9C[( i * 2 ) + 1], 10 );
                }
                break;
            case 9:
                for ( i = 0; i < 8; i++ )
                {
                    IMEICC[i] = lib_mod ( ( ( IMEI74[i * 2] & dest[i * 2] ) | IMEI9C[i * 2] ) & IMEI9C[i * 2], 10 );
                }
                break;
            default:
                for ( i = 0; i < 8; i++ )
                {
                    IMEICC[i] = lib_mod ( ( ( IMEI74[( i * 2 ) + 1] & dest[( i * 2 ) + 1] ) | IMEI9C[( i * 2 ) + 1] ) & IMEI9C[( i * 2 ) + 1], 10 );
                }
        }
    }


    memset ( std1, 0, 4 );
    if ( code == 1 && model != 3 )
        for ( i = 0; i < 8; i++ )
        {
            sprintf ( std1, "%d", IMEICC[i + 8] );
            strcat ( output, std1 );
        }
    else
        for ( i = 0; i < 8; i++ )
        {
            sprintf ( std1, "%d", IMEICC[i] );
            strcat ( output, std1 );
        };



}

#endif
