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


// #define BV(bit)              (1 << bit)
#define setBit(byte, bit)    (byte |= _BV(bit))
#define clearBit(byte, bit)  (byte &= ~_BV(bit))
#define toggleBit(byte, bit) (byte ^= _BV(bit))

#define LED_PIN PB5 // Define o pino do LED como PB5 (pino 13 no Arduino)

int main (void)
{

    // Configura o pino PB5 como saída
    //DDRB |= (1 << LED_PIN);
    setBit (DDRB, LED_PIN);
    while (1)
    {
        // Liga o LED
        //PORTB |= (1 << LED_PIN);
        setBit (PORTB, LED_PIN);
        _delay_ms (1000); // Espera por 1000 milissegundos

        // Desliga o LED
        // PORTB &= ~ (1 << LED_PIN);
        toggleBit (PORTB, LED_PIN);
        _delay_ms (1000); // Espera por 1000 milissegundos
    }

    return 0;
}
