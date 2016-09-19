/**
 * Nokia test
 * wumpus <blacksphere@goliath.darktech.org> 2003
 */

#include <nlib/typedef.h>
#include <nlib/nokio.h>
#include <nlib/flashdbg.h>
#include <nlib/dsp.h>
#include <nlib/dspblocks.h>
#include <nlib/gensio.h>
#include <nlib/ccont.h>
#include <nlib/lcd.h>
#include <nlib/interrupt.h>
#include <nlib/ptimer.h>
#include <nlib/lights.h>

extern void flashjump (  );
extern struct dsp_codeblock block00;

char bla[] = "hallo!";

char bsstest;

void
IO_MbusCtrl ( uint x )
{
    _io[IO_MBUS_CTRL] = x;
}

void
IO_KeypadInitialize (  )
{
    //writeb(readb(IO_KEY_IRQC) | 0x1F, IO_KEY_IRQC);
    _io[IO_KEY_CCC] = 0x20;
    _io[IO_KEY_COL_RD] = 0x3F;
    _io[IO_KEY_IRQC] = 0x60;    /* 0110 0000 mask row 5 and 6 */
    _io[IO_KEY_FFF] = 0x1F;
    _io[IO_KEY_ROW_SET] = 0x1F;
    _io[IO_KEY_ROW_CLR] = 0x00;
    _io[IO_KEY_AAA] = 0x1F;
    _io[IO_KEY_BBB] = 0x1F;
    _io[IO_KEY_EEE] = 0x1F;

    /*
     * FFF is concerned with interrupt triggering
     * it seems to mean 'trigger on release'
     */

    //writeb(readb(IO_KEY_IRQC) & 0xE0, IO_KEY_IRQC);
    /*
     * enable IRQ 0
     * writeb(0x01, 0x20009);
     * writeb(readb(0x2000B) & 0xFE, 0x2000B);
     */
}

void
debug_dumpAD (  )
{
    int x, value;
    uint8 buffer[18];
    /*
     * dump A/D 
     */
    buffer[0] = 'A';
    for ( x = 0; x < 8; x++ )
        *( uint16 * ) & buffer[2 + 2 * x] = IO_CContADRead ( x );
    IO_flashdbgSendPacket ( buffer, sizeof ( buffer ) );
}

void
debug_dumpCTRLIO (  )
{
    uint8 buffer[18 + 4];
    int x;
    buffer[0] = 'C';

    for ( x = 0; x < 4; x++ )
    {
        buffer[x + 2] = _io[0x30 + x];
        buffer[x + 6] = _io[0x70 + x];
        buffer[x + 10] = _io[0xB0 + x];
        /**
		 * _io[0xF0] = (_io[0x30+x] & _io[0x70+x]) | ???;
		 */
        buffer[x + 14] = _io[0xF0 + x];
        buffer[x + 18] = _io[0xF0 + x] & ( ~_io[0x70 + x] );
    }
    IO_flashdbgSendPacket ( buffer, sizeof ( buffer ) );
}

void
debug_testCTRLIO (  )
{
    int x;
    for ( x = 0; x < 8; x++ )
    {
        /*
         * Only state 3 gives light 
         * 0x33 0x02
         * 0x73 0x02
         * 0xB3 0x00
         */
        IO_flashdbgSendPacket ( &x, 4 );
        IO_setLights ( x & 1 );
        IO_setBit ( 0x73, CTRL3_DISPLAYLEDS, x & 2 );
        IO_setBit ( 0xB3, CTRL3_DISPLAYLEDS, x & 4 );
        usleep ( 1000000 );
        debug_dumpCTRLIO (  );
    }

}

void
keyboardInterrupt (  )
{
    IO_setLights ( 3 );
    /*
     * uint8 buffer[2];
     * buffer[0] = 'I';
     * buffer[1] = '0';
     * IO_flashdbgSendPacket(buffer, 2);
     */

}

void
timerInterrupt (  )
{
    //IO_setLights(3);
    uint8 buffer[2];
    buffer[0] = 'F';
    buffer[1] = '4';
    IO_flashdbgSendPacket ( buffer, 2 );
}

volatile int count;
void
fasttimerInterrupt (  )
{
    count++;
}


extern uint8 _last_int;

void
debugInterrupt (  )
{
    //IO_setLights(3);
    int x;
    uint8 buffer[0x20 + 0x2];
    buffer[0] = 'F';
    buffer[1] = _last_int;
    for ( x = 0; x < 0x20; x++ )
        buffer[x + 2] = _io[x];
    IO_flashdbgSendPacket ( buffer, sizeof ( buffer ) );
}

void
mdiSendInterrupt (  )
{
}

void
mdiRecvInterrupt (  )
{
}

/**
 * Copy length halfwords from source to dest. Source and dest must be
 * halfword aligned.
 * TODO: optimize
 */
void
fastHWCopy ( uint16 * dest, uint16 * source, uint length )
{
    while ( length )
    {
        *( dest++ ) = *( source++ );
        length--;
    }
}

/**
 * Poll MDI receive queue.
 *
 * @returns -1 if no packet available
 *          otherwise, size of packet (excluding length and MDI type byte)
 */
int
mdiPollReceive (  )
{
    uint head, tail;
    head = _dsp[DSP_MDIRCV_HEAD];
    tail = _dsp[DSP_MDIRCV_TAIL];
    if ( head != tail )
        return _dsp[head] >> 8;
    return -1;
}

/**
 * Receive MDI packet(long type) from DSP.
 * Buffer must be able to hold full packet(as probed with mdiPollReceive), 
 * rounded up to multiples of 2 and must be 2-aligned.
 * @param buffer
 *   buffer[0] size in bytes
 *   buffer[1] MDI type
 *   buffer[2..] payload
 */
int
mdiReceive ( uint8 * buffer )
{
    uint head, tail, size, size2;
    head = _dsp[DSP_MDIRCV_HEAD];
    tail = _dsp[DSP_MDIRCV_TAIL];
    if ( head != tail )
    {
        /*
         * something to get 
         */
        *( ( uint16 * ) & buffer[0] ) = _dsp[head];
        head++;
        if ( head >= DSP_MDIRCV_QUEUEEND )
            head = DSP_MDIRCV_QUEUE;

        size = ( buffer[0] + 1 ) / 2;   /* Round up in halfwords */
        size2 = DSP_MDIRCV_QUEUEEND - head;

        if ( size > size2 )
        {
            fastHWCopy ( ( uint16 * ) & buffer[2], ( uint16 * ) & _dsp[head], size2 );
            fastHWCopy ( ( uint16 * ) & buffer[2 + size2 * 2], ( uint16 * ) & _dsp[DSP_MDIRCV_QUEUE], size - size2 );
            head = head + size - DSP_MDIRCV_SIZE;
        }
        else
        {
            fastHWCopy ( ( uint16 * ) & buffer[2], ( uint16 * ) & _dsp[head], size );
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
mdiSend ( uint8 * buffer )
{
    uint head, tail, size, size2;
    int free;
    head = _dsp[DSP_MDISND_HEAD];
    tail = _dsp[DSP_MDISND_TAIL];
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
        fastHWCopy ( ( uint16 * ) & _dsp[tail], ( uint16 * ) & buffer[0], size2 );
        fastHWCopy ( ( uint16 * ) & _dsp[DSP_MDISND_QUEUE], ( uint16 * ) & buffer[size2 * 2], size - size2 );
        tail = tail + size - DSP_MDISND_SIZE;
    }
    else
    {
        fastHWCopy ( ( uint16 * ) & _dsp[tail], ( uint16 * ) & buffer[0], size );

        tail = tail + size;
    }

    _dsp[DSP_MDISND_TAIL] = tail;

    return 1;
}

/*
uint16 mdiPktTest[] = {
	0x0270,
	0x0D00
};
*/

uint16 mdiPktTest[] = {
    0x0103,
};

//uint8 mdiPktTest[] = {0x00, 0x00};

int
main (  )
{
    int x, y, u;
    IO_initialize (  );
    //writew(0x0000, 0x30000); /* ?? (gebeurt in init_ram_table) */

    /*
     * confirm 
     */
    IO_flashdbgSetSDA ( 0x00 );
    IO_flashdbgReceiveByte (  );
    IO_flashdbgSetSDA ( 0x80 );

    usleep ( 100 );
    IO_flashdbgSetSDA ( 0x00 );
    usleep ( 100 );

    /*
     * Send dummy 
     */
    IO_flashdbg ( 0x01000000, 0, 0 );

    //flashjump();

    /*
     * clocks 
     */
    IO_gensioInitialize (  );
    IO_CContInitialize (  );
    IO_KeypadInitialize (  );
    IO_LCDInitialize (  );
    DSP_initialize (  );

    debug_dumpAD (  );

    /*
     * iets. .. (eind van setup ) 
     */
    //writeb(readb(0x20002)|0x02, 0x20002); 

    /*
     * Write watch dog 
     */
    IO_CContWrite ( 0x05FF, 0x10 );
    _io[0x03] = 0xFF;

    int rd, prev = -1, stat = 0;
    uint8 packet[32];

    /*
     * Clock divider and clocks 
     */
    _io[0x0F] = 0xFF;
    //_io[0x0D] = 0xFF;

    /*
     * Enable interrupt handling 
     */
    IO_globalInterruptEnable ( 1 );

    /*
     * Debug interrupt 
     */
    for ( x = 0; x < 8; x++ )
    {
        IO_setInterruptHandler ( x | IRQ, debugInterrupt );
        IO_setInterruptEnable ( x | IRQ, 1 );
        if ( x != 3 )
        {
            IO_setInterruptHandler ( x | FIQ, debugInterrupt );
            IO_setInterruptEnable ( x | FIQ, 1 );
        }
    }

    /*
     * Set handler 
     */
    IO_setInterruptHandler ( IRQ_KEYBOARD, keyboardInterrupt );

    /*
     * Enable IRQ 0 (Keyboard) 
     */
    IO_setInterruptEnable ( IRQ_KEYBOARD, 1 );

    /*
     * Enable interrupt for column 0-4 
     */
    _io[IO_KEY_IRQC] &= 0xE0;

    /*
     * Enable all rows 
     */
    _io[IO_KEY_ROW_SET] = 0x1F;
    _io[IO_KEY_ROW_CLR] = ~0x1F;

    /*
     * Enable timer interrupt 
     */
    iowritew ( 0x12, IO_getTimestamp ( 0 ) + 0x1000 );
    IO_setInterruptHandler ( FIQ_PTIMER, timerInterrupt );
    IO_setInterruptEnable ( FIQ_PTIMER, 1 );
    //IO_setInterruptHandler(FIQ_MBUSTIM, fasttimerInterrupt);
    //IO_setInterruptEnable(FIQ_MBUSTIM, 1);

    //IO_setLights(0);
    //IO_delay(200);
    //iowritew(0x6, 0x0000);
    u = 0;
    //_io[0x06] = _io[0x07] = 0x10;
    //_io[0x0E] = 0x00;

    /*
     * Set up MDI 
     */
    IO_setInterruptHandler ( FIQ_MDIRCV, mdiRecvInterrupt );
    IO_setInterruptHandler ( FIQ_MDISND, mdiSendInterrupt );
    IO_setInterruptEnable ( FIQ_MDIRCV, 1 );
    IO_setInterruptEnable ( FIQ_MDISND, 1 );

    //IO_setBit(IO_DSP_RESET, 0x02, 1); 
    _dsp[DSP_MDISND_HEAD] = _dsp[DSP_MDISND_TAIL] = 0x00;
    _dsp[DSP_MDIRCV_HEAD] = _dsp[DSP_MDIRCV_TAIL] = 0x80;
    DSP_startup (  );

    /*
     * IRQ 4 should now be raised 
     */
    //IO_delay(100);
    IO_setBit ( 0x22, 0x20, 1 );


    IO_delay ( 0x100 );

    while ( 1 )
    {
        //int destcount = count + 846;
        //while(count < destcount) ;

        int d = 0, r;
        /*
         * 231.3 refreshes per second
         * 4.32ms to blit entire screen
         * update takes
         */
        /*
         * for(r=0; r<231; r++) {
         * IO_LCDSendCmd(0x40);
         * IO_LCDSendCmd(0x80);
         * for(x=0; x<6; x++) {
         * //IO_LCDSendCmd(0x40 | x);
         * //IO_LCDSendCmd(0x80);
         * for(y=0; y<84; y++) {
         * IO_LCDSendData(d);
         * }
         * }
         * if(d==0) {
         * d = 0xFF;
         * } else {
         * d = 0x00;
         * }
         * }
         */
        u++;
        //x = IO_getTimestamp();
        //x = 0x32442B7E;

        //_io[0x0D] = 0x01;

        packet[0] = 'T';
        packet[1] = 0;
        packet[2] = _dsp[DSP_MDISND_HEAD] >> 8;
        packet[3] = _dsp[DSP_MDISND_HEAD];
        packet[4] = _dsp[DSP_MDISND_TAIL] >> 8;
        packet[5] = _dsp[DSP_MDISND_TAIL];
        packet[6] = _dsp[DSP_MDIRCV_HEAD] >> 8;
        packet[7] = _dsp[DSP_MDIRCV_HEAD];
        packet[8] = _dsp[DSP_MDIRCV_TAIL] >> 8;
        packet[9] = _dsp[DSP_MDIRCV_TAIL];
        IO_flashdbgSendPacket ( packet, 10 );

        //IO_flashdbgSendPacket(&count, 4);
        if ( mdiPollReceive (  ) >= 0 )
        {
            /*
             * packet available 
             */
            mdiReceive ( packet );
            IO_flashdbg ( 0x06000000, packet, packet[0] + 2 );
        }

        if ( mdiSend ( ( uint8 * ) mdiPktTest ) )
        {
            DSP_interrupt (  );
            /*
             * Success 
             */
            IO_flashdbg ( 0x06000001, 0, 0 );
        }
        else
        {
            /*
             * Fail 
             */
            IO_flashdbg ( 0x06000002, 0, 0 );
        }
        /*
         * {
         * int tail = _dsp[DSP_MDISND_TAIL];
         * _dsp[tail++] = 0x0270;
         * if(tail >= DSP_MDISND_QUEUEEND)
         * tail = DSP_MDISND_QUEUE;
         * _dsp[tail++] = 0x0D00;
         * if(tail >= DSP_MDISND_QUEUEEND)
         * tail = DSP_MDISND_QUEUE;
         * _dsp[DSP_MDISND_TAIL] = tail;
         * DSP_interrupt();
         * }
         */
        /*
         * timer 0:
         * (clock divider 256)
         * 4096.0 units takes 31722.0msec
         * clock: 129.12Hz
         * total clock: 33055Hz (*256)
         * 
         * timer 1:
         * 16384.0 units takes 15492.0msec
         * 4096.0 units takes 3877.0.msec
         * clock: 1057Hz
         */
        //IO_delay(0x100); /* 15863 */
        //IO_delay(0x400); /* 7934 */
        stat = !stat;
        /*
         * do {
         * prev = rd;
         * //writeb(readb(IO_KEY_HUH) | 0x1F, IO_KEY_HUH);
         * 
         * _io[IO_KEY_ROW_SET] = 0x01;
         * _io[IO_KEY_ROW_CLR] = ~0x01;
         * 
         * rd = _io[IO_KEY_COL_RD];
         * if(prev==-1) prev = rd;
         * //writeb(readb(IO_KEY_HUH) & 0xE0, IO_KEY_HUH);
         * } while(rd == prev);
         */
    }
}
