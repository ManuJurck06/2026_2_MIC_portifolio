/*
 * main.c
 *
 * Created: 10/22/2026 10:51:02 AM
 *  Author: Manuelly Jurck
 */ 

#include <xc.h>
#include "avr/interrupt.h"

//obter ujma interrupção com periodo de 10ms

ISR(TIMER0_COMPA_vect){ //Interrupção de comparação A
	PORTB ^= (1<<PORTB0);
	
}

void TMR0_config(){
	TCCR0A = (1<<WGM01)|(0<<WGM00); //define modo de operação do timer   --> MODO CTC --> conta até o valor colocado no registrador OCRA
	TCCR0B = (0<<WGM02)
	        |(1<<CS02)|(0<<CS01)|(1<<CS00);   //--> Fator de divisão 1024
	OCR0A = 155; //Corresponde a 9,984ms   (156*1024)/16000000
	TIMSK0 = (1<<OCIE0A); //Habilita interrupção COMPA
	
}

int main(void)
{
	DDRB |= (1<<DDB0);
	TMR0_config();
	sei();
    while(1)
    {
        //TODO:: Please write your application code 
    }
}