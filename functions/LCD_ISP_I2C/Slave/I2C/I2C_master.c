#include "I2C_master.h"

static uint8_t Slave_Write_Address = 0x00;
static uint8_t Slave_Read_Address = 0x00;

void I2C_Init() /* I2C initialize function */
{
    TWBR = BITRATE(TWSR = 0x00); /* Get bit rate register value by formula */
}

uint8_t I2C_Start(char write_address) /* I2C start function */
{
    uint8_t status;                                   /* Declare variable */
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); /* Enable TWI, generate start condition and clear interrupt flag */
    while (!(TWCR & (1 << TWINT)))
        ;                              /* Wait until TWI finish its current job (start condition) */
    status = TWSR & 0xF8;              /* Read TWI status register with masking lower three bits */
    if (status != 0x08)                /* Check weather start condition transmitted successfully or not? */
        return 0;                      /* If not then return 0 to indicate start condition fail */
    TWDR = write_address;              /* If yes then write SLA+W in TWI data register */
    TWCR = (1 << TWEN) | (1 << TWINT); /* Enable TWI and clear interrupt flag */
    while (!(TWCR & (1 << TWINT)))
        ;                 /* Wait until TWI finish its current job (Write operation) */
    status = TWSR & 0xF8; /* Read TWI status register with masking lower three bits */
    if (status == 0x18)   /* Check weather SLA+W transmitted & ack received or not? */
        return 1;         /* If yes then return 1 to indicate ack received i.e. ready to accept data byte */
    if (status == 0x20)   /* Check weather SLA+W transmitted & nack received or not? */
        return 2;         /* If yes then return 2 to indicate nack received i.e. device is busy */
    else
        return 3; /* Else return 3 to indicate SLA+W failed */
}

uint8_t I2C_Repeated_Start(char read_address) /* I2C repeated start function */
{
    uint8_t status;                                   /* Declare variable */
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); /* Enable TWI, generate start condition and clear interrupt flag */
    while (!(TWCR & (1 << TWINT)))
        ;                              /* Wait until TWI finish its current job (start condition) */
    status = TWSR & 0xF8;              /* Read TWI status register with masking lower three bits */
    if (status != 0x10)                /* Check weather repeated start condition transmitted successfully or not? */
        return 0;                      /* If no then return 0 to indicate repeated start condition fail */
    TWDR = read_address;               /* If yes then write SLA+R in TWI data register */
    TWCR = (1 << TWEN) | (1 << TWINT); /* Enable TWI and clear interrupt flag */
    while (!(TWCR & (1 << TWINT)))
        ;                 /* Wait until TWI finish its current job (Write operation) */
    status = TWSR & 0xF8; /* Read TWI status register with masking lower three bits */
    if (status == 0x40)   /* Check weather SLA+R transmitted & ack received or not? */
        return 1;         /* If yes then return 1 to indicate ack received */
    if (status == 0x20)   /* Check weather SLA+R transmitted & nack received or not? */
        return 2;         /* If yes then return 2 to indicate nack received i.e. device is busy */
    else
        return 3; /* Else return 3 to indicate SLA+W failed */
}

void I2C_Stop() /* I2C stop function */
{
    TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN); /* Enable TWI, generate stop condition and clear interrupt flag */
    while (TWCR & (1 << TWSTO))
        ; /* Wait until stop condition execution */
}

void I2C_Start_Wait(char write_address) /* I2C start wait function */
{
    uint8_t status; /* Declare variable */
    while (1)
    {
        TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); /* Enable TWI, generate start condition and clear interrupt flag */
        while (!(TWCR & (1 << TWINT)))
            ;                              /* Wait until TWI finish its current job (start condition) */
        status = TWSR & 0xF8;              /* Read TWI status register with masking lower three bits */
        if (status != 0x08)                /* Check weather start condition transmitted successfully or not? */
            continue;                      /* If no then continue with start loop again */
        TWDR = write_address;              /* If yes then write SLA+W in TWI data register */
        TWCR = (1 << TWEN) | (1 << TWINT); /* Enable TWI and clear interrupt flag */
        while (!(TWCR & (1 << TWINT)))
            ;                 /* Wait until TWI finish its current job (Write operation) */
        status = TWSR & 0xF8; /* Read TWI status register with masking lower three bits */
        if (status != 0x18)   /* Check weather SLA+W transmitted & ack received or not? */
        {
            I2C_Stop(); /* If not then generate stop condition */
            continue;   /* continue with start loop again */
        }
        break; /* If yes then break loop */
    }
}

uint8_t I2C_Write(char data) /* I2C write function */
{
    uint8_t status;                    /* Declare variable */
    TWDR = data;                       /* Copy data in TWI data register */
    TWCR = (1 << TWEN) | (1 << TWINT); /* Enable TWI and clear interrupt flag */
    while (!(TWCR & (1 << TWINT)))
        ;                 /* Wait until TWI finish its current job (Write operation) */
    status = TWSR & 0xF8; /* Read TWI status register with masking lower three bits */
    if (status == 0x28)   /* Check weather data transmitted & ack received or not? */
        return 0;         /* If yes then return 0 to indicate ack received */
    if (status == 0x30)   /* Check weather data transmitted & nack received or not? */
        return 1;         /* If yes then return 1 to indicate nack received */
    else
        return 2; /* Else return 2 to indicate data transmission failed */
}

char I2C_Read_Ack() /* I2C read ack function */
{
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); /* Enable TWI, generation of ack and clear interrupt flag */
    while (!(TWCR & (1 << TWINT)))
        ;        /* Wait until TWI finish its current job (read operation) */
    return TWDR; /* Return received data */
}

char I2C_Read_Nack() /* I2C read nack function */
{
    TWCR = (1 << TWEN) | (1 << TWINT); /* Enable TWI and clear interrupt flag */
    while (!(TWCR & (1 << TWINT)))
        ;        /* Wait until TWI finish its current job (read operation) */
    return TWDR; /* Return received data */
}
void Set_Slave_Write_Address(uint8_t write_address, uint8_t read_address)
{
    Slave_Write_Address = write_address;
    Slave_Read_Address = read_address;
}

void send_message(char *message, int length)
{
    I2C_Start_Wait(Slave_Write_Address);
    _delay_ms(5);
    int i;
    for (i = 0; i < length; i++)
    {
        I2C_Write(message[i]);
        _delay_ms(5);
    }
    I2C_Stop();
    _delay_ms(5);
}

void recive_message(char *message, int length)
{
    I2C_Start(Slave_Write_Address);
    I2C_Write(0x00);
    I2C_Repeated_Start(Slave_Read_Address);
    int i;
    char temp;
    for (i = 0; i < length; i++)
    {
        if (i < length - 1)
            temp = I2C_Read_Ack();
        else
            temp = I2C_Read_Nack();
        message[i] = temp;
    }
}
