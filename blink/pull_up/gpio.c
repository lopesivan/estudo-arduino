#include "gpio.h"
#include "configure.h"
#include "on.h"
#include "off.h"
#include "toggle.h"
#include "is_low.h"

#include <avr/io.h>

struct gpio
{
    uint8_t id;
    Address address;
};

#define MAX_NO_OF_GPIOS 2

static struct gpio objectPool[MAX_NO_OF_GPIOS];
static unsigned char numberOfObjects = 0;

gpio_ptr create_gpio (uint8_t id, const Address* address)
{
    gpio_ptr gpio = NULL;

    if (numberOfObjects < MAX_NO_OF_GPIOS)
    {
        gpio = &objectPool[numberOfObjects++];

        /* Initialize the object... */
        gpio->id      = id;
        gpio->address = *address;
    }

    return gpio;
}

/*
void destroygpio (gpio_ptr gpio)
{
     * Perform clean-up of the gpio internals, if necessary.
}
*/

int input (gpio_ptr gpio)
{
    off (gpio->address.ddr, gpio->id);

    return 0;
}

int output (gpio_ptr gpio)
{
    on (gpio->address.ddr, gpio->id);

    return 0;
}

int higt (gpio_ptr gpio)
{
    on (gpio->address.port, gpio->id);

    return 0;
}

int low (gpio_ptr gpio)
{
    off (gpio->address.port, gpio->id);

    return 0;
}

int pull_up (gpio_ptr gpio)
{
    input (gpio);   // 0
    higt  (gpio);   // 1

    return EXIT_SUCCESS;
}

bool is_pushed (gpio_ptr gpio)
{
    if (is_low (gpio->address.pin, gpio->id))
        return true;
    else
        return false;
}
