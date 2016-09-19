/**
 * Interrupt functions
 * wumpus <blacksphere@goliath.darktech.org> 2003
 */
#include <nlib/typedef.h>
#include <nlib/nokio.h>
#include <nlib/interrupt.h>

/**
 * Interrupt handlers (refered to by crt0.s)
 */
inthandler _irq_handlers[IRQ_COUNT];
inthandler _fiq_handlers[FIQ_COUNT];

uint8 _last_int;
/* TODO: IRQ and FIQ 8 */

/**
 * Set IRQ/FIQ mode
 * mode=0 disable, mode!=0 enable
 */
void
IO_globalInterruptEnable ( int mode )
{
    static int icount = -1;
    if ( !mode )
    {
        /*
         * disable 
         */
        _io[IO_INT_CTRL] = 0xA;
        icount--;
    }
    else
    {
        /*
         * enable 
         */
        icount++;
        if ( icount == 0 )
            _io[IO_INT_CTRL] = 0x5;
    }
}

/**
 * Set the handler routine for an interrupt of a certain type.
 *
 * @param num     Interrupt # (FIQ_*, IRQ_*)
 * @param handler Handler address
 */
void
IO_setInterruptHandler ( uint num, inthandler handler )
{
    int type = num & ~0x3F;     /* decode type */
    num = num & 0x3F;

    switch ( type )
    {
        case FIQ:
            _fiq_handlers[num] = handler;
            break;
        case IRQ:
            _irq_handlers[num] = handler;
            break;
    }
}

/**
 * Enable or disable an interrupt.
 *
 * @param num    Interrupt # (FIQ_*, IRQ_*)
 * @param state  0 disable, 1 enable
 */
void
IO_setInterruptEnable ( uint num, int state )
{
    int type = num & ~0x3F;     /* decode type */
    num = num & 0x3F;

    num = 1 << num;             /* bit number */
    state = !state;             /* mask 0 = enabled */
    switch ( type )
    {
        case FIQ:
            IO_setBit ( IO_FIQ_ACTIVE, num, 1 );    /* clear pending */
            IO_setBit ( IO_FIQ_MASK, num, state );  /* mask/unmask */
            break;
        case IRQ:
            IO_setBit ( IO_IRQ_ACTIVE, num, 1 );    /* clear pending */
            IO_setBit ( IO_IRQ_MASK, num, state );  /* mask/unmask */
            break;
    }
}
