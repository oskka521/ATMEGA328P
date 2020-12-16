#define F_CPU 16000000UL

#include "LCD/lcd.h"
#include "I2C/I2C_slave.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UART/uart_utility_functions.h"
#define Slave_Address 0x20
#define MESSAGE_LENGTH 100

//void send_message(char *message);
//void recive_message(char *message);
void listen_I2C();

int main(void)
{

    char message[MESSAGE_LENGTH] = "SLAVE";
    char received[MESSAGE_LENGTH] = {'0'};

    init_uart();
    LCD_Init();
    I2C_Slave_Init(Slave_Address);

    LCD_String_xy(0, 0, "Slave Device");

    while (1)
    {
        printf("System Booted, built %s on %s\r\n", __TIME__, __DATE__);
        listen_I2C(received, message);
    }
    return 0;
}

void listen_I2C(char *received, char *message)
{
    switch (I2C_Slave_Listen())
    {
    case 0:
        LCD_String_xy(1, 0, "                       ");
        LCD_String_xy(1, 0, "R:");
        recive_message(received);
        LCD_String_xy(1, 2, received);
        break;
    case 1:
        LCD_String_xy(1, 0, "                       ");
        LCD_String_xy(1, 0, "S:");
        send_message(message, 10);
        LCD_String_xy(1, 2, message);
        break;
    default:
        break;
    }
}
/*
void recive_message(char *received)
{
    int8_t data = 0;
    int i = 0;
    char temp;
    while (data != -1)
    {
        data = I2C_Slave_Receive();
        if (data != -1)
        {
            temp = (char)data;
            received[i] = temp;
            i++;
        }
    }
}

void send_message(char *message)
{
    int8_t Ack_status;
    int i = 0;
    do
    {
        Ack_status = I2C_Slave_Transmit(message[i]); 
        i++;

    } while (Ack_status == 0);
}
*/