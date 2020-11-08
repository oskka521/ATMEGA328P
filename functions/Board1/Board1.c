#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void light_RGB(char c);
void light_intro();

int main()
{
    DDRB |= (1 << DDB2) | (1 << DDB5);
    DDRD |= (1 << DDD2) | (1 << DDD3);

    light_intro();

    while (1)
    {

        PORTB ^= (1 << PORTB5);
    }
}

void light_intro()
{
    char lights[5] = {'A', 'r', 'g', 'b', 'Z'};
    int iterations = 5;
    int speed = 1000;
    int i;
    for (i = 0; i < iterations; i++)
    {
        light_RGB(lights[i]);
        _delay_ms(speed);
    }
}

void light_RGB(char c)
{
    if (c == 'g')
    {
        PORTD |= (1 << PORTD3);
        PORTD &= ~(1 << PORTD2);
        PORTB &= ~(1 << DDB2);
    }
    else if (c == 'b')
    {
        PORTD &= ~(1 << PORTD3);
        PORTD |= (1 << PORTD2);
        PORTB &= ~(1 << DDB2);
    }
    else if (c == 'r')
    {
        PORTD &= ~(1 << PORTD3);
        PORTD &= ~(1 << PORTD2);
        PORTB |= (1 << DDB2);
    }
    else if (c == 'Z')
    {
        PORTD &= ~(1 << PORTD3);
        PORTD &= ~(1 << PORTD2);
        PORTB &= ~(1 << DDB2);
    }
    else
    {
        PORTD |= (1 << PORTD3);
        PORTD |= (1 << PORTD2);
        PORTB |= (1 << DDB2);
    }
}
