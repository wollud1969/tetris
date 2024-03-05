#include "colors.h"

  .section ".rodata","a"
screendata_tmpl:
  .global screendata_tmpl
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
  .byte _green
screendataend_tmpl:
  .byte   0xff

;; color definitions according to
;; https://learn.sparkfun.com/tutorials/lilypad-protosnap-plus-activity-guide/3-custom-color-mixing
colors:
  .global colors
  ;;      red, green, blue, padding
off:
  .byte   0x00, 0x00, 0x00, 0
blue:
  .byte   0x00, 0x00, 0xff, 0
green:
  .byte   0x00, 0xff, 0x00, 0
orange:
  .byte   0xff, 0x80, 0x00, 0
rose:
  .byte   0xff, 0x00, 0x80, 0
magenta:
  .byte   0xff, 0x00, 0xff, 0
violet:
  .byte   0x80, 0x00, 0xff, 0
azure:
  .byte   0x00, 0x80, 0xff, 0
cyan:
  .byte   0x00, 0xff, 0xff, 0
springgreen:
  .byte   0x00, 0xff, 0x80, 0
chartreuse:
  .byte   0x80, 0xff, 0x00, 0
yellow:
  .byte   0xff, 0xff, 0x00, 0
white:
  .byte   0xff, 0xff, 0xff, 0
red:
  .byte   0xff, 0x00, 0x00, 0

