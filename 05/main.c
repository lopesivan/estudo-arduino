#include <avr/io.h>
#include <avr/interrupt.h>
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
//*|*9***********|*PB1*|*****|*****|************|
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


volatile uint16_t adc_value = 0; // Variável global para armazenar o valor do ADC

// Função para inicializar o ADC
void adc_init (void)
{
    // Seleciona a referência de voltagem externa (3.3V) e o canal ADC0
    ADMUX = (1 << REFS0);
    // Habilita o ADC e define o prescaler para 128 (16 MHz / 128 = 125 KHz)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    // Habilita interrupção do ADC
    ADCSRA |= (1 << ADIE);
    // Inicia a primeira conversão
    ADCSRA |= (1 << ADSC);
}

// Função para inicializar o PWM no Timer 1
void pwm_init (void)
{
    // Configura o pino PB1 (OC1A / pino digital 9) como saída
    DDRB |= (1 << DDB1);
    // Configura o Timer 1 para modo Fast PWM com TOP em ICR1
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10); // Prescaler 1
    // Define o valor do TOP para gerar uma frequência de 60Hz
    ICR1 = 26666; // (16 MHz / (60 * 1)) - 1
}

// Função para iniciar uma conversão ADC
void start_adc_conversion (void)
{
    ADCSRA |= (1 << ADSC);
}

// Interrupção de Conversão ADC Completa
ISR (ADC_vect)
{
    adc_value = ADC; // Lê o valor do ADC
    // Atualiza o ciclo de trabalho do PWM com base no valor do ADC
    // Ajuste proporcional para 0-3.3V correspondendo a 0-100% ciclo de trabalho
    OCR1A = (uint16_t) (((uint32_t)adc_value * 26666) / 1023);
    // Inicia uma nova conversão ADC
    start_adc_conversion();
}

int main (void)
{
    // Inicializa o ADC e o PWM
    adc_init();
    pwm_init();

    // Habilita interrupções globais
    sei();

    while (1)
    {
        // O loop principal está vazio porque todo o trabalho é feito na ISR
    }

    return 0;
}
