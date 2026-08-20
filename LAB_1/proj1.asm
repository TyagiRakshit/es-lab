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
	MOV R0,#0x10
	MOV R1,R0 
	LDR R0,=src1
	LDR R2,[R0]
	LDR R1,=src2
	LDR R3,[R1]
	ADD R2,R3
	LDR R4,=dst
	STR R2,[R4]
stop b stop
src1 DCD 0X12345678
src2 DCD 0X23456789
	area mydata,data,readwrite
dst dcd 0X70000000
	END
	
	