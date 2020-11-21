FILENAME1   = master
FILENAME2   = lcd
FILENAME3   = I2C_master
PORT       = usb
DEVICE     = atmega328p
PROGRAMMER = avrispmkII
BAUD       = 57600
COMPILE    = avr-gcc -Wall -mmcu=$(DEVICE) -Os


default: compile upload


compile: main.o lcd.o I2C_master.o
	@echo "LINKING"
	$(COMPILE) -o  $(FILENAME1).elf $(FILENAME1).o $(FILENAME2).o $(FILENAME3).o
	avr-objcopy -O ihex -j .text -j .data $(FILENAME1).elf $(FILENAME1).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME1).elf

main.o: $(FILENAME1).c
	@echo "MAIN"
	$(COMPILE) -c $(FILENAME1).c

lcd.o: LCD/$(FILENAME2).c LCD/$(FILENAME2).h
	@echo "LCD"
	$(COMPILE) -c LCD/$(FILENAME2).c

I2C_master.o: I2C/$(FILENAME3).c I2C/$(FILENAME3).h
	@echo "I2C MASTER"
	$(COMPILE) -c I2C/$(FILENAME3).c


upload:
	@echo "UPLOAD"
	avrdude -b $(BAUD) -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -Uflash:w:$(FILENAME1).hex:i

clean:
	rm $(FILENAME1).o
	rm $(FILENAME2).o
	rm $(FILENAME3).o
	rm $(FILENAME1).hex
	rm $(FILENAME1).elf