; PROGRAM TO FIND LCM OF TWO 32-BIT NUMBERS USING RESET_HANDLER

    AREA RESET, DATA, READONLY
    EXPORT __Vectors

__Vectors
    DCD 0x10001000     ; Initial Stack Pointer value
    DCD Reset_Handler  ; Reset vector points to Reset_Handler

    ALIGN

    AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler

Reset_Handler          ; Entry point matches vector table
    LDR R0, =NUM_A     ; Pointer to NUM_A
    LDR R1, [R0]       ; R1 = a (First number)

    LDR R0, =NUM_B     ; Pointer to NUM_B
    LDR R2, [R0]       ; R2 = b (Second number)

    MOV R3, #1         ; R3 = i (multiplier, initialized to 1)

LCM_LOOP
    MUL R4, R3, R1     ; R4 = i * a (candidate LCM value)

    ; --- Compute Remainder: R5 = (i * a) mod b ---
    UDIV R5, R4, R2    ; R5 = (i * a) / b  [Quotient]
    MUL R6, R5, R2     ; R6 = Quotient * b
    SUB R5, R4, R6     ; R5 = (i * a) - (Quotient * b)  [Remainder]

    CMP R5, #0         ; Check if remainder == 0
    BEQ LCM_FOUND      ; If remainder == 0, exit loop!

    ADD R3, R3, #1     ; Else i++
    B LCM_LOOP         ; Repeat loop

LCM_FOUND
    LDR R0, =LCM_RESULT; Pointer to LCM_RESULT in RAM
    STR R4, [R0]       ; Store final LCM into memory

STOP B STOP            ; Infinite loop to end execution

    ALIGN
NUM_A DCD 12           ; First number  (a = 12)
NUM_B DCD 15           ; Second number (b = 15)

    AREA mydata, DATA, READWRITE
    ALIGN
LCM_RESULT DCD 0       ; Space in RAM to store final LCM

    END
	