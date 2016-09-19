/**
 * DSP/MDI functions
 * wumpus <blacksphere@goliath.darktech.org> 2003
 */

#include <nlib/typedef.h>
#include <nlib/nokio.h>
#include <nlib/flashdbg.h>

#include <nlib/dsp.h>
#include <nlib/dspblocks.h>
#include <nlib/interrupt.h>


/** 
 * Upload codeblock to DSP
 *
 * @param c	Code to upload
 * @param sub	Sub block
 *              -1  don't care about segmenting, just send all
 *              0   first block
 *              1.. second to nth block
 * @returns  	0 if completed, otherwise more to go
 **/
int
DSP_uploadCodeblock ( struct dsp_codeblock *c, int sub )
{
    uint totalsize = c->header[DSP_UPLHDR_SIZE];
    uint doffset = c->header[DSP_UPLHDR_OFFSET];
    uint blocksize = c->header[DSP_UPLHDR_BLOCKSIZE];
    uint soffset;               /* data source offset */
    uint ptr;
    if ( sub >= 0 )
    {
        /*
         * One block 
         */
        soffset = sub * blocksize;
        if ( ( soffset + blocksize ) > totalsize )
            blocksize = totalsize - soffset;
        //IO_flashdbg(0x040F0000 | soffset, 0, 0);
    }
    else
    {
        /*
         * Transfer all.. 
         */
        soffset = 0;
        blocksize = totalsize;
    }
    /*
     * upload code 
     */
    for ( ptr = 0; ptr < blocksize; ptr++ )
        _dsp[doffset++] = c->data[soffset++];
    if ( sub <= 0 )
    {
        /*
         * upload header 
         */
        for ( ptr = 0; ptr < 5; ptr++ )
            _dsp[DSP_UPLOADHEADER + ptr] = c->header[ptr];
    }
    return soffset < totalsize;
}

/**
 * Interrupt handler FROM DSP
 */
static void
dspInterruptHandler (  )
{
    static uint8 sub = 0;
    uint cmd = _dsp[DSP_UPLOADREQUEST];

    if ( cmd )
    {
        if ( sub == 0 )
            IO_flashdbg ( 0x04010000 | cmd, 0, 0 );
        struct dsp_codeblock *block = DSP_getCodeBlock ( cmd );
        if ( block != 0 )
        {
            //IO_flashdbg(0x04020000 | sub, 0, 0);
            if ( DSP_uploadCodeblock ( block, sub ) )
            {
                /*
                 * more to go 
                 */
                sub++;
                //IO_flashdbg(0x04030000 | DSP_UPLOADREPLY_MORE, 0, 0);
                _dsp[DSP_UPLOADREPLY] = DSP_UPLOADREPLY_MORE;
            }
            else
            {
                sub = 0;
                //IO_flashdbg(0x04030000 | DSP_UPLOADREPLY_FINISHED, 0, 0);
                _dsp[DSP_UPLOADREPLY] = DSP_UPLOADREPLY_FINISHED;
            }

            DSP_interrupt (  );

        }
        else
        {
            /*
             * Error -- non existant block req 
             */
        }
    }
}

/**
 * Initialize DSP
 */
void
DSP_initialize (  )
{
    int x;
    DSP_enable ( 0 );
    /*
     * Clear shared mem 
     */
    for ( x = 0; x < DSP_SHARED_SIZE; x++ )
        _dsp[x] = 0;

    /*
     * DSP may access shared memory 
     */
    _dspif[0] = DSPIF_ENABLE_SHARED;

}

/**
 * Reset and startup DSP with default program. 
 * 1) Make sure the DSP is initialised with DSP_initialize before calling 
 * this.
 * 2) MDI should be initialized.
 */
void
DSP_startup (  )
{
    DSP_enable ( 0 );
    /*
     * Enable DSP interrupt 
     */
    IO_setInterruptHandler ( IRQ_DSP, dspInterruptHandler );
    IO_setInterruptEnable ( IRQ_DSP, 1 );

    _dsp[DSP_INITDATA + 0] = 0x900F;
    _dsp[DSP_INITDATA + 11] = 0xFF80;
    _dsp[DSP_INITDATA + 13] = 0xFFFF;

    /*
     * Initialisation code block 
     */
    DSP_uploadCodeblock ( DSP_getCodeBlock ( 0x00 ), -1 );
    DSP_enable ( 1 );
}

/**
 * Interrupt DSP
 */
void
DSP_interrupt (  )
{
    _dspif[0] = DSPIF_INTERRUPT;
}

/**
 * Enable/Reset DSP
 *
 * @param state: 0=disable 1=enable
 */
void
DSP_enable ( int state )
{
    /*
     * Take 'em out 
     */
    IO_setBit ( IO_DSP_RESET, DSP_ENABLE, state );
}
