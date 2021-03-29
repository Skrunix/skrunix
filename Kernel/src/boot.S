.code64
.section .text
.org 0x0

Start:
	# Setup stack
	MOVQ $0xFFFF800000010000, %RAX
	MOVQ %RAX, %RSP
	MOVQ %RAX, %RBP

	JMP main
