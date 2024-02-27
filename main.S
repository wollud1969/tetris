  .file "main.S"

#include <msp430g2553.h>
#include "colors.h"

#define PC r0
#define SP r1
#define SR r2


#define SIGNAL_REGISTER r4
#define DATA_NEXT_REGISTER r7
#define DATA_END_REGISTER r8

  .section ".data"
screendata:
  .rept 3
  .byte 0
  .endr
screendataend:
  .byte 0xff

  .section ".rodata"
  .extern screendata_tmpl
  .extern colors

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

  ;; ----------------------------------------------
  ;; load data from template area in rom into ram
  mov.w   #screendata, r7
  mov.w   #screendataend, r8
  mov.w   #screendata_tmpl, r9
_start_load_next:
  mov.b   @r9, @r7
  inc.w   r7
  inc.w   r9
  cmp.w   r7, r8
  jnz _start_load_next
  ;; ----------------------------------------------

init:
  ;; configuration of GPIO Ports
  mov.b   #BIT0|BIT1|BIT2,&P1DIR
  mov.b   #0,&P1OUT
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
  ;; initialize isr-sync register, signal BYTE_DONE for the first start
  mov.b   #0x01, SIGNAL_REGISTER

  ;; screen data start/next into r7
  mov.w   #screendata, DATA_NEXT_REGISTER
  ;; screen data end into r8
  mov.w   #screendataend, DATA_END_REGISTER

  ;; start timer in up mode
  bis.w   #MC0,&TA1CTL
  ;; enable interrupts
  eint




  ;; r4: synchronization between mainloop and isr
  ;; r5: data byte to be handled by isr
mainloop:
  ;; prepare next byte to handle by isr
  cmp.w   DATA_NEXT_REGISTER, DATA_END_REGISTER
  jz      mainloop_data_done

  ;; load next data byte
  mov.b   @DATA_NEXT_REGISTER,r9
  inc.w   DATA_NEXT_REGISTER

  ;; multiple color code by four to get color data
  rla.b   r9
  rla.b   r9

  ;; enable isr
  bis     #0x02, SIGNAL_REGISTER

mainloop_wait_for_isr_0:
  ;; check bit0 in sync register
  bit     #0x01, SIGNAL_REGISTER
  jz      mainloop_wait_for_isr_0
  ;; load data
  mov.b   colors(r9), r5
  ;; clear BYTE_DONE
  bic     #0x01,  SIGNAL_REGISTER
mainloop_wait_for_isr_1:
  ;; check bit0 in sync register
  bit     #0x01, SIGNAL_REGISTER
  jz      mainloop_wait_for_isr_1
  ;; load data
  mov.b   colors+1(r9), r5
  ;; clear BYTE_DONE
  bic     #0x01,  SIGNAL_REGISTER
mainloop_wait_for_isr_2:
  ;; check bit0 in sync register
  bit     #0x01, SIGNAL_REGISTER
  jz      mainloop_wait_for_isr_2
  ;; load data
  mov.b   colors+2(r9), r5
  ;; clear BYTE_DONE
  bic     #0x01,  SIGNAL_REGISTER

  ;; continue
  jmp     mainloop

mainloop_data_done:
  ;; signal all data processed, isr finish
  bis     #0x04,  SIGNAL_REGISTER
  bis     #BIT2, &P1OUT
  ;; continue
  jmp     mainloop




; --- timer isr ---
  ;; r6: exclusively used by isr as bit-counter
timer1_a0_isr:
  ;; check isr enable bit
  bit     #0x02, SIGNAL_REGISTER
  jz      timer1_a0_isr_exit

  ;; shift msb of data register r5 into carry flag and set or reset P1.0 accordingly
  rla.b   r5
  jnc     timer1_a0_isr_false_bit
  bis     #BIT0,&P1OUT
  jmp     timer1_a0_isr_end
timer1_a0_isr_false_bit:
  bic     #BIT0,&P1OUT
   
timer1_a0_isr_end:
  ;; enable output
  bis     #BIT1, &P1OUT

  ;; roll bit-counter
  rla.b   r6
  jnc     timer1_a0_isr_exit

  ;; reset bit-counter
  mov.b   #0x01,r6
  ;; signal byte done
  bis     #0x01, SIGNAL_REGISTER

  ;; check whether all data are processed
  bit     #0x04,  SIGNAL_REGISTER
  jz      timer1_a0_isr_exit
  ;; disable isr
  bic     #0x02,  SIGNAL_REGISTER
  ;; disable output
  bic     #BIT1, &P1OUT

timer1_a0_isr_exit:
  reti



  .section "__interrupt_vector_14","ax",@progbits
  .word   timer1_a0_isr

  ;; .resetvec comes from linker
  .section ".resetvec","ax",@progbits
  .word   _start

  .end
