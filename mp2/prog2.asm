;partners: awinick2, hyunwoo6, crjung2

;First thing we do is get the user input using GETC.
;Then we check whether or not the the user inputted a valid number, or character
;if it isn't, then we print invalid message and end the code.
;If it is, it checks what it is. If its a number, it gets pushed to the stack
;if it is an operation, it branches to which operation it is
;and pops the two values in the stack and operates
;it is then pushed into the stack from R0
;Every iteration checks if it is an equal sign and if it also has one value in the stack
;it is then coverted to hex and printed out

	;R0			Used for PUSH and POP and print OUT value. Also Temp Var for computation
	;R1			Temp Var to Check
	;R2			Unused
	;R3			Value of START stack. Also holds the value after POP
	;R4			Value of TOP stack. Also holds the value after POP
	;R5			Used to check underflow and overflow.
	;			Also used for storing what we need to printing
	;R6			used for printing and in exponential loop as a counter
	;R7			only used for PC value


.ORIG x3000
	
;your code goes here
				;Reset all REG
	AND R0,R0,#0		;used to hold what gets put in stack after the operation
	AND R1,R1,#0		;Temp Var to Check
	AND R2,R2,#0		;unused
	AND R3,R3,#0		;Value of START stack
	AND R4,R4,#0		;Value of TOP stack
	AND R5,R5,#0		;used to check underflow and overflow. Also used for storing what we need to printing
	AND R6,R6,#0		;used for printing and in exponential loop as a counter
	AND R7,R7,#0		;only used for PC values

EVALUATE 
	GETC			;gets the character from user input
	OUT			;prints it out

CHECK_EQ			;this checks if the input character was an equal sign
	AND R1,R1,#0		;clear R1
	LD R1,EQUAL_SIGN	;Loads into R1 the hex value of equal sign
	NOT R1,R1		;make R1 negative
	ADD R1,R1,#1
	ADD R1,R1,R0		;subtract to see if they are equal
	BRz CHECK_STACK		;If it is 0, it branches to check stack

CHECK_SP			;this checks if the in character was an space
	AND R1,R1,#0		;clear R1
	LD R1,SPACE_SIGN	;Loads into R1 the hex value of equal sign
	NOT R1,R1		;make R1 negative
	ADD R1,R1,#1		;
	ADD R1,R1,R0		;subtract to see if they are equal
	BRz EVALUATE		;branches to evaluate if its 0

CHECK_NUM			;checks if the input was a number
	AND R1,R1,#0		;clear R1
	LD R1,NINE_SIGN		;load the hex value of 9
	NOT R1,R1			;invert R1
	ADD R1,R1,#1
	ADD R1,R1,R0		;subtract r0 and r1
	BRp CHECK_OP		;if the character inputted minus the hex value of 9 is positive, meaning 					;that its>9, branch to check operation

	AND R1,R1,#0		;clear R1
	LD R1,ZERO_SIGN		;load into R1 the hex value of 0
	NOT R1,R1		;invert R1
	ADD R1,R1,#1
	ADD R1,R1,R0		;subtract r0 and r1
	BRn CHECK_OP		;if the character inputted is less than 0, then branch to check operation

;It is 0~9
	AND R1,R1,#0		;clear R1
	LD R1,ZERO_SIGN		;load into R1 the hex value of 0
	NOT R1,R1		;invert R1
	ADD R1,R1,#1
	ADD R0,R1,R0		;subtract r0 from r1
	JSR PUSH		;push that into the stack
	BRnzp EVALUATE		;branch to evaluate
	
CHECK_OP			;check what the operation we need to check is
	AND R1,R1,#0		;clear r1
	LD R1,ADD_SIGN		;load the hex value of addition sign into R1
	NOT R1,R1		;invert r1
	ADD R1,R1,#1
	ADD R1,R1,R0		;subtract r0 to r1
	BRz PLUS		;if they are the same, branch to addition function

	AND R1,R1,#0		;clear r1
	LD R1,SUB_SIGN		;load the hex value of subtraction sign into R1
	NOT R1,R1		;invert R1
	ADD R1,R1,#1
	ADD R1,R1,R0		;add r0 to r1
	BRz MIN			;if they are the same, branch to subtraction function

	AND R1,R1,#0		;clear r1
	LD R1,MUL_SIGN		;load the hex value of the  multiplication sign into r1
	NOT R1,R1		;invert r1
	ADD R1,R1,#1		
	ADD R1,R1,R0		;subtract r1 from r0 to see if they are equal
	BRz MUL			;branch to multiplication if they are equal

	AND R1,R1,#0		;clear r1
	LD R1,DIV_SIGN		;load into r1 the hex value of the division sign
	NOT R1,R1		;invert r1
	ADD R1,R1,#1
	ADD R1,R1,R0		;subtract r0 from r1
	BRz DIV			;if 0, branch to division function

	AND R1,R1,#0		;clear r1
	LD R1,POW_SIGN		;load the hex value of the power sign into r1
	NOT R1,R1		;invert r1
	ADD R1,R1,#1
	ADD R1,R1,R0		;subtract r0 from r1
	BRz EXP			;if 0, branch to exponential function
	
	BRnzp INVALID		;Print Invalid

CHECK_STACK			;check the stack
	LD R3,STACK_START	;load r3 as stack start pointer
	LD R4,STACK_TOP		;load r4 as stack top
	NOT R4,R4		;invert r4, but don't add the r1 because we use the -1 value to check how 					;many items in the stack
	ADD R3,R3,R4		;subtract r4 from r3
	BRnp INVALID		;Invalid if number isn't 0

;There is one in stack
	JSR POP			;Pop the single value
	BRnzp PRINT_HEX		;Convert the binary to hex

PRE_OP			
	ST R7, SAVE_R7		;save r7
	LD R3,STACK_START	;load r3 as stack sart
	LD R4,STACK_TOP		;load r4 as stack top
	NOT R4,R4		;invert r4 but keep is as r4-1
	ADD R3,R3,R4		;subtract r4 from r3 
	ADD R3,R3,#-1		;subtract one from r3
	BRn INVALID		;Invalid if the solution is negative meaning there aren’t 2 values in the stack

;There is two in stack
	JSR POP
	AND R3,R0,R0		;put the popper value into r3	
	JSR POP
	AND R4,R0,R0		;putted popped value into r4
	LD R7,SAVE_R7
	RET

INVALID
	LEA R0,INVALID_SIGN	;load ito r0 the message from invalid sign
	PUTS			;print the message
	BRnzp DONE		;end the code

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX

AND R5,R0,R0			;Final Answer
ST R5, SAVE_ANS			;Save Answer

AND R1,R1,#0			;clear all registers except for r0, to be able to be used for the print function
AND R2,R2,#0
AND R4,R3,#0
AND R4,R4,#0
AND R5,R5,#0
AND R6,R6,#0

ADD R3,R3,#4	;make r3 a counter 
ADD R5,R5,#4	;make r5 a counter
AND R4,R0,R0	;put r0 into r4

INNER_F	ADD R3,R3,#-1		;Decrement inner four loop
	BRn OUTER_F		;Check if we did 4 bits
	ADD R4,R4,#0		;Check R4
	BRzp #4			;If MSB is 0
	ADD R4,R4,R4		;Left shift
	ADD R6,R6,R6		;Left shift
	ADD R6,R6,#1		;add one to  r6
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
	AND R0,R0,#0	;clear r0	
	JSR PRE_OP
	ADD R0,R3,R4	;add r3 and r4
	JSR PUSH
	BRnzp EVALUATE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
	AND R0,R0,#0		;clear r0
	ST R7, SAVE_R7
	JSR PRE_OP
	NOT R3,R3		;invert r3
	ADD R3,R3,#1
	ADD R0,R4,R3		;subtract r4 from r3 
	JSR PUSH
	BRnzp EVALUATE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

MUL	
	ST R7, SAVE_R7	;save r7
	JSR PRE_OP
	AND R0,R0,#0	;clear r0
	ADD R4,R4,#0	;check if R4
	BRn NEG_MUL

MUL_LOOP
	ADD R0,R3,R0	;add r3 to r0
	ADD R4,R4,#-1	;decrement r4
	BRp MUL_LOOP
	BRnz DONE_MUL

NEG_MUL
	NOT R4,R4
	ADD R4,R4,#1		;Negate R4 if it is negative

NEG_MUL_LOOP
	ADD R0,R3,R0		;add r3 to r0
	ADD R4,R4,#-1		;decrement r4
	BRp NEG_MUL_LOOP
	NOT R0,R0
	ADD R0,R0,#1		;Negate R4 again to get neg value
	
DONE_MUL
	JSR PUSH
	BRnzp EVALUATE

DIV	
	AND R0,R0,#0		;clear r0
	ST R7, SAVE_R7 
	JSR PRE_OP	
ADD R3,R3,#0			;see if r3 is 0
BRz INVALID
	NOT R3,R3		;invert r3
	ADD R3,R3,#1		;
	AND R0,R0,#0		;clear r0
		DIVIDE_LOOP	
	ADD R4,R4,R3		;subtract r3 from r4
	BRz ZER
	BRn DONE_DIV		;if the number  is negative, branch to done_div
	ADD R0,R0,#1		;increment r0
	BRnzp DIVIDE_LOOP

ZER
	ADD R0,R0,#1		;if there is no remainder, add 1 to r0, the it leads into done_div

DONE_DIV
	ADD R0,R0,#0		;add 0 to r0
	JSR PUSH		;push solution into stack
	BRnzp EVALUATE




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0


	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
	JSR PRE_OP	;
	AND R0,R0,#0	;clear r0

	AND R0, R4, R4 	; R0 = R4


	ADD R3,R3,#0	; If exp is 0, then always 1
	BRz EXPO_ZERO	; If exp is 0, then always 1


	ADD R3, R3, #-1 ;subtract 1 for counting purposes in the loop
	; SET R5 to ZERO for multiplication sum thing
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
	ADD R0, R0, R5	;add r5 to r0

	; decrement counter
	ADD R6, R6, #-1

	BRp EXP_MUL_LOOP

;;;;;;;;;;;;;;;;;
	; decrement EXP counter R3
	ADD R3, R3, #-1


BRp EXP_LOOP

BRnzp DONE_EXP


EXPO_ZERO
	AND R0, R0, #0		;clear r0
	ADD R0, R0, #1		;add 1 to r0
	BRnzp DONE_EXP		

DONE_EXP

JSR PUSH		;push number onto stack
BRnzp EVALUATE


;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3		;save R3
	ST R4, PUSH_SaveR4		;save R4
	AND R5, R5, #0		;clear r5
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;decrement r3
	NOT R3, R3		;invert r3
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;subtract r3 from r4
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;branch to done_push
OVERFLOW
	ADD R5, R5, #1		;add 1 to r5 if overflow

DONE_PUSH
	LD R3, PUSH_SaveR3		;restore r3
	LD R4, PUSH_SaveR4		;restore r4
	RET


PUSH_SaveR3	.BLKW #1	;save r3
PUSH_SaveR4	.BLKW #1	;save r4


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3	;sore r4
	ST R4, POP_SaveR4	;save R3	;store r3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START		;put r3 on stack start
	LD R4, STACK_TOP		;put r4 on stack top
	NOT R3, R3		;make r3 the negative value
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;subtract r3 from r4
	BRz UNDERFLOW		;check underflow
	ADD R4, R4, #1		;add one to r4
	LDR R0, R4, #0		;load from memory of r4 into r0
	ST R4, STACK_TOP		;store r4 on stacktop
	BRnzp DONE_POP		;branch to done_pop
UNDERFLOW
	ADD R5, R5, #1		;check underflow, if it is, add 1 to r5
DONE_POP
	LD R3, POP_SaveR3		;restore r3
	LD R4, POP_SaveR4		;restore r4
	RET


DONE 
	LD R5,SAVE_ANS		;puts the solution into r5 before ending the code
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
EQUAL_SIGN	.FILL x3D	;hex of equal sign
SPACE_SIGN	.FILL x20	;hex of space
ZERO_SIGN	.FILL x30	;hex of 0
NINE_SIGN	.FILL x39	;hex of 9
ADD_SIGN	.FILL x2B		;hex of add sign
SUB_SIGN	.FILL x2D		;hex of subtract sign
MUL_SIGN	.FILL x2A		;hex of multiplication sign
DIV_SIGN	.FILL x2F		;hex of division sign
POW_SIGN	.FILL x5E	;hex of power sign
INVALID_SIGN	.STRINGZ "Invalid Expression"	;used for invalid character
ZEROCHECK		.FILL x30	; Contains Zero	
LETTERCHECK		.FILL x41	; Contains A
;
.END

