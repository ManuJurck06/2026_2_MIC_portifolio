/*
 * main.c
 *
 * Created: 10/15/2026 8:59:56 AM
 *  Author: Manuelly Jurck
 */ 
#define F_CPU 16000000
#include <util/delay.h>
#include <xc.h>

void TWI_master_config(){
	TWBR = 64;    //divisor 64, fscl=100kHz
	TWSR |= (0<<TWPS1)|(0<<TWPS0); //Prescaler de 1
	TWCR |= (1<<TWEN); //habilita periférico
}

int main(void)
{
	TWI_master_config();
	_delay_ms(1000);
	uint8_t tSlaveAddress = 10;
    while(1)
    {
        //iniciar uma transmissão como metre
		TWCR |= (1<<TWSTA); //Inicia condição de start
		while((TWCR & (1<<TWINT)) == 0);  //Aguarda flag de interrupção subir
		uint8_t tStatusCode = (TWSR & 0b11111000);
		//condição de start ok??
		if(tStatusCode ==0x08){
			//condição start ok
			TWDR = (tSlaveAddress<<1)|1; //Endereço mais flag R/W (1 para leitura e 0 para escrita) 
			TWCR = (1<<TWINT)|(1<<TWEN);
			while((TWCR & (1<<TWINT)) == 0);
			tStatusCode = (TWSR & 0b11111000);
			if(tStatusCode == 0x28){
				//Nack recebido
			}else{
				//outro erro
			}
		}else{
			//algum erro...
		}
		TWCR |= (1<<TWINT);  //Limpar flag de interrupção
		_delay_ms(100);
	}
}