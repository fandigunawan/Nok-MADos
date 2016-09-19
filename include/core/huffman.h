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

#ifndef MADOS_HUFFMAN
#define MADOS_HUFFMAN

//needs some tweaking
typedef struct
{
    unsigned int uncompressed_size;
    unsigned int compressed_size;
    const unsigned char *blockname;
} huffman_compressed;

int Huffman_Compress ( unsigned char *in, unsigned char *out, unsigned int insize );
void Huffman_Uncompress ( unsigned char *in, unsigned char *out, unsigned int insize, unsigned int outsize );
void huffman_decompress ( huffman_compressed hc, unsigned char *uncompressed );
inline void huffman_free ( unsigned char *uncompressed );
void huffman_testtextdisplay ( void );

#endif
