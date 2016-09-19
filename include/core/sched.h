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



#define SCHED_THREADS  8
#define SCHED_NUM_DATA 8

#define SCHED_PARM_STOP    0x01
#define SCHED_PARM_RUN     0x02
#define SCHED_PARM_MASTER  0x04
#define SCHED_PARM_WAITIPC 0x08

#define SCHED_DATA_IPC 0x00

#define SCHED_LOCK sched_set_parm ( 0xFF, SCHED_PARM_MASTER );
#define SCHED_UNLOCK sched_set_parm ( 0xFF, SCHED_PARM_RUN );

typedef struct
{
    unsigned char id;
    unsigned char used;
    unsigned char started;
    unsigned char remove;
    unsigned int regs[17];
    unsigned char parms;
    unsigned int act_time;
    unsigned char *data[SCHED_NUM_DATA];
}
thread_t;

typedef struct
{
    unsigned int time;
    unsigned int next_act;
    unsigned char force_thread;
    unsigned char cur_thread;
    unsigned char num_threads;
    thread_t threads[SCHED_THREADS];
    unsigned int regs[17];
}
sched_t;

#ifdef _SCHED_
unsigned int sched_stacks[] = {
    0x00110000, 0x00111000, 0x00112000, 0x00113000,
    0x00114000, 0x00115000, 0x00116000, 0x00117000
};
#endif



unsigned int sched_now ( void );
void sched_yield ( void );
void sched_init ( void );
void sched_save ( unsigned char reg, unsigned int val );
unsigned int sched_get ( unsigned char reg );
void sched_critical ( void );
void sched_next ( void );
void sched_delete ( unsigned char num );
void sched_remove ( unsigned char num );
void sched_threadend ( void );
void sched_update_activation ( void );
void sched_activation ( void );
void sched_set_activation ( unsigned char thread, unsigned int time );
void sched_set_parm ( unsigned char thread, unsigned char parm );
unsigned char sched_get_parm ( unsigned char thread );
unsigned char sched_add ( unsigned int addr, unsigned int thumb, unsigned char parm );
