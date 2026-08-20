/*
 * main.c
 *
 * Created: 8/20/2026 8:58:56 AM
 *  Author: Manuelly Jurck
 */ 
#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

int main(void){
	DDRB |= 0b00100000; // Define PB5 como saída
	DDRD &= 0b11110111; // Define pino PD3 como entrada --> força o bit 3 ser uma entrada - está zerando ele
    while(1){
		if((PIND & 0b00001000) != 0) { //Ler valor da chave PD3, segue se tiver em nível lógico alto  --> isolar um bit sempre significa aplicar a operação E -- funciona como um filtro
			PORTB |= 0b00100000; // Atribui nível lógico alto ao pino PB5
			_delay_ms(100);
			PORTB &= 0b11011111; // Atribui nível lógico baixo ao pino PB5
			_delay_ms(900);
		}
    }                                                  
}