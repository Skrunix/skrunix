.code64
.section .text
.org 0x0

Start:
	# Setup stack
	MOVL $0x200000, %EAX
	MOVL %EAX, %ESP
	MOVL %EAX, %EBP

	CALL kmain

	MOVL $1920, %EDI
	LEAL strKernel, %ESI
	CALL PrintString64

Halt:
	CLI
	HLT
	JMP Halt


.section .data

strKernel:
	.asciz "Kernel exit"
