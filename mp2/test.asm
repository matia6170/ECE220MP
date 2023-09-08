.ORIG x3000
	
;your code goes here

	AND R0,R0,#0		;Reset all REG
	AND R1,R1,#0		;Temp Var to Check
	AND R2,R2,#0
	AND R3,R3,#0		;Value of START stack
	AND R4,R4,#0		;Value of TOP stack
	AND R5,R5,#0
	AND R6,R6,#0
	AND R7,R7,#0

EVALUATE 
	GETC			;
	OUT			;

CHECK_EQ
	AND R1,R1,#0
	LD R1,EQUAL_SIGN
	NOT R1,R1
	ADD R1,R1,#1
	ADD R1,R1,R0
	BRz CHECK_STACK

CHECK_SP
	AND R1,R1,#0
	LD R1,SPACE_SIGN
	NOT R1,R1
	ADD R1,R1,#1
	ADD R1,R1,R0
	BRz EVALUATE		;

CHECK_NUM
;Checking if it is 0~9
	AND R1,R1,#0
	LD R1,NINE_SIGN
	NOT R1,R1
	ADD R1,R1,#1
	ADD R1,R1,R0
	BRp CHECK_OP

	AND R1,R1,#0
	LD R1,ZERO_SIGN
	NOT R1,R1
	ADD R1,R1,#1
	ADD R1,R1,R0
	BRn CHECK_OP

;It is 0~9
	AND R1,R1,#0
	LD R1,ZERO_SIGN
	NOT R1,R1
	ADD R1,R1,#1
	ADD R0,R1,R0
	JSR PUSH
	BRnzp EVALUATE
	
CHECK_OP
	AND R1,R1,#0
	LD R1,ADD_SIGN
	NOT R1,R1
	ADD R1,R1,#1
	ADD R1,R1,R0
	BRz PLUS

	AND R1,R1,#0
	LD R1,SUB_SIGN
	NOT R1,R1
	ADD R1,R1,#1
	ADD R1,R1,R0
	BRz MIN

	AND R1,R1,#0
	LD R1,MUL_SIGN
	NOT R1,R1
	ADD R1,R1,#1
	ADD R1,R1,R0
	BRz MUL

	AND R1,R1,#0
	LD R1,DIV_SIGN
	NOT R1,R1
	ADD R1,R1,#1
	ADD R1,R1,R0
	BRz DIV

	AND R1,R1,#0
	LD R1,POW_SIGN
	NOT R1,R1
	ADD R1,R1,#1
	ADD R1,R1,R0
	BRz EXP
	
	BRnzp INVALID		;Print Invalid

CHECK_STACK
	LD R3,STACK_START
	LD R4,STACK_TOP
	NOT R4,R4
	ADD R3,R3,R4
	BRnp INVALID		;Invalid

;There is one in stack
	JSR POP			;Pop the single value
	BRnzp PRINT_HEX		;Covert the binary to hex

PRE_OP
	ST R7, SAVE_R7
	LD R3,STACK_START
	LD R4,STACK_TOP
	NOT R4,R4
	ADD R3,R3,R4
	ADD R3,R3,#-1
	BRn INVALID		;Invalid

;There is two in stack
	JSR POP
	AND R3,R0,R0	
	JSR POP
	AND R4,R0,R0	
	LD R7,SAVE_R7
	RET

INVALID
	LEA R0,INVALID_SIGN
	PUTS
	BRnzp DONE

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX

AND R5,R0,R0			;Final Answer
ST R5, SAVE_ANS			;Save Answer

AND R1,R1,#0			;
AND R2,R2,#0
AND R4,R3,#0
AND R4,R4,#0
AND R5,R5,#0
AND R6,R6,#0

ADD R3,R3,#4
ADD R5,R5,#4
AND R4,R0,R0

INNER_F	ADD R3,R3,#-1		;Decrement inner four loop
	BRn OUTER_F		;Check if we did 4 bits
	ADD R4,R4,#0		;Check R4
	BRzp #4			;If MSB is 0
	ADD R4,R4,R4		;Left shift
	ADD R6,R6,R6		;Left shift
	ADD R6,R6,#1
	BRnzp #2			;If MSB was 1
	ADD R4,R4,R4		;Left shift our binary
	ADD R6,R6,R6		;Left shift
	BRnzp INNER_F		;Run 4 times

OUTER_F ADD R5,R5,#-1		;Decrement outer four loop
	BRn DONE			;Done
	AND R3,R3,#0		;Reset inner counter
	ADD R3,R3,#4		;Set inner counter
	BRnzp CONV

;This is to check if the value needs 0~9 or A~Z
CONV	ADD R6,R6,#-5
	ADD R6,R6,#-5		;Subtract R6 by 10
	BRn Z_TO_N		;If neg, it will be 0~9

	LD R0,LETTERCHECK		;Load in hex A
	ADD R0,R0,R6		;Offset A to correct letter
	OUT
	AND R6,R6,#0		;Reset 4 bit
	BRnzp INNER_F		;Return for next 4 bit

Z_TO_N	ADD R6,R6,#5		;
	ADD R6,R6,#5		;Add R6 by 10 as we subtracted 10 to check
	LD R0,ZEROCHECK		;Load in hex 0
	ADD R0,R0,R6		;Offset 0 to correct number
	OUT
	AND R6,R6,#0		;Reset 4 bit binary
	BRnzp INNER_F		;Return for next 4 bit


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;


;your code goes here


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
	AND R0,R0,#0		
	; ST R7, SAVE_R7 ---TEMP DELTE
	JSR PRE_OP
	ADD R0,R3,R4
	JSR PUSH
	BRnzp EVALUATE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
	AND R0,R0,#0
	ST R7, SAVE_R7
	JSR PRE_OP
	NOT R3,R3
	ADD R3,R3,#1
	ADD R0,R4,R3
	JSR PUSH
	BRnzp EVALUATE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

MUL	
	ST R7, SAVE_R7
	JSR PRE_OP
	AND R0,R0,#0
	ADD R4,R4,#0	;Check R4
	BRnz DONE_MUL	;if its 0 or negative, done

MUL_LOOP
	ADD R0,R3,R0
	ADD R4,R4,#-1
	BRp MUL_LOOP

DONE_MUL
	JSR PUSH
	BRnzp EVALUATE

DIV	
	AND R0,R0,#0
	ST R7, SAVE_R7 
	JSR PRE_OP
	NOT R3,R3
	ADD R3,R3,#1
	AND R0,R0,#0
	DIVIDE_LOOP
	ADD R4,R4,R3
	BRz ZER
	BRn DONE_DIV
	ADD R0,R0,#1
	BRnzp DIVIDE_LOOP

ZER
	ADD R0,R0,#1

DONE_DIV
	ADD R0,R0,#0
	JSR PUSH
	BRnzp EVALUATE




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0


	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
	JSR PRE_OP	;
	AND R0,R0,#0

	AND R0, R4, R4 	; R0 = R4


	ADD R3,R3,#0	; If exp is 0, then always 1
	BRz EXPO_ZERO	; If exp is 0, then always 1


	ADD R3, R3, #-1 ;subtract 1 for counting purposes in the loop
	; SET R5 to ZERO for mutliplication sum thing
	AND R0, R0, R4
	AND R5, R4, R4

EXP_LOOP
	;COUNTER HERE IS R3


	;Initialize R6(the counter) with R4 
	AND R6, R4, R4
	ADD R6, R6, #-1

	AND R5, R0, R0

EXP_MUL_LOOP
	; COUNTER IS R6, intialized wiht R4 every EXP_LOOP ITERATION

	; R5 += R4
	ADD R0, R0, R5

	; decrement counter
	ADD R6, R6, #-1

	BRp EXP_MUL_LOOP

;;;;;;;;;;;;;;;;;
	; decrement EXP counter R3
	ADD R3, R3, #-1


BRp EXP_LOOP

BRnzp DONE_EXP


EXPO_ZERO
	AND R0, R0, #0
	ADD R0, R0, #1
	BRnzp DONE_EXP

DONE_EXP

JSR PUSH
BRnzp EVALUATE









;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP		;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3		;
	LD R4, POP_SaveR4		;
	RET


DONE 
	LD R5,SAVE_ANS		;
HALT			;

POP_SaveR3	.BLKW #1	;
SAVE_ANS 	.BLKW #1
POP_SaveR4	.BLKW #1
SAVE_R7		.BLKW #1
SAVE_R6		.BLKW #1
SAVE_R5		.BLKW #1
SAVE_R4		.BLKW #1
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;
EQUAL_SIGN	.FILL x3D	;
SPACE_SIGN	.FILL x20	;
ZERO_SIGN	.FILL x30	;
NINE_SIGN	.FILL x39	;
ADD_SIGN	.FILL x2B	;
SUB_SIGN	.FILL x2D	;
MUL_SIGN	.FILL x2A	;
DIV_SIGN	.FILL x2F	;
POW_SIGN	.FILL x5E	;
INVALID_SIGN	.STRINGZ "Invalid Expression"	;
ZEROCHECK		.FILL x30	; Contains Zero
LETTERCHECK		.FILL x41	; Contains A

;
.END
