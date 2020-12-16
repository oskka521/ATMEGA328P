#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "UART/uart_utility_functions.h"

class Room
{

public:
    int length;
    double breadth;

    double calculateArea()
    {
        return (double)length * breadth;
    }
};

int main()
{
    uart_init(9600U);
    DDRB |= (1 << DDB5);
    Room room1;
    room1.length = 42;
    room1.breadth = 30.8;

    while (1)
    {
        printf("hello -> %d\n", room1.length);
        printf("world -> %lf\n", room1.breadth);
        for (int i = 0; i < 5; i++)
        {
            PORTB ^= (1 << PORTB5);
            _delay_ms(i * 100);
        }

        //PORTB ^= (1 << PORTB5);
        //_delay_ms(500);
    }
}