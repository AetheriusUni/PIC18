//using #define allows you to declare constants

#include <p18f4321.h> 						//declare microcontroller

#include <stdio.h> 		

#include <math.h> 

#include <usart.h> 

#pragma config OSC = INTIO2 					//using internal oscillator

#pragma config WDT=OFF 						//turning off watch dog timer

#pragma config LVP=OFF 

#pragma config BOR =OFF 
//Prototype Area
void do_init()
{
TRISA = 0xFF;
TRISB = 0x00;
TRISC = 0x00;
TRISD = 0x00;
ADCON1 = 0x0F;							//change from analog to digital
}

void delay_one_sec()						//approximately one second delay to LED blinking
{
int I;
	for(I=0;I<20000;I++);
}
//Main Routine
void main() 
{ 
char I;								//initiates I
	do_init();						//call do_init
	while(1)						//infinite loop
	{
		for(I=0;I<8;I++)				//loop to count up until 7
		{
			PORTC = I;				//assign I to PORTC to output color
			PORTD = ~I;				//compliment PORTC's value/color
			delay_one_sec();			//call delay_one_sec
		}
	}
} 
