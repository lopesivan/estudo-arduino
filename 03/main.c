#include <avr/io.h>
#include <util/delay.h>

// -> Quero o pino 7 com 5V

// | Digital Pin | PB# | PC# | PD# | Analog Pin |
// | ----------- | --- | --- | --- | ---------- |
// | 0           |     |     | PD0 |            |
// | 1           |     |     | PD1 |            |
// | 2           |     |     | PD2 |            |
// | 3           |     |     | PD3 |            |
// | 4           |     |     | PD4 |            |
// | 5           |     |     | PD5 |            |
// | 6           |     |     | PD6 |            |
//*|*7***********|*****|*****|*PD7*|************|
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
    DDRD = BV (7);
    setBit (PORTD, 7);
    //           76543210
    // DDRD  = 0b10000000;  // defino PD7 como saida
    // PORTD |= (1<<5);     // aplicamos 5V no pino PD7

    while (1)
        _delay_ms (2000);

    return 0;
}
