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
// | 13          | PB5 |     |     |            |
// | A0          |     | PC0 |     | A0         |
// | A1          |     | PC1 |     | A1         |
// | A2          |     | PC2 |     | A2         |
// | A3          |     | PC3 |     | A3         |
// | A4          |     | PC4 |     | A4         |
// | A5          |     | PC5 |     | A5         |
// | XTAL1       | PB6 |     |     |            |
// | XTAL2       | PB7 |     |     |            |
// | RESET       |     | PC6 |     |            |


#define BV(bit)              (1 << bit)
#define setBit(byte, bit)    (byte |= BV(bit))
#define clearBit(byte, bit)  (byte &= ~BV(bit))
#define toggleBit(byte, bit) (byte ^= BV(bit))

int main (void)
{
    //          543210
    DDRB  = 0b00100000;  // defino PB5 como saida
    PORTB |= (1<<5);     // aplicamos 5V no pino PB5

    while (1)
        _delay_ms (2000);

    return 0;
}
