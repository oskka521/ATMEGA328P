

#pragma once

#include <avr/io.h>
void I2C_Slave_Init(uint8_t slave_address);
int8_t I2C_Slave_Listen();
int8_t I2C_Slave_Transmit(char data);
char I2C_Slave_Receive();