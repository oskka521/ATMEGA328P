#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h> //UART
#include <avr/interrupt.h>
#include "uart_utility_functions.h"

int main(void)
{
    init_uart(); // initialization
    printf("System Booted, built %s on %s\n", __TIME__, __DATE__);
    while (1)
    {
        printf("Hello There. What is your name?\r\n");
        _delay_ms(1000);
    }
}