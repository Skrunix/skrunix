.code32
.section .text
.org 0x0

/// Check if Long mode is supported
///
/// Input:
///  NONE
/// Output:
///  - `Carry bit`: clear if LBA extension is present
.global DetectLongMode
DetectLongMode:
	PUSHA

	MOVL $0x80000000, %EAX
	CPUID
	CMP $0x80000001, %EAX
	JB .NoLongMode

	MOV $0x80000001, %EAX
	CPUID
	TEST $1<<29, %EDX
	JZ .NoLongMode

	CLC
	JMP .DetectLongModeEnd

.NoLongMode:
	STC

.DetectLongModeEnd:
	POPA
	RET
