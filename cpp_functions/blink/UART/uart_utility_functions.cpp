#include "uart_utility_functions.h"

//FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
//FILE mystdin = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

/******************************************************************************
******************************************************************************/
int uart_putchar(char c, FILE *stream)
{
    if (c == '\n')
        uart_putchar('\r', stream);
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    return 0;
}
/******************************************************************************
******************************************************************************/
int uart_getchar(FILE *stream)
{
    /* Wait until data exists. */
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}
/******************************************************************************
******************************************************************************/
void uart_init(unsigned long int baud)
{
    unsigned int baudrate = F_CPU / (baud * 16UL) - 1;
    UBRR0H = (baudrate >> 8);                // shift the register right by 8 bits
    UBRR0L = baudrate;                       // set baud rate
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);   // enable receiver and transmitter
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); // 8bit data format

    //// with static FILE variable:
    // static FILE uart0fd;
    // fdev_setup_stream((&uart0fd), uart_putchar, NULL,  _FDEV_SETUP_WRITE);
    // stdout = &uart0fd;

    //// or directly by using dynamically allocated FILE struct:
    stdout = fdevopen(uart_putchar, NULL);
}