.code64
.section .text
.org 0x0

.set VIDEO_MEMORY, 0xB8000
.set WHITE_ON_RED, 0x4F00

/// Print a null-terminated string
///
/// Input:
///  - `RDX`: Character offset to print at
///  - `DS:SI`: String start address
///  - `DF`: Specifies the direction to move the pointer (0 to increment)
/// Output:
///  NONE
.global PrintString64
PrintString64:
	PUSH %RAX
	PUSH %RDX

	MOVL $0, %EAX
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

	POP %RDX
	POP %RAX
	RET
