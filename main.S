  .file "main.S"

#include <msp430g2553.h>


#define PC r0
#define SP r1
#define SR r2


  .section ".rodata","a"
screendata:
  .byte   0x00
  .byte   0x01
  .byte   0x02
  .byte   0x03
screendataend:
  .byte   0xff
red:
colors1:
  .byte   0b01001111
colors2:
  .byte   0b01000111
colors3:
  .byte   0b01000011
  .byte   0
blue:
  .byte   0b11001111
  .byte   0b11000111
  .byte   0b11000011
  .byte   0
green:
  .byte   0b10001111
  .byte   0b10000111
  .byte   0b10000011
  .byte   0

  ;; .text is the name of the section, it is a hint for the linker to
  ;; allocate the section
  ;; ax: a means allocatable by linker, x means executable
  ;; @progbits is a hint for the linker to allocate this section into
  ;; program memory (flash)
  .section ".text","ax",@progbits
_start:
  ;; disable watchdog
  mov.w   #WDTPW|WDTHOLD,&WDTCTL

  ;; configure clock system to the highest frequency
  mov.b   #DCO0|DCO1|DCO2,&DCOCTL
  mov.b   #XT2OFF|RSEL0|RSEL1|RSEL2|RSEL3,&BCSCTL1
  mov.b   #0,&BCSCTL2
  mov.b   #0,&BCSCTL3

  ;; initialize stack pointer with value from linker
  mov.w   #__stack, SP

  mov.w   #0xaaaa, r7
  mov.w   #0x5555, r8

init:
  ;; configuration of GPIO Ports
  mov.b   #BIT0|BIT1|BIT2,&P1DIR
  mov.b   #BIT1|BIT4,&P2DIR
  mov.b   #BIT1|BIT4,&P2SEL

  ;; timer configuration
  ;;  configure and stop timer
  ;;  cycle time is 56.25ns
  mov.w   #ID_0|MC_0|TACLR|TASSEL_2,&TA1CTL
  ;;  2.0us 
  mov.w   #45,&TA1CCR0
  ;;  a bit less
  mov.w   #10,&TA1CCR1
  mov.w   #22,&TA1CCR2
  ;;  configure output mode for TA0.1
  mov.w   #CCIE,&TA1CCTL0
  mov.w   #OUTMOD_7,&TA1CCTL1
  mov.w   #OUTMOD_7,&TA1CCTL2

  ;; initialize bit-counter for isr
  mov.b   #0x01,r6
  ;; initialize isr-sync register
  mov.b   #0x00,r4

  ;; screen data start/next into r7
  mov.w   #screendata, r7
  ;; screen data end into r8
  mov.w   #screendataend, r8
  ;; load first screen data value into r5
  mov.b   @r7,r5
  inc.w   r7

  ;; start timer in up mode
  bis.w   #MC0,&TA1CTL
  ;; enable interrupts
  eint




  ;; r4: synchronization between mainloop and isr
  ;; r5: data byte to be handled by isr
mainloop:
  ;; prepare next byte to handle by isr
  cmp.w   r7,r8
  jnz     mainloop_prepare_next_byte
  mov.w   &screendata,r7
mainloop_prepare_next_byte:
  mov.b   @r7,r9
  inc.w   r7

mainloop_wait_for_isr:
  ;; check bit0 in sync register
  bit     #0x01,r4
  jz      mainloop_wait_for_isr

  ;; load data
  mov.b   r9,r5
  mov.b   #0x00,r4
  ;; signal reload
  bis     #BIT2,&P1OUT
  bic     #BIT2,&P1OUT

  ;; continue
  jmp     mainloop




; --- timer isr ---
  ;; r6: exclusively used by isr as bit-counter
timer1_a0_isr:
  ;; func begin marker
  bis     #BIT0,&P1OUT
  ;; check isr idle bit
  bit     #BIT1,r4
  jnz     timer1_a0_isr_exit

  ;; shift msb of data register r5 into carry flag and set or reset P1.1 accordingly
  rla.b   r5
  jnc     timer1_a0_isr_false_bit
  bis     #BIT1,&P1OUT
  jmp     timer1_a0_isr_end
timer1_a0_isr_false_bit:
  bic     #BIT1,&P1OUT
   
  ;; shift bit-counter, after eight shifts signal byte done and reset bit-counter
timer1_a0_isr_end:
  rla.b   r6
  jnc     timer1_a0_isr_exit

  ;; reset bit-counter
  mov.b   #0x01,r6
  ;; signal byte done
  mov.b   #0x01,r4

timer1_a0_isr_exit:
  ;; func end marker
  bic     #BIT0,&P1OUT
  reti



;timer0_a1_isr:
;  reti

; --- interrupt vectors ---
;  .section "__interrupt_vector_9","ax",@progbits
;  .word   timer0_a1_isr
  .section "__interrupt_vector_14","ax",@progbits
  .word   timer1_a0_isr

  ;; .resetvec comes from linker
  .section ".resetvec","ax",@progbits
  .word   _start

  .end
