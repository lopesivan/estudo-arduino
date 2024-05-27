No microcontrolador ATmega328P, utilizado no Arduino Uno, os pinos são organizados em grupos chamados de portos (ports), cada um designado por uma letra: B, C e D. Cada pino de I/O é identificado por um número dentro do seu respectivo porto. Vamos ver a diferenciação entre os pinos PC# e PD# onde `#` é um número.

### Port C (PC#)

O Port C é composto pelos pinos de PC0 a PC6. Esses pinos são mapeados para as funções de I/O e outras funções específicas no ATmega328P. No Arduino Uno, os pinos do Port C são mapeados como entradas analógicas, de A0 a A5 (PC0 a PC5), e o pino PC6 é utilizado como RESET.

#### Mapeamento do Port C no Arduino Uno:
- PC0: A0 (pino analógico 0)
- PC1: A1 (pino analógico 1)
- PC2: A2 (pino analógico 2)
- PC3: A3 (pino analógico 3)
- PC4: A4 (pino analógico 4, também SDA para I2C)
- PC5: A5 (pino analógico 5, também SCL para I2C)
- PC6: RESET

### Port D (PD#)

O Port D é composto pelos pinos de PD0 a PD7. Esses pinos são utilizados para I/O digital no ATmega328P. No Arduino Uno, os pinos do Port D são mapeados para os pinos digitais de D0 a D7.

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

- **Port C (PC#)**: Utilizado principalmente para entradas analógicas (A0 a A5) e o pino RESET (PC6).
- **Port D (PD#)**: Utilizado para pinos digitais (D0 a D7), incluindo pinos para comunicação serial (RX, TX) e PWM.

### Exemplo de Uso

Vamos supor que queremos configurar o pino PC5 (A5 no Arduino Uno) como uma entrada e o pino PD5 (D5 no Arduino Uno) como uma saída. Veja como fazer isso:

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

Neste exemplo, o pino analógico A5 (PC5) é configurado como entrada, e o pino digital 5 (PD5) é configurado como saída. O LED conectado ao pino digital 5 (PD5) será aceso ou apagado com base no estado lido do pino analógico A5 (PC5).
