;Write an assembly program to sort an array using selection sort
; PROGRAM TO SORT AN ARRAY OF TEN 32-BIT NUMBERS USING SELECTION SORT
; ARRAY IS SORTED IN-PLACE IN ASCENDING ORDER IN DATA SEGMENT (RAM)

    AREA RESET, DATA, READONLY
    EXPORT __Vectors

__Vectors
    DCD 0x10001000     ; Stack Pointer initial value (Top of SRAM)
    DCD Reset_Handler  ; Reset Vector pointing to execution entry point

    ALIGN

    AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler

Reset_Handler
    ; --- Step 1: Copy Input Array from FLASH (CODE) to RAM (DATA) ---
    LDR R0, =SRC_ARRAY 
    LDR R1, =ARR_RAM   
    MOV R2, #10       

COPY_LOOP
    LDR R3, [R0], #4   ; Load word from code, increment pointer
    STR R3, [R1], #4   ; Store word into RAM, increment pointer
    SUBS R2, R2, #1    ; Decrement counter
    BNE COPY_LOOP

    ; --- Step 2: Initialize Selection Sort Parameters ---
    LDR R0, =ARR_RAM   ; Base address of RAM array (i = 0 pointer)
    MOV R1, #0         ; Outer loop index i = 0

OUTER_LOOP
    CMP R1, #9         ; Outer loop runs for i = 0 to 8 (N-1 passes)
    BGE SORT_DONE      ; If i >= 9, 
	                   ;sorting done

    ADD R2, R1, #1     ; Inner loop index j = i + 1
    MOV R3, R1         ; R3 stores index of minimum element (min_idx = i)

INNER_LOOP
    CMP R2, #10        ; Check if j == 10 (end of array)
    BGE SWAP_STAGE     ; If j >= 10, inner loop finished -> swap

    ; Compare ARR[j] and ARR[min_idx]
    ADD R4, R0, R2, LSL #2   ; R4 = &ARR[j]  (Base + j * 4)
    LDR R5, [R4]             ; R5 = ARR[j]

    ADD R6, R0, R3, LSL #2   ; R6 = &ARR[min_idx] (Base + min_idx * 4)
    LDR R7, [R6]             ; R7 = ARR[min_idx]

    CMP R5, R7               ; Compare ARR[j] with ARR[min_idx]
    BHS NEXT_INNER           ; If ARR[j] >= ARR[min_idx], skip update

    MOV R3, R2               ; Else update min_idx: min_idx = j

NEXT_INNER
    ADD R2, R2, #1     ; j++
    B INNER_LOOP

SWAP_STAGE
    ; Swap ARR[i] and ARR[min_idx]
    CMP R3, R1         ; Check if min_idx == i
    BEQ NEXT_OUTER     ; If min_idx == i, no swap needed

    ADD R4, R0, R1, LSL #2   ; R4 = &ARR[i]
    LDR R5, [R4]             ; R5 = ARR[i]

    ADD R6, R0, R3, LSL #2   ; R6 = &ARR[min_idx]
    LDR R7, [R6]             ; R7 = ARR[min_idx]

    STR R7, [R4]             ; ARR[i] = ARR[min_idx]
    STR R5, [R6]             ; ARR[min_idx] = ARR[i]

NEXT_OUTER
    ADD R1, R1, #1     ; i++
    B OUTER_LOOP

SORT_DONE
STOP B STOP            ; Infinite loop to end execution

    ALIGN
SRC_ARRAY 
    DCD 0x00000032, 0x00000007, 0x00000019, 0x00000002, 0x00000045
    DCD 0x00000012, 0x00000001, 0x00000088, 0x00000023, 0x0000000F
    ; Decimal values: 50, 7, 25, 2, 69, 18, 1, 136, 35, 15

    AREA mydata, DATA, READWRITE
    ALIGN
ARR_RAM SPACE 40       

    END