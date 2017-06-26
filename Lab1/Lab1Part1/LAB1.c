#include <p18f4321.h>

#pragma config OSC = INTIO2 

#pragma config WDT=OFF 

#pragma config LVP=OFF 

#pragma config BOR =OFF 

#define delay 5 

// Prototype Area 

void Init_ADC(void); 

unsigned int Get_Full_ADC(void); 

void Flash_LED(unsigned char); 

void main(void) 

{ 

 unsigned int ADC_Result; 

 Init_ADC(); 

 TRISB =0x00; 

 while(1) 

 { 

 ADC_Result = Get_Full_ADC(); 

 Flash_LED(ADC_Result); 

 } 

} 

void Init_ADC(void) 

{ 

 ADCON0=0x01; // select channel AN0, and turn on the ADDC subsystem 

 ADCON1=0x0E; // set pin 2 as analog signal, VDD-VSS as reference voltage 

 ADCON2=0xA9; // Set the bit conversion time (TAD) and acquisition time 

} 

unsigned int Get_Full_ADC(void) 

{ 

int result; 

 ADCON0bits.GO=1; // Start Conversion 

 while(ADCON0bits.DONE==1); // Wait for conversion to be completed (DONE=0) 

 result = (ADRESH * 0x100) + ADRESL; // Combine result of upper byte and lower byte into 

 return result; // return the most significan 8- bits of the result. 

} 

void Flash_LED(unsigned char ADC_result) 

{ 

unsigned int counter1, counter2; 

 LATB = 0x0A; 

 for (counter2=delay; counter2>0; --counter2) 

 { 

 for (counter1=ADC_result ; counter1>0; -- counter1); 

 } 

 LATB = 0x05; 

 for (counter2=delay; counter2>0; --counter2) 

 { 

 for (counter1=ADC_result ; counter1>0; -- counter1); 

 } 

}