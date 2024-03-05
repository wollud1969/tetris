#include <msp430g2553.h>
#include "colors.h"

#define PC r0
#define SP r1
#define SR r2


#define SIGNAL_REGISTER r4
#define SIGNAL_OCTET_DONE 0x01
#define SIGNAL_ISR_ENABLE 0x02
#define SIGNAL_ALL_DATA_DONE 0x04


#define DATA_NEXT_ADDRESS_REGISTER r7
#define DATA_END_ADDRESS_REGISTER r8
#define DATA_REGISTER r5
#define NEXT_DATA_REGISTER r9

#define BIT_COUNTER_REGISTER r6
#define BIT_COUNTER_INIT_VALUE 0x01



;; 2.48us
#define TIMER_COMPLETE 45
;; 1.18us
#define TIMER_LONG 22
;; 550ns
#define TIMER_SHORT 10

  .macro set_data_bit
  bis   #BIT0, &P1OUT
  .endm
  .macro clear_data_bit
  bic   #BIT0, &P1OUT
  .endm
  .macro set_output_enable
  bis   #BIT1, &P1OUT
  .endm
  .macro clear_output_enable
  bic   #BIT1, &P1OUT
  .endm
  .macro set_debug
  bis   #BIT2, &P1OUT
  .endm
  .macro clear_debug
  bic   #BIT2, &P1OUT
  .endm

  .section ".data"
screendata:
  .rept 60
  .byte 0
  .endr
screendataend:
  .byte 0xff


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

;  ;; ----------------------------------------------
;  ;; load data from template area in rom into ram
;  ;; uses arbitrary register before loading registers
;  ;; for later use
;  mov.w   #screendata, r7
;  mov.w   #screendataend, r8
;  mov.w   #screendata_tmpl, r9
;_start_load_next:
;  mov.b   @r9, @r7
;  inc.w   r7
;  inc.w   r9
;  cmp.w   r7, r8
;  jnz _start_load_next
;  ;; ----------------------------------------------


init:
  ;; configuration of GPIO Ports
  ;; BIT0: data bit
  ;; BIT1: output enable
  ;; BIT2: debug
  mov.b   #BIT0|BIT1|BIT2,&P1DIR
  mov.b   #0,&P1OUT
  ;; BIT4: long pulse
  ;; BIT1: short pulse
  mov.b   #BIT1|BIT4,&P2DIR
  mov.b   #BIT1|BIT4,&P2SEL

  ;; timer configuration
  ;;  configure and stop timer
  ;;  cycle time is 56.25ns
  mov.w   #ID_0|MC_0|TACLR|TASSEL_2,&TA1CTL
  ;;  2.0us 
  mov.w   #TIMER_COMPLETE,&TA1CCR0
  ;;  a bit less
  mov.w   #TIMER_SHORT,&TA1CCR1
  mov.w   #TIMER_LONG,&TA1CCR2
  ;;  configure output mode for TA0.1
  mov.w   #CCIE,&TA1CCTL0
  mov.w   #OUTMOD_7,&TA1CCTL1
  mov.w   #OUTMOD_7,&TA1CCTL2


  ;; initialize bit-counter for isr
  mov.b   #BIT_COUNTER_INIT_VALUE, BIT_COUNTER_REGISTER
  ;; initialize isr-sync register, signal BYTE_DONE for the first start
  mov.b   #SIGNAL_OCTET_DONE, SIGNAL_REGISTER

  ;; start timer in up mode
  bis.w   #MC0,&TA1CTL
  ;; enable interrupts
  eint

mainloop:
  call    #resetscreen
  call    #drawscreen

  jmp     mainloop


resetscreen:
  ;; reset screen data
  mov.w   #screendata, r7
  mov.w   #screendataend, r8
resetscreen_continue:
  mov.b   #_off, @r7
  inc.w   r7
  cmp.w   r7, r8
  jnz resetscreen_continue
  ret



drawscreen:
  ;; initialize bit-counter for isr
  mov.b   #BIT_COUNTER_INIT_VALUE, BIT_COUNTER_REGISTER
  ;; initialize isr-sync register, signal BYTE_DONE for the first start
  mov.b   #SIGNAL_OCTET_DONE, SIGNAL_REGISTER

  ;; screen data start/next into r7
  mov.w   #screendata, DATA_NEXT_ADDRESS_REGISTER
  ;; screen data end into r8
  mov.w   #screendataend, DATA_END_ADDRESS_REGISTER

drawscreen_continue:
  ;; prepare next byte to handle by isr
  cmp.w   DATA_NEXT_ADDRESS_REGISTER, DATA_END_ADDRESS_REGISTER
  jz      drawscreen_data_done

  ;; load next data byte
  mov.b   @DATA_NEXT_ADDRESS_REGISTER, NEXT_DATA_REGISTER
  inc.w   DATA_NEXT_ADDRESS_REGISTER

  ;; multiple color code by four to get color data
  rla.b   NEXT_DATA_REGISTER
  rla.b   NEXT_DATA_REGISTER

  ;; enable isr
  bis     #SIGNAL_ISR_ENABLE, SIGNAL_REGISTER

drawscreen_wait_for_isr_0:
  ;; check bit0 in sync register
  bit     #SIGNAL_OCTET_DONE, SIGNAL_REGISTER
  jz      drawscreen_wait_for_isr_0
  ;; load data
  mov.b   colors(NEXT_DATA_REGISTER), DATA_REGISTER
  ;; clear BYTE_DONE
  bic     #SIGNAL_OCTET_DONE,  SIGNAL_REGISTER
drawscreen_wait_for_isr_1:
  ;; check bit0 in sync register
  bit     #SIGNAL_OCTET_DONE, SIGNAL_REGISTER
  jz      drawscreen_wait_for_isr_1
  ;; load data
  mov.b   colors+1(NEXT_DATA_REGISTER), DATA_REGISTER
  ;; clear BYTE_DONE
  bic     #SIGNAL_OCTET_DONE,  SIGNAL_REGISTER
drawscreen_wait_for_isr_2:
  ;; check bit0 in sync register
  bit     #SIGNAL_OCTET_DONE, SIGNAL_REGISTER
  jz      drawscreen_wait_for_isr_2
  ;; load data
  mov.b   colors+2(NEXT_DATA_REGISTER), DATA_REGISTER
  ;; clear BYTE_DONE
  bic     #SIGNAL_OCTET_DONE,  SIGNAL_REGISTER

  ;; continue
  jmp     drawscreen_continue

drawscreen_data_done:
  ;; signal all data processed, isr finish
  bis     #SIGNAL_ALL_DATA_DONE,  SIGNAL_REGISTER

  ret




; --- timer isr ---
  ;; r6: exclusively used by isr as bit-counter
timer1_a0_isr:
  ;; check isr enable bit
  bit     #SIGNAL_ISR_ENABLE, SIGNAL_REGISTER
  jz      timer1_a0_isr_exit

  ;; shift msb of data register r5 into carry flag and set or reset P1.0 accordingly
  rla.b   DATA_REGISTER
  jnc     timer1_a0_isr_false_bit
  set_data_bit
  jmp     timer1_a0_isr_end
timer1_a0_isr_false_bit:
  clear_data_bit
   
timer1_a0_isr_end:
  ;; enable output
  set_output_enable

  ;; roll bit-counter
  rla.b   BIT_COUNTER_REGISTER
  jnc     timer1_a0_isr_exit

  ;; reset bit-counter
  mov.b   #BIT_COUNTER_INIT_VALUE, BIT_COUNTER_REGISTER
  ;; signal byte done
  bis     #SIGNAL_OCTET_DONE, SIGNAL_REGISTER

  ;; check whether all data are processed
  bit     #SIGNAL_ALL_DATA_DONE,  SIGNAL_REGISTER
  jz      timer1_a0_isr_exit
  ;; disable isr
  bic     #SIGNAL_ISR_ENABLE,  SIGNAL_REGISTER
  ;; disable output
  clear_output_enable

timer1_a0_isr_exit:
  reti



  .section "__interrupt_vector_14","ax",@progbits
  .word   timer1_a0_isr

  ;; .resetvec comes from linker
  .section ".resetvec","ax",@progbits
  .word   _start

  .end



