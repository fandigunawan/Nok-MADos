/**
 * Nokia DCT3 I/O definitions
 * wumpus <gnufnork@hetdigitalegat.nl> 2003
 *    x   x     
 *   xx x xx   
 *  XxxxxxxxX   
 *   x\xx  x    
 *    xxxx     
 *   _ xxxx
 *  Xxxxx\xxX
 *   xx x xx
 *    x   x
 */
#ifndef BS_NOKIA_H_INCLUDED
#define BS_NOKIA_H_INCLUDED

/* Ports */

#define IO_ASIC_ID      0x00
#define IO_DSP_RESET	 0x02
#define DSP_ENABLE		0x01
#define IO_FIQ_ACTIVE	 0x08
#define IO_IRQ_ACTIVE	 0x09
#define IO_FIQ_MASK	 0x0A
#define IO_IRQ_MASK	 0x0B
#define IO_INT_CTRL	 0x0C
#define IO_CLOCKS	 0x0D
#define CLOCK_GENSIO	 0x04   /* Generic serial I/O */
#define CLOCK_PROG	 0x08       /* ?? */
#define IO_TIMESTAMP	 0x10   /* halfword */
#define IO_WATCHDOG	 0x12       /* halfword */
#define IO_BUZCTRL	 0x15
#define BUZCTRL_VIBRATOR	0x10
#define BUZCTRL_BUZZER	0x20
#define IO_FIQ8	 0x16           /* ? */
#define IO_MBUS_CTRL    0x18
#define IO_MBUS_STATUS  0x19
#define IO_MBUS_BYTE    0x1A
#define IO_VIBRATOR	 0x1B
#define IO_BUZFREQ	 0x1C       /* halfword */
#define IO_BUZVOL	 0x1E
#define IO_GENIO_D	 0x20
#define IO_GENIO_RW	 0x24
#define IO_CCONT_WRITE  0x2C
#define IO_GENSIO_CTRL	 0x2D
#define IO_LCD_DATA	 0x2E
#define IO_GENPIO 	 0x32
#define LCD_RESET		0x20
#define IO_CTRL3 	 0x33
#define CTRL3_DISPLAYLEDS	0x02
#define IO_CCONT_READ   0x6C
#define IO_LCD_STATUS	 0x6D
#define IO_LCD_CMD	 0x6E
/* Keyboard */
#define IO_KEY_AAA	 0x68
#define IO_KEY_BBB	 0x69
#define IO_KEY_CCC	 0x6A       /* columns; 0 = enabled; 1 = always disabled */
#define IO_KEY_IRQC	 0x6B       /* columns; 0 = cause IRQ0, 1 = no irq */
#define IO_KEY_ROW_CLR  0x28    /* rows; 0 = enabled, 1 = disabled */
#define IO_KEY_COL_RD	 0x2A   /* columns; 0 = pressed, 1 = no signal */
#define IO_KEY_ROW_SET	 0xA8   /* rows; 0 = tristate, 1 = pass */
#define IO_KEY_EEE	 0xA9
#define IO_KEY_FFF	 0xAB

/* CCont */
#define CCONT_REGS	0x20

/* Danger -- Memory Mapped I/O ahead */
extern volatile uint16 _dsp[];
extern volatile uint8 _io[];
#define ioreadw(addr) (*(volatile unsigned short *) &_io[addr])
#define iowritew(addr, value) ((*(volatile unsigned short *) &_io[addr]) = (value))
extern volatile uint16 _dspif[];
extern volatile uint8 _mcuif[];

/* Generic functions */
void IO_initialize (  );
void IO_globalInterruptEnable ( int mode );
void IO_setBit ( uint reg, uint bit, uint mode );
void usleep ( uint micros );

#endif
