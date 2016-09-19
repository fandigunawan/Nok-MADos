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


const unsigned char kpd_getkey_matrix[2][25] = {

    {0x10, 0x20, 0x12, 0x03, 0x0F,
     0x07, 0x08, 0x09, 0x0f, 0x0F,
     0x04, 0x05, 0x06, 0x0f, 0x0F,
     0x01, 0x02, 0x01, 0x13, 0x0F,
     0x21, 0x0f, 0x00, 0x16, 0x0F},
    //return values for the keys (3310):
    //dd    *    |   menu    |     #      |     3  (PWR)|
    //dd    7    |    8      |     9      |     NA (PWR)|
    //dd    4    |    5      |     6      |     NA (PWR)|
    //dd    1    |    2      |     NA     | down (PWR)  |
    //dd  clear  |   NA      |     0      | hoch (PWR)  |
    {0x12, 0x00, 0x10, 0x21, 0x24,
     0x09, 0x08, 0x07, 0x13, 0x23,
     0x06, 0x05, 0x04, 0x16, 0x22,
     0x03, 0x02, 0x01, 0x20, 0x25,
     0x30, 0x0F, 0x0F, 0x0F, 0x0F}
    //return values for the keys (8210):
    //dd    #    |     0     |     *     |  SOFTBTN2  |    VOLUP    |
    //dd    9    |     8     |     7     |   DOWN     |     RED     |
    //dd    6    |     5     |     4     |    UP      |    GREEN    |
    //dd    3    |     2     |     1     |  SOFTBTN1  |   VOLDOWN   |
    //dd   PWR   |           |           |            |             |
};

const unsigned char kpd_off[2][3] = {
    {0x0F, 0x13, 0x16},
    {0x03, 0x06, 0x30}
};
