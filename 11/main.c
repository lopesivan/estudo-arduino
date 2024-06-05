#include <avr/io.h>
#include <util/delay.h>

#define ADC_PRESCALER 128
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define REF 2

#define setBit(byte, bit)    (byte |= _BV(bit))
#define clearBit(byte, bit)  (byte &= ~_BV(bit))
#define toggleBit(byte, bit) (byte ^= _BV(bit))

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

int main (void)
{
    adc_init();
    usart_init (MYUBRR);

    uint16_t adc_value;
    float voltage;

    float medio = 0.0;
    float rampa1 = 0.0;
    float rampa2 = 0.0;
    float rampa = 0.0;
    float delta = 0;
    float max = 0;
    float min = 5; // Inicializa com o valor máximo possível para uma leitura de 0-5V

    while (1)
    {
        adc_value = adc_read (0); // Lê o valor do pino analógico A0
        voltage = adc_value * (5.0 / 1023.0); // Converte para tensão

        // Atualiza os valores máximos e mínimos
        if (voltage > max)
        {
            max = voltage;
        }

        if (voltage < min)
        {
            min = voltage;
        }

        medio = (max + min)/2;
        delta = medio/1000;

        if (voltage >= medio)
        {
            rampa1 = rampa1 + delta;
            rampa2= 0;
        }
        else
        {
            rampa1=0;
            rampa2 = rampa2 + delta;
        }

        rampa = rampa1 + rampa2;

        usart_print_float (rampa);
        usart_println ("");
        // Controle do LED com base na rampa e referência
        if (rampa >= REF)
        {
            setBit (PORTB, PB5); // Liga o LED (5V no pino PB5)
        }
        else
        {
            clearBit (PORTB, PB5); // Desliga o LED (0V no pino PB5)
        }

        _delay_ms (1); // Ajusta a taxa de amostragem para 1 ms (~1 kHz)
    }
}
