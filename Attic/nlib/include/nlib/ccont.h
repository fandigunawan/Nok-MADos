#ifndef WMX_CCONT

#define WMX_CCONT

#define CCONT_READCACHE  0x8000
#define CCONT_WRITECACHE 0x8000

void IO_CContWrite ( uint reg, uint value );
int IO_CContRead ( uint reg );
uint IO_CContADRead ( int n );
void IO_CContInitialize (  );

#endif
