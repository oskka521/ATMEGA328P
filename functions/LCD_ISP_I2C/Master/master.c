#define F_CPU 16000000UL

#include "LCD/lcd.h"
#include "I2C/I2C_master.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Slave_Write_Address 0x20
#define Slave_Read_Address 0x21
#define count 10

int main(void)
{
    char buffer[10];

    LCD_Init(); /* Initialize LCD */
    I2C_Init(); /* Initialize I2C */

    LCD_String_xy(0, 0, "Master Device");

    while (1)
    {
        LCD_String_xy(1, 0, "Send:       ");
        I2C_Start_Wait(Slave_Write_Address); /* Start I2C with SLA+W */
        _delay_ms(5);
        uint8_t i;
        for (i = 0; i < count; i++)
        {
            sprintf(buffer, "%d    ", i);
            LCD_String_xy(1, 6, buffer);
            I2C_Write(i); /* Send Incrementing count */
            _delay_ms(500);
        }
        LCD_String_xy(1, 0, "Rec:       ");
        I2C_Repeated_Start(Slave_Read_Address); /* Repeated Start with SLA+R */
        _delay_ms(5);
        for (i = 0; i < count; i++)
        {
            if (i < count - 1)
                sprintf(buffer, "%d    ", I2C_Read_Ack()); /* Read & Ack of data */
            else
                sprintf(buffer, "%d    ", I2C_Read_Nack()); /* Read & Nack to data */
            LCD_String_xy(1, 6, buffer);
            _delay_ms(500);
        }
        I2C_Stop(); /* Stop I2C */
    }               /* Stop I2C */
    return 0;
}
