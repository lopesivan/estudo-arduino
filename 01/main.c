#include <avr/io.h>
#include <util/delay.h>

#define LED 1
#define BUTTON 4
#define ON 1
#define OFF 0

#define BV(bit) (1 << bit)
#define setBit(byte, bit) (byte |= BV(bit))
#define clearBit(byte, bit) (byte &= ~BV(bit))
#define toggleBit(byte, bit) (byte ^= BV(bit))

int light = OFF;

int button_is_pushed (void)
{
    /* pushed=0 and not_pushed=1 */
    return ! (PINB & (1<<BUTTON));
}

/*
int light_up_led(void)
{

    return 0;
}

int light_down_led(void)
{

    return 0;
}
*/

int toogle_led()
{
    if (light == OFF)
    {
        PORTB ^= (1<<LED);
//                76543210
        PORTB = 0b00010010;
        light = ON;
    } else
    {
//                76543210
        PORTB = 0b00010010;
        light = OFF;
    }

    return 0;
}

int main (void)
{
//           76543210
    DDRB = 0b00000010;
//  DDRB = (1<<LED);

//            76543210
    PORTB = 0b00010000;
//  PORTB = (1<<BUTTON);
//
    while (1)
    {
        if (button_is_pushed)
        {
            toogle_led();
        }
    }

    return 0;
}
