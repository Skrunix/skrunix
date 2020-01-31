.code16
.section .text
.org 0x0

/// Enable A20
///
/// Input:
///  NONE
/// Output:
///  NONE
.global EnableA20
EnableA20:
	PUSHA

	CALL EnableA20BIOS
	CALL CheckA20
	JNC .EnableA20Done

.EnableA20Done:
	POPA
	RET

EnableA20BIOS:
	MOVW $0x2401, %AX
	INT $0x15
	RET
