
#include <core/fs.h>
#include <core/ffs.h>

#define _CONFIG_FFS_

#ifdef _CONFIG_FFS_
int
fs_check ( void *base )
{
    return ffs_check ( base );
}

int
fs_unlink ( const char *name )
{
    return ffs_unlink ( name );
}

int
fs_exists ( const char *name )
{
    return ffs_file_exists ( name );
}

int
fs_getsize ( const char *name )
{
    return ffs_get_size ( name );
}

char *
fs_listfile ( int number )
{
    return ( void * ) ffs_list_file_ex ( FFS_FIND_FIRST, number );
}

int
fs_countfiles (  )
{
    return ffs_file_count ( FFS_FIND_FIRST );
}

int
fs_format ( void *base )
{
    return ffs_format ( base );
}

int
fs_fclose ( FILE * stream )
{
    return ffs_fclose ( stream );
}

FILE *
fs_fopen ( const char *name, const char *mode )
{
    return ffs_fopen ( name, mode );
}

unsigned long
fs_fwrite ( void *ptr, unsigned long size, unsigned long nmemb, FILE * stream )
{
    return ffs_fwrite ( ptr, size, nmemb, stream );
}

unsigned long
fs_fread ( void *ptr, unsigned long size, unsigned long nmemb, FILE * stream )
{
    return ffs_fread ( ptr, size, nmemb, stream );
}
#else
int
fs_check ( void *base )
{
    return 0;
}

int
fs_unlink ( const char *name )
{
    return 0;
}

int
fs_format ( void *base )
{
    return 0;
}

int
fs_fclose ( FILE * stream )
{
    return 0;
}

FILE *
fs_fopen ( const char *name, const char *mode )
{
    return NULL;
}

unsigned long
fs_fwrite ( void *ptr, unsigned long size, unsigned long nmemb, FILE * stream )
{
    return 0;
}

unsigned long
fs_fread ( void *ptr, unsigned long size, unsigned long nmemb, FILE * stream )
{
    return 0;
}

int
fs_exists ( const char *name )
{
    return 0;
}

int
fs_getsize ( const char *name )
{
    return 0;
}

char *
fs_listfile ( int number )
{
    return 0;
}

int
fs_countfiles (  )
{
    return 0;
}
#endif
