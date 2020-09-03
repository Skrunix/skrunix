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
	MOVL $0x9900, %EDI
	MOVL %EDI, %CR3
	XORL %EAX, %EAX
	MOVL $4096, %ECX
	REP STOSL
	MOVL %CR3, %EDI

	# PML4T - 0x9900 (0xA000 real)
	# PDPT  - 0xA900 (0xB000 real)
	# PDT   - 0xB900 (0xC000 real)
	# PT    - 0xC900 (0xD000 real) - Does not exist
	MOVL $0xB003, (%EDI) # First low entry (present + writable)
	ADDL $0x800, %EDI
	MOVL $0xB003, (%EDI) # First high entry (present + writable)
	ADDL $0x800, %EDI
	MOVL $0xC003, (%EDI)
	ADDL $0x1000, %EDI

	# Map the first gigabyte (Identity for low, offset mapping for high)
	MOVL $0b10000011, %EBX // present + writable + huge
	MOVL $512, %ECX
.SetEntry1:
	MOVL %EBX, (%EDI)
	ADDL $0x200000, %EBX // 2MiB
	ADDL $8, %EDI
	LOOP .SetEntry1

	# Set CR3 to the physical address
	MOVL $0xA000, %EDI
	MOVL %EDI, %CR3

	# Enable PAE-paging
	MOVL %CR4, %EAX
	ORL $1<<5, %EAX
	MOVL %EAX, %CR4

	POPA
	RET
