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



/*
 *   http://www.panasonic.com/industrial/battery/oem/images/pdf/Panasonic_LiIon_Charging.pdf
 *   http://www.national.com/appinfo/power/files/f7.pdf
 */

/*
 * BSI values
 * 
 * 38  BMC-3
 * 38  BMC-3
 * 62  BMC-3
 * 63  BMC-3
 * 66  BMC-3
 * 643 BLC-1
 * 633 BLC-1
 * 684 BLC-2
 *
 */

#include <apps/charger.h>
#include <core/bitmap.h>
#include <core/lib.h>
#include <hw/mbus.h>
#include <hw/io.h>
#include <hw/ioports.h>
#include <hw/ccont.h>

#define ub ccont_get_ub()
#define uc ccont_get_uc()
#define ic ccont_get_ic()
#define bi ccont_get_bi()

extern unsigned char startup;
#define NORMAL 0
#define CHARGE 1
/*
 * charger configuration
 *
 *  for Li-Ion  [0]
 *      NiMH/Cd [1]   
 *      Service [2]
 */
int charger__min_charge_uc[] = { 4500, 4500, 99999 };
int charger__overloaded_ub[] = { 4200, 4095, 0 };
int charger__cool_down__ub[] = { 4170, 4060, 1 };
int charger__nearlyfull_ub[] = { 4150, 4000, 0 };
int charger__empty_batt_ub[] = { 2700, 2700, 0 };
int charger__discharged_ub[] = { 2300, 2400, 0 };

char *charger_battname[] = { "Li-Ion", "NiCd/NiMH", "Service" };

/*
 *   the different delays in 500ms for each of the chargers states
 */
int charger_delays[] = { 20, 40, 10, 10, 10, 1 };


/*
 * global variables
 */
int charger_prev_state = 0;
int charger_state = BATT_NORM;
int charger_run = 1;
int charger_power = 0;
int charger_discharge = 0;
int charger_maxcurrent = 0;
int charger_maxvoltage = 0;
int charger_battery = 0;

int charger_un = 0;
int charger_ub = 0;
int charger_uc = 0;
int charger_ic = 0;
int charger_locked = 0;

int
charger_get_batt ( void )
{
    return charger_battery;
}

char *
charger_get_battname ( void )
{
    return charger_battname[charger_battery];
}

int
charger_lock ( void )
{
    charger_locked = 1;
}

int
charger_unlock ( void )
{
    charger_locked = 0;
}

int
charger_get_un ( void )
{
    return charger_un;
}

int
charger_get_ub ( void )
{
    return charger_ub;
}

int
charger_get_uc ( void )
{
    return charger_uc;
}

int
charger_get_ic ( void )
{
    return charger_ic;
}

int
charger_get_state ( void )
{
    return charger_state;
}

int
charger_get_power ( void )
{
    return charger_power;
}

int
charger_get_discharge ( void )
{
    return charger_discharge;
}

int
charger_get_maxcurrent ( void )
{
    return charger_maxcurrent;
}

int
charger_get_maxvoltage ( void )
{
    return charger_maxvoltage;
}


int
charger_set_current ( int power )
{
    charger_power = power;
    return 1;
}


int
charger_get_battstate ( void )
{
    int state;
    int u = charger_ub;

    if ( u >= charger__overloaded_ub[charger_battery] )
        state = BATT_OVERLOAD;
    else if ( u > charger__nearlyfull_ub[charger_battery] )
        state = BATT_SLOWCHARGE;
    else if ( u < charger__discharged_ub[charger_battery] )
        state = BATT_OVERDISCHARGED;
    else if ( u < charger__empty_batt_ub[charger_battery] )
        state = BATT_SLOWCHARGE;
    else if ( u > charger_discharge && charger_discharge )
        state = BATT_DISCHARGE;
    else
        state = BATT_CHARGE;

    return state;
}

int
charger_set_power ( void )
{
    if ( charger_power > 1 )
    {
        ccont_set_charger ( 1 );
        // set CCUT to low
        _io_clr_bit ( IO_PUP_GENIO, 0x01 );
    }
    else
    {
        ccont_set_charger ( 0 );
        // set CCUT to high
        _io_set_bit ( IO_PUP_GENIO, 0x01 );
    }
    ccont_set_chargemode ( charger_power );
}


int
charger_connected ( void )
{
    if ( uc > charger__min_charge_uc[charger_battery] )
        return 1;

    return 0;
}

int
charger_update ( void )
{
    charger_ub = ub;
    // if no charger is connected, update *REAL* Ub (named Un, Unominal)
    if ( !charger_connected (  ) || charger_power == CHARGE_OFF )
        charger_un = charger_ub;
    charger_uc = uc;
    charger_ic = ic;
}

int
charger_main ( void )
{
    int saved = 0;
    int i = 0;
    int bsi = 0;
    int cycle = 0;
    char txt[128];

    if ( startup != CHARGE )
        sleep ( 5 );
    mbus_print ( "CHARGER: Initializing\r\n" );

    // disable CHAR_CTRL so we have 4.8/5.2V limit
    _io_clr_bit ( IO_UIF_CTRL3, 0x40 );

    // and disable charging
    charger_power = CHARGE_OFF;
    charger_set_power (  );

    bsi = bi;

    // set CCUT to low
    _io_clr_bit ( IO_PUP_GENIO, 0x01 );

    if ( bsi < 100 )
    {
        // NiCd/NiMH
        charger_battery = 1;
        // set VLIM to high, for Ni batteries
        _io_set_bit ( IO_PUP_GENIO, 0x10 );
    }
    else if ( bsi < 500 )
    {
        // service battery
        charger_battery = 2;
        // set VLIM to high, for Ni batteries
        _io_set_bit ( IO_PUP_GENIO, 0x10 );
    }
    else if ( bsi < 800 )
    {
        // Li-Ion
        charger_battery = 0;
        // set VLIM to high, for Ni batteries
        _io_clr_bit ( IO_PUP_GENIO, 0x10 );
    }

    // initially fill in the measured values
    charger_update (  );

    sprintf ( txt, "CHARGER: Found Battery: %s\r\n", charger_get_battname (  ) );
    mbus_print ( txt );
    sprintf ( txt, "CHARGER: Current voltage %i mV\r\n", charger_get_un (  ) );
    mbus_print ( txt );

    // as long we should run, normally forever
    while ( charger_run )
    {
        // a baaaad baaad baaad locking (needed for advalues in other thread)
        while ( charger_locked ) ;

        // if a charger is connected, 
        if ( charger_connected (  ) )
        {
            // save previous state
            charger_prev_state = charger_state;
            // and check if we were on battery before
            if ( charger_prev_state & 0x10 )
            {
                sprintf ( txt, "CHARGER: Charger connected\r\n" );
                mbus_print ( txt );
                // get the chargers maximum voltage
                charger_power = CHARGE_OFF;
                charger_set_power (  );
                // wait to stabilize
                usleep ( 100000 );
                charger_update (  );
                charger_maxvoltage = charger_uc;
                sprintf ( txt, "CHARGER: Charger's maximum voltage: %i mV\r\n", charger_maxvoltage );
                mbus_print ( txt );
                // get the chargers maximum current
                charger_power = CHARGE_FAST;    // CHARGE_CHECK;
                charger_set_power (  );
                // wait to stabilize
                usleep ( 250000 );
                // and save it...
                charger_update (  );
                charger_maxcurrent = charger_ic;
                charger_discharge = 0;
                sprintf ( txt, "CHARGER: Charger's maximum current: %i mA\r\n", charger_maxcurrent );
                mbus_print ( txt );
            }

            // lets check what we should do now

            // save previous state
            charger_state = BATT_CHECK;
            saved = charger_power;
            // disable charger
            charger_power = CHARGE_OFF;
            charger_set_power (  );
            usleep ( 1000000 );
            // read battery state
            charger_update (  );
            charger_state = charger_get_battstate (  );
            // and restore the saved state
            charger_power = saved;
            charger_set_power (  );

            switch ( charger_state )
            {
                case BATT_OVERLOAD:
                    // ouch, the battery voltage is too high
                    // or it reached the maximum charge voltage
                    if ( charger_power != CHARGE_OFF )
                    {
                        sprintf ( txt, "CHARGER: Disabling charging, battery too high: %i mV\r\n", charger_un );
                        mbus_print ( txt );
                        // shut down the charger if it isnt already done
                        charger_power = CHARGE_OFF;
                        charger_set_power (  );
                        // let the battery cool down
                        // then charge again
                        charger_discharge = charger__cool_down__ub[charger_battery];
                    }
                    break;
                case BATT_OVERDISCHARGED:
                case BATT_SLOWCHARGE:
                    // we are in a critical zone, so charge slowly
                    // first check if we should let the batt discharge before
                    if ( !charger_discharge || charger_un < charger_discharge )
                    {
                        charger_discharge = 0;
                        if ( charger_power != CHARGE_SLOW )
                        {
                            sprintf ( txt, "CHARGER: Slow Charging\r\n" );
                            mbus_print ( txt );
                            charger_power = CHARGE_SLOW;
                            charger_set_power (  );
                        }
                    }
                    break;
                case BATT_DISCHARGE:
                    // nothing to do here except disabling and waitng
                    if ( charger_power != CHARGE_OFF )
                    {
                        sprintf ( txt, "CHARGER: Disabling charging, battery discharge until: %i mV\r\n", charger_discharge );
                        mbus_print ( txt );
                        // shut down the charger if it isnt already done
                        charger_power = CHARGE_OFF;
                        charger_set_power (  );
                    }
                    break;
                case BATT_CHARGE:
                    // beam me up, scotty.. full power!
                    // first check if we should let the batt discharge before
                    if ( !charger_discharge || charger_un < charger_discharge )
                    {
                        charger_discharge = 0;
                        if ( charger_power != CHARGE_FAST )
                        {
                            sprintf ( txt, "CHARGER: Charging\r\n" );
                            mbus_print ( txt );
                            charger_power = CHARGE_FAST;
                            charger_set_power (  );
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        else
        {
            // hmm no charger connected
            // switch off charging if it was on
            if ( !( charger_state & 0x10 ) )
            {
                sprintf ( txt, "CHARGER: Charger disconnected\r\n" );
                mbus_print ( txt );
                charger_power = CHARGE_OFF;
                charger_set_power (  );
                charger_maxcurrent = 0;
                charger_maxvoltage = 0;
                charger_discharge = 0;
            }
            if ( startup == CHARGE )
            {
                cycle = 40;
                while ( --cycle )
                {
                    if ( charger_connected (  ) )
                        break;
                    usleep ( 100000 );
                }
                if ( !cycle )
                    ccont_poweroff (  );
            }
            // and check our battery state (not very comfortable ;)
            if ( charger_ub < charger__empty_batt_ub[charger_battery] )
                charger_state = BATT_LOW;
            else
                charger_state = BATT_NORM;
        }

        // in idle mode, just update the measures cache
        for ( i = 0; ( i < charger_delays[charger_state] ) && ( !( charger_state & 0x10 && charger_connected (  ) ) ); i++ )
        {
            charger_update (  );
            usleep ( 500000 );
        }
    }

}

int
charger_chargemode ( void )
{
    int value = 0;
    unsigned char *text = malloc ( 32 );

    ani_play ( &ani_charge, 0, 4, 400, 0, 0 );
    while ( kpd_getkey (  ) || 1 )
    {
        value = ccont_get_ub (  );
        sprintf ( text, "%i.%i V", lib_div ( value, 1000 ), lib_mod ( value, 1000 ) );
        lcd_render_text ( 40, 2 * 8, charger_get_battname (  ), 1 );
        lcd_render_text ( 40, 3 * 8, text, 1 );
        lcd_to_screen (  );
        sleep ( 1 );
        lcd_render_text ( 40, 2 * 8, charger_get_battname (  ), 0 );
        lcd_render_text ( 40, 3 * 8, text, 0 );
        lcd_to_screen (  );
    }

}
