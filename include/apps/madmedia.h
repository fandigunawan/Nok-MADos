
typedef struct
{
    char ext[5];                // extention
    char discription[50];       // discription length 50
    unsigned long type;         // types
    char shortname[14];         // short name
}
file_type_t;




#define FILE_TYPE_UNKNOWN 0x0
#define FILE_TYPE_TEST 0x1
#define FILE_TYPE_SYSTEM 0x2
#define FILE_TYPE_IMAGE 0x3
#define FILE_TYPE_SOUND 0x4
#define FILE_TYPE_TEXT 0x5
#define FILE_TYPE_ALL 0xFF



extern const file_type_t file_types[];


int mediamain (  );
