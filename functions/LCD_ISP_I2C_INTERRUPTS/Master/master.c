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
#define MESSAGE_LENGTH 100

void send_message(char *message, int length);
void recive_message(char *message);

int main(void)
{
    char message[MESSAGE_LENGTH] = "HELLO";
    char *mess = message;

    char received[MESSAGE_LENGTH];

    LCD_Init();
    I2C_Init();

    LCD_String_xy(0, 0, "Master Device");

    int num = 10;
    char snum[3];

    while (1)
    {
        char message[MESSAGE_LENGTH] = "HELLO";
        char *mess = message;
        itoa(num, snum, 10);
        num++;
        strcat(mess, snum);

        LCD_String_xy(1, 0, "                       ");
        LCD_String_xy(1, 0, "S:");
        send_message(mess, strlen(mess));
        LCD_String_xy(1, 2, mess);
        _delay_ms(5000);

        LCD_String_xy(1, 0, "                       ");
        LCD_String_xy(1, 0, "R:");
        recive_message(received);
        LCD_String_xy(1, 2, received);

        _delay_ms(5000);

        I2C_Stop(); /* Stop I2C */
    }
    return 0;
}

void send_message(char *message, int length)
{
    I2C_Start_Wait(Slave_Write_Address);
    _delay_ms(5);
    int i;
    for (i = 0; i < length; i++)
    {
        I2C_Write(message[i]);
        _delay_ms(5);
    }
    I2C_Stop();
    _delay_ms(5);
}

void recive_message(char *message)
{
    I2C_Start(Slave_Write_Address);
    I2C_Write(0x00);
    I2C_Repeated_Start(Slave_Read_Address);
    int i;
    char temp;
    for (i = 0; i < MESSAGE_LENGTH; i++)
    {
        if (i < MESSAGE_LENGTH - 1)
            temp = I2C_Read_Ack();
        else
            temp = I2C_Read_Nack();
        message[i] = temp;
    }
}
