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

ISR (TIMER1_COMPA_vect)
{
    TCNT1 = 0xC2F7;                                 // Renicia TIMER
    // Alterna o estado do LED no pino 13
    toggleBit (PORTB, PORTB5);
}

void loop()
{
    // O loop principal fica vazio, pois a ação é tratada pela interrupção
}

int main (void)
{
    // Utilizando o TIMER1  no Arduino
    // Modo Normal com interrupção por overflow
    // O exemplo a seguir exibe como piscar o LED no pino 13,
    // da placa Arduino UNO, em intervalos de 1 segundo e utilizando
    // interrupção por estouro timer:

    // Configuração do timer1
    TCCR1A = 0;                        //confira timer para operação normal pinos OC1A e OC1B desconectados
    TCCR1B = 0;                        //limpa registrador
    TCCR1B |= (1<<CS10)| (1 << CS12);  // configura prescaler para 1024: CS12 = 1 e CS10 = 1

    // incia timer com valor para que estouro ocorra em 1 segundo
    // 65536-(16MHz/1024/1Hz) = 49911 = 0xC2F7
    TCNT1 = 0xC2F7;

    TIMSK1 |= (1 << TOIE1);           // habilita a interrupção do TIMER1

    // Habilita interrupções globais
    sei();

    while (1)
    {
        loop();
    }

    return EXIT_SUCCESS;
}
