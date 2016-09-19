#ifndef WMX_LCD
#define WMX_LCD

void IO_LCDInitialize (  );
void IO_LCDSendCmd ( uint cmd );
void IO_LCDSendData ( uint dat );
void IO_LCDSetContrast ( int vop );

#endif
