#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

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

#define setBit(byte, bit)    (byte |= _BV(bit))
#define clearBit(byte, bit)  (byte &= ~_BV(bit))
#define toggleBit(byte, bit) (byte ^= _BV(bit))

ISR (INT0_vect)
{
    // Alterna o estado do LED no pino 13
    toggleBit (PORTB, PORTB5);
}

void loop()
{
    // O loop principal fica vazio, pois a ação é tratada pela interrupção
}

int main (void)
{
    // Configura o pino 13 como saída
    //DDRB |= (1 << DDB5);
    setBit (DDRB, DDB5);

    // Configura o temporizador 1 para gerar uma interrupção a cada 1 segundo
    setBit (TCCR1B, WGM12); // Modo CTC

    OCR1A = 15624;           // Valor de comparação para 1 Hz (prescaler 1024)
    setBit (TIMSK1, OCIE1A); // Habilita interrupção de comparação A
    TCCR1B |= _BV (CS12) | _BV (CS10); // Prescaler 1024

    // Habilita interrupções globais
    sei();

    while (1)
    {
        loop();
    }

    return EXIT_SUCCESS;
}
