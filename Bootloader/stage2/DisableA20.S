.code16
.section .text
.org 0x0

/// Disable A20
///
/// Input:
///  NONE
/// Output:
///  NONE
.global DisableA20
DisableA20:
	PUSHA

	CALL DisableA20BIOS
	CALL CheckA20
	JC .DisableA20Done

.DisableA20Done:
	POPA
	RET

DisableA20BIOS:
	MOVW $0x2400, %AX
	INT $0x15
	RET
