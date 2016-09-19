                .CODE 32
@@;--------------------------------------------------------------------
                .text
bad_int:        b       bad_int
@;--------------------------------------------------------------------
                .CODE 32
                .global delay
                .global delay_1
                .global delay_2
                .global delay_3
                .global delay_4
                .global delay_5
                .global delay_6
                .global delay_7
                .global delay_8
                .global delay_9
                .global delay_10
                .global delay_11
                .global delay_12
                .global delay_13
                .global delay_14
                .global delay_15
                .global delay_16
                .global delay_17
                .global delay_18
                .global delay_19
                .global delay_20
                .global delay_21
                .global delay_22
                .global delay_23
                .global delay_24
@;                 .global delay_25
@;                 .global delay_26
@;                 .global delay_27
@;                 .global delay_28
@;                 .global delay_29
@;                 .global delay_30

@;--------------------------------------------------------------------
delay_24:      stmfd   sp!,  {V1, V2, V3, LR}      @; 24 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                b       delay_end
@@;--------------------------------------------------------------------
delay_23:      stmfd   sp!,  {V1, V2, V3, LR}      @; 23 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x040000
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_22:      stmfd   sp!,  {V1, V2, V3, LR}      @; 22 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x0400
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_21:       stmfd   sp!,  {V1, V2, V3, LR}      @; 21 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_20:      stmfd   sp!,  {V1, V2, V3, LR}      @; 20 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_19:      stmfd   sp!,  {V1, V2, V3, LR}      @; 19 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x040000
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_18:      stmfd   sp!,  {V1, V2, V3, LR}      @; 18 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x0400
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_17:       stmfd   sp!,  {V1, V2, V3, LR}      @; 17 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_16:      stmfd   sp!,  {V1, V2, V3, LR}      @; 16 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_15:      stmfd   sp!,  {V1, V2, V3, LR}      @; 15 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x040000
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_14:      stmfd   sp!,  {V1, V2, V3, LR}      @; 14 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x0400
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_13:       stmfd   sp!,  {V1, V2, V3, LR}      @; 13 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_12:      stmfd   sp!,  {V1, V2, V3, LR}      @; 12 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_11:      stmfd   sp!,  {V1, V2, V3, LR}      @; 11 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x040000
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_10:      stmfd   sp!,  {V1, V2, V3, LR}      @; 10 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x0400
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_9:       stmfd   sp!,  {V1, V2, V3, LR}      @; 9 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_8:       stmfd   sp!,  {V1, V2, V3, LR}      @; 8 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_7:       stmfd   sp!,  {V1, V2, V3, LR}      @; 7 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x040000
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_6:       stmfd   sp!,  {V1, V2, V3, LR}      @; 6 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x0400
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_5:       stmfd   sp!,  {V1, V2, V3, LR}      @; 5 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                mov     V3, #0x04
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_4:       stmfd   sp!,  {V1, V2, V3, LR}      @; 4 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04000000
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_3:       stmfd   sp!,  {V1, V2, V3, LR}      @; 3 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x040000
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_2:       stmfd   sp!,  {V1, V2, V3, LR}      @; 2 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x0400
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay_1:       stmfd   sp!,  {V1, V2, V3, LR}      @; 1 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mul     V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
delay:         stmfd   sp!,  {V1, V2, V3, LR}      @; 0 I
                eors    V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                mov     V3, #0x04
                mulne   V2, V3, V3
                b       delay_end
@;--------------------------------------------------------------------
                mov     V3, #0x04                   @; eliminate prefetch
                mov     V3, #0x04
                mov     V3, #0x04
                mov     V3, #0x04
@;--------------------------------------------------------------------
delay_end:
                add     V1, pc, #1
                bx      V1
                .CODE 16
$del_loop:      sub     A1, A1, #1
                bne     $del_loop
                bx      pc
                nop
                .CODE 32
                ldmfd   sp!,  {V1, V2, V3, PC}
@;--------------------------------------------------------------------
                .end


