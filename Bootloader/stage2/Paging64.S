.code32
.section .text
.org 0x0

/// Enable A20
///
/// Input:
///  NONE
/// Output:
///  NONE
.global Paging64
Paging64:
	PUSHA
	# Clear the page tables
	MOVL $0x2400, %EDI
	MOVL %EDI, %CR3
	XORL %EAX, %EAX
	MOVL $4096, %ECX
	REP STOSL
	MOVL %CR3, %EDI

	# PML4T - 0x2400 (0xA000 real)
	# PDPT  - 0x3400 (0xB000 real)
	# PDT   - 0x4400 (0xC000 real)
	# PT    - 0x5400 (0xD000 real)
	MOVL $0xB003, (%EDI)
	ADDL $0x1000, %EDI
	MOVL $0xC003, (%EDI)
	ADDL $0x1000, %EDI
	MOVL $0xD003, (%EDI)
	ADDL $0x1000, %EDI

	# Identity map the first two megabytes
	MOVL $0x3, %EBX
	MOVL $512, %ECX
.SetEntry:
	MOVL %EBX, (%EDI)
	ADDL $0x1000, %EBX
	ADDL $8, %EDI
	LOOP .SetEntry

	# Set CR3 to the physical address
	MOVL $0xA000, %EDI
	MOVL %EDI, %CR3

	# Enable PAE-paging
	MOVL %CR4, %EAX
	ORL $1<<5, %EAX
	MOVL %EAX, %CR4

	POPA
	RET
