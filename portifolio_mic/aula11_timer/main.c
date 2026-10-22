/*
 * main.c
 *
 * Created: 10/22/2026 10:51:02 AM
 *  Author: Manuelly Jurck
 */ 

#include <xc.h>
#include "avr/interrupt.h"

uint16_t gMilliseconds = 0;
uint8_t gClockSeconds = 0;
uint8_t gClockMinutes = 0;
uint8_t gClockHours = 0;

//obter ujma interrupção com periodo de 10ms

ISR(TIMER0_COMPA_vect){ //Interrupção de comparação A
	gMilliseconds += 10;

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
    while(1){
		if(gMilliseconds < 100){
			PORTB |= (1<<PORTB0); //Seta PB0 por 100ms
		}else{
			PORTB &= ~(1<<PORTB0); //Zera PB0 por 900ms
		}
		//lógica do RTC (Real Time Clock)
        	if(gMilliseconds >= 1000){
	        	gMilliseconds = 0;
	        	gClockSeconds++;
	        	if(gClockSeconds >= 60){
		        	gClockSeconds = 0;
		        	gClockMinutes++;
		        	if(gClockMinutes >=60){
			        	gClockMinutes = 0;
			        	gClockHours++;
			        	if(gClockHours >= 24){
				        	gClockHours = 0;
			        	}
		        	}
	        	}
        	} 
    }
}