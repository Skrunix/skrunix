.code16
.section .text
.org 0x0

/// Check and print the status of A20
///
/// Input:
///  NONE
/// Output:
///  NONE
.global A20Status
A20Status:
	PUSHA

	CALL CheckA20
	JC .a20Disabled
	JMP .a20Enabled
.a20Disabled:
	CALL PrintA20Disabled
	JMP .endA20Status
.a20Enabled:
	CALL PrintA20Enabled
	JMP .endA20Status

.endA20Status:
	POPA
	RET


PrintA20Enabled:
	PUSHA
	LEAW strA20Enabled, %SI
	CALL PrintString
	POPA
	RET

PrintA20Disabled:
	PUSHA
	LEAW strA20Disabled, %SI
	CALL PrintString
	POPA
	RET


.section .data

strA20Enabled:
	.asciz "A20 Enabled\r\n"
strA20Disabled:
	.asciz "A20 Disabled\r\n"
