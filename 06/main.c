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

#define ADC_PRESCALER 128

#define setBit(byte, bit)    (byte |= _BV(bit))
#define clearBit(byte, bit)  (byte &= ~_BV(bit))
#define toggleBit(byte, bit) (byte ^= _BV(bit))

uint16_t adc_read (uint8_t channel)
{
    // Seleciona o canal do ADC (deve estar entre 0 e 7)
    channel &= 0x07;
    ADMUX = (ADMUX & 0xF8) | channel;

    // Inicia a conversão
    ADCSRA |= (1 << ADSC);

    // Aguarda a conclusão da conversão
    while (ADCSRA & (1 << ADSC));

    // Retorna o valor lido (ADC é um registrador que combina ADCL e ADCH)
    return ADC;
}

int main (void)
{
    // Seleciona a referência de voltagem AVcc e o canal ADC0
    ADMUX = (1 << REFS0);

    // Habilita o ADC e define o prescaler para 128 (16 MHz / 128 = 125 KHz)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    //                     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //                     Prescaler de 128

    uint16_t adc_value;
    float voltage;

    while (1)
    {
        adc_value = adc_read (0); // Lê o valor do pino analógico A0
        voltage = adc_value * (5.0 / 1023.0); // Converte para tensão

        _delay_ms (1); // Ajusta a taxa de amostragem para 1 ms (~1 kHz)
    }
    return EXIT_SUCCESS;
}
