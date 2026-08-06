;b.When the source and destination blocks are overlapping
	AREA RESET,DATA,READONLY
	EXPORT __Vectors

__Vectors
	DCD 0x10001000     ;STACK POINTER VALUE WHEN STACK IS EMPTY
	DCD Reset_Handler  ;reset vector
	
	ALIGN
	
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler
	LDR R0, =src1
	ADD R0,R0, #36
	
	LDR R1, =dst
	ADD R1,R1, #36
	MOV R2, #10         

L1  LDR R3, [R0], #-4   
    STR R3, [R1], #-4   
    SUBS R2, R2, #1     
    BNE L1              
	

stop B stop             
src1 DCD 0x20100123, 0x70023021, 0x21345678, 0x11111111, 0x22222222
     DCD 0xAAAAAAAA, 0x33333333, 0x88888888, 0x99999999, 0x44444444

    area dataseg , data,READWRITE
dst DCD 0,0,0,0,0,0,0,0,0,0

    END