#include "lcd.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define F_CPU 16000000UL

int main(void){

    LCD_Init(); /* Initialization of LCD*/
    LCD_Clear();
    _delay_ms(20);      
    LCD_String("WORK?");
    LCD_Command(0xC0); /* Go to 2nd line*/
    LCD_String("OSKAR ");
    while(1){
        
    }
}