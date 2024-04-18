TOOLCHAIN_PREFIX=/opt/msp430-gcc
CC=$(TOOLCHAIN_PREFIX)/bin/msp430-elf-gcc
OBJDUMP=$(TOOLCHAIN_PREFIX)/bin/msp430-elf-objdump

ARTIFACT=firmware
MCU=msp430g2553
COMMONFLAGS=-Wall -mmcu=$(MCU) -I $(TOOLCHAIN_PREFIX)/include -O0 -g0
CFLAGS=$(COMMONFLAGS) -std=gnu99 
ASFLAGS=$(COMMONFLAGS) -D__ASSEMBLER__

# for debugging
CFLAGS+= -g3 -ggdb -gdwarf-2

LDFLAGS=-mmcu=$(MCU) -L $(TOOLCHAIN_PREFIX)/include

$(ARTIFACT).elf:	main.o scheduler.o spi.o spi_init.o sequencer.o melody_tetris.o melody_tusch1.o ay_3_8913.o mute.o effects.o
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
	-rm -f *.o $(ARTIFACT).elf $(ARTIFACT).txt

.PHONY: upload
upload: $(ARTIFACT).elf
	mspdebug rf2500 "prog $(ARTIFACT).elf"
