#include <avr/io.h>
#include <avr/interrupt.h>

#define ADC_PRESCALER 128
#define TIMER1_PRESCALER 64
#define ZERO_CROSS_THRESHOLD 0.1
#define REF 2.5

#define setBit(byte, bit)    (byte |= _BV(bit))
#define clearBit(byte, bit)  (byte &= ~_BV(bit))
#define toggleBit(byte, bit) (byte ^= _BV(bit))

volatile uint16_t adc_value;
volatile float voltage;
volatile float ramp = 0.0;
volatile float ramp1 = 0.0;
volatile float ramp2 = 0.0;
volatile float delta = 5.0 / (60.0 * 1);

void adc_init (void)
{
    // Configura o ADC: usa AVcc como referência e define o prescaler
    ADMUX = (1 << REFS0); // Referência de tensão AVcc
    ADCSRA = (1 << ADEN) // Habilita o ADC
             | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler de 128
}

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

void timer1_init (void)
{
    // Configura o Timer1 para CTC mode
    TCCR1B |= (1 << WGM12); // Modo CTC (Clear Timer on Compare Match)
    OCR1A = (F_CPU / TIMER1_PRESCALER / 1) - 1; // Configura para 1 kHz
    TIMSK1 |= (1 << OCIE1A); // Habilita interrupção de comparação A
    TCCR1B |= (1 << CS11) | (1 << CS10); // Prescaler de 64
}

ISR (TIMER1_COMPA_vect)
{
    adc_value = adc_read (0); // Lê o valor do pino analógico A0
    voltage = adc_value * (5.0 / 1023.0); // Converte para tensão

    if (voltage >= 1.82)
    {
        ramp1 += delta;
        ramp2 = 0;
    }
    else
    {
        ramp2 += delta;
        ramp1 = 0;
    }

    ramp = ramp1+ramp2;

    if (ramp >5 )
        ramp = 0;

    // Controle do LED com base na rampa e referência
    if (ramp >= REF)
    {
        setBit (PORTB, PB5); // Liga o LED (5V no pino PB5)
    }
    else
    {
        clearBit (PORTB, PB5); // Desliga o LED (0V no pino PB5)
    }

}

int main (void)
{
    adc_init();
    timer1_init();
    sei(); // Habilita interrupções globais

    // Inicializa o pino PB5 como saída
    DDRB = (1 << PB5);

    while (1)
    {
        // O loop principal pode ser vazio, pois tudo é tratado na interrupção
    }

    return 0;
}
