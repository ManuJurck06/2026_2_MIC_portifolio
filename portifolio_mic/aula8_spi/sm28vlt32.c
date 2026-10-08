/*
 * sm28vlt32.c
 *
 * Created: 08/10/2026 10:34:58
 *  Author: Manuelly Jurck
 */ 

#include <xc.h>
#include "spi.h"

void SM28VLT32_config(){
	DDRC = (1<<DDC0);         //Usando PC0 como Slave Select (saída)
	PORTC |= (1<<PORTC0);     //Slave select em nível alto
}

void SM28VLT_readWord(uint32_t pAdrress){
	uint8_t tAdressByte2 = pAdrress & 0x00FF0000 >> 16;
	uint8_t tAdressByte1 = pAdrress & 0x0000FF00 >> 8;
	uint8_t tAdressByte0 = pAdrress & 0x000000FF >> 0;
	uint8_t tDataByte1;
	uint8_t tDataByte0;
	uint16_t tDataWord;
	PORTC &= ~(1<<PORTC0);           //slave select em nível baixo
	SPI_transceive(0x15);                //Comando 'Read Word'
	SPI_transceive(tAdressByte2);
	SPI_transceive(tAdressByte1);
	SPI_transceive(tAdressByte0);
	tDataByte1 = SPI_transceive(0x00);
	tDataByte0 = SPI_transceive(0x00);
	SPI_transceive(0x00); //Dummy
	PORTC |= (1<<PORTC0);          //slave select em nível alto
	
	tDataWord = ((uint16_t) tDataByte1) <<8
						|((uint16_t) tDataByte1) <<0;
	return tDataWord;
	
} 