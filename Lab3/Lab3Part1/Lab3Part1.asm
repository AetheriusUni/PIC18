; THIS FIRST ASSEMBLY LANGUAGE PROGRAM WILL FLASH AN LED CONNECTED 

; TO THE PINS 0 THROUGH 3 OF PORT B 

#include<P18F4321.inc> 

config OSC = INTIO2 

config WDT = OFF 

config LVP = OFF 

config BOR = OFF 

ORG 0x0000 

 ; CODE STARTS FROM THE NEXT LINE 

START: 

 MOVLW 0xF0 ; Load W with 0x0 

 MOVWF TRISB ; Make PORT B bits 0-7 as outputs 

LOOP: 

MOVLW 0x0A ; Load W with value 0x0A 

MOVWF PORTB ; Output to PORT B 

; NESTED DELAY LOOP 

MOVLW 0xFF ; Load 0xFF to W 

MOVWF 0x20 ; Load W to memory 0x20 (value 0xFF) 

LOOP1_1: 

NOP ; Do nothing 

MOVLW 0xFF ; Load 0xFF to W 

MOVWF 0x21 ; Load W to memory 0x21 (value 0xFF) 

LOOP2_1: 

NOP ; Do nothing 

DECF 0x21,F ; Decrement memory location 0x21 

BNZ LOOP2_1 ; If value not zero, go back to LOOP2_1 

DECF 0x20,F ; Decrement memory location 0x20 

BNZ LOOP1_1 ; If value not zero, go back to LOOP1_1 

MOVLW 0x05 ; Load W with value 0x05 

MOVWF PORTB ; Output to PORT B (flipping the LEDs) 

; NESTED DELAY LOOP AGAIN 

MOVLW 0xFF ; Load 0xFF to W 

MOVWF 0x20 ; Load W to memory 0x20 (value 0xFF) 

LOOP1_2: 

NOP ; Do nothing 

MOVLW 0xFF ; Load 0xFF to W 

MOVWF 0x21 ; Load W to memory 0x21 (value 0xFF) 

LOOP2_2: 

 NOP ; Do nothing 

DECF 0x21,F ; Decrement memory location 0x21 

BNZ LOOP2_2 ; If value not zero, go back to LOOP2_2 

DECF 0x20,F ; Decrement memory location 0x20 

BNZ LOOP1_2 ; If value not zero, go back to LOOP1_2 

; START ALL OVER AGAIN END 

GOTO LOOP 

 END