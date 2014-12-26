#configuration
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
AVRDUDE_CONF = -C /home/timothy/bin/avrdude.conf

#board
MCU = attiny85
FCPU = 16500000L

all: main.hex

main.hex: main.elf
	$(OBJCOPY) -O ihex main.elf main.hex

#source files
SRC = main.c
SRC += ../MidiKeyboardC.c
SRC += ../usbdrvasm_includer.S
SRC += ../usbdrv_includer.c
SRC += ../osccal.c

main.elf:
	$(CC) -mmcu=$(MCU) -DF_CPU=$(FCPU) -Os -o main.elf -I../ $(SRC)
	
flash:
	$(AVRDUDE) $(AVRDUDE_CONF) -p$(MCU) -cusbtiny -e -v -U flash:w:main.hex:i
	
clean:
	rm -f main.hex main.elf
