.code16
.section .text
.org 0x0

/// DetectMemory
///
/// Input:
///  NONE
/// Output:
///  NONE
.global DetectMemory
DetectMemory:
	PUSHA

	LEAW strDetectMemory, %SI
	CALL PrintString

	MOVL $0x8000, %EAX
	MOVW %AX, %ES
	MOVW $24, %DI

	XORW %BX, %BX
	XORW %BP, %BP # Entry count

.NextBlock:
	MOVL $0x534D4150, %EDX # 'SMAP'
	MOVW $0xE820, %AX
	MOVW $24, %CX
	MOVW $1, %ES:20(%DI)
	INT $0x15
	JC .DetectMemoryEnd

	LEAW strFoundBlock, %SI
	CALL PrintString
	ADDW $1, %BP
	ADDW $24, %DI

	TESTW %BX, %BX
	JZ .DetectMemoryEnd
	JMP .NextBlock

.DetectMemoryEnd:
	MOVW $0, %DI
	MOVW %BP, %ES:(%DI)

	LEAW strDetectMemoryDone, %SI
	CALL PrintString

	POPA
	RET


.section .data

strDetectMemory:
	.asciz "Detecting memory...\r\n"
strFoundBlock:
	.asciz "block found..\r\n"
strDetectMemoryDone:
	.asciz "Found memory!\r\n"
