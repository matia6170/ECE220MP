.ORIG x3000

; Hyunwoo(Matia) Choi
; netId: hyunwoo6

; R0: digit(the thing to print)
; R1: digit counter
; R2: bit counter
; R3: input


; init digit counter
AND R1, R1, #0
ADD R1, R1, #4

DIGITS	AND R1, R1, R1
	BRnz ENDPROG	; HALT program if we printed 4 digits
	
	AND R0, R0, #0	; init digit


	AND R2, R2, #0 ; init bit counter
	ADD R2, R2, #4	; bit counter start from 4	
	
BITS	AND R2, R2, R2	; load R2(bitcnt to nzp) MAY NOT NEED THIS LINE
	BRnz PRINT 	; if bitCnt <= 0 branch 	

	ADD R0, R0, R0 	; shift digit(output) left

	AND R3, R3, R3	; load R3 to nzp
	BRn #2		; if MSB == 1 branch

	ADD R0, R0, #0	; if MSB == 0 		
	BRnzp #1
	ADD R0, R0, #1	; if MSB == 1

	ADD R3, R3, R3	; shift R3 left
	
	ADD R2, R2, #-1	; decrement bit counter
	BRnzp BITS

	
PRINT	AND R0, R0, R0	; load R0 for nzp
	
	ADD R2, R0, #-9 ; repurpose R2 for comparing of R0 <= 9

	; set the ascii offset	
	BRnz #2
	LD R2, PRINTCONST2
	BRnzp #1
	LD R2, PRINTCONST1 ; if R0 <= 9



	ADD R0, R0, R2 ; add ascii offset to R0

	OUT ; Print character to screen

	ADD R1, R1, #-1
	
	BRnzp DIGITS
	

ENDPROG	HALT 

PRINTCONST1 .FILL x0030
PRINTCONST2 .FILL x0037


.END
