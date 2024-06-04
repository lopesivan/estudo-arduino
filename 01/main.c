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
    //PORTB ^= (1 << PB5);
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

    // Configura o pino 2 (INT0) como entrada
    //DDRD &= ~ (1 << DDD2);
    clearBit (DDRD, DDD5);

    // Habilita a interrupção externa INT0
    // EIMSK |= (1 << INT0);
    setBit (EIMSK, INT0);

    // Configura a interrupção para disparar na borda de descida
    // EICRA |= (1 << ISC01);
    // EICRA &= ~ (1 << ISC00);
    setBit (EICRA, ISC01);
    clearBit (EICRA, ISC00);

    // ***********************************************************************

    // - **Nível baixo:**

    //   ```c
    //   clearBit(EICRA, ISC01);
    //   clearBit(EICRA, ISC00);
    //   ```

    // - **Qualquer mudança de nível:**

    //   ```c
    //   clearBit(EICRA, ISC01);
    //   setBit(EICRA, ISC00);
    //   ```

    // - **Borda de descida:**

    //   ```c
    //   setBit(EICRA, ISC01);
    //   clearBit(EICRA, ISC00);
    //   ```

    // - **Borda de subida:**
    //   ```c
    //   setBit(EICRA, ISC01);
    //   setBit(EICRA, ISC00);
    //   ```

    // Habilita interrupções globais
    sei();

    while (1)
    {
        loop();
    }

    return EXIT_SUCCESS;
}
