/*
 * main.c
 *
 * Created: 9/3/2026 8:57:02 AM
 *  Author: Manuelly Jurck
 */ 
#define F_CPU 16000000
#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

ISR(PCINT0_vect){
	PORTC |= (1<<PORTC0); //seta pino PC0
	_delay_ms(100);
	PORTC &= ~(1<<PORTC0);
}

void GPIO_config(){    //&= (bit 0 - limpa bits)   -> |= seta para 1 
	DDRB &= ~((1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)); // Portas PB0, PB1, PB2, PB3 como entradas 
	//(<<) shift a esquerda, (1<<DDB0)-> 1 com 0 shitf a esquerda. (1<<DDB1)-> 1 com 1 shitf a esquerda. (1<<DDB2)-> 1 com 2 shift a esquerda.
	PORTB |= ((1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)); //habilita pullup nos pinos PB0, PB1, PB2, PB3 ->DDxn como 0; PORTX como 1, PUD como zero -> já vem assim
	//DDRD = 0xff // seta tudo como saida , mesmo que 0b1111 1111   -> DDRB = Registrador de Direção. Define se é entrada ou saída
	DDRD |= (1<<DDD0)|(1<<DDD1)|(1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7); //configura PD0. PD1, PD2, PD3, PD4, PD5, PD6, PD7 como saída
	DDRC |= (1<<DDC0);
}

void PCINT_config(){
	PCICR |= (1<<PCIE0); // Habilita grupo de interrupção  PCINT0-PCINT7
	PCMSK0 |= (1<<PCINT2)|(1<<PCINT0); //Mascara que seta 1 para os PCINT 
	//ou PCMSK0 |= (0<<PCINT3)|(1<<PCINT2)|(0<<PCINT1)|(1<<PCINT0);
}

int main(void){
	GPIO_config();
	PCINT_config();
	sei();  //habilita interrupções globais
    while(1)
    {
        //TODO:: Please write your application code 
    }
}