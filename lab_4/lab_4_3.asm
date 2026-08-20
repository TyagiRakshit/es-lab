; PROGRAM TO CONVERT A 2-DIGIT HEX NUMBER TO PACKED BCD
; INPUT:  0x19 (25 in decimal)
; OUTPUT: 0x25 (Packed BCD)

    AREA RESET, DATA, READONLY
    EXPORT __Vectors

__Vectors
    DCD 0x10001000     ; Initial Stack Pointer
    DCD Reset_Handler  ; Reset Vector

    ALIGN

    AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler

Reset_Handler
    LDR R0, =HEX_NUM   
    LDRB R1, [R0]      

    MOV R2, #10        

    UDIV R3, R1, R2    ; R3 = 25/10 =2 

    MUL R4, R3, R2     ; R4 = 2*10 = 20
    SUB R5, R1, R4     ; R5 = 25-20 = 5 

    LSL R3, R3, #4     
    ORR R6, R3, R5     

    LDR R0, =BCD_OUT   
    STRB R6, [R0]      

STOP B STOP            

    ALIGN
HEX_NUM DCD 0x19       

    AREA mydata, DATA, READWRITE
    ALIGN
BCD_OUT DCB 0          

    END