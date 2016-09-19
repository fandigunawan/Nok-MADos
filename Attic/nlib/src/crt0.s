@ | RTOS-DCT3 initialisation             |
@ | wumpus <wumpus@goliath.darktech.org> |

.equ IO_FIQ_ACTIVE, 0x08
.equ IO_IRQ_ACTIVE, 0x09
.equ IO_FIQ_MASK,   0x0A
.equ IO_IRQ_MASK,   0x0B
.equ IO_INT_CTRL,   0x0C


    .TEXT

    .GLOBAL     _start
_start:

        .ALIGN
        .CODE 32
@ start address
        .word start_vector

@ exception vector table
    	.word 0			@ Undefined instruction
    	.word 0			@ Software interrupt
    	.word 0			@ Abort (prefetch)
    	.word 0			@ Abort (data)
    	.word 0			@ Reserved
    	b service_irq		@ IRQ
    	b service_fiq		@ FIQ

start_vector:
@ system initialisation
@ pre-init (memory map?)
	ldr     r0, _memmapper    @ reverse word
	mov     r1, #0x40000
	str     r0, [r1]

@ stack setup
	adr	r3, _stacksizes		@ r3 = _stacksizes
	ldr	r1, _stackbase		@ r1 = [_stackbase]
	mrs     r2, CPSR
	bic     r2, r2, #0x1F		@ CPSR minus M bits
@ loop
	b .beginstackloop
.stackloop:
	orr     r0, r2, r0		@ or mode and CPSR base
	msr     CPSR_cf, r0		@ set CPSR
	ldrh	r0, [r3,#2]		@ get size
	add	r1, r1, r0		@ add size to stack base
	mov     SP, r1
	add	r3, r3, #4		@ next record
.beginstackloop:
	ldrh	r0, [r3,#0]		@ r0 = mode
	cmp	r0, #0
	bne	.stackloop		@ if not zero, loop

@ Go to System mode
	orr     r0, r2, #0x1F		@ M = 11111 System
	msr     CPSR_cf, r0

@ Set up vectors
@	ldr     r0, =vector_table
@	mov     r1, #0
@	ldmia   r0, {r2-r9}
@	stmia   r1, {r2-r9}

@ Mask all FIQ and IRQ lines
	mov     r0, #0x20000
	mov     r1, #0xFF
	strb    r1, [r0,#0xA]
	strb    r1, [r0,#0xB]

@ Enable FIQ/IRQ ARM-wise
	mrs     r0, CPSR
	bic     r0, r0, #0xc0
	msr     CPSR_cf, r0

@ clear .bss
	ldr     a1, .LC1
	ldr     a3, .LC2
	sub     a3, a3, a1
	bl      clearmem

	ldr     r0, _mainptr
	bx      r0

.CODE 32


.ALIGN 4
@ slow, lazy
clearmem:
    	mov     r3, #0
.clearmemloop:
    	strb    r3, [r0], #1
   	subs    r2, r2, #1
    	bne     .clearmemloop
    	mov     pc, lr

    	.align 0
.LC1:	.word   __bss_start__
.LC2:	.word   __bss_end__

@ FIQ handler
service_fiq:
	stmed 	sp!, { r0-r7 }	@ r8-r15 are saved by system
	stmed	sp!, { lr }

	mov 	r7, #0x20000
@	adr     r0, [pc+9]
	bx      r0
.CODE 16
	mov	r2, #IO_FIQ_ACTIVE
	ldrb	r0, [r7,r2]
@ No active irq	? error
	cmp	r0, #0
	beq	_fiqerror
@ Scan which bit is set
	mov	r1, #0
_fiqscanloop:
	add	r1, #1
	lsr	r0, r0, #1
	bcc _fiqscanloop
	sub	r6, r1, #1		@ r6 = IRQ #
@ Last interrupt, for debugging purposes
	ldr	r0, =_last_int
	strb	r6, [r0]
@ Mark as handled
	mov	r0, #1
	lsl	r0, r0, r6
	@mov	r2, #IO_IRQ_ACTIVE
	strb	r0, [r7,r2]
@ Call handler
	ldr	r0, _fiqh		@ _irq_handlers
	lsl	r1, r6, #2
	ldr	r0, [r0,r1]
	cmp	r0, #0
	beq	_nofiqhandler		@ if it is not set, discard
	mov	r1, pc
	add	r1, r1, #5
	mov	lr, r1
	bx	r0
_nofiqhandler:
_fiqerror:
.ALIGN 4
	mov     r0, pc
	bx      r0
.CODE 32
	ldmed	sp!, { lr }		@ Back to 32 bit and return
	ldmed 	sp!, { r0-r7 }
	subs	pc, lr, #4
_fiqh:	.word _fiq_handlers

@ IRQ handler
service_irq:
	stmed 	sp!, { r0-r12 }
	stmed	sp!, { lr }

	mov 	r7, #0x20000
@	adr     r0, [pc+9]
	bx      r0
.CODE 16
	mov	r2, #IO_IRQ_ACTIVE
	ldrb	r0, [r7,r2]
@ No active irq	? error
	cmp	r0, #0
	beq	_irqerror
@ Scan which bit is set
	mov	r1, #0
_irqscanloop:
	add	r1, #1
	lsr	r0, r0, #1
	bcc _irqscanloop
	sub	r6, r1, #1		@ r6 = IRQ #
@ Mark last interrupt for debugging purposes
	ldr	r0, =_last_int
	mov	r1, #0x40		@ 0x40 -- IRQ
	orr	r1, r6
	strb	r1, [r0]
@ Mark as handled
	mov	r0, #1
	lsl	r0, r0, r6
	@mov	r2, #IO_IRQ_ACTIVE
	strb	r0, [r7,r2]
@ Call handler
	ldr	r0, _irqh		@ _irq_handlers
	lsl	r1, r6, #2
	ldr	r0, [r0,r1]
	cmp	r0, #0
	beq	_noirqhandler		@ if it is not set, discard
	@mov	lr, pc -- WRONG switched system into arm state
	mov	r1, pc
	add	r1, r1, #5
	mov	lr, r1
	bx	r0
_noirqhandler:
_irqerror:
.ALIGN 4
	mov     r0, pc
	bx      r0
.CODE 32
	ldmed	sp!, { lr }		@ Back to 32 bit and return
	ldmed 	sp!, { r0-r12 }
	subs	pc, lr, #4
_irqh:	.word _irq_handlers

.THUMB_FUNC
.global flashjump
flashjump:
	ldr	r0, .flash
	bx 	r0 @test
.flash:     .word 0x200149

@ Memory ranges
.global _dsp
_dsp = 0x10000
.global _io
_io = 0x20000
.global _dspif
_dspif = 0x30000
.global _mcuif
_mcuif = 0x40000

@ main function reference
_mainptr: .word main

@ written to 0x4000
_memmapper: .word 0x590F6520

@ stack top
_stackbase: .word 0x11E000

@ Stack sizes (mode, size in bytes)
_stacksizes:
.short 0x11, 0x100		@ FIQ
.short 0x12, 0x100		@ IRQ
.short 0x13, 0x10		@ Supervisor mode
.short 0x17, 0x10		@ Abort
.short 0x1B, 0x10		@ Undefined
.short 0x1F, 0x1000		@ System
.short 0x00


    .END


