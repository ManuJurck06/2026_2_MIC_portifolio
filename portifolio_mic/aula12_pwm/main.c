/*
 * main.c
 *
 * Created: 10/29/2026 9:02:07 AM
 *  Author: Aluno
 */ 

#include <xc.h>

void PWM_config(){
	TCCR0A = (1<<COM0A1)|(0<<COM0A0)
			|(1<<COM0B1)|(1<<COM0B0)
			|(1<<WGM01)|(1<<WGM00);//Modo Fast PWM, saída OCR0A não-inversora
	TCCR0B = (0<<WGM02)|(0<<CS02)|(0<<CS01)|(1<<CS00); //Habilita timer com Prescaler de 1x
	OCR0A = 101; //Razão de ciclo de 40%
	OCR0B = 76; //Razão de ciclo de 30%
	DDRD = (1<<DDD6)|(1<<DDD5); //Configura pino PD6 PD5 como saída
	
}
int main(void){
	PWM_config();
    while(1)
    {
        //TODO:: Please write your application code 
    }
}