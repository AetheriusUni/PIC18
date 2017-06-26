#include <p18f4321.h> 

#include <stdio.h> 

#include <math.h> 

#include <usart.h> 

#pragma config OSC = INTIO2 

#pragma config WDT=OFF 

#pragma config LVP=OFF 

#pragma config BOR =OFF 

void do_print_float ( float float_num, char num_digit) 

{ 

int integer; 

int mantissa; 

float multiplier; 

 integer = (int) float_num; 

 if (num_digit == 1) 

 { 

 mantissa = (int) (float_num*10) - (integer*10); 

 printf ("%d.%01d\r\n", integer, mantissa); 

 } 

 else if (num_digit == 2) 

 { 

 mantissa = (int) (float_num*100) - (integer*100); 

 printf ("%d.%02d\r\n", integer, mantissa); 

 } 

 else 

 { 

 mantissa = (int) (float_num*1000) - (integer*1000); 

 printf ("%d.%03d\r\n", integer, mantissa); 

 } 

} 

void init_UART() 

{ 

 OpenUSART (USART_TX_INT_OFF & USART_RX_INT_OFF & 

USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & 

USART_BRGH_HIGH, 25); 

 OSCCON = 0x60; 

} 

void main(void) 

{ 

char k; 

float t; 

 init_UART(); 

 while(1) 

 { 

 float t1;

 t= 19.909; 
 
 t1 = t + 0.345;

 printf ("\r\nHello World! First Floating Point Print with 1 decimal place "); 

 do_print_float(t,1); 

 printf ("\r\nHello World! First Floating Point print with 2 decimal places "); 

 do_print_float(t,2); 
 
 printf ("\r\nHello my name is Marc. Second Floating Point Print with 1 decimal place");
 
 do_print_float(t1,1);
 
 printf ("\r\nHello my name is Marc. Second Floating Point Print with 2 decimal places");
 
 do_print_float(t1,2);
 
 printf ("\r\nHello my name is Marc. Second Floating Point Print with 3 decimal places");
 
 do_print_float(t1,3);
 
 } 

}