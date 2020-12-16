/*
PIN D6 -> PD6 -> sound PWM
PIN D2 -> PD2 -> LED
PIN A4 -> PC4 ADC[4] -> BUTTOM
    PCINT12 -> Enable interrupt
    PCMSK1
    INTF1
*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "uart_utility_functions.h"

#define SOUND_PIN PD6
#define LED_PIN PD6
#define READ_PIN PC4

static int state = 0;

ISR(PCINT1_vect)
{
    if ((PINC & (1 << PINC4)))
    {
        printf("FL\r\n");
    }
    else
    {
        printf("RE\r\n");
        if (state == 0)
        {
            printf("ON\r\n");
            PORTD |= (1 << PORTD2);
            state = 1;
        }
        else
        {
            printf("OFF\r\n");
            PORTD &= ~(1 << PORTD2);
            state = 0;
        }
    }
}
int main(void)
{
    init_uart(); // initialization
    printf("System Booted, built %s on %s\r\n", __TIME__, __DATE__);

    DDRD |= (1 << DDD6);
    DDRD |= (1 << DDD2);
    DDRC &= ~(1 << DDC4);

    //hardware Interrupts
    EICRA |= (1 << ISC10);
    //EICRA &= ~(1 << ISC11);
    PCMSK1 |= (1 << PCINT12);
    PCICR |= (1 << PCIE1);

    // PORT D6's PWM
    TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
    //TIMSK0 = (1 << TOIE0);
    int dutyCycle = 0;
    OCR0A = (double)(dutyCycle / 100.0) * 255.0;

    TCCR0B = (1 << CS00) | (1 << CS02);

    //enable gobal intrrupts
    sei();

    while (1)
    {

        if (state == 1)
        {
            int r = rand() % 10;
            r = r * 10;
            OCR0A = (double)((r) / 100.0) * 255.0;
            printf("Hello Worlda -> PWM = %d \r\n", r);
        }
        else
        {

            OCR0A = 0.0;
            printf("Hello World -> PWM = %d \r\n", 0);
        }

        _delay_ms(200);
    }
}
