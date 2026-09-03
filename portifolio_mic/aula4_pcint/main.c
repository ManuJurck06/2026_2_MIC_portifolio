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

#define KEY_RELEASED 0
#define KEY_PRESSED 1

uint8_t gKeyState_w = 0;
uint8_t gKeyState_a = 0;
uint8_t gKeyState_s = 0;
uint8_t gKeyState_d = 0;

void GPIO_config(){    //&= (bit 0 - limpa bits)   -> |= seta para 1 
	DDRB &= ~((1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)); // Portas PB0, PB1, PB2, PB3 como entradas 
	//(<<) shift a esquerda, (1<<DDB0)-> 1 com 0 shitf a esquerda. (1<<DDB1)-> 1 com 1 shitf a esquerda. (1<<DDB2)-> 1 com 2 shift a esquerda.
	PORTB |= ((1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)); //habilita pullup nos pinos PB0, PB1, PB2, PB3 ->DDxn como 0; PORTX como 1, PUD como zero -> já vem assim
	//DDRD = 0xff // seta tudo como saida , mesmo que 0b1111 1111   -> DDRB = Registrador de Direção. Define se é entrada ou saída
	DDRD |= (1<<DDD0)|(1<<DDD1)|(1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7); //configura PD0. PD1, PD2, PD3, PD4, PD5, PD6, PD7 como saída
	DDRC |= (1<<DDC0);
}

void GPIO_decBar(){
	PORTD = PORTD << 1;
}
void GPIO_incBar(){
	PORTD = PORTD >> 1;
	PORTD |= 0b10000000; //Aciona bit mais significativo
}

void PCINT_config(){
	PCICR |= (1<<PCIE0); // Habilita grupo de interrupção  PCINT0-PCINT7
	PCMSK0 |= (1<<PCINT3)|(1<<PCINT2)|(1<<PCINT1)|(1<<PCINT0); //Mascara que seta 1 para os PCINT 
	//ou PCMSK0 |= (0<<PCINT3)|(1<<PCINT2)|(0<<PCINT1)|(1<<PCINT0);
}

ISR(PCINT0_vect){
	//Lógica da tecla w
	uint8_t tCurrentKeyState_w = 0; 
	if((PINB & (1<<PINB0)) != 0){  //TESTA PINO PB0 ------------->//PIN é para leitura do pino e POR é para escrita
		//PB0 = 1, tecla w solta
		tCurrentKeyState_w = KEY_RELEASED;
	} else{
		//PB0 = 0, tecla w pressionada
		tCurrentKeyState_w = KEY_PRESSED;
	}
	if(tCurrentKeyState_w == KEY_PRESSED && gKeyState_w == KEY_RELEASED){
		//tecla W, acabou de ser pressionada
		gKeyState_w = KEY_PRESSED;
		GPIO_incBar(); //puxa função da barra de leds
	}else{
		if(tCurrentKeyState_w == KEY_RELEASED && gKeyState_w == KEY_PRESSED){
			//tecla W, acabou de ser solta
			gKeyState_w = KEY_RELEASED;	
	}}
	gKeyState_w = tCurrentKeyState_w;
	
	//Lógica da tecla s
	uint8_t tCurrentKeyState_s = 0;
	if((PINB & (1<<PINB1)) != 0){  //TESTA PINO PB0 ------------->//PIN é para leitura do pino e POR é para escrita
		//PB0 = 1, tecla s solta
		tCurrentKeyState_s = KEY_RELEASED;
		} else{
		//PB0 = 0, tecla s pressionada
		tCurrentKeyState_s = KEY_PRESSED;
	}
	if(tCurrentKeyState_s == KEY_PRESSED && gKeyState_s == KEY_RELEASED){
		//tecla s, acabou de ser pressionada
		gKeyState_s = KEY_PRESSED;
		GPIO_decBar(); //puxa função da barra de leds
		}else{
		if(tCurrentKeyState_s == KEY_RELEASED && gKeyState_s == KEY_PRESSED){
			//tecla s, acabou de ser solta
			gKeyState_s = KEY_RELEASED;
		}}
		gKeyState_s = tCurrentKeyState_s;
	PORTC ^= (1<<PORTC0); //seta pino PC0    ---> shor (ou exclusivo)
	//_delay_ms(100);
	//PORTC &= ~(1<<PORTC0);
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