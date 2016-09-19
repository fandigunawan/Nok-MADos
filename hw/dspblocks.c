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

/**
 * DSP code blocks
 * wumpus <blacksphere@goliath.darktech.org> 2003
 *
 * merged into MADos by g3gg0
 */

#include <hw/dsp.h>
#include <hw/dspblocks.h>
#include <dspblocks/block00.h>
#include <dspblocks/block01.h>
#include <dspblocks/block14.h>


/** 
 * Get codeblock by ID 
 * @param n
 *   Codeblock ID
 *   0x00 = Initialisation
 *   0x01 = MDI setup
 *   0x14 = Secondary initialisation
 */
struct dsp_codeblock *
dspblocks_get_block ( int n )
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
