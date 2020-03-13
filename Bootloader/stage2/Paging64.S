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
	# PDPT1 - 0x3400 (0xB000 real)
	# PDPT2 - 0x4400 (0xC000 real)
	# PDT1  - 0x5400 (0xD000 real)
	# PDT2  - 0x6400 (0xE000 real)
	# PT    - 0x7400 (0xF000 real) - Does not exist
	MOVL $0xB003, (%EDI) # First low entry (present + writable)
	ADDL $0x800, %EDI
	MOVL $0xC003, (%EDI) # First high entry (present + writable)
	ADDL $0x800, %EDI
	MOVL $0xD003, (%EDI)
	ADDL $0x1000, %EDI
	MOVL $0xE003, (%EDI)
	ADDL $0x1000, %EDI

	# Identity map the first low gigabyte
	MOVL $0b10000011, %EBX // present + writable + huge
	MOVL $512, %ECX
.SetEntry1:
	MOVL %EBX, (%EDI)
	ADDL $0x200000, %EBX // 2MiB
	ADDL $8, %EDI
	LOOP .SetEntry1
	
	# Map the first high gigabyte
	MOVL $0b10000011, %EBX // present + writable + huge
	MOVL $512, %ECX
.SetEntry2:
	MOVL %EBX, (%EDI)
	ADDL $0x200000, %EBX // 2MiB
	ADDL $8, %EDI
	LOOP .SetEntry2

	# Set CR3 to the physical address
	MOVL $0xA000, %EDI
	MOVL %EDI, %CR3

	# Enable PAE-paging
	MOVL %CR4, %EAX
	ORL $1<<5, %EAX
	MOVL %EAX, %CR4

	POPA
	RET
