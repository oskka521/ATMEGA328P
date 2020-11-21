#define F_CPU 16000000UL

#include "LCD/lcd.h"
#include "I2C/I2C_slave.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Slave_Address 0x20

int main(void)
{
    char buffer[10];
    int8_t count = 0;

    LCD_Init();
    I2C_Slave_Init(Slave_Address);

    LCD_String_xy(0, 0, "Slave Device");

    while (1)
    {
        switch (I2C_Slave_Listen()) /* Check for SLA+W or SLA+R */
        {
        case 0:
        {
            LCD_String_xy(1, 0, "Rec:       ");
            do
            {
                sprintf(buffer, "%d    ", count);
                LCD_String_xy(1, 6, buffer);
                count = I2C_Slave_Receive(); /* Receive data byte*/
            } while (count != -1);           /* Receive until STOP/REPEATED START */
            count = 0;
            break;
        }
        case 1:
        {
            int8_t Ack_status;
            LCD_String_xy(1, 0, "Send:       ");
            do
            {
                Ack_status = I2C_Slave_Transmit(count); /* Send data byte */
                sprintf(buffer, "%d    ", count);
                LCD_String_xy(1, 6, buffer);
                count++;
            } while (Ack_status == 0); /* Send until Ack is receive */
            break;
        }
        default:
            break;
        }
    }

    return 0;
}
