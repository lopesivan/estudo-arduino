#include <avr/io.h>
#include <util/delay.h>

// -> Quero o pino 13 com 5V

// | Digital Pin | PB# | PC# | PD# | Analog Pin |
// | ----------- | --- | --- | --- | ---------- |
// | 0           |     |     | PD0 |            |
// | 1           |     |     | PD1 |            |
// | 2           |     |     | PD2 |            |
// | 3           |     |     | PD3 |            |
// | 4           |     |     | PD4 |            |
// | 5           |     |     | PD5 |            |
// | 6           |     |     | PD6 |            |
// | 7           |     |     | PD7 |            |
// | 8           | PB0 |     |     |            |
// | 9           | PB1 |     |     |            |
// | 10          | PB2 |     |     |            |
// | 11          | PB3 |     |     |            |
// | 12          | PB4 |     |     |            |
//*|*13**********|*PB5*|*****|*****|************|
// | A0          |     | PC0 |     | A0         |
// | A1          |     | PC1 |     | A1         |
// | A2          |     | PC2 |     | A2         |
// | A3          |     | PC3 |     | A3         |
// | A4          |     | PC4 |     | A4         |
// | A5          |     | PC5 |     | A5         |
// | XTAL1       | PB6 |     |     |            |
// | XTAL2       | PB7 |     |     |            |
// | RESET       |     | PC6 |     |            |

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define NULL 0

enum _bool
{
    false = 0,
    true  = 1
};

typedef enum _bool bool;

typedef volatile uint8_t* address;

#define PORTX(led, X, num) do { \
    led.address = &DDR##X;      \
    led.id_addr = DD##X##num;   \
    led.port    = &PORT##X;     \
    led.id_port = PORT##X##num; \
} while(0)

struct gpio_t
{
    address  address;
    uint8_t  id_addr;
    address  port;
    uint8_t  id_port;
};

typedef struct gpio_t gpio;


int output   (address port, uint8_t mask);
int turn_on  (address port, uint8_t mask);
int turn_off (address port, uint8_t mask);

typedef int (*function) (address, uint8_t);

enum
{
    BLINK_DELAY_MS = 1000,
};

int main (void)
{
    function f = NULL;

    gpio fonte;

    PORTX (fonte, B, 5);

    f = output;
    f (fonte.address, fonte.id_addr);

    bool finished = false;

    f = turn_on;
    f (fonte.port, fonte.id_port);

    while (!finished)
    {
        _delay_ms (BLINK_DELAY_MS);
    }

    return EXIT_SUCCESS;
}


int output (address port, uint8_t mask)
{
    *port |= _BV (mask);

    return 0;
}

int turn_on (address port, uint8_t mask)
{
    output (port, mask);

    return 0;
}

int turn_off (address port, uint8_t mask)
{
    *port &= ~ _BV (mask);

    return 0;
}
