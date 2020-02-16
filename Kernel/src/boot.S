.code64
.section .text
.org 0x0

Start:
	# Setup stack
	MOVL $0x200000, %EAX
	MOVL %EAX, %ESP
	MOVL %EAX, %EBP

	JMP main
