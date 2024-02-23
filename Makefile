TOOLCHAIN_PREFIX=/opt/msp430-gcc
CC=$(TOOLCHAIN_PREFIX)/bin/msp430-elf-gcc
OBJDUMP=$(TOOLCHAIN_PREFIX)/bin/msp430-elf-objdump

MCU=msp430g2553
ARTIFACT=firmware
COMMON=-Wall -mmcu=$(MCU) -std=gnu99 -I $(TOOLCHAIN_PREFIX)/include -Os -g0 -fdata-sections -ffunction-sections
CFLAGS=$(COMMON)
ASFLAGS=$(COMMON) -D__ASSEMBLER__

LDFLAGS=-L $(TOOLCHAIN_PREFIX)/include -Wl,-Map,firmware.map -nostdlib -nostartfiles -T $(MCU).ld

$(ARTIFACT).elf:	main.o
	$(CC) -o $@ $(LDFLAGS) $^
	$(OBJDUMP) -D $(ARTIFACT).elf > $(ARTIFACT).txt
  

.c.o:	
	$(CC) $(CFLAGS) -c $<

.S.o:	
	$(CC) $(ASFLAGS) -c $<


.PHONY: all
all:	$(ARTIFACT).elf

.PHONY: clean
clean:
	-rm -f *.o *.elf *.map *.txt

.PHONY: upload
upload: $(ARTIFACT).elf
	mspdebug rf2500 "prog $(ARTIFACT).elf"


