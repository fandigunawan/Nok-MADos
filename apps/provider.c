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
#include <apps/provider.h>

#ifndef LOADER

// Provider/GID1 codes list by GsmCyber

int country_type = 0;

MENU_CALLBACK ( network_country )
{
    char *entries[] = {
        "Albania",
        "Algeria",
        "Andorra",
        "Armenia",
        "Austria",
        "Australia",
        "Azerbeijan",
        "Bahrain",
        "Bangladesh",
        "Belgium",
        "Botswana",
        "Brazil",
        "Brunei Darussalam",
        "Bulgaria",
        "Cambodia",
        "Cameroon",
        "Canada",
        "Cape Verde",
        "China",
        "Columbia",
        "Cote d'Ivoire",
        "Croatia",
        "Cyprus",
        "Czech Republic",
        "Denmark",
        "Egypt",
        "Estonia",
        "Ethiopia",
        "Fiji Fiji",
        "Finland",
        "France",
        "Georgia",
        "Germany",
        "Ghana",
        "Gibraltar",
        "Greece",
        "Greenland",
        "Guinea",
        "Herzegovina,Bosnia",
        "Hong Kong",
        "Hungary",
        "Iceland",
        "India",
        "Indonesia",
        "Iran",
        "Iraq",
        "Ireland",
        "Israel",
        "Italy",
        "Japan",
        "Jordan",
        "Kazaksthan",
        "Kuwait",
        "Kyrgyz Republic",
        "Lao",
        "Latvia",
        "Lebanon",
        "Lesothp",
        "Liberia",
        "Lithuania",
        "Luxembourg",
        "Macau",
        "Macedonia",
        "Madagascar",
        "Malaysia",
        "Malawi",
        "Malta",
        "Mauritius",
        "Marocco",
        "Moldova",
        "Namibia",
        "Netherlands",
        "New Caledonia",
        "New Guinea",
        "New Zealand",
        "Norway",
        "Oman",
        "Pakistan",
        "Philippines",
        "Poland",
        "Polynesia",
        "Portugal",
        "Qatar",
        "Romania",
        "Russia",
        "Rwanda",
        "Saudi Arabia",
        "Senegal",
        "Seychelles",
        "Singapore",
        "Slovak Republic",
        "Slovenia",
        "South Africa",
        "Spain",
        "Sri Lanka",
        "Sudan",
        "Syria",
        "Sweden",
        "Switzerland",
        "Taiwan",
        "Tanzania",
        "Thailand",
        "Togo",
        "Tunisia",
        "Turkey",
        "U.S.A.",
        "Uganda",
        "Ukraine",
        "United Arab Emirates",
        "United Kingdom",
        "Uzbekistan",
        "Venezuela",
        "Vietnam",
        "Yugoslavia",
        "West Indies",
        "Zambia",
        "Zimbabwe", NULL
    };
    int t;

    switch ( cmd )
    {
        case MENU_SELECT:
            t = menu_dropdown ( entries, country_type );
            if ( t > -1 )
                country_type = t;
            break;
        case MENU_REDRAW:
        case MENU_DRAW:
            menu_disp ( entries[country_type] );
            break;
        default:
            break;
    }

}

int operator_type = 0;

MENU_CALLBACK ( network_provider )
{

    if ( country_type == 0 )
    {
        char *entries[] = { "Albanian Mobile Comms", "Vodafone", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 1 )
    {
        char *entries[] = { "Algerian Mobile Network", "Djezzy", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 2 )
    {
        char *entries[] = { "S.T.A. MobilAnd", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 3 )
    {
        char *entries[] = { "ArmenTel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 4 )
    {
        char *entries[] = { "MobilKom Austria A1", "T-Mobile", "Connect Austria One", "Tele.ring", "3AT", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 5 )
    {
        char *entries[] = { "Telstra Mobile Comms", "Optus", "Vodafone", "3", "OneTel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 6 )
    {
        char *entries[] = { "Acell Telekom B.M.", "BKcell GSM 2000", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 7 )
    {
        char *entries[] = { "Batelco", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 8 )
    {
        char *entries[] = { " Grameen Phone", "Aktel", "Sheba Telecom", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 9 )
    {
        char *entries[] = { "Proximus", "Mobistar", "Base", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 10 )
    {
        char *entries[] = { "Mascom Wireless", "Vista", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 11 )
    {
        char *entries[] = { "TIM", "Oi", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 12 )
    {
        char *entries[] = { "DST Communications", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 13 )
    {
        char *entries[] = { "MobilTel AD", "Globul", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 14 )
    {
        char *entries[] = { "Mobitel", "SM", "Camshin", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 15 )
    {
        char *entries[] = { "MTN", "Orange", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 16 )
    {
        char *entries[] = { "Fido", "Microcell Connexions Inc", "Rogers AT&T", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 17 )
    {
        char *entries[] = { "Cabo Verde Movel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 18 )
    {
        char *entries[] = { "China Telecom GSM", "China Unicom GSM", "Liaoning PPTA", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 19 )
    {
        char *entries[] = { "Comcel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 20 )
    {
        char *entries[] = { "Comstar Cellular Network", "Orange", "Telecel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 21 )
    {
        char *entries[] = { "Croatian Telecoms Cronet", "VIP", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 22 )
    {
        char *entries[] = { "Cyprus Telecoms Authority", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 23 )
    {
        char *entries[] = { "T-mobile", "EuroTel Praha", "Oskar", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 24 )
    {
        char *entries[] = { "Debitel", "Tele-Danmark Mobil", "Sonofon", "Telia Denmark", "Orange", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 25 )
    {
        char *entries[] = { "MobiNil", "Vodafone", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 26 )
    {
        char *entries[] = { "Estonian Mobile Telephone", "RadioLinja Eesti", "Tele 2", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 27 )
    {
        char *entries[] = { "Ethiopian Telecoms Auth.", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 28 )
    {
        char *entries[] = { "Vodafone", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 29 )
    {
        char *entries[] = { "Telia Finland", "Radiolinja", "Finnet Group", "2G Finland", "AMT", "Sonera Corporation", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 30 )
    {
        char *entries[] = { "Orange France", "SFR", "Bouygtel Telecom", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 31 )
    {
        char *entries[] = { "Geocell Limited", "Magti GSM", "Geo 03", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 32 )
    {
        char *entries[] = { "T-Mobile", "Vodafone", "E-Plus Mobilfunk", "O2", "MobilCom", "Quam", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 33 )
    {
        char *entries[] = { "ScanCom", "OneToch", "Mobitel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 34 )
    {
        char *entries[] = { "Gibraltar Telecoms Gibtel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 35 )
    {
        char *entries[] = { "Cosmote", "Vodafone", "Q-Telecom", "Telestet", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 36 )
    {
        char *entries[] = { "Tele Greenland", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 37 )
    {
        char *entries[] = { "Sotelgui Lagui", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 38 )
    {
        char *entries[] = { "Eronet", "Mobi's", "GSM BIH", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 39 )
    {
        char *entries[] = { "Hong Kong Telecom CSL", "Hutchison Telecom", "SmarTone Mobile Comms", "New World PCS", "Peoples Telephone", "Mandarin Com. Sunday", "Pacific Link", "P Plus Comm", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 40 )
    {
        char *entries[] = { "Pannon GSM", "Westel 900 GSM Mobile", "Vodafone", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 41 )
    {
        char *entries[] = { "Iceland Telecom Siminn", "TAL hf", "Islandss", "Viking", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 42 )
    {
        char *entries[] =
            { "Aircel Digilink Essar Cellph.", "Hutch", "TATA Cellular", "Ushafon", "Bharti Cellular Telecom Airtel", "Escotel Mobile Comms", "Ina Spice", "Orange", "BPL USWest Cellular",
            "Usha Martin Tel. Command", "Idea", "INA AIRTel", "RPG MAA", "Srinivas Cellcom", "Spice", "BSNL Mobile", "Dolphin", "Oasis", NULL
        };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 43 )
    {
        char *entries[] = { "PT. SATelindo C", "Lippo Telkomsel", "TelKomSel", "Pro XL", "IM3", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 44 )
    {
        char *entries[] = { "TCI", "Kish", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 45 )
    {
        char *entries[] = { "Iraq Telecom", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 46 )
    {
        char *entries[] = { "Vodafone", "O2", "Meteor", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 47 )
    {
        char *entries[] = { "Orange", "Cellcom", "JAWWAL", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 48 )
    {
        char *entries[] = { "Telecom Italia Mobile TIM", "Vodafone", "Wind Telecomunicazioni", "BLU", "3", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 49 )
    {
        char *entries[] = { "DoCoMo", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 50 )
    {
        char *entries[] = { "J.M.T.S Fastlink", "MobCom", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 51 )
    {
        char *entries[] = { "K-Mobile", "KCELL", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 52 )
    {
        char *entries[] = { "Mobile Telecoms MTCNet", "Wataniya", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 53 )
    {
        char *entries[] = { "Bitel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 54 )
    {
        char *entries[] = { "Lao Shinawatra Telecom", "ETLMNW", "LatMil", "Tango", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 55 )
    {
        char *entries[] = { "Latvian Mobile Tel.", "Tele 2", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 56 )
    {
        char *entries[] = { "FTML Cellis", "LibanCell", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 57 )
    {
        char *entries[] = { "VCL Comms", "Ezi Cel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 58 )
    {
        char *entries[] = { "Lonestar", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 59 )
    {
        char *entries[] = { "Omnitel", "UAB Bite GSM", "Tele 2", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 60 )
    {
        char *entries[] = { "P+T LUXGSM", "Millicom Tango GSM", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 61 )
    {
        char *entries[] = { "C.T.M. TELEMOVEL+", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 62 )
    {
        char *entries[] = { "MobiMak", "MTS AD", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 63 )
    {
        char *entries[] = { "Madacom", "SMM Antaris", "Sacel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 64 )
    {
        char *entries[] = { "Binariang", "Maxis", "Telekom Cellular TM Touch", "DiGi Telecommunications", "TimeCel Wireless Adam", "Celcom", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 65 )
    {
        char *entries[] = { "Telekom Network Callpoint", "CelTel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 66 )
    {
        char *entries[] = { "Vodafone", "Go Mobile", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 67 )
    {
        char *entries[] = { "Cellplus Mobile Comms", "Emtel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 68 )
    {
        char *entries[] = { "Meditel", "Itissalat Al-Maghrib IAM", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 69 )   //good number ;)
    {
        char *entries[] = { "Voxtel", "Moldcell", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 70 )
    {
        char *entries[] = { "MTC", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 71 )
    {
        char *entries[] = { "Vodafone", "KPN", "O2", "T-Mobile", "Orange", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 72 )
    {
        char *entries[] = { "Mobilis", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 73 )
    {
        char *entries[] = { "Pacific Mobile Comms Papua", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 74 )
    {
        char *entries[] = { "Vodafone", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 75 )
    {
        char *entries[] = { "Telenor Mobil", "NetCom GSM", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 76 )
    {
        char *entries[] = { "General Telecoms", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 77 )
    {
        char *entries[] = { "Ufone", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 78 )
    {
        char *entries[] = { "Isla Comms", "Globe Telecom", "Smart Communications", "DigiTel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 79 )
    {
        char *entries[] = { "Polkomtel PLUS GSM", "ERA GSM", "IDEA Centertel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 80 )
    {
        char *entries[] = { "Vini French", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 81 )
    {
        char *entries[] = { "Vodafone", "Optimus", "TMN", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 82 )
    {
        char *entries[] = { "QATARNET", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 83 )
    {
        char *entries[] = { "MobiFon CONNEX GSM", "Cosmorom", "Mobil Rom DIALOG", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 84 )
    {
        char *entries[] = { "MTS Moscow", "Megafon", "Siberian Cellular", "Zao Smarts", "Don Telecom", "New Telephone Company", "Kuban GSM", "Uratel", "North Caucasian GSM", "BeeLine", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 85 )
    {
        char *entries[] = { "Rwandacell", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 86 )
    {
        char *entries[] = { "Ministry of PTT Al Jawal", "Electronics App' Est. EAE", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 87 )
    {
        char *entries[] = { "Sonatel ALIZE", "Sentel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 88 )
    {
        char *entries[] = { "Seychelles Cellular Services", "AIRTEL", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 89 )
    {
        char *entries[] = { "Sing. Tel. GSM 900", "Sing. Tel. GSM 1800", "MobileOne Asia", "M1-3GSM", "StarHub", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 90 )
    {
        char *entries[] = { "Orange GSM", "EuroTel GSM", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 91 )
    {
        char *entries[] = { "Si.mobil", "Si-GSM", "Si VEGA 070", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 92 )
    {
        char *entries[] = { "Vodacom", "Cell C", "MTN", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 93 )
    {
        char *entries[] = { "Vodafone", "Movistar", "Amena", "Xfera", "Telefonica Movistar", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 94 )
    {
        char *entries[] = { "MTN Networks Dialog GSM", "CellTel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 95 )
    {
        char *entries[] = { "Mobile Telephone Company", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 96 )
    {
        char *entries[] = { "SyriaTel", "94", "MOBILE Syrian Telecom Est.", "SyriaTel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 97 )
    {
        char *entries[] = { "Telia Mobitel", "3", "Orange", "Comviq GSM", "Vodafone", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 98 )
    {
        char *entries[] = { "Swisscom NATEL", "Sunrise", "Orange", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 99 )
    {
        char *entries[] = { "Far EasTone Telecoms", "TUNTEX Telecom", "KG Telecom", "Chunghwa Telecom", "Mobitai Communications", "Pacific Cellular TWNGSM", "TransAsia Telecoms", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 100 )
    {
        char *entries[] = { "Tritel", "Mobitel", "Zantel", "CelTel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 101 )
    {
        char *entries[] = { "Advanced Info Service AIS", "Orange", "DTotal Access Worldphone", "GSM 1800", "Orange", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 102 )
    {
        char *entries[] = { "Togo Telecom TOGO CELL", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 103 )
    {
        char *entries[] = { "Tunisie Telecom Tunicell", "Tunisiana", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 104 )
    {
        char *entries[] = { "Turkcell", "TELSIM", "Aria", "Aycell", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 105 )
    {
        char *entries[] =
            { "AT&T", "APC Sprint Spectrum", "Wireless 2000 Telephone", "BellSouth Mobility DCS", "Cingular (Pacific Bell Wireless)", "T-Mobile", "Western Wireless Voicestream", "Powertel",
            "Aerial Communications", "Iowa Wireless Services", NULL
        };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 106 )
    {
        char *entries[] = { "Celtel Cellular", "MTN Uganda", "UTL Telecel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 107 )
    {
        char *entries[] = { "Ukrainian Mobile Comms", "Ukrainian Radio Systems", "Kyivstar GSM", "Golden Telecom", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 108 )
    {
        char *entries[] = { "UAE ETISALAT-G1", "UAE ETISALAT-G2", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 109 )
    {
        char *entries[] = { "Virgin", "02", "Vodafone", "3", "Virgin", "T-Mobile", "Orange", "Jersey Telecom GSM", "Guernsey Telecoms GSM", "Manx Telecom Pronto GSM", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 110 )
    {
        char *entries[] = { "Uzmacom", "Buztel", "Uzmacom", "Daewoo Unitel", "Coscom", "UZD", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 111 )
    {
        char *entries[] = { "Infonet", "Digitel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 112 )
    {
        char *entries[] = { "Mobifone", "Vinaphone", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 113 )
    {
        char *entries[] = { "MOBTEL", "ProMonte GSM", "03", "Monet Yugoslavia", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 114 )
    {
        char *entries[] = { "Orange French", "BouygTel French", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 115 )
    {
        char *entries[] = { "Celtel", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

    if ( country_type == 116 )
    {
        char *entries[] = { "NET*ONE", "Telecel", "Econet", NULL };
        int t;

        switch ( cmd )
        {
            case MENU_SELECT:
                t = menu_dropdown ( entries, operator_type );
                if ( t > -1 )
                    operator_type = t;
                break;
            case MENU_REDRAW:
            case MENU_DRAW:
                menu_disp ( entries[operator_type] );
                break;
            default:
                break;
        }
    }

}

MENU_CALLBACK ( network_mcc_mnc_gid1 )
{

    MENU_ONLY_SELECT;

    if ( country_type == 0 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 27601 GID1 Not avaible" );
        }

    if ( country_type == 0 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 27602 GID1 Not avaible" );
        }

    if ( country_type == 1 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 60301 GID1 Not avaible" );
        }

    if ( country_type == 1 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 60302 GID1 Not avaible" );
        }

    if ( country_type == 2 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 21303 GID1 Not avaible" );
        }

    if ( country_type == 3 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 28301 GID1 Not avaible" );
        }

    if ( country_type == 4 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23201 GID1 4D4B" );
        }

    if ( country_type == 4 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23203 GID1 Not avaible" );
        }

    if ( country_type == 4 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23205 GID1 Not avaible" );
        }

    if ( country_type == 4 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23207 GID1 Not avaible" );
        }

    if ( country_type == 4 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23210 GID1 Not avaible" );
        }

    if ( country_type == 5 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 50501 GID1 Not avaible" );
        }

    if ( country_type == 5 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 50502 GID1 Not avaible" );
        }

    if ( country_type == 5 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 50503 GID1 Not avaible" );
        }

    if ( country_type == 5 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 50503 GID1 Not avaible" );
        }

    if ( country_type == 5 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 50508 GID1 Not avaible" );
        }

    if ( country_type == 6 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40001 GID1 Not avaible" );
        }

    if ( country_type == 6 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40002 GID1 Not avaible" );
        }

    if ( country_type == 7 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 42601 GID1 Not avaible" );
        }

    if ( country_type == 8 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 47001 GID1 Not avaible" );
        }

    if ( country_type == 8 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 47002 GID1 Not avaible" );
        }

    if ( country_type == 8 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 47003 GID1 Not avaible" );
        }

    if ( country_type == 9 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 20601 GID1 Not avaible" );
        }

    if ( country_type == 9 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 20610 GID1 FFFF" );
        }

    if ( country_type == 9 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 20620 GID1 Not avaible" );
        }

    if ( country_type == 10 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 65201 GID1 Not avaible" );
        }

    if ( country_type == 10 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 65202 GID1 Not avaible" );
        }

    if ( country_type == 11 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 72402/72403/72404 GID1 Not avaible" );
        }

    if ( country_type == 11 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 72431 GID1 Not avaible" );
        }

    if ( country_type == 12 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 52811 GID1 Not avaible" );
        }

    if ( country_type == 13 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 28401 GID1 Not avaible" );
        }

    if ( country_type == 13 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 28405 GID1 Not avaible" );
        }

    if ( country_type == 14 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45601 GID1 Not avaible" );
        }

    if ( country_type == 14 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45602 GID1 Not avaible" );
        }

    if ( country_type == 14 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45618 GID1 Not avaible" );
        }
    if ( country_type == 15 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 62401 GID1 Not avaible" );
        }

    if ( country_type == 15 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 62402 GID1 Not avaible" );
        }

    if ( country_type == 16 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 30200001 GID1 Not avaible" );
        }

    if ( country_type == 16 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 30237 GID1 DDFF" );
        }

    if ( country_type == 16 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 30272 GID1 Not avaible" );
        }
    if ( country_type == 17 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 62501 GID1 Not avaible" );
        }

    if ( country_type == 18 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 46000 GID1 Not avaible" );
        }

    if ( country_type == 18 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 46001 GID1 Not avaible" );
        }

    if ( country_type == 18 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 46002 GID1 Not avaible" );
        }

    if ( country_type == 19 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 732101 GID1 Not avaible" );
        }

    if ( country_type == 20 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 61201 GID1 Not avaible" );
        }

    if ( country_type == 20 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 61203 GID1 Not avaible" );
        }

    if ( country_type == 20 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 61205 GID1 Not avaible" );
        }

    if ( country_type == 21 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 21901 GID1 Not avaible" );
        }

    if ( country_type == 21 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 21910 GID1 Not avaible" );
        }

    if ( country_type == 22 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 28001 GID1 Not avaible" );
        }

    if ( country_type == 23 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23001 GID1 Not avaible" );
        }

    if ( country_type == 23 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23002 GID1 Not avaible" );
        }

    if ( country_type == 23 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23003 GID1 Not avaible" );
        }

    if ( country_type == 24 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23800001 GID1 Not avaible" );
        }

    if ( country_type == 24 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23801 GID1 Not avaible" );
        }

    if ( country_type == 24 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23802 GID1 Not avaible" );
        }

    if ( country_type == 24 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23820 GID1 Not avaible" );
        }

    if ( country_type == 24 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23830 GID1 Not avaible" );
        }

    if ( country_type == 25 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 60201 GID1 Not avaible" );
        }

    if ( country_type == 25 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 60202 GID1 Not avaible" );
        }

    if ( country_type == 26 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24801 GID1 Not avaible" );
        }

    if ( country_type == 26 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24802 GID1 Not avaible" );
        }

    if ( country_type == 26 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24803 GID1 Not avaible" );
        }

    if ( country_type == 27 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 63601 GID1 Not avaible" );
        }

    if ( country_type == 28 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 54201 GID1 Not avaible" );
        }

    if ( country_type == 29 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24403 GID1 Not avaible" );
        }

    if ( country_type == 29 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24405 GID1 Not avaible" );
        }

    if ( country_type == 29 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24409 GID1 Not avaible" );
        }

    if ( country_type == 29 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24412 GID1 Not avaible" );
        }

    if ( country_type == 29 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24414 GID1 Not avaible" );
        }

    if ( country_type == 29 )
        if ( operator_type == 5 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24491 GID1 Not avaible" );
        }

    if ( country_type == 30 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 20801 GID1 0000/FFFF" );
        }

    if ( country_type == 30 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 20810 GID1 90FF/10FF" );
        }

    if ( country_type == 30 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 20820 GID1 Not avaible" );
        }

    if ( country_type == 31 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 28201 GID1 Not avaible" );
        }

    if ( country_type == 31 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 28202 GID1 Not avaible" );
        }

    if ( country_type == 31 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 28203 GID1 Not avaible" );
        }

    if ( country_type == 32 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 26201 GID1 Not avaible" );
        }

    if ( country_type == 32 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 26202 GID1 Not avaible" );
        }

    if ( country_type == 32 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 26203 GID1 Not avaible" );
        }

    if ( country_type == 32 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 26207 GID1 Not avaible" );
        }

    if ( country_type == 32 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 26213 GID1 Not avaible" );
        }

    if ( country_type == 32 )
        if ( operator_type == 5 )
        {
            ui_draw_scrolltext ( "MCC+MNC 26214 GID1 Not avaible" );
        }

    if ( country_type == 33 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 62001 GID1 Not avaible" );
        }

    if ( country_type == 33 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 62002 GID1 Not avaible" );
        }

    if ( country_type == 33 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 62003 GID1 Not avaible" );
        }

    if ( country_type == 34 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 26601 GID1 Not avaible" );
        }

    if ( country_type == 35 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 20201 GID1 Not avaible" );
        }

    if ( country_type == 35 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 20205 GID1 Not avaible" );
        }

    if ( country_type == 35 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 20209 GID1 Not avaible" );
        }

    if ( country_type == 35 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 20210 GID1 Not avaible" );
        }

    if ( country_type == 36 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 29001 GID1 Not avaible" );
        }

    if ( country_type == 37 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 61102 GID1 Not avaible" );
        }

    if ( country_type == 38 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 21803 GID1 Not avaible" );
        }

    if ( country_type == 38 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 21805 GID1 Not avaible" );
        }

    if ( country_type == 38 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 21890 GID1 Not avaible" );
        }

    if ( country_type == 39 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45400 GID1 Not avaible" );
        }

    if ( country_type == 39 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45404 GID1 Not avaible" );
        }

    if ( country_type == 39 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45406 GID1 Not avaible" );
        }

    if ( country_type == 39 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45410 GID1 Not avaible" );
        }

    if ( country_type == 39 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45412 GID1 Not avaible" );
        }

    if ( country_type == 39 )
        if ( operator_type == 5 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45416 GID1 Not avaible" );
        }

    if ( country_type == 39 )
        if ( operator_type == 6 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45418 GID1 Not avaible" );
        }

    if ( country_type == 39 )
        if ( operator_type == 7 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45422 GID1 Not avaible" );
        }

    if ( country_type == 40 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 21601 GID1 Not avaible" );
        }

    if ( country_type == 40 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 21630 GID1 Not avaible" );
        }

    if ( country_type == 40 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 21670 GID1 Not avaible" );
        }

    if ( country_type == 41 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 27401 GID1 Not avaible" );
        }

    if ( country_type == 41 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 27402 GID1 Not avaible" );
        }

    if ( country_type == 41 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 27403 GID1 Not avaible" );
        }

    if ( country_type == 41 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 27404 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40401/40415/40460 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40405/40411/40413/40486 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40407 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40408/40432 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40402/40403/40410/40431/40445/40449/40490/40492/40493/40494/40495/40496/40497/40498 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 5 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40412/40419/40456 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 6 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40414 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 7 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40420 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 8 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40421/40427/40434/40438/40443/40446 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 9 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40423/40426/40430 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 10 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40422/40424/40478 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 11 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40440 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 12 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40441 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 13 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40442 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 14 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40444 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 15 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40451/40453/40454/40455/40457/40458/40459/40462/40464/40466/40471/40472/40473/40474/40475/40476/40477/40479/40480/40481 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 16 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40468/40469 GID1 Not avaible" );
        }

    if ( country_type == 42 )
        if ( operator_type == 17 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40470 GID1 Not avaible" );
        }

    if ( country_type == 43 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 51001 GID1 Not avaible" );
        }

    if ( country_type == 43 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 51008 GID1 Not avaible" );
        }

    if ( country_type == 43 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 51010 GID1 Not avaible" );
        }

    if ( country_type == 43 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 51011 GID1 Not avaible" );
        }

    if ( country_type == 43 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 51021 GID1 Not avaible" );
        }

    if ( country_type == 44 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 43211 GID1 Not avaible" );
        }

    if ( country_type == 44 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 43214 GID1 Not avaible" );
        }

    if ( country_type == 45 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 41801 GID1 Not avaible" );
        }

    if ( country_type == 46 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 27201 GID1 Not avaible" );
        }

    if ( country_type == 46 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 27202 GID1 Not avaible" );
        }

    if ( country_type == 46 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 27203 GID1 Not avaible" );
        }

    if ( country_type == 47 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 42501 GID1 Never locked" );
        }

    if ( country_type == 47 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 42502 GID1 Never locked" );
        }

    if ( country_type == 47 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 42505 GID1 Never locked" );
        }

    if ( country_type == 48 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 22201 GID1 Not avaible" );
        }

    if ( country_type == 48 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 22210 GID1 Not avaible" );
        }

    if ( country_type == 48 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 22288 GID1 Not avaible" );
        }

    if ( country_type == 48 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 22298 GID1 Not avaible" );
        }

    if ( country_type == 48 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 22299 GID1 Not avaible" );
        }

    if ( country_type == 49 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 44010 GID1 Not avaible" );
        }

    if ( country_type == 50 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 41601 GID1 Not avaible" );
        }

    if ( country_type == 50 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 41677 GID1 Not avaible" );
        }

    if ( country_type == 51 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40101 GID1 Not avaible" );
        }

    if ( country_type == 51 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 40102 GID1 Not avaible" );
        }

    if ( country_type == 52 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 41902 GID1 Not avaible" );
        }

    if ( country_type == 52 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 41903 GID1 Not avaible" );
        }

    if ( country_type == 53 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 43701 GID1 Not avaible" );
        }

    if ( country_type == 54 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45701 GID1 Not avaible" );
        }

    if ( country_type == 54 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45702 GID1 Not avaible" );
        }

    if ( country_type == 54 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45703 GID1 Not avaible" );
        }

    if ( country_type == 54 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45708 GID1 Not avaible" );
        }

    if ( country_type == 55 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24701 GID1 Not avaible" );
        }

    if ( country_type == 55 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24702 GID1 Not avaible" );
        }

    if ( country_type == 56 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 41501 GID1 Not avaible" );
        }

    if ( country_type == 56 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 41503 GID1 Not avaible" );
        }

    if ( country_type == 57 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 65101 GID1 Not avaible" );
        }

    if ( country_type == 57 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 65102 GID1 Not avaible" );
        }

    if ( country_type == 58 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 61801 GID1 Not avaible" );
        }

    if ( country_type == 59 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24601 GID1 Not avaible" );
        }

    if ( country_type == 59 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24602 GID1 Not avaible" );
        }

    if ( country_type == 59 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24603 GID1 Not avaible" );
        }

    if ( country_type == 60 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 27001 GID1 Not avaible" );
        }

    if ( country_type == 60 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 27077 GID1 Not avaible" );
        }

    if ( country_type == 61 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45501 GID1 Not avaible" );
        }

    if ( country_type == 62 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 29401 GID1 Not avaible" );
        }

    if ( country_type == 62 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 29402 GID1 Not avaible" );
        }

    if ( country_type == 63 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 64601 GID1 Not avaible" );
        }

    if ( country_type == 63 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 64602 GID1 Not avaible" );
        }

    if ( country_type == 63 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 64603 GID1 Not avaible" );
        }

    if ( country_type == 64 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 50202 GID1 Not avaible" );
        }

    if ( country_type == 64 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 50212 GID1 Not avaible" );
        }

    if ( country_type == 64 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 50213 GID1 Not avaible" );
        }

    if ( country_type == 64 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 50216 GID1 Not avaible" );
        }

    if ( country_type == 64 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 50217 GID1 Not avaible" );
        }

    if ( country_type == 64 )
        if ( operator_type == 5 )
        {
            ui_draw_scrolltext ( "MCC+MNC 50219 GID1 Not avaible" );
        }

    if ( country_type == 65 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 65001 GID1 Not avaible" );
        }

    if ( country_type == 65 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 65010 GID1 Not avaible" );
        }

    if ( country_type == 66 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 27801 GID1 Not avaible" );
        }

    if ( country_type == 66 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 27821 GID1 Not avaible" );
        }

    if ( country_type == 67 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 61701 GID1 Not avaible" );
        }

    if ( country_type == 67 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 61710 GID1 Not avaible" );
        }

    if ( country_type == 68 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 60400 GID1 Not avaible" );
        }

    if ( country_type == 68 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 60401 GID1 Not avaible" );
        }

    if ( country_type == 69 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 25901 GID1 Not avaible" );
        }

    if ( country_type == 69 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 25902 GID1 Not avaible" );
        }

    if ( country_type == 70 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 64901 GID1 Not avaible" );
        }

    if ( country_type == 71 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 20404 GID1 Not avaible" );
        }

    if ( country_type == 71 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 20408 GID1 5050" );
        }

    if ( country_type == 71 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 20412 GID1 Not avaible" );
        }

    if ( country_type == 71 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 20416 GID1 Not avaible" );
        }

    if ( country_type == 71 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 20420 GID1 504F" );
        }

    if ( country_type == 72 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 54601 GID1 Not avaible" );
        }

    if ( country_type == 73 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 31001 GID1 Not avaible" );
        }

    if ( country_type == 74 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 53001 GID1 Not avaible" );
        }

    if ( country_type == 75 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24201 GID1 Not avaible" );
        }

    if ( country_type == 75 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24202 GID1 Not avaible" );
        }

    if ( country_type == 76 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 42202 GID1 Not avaible" );
        }

    if ( country_type == 77 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 41001 GID1 Not avaible" );
        }

    if ( country_type == 78 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 51501 GID1 Not avaible" );
        }

    if ( country_type == 78 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 51502 GID1 Not avaible" );
        }

    if ( country_type == 78 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 51503 GID1 Not avaible" );
        }

    if ( country_type == 78 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 51505 GID1 Not avaible" );
        }

    if ( country_type == 79 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 26001 GID1 Not avaible" );
        }

    if ( country_type == 79 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 26002 GID1 Not avaible" );
        }

    if ( country_type == 79 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 26003 GID1 Not avaible" );
        }

    if ( country_type == 80 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 54720 GID1 Not avaible" );
        }

    if ( country_type == 81 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 26801 GID1 Never locked" );
        }

    if ( country_type == 81 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 26803 GID1 Never locked" );
        }

    if ( country_type == 81 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 26806 GID1 Never locked" );
        }

    if ( country_type == 82 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 42701 GID1 Not avaible" );
        }

    if ( country_type == 83 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 22601 GID1 Not avaible" );
        }

    if ( country_type == 83 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 22603 GID1 Not avaible" );
        }

    if ( country_type == 83 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 22610 GID1 Not avaible" );
        }

    if ( country_type == 84 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 25001 GID1 Not avaible" );
        }

    if ( country_type == 84 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 25002 GID1 Not avaible" );
        }

    if ( country_type == 84 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 25005 GID1 Not avaible" );
        }

    if ( country_type == 84 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 25007 GID1 Not avaible" );
        }

    if ( country_type == 84 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 25010 GID1 Not avaible" );
        }

    if ( country_type == 84 )
        if ( operator_type == 5 )
        {
            ui_draw_scrolltext ( "MCC+MNC 25012 GID1 Not avaible" );
        }

    if ( country_type == 84 )
        if ( operator_type == 6 )
        {
            ui_draw_scrolltext ( "MCC+MNC 25013 GID1 Not avaible" );
        }

    if ( country_type == 84 )
        if ( operator_type == 7 )
        {
            ui_draw_scrolltext ( "MCC+MNC 25039 GID1 Not avaible" );
        }

    if ( country_type == 84 )
        if ( operator_type == 8 )
        {
            ui_draw_scrolltext ( "MCC+MNC 25044 GID1 Not avaible" );
        }

    if ( country_type == 84 )
        if ( operator_type == 9 )
        {
            ui_draw_scrolltext ( "MCC+MNC 25099 GID1 Not avaible" );
        }

    if ( country_type == 85 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 63510 GID1 Not avaible" );
        }

    if ( country_type == 86 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 42001 GID1 Not avaible" );
        }

    if ( country_type == 86 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 42007 GID1 Not avaible" );
        }

    if ( country_type == 87 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 60801 GID1 Not avaible" );
        }

    if ( country_type == 87 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 60802 GID1 Not avaible" );
        }

    if ( country_type == 88 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 63301 GID1 Not avaible" );
        }

    if ( country_type == 88 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 63310 GID1 Not avaible" );
        }

    if ( country_type == 89 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 52501 GID1 Not avaible" );
        }

    if ( country_type == 89 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 52502 GID1 Not avaible" );
        }

    if ( country_type == 89 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 52503 GID1 Not avaible" );
        }

    if ( country_type == 89 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 52504 GID1 Not avaible" );
        }

    if ( country_type == 89 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 52505 GID1 Not avaible" );
        }

    if ( country_type == 90 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23101 GID1 Not avaible" );
        }

    if ( country_type == 90 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23102 GID1 Not avaible" );
        }

    if ( country_type == 91 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 29340 GID1 Not avaible" );
        }

    if ( country_type == 91 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 29341 GID1 Not avaible" );
        }

    if ( country_type == 91 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 29370 GID1 Not avaible" );
        }

    if ( country_type == 92 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 65501 GID1 Not avaible" );
        }

    if ( country_type == 92 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 65507 GID1 Not avaible" );
        }

    if ( country_type == 92 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 65510 GID1 Not avaible" );
        }

    if ( country_type == 93 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 21401 GID1 FFFF" );
        }

    if ( country_type == 93 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 21402 GID1 Not avaible" );
        }

    if ( country_type == 93 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 21403 GID1 Not avaible" );
        }

    if ( country_type == 93 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 21404 GID1 Not avaible" );
        }

    if ( country_type == 93 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 21407 GID1 01FF/10FF" );
        }

    if ( country_type == 94 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 41302 GID1 Not avaible" );
        }

    if ( country_type == 94 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 41303 GID1 Not avaible" );
        }

    if ( country_type == 95 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 63401 GID1 Not avaible" );
        }

    if ( country_type == 96 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 41701 GID1 Not avaible" );
        }

    if ( country_type == 96 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 41702 GID1 Not avaible" );
        }

    if ( country_type == 96 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 41709 GID1 Not avaible" );
        }

    if ( country_type == 96 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 41793 GID1 Not avaible" );
        }

    if ( country_type == 97 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24001 GID1 Not avaible" );
        }

    if ( country_type == 97 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24002 GID1 Not avaible" );
        }

    if ( country_type == 97 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24003 GID1 Not avaible" );
        }

    if ( country_type == 97 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24007 GID1 Not avaible" );
        }

    if ( country_type == 97 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24008 GID1 Not avaible" );
        }

    if ( country_type == 98 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 22801 GID1 Not avaible" );
        }

    if ( country_type == 98 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 22802 GID1 Not avaible" );
        }

    if ( country_type == 98 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 22803 GID1 Not avaible" );
        }

    if ( country_type == 99 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 46601 GID1 Not avaible" );
        }

    if ( country_type == 99 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 46606 GID1 Not avaible" );
        }

    if ( country_type == 99 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 46688 GID1 Not avaible" );
        }

    if ( country_type == 99 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 46692 GID1 Not avaible" );
        }

    if ( country_type == 99 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 46693 GID1 Not avaible" );
        }

    if ( country_type == 99 )
        if ( operator_type == 5 )
        {
            ui_draw_scrolltext ( "MCC+MNC 46697 GID1 Not avaible" );
        }

    if ( country_type == 99 )
        if ( operator_type == 6 )
        {
            ui_draw_scrolltext ( "MCC+MNC 46699 GID1 Not avaible" );
        }

    if ( country_type == 100 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 64001 GID1 Not avaible" );
        }

    if ( country_type == 100 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 64002 GID1 Not avaible" );
        }

    if ( country_type == 100 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 64003 GID1 Not avaible" );
        }

    if ( country_type == 100 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 64005 GID1 Not avaible" );
        }

    if ( country_type == 101 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 52001 GID1 Not avaible" );
        }

    if ( country_type == 101 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 52010 GID1 Not avaible" );
        }

    if ( country_type == 101 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 52018 GID1 Not avaible" );
        }

    if ( country_type == 101 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 52023 GID1 Not avaible" );
        }

    if ( country_type == 101 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 52099 GID1 Not avaible" );
        }

    if ( country_type == 102 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 61501 GID1 Not avaible" );
        }

    if ( country_type == 103 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 60502 GID1 Not avaible" );
        }

    if ( country_type == 103 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 60503 GID1 Not avaible" );
        }

    if ( country_type == 104 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 28601 GID1 Not avaible" );
        }

    if ( country_type == 104 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 28602 GID1 Not avaible" );
        }

    if ( country_type == 104 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 28603 GID1 Not avaible" );
        }

    if ( country_type == 104 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 28604 GID1 Not avaible" );
        }

    if ( country_type == 105 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 24407/31038 GID1 Not avaible" );
        }

    if ( country_type == 105 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 31002 GID1 Not avaible" );
        }

    if ( country_type == 105 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 31011 GID1 Not avaible" );
        }

    if ( country_type == 105 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 31015 GID1 Not avaible" );
        }

    if ( country_type == 105 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 31017 GID1 Not avaible" );
        }

    if ( country_type == 105 )
        if ( operator_type == 5 )
        {
            ui_draw_scrolltext ( "MCC+MNC 31020 GID1 Not avaible" );
        }

    if ( country_type == 105 )
        if ( operator_type == 6 )
        {
            ui_draw_scrolltext ( "MCC+MNC 31026 GID1 Not avaible" );
        }

    if ( country_type == 105 )
        if ( operator_type == 7 )
        {
            ui_draw_scrolltext ( "MCC+MNC 31027 GID1 Not avaible" );
        }

    if ( country_type == 105 )
        if ( operator_type == 8 )
        {
            ui_draw_scrolltext ( "MCC+MNC 31031 GID1 Not avaible" );
        }

    if ( country_type == 105 )
        if ( operator_type == 9 )
        {
            ui_draw_scrolltext ( "MCC+MNC 31077 GID1 Not avaible" );
        }

    if ( country_type == 106 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 64101 GID1 Not avaible" );
        }

    if ( country_type == 106 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 64110 GID1 Not avaible" );
        }

    if ( country_type == 106 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 64111 GID1 Not avaible" );
        }

    if ( country_type == 107 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 25501 GID1 Not avaible" );
        }

    if ( country_type == 107 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 25502 GID1 Not avaible" );
        }

    if ( country_type == 107 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 25503 GID1 Not avaible" );
        }

    if ( country_type == 107 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 25505 GID1 Not avaible" );
        }

    if ( country_type == 108 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 42401 GID1 Not avaible" );
        }

    if ( country_type == 108 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 42402 GID1 Not avaible" );
        }

    if ( country_type == 109 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23400001 GID1 Not avaible" );
        }

    if ( country_type == 109 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23410 GID1 0AFF/10FF" );
        }

    if ( country_type == 109 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23415 GID1 E1FF" );
        }

    if ( country_type == 109 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23420 GID1 Not avaible" );
        }

    if ( country_type == 109 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23430 GID1 2800" );
        }

    if ( country_type == 109 )
        if ( operator_type == 5 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23430 GID1 Not avaible" );
        }

    if ( country_type == 109 )
        if ( operator_type == 6 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23433 GID1 0000" );
        }

    if ( country_type == 109 )
        if ( operator_type == 7 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23450 GID1 Not avaible" );
        }

    if ( country_type == 109 )
        if ( operator_type == 8 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23455 GID1 Not avaible" );
        }

    if ( country_type == 109 )
        if ( operator_type == 9 )
        {
            ui_draw_scrolltext ( "MCC+MNC 23458 GID1 Not avaible" );
        }

    if ( country_type == 110 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 43400 GID1 Not avaible" );
        }

    if ( country_type == 110 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 43401 GID1 Not avaible" );
        }

    if ( country_type == 110 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 43402 GID1 Not avaible" );
        }

    if ( country_type == 110 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 43404 GID1 Not avaible" );
        }

    if ( country_type == 110 )
        if ( operator_type == 4 )
        {
            ui_draw_scrolltext ( "MCC+MNC 43405 GID1 Not avaible" );
        }

    if ( country_type == 110 )
        if ( operator_type == 5 )
        {
            ui_draw_scrolltext ( "MCC+MNC 43407 GID1 Not avaible" );
        }

    if ( country_type == 111 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 73401 GID1 Not avaible" );
        }

    if ( country_type == 111 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 73402 GID1 Not avaible" );
        }

    if ( country_type == 112 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45201 GID1 Not avaible" );
        }

    if ( country_type == 112 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 45202 GID1 Not avaible" );
        }

    if ( country_type == 113 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 22001 GID1 Not avaible" );
        }

    if ( country_type == 113 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 22002 GID1 Not avaible" );
        }

    if ( country_type == 113 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 22003 GID1 Not avaible" );
        }

    if ( country_type == 113 )
        if ( operator_type == 3 )
        {
            ui_draw_scrolltext ( "MCC+MNC 22004 GID1 Not avaible" );
        }

    if ( country_type == 114 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 34001 GID1 Not avaible" );
        }

    if ( country_type == 114 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 34020 GID1 Not avaible" );
        }

    if ( country_type == 115 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 64501 GID1 Not avaible" );
        }

    if ( country_type == 116 )
        if ( operator_type == 0 )
        {
            ui_draw_scrolltext ( "MCC+MNC 64801 GID1 Not avaible" );
        }

    if ( country_type == 116 )
        if ( operator_type == 1 )
        {
            ui_draw_scrolltext ( "MCC+MNC 64803 GID1 Not avaible" );
        }

    if ( country_type == 116 )
        if ( operator_type == 2 )
        {
            ui_draw_scrolltext ( "MCC+MNC 64804 GID1 Not avaible" );
        }

}

#endif
