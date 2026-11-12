/*
 * main.c
 *
 * Created: 11/12/2026 10:16:24 AM
 *  Author: Manuelly Jurck
 */ 
#define F_CPU 16000000
#include <xc.h>


void ADC_config(){
	ADMUX = (1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(0<<MUX3)    //Canal de conversão: pino ADC 7 
			|(1<<REFS1)|(1<<REFS0);                    //Referencia de tensão interna 1.1V
			ADCSRA = (1<<ADEN)|(0<<ADATE)             //Habilita o ADC no modo manual
			|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);        //Fator de Prescaler 128 (125kHz freq adc)
			DIDR0 = (1<<ADC0D);
			
}
int main(void)
{
	DDRB |= (1<<DDB0);
	ADC_config();
	_delay_ms(1);
    while(1)
    {
		ADCSRA |= (1<<ADSC);
		while((ADCSRA & (1<<ADSC)) != 0);
       uint8_t tADCData = ADC;                         // Acesso a ADCH e ADCL como um unico registrador de 16 bits, faixa inteiros de 0 a 1023 (ADLAR = 0) 
	   if(tADCData < 670){
		   PORTB |= (1<<PORTB0);                        //Acender LED abaixo de 720mV
	   }else{
		   PORTB &= ~(1<<PORTB0);                      //Apagar LED caso contrario
	   }
    }
}