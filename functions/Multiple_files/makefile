FILENAME1   = main
FILENAME2   = LiquidCrystal
PORT       = COM4
DEVICE     = atmega328p
PROGRAMMER = arduino
BAUD       = 57600
COMPILE    = avr-gcc -Wall -mmcu=$(DEVICE) -Os


default: compile upload


compile: main.o LiquidCrystal.o
	@echo "third"
	$(COMPILE) -o  $(FILENAME1).elf $(FILENAME1).o $(FILENAME2).o
	avr-objcopy -O ihex -j .text -j .data $(FILENAME1).elf $(FILENAME1).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME1).elf

LiquidCrystal.o: $(FILENAME2).c $(FILENAME2).h
	@echo "sec"
	$(COMPILE) -c $(FILENAME2).c

main.o: $(FILENAME1).c
	@echo "main"
	$(COMPILE) -c $(FILENAME1).c



upload:
	avrdude -b $(BAUD) -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT)  -D -Uflash:w:$(FILENAME1).hex:i

clean:
	rm $(FILENAME1).o
	rm $(FILENAME2).o
	rm $(FILENAME1).hex
	rm $(FILENAME1).elf