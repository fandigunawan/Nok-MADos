/*  
  
MADos, a free OS for N* handsets  
Copyright (C) 2003/2004 MADos Core Developer Team  
  
This library is free software; you can redistribute it and/or  
modify it under the terms of the GNU Lesser General Public  
License as published by the Free Software Foundation; either  
version 2.1 of the License, or (at your option) any later version.  
  
This library is distributed in the hope that it will be useful,  
but WITHOUT ANY WARRANTY; without even the implied warranty of  
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU  
Lesser General Public License for more details.  
  
You should have received a copy of the GNU Lesser General Public  
License along with this library; if not, write to the Free Software  
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA  
  
 contact http://64.246.26.121/forum/forumdisplay.php?f=99  

*/

#include <hw/phoneinfo.h>

#include <hw/snd_keypress.h>
#include <hw/ioports.h>
#include <hw/io.h>
#include <hw/kpd.h>
#include <hw/lcd.h>
#include <hw/int.h>
#include <core/lib.h>
#define LCD_CONTRAST  0x44

// nrs for pixel count appear instead of the topper lcd border (pc)
//#define NUMBER_LCD_FRAME

// used for win98 cygwin
#ifdef OS_WIN98
#define FIXEDSIZE_WIN98
#endif

#ifdef FIXEDSIZE_WIN98
#define MAX_COLS 79
#define MAX_ROWS 6
#else
#define MAX_COLS 86
#define MAX_ROWS 6
#endif
/*
//old font
extern const unsigned char lcd_font_big[128][8];
extern const unsigned char lcd_font_small[128][8];

Use lcd_fontsettings( FONT_SIZED ) to get original stule fonts use FONT_SYSTEM to get a standard font with a constant
height and width

  font.space the amount of pixels in char 0x020 ( space )

*/

extern const unsigned char lcd_font_large[128][22];
extern unsigned int lcd_font_size_large[128][2];
extern const unsigned char lcd_font_big[128][22];
extern unsigned int lcd_font_size_big[128][2];
extern const unsigned char lcd_font_small[128][22];
extern unsigned int lcd_font_size_small[128][2];
extern const unsigned char lcd_font_small_bold[128][22];
extern unsigned int lcd_font_size_small_bold[128][2];





extern unsigned char tid_lcd;

int max_contrast = LCD_CONTRAST;
unsigned char lcd_cursor = 1;
unsigned char font_flags;
static unsigned char lcd_buf[LCD_BUFLEN];

static unsigned char lcd_io_buf[LCD_BUFLEN];
static unsigned char ani_buf[LCD_BUFLEN];
static unsigned char ani_mask[LCD_BUFLEN];
char lcd_changed = 0;
char ani_playing = 0;
unsigned int currfont;
unsigned int font_settings;
font *lcd_font;
font lcd_fonts[4];

#ifndef ARM
int contrast;
#endif

unsigned char *
lcd_get_buf ( void )
{
    return lcd_buf;
}

unsigned int
lcd_get_bufsize ( void )
{
    return LCD_BUFLEN;
}

void
lcd_to_screen_hw ( void )
{
    memcpy ( lcd_io_buf, lcd_buf, LCD_BUFLEN );
    lcd_screen_to_io (  );
}

void volatile
lcd_to_screen ( void )
{
    if ( tid_lcd == 0xFF )
    {
        lcd_to_screen_hw (  );
        return;
    }

    memcpy ( lcd_io_buf, lcd_buf, LCD_BUFLEN );
#ifdef LOADER
    lcd_screen_to_io (  );
#endif
#ifndef PC
    lcd_changed = 1;
#else
    lcd_screen_to_io (  );
#endif
}

// draws all ram paintings to screen
void volatile
lcd_screen_to_io ( void )
{
    int i = 0;
    int x = 0;
    int y = 0;


    int_disable (  );
    lcd_changed = 0;
    if ( ani_playing )
        for ( i = 0; i < LCD_BUFLEN; i++ )
            lcd_io_buf[i] = ( lcd_io_buf[i] & ani_mask[i] ) | ( ani_buf[i] & ~ani_mask[i] );

#ifndef PC
    if ( mados_info[mados_phone].lcd_xsize > 84 && mados_phone != NOKIA6210 )
    {
        //6210 patch copied :p
        for ( x = 0; x < 6; x++ )
        {
            lcd_write_cmd ( 0x40 | ( x + 1 ) );
            lcd_write_cmd ( 0x80 | 0x6 );
            for ( y = 0; y < 84; y++ )
                lcd_write_data ( lcd_io_buf[y + 84 * x] );
        }
    }
    else if ( mados_phone == NOKIA6210 )
    {
        // draw a 48x84 screen in the middle of the 6210 screen
        for ( x = 0; x < 6; x++ )
        {
            lcd_write_cmd ( 0x40 | ( x + 1 ) );
            lcd_write_cmd ( 0x80 | 0x6 );
            for ( y = 0; y < 84; y++ )
                lcd_write_data ( lcd_io_buf[y + 84 * x] );
        }
    }
    else
    {
        lcd_write_cmd ( 0x80 );

        for ( i = 0; i < LCD_BUFLEN; i++ )
            lcd_write_data ( lcd_io_buf[i] );
    }

#else
    int pot[8];

    pot[0] = 1;
    pot[1] = 2;
    pot[2] = 4;
    pot[3] = 8;
    pot[4] = 16;
    pot[5] = 32;
    pot[6] = 64;
    pot[7] = 128;

//    system ( "clear" );
    printf ( "\x1b[1;1H\x1b[2J" );
#ifdef NUMBER_LCD_FRAME
    for ( x = 9; x < MAX_COLS + 9; x++ )
        printf ( "%i", x % 10 );
#else
    for ( x = 0; x < MAX_COLS; x++ )
        printf ( "-" );
#endif
    printf ( "\n" );
    for ( y = 0; y < MAX_ROWS; y++ )
        for ( i = 0; i < 8; i++ )
        {
            printf ( "I" );
            for ( x = 0; x < MAX_COLS - 2; x++ )
            {
                if ( lcd_io_buf[x + ( y * 84 )] & pot[i] )
                {
                    if ( contrast > 0x1A )
                        printf ( "#" );
                    else if ( contrast > 0x17 )
                        printf ( "X" );
                    else if ( contrast > 0x11 )
                        printf ( "x" );
                    else if ( contrast > 0x0C )
                        printf ( "." );
                    else
                        printf ( " " );
                }
                else
                    printf ( " " );
            }
            printf ( "I\n" );
        }
#ifndef FIXEDSIZE_WIN98
    for ( x = 0; x < MAX_COLS; x++ )
        printf ( "-" );
    printf ( "\n" );
#endif
#endif
    memcpy ( lcd_io_buf, lcd_buf, LCD_BUFLEN );

    int_enable (  );
    return;
}

void
lcd_fontsettings ( int num )
{
    font_settings = num;
}

// clears the screen in ram
void volatile
lcd_clr ( void )
{
    memset ( lcd_buf, 0x00, LCD_BUFLEN );
    return;
}

// writes a text like a human at a typewriter without keypress sound
void
lcd_type_text ( int x, int y, int speed, unsigned char *text, int sc )
{
    int pos;
    unsigned int xpos = 0;
    unsigned char c;

    kpd_mode ( KPD_UNBUFFERED );
    pos = 0;
    c = text[pos];
    while ( c )
    {
        xpos += lcd_render_char ( x + xpos, y, c, sc );
        lcd_to_screen (  );
        pos++;
        c = text[pos];
        if ( kpd_getkey (  ) == 0xFF )
            usleep ( 100000 * speed );
    }
    kpd_mode ( KPD_BUFFERED );
}

// writes a text like a human at a typewriter with keypress sound
void
lcd_type_text_2 ( int x, int y, int speed, unsigned char *text, int sc )
{
    int pos;
    unsigned int xpos = 0;
    unsigned char c;

    kpd_mode ( KPD_UNBUFFERED );
    pos = 0;
    c = text[pos];
    while ( c )
    {
        //need getkey because buzzer_snd_play plays snd_key (smaller than 0.5 sec.)
        if ( kpd_getkey (  ) == 0xFF )
            if ( c != 0x20 )
                buzzer_snd_play ( snd_key, sizeof ( snd_key ) );
        xpos += lcd_render_char ( x + xpos, y, c, sc );
        lcd_to_screen (  );
        pos++;
        c = text[pos];
        if ( kpd_getkey (  ) == 0xFF )
            usleep ( 50000 * speed );
    }
    kpd_mode ( KPD_BUFFERED );
}

void
lcd_set_cursor ( unsigned char t )
{
    if ( t )
        lcd_cursor = 1;
    else
        lcd_cursor = 0;
}

// fills the full screen with 1 byte in ram
void volatile
lcd_fill ( unsigned char c )
{
    int i = 0;

    for ( i = 0; i < LCD_BUFLEN; i++ )
        lcd_buf[i] = c;

    return;
}

// fills the full screen with 2 alternating bytes in ram
void volatile
lcd_fill_2 ( unsigned char c, unsigned char d )
{
    int i = 0;

    for ( i = 0; i < LCD_BUFLEN; i += 2 )
    {
        lcd_buf[i] = c;
        lcd_buf[i + 1] = d;
    }
    return;
}

unsigned int
mod ( int x, int y )
{
    return lib_mod ( x, y );
}
unsigned int
div ( int x, int y )
{
    return lib_div ( x, y );
}

// draws a font character to the ram
unsigned char volatile
lcd_render_char_x ( int x, int y, unsigned char c, int sc )
{

    int width;
    int buf_width;
    int height;

    switch ( font_settings )
    {
        case FONT_SYSTEM:
            width = lcd_font->w;
            buf_width = lcd_font->w;
            height = lcd_font->h;
        case FONT_SIZED:
            width = ( *lcd_font->size )[c][0];
            buf_width = ( *lcd_font->size )[c][0];
            height = ( *lcd_font->size )[c][1];
    }
    int bufpos = height;
    int i = 0;
    int offset = 0;

    if ( c == 32 )
        return lcd_font->space;




    if ( c == 0xFF )
    {
        lcd_draw_line ( x, y, x, y + lcd_font->h, lcd_cursor );
        return 1;
    }


// Untill we get this function to draw on y axies > 8
    if ( currfont == 3 )
    {
        bitmap_t bmp_font = { width, 13, ( *lcd_font->data )[c] };
        lcd_draw_bitmap ( x, y, &bmp_font );
        return width;
    }

/*

    if ( ( font_flags & FONT_DYNAMIC ) == FONT_DYNAMIC )
    {
        for ( i = width; ( i >= 0 ) && ( ( *lcd_font->data )[c][i] == 0 ); i--, width-- ) ;
        if ( !width )
            width = buf_width;
    }
*/
    if ( y >= 0 )
    {
        offset = mod ( y, height );
        y = div ( y, height );
        bufpos = y * 84 + x;
    }
    else if ( y >= height - 84 )
    {
        y += height;
        offset = mod ( y, height );
        y = div ( y, height );
        bufpos = y * 84 + x;
        bufpos -= 84;
    }
    else
        return 0;




    if ( c > 128 )
        c = 'x';

    for ( i = 0; i < width; i++ )
        if ( i + x < 84 )
        {
            if ( bufpos + i < LCD_BUFLEN && bufpos + i >= 0 )
            {
                if ( !sc )
                    lcd_buf[bufpos + i] &= ( ( *lcd_font->data )[c][i] << offset ) ^ 0xFF;
                else if ( sc == 1 )
                    lcd_buf[bufpos + i] |= ( *lcd_font->data )[c][i] << offset;
                else
                    lcd_buf[bufpos + i] ^= ( *lcd_font->data )[c][i] << offset;
            }
            if ( bufpos + i + 84 < LCD_BUFLEN && bufpos + i + 84 >= 0 )
            {
                if ( !sc )
                    lcd_buf[bufpos + i + 84] &= ( ( *lcd_font->data )[c][i] >> ( 8 - offset ) ) ^ 0xFF;
                else if ( sc == 1 )
                    lcd_buf[bufpos + i + 84] |= ( *lcd_font->data )[c][i] >> ( 8 - offset );
                else
                    lcd_buf[bufpos + i + 84] ^= ( *lcd_font->data )[c][i] >> ( 8 - offset );
            }
        }

    if ( ( font_flags & FONT_CONDENSED ) != FONT_CONDENSED )
        width++;

    switch ( font_settings )
    {
        case FONT_SYSTEM:
            return width;
        case FONT_SIZED:
            return width - 1;
    }

}




/*
// draws a font character to the ram old
unsigned char volatile
lcd_render_char_x ( int x, int y, unsigned char c, int sc )
{
    int bufpos = 0;
    int i = 0;
    int offset = 0;
    unsigned char width = lcd_font->w;







    if ( c == 0xFF )
    {
        lcd_draw_line ( x, y, x, y + 8, lcd_cursor );
        return 1;
    }

    if ( ( font_flags & FONT_DYNAMIC ) == FONT_DYNAMIC )
    {
        for ( i = lcd_font->w - 1; ( i >= 0 ) && ( ( *lcd_font->data )[c][i] == 0 ); i--, width-- ) ;
        if ( !width )
            width = lcd_font->w;
    }

    if ( y >= 0 )
    {
        offset = y % 8;
        y = y / 8;
        bufpos = y * 84 + x;
    }
    else if ( y >= -8 )
    {
        y += 8;
        offset = y % 8;
        y = y / 8;
        bufpos = y * 84 + x;
        bufpos -= 84;
    }
    else
        return 0;


    if ( c > 128 )
        c = 'x';

    for ( i = 0; i < width; i++ )
        if ( i + x < 84 )
        {
            if ( bufpos + i < LCD_BUFLEN && bufpos + i >= 0 )
            {
                if ( !sc )
                    lcd_buf[bufpos + i] &= ( ( *lcd_font->data )[c][i] << offset ) ^ 0xFF;
                else if ( sc == 1 )
                    lcd_buf[bufpos + i] |= ( *lcd_font->data )[c][i] << offset;
                else
                    lcd_buf[bufpos + i] ^= ( *lcd_font->data )[c][i] << offset;
            }
            if ( bufpos + i + 84 < LCD_BUFLEN && bufpos + i + 84 >= 0 )
            {
                if ( !sc )
                    lcd_buf[bufpos + i + 84] &= ( ( *lcd_font->data )[c][i] >> ( 8 - offset ) ) ^ 0xFF;
                else if ( sc == 1 )
                    lcd_buf[bufpos + i + 84] |= ( *lcd_font->data )[c][i] >> ( 8 - offset );
                else
                    lcd_buf[bufpos + i + 84] ^= ( *lcd_font->data )[c][i] >> ( 8 - offset );
            }
        }

    if ( ( font_flags & FONT_CONDENSED ) != FONT_CONDENSED )
        width++;

    return width;
}
*/


// draws a font character to the ram
unsigned char volatile
lcd_render_char ( int x, int y, unsigned char c, int sc )
{
    return lcd_render_char_x ( x, y, c, sc );
}

//return char width
unsigned char volatile
lcd_get_char_width ( unsigned char c )
{
    unsigned char width;
    int i = 0;
    if ( c == 32 )
        return lcd_font->space;

    switch ( font_settings )
    {
        case FONT_SYSTEM:
            width = lcd_font->w;
        case FONT_SIZED:
            width = ( *lcd_font->size )[c][0];
    }

    if ( c == 0xFF )
        return 1;
/*
    if ( ( font_flags & FONT_DYNAMIC ) == FONT_DYNAMIC )
    {
        for ( i = lcd_font->w - 1; ( i >= 0 ) && ( ( *lcd_font->data )[c][i] == 0 ); i--, width-- ) ;
        if ( !width )
            width = lcd_font->w;
    }
	*/

    switch ( font_settings )
    {
        case FONT_SYSTEM:
            if ( ( font_flags & FONT_CONDENSED ) != FONT_CONDENSED )
                width++;
        case FONT_SIZED:
            return ( width );
    }


    return ( width );
}

//return text string width
unsigned int volatile
lcd_get_text_width ( unsigned char *text )
{
    unsigned int i = 0, sum = 0;

    while ( text[i] )
        sum += lcd_get_char_width ( text[i++] );

    return sum;
}

// draws a line of font characters to the ram
void
lcd_render_text ( int x, int y, unsigned char *text, int sc )
{
    int pos;
    int xpos;
    unsigned char c;

    pos = 0;
    xpos = 0;
    c = text[pos];

    while ( c )
    {
        xpos += lcd_render_char_x ( x + xpos, y, c, sc );
        pos++;
        c = text[pos];
    }
}

//draws multiple text lines
void
lcd_render_text_ml ( int x, int y, unsigned char *text, int sc, int align )
{
    int i, done = 0, first = 0, pos = 0, len, line = 0, xoff;
    char *buf;

    if ( ( align & AL_BOTTOM ) == AL_BOTTOM )
    {
        line--;
        while ( text[pos] )
            if ( text[pos++] == '\n' )
                line--;
        pos = 0;
    }

    while ( !done )
    {
        while ( text[pos] != '\n' && text[pos] )
            pos++;
        if ( !text[pos] )
            done = 1;
        len = pos - first;
        buf = ( char * ) malloc ( len + 1 );
        memcpy ( buf, &text[first], len );
        buf[len] = 0x00;

        xoff = 0;
        for ( i = 0; i < len; i++ )
            xoff += lcd_get_char_width ( buf[i] );
        if ( ( align & AL_CENTER ) == AL_CENTER )
            xoff = xoff / 2;
        else if ( ( align & AL_RIGHT ) != AL_RIGHT )
            xoff = 0;

        lcd_render_text ( x - xoff, y + 8 * line, buf, sc );
        free ( buf );
        line++;
        pos++;
        first = pos;
    }
}

// waits until serial controller is ready
void inline
lcd_wait_ready ( void )
{
    _io_wait ( GENSIO_STATUS, GENSIO_STATUS_RDY );
}

// send data to the lcd
void volatile
lcd_write_data ( unsigned long byte )
{
    _io_set ( GENSIO_CFG, GENSIO_LCD_ENABLE | 0x1 );
    lcd_wait_ready (  );
    _io_set ( GENSIO_LCD_DATA, byte );
}

// send a command to the lcd 
void volatile
lcd_write_cmd ( unsigned long byte )
{
    _io_set ( GENSIO_CFG, GENSIO_LCD_ENABLE | 0x1 );
    lcd_wait_ready (  );
    _io_set ( GENSIO_LCD_CMD, byte );
}

// initializes the GENIO
void volatile
lcd_genio_init ( void )
{
    _io_wait ( GENSIO_STATUS, 0x02 );
    _io_set ( GENSIO_CFG, GENSIO_LCD_ENABLE | 0x5 );
//    _io_set_bit ( IO_CTSI_CTRL, CTSI_CTL_GC | CTSI_CTL_UU );
}

// resets the lcd
void volatile
lcd_reset ( void )
{
    int x, y;

    switch ( mados_info[mados_phone].lcd )
    {
        case 0:
            usleep ( 10000 );
            _io_clr_bit ( IO_UIF_CTRL2, UIF_CTRL2_RST );
            usleep ( 10000 );
            _io_set_bit ( IO_UIF_CTRL2, UIF_CTRL2_RST );
            usleep ( 10000 );
            break;
        case 1:
            _io_set_bit ( IO_PUP_DIR, PUP_GENIO_DISP );
            _io_set_bit ( IO_PUP_GENIO, PUP_GENIO_DISP );
            _io_clr_bit ( IO_PUP_GENIO, PUP_GENIO_DISP );
            usleep ( 10000 );
            _io_set_bit ( IO_PUP_GENIO, PUP_GENIO_DISP );
            lcd_write_cmd ( 0x20 );
            lcd_write_cmd ( 0x11 ); // extra command in 6210

            // clean display
            // if this works for other phones it can be moved down
            for ( x = 0; x < mados_info[mados_phone].lcd_xsize / 8; x++ )
            {
                lcd_write_cmd ( 0x40 | x );
                lcd_write_cmd ( 0x80 );
                for ( y = 0; y < mados_info[mados_phone].lcd_ysize; y++ )
                    lcd_write_data ( 0x00 );
            }
            break;
        case 2:
            _io_set_bit ( IO_PUP_DIR, PUP_GENIO_DISP );
            _io_set_bit ( IO_PUP_GENIO, PUP_GENIO_DISP );
            _io_clr_bit ( IO_PUP_GENIO, PUP_GENIO_DISP );
            usleep ( 10000 );
            _io_set_bit ( IO_PUP_GENIO, PUP_GENIO_DISP );
            lcd_write_cmd ( 0x24 );
            lcd_write_cmd ( 0x40 );
            lcd_write_cmd ( 0x80 );
            for ( x = 0; x < mados_info[mados_phone].lcd_xsize / 8; x++ )
            {
                for ( y = 0; y < mados_info[mados_phone].lcd_ysize; y++ )
                    lcd_write_data ( 0x00 );
            }
            lcd_write_cmd ( 0x20 );
            break;
    }
}

void
lcd_set_max_contrast ( unsigned char c )
{
    max_contrast = c;
    lcd_set_contrast ( c );
}


void
lcd_test_bias ( int dir )
{
    static int tc = 0x14;

    if ( dir )
        tc++;
    else
        tc--;

    if ( tc < 0x10 )
        tc = 0x10;
    if ( tc > 0x17 )
        tc = 0x17;

    lcd_write_cmd ( 0x21 );
    lcd_write_cmd ( tc );
    lcd_write_cmd ( 0x20 );

}

void
lcd_test_tc ( int dir )
{
    static int tc = 5;

    if ( dir )
        tc++;
    else
        tc--;

    if ( tc < 4 )
        tc = 4;
    if ( tc > 7 )
        tc = 7;

    lcd_write_cmd ( 0x21 );
    lcd_write_cmd ( tc );
    lcd_write_cmd ( 0x20 );

}

// sets the contrast of the lcd
void
lcd_set_contrast ( unsigned char c )
{
#ifdef ARM
    int_disable (  );
    lcd_write_cmd ( 0x21 );
    switch ( mados_info[mados_phone].lcd )
    {
        case 0:
        case 2:
            lcd_write_cmd ( 0x80 | c );
            lcd_write_cmd ( 0x05 ); // wumpus' patch
            lcd_write_cmd ( 0x14 ); // nokia's values
            break;
        case 1:
            lcd_write_cmd ( 0x80 | c );
            lcd_write_cmd ( 0x07 );
            lcd_write_cmd ( 0x14 );
            lcd_write_cmd ( 0x0A );
            break;
    }
    lcd_write_cmd ( 0x20 );
    int_enable (  );
#else
    contrast = c;
    lcd_to_screen (  );
#endif
}

unsigned char
lcd_get_contrast ( void )
{
    return max_contrast;
}

void
lcd_set_mode ( int mode )
{
#ifdef ARM
    int_disable (  );
    lcd_write_cmd ( 0x08 | ( mode & 7 ) );
    int_enable (  );
#endif
}

// fades in the lcd
void
lcd_fade_in ( int delay )
{
    int i = 0;

    if ( !delay )
    {
        lcd_set_contrast ( max_contrast );
        return;
    }
    for ( i = 0x07; i < max_contrast; i++ )
    {
        usleep ( 50000 * delay );
        lcd_set_contrast ( i );
    }
}

// fades out the lcd
void
lcd_fade_out ( int delay )
{
    int i = 0;
    if ( !delay )
    {
        lcd_set_contrast ( 0 );
        return;
    }

    for ( i = max_contrast; i > 0x07; i-- )
    {
        usleep ( 50000 * delay );
        lcd_set_contrast ( i );
    }
}

void
lcd_set_font ( int num )
{
    font_flags = num & 0xFFFFFFF0;
    num = num & 0x0000000F;
    lcd_font = &lcd_fonts[num];
    currfont = num;
}

// initializes the lcd
void volatile
lcd_init ( void )
{
    unsigned int i = 0;

    lcd_fonts[0].data = &lcd_font_small;
    lcd_fonts[0].size = &lcd_font_size_small;
    lcd_fonts[0].space = 3;
    lcd_fonts[0].w = 5;
    lcd_fonts[0].h = 8;
    lcd_fonts[0].name = "Small";

    lcd_fonts[1].data = &lcd_font_big;
    lcd_fonts[1].size = &lcd_font_size_big;
    lcd_fonts[1].space = 3;
    lcd_fonts[1].w = 8;
    lcd_fonts[1].h = 8;
    lcd_fonts[1].name = "Big";

    lcd_fonts[2].data = &lcd_font_small_bold;
    lcd_fonts[2].size = &lcd_font_size_small_bold;
    lcd_fonts[2].space = 3;
    lcd_fonts[2].w = 8;
    lcd_fonts[2].h = 8;
    lcd_fonts[2].name = "Small bold";

    lcd_fonts[3].data = &lcd_font_large;
    lcd_fonts[3].size = &lcd_font_size_large;
    lcd_fonts[3].space = 4;
    lcd_fonts[3].w = 8;
    lcd_fonts[3].h = 8;
    lcd_fonts[3].name = "Large";

/*
extern const unsigned char lcd_font_large[128][22];
extern unsigned int lcd_font_size_large[128][2];
extern const unsigned char lcd_font_big[128][22];
extern unsigned int lcd_font_size_big[128][2];
extern const unsigned char lcd_font_small[128][22];
extern unsigned int lcd_font_size_small[128][2];
extern const unsigned char lcd_font_small_bold[128][22];
extern unsigned int lcd_font_size_small_bold[128][2];

*/


    lcd_fontsettings ( FONT_SYSTEM );
    lcd_set_font ( 0 );
    lcd_cursor = 1;

    if ( !mados_info[mados_phone].kpd_led )
        _io_set_bit ( IO_PUP_GENIO, 0x08 );

    lcd_genio_init (  );
    lcd_reset (  );
    max_contrast = mados_info[mados_phone].lcd_contrast;
    lcd_set_contrast ( max_contrast );
    lcd_set_mode ( LCD_MODE_NORMAL );   /* display configuration: normal mode */
    lcd_fill_2 ( 0x5A, 0xA5 );
    memset ( ani_mask, 0xFF, LCD_BUFLEN );

}


/*********************************************************\
*                                                         *
*       converts a 8bpp bitmap and renders to LCD         *
*                                                         *
* sc:                                                     *
*     0: if pixel set, this point gets cleared            *
*     1: if pixel set, this point gets set                *
*     2: if pixel set, this point gets XORed              *
*     3: just render this bmp to screen                   *
*                                                         *
\*********************************************************/
void
lcd_render_bitmap ( int px, int py, int sx, int sy, unsigned char *b, int sc )
{
    int x = 0;
    int y = 0;

    for ( y = 0; y < sy; y++ )
        for ( x = 0; x < sx; x++ )
            switch ( sc )
            {
                case 0:
                    if ( b[x + y * sx] > 60 )
                        lcd_set_pixel ( px + x, py + y, 0 );
                    break;
                case 1:
                    if ( b[x + y * sx] > 60 )
                        lcd_set_pixel ( px + x, py + y, 1 );
                    break;
                case 2:
                    if ( b[x + y * sx] > 60 )
                        lcd_set_pixel ( px + x, py + y, 2 );
                    break;
                case 3:
                    lcd_set_pixel ( px + x, py + y, b[x + y * sx] > 60 ? 1 : 0 );
                    break;
                default:
                    break;
            }
}


//draws a bitmap_t at position (xpos,ypos) to screen
//if xpos or ypos == -1 the bmp is centered in this direction
void
lcd_draw_bitmap ( int xpos, int ypos, bitmap_t * bitmap )
{
    lcd_draw_bitmap_x ( xpos, ypos, bitmap, T_LCD_BUF );
}

void
lcd_draw_bitmap_x ( int xpos, int ypos, bitmap_t * bitmap, char target )
{
    int i, j, yrow, yoff, line = 0;
    int towrite = bitmap->y;
    int width = bitmap->x;
    char mask = 0;
    unsigned char *buf;
    unsigned char *target_buf;

    if ( xpos == -1 )
        xpos = ( 84 - width ) >> 1;
    if ( ypos == -1 )
        ypos = ( 48 - towrite ) >> 1;

    if ( ypos + towrite > 48 )
        towrite = 48 - ypos;
    if ( xpos + width > 84 )
        width = 84 - xpos;

    switch ( target )
    {
        case T_ANI_BUF:
            target_buf = ani_buf;
            memset ( ani_mask, 0xFF, LCD_BUFLEN );
            mask = 1;
            break;
        case T_LCD_BUF:
        default:
            target_buf = lcd_buf;
            break;
    }

    if ( towrite < 8 )          //simple method
    {
        for ( j = 0; j < towrite; j++ )
            for ( i = 0; i < width; i++ )
                lcd_set_pixel ( i + xpos, j + ypos, bitmap->data[( j >> 3 ) * bitmap->x + i] & ( 1 << ( j % 8 ) ) ? 1 : 0 );
    }
    else                        //speed method
    {
        yrow = ypos / 8;
        yoff = ypos % 8;

        buf = ( unsigned char * ) malloc ( width );
        if ( yoff )
        {
            memcpy ( buf, &target_buf[84 * yrow + xpos], width );
            for ( i = 0; i < width; i++ )
                buf[i] = ( buf[i] & ( 0xFF >> ( 8 - yoff ) ) ) | ( bitmap->data[i] << yoff );
            memcpy ( &target_buf[84 * yrow + xpos], buf, width );
            if ( mask )
                memset ( &ani_mask[84 * yrow + xpos], 0xFF >> ( 8 - yoff ), width );
            towrite -= 8 - yoff;
            line++;
            while ( towrite >= 8 )
            {
                for ( i = 0; i < width; i++ )
                    buf[i] = ( bitmap->data[bitmap->x * ( line - 1 ) + i] >> ( 8 - yoff ) ) | ( bitmap->data[bitmap->x * line + i] << yoff );
                memcpy ( &target_buf[84 * ( yrow + line ) + xpos], buf, width );
                if ( mask )
                    memset ( &ani_mask[84 * ( yrow + line ) + xpos], 0x00, width );
                towrite -= 8;
                line++;
            }
            if ( towrite )
            {
                memcpy ( buf, &target_buf[84 * ( yrow + line ) + xpos], width );
                for ( i = 0; i < width; i++ )
                    buf[i] = ( buf[i] & ( 0xFF & ( 0xFF << towrite ) ) ) | ( bitmap->data[bitmap->x * ( line - 1 ) + i] >> ( 8 - yoff ) );
                if ( towrite > yoff )
                    for ( i = 0; i < width; i++ )
                        buf[i] = buf[i] | ( bitmap->data[bitmap->x * line + i] << yoff );
                memcpy ( &target_buf[84 * ( yrow + line ) + xpos], buf, width );
                if ( mask )
                    memset ( &ani_mask[84 * ( yrow + line ) + xpos], ( 0xFF >> towrite ) << towrite, width );
            }
        }
        else                    // yoff == 0
        {
            while ( towrite >= 8 )
            {
                memcpy ( &target_buf[84 * ( yrow + line ) + xpos], &bitmap->data[bitmap->x * line], width );
                if ( mask )
                    memset ( &ani_mask[84 * ( yrow + line ) + xpos], 0x00, width );
                towrite -= 8;
                line++;
            }
            if ( towrite )
            {
                memcpy ( buf, &target_buf[84 * ( yrow + line ) + xpos], width );
                for ( i = 0; i < width; i++ )
                    buf[i] = ( buf[i] & ( 0xFF & ( 0xFF << towrite ) ) ) | bitmap->data[bitmap->x * line + i];
                memcpy ( &target_buf[84 * ( yrow + line ) + xpos], buf, width );
                if ( mask )
                    memset ( &ani_mask[84 * ( yrow + line ) + xpos], ( 0xFF >> towrite ) << towrite, width );
            }
        }
        free ( buf );
    }
}


// sets a pixel in lcd ram
void
lcd_set_pixel ( int x, int y, int sc )
{
    if ( x >= 0 && x < 84 && y >= 0 && y < 48 )
    {
        if ( !sc )
            lcd_buf[x + ( ( y / 8 ) * 84 )] &= 0xFF ^ ( 1 << y % 8 );
        else if ( sc == 1 )
            lcd_buf[x + ( ( y / 8 ) * 84 )] |= 1 << y % 8;
        else
            lcd_buf[x + ( ( y / 8 ) * 84 )] ^= 1 << y % 8;
    }
}

// return pixelstate ( 1 on; 0 off )
unsigned char
lcd_get_pixel ( int x, int y )
{
    if ( x >= 0 && x < 84 && y >= 0 && y < 48 && lcd_buf[x + ( ( y / 8 ) * 84 )] & ( 1 << y % 8 ) )
        return 1;
//    {
//            if ( lcd_buf[x + ( ( y / 8 ) * 84 )] & ( 1 << y % 8 ) /*== ( 1 << y % 8 )*/ ) return 1;
//            else return 0;
//    }
    return 0;
}

// draws a rectangle in lcd ram
void
lcd_draw_rect ( int x1, int y1, int x2, int y2, int sc )
{
    int x;
    int y;

    for ( x = x1; x <= x2; x++ )
        for ( y = y1; y <= y2; y++ )
            lcd_set_pixel ( x, y, sc );

}

// draws a line in lcd ram
void
lcd_draw_line ( int x1, int y1, int x2, int y2, int sc )
{
    int i;
    int ystep, xstep;
    int error;
    int errorprev;
    int y = y1, x = x1;
    int ddy, ddx;
    int dx = x2 - x1;
    int dy = y2 - y1;
    lcd_set_pixel ( x1, y1, sc );

    if ( dy < 0 )
    {
        ystep = -1;
        dy = -dy;
    }
    else
        ystep = 1;
    if ( dx < 0 )
    {
        xstep = -1;
        dx = -dx;
    }
    else
        xstep = 1;
    ddy = 2 * dy;
    ddx = 2 * dx;
    if ( ddx >= ddy )
    {
        errorprev = error = dx;
        for ( i = 0; i < dx; i++ )
        {
            x += xstep;
            error += ddy;
            if ( error > ddx )
            {
                y += ystep;
                error -= ddx;
                if ( error + errorprev < ddx )
                    lcd_set_pixel ( x, y - ystep, sc );
                else if ( error + errorprev > ddx )
                    lcd_set_pixel ( x - xstep, y, sc );
                /*
                 * else{ // diagonal lines are more fat with this part
                 * lcd_set_pixel (x, y-ystep, sc); 
                 * lcd_set_pixel (x-xstep, y, sc); 
                 * }
                 */
            }
            lcd_set_pixel ( x, y, sc );
            errorprev = error;
        }
    }
    else
    {
        errorprev = error = dy;
        for ( i = 0; i < dy; i++ )
        {
            y += ystep;
            error += ddx;
            if ( error > ddy )
            {
                x += xstep;
                error -= ddy;
                if ( error + errorprev < ddy )
                    lcd_set_pixel ( x - xstep, y, sc );
                else if ( error + errorprev > ddy )
                    lcd_set_pixel ( x, y - ystep, sc );
                else
                {
                    lcd_set_pixel ( x - xstep, y, sc );
                    lcd_set_pixel ( x, y - ystep, sc );
                }
            }
            lcd_set_pixel ( x, y, sc );
            errorprev = error;
        }
    }
}

/* old routine
void
lcd_draw_line ( int x1, int y1, int x2, int y2, int sc )
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int y = y1;
    int eps = 0;
    int x = 0;

    for ( x = x1; x <= x2; x++ )
    {
        lcd_set_pixel ( x, y, sc );
        eps += dy;
        if ( ( eps << 1 ) >= dx )
        {
            y++;
            eps -= dx;
        }
    }
    if ( dx == 0 )
    {
        x--;
        for ( y = y1; y <= y2; y++ )
            lcd_set_pixel ( x, y, sc );
    }
}
*/
