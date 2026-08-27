; PROGRAM TO SEARCH AN ELEMENT IN AN ARRAY USING LINEAR SEARCH

    AREA RESET, DATA, READONLY
    EXPORT __Vectors

__Vectors
    DCD 0x10001000     ; Stack Pointer initial value
    DCD Reset_Handler  ; Reset vector pointing to execution entry point

    ALIGN

    AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler

Reset_Handler
    LDR R0, =ARR       ; R0 = Pointer to array base address
    MOV R1, #10        ; R1 = Array size (10 elements)
    
    LDR R2, =KEY       ; Load address of search key
    LDR R2, [R2]       ; R2 = Target value to search (e.g., 25)

    MOV R3, #0         ; R3 = Index counter (i = 0)

SEARCH_LOOP
    CMP R3, R1         ; Check if index i == 10 (End of array)
    BGE NOT_FOUND      ; If i >= 10, element is not present

    LDR R4, [R0, R3, LSL #2]  ; R4 = ARR[i]  (Base + i * 4)

    CMP R4, R2         ; Compare ARR[i] with target key
    BEQ ELEMENT_FOUND  ; If ARR[i] == KEY, match found!

    ADD R3, R3, #1     ; i++
    B SEARCH_LOOP      ; Repeat loop

ELEMENT_FOUND
    LDR R5, =INDEX     ; Load destination RAM address
    STR R3, [R5]       ; Store found index (0-based) into RAM
    B STOP

NOT_FOUND
    LDR R5, =INDEX     ; Load destination RAM address
    MOV R6, #-1        ; Store -1 (0xFFFFFFFF) for element not found
    STR R6, [R5]

STOP B STOP            ; Infinite loop to end program

    ALIGN
; Data segment in Flash Memory
ARR DCD 50, 7, 25, 2, 69, 18, 1, 136, 35, 15  ; Array of 10 elements
KEY DCD 25                                   ; Target element to search

    AREA mydata, DATA, READWRITE
    ALIGN
; Output location in SRAM (0x10000000)
INDEX DCD 0            ; Space to store index of found element

    END