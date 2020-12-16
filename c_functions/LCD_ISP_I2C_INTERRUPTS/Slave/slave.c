#define F_CPU 16000000UL

#include "LCD/lcd.h"
#include "I2C/I2C_slave.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>

#define Slave_Address 0x20
#define MESSAGE_LENGTH 100

void send_message(char *message);
void recive_message(char *message);
void listen_I2C();

int main(void)
{

    char message[MESSAGE_LENGTH] = "WORLD";
    char received[MESSAGE_LENGTH] = {'0'};
    DDRB |= (1 << DDB5);
    PORTB |= (1 << PORTB5);

    PORTB |= (1 << PORTB5);

    LCD_Init();
    I2C_Slave_Init(Slave_Address);

    LCD_String_xy(0, 0, "Slave Device");
    TWCR |= (1 << TWIE);
    sei();
    _delay_ms(200);

    while (1)
    {
        //I2C_Slave_Init(Slave_Address);
        listen_I2C(received, message);
    }
    return 0;
}

ISR(TWI_vect)
{

    //
    PORTB ^= (1 << PORTB5);
    _delay_ms(250);
    PORTB ^= (1 << PORTB5);
    _delay_ms(250);
    PORTB ^= (1 << PORTB5);
    _delay_ms(250);
    PORTB ^= (1 << PORTB5);
    _delay_ms(250);
    TWCR = (0 << TWEN) | (1 << TWIE); // Acknowledge on any new requests.
}

void listen_I2C(char *received, char *message)
{
    cli();
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
        send_message(message);
        LCD_String_xy(1, 2, message);
        break;

    default:
        //PORTB ^= (1 << PORTB5);
        //_delay_ms(100);
        break;
    }
    sei();
    //TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT) | (1 << TWIE);
}

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
        Ack_status = I2C_Slave_Transmit(message[i]); /* Send data byte */
        i++;

    } while (Ack_status == 0);
}
