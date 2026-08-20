; PROGRAM TO CONVERT 2-DIGIT BCD TO EQUIVALENT HEXADECIMAL
; INPUT:  0x25 (BCD representation of decimal 25)
; OUTPUT: 0x00000019 (25 in Hexadecimal)

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
    LDR R0, =BCD_NUM  
    LDRB R1, [R0]      

    
    LSR R2, R1, #4     
    MOV R3, #10        
    MUL R2, R2, R3     
    
    AND R3, R1, #0x0F 
    ADD R4, R2, R3     

    LDR R0, =RESULT   
    STRB R4, [R0]      ; Store 8-bit hex result into RAM

STOP B STOP            

    ALIGN
BCD_NUM DCD 0x25       

    AREA mydata, DATA, READWRITE
    ALIGN
RESULT DCB 0          

    END