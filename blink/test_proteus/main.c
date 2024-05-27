#include <avr/io.h>
#include <util/delay.h>

#include "configure.h"
#include "gpio.h"

typedef int (*function) (gpio_ptr);

enum
LED { OFF, ON, CHANGE };

int main (void)
{
    Address B = PINX (B);

    gpio_ptr led = create_gpio (5, &B);

    output  (led);

    bool finished = false;

    while (!finished)
    {
        higt (led);
        _delay_ms(1000);

        low  (led);

        _delay_ms(1000);
    }

    return EXIT_SUCCESS;
}

