### Código

```c
// Configura o temporizador 1 para gerar uma interrupção a cada 1 segundo
TCCR1B |= (1 << WGM12); // Modo CTC
OCR1A = 15624; // Valor de comparação para 1 Hz (prescaler 1024)
TIMSK1 |= (1 << OCIE1A); // Habilita interrupção de comparação A
TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024
```

### Explicação Detalhada

1. **Modo CTC (Clear Timer on Compare Match):**

   ```c
   TCCR1B |= (1 << WGM12); // Modo CTC
   ```

   - `TCCR1B` é o registrador de controle do Timer/Counter 1.
   - `WGM12` é o bit que define o modo CTC.
   - Configurar o bit `WGM12` coloca o Timer 1 no modo CTC,
     onde o timer é limpo (resetado) quando o valor do contador
     atinge o valor do registrador de comparação (`OCR1A`).

2. **Valor de Comparação (1 Hz):**

   ```c
   OCR1A = 15624; // Valor de comparação para 1 Hz (prescaler 1024)
   ```

   - `OCR1A` é o registrador de comparação do Timer 1.
   - O valor 15624 é escolhido para gerar uma interrupção
     a cada 1 segundo, com base na frequência do clock do
     microcontrolador e no prescaler.
   - Cálculo:
     \[
     \text{Valor de Comparação} = \frac{F\_{\text{CPU}}}{\text{Prescaler} \times \text{Frequência desejada}} - 1
     \]
     Onde:
     - \( F\_{\text{CPU}} = 16.000.000 \, \text{Hz} \) (16 MHz, frequência do Arduino Uno)
     - Prescaler = 1024
     - Frequência desejada = 1 Hz
       \[
       \text{Valor de Comparação} = \frac{16.000.000}{1024 \times 1} - 1 = 15624
       \]

3. **Habilitar Interrupção de Comparação A:**

   ```c
   TIMSK1 |= (1 << OCIE1A); // Habilita interrupção de comparação A
   ```

   - `TIMSK1` é o registrador de máscara de interrupção do Timer/Counter 1.
   - `OCIE1A` é o bit que habilita a interrupção de comparação A.
   - Configurar o bit `OCIE1A` permite que o Timer 1 gere uma
     interrupção quando o valor do contador atinge o valor de
     `OCR1A`.

4. **Configuração do Prescaler (1024):**
   ```c
   TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024
   ```
   - `CS12` e `CS10` são bits no registrador `TCCR1B` que
     configuram o prescaler do Timer 1.
   - Configurar `CS12` e `CS10` coloca o prescaler em 1024.
   - Isso significa que o clock do Timer 1 é dividido por
     1024, reduzindo a frequência do clock do timer, o que
     permite períodos de temporização mais longos.

### Resumo

Esse conjunto de configurações faz o seguinte:

- **Modo CTC:** Coloca o Timer 1 no modo CTC, onde o timer
  é limpo quando o valor do contador atinge o valor de `OCR1A`.
- **Valor de Comparação:** Define o valor de comparação
  para 15624, calculado para gerar uma interrupção a cada 1
  segundo com um prescaler de 1024.
- **Interrupção de Comparação A:** Habilita a interrupção
  de comparação A, permitindo que o Timer 1 gere uma
  interrupção quando o valor do contador atinge o valor de
  `OCR1A`.
- **Prescaler de 1024:** Configura o prescaler do Timer 1
  para 1024, reduzindo a frequência do clock do timer.

### Exemplo Completo

Aqui está um exemplo completo de código que configura
o Timer 1 para gerar uma interrupção a cada 1 segundo e
define a função de interrupção correspondente:

```c
#include <avr/io.h>
#include <avr/interrupt.h>

// Função de interrupção para Timer 1
ISR(TIMER1_COMPA_vect) {
    // Código a ser executado na interrupção
    PORTB ^= (1 << PORTB5); // Alterna o estado do LED no pino 13 (PORTB5)
}

void setup() {
    // Configura o pino 13 como saída
    DDRB |= (1 << DDB5);

    // Configura o Timer 1 para gerar uma interrupção a cada 1 segundo
    TCCR1B |= (1 << WGM12); // Modo CTC
    OCR1A = 15624; // Valor de comparação para 1 Hz (prescaler 1024)
    TIMSK1 |= (1 << OCIE1A); // Habilita interrupção de comparação A
    TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024

    // Habilita interrupções globais
    sei();
}

void loop() {
    // O loop principal fica vazio, pois a ação é tratada pela interrupção
}
```

Neste exemplo, o LED no pino 13 (PORTB5) do Arduino é
alternado a cada 1 segundo, usando a interrupção do Timer 1.

Para configurar o Timer 1 para gerar uma interrupção a cada
2 segundos, você precisa ajustar o valor de comparação
(OCR1A) de acordo. Vamos recalcular o valor de comparação
para 2 segundos com um prescaler de 1024.

### Cálculo do Valor de Comparação para 2 Segundos

Usando a fórmula:
\[
\text{Valor de Comparação} = \frac{F\_{\text{CPU}}}{\text{Prescaler} \times \text{Frequência desejada}} - 1
\]

Para 2 segundos (0.5 Hz):

- \( F\_{\text{CPU}} = 16.000.000 \, \text{Hz} \) (16 MHz, frequência do Arduino Uno)
- Prescaler = 1024
- Frequência desejada = 0.5 Hz

\[
\text{Valor de Comparação} = \frac{16.000.000}{1024 \times 0.5} - 1 = 31.249
\]

Portanto, precisamos definir o registrador OCR1A para 31.249.

### Código Atualizado

Aqui está o código completo atualizado para configurar o
Timer 1 para gerar uma interrupção a cada 2 segundos:

```c
#include <avr/io.h>
#include <avr/interrupt.h>

// Função de interrupção para Timer 1
ISR(TIMER1_COMPA_vect) {
    // Código a ser executado na interrupção
    PORTB ^= (1 << PORTB5); // Alterna o estado do LED no pino 13 (PORTB5)
}

void setup() {
    // Configura o pino 13 como saída
    DDRB |= (1 << DDB5);

    // Configura o Timer 1 para gerar uma interrupção a cada 2 segundos
    TCCR1B |= (1 << WGM12); // Modo CTC
    OCR1A = 31249; // Valor de comparação para 0.5 Hz (prescaler 1024)
    TIMSK1 |= (1 << OCIE1A); // Habilita interrupção de comparação A
    TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024

    // Habilita interrupções globais
    sei();
}

void loop() {
    // O loop principal fica vazio, pois a ação é tratada pela interrupção
}
```

### Explicação das Modificações

1. **Valor de Comparação (2 Segundos):**
   ```c
   OCR1A = 31249; // Valor de comparação para 0.5 Hz (prescaler 1024)
   ```
   - Define o valor de comparação para 31.249, o que gera uma
     interrupção a cada 2 segundos com um prescaler de 1024.

O restante do código permanece o mesmo, configurando o Timer
1 no modo CTC, habilitando a interrupção de comparação
A, e alternando o estado do LED no pino 13 na rotina de
interrupção.
