#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> //dutycucle

double dutyCycle = 0;

int main(void)
{
    DDRD = (1 << PORTD6);

    TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01); //PWM setup, now fast PWM
    TIMSK0 = (1 << TOIE0);                                //timer comp, not needed, only for IR.

    OCR0A = (dutyCycle / 100.0) * 255.0;

    sei();

    TCCR0B = (1 << CS00) | (1 << CS02); //how fast, prescalar

    while (1)
    {

        _delay_ms(100);

        dutyCycle += 10;
        OCR0A = (dutyCycle / 100.0) * 255.0;

        if (dutyCycle > 100)
        {
            dutyCycle = 0;
        }
    }
}

ISR(TIMER0_OVF_vect) //overflow comp
{
    //OCR0A = (dutyCycle / 100.0) * 255;
}
