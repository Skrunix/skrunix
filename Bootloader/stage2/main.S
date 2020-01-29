.code16
.section .text
.org 0x0

Start:
	MOVW $0x07C0, %AX
	MOVW %AX, %DS
	LEAW String, %SI
	CALL PrintString

Halt:
	CLI
	HLT
	JMP Halt


.section .data

String:
	.asciz "\r\nStarting Stage 2\r\n"
