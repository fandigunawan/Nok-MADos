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
    char *filename_in, *filename_out, *blockname, *tmp;
    unsigned char buf = 0;
    FILE *input, *output;

    filename_in = ( char * ) malloc ( 256 );
    filename_out = ( char * ) malloc ( 256 );
    blockname = ( char * ) malloc ( 256 );
    tmp = ( char * ) malloc ( 512 );

    printf ( "this tool converts a hex file to a c-header file\n" );
    // similiar to conv.c but more options

    printf ( "input file (hex): " );
    scanf ( "%s", filename_in );

    printf ( "\noutput file (header, add extension .h): " );
    scanf ( "%s", filename_out );

    printf ( "\nname of block: " );
    scanf ( "%s", blockname );

    input = fopen ( filename_in, "rb" );
    output = fopen ( filename_out, "wba" );
    if ( !input || !output )
    {
        printf ( "\nthe input or output file couldn't be opened ... aborting ..." );
        //files should be closed, mem should be free'd
        return 1;
    }

    sprintf ( tmp, "const unsigned char %s[] =\n{\n    ", blockname );
    fwrite ( tmp, 1, strlen ( tmp ), output );
    while ( fread ( &buf, 1, 1, input ) )
    {
        sprintf ( tmp, "0x%02X, ", buf );
        fwrite ( tmp, 1, strlen ( tmp ), output );
        if ( i == 16 )
        {
            fwrite ( "\n    ", 1, 5, output );
            i = 1;
        }
        else
            i++;
    }
    fwrite ( "\n};\n", 1, 4, output );

    fclose ( input );
    fclose ( output );

    free ( filename_in );
    free ( filename_out );
    free ( blockname );
    free ( tmp );

    printf ( "done ;)" );
    return 0;

}
