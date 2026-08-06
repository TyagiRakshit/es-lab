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
    
    LDR R1, =src1
    ADD R1, R1, #18     

    MOV R2, #5         

REVERSE_LOOP
    LDRH R3, [R0]        
    LDRH R4, [R1]      

    STRH R4, [R0], #2    
    STRH R3, [R1], #-2  

    SUBS R2, R2, #1     
    BNE REVERSE_LOOP
stop B stop             
src1 DCW 0x0010, 0x7002, 0x2134, 0x1111, 0x2222
     DCW 0x0001, 0x3333, 0x8888, 0x9999, 0x4444

    area dataseg , data,READWRITE
dst DCD 0,0,0,0,0,0,0,0,0,0

    END