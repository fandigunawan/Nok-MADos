

.GLOBAL     _start



_start:
.ALIGN 




.ORG  0x00000000

.CODE 16
    bl      int_disable
    adr     r0, bootloader
    bx      r0
.CODE 32
bootloader:
    ldr     r0, .MAGIC
    mov     r1, #0x00040000
    str     r0, [r1]
    
    
    mov     r1, #0x00020000
    mov     r0, #0x00
    strb    r0, [r1, #0x70]
    mov     r0, #0x02
    strb    r0, [r1, #0x71]
    mov     r0, #0xA0
    strb    r0, [r1, #0x72]
    mov     r0, #0x63
    strb    r0, [r1, #0x73]
    mov     r0, #0xFF
    strb    r0, [r1, #0xB0]
    mov     r0, #0xFD
    strb    r0, [r1, #0xB1]
    mov     r0, #0x5F
    strb    r0, [r1, #0xB2]
    mov     r0, #0x00
    strb    r0, [r1, #0xB3]
    mov     r0, #0x60
    strb    r0, [r1, #0xAF]
    mov     r0, #0x04
    strb    r0, [r1, #0x6F]
    mov     r0, #0x00
    strb    r0, [r1, #0xEF]

    mrs     r2, CPSR
    bic     r2, r2, #0x1F
    ldr     r1, .STACK
    add     sp, r1, #0x10
    orr     r0, r2, #0x17
    msr     CPSR_cf, r0
    add     sp, r1, #0x10
    orr     r0, r2, #0x1B
    msr     CPSR_cf, r0
    add     sp, r1, #0x10
    orr     r0, r2, #0x12
    msr     CPSR_cf, r0
    mov     sp, r1
    orr     r0, r2, #0x11
    msr     CPSR_cf, r0
    
    add     sp, r1, #0x170
    orr     r0, r2, #0x1F
    msr     CPSR_cf, r0
    mov     sp, r1
    
    adr     r0, .INTS
    mov     r1, #0x00000000
    ldmia   r0, {r2-r9}
    stmia   r1, {r2-r9}

    mov     r0, #0x00020000
    mov     r1, #0xFF
    strb    r1, [r0, #0x0A]
    strb    r1, [r0, #0x0B]
    
    mrs     r0, CPSR
    bic     r0, r0, #0xC0
    msr     CPSR_cf, r0

    ldr     r0, =_sdata
    ldr     r1, =__data_start
    ldr     r3, =_edata
    
.data_copy:
    cmp     r1, r3
    ldrcc   r2, [r0]
    strcc   r2, [r1]
    add     r0, r0, #0x04
    add     r1, r1, #0x04
    bcc     .data_copy
    
    adr     r0, start_vector
    bx      r0

.MAGIC:
    .word 0x590F6520


.STACK:
    .word 0x0011D000
    
.ORG       0x00000160
.INTS:
    b       0x00680460
    b       0x00680460
    b       0x00680460
    b       0x00680460
    b       0x00680460
    b       0x00680360
    b       0x00680360
    b       0x00680360
    
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.ORG 0x00000180

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@   interrupt handler ;)      @@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.CODE 32
inthandler:
    stmfd   SP, { R0-R14 }^
    sub     SP, SP, #0x3C
@@
@@ disable ints
@@  
  
@    ldr     R0, .LOCK
@    ldrb    R1, [R0, #0x00]
@    cmp     R1, #0x00
@    bne     int_critical
@    mov     R1, #0x01
@    strb    R1, [R0, #0x00]
    
    mov     R0, #0x00020000
    mov     R1, #0x0C
    strb    R1, [R0, #0x0C]
    
    mrs     r0, CPSR
    orr     r0, r0, #0xC0
    msr     CPSR_cf, r0

    mrs     R7, SPSR
    
    adr     R0,  int_vector+1
    bx      R0
    
.CODE 16
int_vector:
    push    { LR }
@
@ if previous state was not user, return now
@
    mov     R0, R7
    mov     R1, #0x1F
    and     R0, R0, R1
    cmp     R0, #0x10
    bne     int_ret
    
    bl      sched_now
    cmp     R0, #0x00
    bne     int_ret      @  bne!!!
    
@@    
@@ time for a thread switch
@@
@@
@@  first pop the old PC, saved in LR and save then CPSR
@@
    pop     { R1 }
    mov     R0, #0x0F
    bl      sched_save

    mov     R1, R7
    mov     R0, #0x10
    bl      sched_save

@@
@@ save other registers
@@
    mov     R4, #0x00
    
int_save:
    cmp     R4, #0x0F
    beq     int_endsave
        
    pop     { R1 }
    mov     R0, R4
    bl      sched_save
    add     R4, R4, #0x01
    b       int_save
    
int_endsave:
@@
@@ we saved now the old registers.... lets switch thread now
@@

    bl      sched_next
@@
@@ and restore the next thread's registers
@@
    mov     R4, #0x0E
    
int_restore:
    cmp     R4, #0x00
    beq     int_endrestore
    
    mov     R0, R4
    bl      sched_get
    push    { R0 }
    sub     R4, R4, #0x01
    b       int_restore

int_endrestore:
    mov     R0, #0x00
    bl      sched_get
    push    { R0 }
@@
@@ get thread's entrypoint and save it
@@    
    mov     R0, #0x0F
    bl      sched_get
    push    { R0 }
    
    mov     R0, #0x10
    bl      sched_get
    mov     R7, R0

int_ret:
    bl      int_handler
    pop     { R0 }
    mov     LR, R0
    adr     R0, int_end
    bx      R0

.CODE 32
int_end:

    ldr     R0, .LOCK
    mov     R1, #0x00
    strb    R1, [R0, #0x00]
    msr     SPSR, R7
    mov     R0, #0x00020000
    mov     R1, #0x05
    strb    R1, [R0, #0x0C]
int_critical:
    ldmfd   SP, { R0-R14 }^
    mov     R0, R0
    add     SP, SP, #0x3C
    subs    PC, LR, #4
    
@critical:
@    stmfd   SP!, { LR }    
@    bl      sched_critical
@    ldmfd   SP!, { LR }    
@    b       int_critical
    
    
.LOCK:
    .word 0x00100030


.ORG 0x00000280

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@   interrupt handler ;)      @@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.CODE 32
    adr     r0, critical + 1
    bx      r0
    
.CODE 16
critical:
    bl      sched_critical

.CODE 32
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@ Clear memory routine        @@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ r0 address
@ r2 size
.ALIGN 4
@ lazy, cocky, dead
clearmem:
    mov     r3, #0
.clearmemloop:
    strb    r3, [r0], #1
    subs    r2, r2, #1
    bne     .clearmemloop
    mov     pc, lr
    
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@ our system startup routine  @@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.CODE 32

start_vector:
@ Data initialisation
@ clear .bss
    ldr     r0, =__bss_start__
    ldr     r2, =__bss_end__
    sub     r2, r2, r0
    bl      clearmem
    
    mrs     r2, CPSR
    bic     r2, r2, #0x1F
    ldr     r1, .IRQSTACK
    orr     r0, r2, #0x12
    msr     CPSR_cf, r0
    mov     lr, #0x00
    mov     sp, r1
    orr     r0, r2, #0x11
    msr     CPSR_cf, r0
    mov     lr, #0x00
    add     sp, r1, #0x170
    orr     r0, r2, #0x10
    msr     CPSR_cf, r0
    
    adr     r0, start_vector2 + 1
    bx      r0
    
.CODE 16
start_vector2:

    bl    main


mainhang: 
    b mainhang
    
.IRQSTACK:
    .word 0x0011E000
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


.code 16
.thumb_func
.global _interwork_call_via_r0
_interwork_call_via_r0:
bx      pc
nop

.code 32
tst     r0, #1
stmeqdb r13!, {lr}
adreq   lr, _arm_return
bx      r0

.code 16
.thumb_func
.global _interwork_call_via_r1
_interwork_call_via_r1:
bx      pc
nop

.code 32
tst     r1, #1
stmeqdb r13!, {lr}
adreq   lr, _arm_return
bx      r1

.code 16
.thumb_func
.global _interwork_call_via_r2
_interwork_call_via_r2:
bx      pc
nop

.code 32
tst     r2, #1
stmeqdb r13!, {lr}
adreq   lr, _arm_return
bx      r2

.code 16
.thumb_func
.global _interwork_call_via_r3
_interwork_call_via_r3:
bx      pc
nop

.code 32
tst     r3, #1
stmeqdb r13!, {lr}
adreq   lr, _arm_return
bx      r3

.code 32
_arm_return:
ldmia   r13!, {r12}
bx      r12
.code 16


@ Memory ranges
.global _dsp
_dsp = 0x10000
.global _io
_io = 0x20000
.global _dspif
_dspif = 0x30000
.global _mcuif
_mcuif = 0x40000



