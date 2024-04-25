TOOLCHAIN_PREFIX=/opt/msp430-gcc
CC=$(TOOLCHAIN_PREFIX)/bin/msp430-elf-gcc
OBJDUMP=$(TOOLCHAIN_PREFIX)/bin/msp430-elf-objdump

ARTIFACT=firmware
MCU=msp430g2553
CFLAGS=-Wall -mmcu=$(MCU) -std=gnu99 -I $(TOOLCHAIN_PREFIX)/include -O1 -g0

# for debugging
#CFLAGS+= -g3 -ggdb -gdwarf-2

LDFLAGS=-mmcu=$(MCU) -L $(TOOLCHAIN_PREFIX)/include

$(ARTIFACT).elf:	main.o spi.o scheduler.o canvas.o shapes.o game.o buttons.o myrand.o display.o sound.o eeprom.o
	$(CC) -o $@ $(LDFLAGS) $^
	$(OBJDUMP) -D $(ARTIFACT).elf > $(ARTIFACT).txt

.c.o:	
	$(CC) $(CFLAGS) -c $<


.PHONY: all
all:	$(ARTIFACT).elf

.PHONY: clean
clean:
	-rm -f *.o $(ARTIFACT).elf $(ARTIFACT).txt

.PHONY: upload
upload: $(ARTIFACT).elf
	mspdebug rf2500 "prog $(ARTIFACT).elf"
