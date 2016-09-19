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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int
main ( void )
{
    int i = 1;
    unsigned char buf = 0;
    FILE *f = NULL;

    f = fopen ( "snd.ub", "rb" );
    if ( !f )
        return 0;

    printf ( "const unsigned char snd_block[] =\n{\n" );
    while ( fread ( &buf, 1, 1, f ) )
    {
        printf ( "0x%02X, ", buf );
        if ( i == 16 )
        {
            printf ( "\n" );
            i = 1;
        }
        else
            i++;
    }
    printf ( "0x%02X, ", 0 );
    printf ( "};\n" );
    fclose ( f );
}
