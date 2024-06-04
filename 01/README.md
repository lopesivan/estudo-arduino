Para aprender a usar interrupções no Arduino usando a
linguagem C, vou fornecer exemplos básicos e explicações. As
interrupções permitem que o Arduino responda a eventos
externos quase imediatamente, interrompendo a execução
normal do código. Aqui está um exemplo básico de como
configurar e usar uma interrupção externa no Arduino.

### Exemplo 1: Interrupção Externa

Este exemplo mostra como configurar uma interrupção externa
no pino digital 2 (INT0) para alternar o estado de um LED no
pino 13.

```c
#include <avr/io.h>
#include <avr/interrupt.h>

void setup() {
    // Configura o pino 13 como saída
    DDRB |= (1 << DDB5);

    // Configura o pino 2 (INT0) como entrada
    DDRD &= ~(1 << DDD2);

    // Habilita a interrupção externa INT0
    EIMSK |= (1 << INT0);

    // Configura a interrupção para disparar na borda de descida
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);

    // Habilita interrupções globais
    sei();
}

ISR(INT0_vect) {
    // Alterna o estado do LED no pino 13
    PORTB ^= (1 << PORTB5);
}

void loop() {
    // O loop principal fica vazio, pois a ação é tratada pela interrupção
}

int main(void) {
    setup();
    while (1) {
        loop();
    }
}
```

### Explicação do Código

1. **Configuração do Pino 13 como Saída:** Configuramos
   o pino 13, que é o pino do LED embutido no Arduino, como
   saída usando o registrador `DDRB`.

2. **Configuração do Pino 2 como Entrada:** Configuramos o
   pino 2 (INT0) como entrada. Esse é o pino que usaremos para
   a interrupção externa.

3. **Habilitação da Interrupção Externa INT0:** Habilitamos
   a interrupção externa para o pino 2 ajustando o bit `INT0`
   no registrador `EIMSK`.

4. **Configuração da Sensibilidade da Interrupção:**
   Configuramos a interrupção para disparar na borda de descida
   (quando o sinal passa de alto para baixo) ajustando os bits
   `ISC01` e `ISC00` no registrador `EICRA`.

5. **Habilitação de Interrupções Globais:** Chamamos a
   função `sei()` para habilitar interrupções globais.

6. **Manipulador de Interrupção (ISR):** A função
   `ISR(INT0_vect)` é chamada sempre que a interrupção INT0
   é disparada. Neste exemplo, alternamos o estado do LED no
   pino 13.

7. **Loop Principal:** O loop principal do programa fica vazio,
   pois a ação é tratada pela interrupção.

### Exemplo 2: Interrupção de Temporizador

Este exemplo mostra como configurar um temporizador para
gerar uma interrupção a cada segundo.

```c
#include <avr/io.h>
#include <avr/interrupt.h>

void setup() {
    // Configura o pino 13 como saída
    DDRB |= (1 << DDB5);

    // Configura o temporizador 1 para gerar uma interrupção a cada 1 segundo
    TCCR1B |= (1 << WGM12); // Modo CTC
    OCR1A = 15624; // Valor de comparação para 1 Hz (prescaler 1024)
    TIMSK1 |= (1 << OCIE1A); // Habilita interrupção de comparação A
    TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024

    // Habilita interrupções globais
    sei();
}

ISR(TIMER1_COMPA_vect) {
    // Alterna o estado do LED no pino 13
    PORTB ^= (1 << PORTB5);
}

void loop() {
    // O loop principal fica vazio, pois a ação é tratada pela interrupção
}

int main(void) {
    setup();
    while (1) {
        loop();
    }
}
```

### Explicação do Código

1. **Configuração do Pino 13 como Saída:** Configuramos
   o pino 13, que é o pino do LED embutido no Arduino, como
   saída usando o registrador `DDRB`.

2. **Configuração do Temporizador 1:** Configuramos o
   temporizador 1 para o modo CTC (Clear Timer on Compare Match)
   ajustando o bit `WGM12` no registrador `TCCR1B`.

3. **Configuração do Valor de Comparação:** Ajustamos
   o valor de comparação `OCR1A` para 15624. Isso gera uma
   interrupção a cada segundo com um prescaler de 1024.

4. **Habilitação da Interrupção de Comparação:**
   Habilitamos a interrupção de comparação A ajustando o bit
   `OCIE1A` no registrador `TIMSK1`.

5. **Configuração do Prescaler:** Configuramos o prescaler
   para 1024 ajustando os bits `CS12` e `CS10` no registrador
   `TCCR1B`.

6. **Manipulador de Interrupção (ISR):** A função
   `ISR(TIMER1_COMPA_vect)` é chamada sempre que a interrupção
   de comparação A do temporizador 1 é disparada. Neste
   exemplo, alternamos o estado do LED no pino 13.

7. **Loop Principal:** O loop principal do programa fica vazio,
   pois a ação é tratada pela interrupção.

Com esses exemplos, você deve ter uma boa base para começar
a usar interrupções no Arduino usando a linguagem C.
