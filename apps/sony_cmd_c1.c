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


// SIMUNLOCK by S.S. v1.0
// posted on nokiafree.org
// MADos import: kraze1984

#include <core/lib.h>
#include <core/ui.h>
#include <apps/sony_cmd_c1.h>

#define KEY	    907
#define PRIME_NUM   9973
#define MAX_DIV_TIME 8


#define RANDOME        118956
#define KEY_OFFSET   89048231
#define MAX_NUM     100000000
#define UINT8 unsigned char
#define INT32 long
#define INT16 long
#define PASSWORD_OK 1
#define PASSWORD_NG 0

unsigned char sony_phoneimei[32] = "20338534";

UINT8 ALCheckSimLockPasswd( INT32 imeiKey, INT32 unlockKey );

void  setOddEvenDigits( INT32 d8digits, INT16 *pwEvenDigits, INT16 *pwOddDigits );

UINT8 checkEachPassWord( INT16 wEachPassWord, INT16 wEachMobileId );

INT32 getPassWord( INT32 dMobileId );

INT16 getEachPassWord( INT16 wEachMobileId );

INT32 builtLong( INT16 wShort1, INT16 wShort2 );

void  splitShort( INT32 dLong, INT16 *pwShort1, INT16 *pwShort2 );

INT16 getInverse( INT16 iInput );



/*--------------------------- Local statics ----------------------------------*/

/*--------------------------- Local functions --------------------------------*/


/*----------------------------------------------------------------------------*/
/*
** This function performs whether the input password is valid against a ID
*/
UINT8	ALCheckSimLockPasswd( INT32 imeiKey, INT32 unlockKey )
{
	UINT8 wResult;
	INT16 wEvenPassWord, wOddPassWord;
	INT16 wEvenMobileId, wOddMobileId;
	INT32  dx;

   imeiKey   %= MAX_NUM;
   unlockKey %= MAX_NUM;

	dx = (imeiKey + RANDOME) % MAX_NUM ;

	setOddEvenDigits( dx, &wEvenMobileId, &wOddMobileId );

	unlockKey -= KEY_OFFSET;

	if( unlockKey < 0 ){
		unlockKey += MAX_NUM;
	}

	splitShort( unlockKey, &wOddPassWord, &wEvenPassWord );

	wResult = checkEachPassWord( wEvenPassWord, wEvenMobileId );

	if( wResult == PASSWORD_NG ){
		return( PASSWORD_NG );
	}

	wResult = checkEachPassWord( wOddPassWord, wOddMobileId );

	return( wResult );
}

/*----------------------------------------------------------------------------*/
/*
** This function makes a 2N-digits integer split a pair of N-digits integers.
** One N-digits integer is composed of even digits of 2N-digits integer..
** Another N-digits interger is composed of odd digits 2N-digits interger.
** The digit order is same(keep the order)
**
** 2N-digits interger   : 76543210
** Odd N-digits intrger :     7531
** Even N-digits integer:     6420
*/
void setOddEvenDigits( INT32 d8digits, INT16 *pwEvenDigits, INT16 *pwOddDigits )
{
	INT16 wDigit;
	INT32  dRest, dDiv;

	dRest = d8digits;
	*pwEvenDigits = 0;
	*pwOddDigits  = 0;

	dDiv = MAX_NUM;

	while( dDiv > 1 ){
		dDiv /= 10;
		wDigit = dRest / dDiv;
		dRest = dRest % dDiv;

		*pwOddDigits *= 10;
		*pwOddDigits += wDigit;

		dDiv /= 10;
		wDigit = dRest / dDiv;
		dRest = dRest % dDiv;

		*pwEvenDigits *= 10;
		*pwEvenDigits += wDigit;
	}
}

/*----------------------------------------------------------------------------*/

UINT8 checkEachPassWord( INT16 wEachPassWord, INT16 wEachMobileId )
{
	INT16 dResult;

	if( wEachPassWord > PRIME_NUM ){
		return( PASSWORD_NG);
	}
	if( (wEachPassWord == PRIME_NUM) || (wEachPassWord == 0) ){
		if( (wEachPassWord + wEachMobileId) == PRIME_NUM ){
			return( PASSWORD_OK );
		}else{
			return( PASSWORD_NG );
		}
	}

	dResult = ( wEachPassWord * wEachMobileId ) % PRIME_NUM;

	if( dResult == KEY ){
		return( PASSWORD_OK );     
	}else{
		return( PASSWORD_NG );
	}
}

/*----------------------------------------------------------------------------*/
/*
** provide one password from one ID
*/
INT32 getPassWord( INT32 dMobileId )
{
	INT16 wEvenMobileId, wOddMobileId;
	INT16 wEvenPassWord, wOddPassWord;
	INT32 dx, dPassWord;

	dx = ( dMobileId + RANDOME ) % MAX_NUM ;

	setOddEvenDigits( dx, &wEvenMobileId, &wOddMobileId );

	wEvenPassWord = getEachPassWord( wEvenMobileId );

	wOddPassWord = getEachPassWord( wOddMobileId );

	dPassWord = builtLong( wEvenPassWord, wOddPassWord );

	dPassWord += KEY_OFFSET;

	dPassWord = dPassWord % MAX_NUM;

	return( dPassWord );
}

/*----------------------------------------------------------------------------*/

INT16 getEachPassWord( INT16 wEachMobileId )
{
	INT16 wInv, wEachPassWord;

	if( wEachMobileId == 0 ){
		return( PRIME_NUM );
	}

	if( wEachMobileId == PRIME_NUM ){
		return( 0 );
	}

	wInv = getInverse( wEachMobileId );

	wEachPassWord = ( KEY * wInv ) % PRIME_NUM ;

	return( (INT16) wEachPassWord );
}

/*----------------------------------------------------------------------------*/
/*
** This function makes a 2N-digits integer using two N-digits integeres.
** The digti order is reverse.
**
** N-digits intrger1 :     7531
** N-digits integer2 :     6420
** 2N-digits integer : 01234567
*/
INT32 builtLong( INT16 wShort1, INT16 wShort2 )
{
	INT16 wDigit;
	INT32 dCt;
	INT32 dLong;

	dLong = 0;

	dCt = 1;

	while( dCt < MAX_NUM ){

		wDigit = wShort1 % 10 ;
		wShort1 /= 10;

		dLong *= 10;
		dLong += wDigit;
		dCt *= 10;

		wDigit = wShort2 % 10 ;
		wShort2 /= 10;

		dLong *= 10;
		dLong += wDigit;
		dCt *= 10;
	}

	return( dLong );

}

/*----------------------------------------------------------------------------*/
/*
** This function makes two N-digits integers using a 2N-digits integer..
** The digti order is reverse.
**
** 2N-digits integer : 76543210
** N-digits intrger1 :     1357
** N-digits integer2 :     0246
*/
void splitShort( INT32 dLong, INT16 *pwShort1, INT16 *pwShort2 )
{
	INT16 wDigit;
	INT32 dCt;

	dCt = 1;

	*pwShort1 = 0;
	*pwShort2 = 0;

	while( dCt < MAX_NUM ){
		wDigit = dLong % 10;
		dLong /= 10;

		*pwShort1 *= 10;
		*pwShort1 += wDigit;

		dCt *= 10;

		wDigit = dLong % 10;
		dLong /= 10;
		
		*pwShort2 *= 10;
		*pwShort2 += wDigit;

		dCt *= 10;

	}
}

/*----------------------------------------------------------------------------*/
/*
** This function returns the reverse Y such as XY = 1 mod P where P is a prime n
umber.
** This is based on Euclid's algorithm.
*/
INT16 getInverse( INT16 iInput )
{
	/*
	** Return x such as that ax = 1 mod N 
	** where 0 < a < N 
	*/

	INT16 g_0, u_0, v_0 ;
	INT16 g_1, u_1, v_1 ;
	INT16 g_2, u_2, v_2 ;
	INT16 x, y;

	/*
	** Initialization 
	**
	** g(0) = u(0)*N + v(0)*a = n
	** g(1) = u(1)*N + v(1)*a = a
	**      :
	** g(n) = u(n)*N + v(n)*a 
	*/

	g_0 = PRIME_NUM ;
	u_0 = 1;
	v_0 = 0;

	g_1 = iInput ;
	u_1 = 0;
	v_1 = 1;

	/*
	** g(n) = g(n-2) mod g(n-1)
	**      = g(n-2) - y(n-1)*g(n-1)
	**      = {u(n-2) - y(n-1)*u(n-2)}*N + {v(n-2) - y(n-1)*v(n-1)}*a
	**
	** u(n) = u(n-2) - y(n-1)*u(n-1)
	** v(n) = v(n-2) - y(n-1)*v(n-1)
	**
	** if g(n) = 1,
	**
	**    u(n)*N + v(n)*a = 1 mod N
	**             v(n)*a = 1 mod N
	**             x = v(n)
	*/
	while ( g_1 != 1 ){
		y   = g_0 / g_1 ;
		g_2 = g_0 - y * g_1 ;
		u_2 = u_0 - y * u_1 ;
		v_2 = v_0 - y * v_1 ;

		g_0 = g_1;
		u_0 = u_1;
		v_0 = v_1;

		g_1 = g_2;
		u_1 = u_2;
		v_1 = v_2;

	}
	
	x = v_1;

	if( x < 0 ){
		return( x + PRIME_NUM );
	}else{
		return( x );
	}
}


MENU_CALLBACK ( sony_imei )
{
    MENU_SCROLL_INIT ( 4 );
//    static int pos = 0;
//    static int cnt = 2;
//    static int dir = 0;
//    char str[20];
//    char buf[64];

    switch ( cmd )
    {
        case MENU_SELECT:
            memset ( sony_phoneimei, 0x00, 32 );
            ui_gettext ( "8 last digits of IMEI, except check digit:", 8, sony_phoneimei, UI_TYPE_NUMBER );
            break;
        case MENU_REDRAW:
            if ( sony_phoneimei )
            {
                MENU_SCROLL ( sony_phoneimei );
            }
            break;
        case MENU_DRAW:
            MENU_SCROLL_RESET;
//      pos = 0;
//      cnt = 2;
            break;
        default:
            break;
    }
}


MENU_CALLBACK ( sony_calc )
{
	MENU_ONLY_SELECT;

    unsigned char tempstring[26];
    unsigned char unlock_code[256];
    unsigned char temppass[256];
    long imei;
    long pass;
    //imei=20338534;
imei = atol (sony_phoneimei); 
    pass = getPassWord(imei);

//*************************DEBUG***************************
//	sprintf (tempstring, "8 digits: ");
//	strcat (unlock_code, tempstring);
//        sprintf (tempstring, "%ld", imei);
//	strcat (unlock_code, tempstring);
//***********************END DEBUG*************************
	sprintf ( tempstring, "Unlock code: *#7465625*12*");
	sprintf ( temppass, "%ld", pass);
	strcat (unlock_code, tempstring);
	strcat (unlock_code, temppass);
	sprintf (tempstring, "#; ");
	strcat (unlock_code,tempstring);
        sprintf ( tempstring, "Lock code: *#7465625*11*");
	strcat ( unlock_code, tempstring);
	strcat (unlock_code,temppass);
	sprintf (tempstring, "#");
	strcat (unlock_code, tempstring);

	ui_draw_scrolltext (unlock_code);

}
