.code64
.section .text
.org 0x0

.set VIDEO_MEMORY, 0xB8000
.set WHITE_ON_RED, 0x4F00

/// Print a null-terminated string
///
/// Input:
///  - `EDI`: Character offset to print at
///  - `ESI`: String start address
///  - `DF`: Specifies the direction to move the pointer (0 to increment)
/// Output:
///  NONE
.global PrintString64
PrintString64:
	PUSH %RAX
	PUSH %RDX
	PUSH %RSI

	MOVL $0, %EAX
	MOVL %EDI, %EDX
	ADDQ %RDX, %RDX
	ADDQ $VIDEO_MEMORY, %RDX
.PrintStringStart64:
	LODSB
	TESTB %AL, %AL
	JZ .PrintStringEnd64
	ORW $WHITE_ON_RED, %AX
	MOVW %AX, (%RDX)
	ADDL $2, %EDX
	JMP .PrintStringStart64
.PrintStringEnd64:

	POP %RSI
	POP %RDX
	POP %RAX
	RET
