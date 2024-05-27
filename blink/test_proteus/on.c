#include <avr/io.h>

int on (volatile uint8_t* port, uint8_t mask)
{
    *port |= _BV (mask);

    return 0;
}
