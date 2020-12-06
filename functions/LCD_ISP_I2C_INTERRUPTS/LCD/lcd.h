
#pragma once
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define DATAPORTDIR DDRD
#define DATAPORT PORTD
#define DATA1 PORTD3
#define DATA2 PORTD2
#define DATA3 PORTD6
#define DATA4 PORTD7

#define CONTROLPORTDIR DDRB
#define CONTROLPORT PORTB
#define CONTROLEN PORTB3
#define CONTROLRES PORTB4

void LCD_Command(unsigned char cmnd);
void LCD_Char(unsigned char data);
void LCD_Init(void);
void LCD_String(char *str);
void LCD_String_xy(char row, char pos, char *str);
void LCD_Clear();
void upload_data_lcd(unsigned char data, int upper);
