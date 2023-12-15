# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/

CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:wakedemo.elf

wakedemo.elf: ${COMMON_OBJECTS} wakedemo.o wdt_handler.o leds.o switches.o buzzer.o wdt_handler.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

load: wakedemo.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
