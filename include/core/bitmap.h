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

#include <hw/lcd.h>

bitmap_t *bitmap_get ( ani_t * ani, int i );
int ani_play ( ani_t * ani, char x, char y, short int delay, short int loop, char wait );
void ani_stop ( void );

extern char lcd_changed;
extern char ani_playing;


extern bitmap_t bmp_tictactoe;
extern bitmap_t bmp_x;
extern bitmap_t bmp_o;
extern bitmap_t bmp_high;
extern bitmap_t bmp_turn;
extern bitmap_t bmp_turnclear;
extern bitmap_t bmp_owins;
extern bitmap_t bmp_xwins;
extern bitmap_t bmp_tictactoe2;
extern bitmap_t bmp_aguilera1;
extern bitmap_t bmp_aguilera2;
extern bitmap_t bmp_aguilera3;
extern bitmap_t bmp_binladen;
extern bitmap_t bmp_error;
extern bitmap_t bmp_jolie;
extern bitmap_t bmp_construction;
extern bitmap_t bmp_nokia1;
extern bitmap_t bmp_nokia2;
extern bitmap_t bmp_nokia3;
extern bitmap_t bmp_nokia4;
extern bitmap_t bmp_nokia5;
extern bitmap_t bmp_nokia6;
extern bitmap_t bmp_nokia7;
extern bitmap_t bmp_nokia8;
extern bitmap_t bmp_nokia9;
extern bitmap_t bmp_nokia10;
extern bitmap_t bmp_nokia11;
extern bitmap_t bmp_nokia12;
extern bitmap_t bmp_nokia13;
extern bitmap_t bmp_nokia14;
extern bitmap_t bmp_nokia15;
extern bitmap_t bmp_nokia16;
extern bitmap_t bmp_nokia17;
extern bitmap_t bmp_aikon1;
extern bitmap_t bmp_aikon2;
extern bitmap_t bmp_aikon3;
extern bitmap_t bmp_aikon4;
extern bitmap_t bmp_aikon5;
extern bitmap_t bmp_aikon6;
extern bitmap_t bmp_aikon7;
extern bitmap_t bmp_calvin1;
extern bitmap_t bmp_calvin2;
extern bitmap_t bmp_calvin3;
extern bitmap_t bmp_calvin4;
extern bitmap_t bmp_calvin5;
extern bitmap_t bmp_calvin6;
extern bitmap_t bmp_calvin7;
extern bitmap_t bmp_homer;
extern bitmap_t bmp_bart;
extern bitmap_t bmp_car;
//MADMEDIA BITMAPS
extern bitmap_t bmp_mconf;
extern bitmap_t bmp_mconfhot;
extern bitmap_t bmp_mconficon;
extern bitmap_t bmp_mheader;
extern bitmap_t bmp_mmovies;
extern bitmap_t bmp_mmovieshot;
extern bitmap_t bmp_mmoviesicon;
extern bitmap_t bmp_mpics;
extern bitmap_t bmp_mpicshot;
extern bitmap_t bmp_mpicsicon;
extern bitmap_t bmp_mmusic;
extern bitmap_t bmp_mmusichot;
extern bitmap_t bmp_mmusicicon;

///////////////////////////////////////////////////////////////////////////////
//  the way of BITMAP declaration
//  
//  1. declare bitmap in bitmap.h
//  2. define raw bitmap data as  const unsigned char array
//  3. define bitmap handle as    const bitmap_t
//
//  for ANIMATIONS
//  1. declare animation in bitmap.h
//  2. define animation handle as const ani_t ( last entry must be NULL )
///////////////////////////////////////////////////////////////////////////////


//declaration of BITMAPS
extern bitmap_t bmp_welcome;
extern bitmap_t bmp_01;
extern bitmap_t bmp_02;
extern bitmap_t bmp_03;
extern bitmap_t bmp_Game;
extern bitmap_t bmp_Tests;
extern bitmap_t bmp_Apps;
extern bitmap_t bmp_Power;
extern bitmap_t bmp_Creditz;
extern bitmap_t bmp_die1;

//declaration of ANIMATIONS
extern ani_t ani_01;
extern ani_t ani_02;
extern ani_t ani_02_r;
extern ani_t ani_03;
extern ani_t ani_04;
extern ani_t ani_charge;
