#define F_CPU 16000000UL

#include "LCD/lcd.h"
#include "I2C/I2C_master.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UART/uart_utility_functions.h"

#define MESSAGE_LENGTH 8

void concat_number_to_string(char *char_p, int number);

int main(void)
{
    init_uart();
    char received[MESSAGE_LENGTH] = "";
    Set_Slave_Write_Address(0x20, 0x21);
    LCD_Init();
    I2C_Init();

    LCD_String_xy(0, 0, "Master Device");
    int num = 10;

    while (1)
    {
        char message[10] = "hello";
        concat_number_to_string(message, num);
        num++;

        LCD_String_xy(1, 0, "                       ");
        LCD_String_xy(1, 0, "S:");
        send_message(message, strlen(message));
        LCD_String_xy(1, 2, message);
        strcpy(message, "");
        _delay_ms(5000);

        LCD_String_xy(1, 0, "                       ");
        LCD_String_xy(1, 0, "R:");
        recive_message(received, MESSAGE_LENGTH);
        printf("sent =  ");
        LCD_String_xy(1, 2, received);

        _delay_ms(5000);

        I2C_Stop(); /* Stop I2C */
    }
    return 0;
}

void concat_number_to_string(char *char_p, int number)
{
    char snum[8];
    itoa(number, snum, 10);
    strcat(char_p, snum);
}
