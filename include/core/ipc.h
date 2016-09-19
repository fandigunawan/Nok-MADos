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


#ifdef LOADER
#define IPC_BUFFERS 0x04
#define IPC_BUFSIZE 0x20
#else
#define IPC_BUFFERS 0x04
#define IPC_BUFSIZE 0xFF
#endif

#ifdef XX
unsigned char b;                // buffer number
#endif

typedef struct
{
    unsigned char *b;           // buffer number
    unsigned int s;             // ringbuffer start
    unsigned int e;             // ringbuffer end
    unsigned char l;            // locked?
}
ipc_data;

void ipc_wakeup_all ( void );
void ipc_wakeup ( unsigned char thread );
unsigned int ipc_get_size ( ipc_data * data, int lock );
void ipc_reorder ( ipc_data * data );
unsigned char ipc_poll ( void );
unsigned char *ipc_read ( unsigned int *len );
unsigned int ipc_get_blocksize ( ipc_data * data );
int ipc_flush ( void );
int ipc_add ( unsigned char thread, unsigned char *buf, unsigned int len );
unsigned char ipc_assign_data ( unsigned char thread, unsigned char num );
