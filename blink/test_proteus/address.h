#ifndef ADDRESS_H
#define ADDRESS_H

#include <avr/io.h>

typedef struct
{
    volatile uint8_t* ddr;
    volatile uint8_t* port;
    volatile uint8_t* pin;
} Address;

#endif
