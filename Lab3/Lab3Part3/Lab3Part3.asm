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

BTFSC PORTA, 3 ; If Bit 3 of PORTA = 0,; skip the next instruction 

 GOTO CASE1 ; else go to CASE1 (PORT A Bit 3 = 1) 

CASE0: 

 BSF PORTB, 0 ; If A3 = 0, set B0 

BCF PORTB, 1 ; and clear B1 

 GOTO LOOP ; go back to Loop 

CASE1: 

 BCF PORTB, 0 ; If A3 = 1, clear B0 

 BSF PORTB, 1 ;set B1 

 GOTO LOOP ; go back to Loop
 
 END