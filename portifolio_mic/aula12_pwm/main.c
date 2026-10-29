/*
 * main.c
 *
 * Created: 10/29/2026 9:02:07 AM
 *  Author: Aluno
 */ 
#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"
void PWM_config(){
	TCCR0A = (1<<COM0A1)|(0<<COM0A0)
			|(1<<COM0B1)|(1<<COM0B0)
			|(1<<WGM01)|(1<<WGM00);//Modo Fast PWM, saída OCR0A não-inversora
	TCCR0B = (0<<WGM02)|(0<<CS02)|(0<<CS01)|(1<<CS00); //Habilita timer com Prescaler de 1x
	OCR0A = 101; //Razão de ciclo de 40%
	OCR0B = 76; //Razão de ciclo de 30%
	DDRD = (1<<DDD6)|(1<<DDD5); //Configura pino PD6 PD5 como saída
	
}

void PWM_setVoltageA(uint16_t pMilivolts){
	if(pMilivolts == 0){
		OCR0A = 0;
	}else{
		if(pMilivolts >= 5000){
			OCR0A = 0xff;
		}else{
			OCR0A = (uint8_t)(0x000000FF & (((uint32_t)pMilivolts * 256)/5000));
		}
	}
	
}
int main(void){
	PWM_config();
	PWM_setVoltageA(800);
    while(1)
    {
        PWM_setVoltageA(2500);
		_delay_ms(1);
        PWM_setVoltageA(3750);
        _delay_ms(1);
        PWM_setVoltageA(4665);
        _delay_ms(1);
        PWM_setVoltageA(5000);
        _delay_ms(1);
        PWM_setVoltageA(4665);
        _delay_ms(1);
        PWM_setVoltageA(3750);
        _delay_ms(1);	
        PWM_setVoltageA(2500);
        _delay_ms(1);
        PWM_setVoltageA(1250);
        _delay_ms(1);
        PWM_setVoltageA(335);
        _delay_ms(1);
        PWM_setVoltageA(0);
        _delay_ms(1);
        PWM_setVoltageA(335);
        _delay_ms(1);
        PWM_setVoltageA(1250);
        _delay_ms(1);
    }
}