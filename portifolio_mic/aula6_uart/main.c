/*
 * main.c
 *
 * Created: 9/17/2026 10:14:53 AM
 *  Author: Manuelly Jurck
 */ 
#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

char gMessage[16] = "Mensagem"; //"Null terminated strings" (8 bytes + 1 terminação nula)

/**
Configuração do módulo USART0 para modo assíncrono, frame de 8bits, paridade par, BAUD de 9600
*/
void UART_config(){
	UCSR0A = (1<<U2X0); ///MODO "DOUBLE SPEED" DESATIVADO
	UCSR0B = (0<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02);  //CONFIGURADO COMO TRANSMISSOR APENAS E OS UCSZ02, UCSZ01, UCSZ00 DEFINE O TAMANHO DO FRAME (TABELA 19-7 PÁG 162 DO DATASHEET) FRAME DE TAMANHO 8BITS
	UCSR0C = (0<<UMSEL00)|(0<<UMSEL01) //MODO ASSÍNCRONO
	         |(1<<UPM01)|(1<<UPM00)    //HABILITA PARIDADE PAR
			 |(1<<USBS0) //2 BIT STOP
			 |(0<<UCPOL0) //POLARIDADE DO CLOCK: IGNORA 
	         |(1<<UCSZ01)|(1<<UCSZ00); //->REGISTRADOR UCSR0C NA POSIÇÃO  UCSZ01, UCSZ00  //FRAME DE 8BITS
    UBRR0 = 103; //BAUD DE 9600 BITS POR SEGUNDO, ERRO DE 0,16% --> 1/9600  --> 1,04x10^-4 TEMPO DE 1 BIT UM FRAME DE 11 BITS VAI SER 0,0011458 SEGUNDOS
	//O  UBRR0 = 103; VEM DA EQUAÇÃO PÁG 146. (160000/(16*9600))-1 = 103...
}
void UART_send_byte(uint8_t pByte){
	//Aguarda espaço buffer
	while((UCSR0A & (1<<UDRE0)) == 0);
	UDR0 = pByte; //Envia o byte do parâmetro
	
}

void UART_send_string(char *pString){  //Lê apenas a posição 385 que é o inicio da mensagem e só vai parar de ler as posições quando encontrar um zero
	char *tMessagePtr = pString;
	while(*tMessagePtr != 0){
	UART_send_byte(*tMessagePtr);
	tMessagePtr++;
	}
}

int main(void)
{
	UART_config();
    while(1)
    {
	UART_send_string(gMessage);
//     UART_send_byte(0x4D); //M ou UART_send_byte(M); //M
//	   UART_send_byte(0x49); //I
//	   UART_send_byte(0x43); //C
//	   UART_send_byte(0x0A); // Line feed ou UART_send_byte(/n); // Line feed
	   _delay_ms(5); //Tempo de silêncio
    }
}