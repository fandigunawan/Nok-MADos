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


//
// vitel
// TSM 3/4/5 unlock code algo
//     >>>>>NOT 5m<<<<<
//
// indear
//
// MADos import: kraze1984
// Finished 24.10.2004

#include <core/lib.h>
#include <core/ui.h>
#include <apps/vitel.h>

#define PREPAGO 1	//prepaid
#define CONTRATO 2	//contract

unsigned char vitel_phoneimei[32] = "350005203385342";
int vitel_cardtype = 0;

unsigned char tabla_contrato[] = { 0x0c,0x2d,0x22,0x43,0x17,0x02,0x13,0x0a,0x0f,0x63,0x4c,0x2d,0x5b,
								   0x03,0x37,0x3b };
unsigned int tabla_contrato2[] = { 0x1E2D3E4F, 0xF5E6F7C8, 0x9E0D1E2F, 0x3E4D5A6E };

unsigned char tabla_prepago[] = { 0x05,0x17,0x43,0x4c,0x0c,0x16,0x4e,0x13,0x59,0x32,0x2b,0x38,0x56,
								  0x0b,0x0f,0x63 };

unsigned int tabla_prepago2[] = { 0x7A8E9E0D, 0xB1E2D3A4, 0x5A6E7E8D, 0x9E0F2E3D };

unsigned int calculo1 (unsigned int param1, unsigned int param2)
{
	int temp=0;

	do {
		if ((param1&1) == 1) {
			temp+=param2;
			temp&=0xFFFF;
		}
		param1&=0xFF;
		param1=param1>>1;
		param2+=param2;
	} while (param1!=0);

	return temp;
}


unsigned int calculo2 (unsigned int param1, unsigned int param2)
{
	unsigned int temp1, temp2;

	temp1=param1;
	param1=0;
	if (param2==0) {
		param1=0;
	}
	else {
		do {
			temp2=param2;
			temp2&=0x80000000;
			if (temp2!=0x80000000) {
				param2+=param2;
				param1++;
			}
		} while (temp2!=0x80000000);
		param1++;
		temp2=param1;

		if (temp2>0) {
			do {
				if (param2<=temp1)
					temp1-=param2;
				param2=param2>>1;
				temp2--;
			} while(temp2 != 0);

		}
		param1=temp1;
	}
	return param1;
}


// tipo= PREPAGO o CONTRATO
// IMEI (>=15 digitos)    [(xxxxxxxxxxxxxxyyz) -> (xxxxxxxxxxxxxxz)]

void codigo_liberacion(int tipo, char *imei, char *codigo_liberacion)
{
	unsigned int temp1, temp2, temp3;
	unsigned char temp4, temp5;
	unsigned int aux1,aux2,aux3,aux4,aux5,aux6,aux7;
	unsigned int destino_1[8];
	unsigned int *p_destino1;
	unsigned char *p_codigoliberacion, *p_IMEI;
	unsigned char *tabla1;
	unsigned int *tabla2;
	char IMEI[20];

	strcpy(IMEI, imei);
	IMEI[14]='0';
	IMEI[15]='0';
	IMEI[16]=0;
	IMEI[17]=0;
	IMEI[18]=0;
	IMEI[19]=0;

	memset(destino_1, 0, sizeof(destino_1));
	memset(codigo_liberacion, 0, 9);

	if (tipo == CONTRATO)
	{
		tabla1=tabla_contrato;
		tabla2=tabla_contrato2;
	}
	else
	{
		tabla1=tabla_prepago;
		tabla2=tabla_prepago2;
	}

	temp2=0;
	aux2=0x0f;
	temp5=0;
	temp4=8;
	aux6=0;
	p_destino1=destino_1;

	do {
		aux5=temp5;
		aux1=0x10;
		aux1-=aux5;
		aux7=IMEI[aux1];
		aux7-=0x30;
		aux7&=0xFFFF;
		aux1=aux2 & 0xFF;
		aux1=tabla1[aux1];
		aux4=aux7;

		aux1=calculo1(aux1, aux4);

		if ((aux1&0xFFFF) >= 0x8000)
			aux1|=0xFFFF0000;
		else
			aux1&=0x0000FFFF;
		aux1+=0x39;
		temp1=aux1;
		aux1=IMEI[aux5];
		aux4=IMEI[aux2];
		aux1+=aux4;
		aux4=9;
		aux1=calculo2(aux1, aux4);
		aux4=temp1;
		aux4-=aux1;
		*p_destino1=aux4;
		aux2--;
		temp5++;
		p_destino1+=1;
		temp4--;
	} while (temp4!=0);

	aux6=0;
	temp4=0x10;
	p_IMEI=IMEI;

	do {
		aux4=0;
		aux4=*p_IMEI;
		aux6+=aux4;
		if (tipo == CONTRATO)
			aux6-=0x30;
		p_IMEI++;
		temp4--;
	} while(temp4 != 0);

	temp4=7;
	p_destino1=&destino_1[7];

	do {
		if (tipo == CONTRATO)
			temp2+=0x9E3779B9;
		else
			temp2+=0x6F55A634;
		aux4=temp2;
		aux4=aux4>>2;
		aux4&=3;
		temp3=aux4;
		aux2=0;

		do {
			aux4=temp4;
			aux3=aux2;
			aux4+=aux3;
			aux4=tabla1[aux4];
			aux3=aux4;
			aux3=aux3<<5;
			aux4=aux4<<4;
			aux3^=aux4;
			aux4=aux3;
			aux3=*p_destino1;
			aux3+=aux6;
			aux4+=aux3;
			aux3=aux2;
			aux3^=temp3;
			aux4+=tabla2[aux3];
			aux4+=temp2;
			*p_destino1=aux4;
			aux2++;
		} while (aux2!=4);

		temp4--;
		p_destino1--;
	} while (temp4!=0xff);

	temp4=0;
	p_codigoliberacion=codigo_liberacion;

	do {
		aux1=temp4;
		aux1+=aux6;
		aux4=6;
		aux1=calculo2(aux1, aux4);
		aux6=destino_1[aux1];
		aux4=0x0A;
		aux1=aux6;
		aux1=calculo2(aux1, aux4);
		aux4=0x39;
		aux4-=aux1;
		*p_codigoliberacion=(char)aux4;
		temp4++;
		p_codigoliberacion++;
	} while (temp4 != 8);
}


MENU_CALLBACK ( vitel_imei )
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
            memset ( vitel_phoneimei, 0x00, 32 );
            ui_gettext ( "enter IMEI", 15, vitel_phoneimei, UI_TYPE_NUMBER );
            break;
        case MENU_REDRAW:
            if ( vitel_phoneimei )
            {
                MENU_SCROLL ( vitel_phoneimei );
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

MENU_CALLBACK ( vitel_calc )
{
	MENU_ONLY_SELECT;
	unsigned char allstring[256];
	unsigned char tempstring[26];
	char codigo1[9];
	char codigo2[9];

	codigo_liberacion(CONTRATO, vitel_phoneimei, codigo1);
	codigo_liberacion(PREPAGO, vitel_phoneimei, codigo2);

        sprintf ( tempstring, "Contract code: ");
	strcat (allstring, tempstring);
	strcat (allstring, codigo1);
	sprintf (tempstring, "; Prepaid code: ");
	strcat (allstring, tempstring);
	strcat (allstring, codigo2);

	ui_draw_scrolltext (allstring);

}
