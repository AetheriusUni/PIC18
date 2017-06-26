; THIS SECOND ASSEMBLY LANGUAGE PROGRAM WILL READ THE VALUES OF ALL 

; THE BITS 0-3 OF PORT A AND OUTPUT THEM 

; TO THE PINS 0 THROUGH 3 OF PORT B 

#include<P18F4321.inc> 

 config OSC = INTIO2 

 config WDT = OFF 

 config LVP = OFF 

 config BOR = OFF 

 ORG 0x0000 

; CODE STARTS FROM THE NEXT LINE 

START: 

 MOVLW 0xFF ; Load W with 0xFF 

 MOVWF TRISA ; Set PORT A as all inputs 

 MOVLW 0xF0 ; Load W with 0xF0 

 MOVWF TRISB ; Make PORT B bits 0-3 as outputs 

 MOVLW 0x0F ; Load W with 0x0F 

 MOVWF ADCON1 ; Set ADCON1 

LOOP: 

 MOVF PORTA, W ; Read from PORT A and move it into W 

 MOVWF PORTB ; Move from W to PORT B 

 GOTO LOOP ; Loop forever 

 END