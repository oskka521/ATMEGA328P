/*
working
https://www.electronicwings.com/avr-atmega/interfacing-lcd-16x2-in-4-bit-mode-with-atmega-16-32-


*/

#define F_CPU 16000000UL
//#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define DATAPORT PORTD
#define DATAPORTDIR DDRD

void LCD_Command(unsigned char cmnd);
void LCD_Char(unsigned char data);
void LCD_Init(void);
void LCD_String(char *str);
void LCD_String_xy(char row, char pos, char *str);
void LCD_Clear();

int main(void)
{
    LCD_Init();        /* Initialization of LCD*/
    LCD_String("HELLO WORLD"); /* Write string on 1st line of LCD*/
    LCD_Command(0xC0); /* Go to 2nd line*/
    LCD_String("WOW");
    while (1)
    {
    }
}

void LCD_Command(unsigned char cmnd)
{
    DATAPORT = (DATAPORT & 0x0F) | (cmnd & 0xF0); /* sending upper nibble */

    PORTB &= ~(1 << PORTB4); /* RS=0, command reg. */
    PORTB |= (1 << PORTB3);  /* Enable pulse */
    _delay_us(1);
    PORTB &= ~(1 << PORTB3);

    _delay_us(200);

    DATAPORT = (DATAPORT & 0x0F) | (cmnd << 4); /* sending lower nibble */

    PORTB |= (1 << PORTB3);
    _delay_us(1);
    PORTB &= ~(1 << PORTB3);
    _delay_ms(2);
}

void LCD_Char(unsigned char data)
{
    DATAPORT = (DATAPORT & 0x0F) | (data & 0xF0); /* sending upper nibble */

    PORTB |= (1 << PORTB4); /* RS=1, data reg. */
    PORTB |= (1 << PORTB3);
    _delay_us(1);
    PORTB &= ~(1 << PORTB3);

    _delay_us(200);

    DATAPORT = (DATAPORT & 0x0F) | (data << 4); /* sending lower nibble */

    PORTB |= (1 << PORTB3);
    _delay_us(1);
    PORTB &= ~(1 << PORTB3);
    _delay_ms(2);
}

void LCD_Init(void) /* LCD Initialize function */
{
    DDRD = 0xFF;
    //DDRD |= (1 << PORTD2) | (1 << PORTD3) | (1 << PORTD4) | (1 << PORTD5); /* Make LCD port direction as o/p */
    DATAPORT |= (1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7);
    DDRB |= (1 << PORTB3) | (1 << PORTB4);

    _delay_ms(20); /* LCD Power ON delay always >15ms */

    LCD_Command(0x02); /* send for 4 bit initialization of LCD  */
    LCD_Command(0x28); /* 2 line, 5*7 matrix in 4-bit mode */
    LCD_Command(0x0c); /* Display on cursor off*/
    LCD_Command(0x06); /* Increment cursor (shift cursor to right)*/
    LCD_Command(0x01); /* Clear display screen*/
    _delay_ms(2);
    //LCD_Command(0x80); /* Cursor 1st row 0th position */
}

void LCD_String(char *str) /* Send string to LCD function */
{
    int i;
    for (i = 0; str[i] != 0; i++) /* Send each char of string till the NULL */
    {
        LCD_Char(str[i]);
    }
}

void LCD_String_xy(char row, char pos, char *str) /* Send string to LCD with xy position */
{
    if (row == 0 && pos < 16)
        LCD_Command((pos & 0x0F) | 0x80); /* Command of first row and required position<16 */
    else if (row == 1 && pos < 16)
        LCD_Command((pos & 0x0F) | 0xC0); /* Command of first row and required position<16 */
    LCD_String(str);                      /* Call LCD string function */
}

void LCD_Clear()
{
    LCD_Command(0x01); /* Clear display */
    _delay_ms(2);
    LCD_Command(0x80); /* Cursor at home position */
}
