TOOLCHAIN_PREFIX=/opt/msp430-gcc
CC=$(TOOLCHAIN_PREFIX)/bin/msp430-elf-gcc

# regular
MCU=msp430g2553
COMMON=-Wall -mmcu=$(MCU) -std=gnu99 -I $(TOOLCHAIN_PREFIX)/include -Os -g0
CFLAGS=$(COMMON)
ASFLAGS=$(COMMON)

LDFLAGS=-L $(TOOLCHAIN_PREFIX)/include -Wl,-Map,firmware.map -nostdlib -nostartfiles -T $(MCU).ld

firmware.elf:	main.o
	$(CC) -o $@ $(LDFLAGS) $^

.c.o:	
	$(CC) $(CFLAGS) -c $<

.S.o:	
	$(CC) $(ASFLAGS) -c $<


.PHONY: all
all:	firmware.elf

.PHONY: clean
clean:
	-rm -f *.o *.elf *.map

.PHONY: upload
upload: firmware.elf
	mspdebug rf2500 "prog firmware.elf"

.PHONY: debug
debug: upload
	mspdebug rf2500 gdb &
	ddd --debugger "msp430-gdb -x firmware.gdb"




# /opt/msp430-gcc/bin/msp430-elf-gcc main.S -D_GNU_ASSEMBLER_ -Wall -Os -g -fdata-sections -ffunction-sections -mmcu=msp430g2553 -T /opt/msp430-gcc/include/msp430g2553.ld -I /opt/msp430-gcc/include/ -L /opt/msp430-gcc/include/ -nostdli
