/*
 * main.c
 *
 * Created: 8/27/2026 10:25:15 AM
 *  Author: Manuelly Jurck
 */

#define F_CPU 16000000
#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"


//Configuração da Interrupção Externa (INT0/INT1)

ISR(INT0_vect){ //Função no vetor de interrupção INT0
PORTB |=(1<<PORTB1); //Acende led em PB1
_delay_ms(50);
PORTB &= ~(1<<PORTB1); //Apaga led em PB1. ~inverte e & limpa o 0 da mascara
}

ISR(INT1_vect){ //Função no vetor de interrupção INT1
PORTB |=(1<<PORTB1); //Acende led em PB1
_delay_ms(100);
PORTB &= ~(1<<PORTB1); //Apaga led em PB1. (~)inverte e & limpa o 0 da mascara
}

void INT_config(){
//São as 3 configurações necessarias para habilitar o interrupt
EICRA = (1<<ISC11)|(1<<ISC10)    //1. configura INT1 na borda de subida
  |(1<<ISC01)|(0<<ISC00);      //1. configura INT0 na borda de descida
EIMSK = (1<<INT1) | (1<<INT0);   //2. Habilita INT0 e INT1
}

void GPIO_config(){
DDRB |= (1<<DDB0); //Pino PB0 como saida
DDRB |= (1<<DDB1); //Pino PB1 como saida
}

int main(void){
GPIO_config();
INT_config();
sei(); //3. habilita interrupções globalmente
    while(1){
cli(); //Desabilita interrupções temporariamente
PORTB |= (1<<PORTB0); //acende led no pino PB0
_delay_ms(100);
        PORTB &= ~(1<<PORTB0); //desliga pino PB0
sei();
_delay_ms(100);
    }
}
