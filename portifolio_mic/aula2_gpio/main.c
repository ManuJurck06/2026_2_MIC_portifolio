/*
 * main.c
 *
 * Created: 8/27/2026 8:25:12 AM
 *  Author: Manuelly Jurck
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"
#include "stdint.h"

//Controle de vários LEDs com operações de shift

void GPIO_config(){
	DDRB = (1<<DDB6)|(1<<DDB4)|(1<<DDB2)|(1<<DDB0);
}
int main(void){
	GPIO_config();
	uint8_t tData = 0x03; //Cria variavel de 8 bits que recebe o numerp hexa 3 -> 0b0000 0011
    while(1)
    {
       PORTB = tData;
	   _delay_ms(1000);
	  tData = tData <<1; //0b0000 0110, 0b0000 1100
	  if(tData == 0){
		  tData = 0x03;
	  }
    }
}