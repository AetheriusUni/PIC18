#include <p18f4321.h> 
#include <stdio.h> 
#include <math.h> 
#include <usart.h> 

//Prototype Area
void do_rgb(int temp);
unsigned int get_full_ADC(void);
void Init_ADC(void);
void do_init();
void init_UART();

void init_UART() 									// used for TeraTerm
{ 
 	OpenUSART (USART_TX_INT_OFF & USART_RX_INT_OFF & 
	USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & 
	USART_BRGH_HIGH, 25); 
 	OSCCON = 0x60;
} 

void do_init()
{
	TRISA = 0xFF;									// initialize TRISA
	TRISB = 0x00;
	TRISC = 0x00;
	TRISD = 0x00;
	ADCON0=0x09; 									// select channel AN2, and turn on the ADC subsystem 
	ADCON1=0x1B; 									// select pins AN0 through AN3 as analog signal, VDD-VSS as reference voltage
	ADCON2=0xA9; 									// right justify the result. Set the bit conversion time (TAD) and acquisition time
}

unsigned int get_full_ADC(void) 
{ 
int result; 
	ADCON0bits.GO = 1; 								// Start Conversion 
	while(ADCON0bits.DONE==1);							// wait for conversion to be completed 
	result = (ADRESH * 0x100) + ADRESL; 						// combine result of upper byte and 
											// lower byte into result  
	return result;       					 			// return the result. 
} 

void do_led(int temp)
{
int u;											// declare u
int l;											// declare l
char array[10] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10}; 			//values for outputting 0,1,2... on the 7 segment display
	u = temp/10;									// temperature tens place
	l = temp%10;									// temperature ones place
	PORTC = array[u]&0x0F;								// output 4 least significant bits of the upper digit
	PORTB = (array[u]&0x70)>>1;							// output bits 3,4,5 of the upper digit
	PORTD = array[l];								// output ones place
}	

void do_rgb(int temp)
{
	if(temp<70)									// red logic
	{
		PORTB = 0x01;
	}	
	if(temp>=70&&temp<80)								// yellow logic
	{
		PORTB = 0x03;
	}
	if(temp>=80&&temp<84)								// green logic
	{
		PORTB = 0x02;
	}
	if(temp>=84)									// white logic
	{
		PORTB = 0x07;
	}			
}	
//Main Routine
void main() 
{ 
unsigned int ivolt, temp, step;								// initialize variables
	init_UART();									// call init_UART
	do_init();									// call do_init
	
	while(1)									// infinite loop
	{
		step = get_full_ADC();							// give value of ADC to step
		ivolt = step*4+15;							// calculation for 
		temp = ivolt/10;							// convert ivolt to temperature
		do_led(temp);								// call do_led
		printf("temp = %d\r\n",temp);						// prints temperature in TeraTerm
		do_rgb(temp);								// call do_rgb
	}
}