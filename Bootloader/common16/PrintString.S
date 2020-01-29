.code16
.section .text
.org 0x0

/// Print a null-terminated string
///
/// Input:
///  - `DS:SI`: String start address
///  - `DF`: Specifies the direction to move the pointer (0 to increment)
/// Output:
///  NONE
.global PrintString
PrintString:
	PUSHA

	MOVB $0x0E, %AH
	MOVW $0, %BX
.PrintStringStart:
	LODSB
	TESTB %AL, %AL
	JZ .PrintStringEnd
	INT $0x10
	JMP .PrintStringStart
.PrintStringEnd:

	POPA
	RET
