#include "lcd.h"

void LCD_Command(unsigned char cmnd)
{
    upload_data_lcd(cmnd,1);
    CONTROLPORT &= ~(1 << CONTROLRES); /* RS=0, command reg. */
    CONTROLPORT |= (1 << CONTROLEN);  /* Enable pulse */
    _delay_us(1);
    CONTROLPORT &= ~(1 << CONTROLEN);
    _delay_us(20);

    upload_data_lcd(cmnd,0);
    CONTROLPORT |= (1 << CONTROLEN);
    _delay_us(1);
    CONTROLPORT &= ~(1 << CONTROLEN);
    _delay_ms(2);
}

void LCD_Char(unsigned char data)
{
    upload_data_lcd(data,1);
    CONTROLPORT |= (1 << CONTROLRES); /* RS=1, data reg. */
    CONTROLPORT |= (1 << CONTROLEN);
    _delay_us(1);
    CONTROLPORT &= ~(1 << CONTROLEN);
    _delay_us(20);

    upload_data_lcd(data,0);
    CONTROLPORT |= (1 << CONTROLEN);
    _delay_us(1);
    CONTROLPORT &= ~(1 << CONTROLEN);
    _delay_ms(2);
}

void LCD_Init(void) 
{
    DATAPORTDIR |= (1 << DATA1) | (1 << DATA2) | (1 << DATA3) | (1 << DATA4);
    CONTROLPORTDIR |= (1 << CONTROLEN) | (1 << PORTB4);
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

void upload_data_lcd(unsigned char data, int upper)
{
    if (upper){
        unsigned char filtered_data = (data & 0xF0);
        DATAPORT &= ~(1 << DATA1) & ~(1 << DATA2) & ~(1 << DATA3) & ~(1 << DATA4);

        if (filtered_data & 0b00010000){
            DATAPORT |= (1 << DATA1);
        }
        if (filtered_data & 0b00100000){
            DATAPORT |= (1 << DATA2);
        }
        if (filtered_data & 0b01000000){
            DATAPORT |= (1 << DATA3);
        }
        if (filtered_data & 0b10000000){
            DATAPORT |= (1 << DATA4);
        }
    }
    else{
        unsigned char filtered_data = (data & 0x0F);
        DATAPORT &= ~(1 << DATA1) & ~(1 << DATA2) & ~(1 << DATA3) & ~(1 << DATA4);

        if (filtered_data & 0b00000001){
            DATAPORT |= (1 << DATA1);
        }
        if (filtered_data & 0b00000010){
            DATAPORT |= (1 << DATA2);
        }
        if (filtered_data & 0b00000100){
            DATAPORT |= (1 << DATA3);
        }
        if (filtered_data & 0b00001000){
            DATAPORT |= (1 << DATA4);
        }
    } 
}


