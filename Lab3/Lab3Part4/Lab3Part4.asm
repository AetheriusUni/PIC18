#include<P18F4321.inc> 
	config OSC = INTIO2 
	config WDT = OFF 
	config LVP = OFF 
	config BOR = OFF 

	ORG 0x0000 					;start at address 0
 
START: 
 
X EQU 0x10 						;sets X to location 10H
Y EQU 0x4D						;sets Y to location 4DH

 	MOVLW 0xFF 					;Load W with 0xFF 
	MOVWF TRISA 					;Set PORT A as all inputs 
 	MOVLW 0xF0 					;Load W with 0xF0 
 	MOVWF TRISC 					;Make PORT C bits 0-3 as outputs 
 	MOVLW 0x0F 					;Load W with 0x0F 
 	MOVWF ADCON1 					;Set ADCON1 

LOOP: 

	BTFSC PORTA, 3 					;If Bit 3 of PORTA = 0, skip the next instruction 
 	GOTO PA3EQ1 					;else check value of Bit 3 
 
 
PA3EQ0:

	BTFSC PORTA, 2					;If bit 2 of PORTA = 0, skip the next instruction
	GOTO GREEN					;else check value of Bit 2 


RED:

	MOVLW 0x01					;bit in binary is 001 so turns on red pin
	MOVWF PORTC					;set WREG = PORTC
	MOVLW X						;Load W with X
	GOTO LOOP1					;go to LOOP1


GREEN:

	MOVLW 0x02					;bit in binary is 010 so turns on green pin
	MOVWF PORTC					;set WREG = PORTC
	MOVLW 2*X					;Load W with 2*X
	GOTO LOOP1					;go to LOOP1

PA3EQ1: 

	BTFSC PORTA, 2; 				;if bit 2 of PORTA = 0, skip the next instruction
	GOTO WHITE					;else check value of bit 2


BLUE:

	MOVLW 0x04					;bit in binary is 100 so turns on blue pin
	MOVWF PORTC					;set WREG = PORTC
	MOVLW 3*X					;Load W with 3*X
	GOTO LOOP1					;go to LOOP1

WHITE:

	MOVLW 0x07					;bit in binary is 111 so turns on all three pins which makes the LED white
	MOVWF PORTC					;set WREG = PORTC
	MOVLW 5*X					;Load W with 5*X
	GOTO LOOP1					;go to LOOP1

LOOP1:
	MOVWF 0x22					;set WREG = 0x22
	MOVWF 0x23					;set WREG = 0x23

	;nested delay loop

LOOP1_1: 

	MOVLW Y 					;Load 0x4D to W 
	MOVWF 0x21 					;Load W to memory 0x21 (value 0x4D) 

LOOP2_1: 

	NOP 						;Do nothing 
	DECF 0x21,F 					;Decrement memory location 0x21 
	BNZ LOOP2_1 					;If value not zero, go back to LOOP2_1 
	DECF 0x22,F 					;Decrement memory location 0x22 
	BNZ LOOP1_1 					;If value not zero, go back to LOOP1_1 
	MOVLW 0x00 					;Load W with value 0x05 
	MOVWF PORTC 					;Output to PORT B (flipping the LEDs) 

	;nested delay loop again

LOOP1_2: 

	MOVLW Y 					;Load 0x4D to W 
	MOVWF 0x21 					;Load W to memory 0x21 (value 0x4D) 

LOOP2_2: 

	NOP 						;Do nothing 
	DECF 0x21,F 					;Decrement memory location 0x21 
	BNZ LOOP2_2 					;If value not zero, go back to LOOP2_2 
	DECF 0x23,F 					;Decrement memory location 0x23 
	BNZ LOOP1_2 					; If value not zero, go back to LOOP1_2 

	;start over again

	GOTO LOOP 

	END


