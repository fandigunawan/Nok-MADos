/**
 * DSP code blocks
 * wumpus <blacksphere@goliath.darktech.org> 2003
 */

#include <nlib/typedef.h>
#include <nlib/nokio.h>
#include <nlib/dsp.h>

#include "dspblocks/block00.h"
#include "dspblocks/block01.h"
#include "dspblocks/block14.h"

/** 
 * Get codeblock by ID 
 * @param n
 *   Codeblock ID
 *   0x00 = Initialisation
 *   0x01 = MDI setup
 *   0x14 = Secondary initialisation
 */
struct dsp_codeblock *
DSP_getCodeBlock ( int n )
{
    switch ( n )
    {
        case 0x00:
            return &block00;
        case 0x01:
            return &block01;
        case 0x14:
            return &block14;
    }
    return 0;
}
