  .file "main.S"

#include <msp430g2553.h>


#define PC r0
#define SP r1
#define SR r2


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

init:
  ;; configuration of GPIO Port1, use Bit6 as TA0.1
  mov.b   #BIT6,&P1DIR
  mov.b   #BIT6,&P1SEL

  ;; timer configuration
  ;;  configure and stop timer
  ;;  cycle time is 56.25ns
  mov.w   #ID_0|MC_0|TACLR|TASSEL_2,&TACTL
  ;;  2.0us 
  mov.w   #45,&TACCR0
  ;;  a bit less
  mov.w   #16,&TACCR1
  ;;  configure output mode for TA0.1
;  mov.w   #CCIE,&TACCTL0
;  mov.w   #CCIE,&TACCTL1
  mov.w   #OUTMOD_7,&TACCTL1
  ;;  start timer in up mode
  bis.w   #MC0,&TACTL

  ;; enable interrupts
  eint

mainloop:
  jmp     mainloop

; --- timer isr ---
;timer0_a0_isr:
;  mov.b   #BIT0,&P1OUT
;  reti

;timer0_a1_isr:
;  mov.b   #0,&P1OUT
;  reti

; --- interrupt vectors ---
;  .section "__interrupt_vector_9","ax",@progbits
;  .word   timer0_a1_isr
;  .section "__interrupt_vector_10","ax",@progbits
;  .word   timer0_a0_isr

  ;; .resetvec comes from linker
  .section ".resetvec","ax",@progbits
  .word   _start

  .end
