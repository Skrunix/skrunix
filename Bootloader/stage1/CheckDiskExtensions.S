.code16
.section .text
.org 0x0

/// Check that disk extensions are available
///
/// Input:
///  - `DL`: Drive index
/// Output:
///  - `Carry bit`: clear if LBA extension is present
.global CheckDiskExtensions
CheckDiskExtensions:
	PUSHA

	MOVB $0x41, %AH
	MOVW $0x55AA, %BX
	INT $0x13

	POPA
	RET
