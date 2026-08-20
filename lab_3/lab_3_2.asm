;Write a program to add two 128 bit numbers stored in code segment and store the result in data segment.
;Hint: Use indexed addressing mode.
	
; PROGRAM TO ADD TWO 128-BIT NUMBERS USING INDEXED ADDRESSING MODE

    AREA RESET, DATA, READONLY
    EXPORT __Vectors

__Vectors
    DCD 0x10001000     ; Stack Pointer
    DCD Reset_Handler  ; Reset vector

    ALIGN

    AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler

Reset_Handler
    LDR R0, =NUM1      ; Base address of 128-bit NUM1 in CODE segment
    LDR R1, =NUM2      ; Base address of 128-bit NUM2 in CODE segment
    LDR R6, =SUM       ; Base address of SUM in DATA segment

    MOV R2, #0         ; Offset index (starts at 0 bytes)
    
    ; --- Word 0: Lowest 32 bits (Bits 0–31) ---
    LDR R3, [R0, R2]   ; Indexed Mode: Load NUM1[0]
    LDR R4, [R1, R2]   ; Indexed Mode: Load NUM2[0]
    ADDS R5, R3, R4    ; Add lowest words and update CARRY flag
    STR R5, [R6, R2]   ; Store result[0] in SUM

    ; --- Word 1: Bits 32–63 ---
    ADD R2, R2, #4     ; Advance offset by 4 bytes (Offset = 4)
    LDR R3, [R0, R2]   ; Load NUM1[1]
    LDR R4, [R1, R2]   ; Load NUM2[1]
    ADCS R5, R3, R4   ; Add with Carry (ADCS = R3 + R4 + Carry)
    STR R5, [R6, R2]   ; Store result[1] in SUM

    ; --- Word 2: Bits 64–95 ---
    ADD R2, R2, #4     ; Advance offset by 4 bytes (Offset = 8)
    LDR R3, [R0, R2]   ; Load NUM1[2]
    LDR R4, [R1, R2]   ; Load NUM2[2]
    ADCS R5, R3, R4   ; Add with Carry
    STR R5, [R6, R2]   ; Store result[2] in SUM

    ; --- Word 3: Highest 32 bits (Bits 96–127) ---
    ADD R2, R2, #4     ; Advance offset by 4 bytes (Offset = 12)
    LDR R3, [R0, R2]   ; Load NUM1[3]
    LDR R4, [R1, R2]   ; Load NUM2[3]
    ADCS R5, R3, R4   ; Add with Carry
    STR R5, [R6, R2]   ; Store result[3] in SUM

STOP
    B STOP           

    ALIGN
; 128-bit Number 1 = 0x11111111_22222222_33333333_44444444 (Stored LSB to MSB)
NUM1 DCD 0x44444444, 0x33333333, 0x22222222, 0x11111111

; 128-bit Number 2 = 0x88888888_77777777_66666666_55555555 (Stored LSB to MSB)
NUM2 DCD 0x55555555, 0x66666666, 0x77777777, 0x88888888

    AREA mydata, DATA, READWRITE
    ALIGN
; Reserve 16 bytes (4 words) for 128-bit result
SUM  DCD 0, 0, 0, 0

    END