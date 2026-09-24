/*
 * main.c
 *
 * Created: 9/24/2026 10:21:02 AM
 *  Author: Manuelly Jurck
 */ 
#define F_CPU 16000000
#include <xc.h>
#include "string.h"
#include "util/delay.h"
#include "avr/interrupt.h"

#define RX_BUFFER_SIZE 16
uint8_t gMessage[16]; //Buffer global da UART
uint8_t gMessageReady;
uint16_t gRxCounter = 0; //Contagem de bytes recebidos
/**
Configuração do módulo USART0 para modo assíncrono, frame de 8bits, paridade par
*/
void UART_config_rx(uint16_t pBAUD){
	UCSR0A = (0<<U2X0);                          ///MODO "DOUBLE SPEED" DESATIVADO
	UCSR0B = (1<<RXEN0)|(0<<TXEN0)|(0<<UCSZ02)  //Habilita o receptor UART, frame 8 bits
			| (1<<RXCIE0);
	UCSR0C = (0<<UMSEL00)|(0<<UMSEL01)           //MODO ASSÍNCRONO
	|(1<<UPM01)|(0<<UPM00)                       //HABILITA PARIDADE PAR
	|(1<<USBS0)                                  //2 BIT STOP
	|(0<<UCPOL0)                                 //POLARIDADE DO CLOCK: IGNORA
	|(1<<UCSZ01)|(1<<UCSZ00);                    //->REGISTRADOR UCSR0C NA POSIÇÃO  UCSZ01, UCSZ00  //FRAME DE 8BITS
	UBRR0 = (1000000 / pBAUD)-1;

}

void GPIO_config(){
	DDRC = (1<<DDC0)|(1<<DDC1); // PC0 e PC1 como saída
}

ISR(USART_RX_vect){
	uint8_t tReceivedByte = UDR0;   //Leitura buffer UART
	gMessage[gRxCounter] = tReceivedByte; //Armazena bytes recebidos no buffer
	gRxCounter++;
	if(gRxCounter == RX_BUFFER_SIZE){ //Proteção contra estouro do buffer
		gRxCounter = 0;
	}
	if(tReceivedByte == '\n'){
		gMessageReady = 1; //Falg de mensagem completa
	}
}
int main(void)
{
	GPIO_config();
	UART_config_rx(9600);
	sei(); //Habilita interrupções globalmente
	while(1)
	{
	if(gMessageReady ){
	//Tratamento da mensagem recebida
	if(strcmp (gMessage, "Message") == 0){
		PORTC |= (1<<PORTC0); // Led Verde
		}else{
		PORTC |= (1<<PORTC1); // Led Vermelho
	}
	_delay_ms(10);
	PORTC = 0; //Apaga todos os LEDs
	}
	}
}