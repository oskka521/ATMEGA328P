FILENAME   = blink
PORT       = COM4
DEVICE     = atmega328p
PROGRAMMER = arduino
BAUD       = 57600
CLOCK      = 16000000
COMPILE    = avr-gcc -Wall -mmcu=$(DEVICE) -std=c99 -Os -DF_CPU=$(CLOCK)


default: compile upload clean

run: 
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o
	rm $(FILENAME).o

compile:
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex 
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf

upload:
	avrdude -b $(BAUD) -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT)  -D -Uflash:w:$(FILENAME).hex:i

clean:
	rm $(FILENAME).o
	rm $(FILENAME).elf
	rm $(FILENAME).hex