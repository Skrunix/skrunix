.code16
.section .text
.org 0x0

Start:
	MOVW $0x1000, %AX
	MOVW %AX, %DS
	LEAW strKernel, %SI
	CALL PrintString

Halt:
	CLI
	HLT
	JMP Halt

.section .data

strKernel:
	.asciz "\r\nStarting Kernel\r\n"
