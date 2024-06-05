#include <avr/io.h>
#include <avr/interrupt.h>

#define ADC_PRESCALER 128
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define TIMER1_PRESCALER 64
#define REF 2.5

#define setBit(byte, bit)    (byte |= _BV(bit))
#define clearBit(byte, bit)  (byte &= ~_BV(bit))
#define toggleBit(byte, bit) (byte ^= _BV(bit))

volatile uint16_t adc_value;
volatile float voltage;
volatile float ramp = 0.0;
volatile float ramp1 = 0.0;
volatile float ramp2 = 0.0;
volatile float delta = .5;

void usart_init (unsigned int ubrr)
{
    // Configura a taxa de transmissão
    UBRR0H = (unsigned char) (ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    // Habilita o transmissor
    UCSR0B = (1 << TXEN0);
    // Define o formato da trama: 8 bits de dados, 1 bit de parada
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void usart_transmit (unsigned char data)
{
    // Aguarda até o buffer de transmissão estar vazio
    while (! (UCSR0A & (1 << UDRE0)));
    // Envia o dado
    UDR0 = data;
}

void usart_print (const char* str)
{
    while (*str)
    {
        usart_transmit (*str++);
    }
}

void usart_println (const char* str)
{
    usart_print (str);
    usart_transmit ('\r');
    usart_transmit ('\n');
}

void usart_print_float (float value)
{
    char buffer[20];
    dtostrf (value, 6, 2, buffer);
    usart_print (buffer);
}

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
    OCR1A = (F_CPU / TIMER1_PRESCALER / .0167) - 1; // Configura para 1 kHz
    TIMSK1 |= (1 << OCIE1A); // Habilita interrupção de comparação A
    TCCR1B |= (1 << CS11) | (1 << CS10); // Prescaler de 64
}

ISR (TIMER1_COMPA_vect)
{
    adc_value = adc_read (0); // Lê o valor do pino analógico A0
    voltage = adc_value * (5.0 / 1023.0); // Converte para tensão

    if (voltage >= 1.82)
    {
        ramp += delta;
    }

    usart_print_float (ramp);
    usart_println ("");
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
    usart_init (MYUBRR);
    sei(); // Habilita interrupções globais

    // Inicializa o pino PB5 como saída
    DDRB = (1 << PB5);

    while (1)
    {
        // O loop principal pode ser vazio, pois tudo é tratado na interrupção
    }

    return 0;
}
