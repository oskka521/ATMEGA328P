FILENAME1   = blink
FILENAME2   = uart_utility_functions
PORT       = COM4
DEVICE     = atmega328p
PROGRAMMER = arduino
BAUD       = 57600
CLOCK      = 16000000UL
LIBS       = -lprintf_flt -lm
LDFLAGS    = -Wl,-u,vfprintf
COMPILE    = avr-g++ -Wall -mmcu=$(DEVICE) -Os -DF_CPU=$(CLOCK)  
PYTHONFILE = run

default: compile upload clean serial 

compile: blink.o uart_utility_functions.o
	@echo "LINKING"
	$(COMPILE) $(LDFLAGS) $(LIBS) -o  $(FILENAME1).elf $(FILENAME1).o $(FILENAME2).o 
	avr-objcopy -O ihex -j .text -j .data $(FILENAME1).elf $(FILENAME1).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME1).elf

blink.o: $(FILENAME1).cpp
	@echo "MAIN"
	$(COMPILE) -c $(FILENAME1).cpp

uart_utility_functions.o: UART/$(FILENAME2).cpp UART/$(FILENAME2).h
	@echo "UART"
	$(COMPILE) -c UART/$(FILENAME2).cpp

upload:
	avrdude -b $(BAUD) -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT)  -D -Uflash:w:$(FILENAME1).hex:i

serial: $(PYTHONFILE).py
	python $(PYTHONFILE).py

clean:
	rm $(FILENAME1).o
	rm $(FILENAME2).o
	rm $(FILENAME1).elf
	rm $(FILENAME1).hex


