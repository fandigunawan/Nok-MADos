#ifndef WMX_INTERRUPT
#define WMX_INTERRUPT

typedef void ( *inthandler ) (  );  /* Interrupt handler type */

#define FIQ_COUNT	9
#define IRQ_COUNT	9

/* Constants for "type" */
#define FIQ	0x00
#define IRQ	0x40

/* Interrupt IDs */
#define IRQ_KEYBOARD	(IRQ|0)
#define IRQ_CCONTINT	(IRQ|2)
#define IRQ_SLEEP	(IRQ|3)
#define IRQ_DSP		(IRQ|4)

#define FIQ_MDIRCV	(FIQ|0)
#define FIQ_MDISND	(FIQ|1)
#define FIQ_MBUSRX	(FIQ|2)
#define FIQ_MBUSTIM	(FIQ|3)     /* triggers 423.1 times per second */
#define FIQ_PTIMER	(FIQ|4)
#define FIQ_SIMCARDDETX	(FIQ|7)

void IO_globalInterruptEnable ( int mode );
void IO_setInterruptHandler ( uint num, inthandler handler );
void IO_setInterruptEnable ( uint num, int state );

#endif
