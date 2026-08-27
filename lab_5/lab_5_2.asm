; PROGRAM TO FIND THE FACTORIAL OF AN UNSIGNED NUMBER USING RECURSION

    AREA RESET, DATA, READONLY
    EXPORT __Vectors

__Vectors
    DCD 0x10001000     ; Initial Stack Pointer (Top of SRAM)
    DCD Reset_Handler  ; Reset vector points to Reset_Handler

    ALIGN

    AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler

Reset_Handler
    ; --- Load Input Number ---
    LDR R0, =NUM       ; Pointer to input number in Flash
    LDR R0, [R0]       ; R0 = n (e.g., n = 5)

    ; --- Call Recursive Function ---
    BL FACTORIAL       ; Branch with Link to recursive function
                       ; R0 will hold the final result (5! = 120 = 0x78)

    ; --- Store Result in RAM ---
    LDR R1, =RESULT    ; Pointer to RESULT in SRAM
    STR R0, [R1]       ; Store n! into memory

STOP B STOP            ; Infinite loop to end program

; --- RECURSIVE FACTORIAL FUNCTION ---
; Input:  R0 = n
; Output: R0 = n!
FACTORIAL
    PUSH {R4, LR}      ; Save working register R4 and Link Register (return address)

    CMP R0, #1         ; Base Case: Check if n <= 1
    BLE BASE_CASE      ; If n <= 1, jump to base case

    MOV R4, R0         ; Save current value of 'n' in R4
    SUB R0, R0, #1     ; R0 = n - 1
    BL FACTORIAL       ; Recursive Call: FACTORIAL(n - 1)
                       ; Upon return, R0 contains (n - 1)!

    MUL R0, R4, R0     ; Combine step: R0 = n * (n - 1)!
    B FACT_EXIT

BASE_CASE
    MOV R0, #1         ; Return 1 for 0! or 1!

FACT_EXIT
    POP {R4, PC}       ; Restore R4 and return from function by popping LR into PC

    ALIGN
; Input number in CODE Segment
NUM DCD 5              ; Compute 5! (5 * 4 * 3 * 2 * 1 = 120)

    AREA mydata, DATA, READWRITE
    ALIGN
; Output location in SRAM (0x10000000)
RESULT DCD 0           ; Space to store the result (120 -> 0x00000078)

    END