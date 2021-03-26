.code64
.section .text
.org 0x0

Start:
	# Setup stack
	MOVQ $0xFFFF80000000FFF8, %RAX
	MOVQ %RAX, %RSP
	MOVQ %RAX, %RBP

	JMP main
