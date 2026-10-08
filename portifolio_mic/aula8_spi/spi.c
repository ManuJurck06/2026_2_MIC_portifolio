/*
 * spi.c
 *
 * Created: 08/10/2026 10:33:28
 *  Author: Aluno
 */ 
#include <xc.h>

void SPI_master_config(){
	SPCR = (1<<SPE)|(1<<DORD)      //Habilita SPI, Ordem MSB primeiro (padrão)
	|(1<<MSTR)             //Modo Mestre
	|(0<<CPOL)|(0<<CPHA)   //SPI modo 0
	|(0<<SPR1)|(0<<SPR0);  //divisor fosc/2, SCK->8MHz
	SPSR = (1<<SPI2X);             //Velocidade dobrada
	DDRB = (1<<DDB3)|(1<<DDB5);     //Config dos pinos MOSI e SCK como saídas
	DDRC = (1<<DDC0);              //Usando PC0 como Slave Select (saída)
	PORTC |= (1<<PORTC0);     //Slave select em nível alto
}

uint8_t SPI_transceive(uint8_t pTxByte){
	uint8_t tReceivedByte;
	PORTC &= ~(1<<PORTC0); //Slave select em nível baixo
	SPDR = pTxByte;                 //Escrita no SPDR dispara transação
	while((SPSR & (1<<SPIF)) == 0);  //Espera flag SPIF subir
	tReceivedByte = SPDR;            //Leitura do registrador de dados
	PORTC |= (1<<PORTC0);     //Slave select em nível alto
	return tReceivedByte;
}