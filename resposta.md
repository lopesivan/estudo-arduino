Para capturar a onda senoidal de amplitude de 0V a 3V e
frequência de 60Hz, e gerar um sinal PWM de mesma frequência
e sincronizado, usando o ADC para amostrar a onda
senoidal e ajustar o ciclo de trabalho do PWM em conformidade.


### Código em C para Captura de Sinal e Geração de PWM

```c
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL // Define a frequência do microcontrolador (16 MHz)

volatile uint16_t adc_value = 0; // Variável global para armazenar o valor do ADC

// Função para inicializar o ADC
void adc_init(void) {
    // Seleciona a referência de voltagem AVcc e o canal ADC0
    ADMUX = (1 << REFS0);
    // Habilita o ADC e define o prescaler para 128 (16 MHz / 128 = 125 KHz)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    // Habilita interrupção do ADC
    ADCSRA |= (1 << ADIE);
    // Inicia a primeira conversão
    ADCSRA |= (1 << ADSC);
}

// Função para inicializar o PWM no Timer 1
void pwm_init(void) {
    // Configura o pino PB1 (OC1A / pino digital 9) como saída
    DDRB |= (1 << DDB1);
    // Configura o Timer 1 para modo Fast PWM com TOP em ICR1
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10); // Prescaler 1
    // Define o valor do TOP para gerar uma frequência de 60Hz
    ICR1 = 26666; // (16 MHz / (60 * 1)) - 1
}

// Função para iniciar uma conversão ADC
void start_adc_conversion(void) {
    ADCSRA |= (1 << ADSC);
}

// Interrupção de Conversão ADC Completa
ISR(ADC_vect) {
    adc_value = ADC; // Lê o valor do ADC
    // Atualiza o ciclo de trabalho do PWM com base no valor do ADC
    OCR1A = (uint16_t)(((uint32_t)adc_value * 26666) / 1023);
    // Inicia uma nova conversão ADC
    start_adc_conversion();
}

int main(void) {
    // Inicializa o ADC e o PWM
    adc_init();
    pwm_init();

    // Habilita interrupções globais
    sei();

    while (1) {
        // O loop principal está vazio porque todo o trabalho é feito na ISR
    }

    return 0;
}
```

### Explicação do Código

1. **Inicialização do ADC**:
   - A função `adc_init` configura o ADC para usar AVcc como referência e o canal ADC0 (pino A0).
   - Habilita interrupções ADC e inicia a primeira conversão.

2. **Inicialização do PWM**:
   - A função `pwm_init` configura o Timer 1 para operar em modo Fast PWM.
   - O valor de TOP (`ICR1`) é calculado para gerar uma frequência de 60Hz.
   - A frequência do PWM é definida por `ICR1 = (F_CPU / (prescaler * target frequency)) - 1`.

3. **Interrupção de Conversão ADC Completa**:
   - A ISR `ADC_vect` é chamada quando a conversão ADC é completada.
   - O valor do ADC é lido e usado para ajustar o ciclo de trabalho do PWM.
   - Uma nova conversão ADC é iniciada imediatamente.

4. **Loop Principal**:
   - O loop principal fica vazio, pois o trabalho é feito na ISR.

### Considerações

- O valor do ciclo de trabalho PWM (`OCR1A`) é atualizado
na ISR com base no valor do ADC. Isso sincroniza o sinal PWM
com a forma de onda capturada.
- Certifique-se de que a tensão da onda senoidal está na
faixa de 0V a 3V para evitar danos ao microcontrolador.
- Você pode ajustar o prescaler e o valor de TOP (`ICR1`)
conforme necessário para obter a frequência PWM desejada.

Este código capturará continuamente a onda senoidal no pino
A0, ajustará o ciclo de trabalho do PWM no pino digital 9
para corresponder ao valor lido, resultando em um sinal PWM
de 60Hz sincronizado com a onda senoidal.
