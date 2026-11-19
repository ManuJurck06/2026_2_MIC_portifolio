/*
 * main.c
 *
 * Created: 11/19/2026 8:33:52 AM
 *  Author: Manuelly Jurck
 */ 

#include <xc.h>
#include "avr/interrupt.h"

//Termos do filtro(função transferencia) (butterworth de ordem 2, corte em 0.114*fs = 114Hz)
const int16_t b[3] = {1372, 2744, 1372};
const int16_t a[2] = {-16899,6002};  //Medidas do ADC

int16_t x[3]; //medidas do adc
int16_t y[3]; //saída filtro


ISR (TIMER1_COMPB_vect){
	PORTB ^= (1<<PORTB1); //debug para visuzalizar o tempo fo TMR1
}
ISR(ADC_vect){ //interrupção referente a conversão concluida
	PORTB |= (1<<PORTB1); //Debug: tempo de processamento
       uint8_t tADCData = ADC;                         // Acesso a ADCH e ADCL como um unico registrador de 16 bits, faixa inteiros de 0 a 1023 (ADLAR = 0)
	   //Linha de atraso do sinal x e y (fila FIFO)
	   x[2] = x[1]; 
	   x[1] = x[0];
	   x[0] = tADCData;
	   y[2] = y[1];
	   y[1] = y[0];
	   y[0] = b[0]*x[0] + b[1]*x[1] + b[2]*x[2] - a[0]*y[1] - a[1]*y[2];
			  
	   uint16_t y = (x[0] + x[1] + x[2] + x[3])/4;  //Filtro Média Movel de ordem 4
	   
       if(y < 670){
	       PORTB ^= (1<<PORTB0);                        //Acender LED abaixo de 720mV
	       }else{
	       PORTB &= ~(1<<PORTB0);                      //Apagar LED caso contrario
       }
	PORTB &= ~(1<<PORTB1); //Debug: tempo de processamento
}
void ADC_config(){
	ADMUX = (1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(0<<MUX3)    //Canal de conversão: pino ADC0
	|(1<<REFS1)|(1<<REFS0);                    //Referencia de tensão interna 1.1V
	ADCSRA = (1<<ADEN)|(1<<ADATE)             //Habilita o ADC no modo autimatico "auto triger"
	|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2)        //Fator de Prescaler 128 (125kHz freq adc)
	|(1<<ADIE);                               //Habilita interrupção do AD
	DIDR0 = (1<<ADC0D);
	ADCSRB = (1<<ADTS2)|(0<<ADTS1)|(1<<ADTS0); //Fonte de disparo: TMR1 Compare match B
	
}
//configurar timer 1 para disparo a cada 1ms
void TMR1_config(){
	TCCR1A = (0<<WGM11)|(0<<WGM10); //
	TCCR1B = (0<<WGM13)|(1<<WGM12) // Modo 4: CTC com topo em OCR1A
			|(0<<CS12)|(0<<CS11)|(1<<CS10);
	OCR1A = 15999; //Periodo de 1ms
//	TIMSK1 = (1<<OCIE1B); //debug:habilita interrupçõa compare match B
}

int main(void)
{
	DDRB = (1<<DDB0)|(1<<DDB1); //Pinos PB0 e PB1 como saída
	TMR1_config();
	ADC_config();
	sei();
    while(1)
    {
        //TODO:: Please write your application code 
    }
}