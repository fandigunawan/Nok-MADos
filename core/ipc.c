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


#include <hw/int.h>
#include <core/lib.h>
#include <core/ipc.h>
#include <core/sched.h>

#ifdef XX
unsigned char ipc_buffers[IPC_BUFFERS][IPC_BUFSIZE];
ipc_data ipc_datas[IPC_BUFFERS];
#endif

int
ipc_checkint ( void )
{
    return int_isactive (  );
}

void
ipc_dump ( ipc_data * data )
{
#ifdef PC
//    printf ( " buf   : %02X\n", data->b );
//    printf ( " start : %02X\n", data->s );
//    printf ( " end   : %02X\n", data->e );
#ifdef XX
    printf ( " buf[s]: %02X\n", ipc_buffers[data->b][data->s] );
#else
    printf ( " buf[s]: %02X\n", data->b[data->s] );
#endif
//    printf ( "\n" );
#endif
}

#define xLOCK(c) \
{\
    if ( ipc_checkint () )\
	return 0;\
    while ( data->l )\
    {\
	int_enable ();\
	while ( data->l );\
	int_disable ();\
    }\
    data->l = 1;\
    int_enable ();\
}

#define LOCK(c) \
{\
    if ( ipc_checkint () )\
	return 0;\
    while ( data->l );\
    data->l = 1;\
}

#define UNLOCK    data->l = 0;

void
ipc_wakeup_all ( void )
{
    unsigned char p;
    unsigned char thread;

    for ( thread = 0; thread < SCHED_THREADS; thread++ )
    {
        p = sched_get_parm ( thread );

        if ( ( p & SCHED_PARM_WAITIPC ) == SCHED_PARM_WAITIPC )
            sched_set_parm ( thread, SCHED_PARM_RUN /*p & ~SCHED_PARM_WAITIPC */  );
    }
    return;
}

void
ipc_wakeup ( unsigned char thread )
{
    unsigned char p = sched_get_parm ( thread );

    if ( ( p & SCHED_PARM_WAITIPC ) == SCHED_PARM_WAITIPC )
        sched_set_parm ( thread, SCHED_PARM_RUN /*p & ~SCHED_PARM_WAITIPC */  );

    return;
}

unsigned int
ipc_get_size ( ipc_data * data, int lock )
{
    unsigned int len;

    if ( lock )
        LOCK ( ipc_get_size ) if ( data->s <= data->e )
            len = data->e - data->s;
        else
            len = ( IPC_BUFSIZE - data->s ) + data->e;

    if ( lock )
        UNLOCK;

    return len;
}

// reorders the buffer, so start will be at pos 0
void
ipc_reorder ( ipc_data * data )
{
    unsigned char tmp[IPC_BUFSIZE];
    unsigned int pos;
#ifdef XX
    unsigned int buf;
#else
    unsigned char *buf;
#endif
    unsigned int len;

    pos = data->s;
    buf = data->b;

    len = ipc_get_size ( data, 1 );

#ifdef XX
    memcpy ( tmp, ipc_buffers[buf] + pos, IPC_BUFSIZE - pos );
    memcpy ( tmp + IPC_BUFSIZE - pos, ipc_buffers[buf], pos );

    memcpy ( ipc_buffers[buf], tmp, IPC_BUFSIZE );
#else
    memcpy ( tmp, buf + pos, IPC_BUFSIZE - pos );
    memcpy ( tmp + IPC_BUFSIZE - pos, buf, pos );

    memcpy ( buf, tmp, IPC_BUFSIZE );
#endif
    data->s = 0;
    data->e = len;
}

unsigned char
ipc_poll ( void )
{
    ipc_data *data;


    data = ( ipc_data * ) sched_get_data ( 0xFF, 0 );
    if ( !data )
        return 0;

    if ( data->s == data->e )
        return 0;

    return 1;
}

unsigned char *
ipc_read ( unsigned int *len )
{
    ipc_data *data;

    data = ( ipc_data * ) sched_get_data ( 0xFF, 0 );
    if ( !data )
        return 0;

    while ( !ipc_poll (  ) )
        sched_set_parm ( 0xFF, SCHED_PARM_WAITIPC | SCHED_PARM_STOP );

    // since we return a ptr to the buffer, we have to make sure
    // data is saved continous, not wrapped in the buffer   
    LOCK ( ipc_read );
    if ( data->s > data->e )
        ipc_reorder ( data );
    UNLOCK;

#ifdef XX
    if ( len )
        *len = ( unsigned char ) ipc_buffers[data->b][data->s];
    ipc_wakeup_all (  );
    return ipc_buffers[data->b] + data->s + 1;
#else
    if ( len )
        *len = ( unsigned char ) data->b[data->s];
    ipc_wakeup_all (  );
    return data->b + data->s + 1;
#endif
}

unsigned int
ipc_get_blocksize ( ipc_data * data )
{
#ifdef XX
    return ipc_buffers[data->b][data->s];
#else
    return data->b[data->s];
#endif
}

// flushes the actual entry in buffer
int
ipc_flush ( void )
{
    ipc_data *data;
    char buf[128];

    data = ( ipc_data * ) sched_get_data ( 0xFF, 0 );
    if ( !data || !ipc_poll (  ) )
        return;

    xbus_send_packet ( "ipc_flush: --------", 0 );
    LOCK ( ipc_flush );
    xbus_send_packet ( "ipc_flush: locked", 0 );
//    sprintf ( buf, "ipc_flush: s->%i blocksize->%i", data->s, ipc_get_blocksize ( data ) );
//    xbus_send_packet ( buf, 0 );
    data->s += ipc_get_blocksize ( data ) + 1;
//    sprintf ( buf, "ipc_flush: s->%i", data->s );
//    xbus_send_packet ( buf, 0 );
    data->s = lib_mod ( data->s, IPC_BUFSIZE );
//    sprintf ( buf, "ipc_flush: s->%i", data->s );
//    xbus_send_packet ( buf, 0 );
    UNLOCK;
    xbus_send_packet ( "ipc_flush done", 0 );
    ipc_wakeup_all (  );
}

int
ipc_add ( unsigned char thread, unsigned char *buf, unsigned int len )
{
    ipc_data *data;

    data = ( ipc_data * ) sched_get_data ( thread, 0 );
    if ( !data )
        return 0;

    xbus_send_packet ( "ipc_add: ---------", 0 );

  addagain:
    while ( ipc_get_size ( data, 1 ) + len >= IPC_BUFSIZE - 5 )
    {
#ifdef PC
//        printf ( "add: size %i\n", ipc_get_size ( data ) );
//        sleep ( 1000 );
#endif
//  mbus_transmit ( "IPC_ADD_ENTER_WAIT\r\n", 20 );
        sched_set_parm ( 0xFF, SCHED_PARM_WAITIPC | SCHED_PARM_STOP );
//  mbus_transmit ( "IPC_ADD_LEAVE_WAIT\r\n", 20 );

    }
//    mbus_transmit ( "IPC_ADD_LEAVE_WAIT______________________________________________", 60 );
    xbus_send_packet ( "ipc_add: enter lock", 0 );

    LOCK ( ipc_add );

    if ( ipc_get_size ( data, 0 ) + len >= IPC_BUFSIZE - 5 )
    {
//  mbus_transmit ( "IPC_ADD_AGAIN_____\r\n", 20 );
        UNLOCK;
        goto addagain;
    }
    //
    // too lazy to copy it twice... just reorder it and append
    // TODO: leave this reorder.. we have a RINGBUFFER!!!
    //
    if ( data->s > data->e || data->e + 5 + len >= IPC_BUFSIZE )
        ipc_reorder ( data );


#ifdef XX
    ipc_buffers[data->b][data->e] = ( unsigned char ) len;
    memcpy ( ipc_buffers[data->b] + data->e + 1, buf, len );
    data->e += len + 1;
    ipc_buffers[data->b][data->e] = 0x00;

//    xbus_send_packet ( ipc_buffers[data->b], 64 );
#else
    data->b[data->e] = ( unsigned char ) len;
    memcpy ( data->b + data->e + 1, buf, len );
    data->e += len + 1;
    data->b[data->e] = 0x00;

//    xbus_send_packet ( data->b, 64 );
#endif

    UNLOCK;

    xbus_send_packet ( "ipc_add: unlock", 0 );
    ipc_wakeup ( thread );

    xbus_send_packet ( "ipc_add: === done ===", 0 );
    return 1;
}

int
ipc_release_data ( unsigned char thread )
{
    ipc_data *data;

    data = ( ipc_data * ) sched_get_data ( 0xFF, 0 );
    if ( !data )
        return;

    if ( data->b )
        free ( data->b );

    free ( data );
    sched_set_data ( thread, SCHED_DATA_IPC, NULL );
}

unsigned char
ipc_assign_data ( unsigned char thread, unsigned char num )
{
#ifdef XX
    ipc_data *data = &ipc_datas[num];

    data->b = num;
    data->s = 0;
    data->e = 0;
    data->l = 0;
    memset ( ipc_buffers[num], 0x00, IPC_BUFSIZE );
    sched_set_data ( thread, SCHED_DATA_IPC, data );
#else
    ipc_data *data = ( ipc_data * ) malloc ( sizeof ( ipc_data ) );

    data->b = ( void * ) malloc ( IPC_BUFSIZE );
    data->s = 0;
    data->e = 0;
    data->l = 0;
    memset ( data->b, 0x00, IPC_BUFSIZE );
    sched_set_data ( thread, SCHED_DATA_IPC, data );
#endif
}

void
ipc_test ( void )
{
#ifdef XPC
    ipc_data *data = &ipc_datas[0];

    sched_set_data ( 0x00, SCHED_DATA_IPC, data );

    data->b = 0;
    data->s = 0;
    data->e = 0;

    printf ( "initial:\n" );
    ipc_dump ( data );

    printf ( "add 150\n" );
    if ( !ipc_add ( 0x00, "Test2", 150 ) )
        printf ( "add failed\n" );
    ipc_dump ( data );

    printf ( "add 50\n" );
    if ( !ipc_add ( 0x00, "Test2", 50 ) )
        printf ( "add failed\n" );
    ipc_dump ( data );

    printf ( "add 5\n" );
    if ( !ipc_add ( 0x00, "Test2", 5 ) )
        printf ( "add failed\n" );
    ipc_dump ( data );
    printf ( "add 5\n" );
    if ( !ipc_add ( 0x00, "Test2", 5 ) )
        printf ( "add failed\n" );
    ipc_dump ( data );
    printf ( "add 5\n" );
    if ( !ipc_add ( 0x00, "Test2", 5 ) )
        printf ( "add failed\n" );
    ipc_dump ( data );
    printf ( "add 5\n" );
    if ( !ipc_add ( 0x00, "Test2", 5 ) )
        printf ( "add failed\n" );
    ipc_dump ( data );



    printf ( "flush 5\n" );
    ipc_flush (  );
    ipc_dump ( data );
    printf ( "flush 5\n" );
    ipc_flush (  );
    ipc_dump ( data );
    printf ( "flush 5\n" );
    ipc_flush (  );
    ipc_dump ( data );
    printf ( "flush 5\n" );
    ipc_flush (  );
    ipc_dump ( data );
    printf ( "flush 50\n" );
    ipc_flush (  );
    ipc_dump ( data );
    printf ( "flush 150\n" );
    ipc_flush (  );
    ipc_dump ( data );







#endif
}
