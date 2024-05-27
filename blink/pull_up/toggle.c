#include <avr/io.h>

int toggle (volatile uint8_t* port, uint8_t mask)
{
    *port ^= _BV (mask);

    return 0;
}
