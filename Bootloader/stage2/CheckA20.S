.code16
.section .text
.org 0x0

/// Check if the A20 line is enabled
///
/// Input:
///  NONE
/// Output:
///  - `Carry bit`: set if disabled
.global CheckA20
CheckA20:
	PUSHA
	PUSH %DS
	PUSH %ES
	CLI

	# Low segment (0x0000)
	XOR %AX, %AX
	MOVW %AX, %ES

	# High segment (0xFFFF)
	NOT %AX
	MOVW %AX, %DS

	# ES:DI -> 0x0000:0x0500
	MOVW $0x0500, %DI
	# DS:SI -> 0xFFFF:0x0510
	MOVW $0x0510, %SI

	# Store the previous values
	MOVB %ES:(%DI), %AL
	MOVB %DS:(%SI), %AH

	# Write different values
	MOVB $0xFF, %ES:(%DI)
	MOVB $0x00, %DS:(%SI)

	# Compare the low value with the expected high value if A20 is disabled
	# If `%ES:(%DI)` contains `0x00` the carry bit is set
	# If `%ES:(%DI)` contains `0xFF` the carry bit is cleared
	CMPB $0xFF, %ES:(%DI)

	# Restore the original values
	MOVB %AL, %ES:(%DI)
	MOVB %AH, %DS:(%SI)

	STI
	POP %ES
	POP %DS
	POPA
	RET
