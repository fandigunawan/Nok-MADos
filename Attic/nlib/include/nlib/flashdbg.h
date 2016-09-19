#ifndef WMX_FLASHER
#define WMX_FLASHER

uint IO_flashdbgReceiveByte (  );
void IO_flashdbgSendByte ( uint dat );
void IO_flashdbgSetSDA ( int state );
void IO_flashdbgSendPacket ( uint8 * packet, uint length );
void IO_flashdbg ( uint code, uint8 * param, uint length );

#endif
