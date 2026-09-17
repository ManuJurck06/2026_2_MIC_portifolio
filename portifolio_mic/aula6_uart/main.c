/*
 * main.c
 *
 * Created: 9/17/2026 10:14:53 AM
 *  Author: Manuelly Jurck
 */ 
#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"
/**
Configuração do módulo USART0 para modo assíncrono, frame de 8bits, paridade par, BAUD de 9600
*/
void UART_config(){
	UCSR0A = (1<<U2X0); ///MODO "DOUBLE SPEED" DESATIVADO
	UCSR0B = (0<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02);  //CONFIGURADO COMO TRANSMISSOR APENAS E OS UCSZ02, UCSZ01, UCSZ00 DEFINE O TAMANHO DO FRAME (TABELA 19-7 PÁG 162 DO DATASHEET) FRAME DE TAMANHO 8BITS
	UCSR0C = (0<<UMSEL00)|(0<<UMSEL01) //MODO ASSÍNCRONO
	         |(1<<UPM01)|(1<<UPM00)    //HABILITA PARIDADE PAR
			 |(0<<USBS0) //1 BIT STOP
			 |(0<<UCPOL0) //POLARIDADE DO CLOCK: IGNORA 
	         |(1<<UCSZ01)|(1<<UCSZ00); //->REGISTRADOR UCSR0C NA POSIÇÃO  UCSZ01, UCSZ00  //FRAME DE 8BITS
    UBRR0 = 103; //BAUD DE 9600 BITS POR SEGUNDO, ERRO DE 0,16% --> 1/9600  --> 1,04x10^-4 TEMPO DE 1 BIT UM FRAME DE 11 BITS VAI SER 0,0011458 SEGUNDOS
	//O  UBRR0 = 103; VEM DA EQUAÇÃO PÁG 146. (160000/(16*9600))-1 = 103...
}
void UART_send(){
	UDR0 = 0x5A; //Envia um byte exemplo
	_delay_ms(2);
}

int main(void)
{
	UART_config();
    while(1)
    {
       UART_send();
    }
}