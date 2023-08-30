;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

; R0: digit(the output)
; R1: digit counter
; R2: bit counter, temp register
; R3: input
; R4: Histogram pointer
; R5: print counter for the historgram


LD R4, HIST_ADDR	; initialize histogram pointer
AND R5, R5, #0


WORDLOOP

LD R3, NUM_BINS
NOT R3, R3
ADD R3, R3, #1
ADD R3, R3, R5 ; Subtract NUM_BINS from the  current histogram row count
BRz DONE 		


LD R0, HISTROWCONST   ; PRINT corresponding character
ADD R0, R0, R5
OUT
LD R0, SPACECONST	; print space
OUT



LDR R3, R4, #0 ; load the value into the input using the pointer
	

; Prints each 16bit hex word
AND R1, R1, #0 ; initialize digit counter
ADD R1, R1, #4

DIGITS  AND R1, R1, R1
        ;BRnz WORDLOOP    ; LOOP again if we printed 4 digits

        AND R0, R0, #0  ; init digit


        AND R2, R2, #0 ; init bit counter
        ADD R2, R2, #4  ; bit counter start from 4      

BITS    AND R2, R2, R2  ; load R2(bitcnt to nzp) MAY NOT NEED THIS LINE
        BRnz PRINT      ; if bitCnt <= 0 branch         

        ADD R0, R0, R0  ; shift digit(output) left

        AND R3, R3, R3  ; load R3 to nzp
        BRn #2          ; if MSB == 1 branch

        ADD R0, R0, #0  ; if MSB == 0           
        BRnzp #1
        ADD R0, R0, #1  ; if MSB == 1

        ADD R3, R3, R3  ; shift R3 left

        ADD R2, R2, #-1 ; decrement bit counter
        BRnzp BITS


PRINT	

		AND R0, R0, R0  ; load R0 for nzp
        ADD R2, R0, #-9 ; repurpose R2 for comparing of R0 <= 9

        ; set the ascii offset  
        BRnz #2
        LD R2, PRINTCONST2
        BRnzp #1
        LD R2, PRINTCONST1 ; if R0 <= 9

		

        ADD R0, R0, R2 ; add ascii offset to R0

        OUT ; Print character to screen

        ADD R1, R1, #-1 ; Decrement digit counter

		

		

        BRp DIGITS ; Contiunue printing rest of the word



LD R0, NEWLINECONST	; prints \n
OUT 
ADD R4, R4, #1	; Increment hist pointer
ADD R5, R5, #1 	; Increment hist Counter
BRnzp WORDLOOP





DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; Constants needed for offseting ascii values
PRINTCONST1 .FILL x0030 
PRINTCONST2 .FILL x0037

HISTROWCONST .FILL x0040
SPACECONST	.FILL x0020
NEWLINECONST .FILL x000A

; for testing, you can use the lines below to include the string in this
; program...
 ;STR_START	.FILL STRING	; string starting address
 ;STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
