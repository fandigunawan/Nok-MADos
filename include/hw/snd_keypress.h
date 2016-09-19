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

const unsigned char snd_key[] = {
    0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x80, 0x80, 0x80, 0x82, 0x82, 0x82, 0x83, 0x84, 0x86, 0x85,
    0x87, 0x88, 0x84, 0x86, 0x88, 0x83, 0x84, 0x86, 0x80, 0x82, 0x81, 0x7B, 0x7F, 0x81, 0x83, 0x89,
    0x86, 0x86, 0x86, 0x83, 0x80, 0x86, 0x97, 0x7C, 0x74, 0x93, 0x8B, 0x85, 0x85, 0x8B, 0x8C, 0x71,
    0x77, 0x88, 0x7C, 0x73, 0x7F, 0x80, 0x7C, 0x82, 0x76, 0x77, 0x79, 0x73, 0x7B, 0x7F, 0x7E, 0x7B,
    0x7D, 0x7C, 0x7E, 0x81, 0x7E, 0x81, 0x80, 0x7D, 0x82, 0x7B, 0x76, 0x85, 0x81, 0x78, 0x7C, 0x7F,
    0x87, 0x78, 0x72, 0x87, 0x8B, 0x81, 0x6F, 0x7C, 0x87, 0x66, 0x6C, 0x7E, 0x7A, 0x7E, 0x7D, 0x84,
    0x89, 0x74, 0x69, 0x71, 0x6E, 0x74, 0x7A, 0x74, 0x6C, 0x76, 0x7C, 0x71, 0x89, 0x93, 0x7E, 0x7D,
    0x87, 0x80, 0x7D, 0x92, 0x8B, 0x7E, 0x8C, 0x90, 0x87, 0x81, 0x81, 0x87, 0x7D, 0x71, 0x7E, 0x80,
    0x6D, 0x6E, 0x76, 0x76, 0x76, 0x73, 0x7C, 0x81, 0x6F, 0x6C, 0x76, 0x6E, 0x6F, 0x76, 0x79, 0x7C,
    0x76, 0x72, 0x7A, 0x7B, 0x72, 0x7A, 0x84, 0x7C, 0x7B, 0x82, 0x83, 0x86, 0x8E, 0x90, 0x88, 0x82,
    0x83, 0x84, 0x7F, 0x78, 0x7F, 0x89, 0x88, 0x83, 0x86, 0x87, 0x7C, 0x7A, 0x80, 0x7A, 0x7C, 0x83,
    0x7F, 0x79, 0x77, 0x77, 0x78, 0x7A, 0x7E, 0x80, 0x7D, 0x7E, 0x7D, 0x7C, 0x7E, 0x7F, 0x83, 0x86,
    0x84, 0x83, 0x82, 0x81, 0x82, 0x81, 0x80, 0x84, 0x84, 0x82, 0x84, 0x82, 0x80, 0x83, 0x82, 0x82,
    0x83, 0x84, 0x84, 0x81, 0x7C, 0x7D, 0x7D, 0x7B, 0x81, 0x85, 0x81, 0x80, 0x82, 0x7F, 0x7D, 0x7F,
    0x80, 0x81, 0x83, 0x84, 0x84, 0x83, 0x81, 0x83, 0x86, 0x83, 0x81, 0x82, 0x82, 0x84, 0x84, 0x80,
    0x7F, 0x82, 0x85, 0x85, 0x86, 0x87, 0x85, 0x7F, 0x7D, 0x7E, 0x7D, 0x7D, 0x7E, 0x7F, 0x7E, 0x7C,
    0x7A, 0x7A, 0x7C, 0x7E, 0x7E, 0x7F, 0x81, 0x7F, 0x7E, 0x7E, 0x7E, 0x80, 0x81, 0x81, 0x82, 0x82,
    0x81, 0x7F, 0x7E, 0x7D, 0x7B, 0x7D, 0x7F, 0x81, 0x80, 0x7D, 0x7B, 0x7D, 0x7D, 0x7D, 0x7F, 0x80,
    0x80, 0x7F, 0x7E, 0x7E, 0x7E, 0x7E, 0x7F, 0x7F, 0x7E, 0x7E, 0x7D, 0x7E, 0x7E, 0x7E, 0x80, 0x81,
    0x82, 0x80, 0x7E, 0x7C, 0x7B, 0x7C, 0x7D, 0x7E, 0x7E, 0x7D, 0x7C, 0x7B, 0x7B, 0x7B, 0x7D, 0x7F,
    0x7F, 0x7E, 0x7F, 0x80, 0x7F, 0x81, 0x83, 0x83, 0x82, 0x81, 0x81, 0x80, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x80, 0x81, 0x81, 0x80, 0x7F, 0x7E, 0x7E, 0x7E, 0x7D, 0x7E,
    0x7E, 0x7E, 0x7D, 0x7D, 0x7C, 0x7C, 0x7C, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7C, 0x7D, 0x7D,
    0x7D, 0x7E, 0x7E, 0x7E, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7E, 0x7F, 0x7E, 0x7E, 0x7D, 0x7D, 0x7E, 0x7D, 0x7E, 0x7E, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7E,
    0x7E, 0x7E, 0x7D, 0x7D, 0x7D, 0x7D, 0x7E, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80,
    0x81, 0x81, 0x81, 0x80, 0x80, 0x80, 0x80, 0x81, 0x82, 0x81, 0x81, 0x81, 0x81, 0x82, 0x82, 0x82,
    0x82, 0x82, 0x82, 0x80, 0x7F, 0x82, 0x82, 0x80, 0x80, 0x81, 0x80, 0x80, 0x81, 0x82, 0x82, 0x81,
    0x81, 0x82, 0x81, 0x80, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x83, 0x80, 0x80, 0x82, 0x81,
    0x80, 0x7F, 0x82, 0x81, 0x7F, 0x81, 0x83, 0x83, 0x82, 0x80, 0x82, 0x81, 0x80, 0x81, 0x82, 0x82,
    0x80, 0x81, 0x82, 0x80, 0x80, 0x80, 0x81, 0x81, 0x7F, 0x7F, 0x7F, 0x7E, 0x7F, 0x80, 0x80, 0x81,
    0x82, 0x81, 0x81, 0x81, 0x81, 0x81, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x7F, 0x7F, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F,
    0x7E, 0x7E, 0x7F, 0x7F, 0x7E, 0x7F, 0x7F, 0x7F, 0x7E, 0x7E, 0x7F, 0x7F, 0x7F, 0x7F, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x81, 0x80, 0x80, 0x80, 0x81, 0x81, 0x81, 0x81, 0x81, 0x80, 0x80, 0x80, 0x80,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7E, 0x7E, 0x7F, 0x7F, 0x7E,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x7F, 0x7F, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x7F, 0x7E, 0x7E, 0x7E, 0x7E, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80,
    0x82, 0x7F, 0x7D, 0x81, 0x81, 0x7E, 0x7E, 0x80, 0x7F, 0x7E, 0x7F, 0x7F, 0x80, 0x7F, 0x80, 0x81,
    0x80, 0x80, 0x82, 0x81, 0x80, 0x81, 0x81, 0x80, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x80,
    0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x7F, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x81, 0x81, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x80, 0x80, 0x80, 0x7F, 0x80,
    0x80, 0x80, 0x81, 0x81, 0x81, 0x82, 0x81, 0x81, 0x82, 0x81, 0x81, 0x82, 0x82, 0x82, 0x82, 0x84,
    0x83, 0x81, 0x82, 0x82, 0x8A, 0x8E, 0x88, 0x85, 0x81, 0x82, 0x85, 0x88, 0x87, 0x89, 0x8A, 0x80,
    0x7F, 0x80, 0x7F, 0x83, 0x7F, 0x7C, 0x82, 0x80, 0x7D, 0x7F, 0x7D, 0x80, 0x7D, 0x7F, 0x86, 0x7D,
    0x7E, 0x7F, 0x78, 0x7A, 0x76, 0x7C, 0x7F, 0x78, 0x7F, 0x7C, 0x79, 0x80, 0x7B, 0x7F, 0x80, 0x7A,
    0x84, 0x83, 0x7B, 0x7E, 0x7E, 0x7B, 0x80, 0x84, 0x81, 0x7F, 0x81, 0x85, 0x80, 0x7F, 0x83, 0x83,
    0x81, 0x81, 0x84, 0x7F, 0x7C, 0x82, 0x80, 0x7C, 0x80, 0x80, 0x7E, 0x81, 0x7E, 0x7D, 0x83, 0x7E,
    0x80, 0x82, 0x7F, 0x83, 0x80, 0x80, 0x85, 0x81, 0x82, 0x82, 0x7C, 0x81, 0x7F, 0x80, 0x85, 0x7F,
    0x84, 0x89, 0x80, 0x80, 0x86, 0x85, 0x80, 0x80, 0x82, 0x7E, 0x7F, 0x80, 0x7D, 0x7A, 0x79, 0x7B,
    0x7B, 0x7C, 0x7C, 0x7A, 0x7E, 0x7A, 0x7C, 0x80, 0x77, 0x7C, 0x83, 0x7F, 0x81, 0x80, 0x7F, 0x7F,
    0x7D, 0x80, 0x7D, 0x7F, 0x84, 0x83, 0x84, 0x80, 0x7E, 0x85, 0x80, 0x84, 0x85, 0x80, 0x87, 0x80,
    0x7D, 0x80, 0x7D, 0x82, 0x7F, 0x80, 0x82, 0x7C, 0x80, 0x80, 0x7C, 0x7F, 0x81, 0x7F, 0x7E, 0x81,
    0x7F, 0x7F, 0x81, 0x80, 0x83, 0x80, 0x7F, 0x84, 0x81, 0x7E, 0x80, 0x80, 0x82, 0x82, 0x7E, 0x81,
    0x80, 0x7F, 0x80, 0x7F, 0x80, 0x81, 0x7E, 0x7E, 0x7F, 0x7C, 0x7B, 0x7D, 0x7E, 0x7E, 0x7F, 0x7E,
    0x7E, 0x7E, 0x7D, 0x7D, 0x7D, 0x7E, 0x80, 0x7F, 0x7E, 0x7E, 0x7F, 0x7F, 0x7D, 0x7F, 0x7F, 0x7E,
    0x80, 0x7F, 0x7E, 0x7E, 0x7E, 0x80, 0x80, 0x80, 0x81, 0x80, 0x7F, 0x7E, 0x7D, 0x7E, 0x7D, 0x7E,
    0x7E, 0x7E, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7E, 0x7E, 0x7D, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E,
    0x7E, 0x7F, 0x7E, 0x7F, 0x7E, 0x7F, 0x7E, 0x7E,
};
