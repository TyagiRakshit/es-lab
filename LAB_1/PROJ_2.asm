	AREA RESET,DATA,READONLY
	EXPORT __Vectors

__Vectors
	DCW 0x10001000     ;STACK POINTER VALUE WHEN STACK IS EMPTY
	DCW Reset_Handler  ;reset vector
	
	ALIGN
	
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler

	LDRH R0,= src1
	LDRH R1,[R0] 
	LDRH R2,= dst
	STRH R1,[R2]
	ADD R0,#2
	ADD R2,#2
	LDRH R3,[R0]
	STRH R3,[R2]


stop b stop
src1 dcw 0xFF12,0XB502
	AREA mydata,data,READWRITE
dst dcw 0,0
	END
	