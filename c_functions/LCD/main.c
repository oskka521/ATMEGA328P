#define F_CPU 16000000UL

#include "lcd.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{

    LCD_Init(); /* Initialization of LCD*/
    LCD_Clear();
    LCD_String("WORKS?");
    LCD_Command(0xC0); /* Go to 2nd line*/
    LCD_String("ORRVAR ");

    _delay_ms(500);
    int counter = 0;
    char counter_string[4];
    while (1)
    {
        _delay_ms(500);
        LCD_Clear();
        LCD_String("OSKAR K ");
        LCD_Command(0xC0);
        itoa(counter, counter_string, 10);
        LCD_String(counter_string);
        LCD_String(" D");
        counter++;
    }
}