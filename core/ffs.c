
#include <core/fs.h>
#include <core/ffs.h>
#include <core/lib.h>
#include <hw/flash.h>
#include <hw/mbus.h>

void *ffs_base = NULL;
void *ffs_end = NULL;


#ifdef PC
void *ffs_emu_base = NULL;
FILE *fopen ( const char *path, const char *mode );
#define flash_write(d,s,l) ffs_emu_flash(d,s,l)
#define flash_erase(d)     ffs_emu_erase(d)
#endif


int
ffs_validaddr ( void *base )
{
#ifndef PC
    if ( !( ( unsigned long ) base < 0x00400000 && ( unsigned long ) base > 0x00200000 ) )
        return 0;
#endif
    return 1;
}

#ifdef PC
int
ffs_emu_write ( void )
{
    FILE *f;

    if ( !ffs_emu_base )
    {
        ffs_emu_base = ( void * ) malloc ( 0x00010000 );
        if ( !ffs_emu_base )
            return -FFS_INV_ADDR;
    }
    f = fopen ( "ffs.bin", "wb" );
    if ( !f )
        return -FFS_INV_ADDR;
    fwrite ( ffs_emu_base, 1, 0x00010000, f );
    fclose ( f );

    return 0;
}

int
ffs_emu_read ( void )
{
    FILE *f;

    if ( !ffs_emu_base )
    {
        ffs_emu_base = ( void * ) malloc ( 0x00010000 );
        if ( !ffs_emu_base )
            return -FFS_INV_ADDR;
    }
    f = fopen ( "ffs.bin", "rb" );
    if ( !f )
        return -FFS_INV_ADDR;
    fread ( ffs_emu_base, 1, 0x00010000, f );
    fclose ( f );

    return 0;
}
unsigned char
ffs_emu_erase ( void *dest )
{
    memset ( dest, 0xFF, 0x00010000 );
    ffs_emu_write (  );

    return 1;
}
unsigned char
ffs_emu_flash ( void *dest, void *src, unsigned int length )
{
    memcpy ( dest, src, length );
    ffs_emu_write (  );

    return 1;
}

#endif

int
ffs_check ( void *base )
{
    ffs_hdr *hdr;

#ifdef PC
    ffs_emu_read (  );
    base = ffs_emu_base;
#endif

    hdr = base;
    if ( !ffs_validaddr ( base ) )
        return -FFS_INV_ADDR;

    if ( strncmp ( ( unsigned char * ) &( hdr->magic ), FFS_MAGIC, 8 ) )
        return -FFS_INV_MAGIC;
    if ( hdr->compat != FFS_COMPAT )
        return -FFS_INV_COMPAT;

    ffs_base = base;
    ffs_end = ( void * ) ( ( unsigned long ) base + hdr->length );


    return 0;
}

int
ffs_format ( void *base )
{
    ffs_hdr *hdr = NULL;

#ifdef PC
    ffs_emu_read (  );
    base = ffs_emu_base;
#endif

    if ( !ffs_validaddr ( base ) )
        return -FFS_INV_ADDR;

    if ( !flash_erase ( base ) )
        return -FFS_FLASHERR;

    hdr = ( ffs_hdr * ) malloc ( sizeof ( ffs_hdr ) );
    strcpy ( ( unsigned char * ) &( hdr->magic ), FFS_MAGIC );
    hdr->version = FFS_VERSION;
    hdr->compat = FFS_COMPAT;
    hdr->length = 0x00010000;
    memset ( &( hdr->spare ), 0xFF, 6 );

    memcpy ( base, hdr, sizeof ( ffs_hdr ) );

    if ( !flash_write ( base, hdr, sizeof ( ffs_hdr ) ) )
    {
        free ( hdr );
        return -FFS_FLASHERR;
    }

    free ( hdr );
    ffs_base = base;
    ffs_end = ( void * ) ( ( unsigned long ) base + hdr->length );

    return 0;
}

void *
ffs_find_first_free ( void )
{
    ffs_fhdr *hdr = ( ffs_fhdr * ) ( ( unsigned long ) ffs_base + sizeof ( ffs_hdr ) );
//    char *buf = malloc (128);

    while ( ( unsigned long ) hdr < ( unsigned long ) ffs_end )
    {
//  sprintf ( buf, "ffs_find_first: 0x%08X length 0x%08X state 0x%08X\r\n", hdr, hdr->length, hdr->state );
//  mbus_transmit ( buf, strlen(buf) );
        if ( hdr->length == 0xFFFFFFFF )
        {
            if ( hdr->state == FFS_STATE_FREE )
                return ( void * ) hdr;
            else
                return NULL;    // its currently in use
        }
        hdr = ( ffs_fhdr * ) ( ( unsigned long ) hdr + hdr->length );
    }

    return NULL;
}

int
ffs_add_file ( unsigned char *name, unsigned long length )
{
    int len = 0;
    int hdrlen = 0;
    void *pos = NULL;
    ffs_fhdr *hdr = NULL;
    unsigned char *buf = NULL;

    if ( !name )
        return -FFS_INV_PARM;

    len = strlen ( name ) + 1;
    if ( len & 1 )
        len++;

    pos = ffs_find_first_free (  );
    if ( !pos )
        return -FFS_FSERR;

    hdrlen = sizeof ( ffs_fhdr ) + len;
    hdr = ( ffs_fhdr * ) malloc ( hdrlen );
    memset ( hdr, 0x00, hdrlen );

    if ( length )
    {
        hdr->fsize = length;
        if ( length & 1 )
            length++;
        hdr->length = hdrlen + length;
        hdr->state = FFS_STATE_ALLOCATED;
    }
    else
    {
        hdr->fsize = 0xFFFFFFFF;
        hdr->length = 0xFFFFFFFF;
        hdr->state = FFS_STATE_ASSIGNED;
    }
    memcpy ( ( void * ) ( ( unsigned long ) hdr + sizeof ( ffs_fhdr ) ), name, strlen ( name ) );

    if ( !flash_write ( pos, hdr, hdrlen ) )
    {
        free ( hdr );
        return -FFS_FLASHERR;
    }

    free ( hdr );
    return 0;
}
unsigned int
ffs_file_exists ( const char *name )
{
    if ( ffs_find_file ( name ) )
        return 1;
    else
        return 0;
}

//file count added si33
int
ffs_file_count ( unsigned char state )
{
    unsigned int skip = 0;
    int cnt = 0;
    void *ret = NULL;
    ffs_fhdr *hdr = ( ffs_fhdr * ) ( ( unsigned long ) ffs_base + sizeof ( ffs_hdr ) );

    while ( ( unsigned long ) hdr < ( unsigned long ) ffs_end )
    {

        //        if ( hdr->state == FFS_STATE_FREE )
        //            return cnt;

        ret = NULL;
        switch ( state )
        {
            case FFS_FIND_FIRST:
                if ( hdr->state != FFS_STATE_DELETED )
                    cnt++;
                break;
            case FFS_FIND_ANY:
                cnt++;
                break;
            default:
                if ( hdr->state == state )
                    cnt++;
                break;
        }
        // if ( ret && !skip-- )
        //     return ret;


        if ( hdr->length == 0xFFFFFFFF )
            return cnt;

        hdr = ( ffs_fhdr * ) ( ( unsigned long ) hdr + hdr->length );
    }

    return cnt;
}

char *
ffs_list_file_ex ( unsigned char state, int number )
{
    unsigned int skip = 0;
    int cnt = 0;
    void *ret = NULL;
    ffs_fhdr *hdr = ( ffs_fhdr * ) ( ( unsigned long ) ffs_base + sizeof ( ffs_hdr ) );

    while ( ( unsigned long ) hdr < ( unsigned long ) ffs_end )
    {

        //        if ( hdr->state == FFS_STATE_FREE )
        //           return NULL;

        ret = NULL;
        switch ( state )
        {
            case FFS_FIND_FIRST:
                if ( hdr->state != FFS_STATE_DELETED )
                {
                    if ( number == cnt + 1 )
                        return ( unsigned char * ) ( ( unsigned long ) hdr + sizeof ( ffs_fhdr ) );
                    else
                        cnt++;
                }
                break;
            case FFS_FIND_ANY:
                if ( number == cnt + 1 )
                    return ( unsigned char * ) ( ( unsigned long ) hdr + sizeof ( ffs_fhdr ) );
                else
                    cnt++;
                break;
            default:
                if ( hdr->state == state )
                    if ( number == cnt + 1 )
                        return ( unsigned char * ) ( ( unsigned long ) hdr + sizeof ( ffs_fhdr ) );
                    else
                        cnt++;
                break;
        }
        // if ( ret && !skip-- )
        //     return ret;


        if ( hdr->length == 0xFFFFFFFF )
            return NULL;

        hdr = ( ffs_fhdr * ) ( ( unsigned long ) hdr + hdr->length );
    }

    return NULL;
}

char *
ffs_list_file ( unsigned char state )
{
    unsigned int skip = 0;
    void *ret = NULL;
    ffs_fhdr *hdr = ( ffs_fhdr * ) ( ( unsigned long ) ffs_base + sizeof ( ffs_hdr ) );

    while ( ( unsigned long ) hdr < ( unsigned long ) ffs_end )
    {

        //        if ( hdr->state == FFS_STATE_FREE )
        //           return NULL;

        ret = NULL;
        switch ( state )
        {
            case FFS_FIND_FIRST:
                if ( hdr->state != FFS_STATE_DELETED )
                    if ( strlen ( ( unsigned char * ) ( ( unsigned long ) hdr + sizeof ( ffs_fhdr ) ) ) > 5 )
                        return ( unsigned char * ) ( ( unsigned long ) hdr + sizeof ( ffs_fhdr ) );
                break;
            case FFS_FIND_ANY:
                if ( strlen ( ( unsigned char * ) ( ( unsigned long ) hdr + sizeof ( ffs_fhdr ) ) ) > 5 )
                    return ( unsigned char * ) ( ( unsigned long ) hdr + sizeof ( ffs_fhdr ) );
                break;
            default:
                if ( hdr->state == state )
                    if ( strlen ( ( unsigned char * ) ( ( unsigned long ) hdr + sizeof ( ffs_fhdr ) ) ) > 5 )
                        return ( unsigned char * ) ( ( unsigned long ) hdr + sizeof ( ffs_fhdr ) );
                break;
        }
        if ( ret && !skip-- )
            return ret;


        if ( hdr->length == 0xFFFFFFFF )
            return NULL;

        hdr = ( ffs_fhdr * ) ( ( unsigned long ) hdr + hdr->length );
    }

    return NULL;
}








//END ADDED BY SPACEIMPACT
void *
ffs_find_file_ex ( const char *name, unsigned char state, unsigned int skip )
{
    void *ret = NULL;
    ffs_fhdr *hdr = ( ffs_fhdr * ) ( ( unsigned long ) ffs_base + sizeof ( ffs_hdr ) );

    while ( ( unsigned long ) hdr < ( unsigned long ) ffs_end )
    {

        if ( hdr->state == FFS_STATE_FREE )
            return NULL;

        ret = NULL;
        switch ( state )
        {
            case FFS_FIND_FIRST:
                if ( hdr->state != FFS_STATE_DELETED && !strcmp ( name, ( unsigned char * ) ( ( unsigned long ) hdr + sizeof ( ffs_fhdr ) ) ) )
                    ret = ( void * ) hdr;
                break;
            case FFS_FIND_ANY:
                if ( !strcmp ( name, ( unsigned char * ) ( ( unsigned long ) hdr + sizeof ( ffs_fhdr ) ) ) )
                    ret = ( void * ) hdr;
                break;
            default:
                if ( hdr->state == state && !strcmp ( name, ( unsigned char * ) ( ( unsigned long ) hdr + sizeof ( ffs_fhdr ) ) ) )
                    ret = ( void * ) hdr;
                break;
        }
        if ( ret && !skip-- )
            return ret;


        if ( hdr->length == 0xFFFFFFFF )
            return NULL;

        hdr = ( ffs_fhdr * ) ( ( unsigned long ) hdr + hdr->length );
    }

    return NULL;
}

void *
ffs_find_file ( const char *name )
{
    return ffs_find_file_ex ( name, FFS_FIND_FIRST, 0 );
}

unsigned int
ffs_get_size ( const char *name )
{
    int size = 0;
    unsigned int num = 0;
    ffs_fhdr *hdr = NULL;

    hdr = ( ffs_fhdr * ) ffs_find_file_ex ( name, FFS_FIND_FIRST, num );

    if ( !hdr )
        return -FFS_NOTFOUND;

    while ( hdr )
    {
//  printf ( "get_size(%s): got one with %i...\n", name, hdr->fsize) ;
        size += hdr->fsize;
        num++;
        hdr = ( ffs_fhdr * ) ffs_find_file_ex ( name, FFS_FIND_FIRST, num );
    }

//sleep ( 5 );
    return size;
}


int
ffs_extend_file ( const char *name )
{
    ffs_fhdr *hdr = ( ffs_fhdr * ) ffs_find_file_ex ( name, FFS_STATE_ALLOCATED, 0 );
    ffs_fhdr *buf = NULL;

    if ( !hdr )
        return -1;

    buf = ( ffs_fhdr * ) malloc ( sizeof ( ffs_fhdr ) );
    memcpy ( buf, hdr, sizeof ( ffs_fhdr ) );

    buf->state = FFS_STATE_EXTENDED;

    if ( !flash_write ( hdr, buf, sizeof ( ffs_fhdr ) ) )
    {
        free ( buf );
        return -FFS_FLASHERR;
    }

    free ( buf );

    return 0;
}

int
ffs_unlink ( const char *name )
{
    ffs_fhdr *hdr = ( ffs_fhdr * ) ffs_find_file ( name );
    ffs_fhdr *buf = NULL;
//    mbus_transmit ( "ffs_unlink: enter\r\n", 19 );

    if ( !hdr )
        return -1;

    buf = ( ffs_fhdr * ) malloc ( sizeof ( ffs_fhdr ) );
    memcpy ( buf, hdr, sizeof ( ffs_fhdr ) );

    buf->state = FFS_STATE_DELETED;

//    mbus_transmit ( "ffs_unlink: flash\r\n", 19 );
    if ( !flash_write ( hdr, buf, sizeof ( ffs_fhdr ) ) )
    {
        free ( buf );
        return -FFS_FLASHERR;
    }

    free ( buf );
//    mbus_transmit ( "ffs_unlink: exit \r\n", 19 );

    return 0;
}

// for an existing one
FILE *
ffs_open_file ( const char *name, const char *mode )
{
    int len = 0;
    FILE *f = NULL;
    ffs_fhdr *hdr = ( ffs_fhdr * ) ffs_find_file ( ( unsigned char * ) name );

    if ( !hdr )
        return NULL;

    f = ( FILE * ) malloc ( sizeof ( FILE ) );
    if ( !f )
        return NULL;

    len = strlen ( ( void * ) ( ( ( unsigned long ) hdr ) + sizeof ( ffs_fhdr ) ) ) + 1;
    if ( len & 1 )
        len++;
    f->addr = ( void * ) ( ( ( unsigned long ) hdr ) + sizeof ( ffs_fhdr ) + len );
    f->priv = ( void * ) hdr;
    f->fpos = 0;
    f->pos = 0;
    f->fsize = ffs_get_size ( name );
//    f->fsize = hdr->fsize;
    f->avail = hdr->fsize;
    f->mode = FS_MODE_READ;

    return f;
}


FILE *
ffs_create_file ( const char *name, const char *mode )
{
    int len = 0;
    FILE *f = NULL;
    ffs_fhdr *hdr = NULL;

    if ( ffs_add_file ( ( unsigned char * ) name, 0 ) )
        return NULL;

    // get the above created one
    hdr = ( ffs_fhdr * ) ffs_find_file_ex ( ( unsigned char * ) name, FFS_STATE_ASSIGNED, 0 );
    if ( !hdr )
        return NULL;

    f = ( FILE * ) malloc ( sizeof ( FILE ) );
    if ( !f )
        return NULL;

    // and fill in the values   
    len = strlen ( ( void * ) ( ( ( unsigned long ) hdr ) + sizeof ( ffs_fhdr ) ) ) + 1;
    if ( len & 1 )
        len++;
    f->addr = ( void * ) ( ( ( unsigned long ) hdr ) + sizeof ( ffs_fhdr ) + len );
    f->priv = ( void * ) hdr;
    f->fpos = 0;
    f->pos = 0;
    f->fsize = 0;
    f->avail = 0;
    f->mode = FS_MODE_WRITE;

    return f;
}


int
ffs_close_file ( FILE * f )
{
    int len = 0;
    ffs_fhdr *hdr = NULL;

    if ( !f || !f->addr )
        return -1;

    hdr = ( ffs_fhdr * ) malloc ( sizeof ( ffs_fhdr ) );
    if ( !hdr )
        return -1;

    memcpy ( hdr, f->priv, sizeof ( ffs_fhdr ) );

    len = strlen ( ( void * ) ( ( ( unsigned long ) f->priv ) + sizeof ( ffs_fhdr ) ) ) + 1;
    if ( len & 1 )
        len++;

    hdr->length = sizeof ( ffs_fhdr ) + f->fsize + len;
    while ( hdr->length & 3 )
        hdr->length++;
    hdr->fsize = f->fsize;
    hdr->state = FFS_STATE_ALLOCATED;

    if ( !flash_write ( f->priv, hdr, sizeof ( ffs_fhdr ) ) )
    {
        free ( hdr );
        return -FFS_FLASHERR;
    }

    free ( hdr );

    return 0;
}

int
ffs_fclose ( FILE * stream )
{
    int ret = 0;

    if ( !stream )
        return -1;

    switch ( stream->mode )
    {
        case FS_MODE_READ:
            free ( stream );
            break;
        case FS_MODE_WRITE:
            if ( ( ( ffs_fhdr * ) stream->priv )->state == FFS_STATE_ASSIGNED )
                ret = ffs_close_file ( stream );
            free ( stream );
            break;
        default:
            ret = -1;
            break;
    }
    return ret;

}


FILE *
ffs_fopen ( const char *name, const char *mode )
{
    FILE *f = NULL;

//    mbus_transmit ( "ffs_fopen: enter\r\n", 18 );
    switch ( *mode )
    {
        case 'r':
            // try to open an existing one    
            f = ffs_open_file ( name, mode );
            break;
        case 'w':
            // create a new file and delete the old
//      mbus_transmit ( "ffs_fopen: unlink\r\n", 19 );
            ffs_unlink ( name );
//      mbus_transmit ( "ffs_fopen: create\r\n", 19 );
            f = ffs_create_file ( name, mode );
            break;
        case 'a':
            // append to existing one
            if ( ffs_find_file ( name ) )
            {
                f = ffs_create_file ( name, mode );
                ffs_extend_file ( name );
            }
            else
                f = ffs_create_file ( name, mode );

            break;
        default:
            break;
    }
//    mbus_transmit ( "ffs_fopen: exit\r\n", 17 );
    return f;
}

int
ffs_getnext ( FILE * stream )
{
    int num = 0;
    unsigned long str = 0;
    unsigned long size = 0;
    unsigned char *name = NULL;
    ffs_fhdr *hdr = NULL;

    // get the name    
    name = ( void * ) ( ( ( unsigned long ) stream->priv ) + sizeof ( ffs_fhdr ) );

    // get the first file block
    hdr = ( ffs_fhdr * ) ffs_find_file ( name );
    if ( !hdr )
        return -1;

    // calculate the filename length
    str = strlen ( name ) + 1;
    if ( str & 1 )
        str++;

    size += hdr->fsize;

    // get the next block until we arrive at "read_bytes_plus_one"
    while ( hdr && size <= stream->fpos )
    {
//  printf ( "getnext: <%s> <%i> <%i>\n", name, num, hdr->fsize );
        num++;
        hdr = ( ffs_fhdr * ) ffs_find_file_ex ( name, FFS_FIND_FIRST, num );
        size += hdr->fsize;
    }
//    sleep ( 5 );
    if ( hdr )
    {
//  printf ( "getnext: <FOUND>\n" );
        stream->addr = ( void * ) ( ( ( unsigned long ) hdr ) + sizeof ( ffs_fhdr ) + str );
        stream->priv = ( void * ) hdr;
        stream->avail = hdr->fsize;
        stream->pos = 0;
        return 0;
    }

    return -1;
}

int
ffs_feof ( FILE * stream )
{
    if ( !stream )
        return 1;

    if ( stream->fpos == stream->fsize )
        return 1;

    return 0;
}

unsigned long
ffs_fread ( void *ptr, unsigned long size, unsigned long nmemb, FILE * stream )
{
    unsigned long len = 0;
    unsigned long bytes = 0;

    if ( !ptr || !size || !nmemb || !stream || !stream->addr )
        return 0;

    // TODO: care about size
    len = nmemb * size;

  fread_again:
    if ( len > ( stream->fsize - stream->fpos ) )
        len = stream->fsize - stream->fpos;

    if ( len > stream->avail )
        len = stream->avail;

    memcpy ( ptr, ( void * ) ( ( unsigned long ) stream->addr + stream->pos ), len );

    stream->pos += len;
    stream->fpos += len;
    stream->avail -= len;

    bytes += len;

    if ( !stream->avail && stream->fpos != stream->fsize )
    {
        ffs_getnext ( stream );
        // advance the destination
        ptr = ( void * ) ( ( unsigned long ) ptr + len );
        // next time read the maximum allowed minus the already read ones
        len = ( nmemb * size ) - len;
        goto fread_again;
    }

    return len;
}

unsigned long
ffs_fwrite ( void *ptr, unsigned long size, unsigned long nmemb, FILE * stream )
{
    unsigned char *buf = NULL;
    unsigned long len = 0;
    unsigned long bytes = 0;
    void *pos = NULL;

//    mbus_transmit ( "ffs_write: enter\n", 17 );
    if ( !ptr || !size || !nmemb || !stream || !stream->addr )
        return 0;

    if ( stream->mode != FS_MODE_WRITE )
        return 0;

    len = nmemb * size;

/*
    // already wrote too many bytes? (if in fixed size mode somewhen)
    if ( stream->fsize && (stream->fpos + stream->pos > stream->fsize) )
	return 0;

    // would we write more that is available?
    if ( stream->fsize && (stream->fpos + stream->pos + len > stream->fsize) )
	len = stream->fsize - (stream->fpos + stream->pos);
*/

    // get a buffer of the data's size and word align its size
    bytes = len;
    if ( bytes & 1 )
        bytes++;

    buf = ( unsigned char * ) malloc ( bytes );
    if ( !buf )
        return 0;

    pos = ( void * ) ( ( unsigned long ) stream->addr + stream->fpos + stream->pos );

    // clear the block we write so we dont have crap behind (1 byte)
    memset ( buf, 0xFF, bytes );
    memcpy ( buf, ptr, len );

//    mbus_transmit ( "ffs_write: flash\n", 17 );
    if ( !flash_write ( pos, buf, bytes ) )
    {
        free ( buf );
        return -1;
    }

    free ( buf );
    stream->pos += len;
    stream->fsize += len;
    stream->avail += len;
//    mbus_transmit ( "ffs_write: exit\n", 16 );

    return len;
}
