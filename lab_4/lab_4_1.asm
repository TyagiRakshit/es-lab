; PROGRAM TO CONVERT A 2-DIGIT HEX NUMBER TO ASCII
; INPUT:  0x21
; OUTPUT: 0x3231 ('2' -> 0x32, '1' -> 0x31)

    AREA RESET, DATA, READONLY
    EXPORT __Vectors

__Vectors
    DCD 0x10001000     ; Initial Stack Pointer value
    DCD Reset_Handler  ; Reset Vector

    ALIGN

    AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler

Reset_Handler
    LDR R0, =HEX_NUM   
    LDRB R1, [R0]      
    LSR R2, R1, #4     
    ADD R2, R2, #0x30  

    AND R3, R1, #0x0F  ;(R3 = 0x01)
    ADD R3, R3, #0x30  

    LSL R2, R2, #8     ;(R2 = 0x3200)
    ORR R4, R2, R3     ;(R4 = 0x3231)

    LDR R0, =ASCII_OUT 
    STRH R4, [R0]      

STOP B STOP            

    ALIGN
HEX_NUM DCD 0x21       

    AREA mydata, DATA, READWRITE
    ALIGN
ASCII_OUT DCW 0        

    END