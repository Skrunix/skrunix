.code32
.section .text
.org 0x0

Start:
	LEAL strKernel, %ESI
	CALL PrintString32

Halt:
	CLI
	HLT
	JMP Halt

.section .data

strKernel:
	.asciz "In Kernel"
