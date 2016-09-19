
#define FFS_VERSION 1
#define FFS_COMPAT  1

#define FFS_ERROR      1
#define FFS_INV_MAGIC  2
#define FFS_INV_COMPAT 3
#define FFS_FSERR      4
#define FFS_FLASHERR   5
#define FFS_INV_PARM   6
#define FFS_NOTFOUND   7
#define FFS_INV_ADDR   8

#define FFS_MAGIC      "MADosFFS"


#define FFS_STATE_FREE       0xFF
#define FFS_STATE_ASSIGNED   0xFE
#define FFS_STATE_ALLOCATED  0xFC
#define FFS_STATE_EXTENDED   0xF8
#define FFS_STATE_DELETED    0xF0

#define FFS_FIND_ANY         0x01
#define FFS_FIND_FIRST       0x00




typedef struct
{
    unsigned char magic[8];
    unsigned long length;
    unsigned char compat;
    unsigned char version;
    unsigned char spare[6];
}
ffs_hdr;

typedef struct
{
    unsigned long length;
    unsigned long fsize;
    unsigned char state;
    unsigned char padding[3];
}
ffs_fhdr;


int ffs_validaddr ( void *base );
int ffs_check ( void *base );
int ffs_format ( void *base );
void *ffs_find_first_free ( void );
int ffs_add_file ( unsigned char *name, unsigned long length );
void *ffs_find_file ( const char *name );
unsigned int ffs_file_exists ( const char *name );
int ffs_unlink ( const char *name );
unsigned int ffs_get_size ( const char *name );
FILE *ffs_open_file ( const char *name, const char *mode );
int ffs_close_file ( FILE * f );
int ffs_fclose ( FILE * stream );
FILE *ffs_fopen ( const char *name, const char *mode );
unsigned long ffs_fwrite ( void *ptr, unsigned long size, unsigned long nmemb, FILE * stream );
unsigned long ffs_fread ( void *ptr, unsigned long size, unsigned long nmemb, FILE * stream );
char *ffs_list_file ( unsigned char state );
char *ffs_list_file_ex ( unsigned char state, int number );
int ffs_file_count ( unsigned char state );
