/*
 * main.c
 *
 * Created: 8/27/2026 8:25:12 AM
 *  Author: Manuelly Jurck
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

#define BIT0_MASK 0b00000001 
#define BIT1_MASK 0b00000010 
#define BIT2_MASK 0b00000100 
#define BIT5_MASK 0b00100000 

int main(void){
	//*****Formas diferentes de setar a direção de PB2 e PB5*****
	//Forma 1: shifts com definições do fabricante
	DDRB = (1<<DDB5); //Numero 1 escorregado 5 vezes a esquerda 1=100000
	//DDRB = 0b00100000; -> mesma coisa que a linha acima
	//Forma 2: Binario Puro
	//DDRB = 0b00100000 | 0b00000100; = 0b00100100 -> mesma coisa quebrado em duas partes
	//DDRB = BIT5_MASK | BIT2_MASK;
    while(1)
    {
        //TODO:: Please write your application code 
    }
}