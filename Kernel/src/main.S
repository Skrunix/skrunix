.code64
.section .text
.org 0x0

Start:
	MOVL $320, %EDX
	LEAL strKernel, %ESI
	CALL PrintString64

Halt:
	CLI
	HLT
	JMP Halt


.section .data

strKernel:
	.asciz "In Kernel           "
