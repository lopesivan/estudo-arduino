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

Claro! Vou explicar como essas linhas de código configuram a
interrupção para disparar na borda de descida (falling edge)
no Arduino, utilizando o microcontrolador ATmega328P.

### Contexto

O ATmega328P, usado no Arduino Uno, possui pinos de
interrupção externa (como INT0 e INT1) que podem ser
configurados para disparar em diferentes condições, como
uma mudança de nível, uma borda de subida ou uma borda
de descida. Essas configurações são feitas utilizando os
registradores de controle de interrupção externa.

### Registrador EICRA

O registrador `EICRA` (External Interrupt Control Register
A) é usado para configurar as condições que disparam as
interrupções externas (INT0 e INT1).

- `ISC01` e `ISC00` são bits no registrador `EICRA` que
  configuram o modo de disparo da interrupção INT0.
- `ISC11` e `ISC10` configuram o modo de disparo da
  interrupção INT1.

### Configuração para Borda de Descida

Para configurar a interrupção INT0 para disparar na borda
de descida, você precisa ajustar os bits `ISC01` e `ISC00`
da seguinte maneira:

- `ISC01` = 1
- `ISC00` = 0

Aqui está o que essas linhas de código fazem:

```c
// Configura a interrupção para disparar na borda de descida
EICRA |= (1 << ISC01);
EICRA &= ~(1 << ISC00);
```

### Explicação do Código

1. **EICRA |= (1 << ISC01);**

   Esta linha usa uma operação OR bit a bit (`|=`) para
   definir o bit `ISC01` no registrador `EICRA`:

   - `(1 << ISC01)` cria uma máscara onde apenas o bit
     `ISC01` está definido como 1.
   - `EICRA |= (1 << ISC01);` aplica essa máscara ao
     registrador `EICRA`, garantindo que o bit `ISC01`
     seja definido como 1, enquanto mantém os outros bits
     inalterados.

2. **EICRA &= ~(1 << ISC00);**

   Esta linha usa uma operação AND bit a bit com o
   complemento (`&= ~`) para limpar o bit `ISC00` no
   registrador `EICRA`:

   - `(1 << ISC00)` cria uma máscara onde apenas o bit
     `ISC00` está definido como 1.
   - `~(1 << ISC00)` inverte essa máscara, resultando em
     uma máscara onde todos os bits são 1, exceto `ISC00`,
     que é 0.
   - `EICRA &= ~(1 << ISC00);` aplica essa máscara ao
     registrador `EICRA`, garantindo que o bit `ISC00`
     seja definido como 0, enquanto mantém os outros bits
     inalterados.

### Resumo

Configurando `ISC01` para 1 e `ISC00` para 0, o registrador
`EICRA` é ajustado para que a interrupção INT0 dispare na
borda de descida do sinal. Aqui está uma tabela resumindo
as configurações possíveis para `ISC01` e `ISC00`:

| ISC01 | ISC00 | Condição de Disparo             |
| ----- | ----- | ------------------------------- |
| 0     | 0     | Nível baixo                     |
| 0     | 1     | Qualquer mudança de nível       |
| 1     | 0     | Borda de descida (falling edge) |
| 1     | 1     | Borda de subida (rising edge)   |

Portanto, as linhas de código fornecidas configuram
corretamente a interrupção para disparar quando o sinal no
pino INT0 passa de alto para baixo (borda de descida).

Claro, aqui estão as quatro possíveis configurações
de disparo para a interrupção INT0 no microcontrolador
ATmega328P (usado no Arduino Uno) em C.

### Configuração para Nível Baixo

Para disparar a interrupção quando o nível do pino INT0
estiver baixo:

```c
// Configura a interrupção para disparar no nível baixo
EICRA &= ~(1 << ISC01);
EICRA &= ~(1 << ISC00);
```

### Configuração para Qualquer Mudança de Nível

Para disparar a interrupção em qualquer mudança de nível
(subida ou descida):

```c
// Configura a interrupção para disparar em qualquer mudança de nível
EICRA &= ~(1 << ISC01);
EICRA |= (1 << ISC00);
```

### Configuração para Borda de Descida

Para disparar a interrupção na borda de descida (falling
edge):

```c
// Configura a interrupção para disparar na borda de descida
EICRA |= (1 << ISC01);
EICRA &= ~(1 << ISC00);
```

### Configuração para Borda de Subida

Para disparar a interrupção na borda de subida (rising edge):

```c
// Configura a interrupção para disparar na borda de subida
EICRA |= (1 << ISC01);
EICRA |= (1 << ISC00);
```

### Resumo

Estas configurações alteram os bits `ISC01` e `ISC00`
no registrador `EICRA` para definir o modo de disparo da
interrupção INT0:

- **Nível baixo:**

  ```c
  EICRA &= ~(1 << ISC01);
  EICRA &= ~(1 << ISC00);
  ```

- **Qualquer mudança de nível:**

  ```c
  EICRA &= ~(1 << ISC01);
  EICRA |= (1 << ISC00);
  ```

- **Borda de descida:**

  ```c
  EICRA |= (1 << ISC01);
  EICRA &= ~(1 << ISC00);
  ```

- **Borda de subida:**
  ```c
  EICRA |= (1 << ISC01);
  EICRA |= (1 << ISC00);
  ```

Cada configuração ajusta os bits `ISC01` e `ISC00` para
definir a condição de disparo desejada para a interrupção
INT0.
