.code32
.section .text
.org 0x0

/// Check if CPUID is supported
///
/// Input:
///  NONE
/// Output:
///  - `Carry bit`: clear if LBA extension is present
.global DetectCPUID
DetectCPUID:
	PUSHA

	PUSHFL
	POP %EAX
	MOVL %EAX, %ECX

	XORL $1<<21, %EAX
	PUSH %EAX
	POPFL

	PUSHFL
	POP %EAX
	PUSH %ECX
	POPFL

	XORL %EAX, %ECX
	JZ .NoCPUID
	CLC
	JMP .DetectCPUIDEnd

.NoCPUID:
	STC

.DetectCPUIDEnd:
	POPA
	RET
