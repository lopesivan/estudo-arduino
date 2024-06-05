# DDRs - Data Direction Registers

Estes registradores definem os pinos de uma PORTA

+------------------------------------------------+
| PB7  | PB6 | PB5 | PB4 | PB3 | PB2 | PB1 | PB0 |
| [1]  | [1] | [0] | [1] | [1] | [0] | [0] | [1] |
+------------------------------------------------+
                ^           ^
                |           |
                |           |
                |           ` - PB3 definido como saída
                |
                ` - PB5 definido como entrada

    $ echo "ibase=2; 11011001"| bc
    217

## Saídas Digitais

Quando um pino de uma PORTA é configurado como saída, o registrador PORT
configura o valor da tensão no pino. Exemplo:

              76543210
    DDRB  = 0b00100000  defino PB5 como saida

NOTA:
$echo "2^5"| bc
32
$ echo "obase=16; 2^5+ 2^4"| bc
30
$ echo "obase=16; 2^5"| bc
20



              76543210
    PORTB = 0b00100000  aplicamos 5V no pino PB5
ou
              76543210
    DDRB  = 0b00100000  defino PB5 como saida
    PORTB |= (1<<5)     aplicamos 5V no pino PB5

ou
    DDRB  = 0b00110000  defino PB5 e PB4 como saida

NOTA:
$ echo "2^5 + 2^4"| bc
48

    PORTB |= ((1<<5) |
              (1<<4)
             )          aplicamos 5V no pino PB5 e PB4

### Setando o i-ésimo Bit de um Byte `BYTE |= (1<<i)`

ON()

Exemplos:

    PORTB |= (1<<PB4);
                      (0bXXXXXXXX)
                      (0b00010000)  <= Máscara
                -------------------------------
                |=    (0bXXX1XXXX)

    PORTB |= ((1<<PB4)|(1<<PB5));
                      (0bXXXXXXXX)
                      (0b00010000)
                |     (0b00100000)
                -------------------------------
                |=    (0bXX11XXXX)

### Limpando o i-ésimo Bit de um Byte `BYTE &= ~(1<<i)`

OFF()

Exemplos:

    PORTB &= ~(1<<PB4);
                      (0bXXXXXXXX)
                      (0b11101111) == ~(0b00010000)
                -------------------------------
                &=    (0bXXX0XXXX)

    PORTB &= ~((1<<PB4)|(1<<PB5));
                      (0bXXXXXXXX)
                      (0b11001111) ==  ~( (0b00010000) |(0b00001000) )
                -------------------------------
                &=    (0bXX00XXXX)

### Mudando o i-ésimo Bit de um Byte `BYTE ^= (1<<i)`

TOOGLE()

Exemplos:

    PORTB ^= (1<<PB4);
                      (0bXXXXXXXX)
                      (0b00010000)
                -------------------------------
                ^=    (0bXXX?XXXX)
                            ^
                            |
                            |
                            ` muda o bit

## Entradas Digitais

Quando um pino de uma PORTA é configurado como entrada, o registrador PIN lê o
valor da tensão no pino.

                                       /
         /                             | BIT == 1,  5V
        |                              |
        |  BIT == 1, saída  =>  PORTB <
        |                              |
DDRB   <                               | BIT == 0, 0V
        |                              \
        |
        |                              /
        |                              | BIT == 1,  5V
        |                              |
        | BIT == 0, entrada =>  PORTB <
        |                              |
        |                              | BIT == 0, 0V
        |                               \


PINB
