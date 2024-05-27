#include <avr/io.h>

int is_low (volatile uint8_t* pin, uint8_t mask)
{
    if (*pin & _BV (mask))
        return 0;

    return 1;
}
