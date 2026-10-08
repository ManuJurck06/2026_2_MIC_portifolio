/*
 * main.c
 *
 * Created: 10/8/2026 9:02:46 AM
 *  Author: Manuelly Jurck
 */ 
#define F_CPU 16000000
#include <xc.h>
#include <util/delay.h>
# include "spi.h"
# include "sm28vlt32.h"

int main(void){
	SPI_master_config();
    while(1)
    {
	uint8_t tMemoryData = SM28VLT_readWord(1000);
	   _delay_ms(1);
    }
}