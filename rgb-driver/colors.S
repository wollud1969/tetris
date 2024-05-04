#include "colors.h"

#define DIMM_FACTOR 3
  .section ".rodata","a"
;; color definitions according to
;; https://learn.sparkfun.com/tutorials/lilypad-protosnap-plus-activity-guide/3-custom-color-mixing
colors:
  .global colors
  ;;      red, green, blue, padding
off:
  .byte   0x00, 0x00, 0x00, 0
blue:
  .byte   0x00>>DIMM_FACTOR, 0x00>>DIMM_FACTOR, 0xff>>DIMM_FACTOR, 0
green:
  .byte   0x00>>DIMM_FACTOR, 0xff>>DIMM_FACTOR, 0x00>>DIMM_FACTOR, 0
orange:
  .byte   0xff>>DIMM_FACTOR, 0x80>>DIMM_FACTOR, 0x00>>DIMM_FACTOR, 0
rose:
  .byte   0xff>>DIMM_FACTOR, 0x00>>DIMM_FACTOR, 0x80>>DIMM_FACTOR, 0
magenta:
  .byte   0xff>>DIMM_FACTOR, 0x00>>DIMM_FACTOR, 0xff>>DIMM_FACTOR, 0
violet:
  .byte   0x80>>DIMM_FACTOR, 0x00>>DIMM_FACTOR, 0xff>>DIMM_FACTOR, 0
azure:
  .byte   0x00>>DIMM_FACTOR, 0x80>>DIMM_FACTOR, 0xff>>DIMM_FACTOR, 0
cyan:
  .byte   0x00>>DIMM_FACTOR, 0xff>>DIMM_FACTOR, 0xff>>DIMM_FACTOR, 0
springgreen:
  .byte   0x00>>DIMM_FACTOR, 0xff>>DIMM_FACTOR, 0x80>>DIMM_FACTOR, 0
chartreuse:
  .byte   0x80>>DIMM_FACTOR, 0xff>>DIMM_FACTOR, 0x00>>DIMM_FACTOR, 0
yellow:
  .byte   0xff>>DIMM_FACTOR, 0xff>>DIMM_FACTOR, 0x00>>DIMM_FACTOR, 0
white:
  .byte   0xff>>DIMM_FACTOR, 0xff>>DIMM_FACTOR, 0xff>>DIMM_FACTOR, 0
red:
  .byte   0xff>>DIMM_FACTOR, 0x00>>DIMM_FACTOR, 0x00>>DIMM_FACTOR, 0
flash:
  .byte   0xff, 0xff, 0xff, 0

