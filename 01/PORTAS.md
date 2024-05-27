No microcontrolador ATmega328P, utilizado no Arduino Uno, os
pinos são organizados em grupos chamados de portos (ports),
cada um designado por uma letra: B, C e D. Cada pino de
I/O é identificado por um número dentro do seu respectivo
porto. Vamos ver a diferenciação entre os pinos PC# e PD#
onde `#` é um número.

### Port C (PC#)

O Port C é composto pelos pinos de PC0 a PC6. Esses pinos
são mapeados para as funções de I/O e outras funções
específicas no ATmega328P. No Arduino Uno, os pinos do Port
C são mapeados como entradas analógicas, de A0 a A5 (PC0
a PC5), e o pino PC6 é utilizado como RESET.

#### Mapeamento do Port C no Arduino Uno:

- PC0: A0 (pino analógico 0)
- PC1: A1 (pino analógico 1)
- PC2: A2 (pino analógico 2)
- PC3: A3 (pino analógico 3)
- PC4: A4 (pino analógico 4, também SDA para I2C)
- PC5: A5 (pino analógico 5, também SCL para I2C)
- PC6: RESET

### Port D (PD#)

O Port D é composto pelos pinos de PD0 a PD7. Esses pinos
são utilizados para I/O digital no ATmega328P. No Arduino
Uno, os pinos do Port D são mapeados para os pinos digitais
de D0 a D7.

#### Mapeamento do Port D no Arduino Uno:

- PD0: D0 (pino digital 0, RX para comunicação serial)
- PD1: D1 (pino digital 1, TX para comunicação serial)
- PD2: D2 (pino digital 2)
- PD3: D3 (pino digital 3, com capacidade de PWM)
- PD4: D4 (pino digital 4)
- PD5: D5 (pino digital 5, com capacidade de PWM)
- PD6: D6 (pino digital 6, com capacidade de PWM)
- PD7: D7 (pino digital 7)

### Resumo

- **Port C (PC#)**: Utilizado principalmente para entradas
  analógicas (A0 a A5) e o pino RESET (PC6).
- **Port D (PD#)**: Utilizado para pinos digitais (D0 a D7),
  incluindo pinos para comunicação serial (RX, TX) e PWM.

### Exemplo de Uso

Vamos supor que queremos configurar o pino PC5 (A5 no Arduino
Uno) como uma entrada e o pino PD5 (D5 no Arduino Uno) como
uma saída. Veja como fazer isso:

```cpp
void setup() {
  // Configurar PC5 (A5) como entrada
  DDRC &= ~(1 << DDC5);

  // Configurar PD5 (D5) como saída
  DDRD |= (1 << DDD5);
}

void loop() {
  // Ler o estado do pino PC5 (A5)
  if (PINC & (1 << PINC5)) {
    // Se PC5 está alto, acender o LED no pino PD5 (D5)
    PORTD |= (1 << PORTD5);
  } else {
    // Se PC5 está baixo, apagar o LED no pino PD5 (D5)
    PORTD &= ~(1 << PORTD5);
  }
}
```

Neste exemplo, o pino analógico A5 (PC5) é configurado
como entrada, e o pino digital 5 (PD5) é configurado como
saída. O LED conectado ao pino digital 5 (PD5) será aceso
ou apagado com base no estado lido do pino analógico A5 (PC5).

O Port B no ATmega328P, usado no Arduino Uno, é outro
conjunto de pinos de I/O digitais. Assim como os Ports C e
D, o Port B é designado por uma letra seguida de números
(PB0 a PB7). Esses pinos têm várias funções e podem ser
utilizados como entradas e saídas digitais.

### Port B (PB#)

O Port B é composto pelos pinos de PB0 a PB7. No Arduino Uno,
esses pinos são mapeados para os pinos digitais D8 a D13,
além dos pinos de cristal e do pino RESET.

#### Mapeamento do Port B no Arduino Uno:

- PB0: D8 (pino digital 8)
- PB1: D9 (pino digital 9, com capacidade de PWM)
- PB2: D10 (pino digital 10, com capacidade de PWM)
- PB3: D11 (pino digital 11, com capacidade de PWM)
- PB4: D12 (pino digital 12)
- PB5: D13 (pino digital 13, geralmente conectado ao LED embutido)
- PB6: XTAL1 (entrada do oscilador de cristal)
- PB7: XTAL2 (saída do oscilador de cristal)

### Exemplo de Uso

Vamos configurar o pino PB5 (D13 no Arduino Uno) como saída
para acender o LED embutido e o pino PB4 (D12 no Arduino Uno)
como entrada para ler seu estado.

```cpp
void setup() {
  // Configurar PB5 (D13) como saída
  DDRB |= (1 << DDB5);

  // Configurar PB4 (D12) como entrada
  DDRB &= ~(1 << DDB4);
}

void loop() {
  // Ler o estado do pino PB4 (D12)
  if (PINB & (1 << PINB4)) {
    // Se PB4 está alto, acender o LED no pino PB5 (D13)
    PORTB |= (1 << PORTB5);
  } else {
    // Se PB4 está baixo, apagar o LED no pino PB5 (D13)
    PORTB &= ~(1 << PORTB5);
  }
}
```

### Explicação

1. **Configuração do pino PB5 (D13) como saída:**

   ```cpp
   DDRB |= (1 << DDB5);
   ```

   Esta linha de código em C++ configura o pino PB5 (D13)
   como saída. `DDRB` é o registrador de direção de dados
   para o port B.

2. **Configuração do pino PB4 (D12) como entrada:**

   ```cpp
   DDRB &= ~(1 << DDB4);
   ```

   Esta linha de código em C++ configura o pino PB4 (D12)
   como entrada.

3. **Ler o estado do pino PB4 (D12):**
   ```cpp
   if (PINB & (1 << PINB4)) {
     PORTB |= (1 << PORTB5);
   } else {
     PORTB &= ~(1 << PORTB5);
   }
   ```
   O estado do pino PB4 é lido e, se estiver alto, o LED no
   pino PB5 (D13) é aceso. Se estiver baixo, o LED é apagado.

### Resumo dos Ports no ATmega328P

- **Port B (PB#)**: Utilizado para pinos digitais (D8 a D13),
  incluindo pinos para PWM e pinos de cristal.
- **Port C (PC#)**: Utilizado principalmente para entradas
  analógicas (A0 a A5) e o pino RESET (PC6).
- **Port D (PD#)**: Utilizado para pinos digitais (D0 a D7),
  incluindo pinos para comunicação serial (RX, TX) e PWM.

Essas portas permitem uma ampla gama de possibilidades para a
configuração e utilização dos pinos do microcontrolador,
dependendo das necessidades específicas do seu projeto.
