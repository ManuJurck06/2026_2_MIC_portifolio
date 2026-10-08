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

int main(void){
	SPI_master_config();
    while(1)
    {
	SPI_transceive(0x42);
	   _delay_ms(1);
    }
}