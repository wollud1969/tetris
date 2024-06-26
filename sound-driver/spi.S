#include <msp430g2553.h>
#include "soundCodes.h"


  .section ".text","ax",@progbits
receive_isr:
  bit     #UCB0RXIFG, &UC0IFG
  jz      receive_isr_no_data
  bit     #SOUND_COMMAND, &cmd
  jnz     receive_isr_no_data
  bis     UCB0RXBUF, &cmd
receive_isr_no_data:
  reti

  .global spiCmdHandler
spiCmdHandler:
spiCmdHandler_0:
  bit     #SOUND_COMMAND, &cmd
  jz      spiCmdHandler_1
  ;; insert a call here
  call    #spiCommandDispatcher
  mov.b   #0, &cmd
  ret
spiCmdHandler_1:
  bit     #SOUND_MUTE, &cmd
  jz      spiCmdHandler_2
  call    #mute
  bic     #SOUND_MUTE, &cmd
spiCmdHandler_2:
  bit     #SOUND_UNMUTE, &cmd
  jz      spiCmdHandler_3
  call    #unMute
  bic     #SOUND_UNMUTE, &cmd
spiCmdHandler_3:
  bit     #SOUND_START, &cmd
  jz      spiCmdHandler_4
  call    #playMelodyTetris
  bic     #SOUND_START, &cmd
spiCmdHandler_4:
  bit     #SOUND_GAMEOVER, &cmd
  jz      spiCmdHandler_5
  call    #stopMelodyTetris
  bic     #SOUND_GAMEOVER, &cmd
spiCmdHandler_5:
  bit     #SOUND_FANFARE, &cmd
  jz      spiCmdHandler_6
  call    #playMelodyTetrisFaster
  call    #playTusch1
  bic     #SOUND_FANFARE, &cmd
spiCmdHandler_6:
  bit     #SOUND_LOCK, &cmd
  jz      spiCmdHandler_7
  ;; insert a call here
  bic     #SOUND_LOCK, &cmd
spiCmdHandler_7:
  bit     #SOUND_PLING, &cmd
  jz      spiCmdHandler_end
  call    #playPling
  bic     #SOUND_PLING, &cmd
spiCmdHandler_end:
  ret


  .section "__interrupt_vector_8","ax",@progbits
  .word   receive_isr


  .end
