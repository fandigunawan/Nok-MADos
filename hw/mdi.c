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


#include <hw/io.h>
#include <hw/dsp.h>
#include <hw/mdi.h>
#include <core/lib.h>



void
mdi_send_interrupt (  )
{
    lcd_clr (  );
    lcd_render_text ( 0, 0, "MDISND", 1 );
    lcd_to_screen (  );
    sleep ( 1 );
}

void
mdi_recv_interrupt (  )
{
    lcd_clr (  );
    lcd_render_text ( 0, 0, "MDIRCV", 1 );
    lcd_to_screen (  );
    sleep ( 1 );
}


/**
 * Poll MDI receive queue.
 *
 * @returns -1 if no buffer available
 *          otherwise, size of buffer (excluding length and MDI type byte)
 */
int
mdi_poll_receive (  )
{
    unsigned int head, tail;

    head = _dsp[DSP_MDIRCV_HEAD];
    tail = _dsp[DSP_MDIRCV_TAIL];

    if ( head != tail )
        return _dsp[head] >> 8;

    return -1;
}


/**
 * Receive MDI buffer(long type) from DSP.
 * Buffer must be able to hold full buffer(as probed with mdiPollReceive), 
 * rounded up to multiples of 2 and must be 2-aligned.
 * @param buffer
 *   buffer[0] size in bytes
 *   buffer[1] MDI type
 *   buffer[2..] payload
 */

int
mdi_receive ( unsigned char *buffer )
{
    unsigned int head, tail, size, size2;

    buffer[0] = 'T';
    buffer[1] = 0;
    buffer[2] = _dsp[DSP_MDISND_HEAD] >> 8;
    buffer[3] = _dsp[DSP_MDISND_HEAD];
    buffer[4] = _dsp[DSP_MDISND_TAIL] >> 8;
    buffer[5] = _dsp[DSP_MDISND_TAIL];
    buffer[6] = _dsp[DSP_MDIRCV_HEAD] >> 8;
    buffer[7] = _dsp[DSP_MDIRCV_HEAD];
    buffer[8] = _dsp[DSP_MDIRCV_TAIL] >> 8;
    buffer[9] = _dsp[DSP_MDIRCV_TAIL];


    head = _dsp[DSP_MDIRCV_HEAD];
    tail = _dsp[DSP_MDIRCV_TAIL];

    if ( head != tail )
    {
        /*
         * something to get 
         */
        *( ( unsigned short * ) &buffer[0] ) = _dsp[head];
        head++;
        if ( head >= DSP_MDIRCV_QUEUEEND )
            head = DSP_MDIRCV_QUEUE;

        size = ( buffer[0] + 1 ) / 2;   /* Round up in halfwords */
        size2 = DSP_MDIRCV_QUEUEEND - head;

        if ( size > size2 )
        {
            memcpy ( ( unsigned short * ) &buffer[2], ( unsigned short * ) &_dsp[head], size2 );
            memcpy ( ( unsigned short * ) &buffer[2 + size2 * 2], ( unsigned short * ) &_dsp[DSP_MDIRCV_QUEUE], size - size2 );
            head = head + size - DSP_MDIRCV_SIZE;
        }
        else
        {
            memcpy ( ( unsigned short * ) &buffer[2], ( unsigned short * ) &_dsp[head], size );
            head = head + size;
        }
        _dsp[DSP_MDIRCV_HEAD] = head;
        return 1;
    }
    return 0;
}




/**
 * Send MDI packet(long type) to DSP.
 * Buffer size must rounded up to multiples of 2 and base must be 2-aligned.
 * Maximum packet size is (DSP_MDISND_SIZE-2)*2 (1 control word 1 guard word)
 * 
 * @param buffer
 *   buffer[0] size in bytes
 *   buffer[1] MDI type
 *   buffer[2..] payload
 */
int
mdi_send ( unsigned char *buffer )
{
    unsigned int head, tail, size, size2;
    int free;
    head = _dsp[DSP_MDISND_HEAD];
    tail = _dsp[DSP_MDISND_TAIL];

    _dsp[0xDC] = 0x3001;

    free = head - tail - 1;

    if ( free < 0 )             /* queue rolled over */
        free += DSP_MDISND_SIZE - 1;
    /*
     * IO_flashdbg(0x07000000|head, 0,0);
     * IO_flashdbg(0x07010000|tail, 0,0);
     * IO_flashdbg(0x07020000|(free&0xFFFF), 0,0);
     */
    //IO_flashdbg(buffer, 0,0);
    size = ( buffer[0] + 1 ) / 2 + 1;   /* Round up in halfwords, add control word */
    size2 = DSP_MDISND_QUEUEEND - tail; /* Size left before rollover */
    if ( size > free )
    {
        /*
         * Not enough space 
         */
        return 0;
    }


    /*
     * free >= size 
     */
    if ( size > size2 )
    {
        memcpy ( ( unsigned short * ) &_dsp[tail], ( unsigned short * ) &buffer[0], size2 );
        memcpy ( ( unsigned short * ) &_dsp[DSP_MDISND_QUEUE], ( unsigned short * ) &buffer[size2 * 2], size - size2 );
        tail = tail + size - DSP_MDISND_SIZE;
    }
    else
    {
        memcpy ( ( unsigned short * ) &_dsp[tail], ( unsigned short * ) &buffer[0], size );

        tail = tail + size;
    }

    _dsp[DSP_MDISND_TAIL] = tail;

    return 1;
}
