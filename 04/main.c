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
    // TCNT1 = 0xEBA7;    // 3s
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
    TCNT1 = 0xC2F7;  //1s
    // TCNT1 = 0xEBA7;    // 3s

    // > 65536 - (16E6/ (1024));
    // 49911.00000

    // > 65536 - (16E6/ (1024*1));
    // 49911.00000

    // > 65536 - (16E6/ (1024*2));
    // 57723.50000

    // > 65536 - (16E6/ (1024*3));
    // 60327.66667
    // 60327 -> 0xeba7
    //
    // > 65536 - (16E6/ (1024*4));
    // 61629.75000



    // Nesse exemplo o timer foi configurado para modo
    // normal, com pinos OC1A e OC1B desconectados (TCCR1A =
    // 0). Foi selecionado o prescaler para 1024 através
    // do registrador TCCR1B.  Para que o timer estoure a
    // cada segundo é necessário iniciar seu valor com a
    // diferença entre o seu valor máximo (65536) e o período
    // desejado. O período é calculado levando em consideração
    // a frequência do oscilador e o prescaler selecionado,
    // além da frequência de interrupção desejada. Por
    // fim foi habilitada a interrupção de estouro do TIMER1
    // através do bit T0IE1 do registrador TIMSK1. A inversão
    // do LED é feita na rotina de interrupção, note que é
    // necessário recarregar o timer para a correta contagem.

    TIMSK1 |= (1 << TOIE1);           // habilita a interrupção do TIMER1

    // Habilita interrupções globais
    sei();

    while (1)
    {
        loop();
    }

    return EXIT_SUCCESS;
}
