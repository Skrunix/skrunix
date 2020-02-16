.code64
.section .text
.org 0x0

.global loadGDT
loadGDT:
	LGDT (%RDI)
	PUSHQ $0x08
	PUSHQ $loadGDTEnd
	LRETQ

loadGDTEnd:
	MOV $0x10, %RAX
	MOVW %AX, %DS
	MOVW %AX, %ES
	MOVW %AX, %FS
	MOVW %AX, %GS
	MOVW %AX, %SS
	RET
