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
// | 7           |     |     | PD7 |            |
// | 8           | PB0 |     |     |            |
// | 9           | PB1 |     |     |            |
// | 10          | PB2 |     |     |            |
// | 11          | PB3 |     |     |            |
// | 12          | PB4 |     |     |            |
// | 13          | PB5 |     |     |            |
//*|*A0**********|*****|*PC0*|*****|*A0*********|
// | A1          |     | PC1 |     | A1         |
// | A2          |     | PC2 |     | A2         |
// | A3          |     | PC3 |     | A3         |
// | A4          |     | PC4 |     | A4         |
// | A5          |     | PC5 |     | A5         |
// | XTAL1       | PB6 |     |     |            |
// | XTAL2       | PB7 |     |     |            |
// | RESET       |     | PC6 |     |            |


// Função para iniciar o ADC
void adc_init (void)
{
    // Seleciona a referência de voltagem AVcc e o canal ADC0
    ADMUX = (1 << REFS0);
    // Habilita o ADC e define o prescaler para 128 (16 MHz / 128 = 125 KHz)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

// Função para ler um valor do ADC
uint16_t adc_read (uint8_t ch)
{
    // Seleciona o canal do ADC (ch deve estar entre 0 e 7)
    ch &= 0b00000111;
    ADMUX = (ADMUX & 0xF8) | ch;

    // Inicia a conversão ADC
    ADCSRA |= (1 << ADSC);

    // Espera a conversão terminar
    while (ADCSRA & (1 << ADSC));

    // Retorna o valor lido
    return (ADC);
}

int main (void)
{
    uint16_t sensorValue;

    // Configura o pino PB5 (pino digital 13) como saída
    DDRB |= (1 << DDB5);

    // Inicializa o ADC
    adc_init();

    while (1)
    {
        // Lê o valor do sensor no pino A0 (PC0)
        sensorValue = adc_read (0);

        // Liga o LED no pino PB5 (pino digital 13)
        PORTB |= (1 << PORTB5);

        // Espera por sensorValue milissegundos
        for (uint16_t i = 0; i < sensorValue; i++)
        {
            _delay_ms (1);
        }

        // Desliga o LED no pino PB5 (pino digital 13)
        PORTB &= ~ (1 << PORTB5);

        // Espera por sensorValue milissegundos
        for (uint16_t i = 0; i < sensorValue; i++)
        {
            _delay_ms (1);
        }
    }

    return 0;
}
