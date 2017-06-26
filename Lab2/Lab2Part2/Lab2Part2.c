//using #define allows you to declare constants

#include <p18f4321.h> 				//declare microcontroller

#include <stdio.h> 		

#include <math.h> 

#include <usart.h> 

#pragma config OSC = INTIO2 //using internal oscillator

#pragma config WDT=OFF 				//turning off watch dog timer

#pragma config LVP=OFF 

#pragma config BOR =OFF 
//Prototype Area
void do_init()
{
TRISA = 0xFF;
TRISB = 0x00;
TRISC = 0x00;
TRISD = 0x00;
ADCON1 = 0x0F;					//change from analog to digital
}
//Main Routine
void main(void) 
{ 
char sw;					//initialize switch "sw"					
	do_init();				//call do_init
	while(1)				//infinite loop
	{
		sw = PORTA&0x07;		//assigns sw the value input by switches
		PORTC = sw;			//store sw to PORTC, switched from regular LEDs to RGB LED D1
	}
} 