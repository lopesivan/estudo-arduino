#include <avr/io.h>
#include <util/delay.h>

#include "configure.h"
#include "gpio.h"

typedef int (*function) (gpio_ptr);

enum
LED { OFF, ON, CHANGE };

int main (void)
{
    Address B = PINX(B),
            D = PINX(D);

    gpio_ptr led = create_gpio (5, &B),
             btn = create_gpio (7, &D);

    output  (led);
    pull_up (btn);

    bool finished = false;

    enum
    LED      light  = OFF;

    enum
    LED      last   = OFF;

    while (!finished)
    {
        if (is_pushed(btn))
        {
            last  = light;
            light = CHANGE;
        }

        if (light == CHANGE)
        {
            if (last == OFF)
            {
                higt (led);
                light = ON;
            }

            else
            {
                low (led);
                light = OFF;
            }
        }

    }

    return EXIT_SUCCESS;
}

