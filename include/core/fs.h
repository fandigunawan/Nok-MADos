
typedef struct
{
    unsigned char magic[8];
    unsigned long length;
    unsigned char compat;
    unsigned char version;
    unsigned char fsdata[6];
}
fs_hdr;

typedef struct
{
    void *addr;                 // the address to read from
    void *priv;                 // the FS's private data
    unsigned long fsize;        // the file's size
    unsigned long fpos;         // the file's pos of the block at addr
    unsigned long avail;        // how many bytes are available at addr
    unsigned long pos;          // the actual pos at addr
    unsigned long mode;         // access mode 
//  int (*read_func)
}
FILE;

#define FS_MODE_READ  0
#define FS_MODE_WRITE 1
#define FS_BASE 0x00300000


int fs_check ( void *base );
int fs_unlink ( const char *name );
int fs_format ( void *base );
int fs_fclose ( FILE * stream );
FILE *fs_fopen ( const char *name, const char *mode );
unsigned long fs_fwrite ( void *ptr, unsigned long size, unsigned long nmemb, FILE * stream );
unsigned long fs_fread ( void *ptr, unsigned long size, unsigned long nmemb, FILE * stream );
int fs_countfiles (  );
char *fs_listfile ( int number );
int fs_exists ( const char *name );
