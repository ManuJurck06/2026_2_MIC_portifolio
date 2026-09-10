/*
 * main.c
 *
 * Created: 9/10/2026 9:10:30 AM
 *  Author: Manuelly Jurck
 */ 

# define F_CPU 16000000
# include <xc.h>
# include "util/delay.h"

void GPIO_config () {
	DDRB |=(1<<DDB5) ; // Pino PB5 (13) como saida
}
int main (void) {
	GPIO_config () ;
	while (1) {
		PORTB ^=(1<<PORTB5); // Alterna o estado do LED
		_delay_ms(100);
	}
}