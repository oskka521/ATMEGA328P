
#pragma once
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

int uart_putchar(char c, FILE *stream);
int uart_getchar(FILE *stream);
void uart_init(unsigned long int baud);
