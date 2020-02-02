.code32
.section .text
.org 0x0

.set VIDEO_MEMORY, 0xB8000 - 0x10000
.set WHITE_ON_BLACK, 0x0F

/// Print a null-terminated string
///
/// Input:
///  - `DS:SI`: String start address
///  - `DF`: Specifies the direction to move the pointer (0 to increment)
/// Output:
///  NONE
.global PrintString32
PrintString32:
	PUSHA

	MOVL $VIDEO_MEMORY, %EDX
.PrintStringStart32:
	LODSB
	TESTB %AL, %AL
	JZ .PrintStringEnd32
	MOVB $WHITE_ON_BLACK, %AH
	MOVW %AX, (%EDX)
	ADD $2, %EDX
	JMP .PrintStringStart32
.PrintStringEnd32:

	POPA
	RET
