#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRB |= (1 << DDB5);

    while (1)
    {
        for (int i = 0; i < 5; i++)
        {
            PORTB ^= (1 << PORTB5);
            _delay_ms(i * 100);
        }

        //PORTB ^= (1 << PORTB5);
        //_delay_ms(500);
    }
}