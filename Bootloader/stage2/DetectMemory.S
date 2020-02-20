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
	CLC

	LEAW strDetectMemory, %SI
	CALL PrintString

	MOVL $0x0900, %EAX
	MOVW %AX, %ES
	MOVW $24, %DI

	XORL %EBX, %EBX
	XORL %EBP, %EBP # Entry count

	// See if 0xE820 is supported
	MOVL $0x534D4150, %EDX # 'SMAP'
	MOVL $0xE820, %EAX
	MOVW $24, %CX
	MOVW $1, %ES:20(%DI)
	INT $0x15
	MOVB $49, strNotSupported
	JC .NotSupported // Carry set on first call means not supported
	MOVL $0x534D4150, %EDX # 'SMAP'
	CMPL %EDX, %EAX
	MOVB $50, strNotSupported
	JNE .NotSupported //
	TEST %EBX, %EBX
	MOVB $51, strNotSupported
	JZ .NotSupported // We looped after the first entry

.NextBlock:
	PUSHA
	LEAW strFoundBlock, %SI
	SHRW $12, %BX
	ANDB $0x0F, %BL
	MOVB %BL, %DS:2(%SI)
	ADDB $48, %DS:2(%SI)
	POPA
	PUSHA
	LEAW strFoundBlock, %SI
	SHRW $8, %BX
	ANDB $0x0F, %BL
	MOVB %BL, 3(%SI)
	ADDB $48, %DS:3(%SI)
	POPA
	PUSHA
	LEAW strFoundBlock, %SI
	SHRW $4, %BX
	ANDB $0x0F, %BL
	MOVB %BL, 4(%SI)
	ADDB $48, %DS:4(%SI)
	POPA
	PUSHA
	LEAW strFoundBlock, %SI
	ANDB $0x0F, %BL
	MOVB %BL, 5(%SI)
	ADDB $48, %DS:5(%SI)
	POPA

	LEAW strFoundBlock, %SI
	CALL PrintString
	ADDW $1, %BP
	ADDW $24, %DI

	TEST %EBX, %EBX
	JZ .DetectMemoryEnd

	MOVL $0x534D4150, %EDX # 'SMAP'
	MOVL $0xE820, %EAX
	MOVW $24, %CX
	MOVW $1, %ES:20(%DI)
	INT $0x15
	JC .DetectMemoryEnd

	JMP .NextBlock

.DetectMemoryEnd:
	// Write count
	MOVW $0, %DI
	MOVW %BP, %ES:(%DI)

	LEAW strDetectMemoryDone, %SI
	CALL PrintString

	POPA
	RET

.NotSupported:
	LEAW strNotSupported, %SI
	CALL PrintString
	JMP Halt


.section .data

strDetectMemory:
	.asciz "Detecting memory...\r\n"
strNotSupported:
	.asciz "_: BIOS int 15h 0xE820 not supported"
strFoundBlock:
	.asciz "0x     block found..\r\n"
strDetectMemoryDone:
	.asciz "Found memory!\r\n"
