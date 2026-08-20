; PROGRAM TO ADD TEN 32-BIT NUMBERS FROM CODE SEGMENT AND STORE IN DATA SEGMENT

    AREA RESET, DATA, READONLY
    EXPORT __Vectors

__Vectors
    DCD 0x10001000     ; Stack Pointer value when stack is empty
    DCD Reset_Handler  ; Reset vector points to Reset_Handler

    ALIGN

    AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler

Reset_Handler
    LDR R0, =NUMBERS   ; R0 = Pointer to array in code segment
    MOV R1, #10        ; R1 = Loop counter (10 numbers)
    MOV R2, #0         ; R2 = Accumulator for the sum (initialized to 0)

LOOP
    LDR R3, [R0], #4   ; Load 32-bit number from [R0] into R3, post-increment R0 by 4 bytes
    ADD R2, R2, R3     ; Accumulate: R2 = R2 + R3
    SUBS R1, R1, #1    ; Decrement counter and set Zero flag
    BNE LOOP           ; Repeat loop until R1 == 0

    LDR R4, =SUM       ; R4 = Pointer to SUM in data segment
    STR R2, [R4]       ; Store the total sum into memory location SUM

STOP
    B STOP             ; Infinite loop to end execution

    ALIGN              ; Ensures 4-byte alignment for the array
NUMBERS
    DCD 0x0000000A, 0x00000014, 0x0000001E, 0x00000028, 0x00000032, 0x0000003C, 0x00000046, 0x00000050, 0x0000005A, 0x00000064     
	;10,20,30,40,50,60,70,80,90,100
    AREA mydata, DATA, READWRITE
    ALIGN
SUM DCD 0              ; Reserve 4 bytes in RAM to store the final result

    END