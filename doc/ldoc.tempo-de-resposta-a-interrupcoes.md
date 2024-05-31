<!-- prettier-ignore-start -->

             Tempo de Resposta a Interrupções
================================================================
                                                              64
<!-- prettier-ignore-end -->

O tempo de resposta à execução de interrupções para
todas as interrupções AVR habilitadas é de no mínimo
quatro ciclos de clock. Após quatro ciclos de clock, o
endereço do vetor de programa para a rotina de tratamento
de interrupção atual é executado. Durante este período
de quatro ciclos de clock, o Contador de Programa (Program
Counter) é empilhado na pilha (Stack). O vetor normalmente
é um salto para a rotina de interrupção, e esse salto
leva três ciclos de clock. Se uma interrupção ocorrer
durante a execução de uma instrução de múltiplos ciclos,
essa instrução é concluída antes que a interrupção
seja atendida. Se uma interrupção ocorrer quando o MCU
(Microcontrolador) estiver em modo de repouso (sleep mode), o
tempo de resposta à execução da interrupção é aumentado
em quatro ciclos de clock. Esse aumento vem além do tempo de
inicialização a partir do modo de repouso selecionado. Um
retorno de uma rotina de tratamento de interrupção leva
quatro ciclos de clock. Durante esses quatro ciclos de clock,
o Contador de Programa (dois bytes) é desempilhado da pilha,
o Ponteiro da Pilha (Stack Pointer) é incrementado em dois,
e o bit I no registrador de status (SREG) é configurado.



vim: set ts=4 sw=4 tw=64 ft=markdown:
