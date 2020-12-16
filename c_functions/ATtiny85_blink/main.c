#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay_basic.h>
#define LED PB3
void delay_ms(uint16_t ms)
{
    while (ms > 0)
    {
        _delay_loop_2(F_CPU / 4000);
        ms--;
    }
}
int main(void)
{
    // Set Pin 2 (PB3) as an output pin.
    DDRB |= 1 << LED;
    while (1)
    {

        // Set pin 2 high.
        PORTB |= 1 << LED;
        delay_ms(1000);
        // Set pin 2 low.
        PORTB &= ~(1 << LED);
        delay_ms(1000);
    }
    return 0;
}