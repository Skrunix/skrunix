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
	XORL %EAX, %EAX
	LEAL PAGING_PML4T, %EDI
	MOVL %EDI, %CR3
	MOVL $0x1000, %ECX # Clear all 4 pages with longs (4 pages * 0x1000 bytes/page * 1/4 words/byte)
	REP STOSL
	MOVL %CR3, %EDI

	LEAL PAGING_PDPT, %EAX
	ADDL $0x703, %EAX   # Virt-Phys offset + (present + writable)
	MOVL %EAX, (%EDI) # First low entry
	ADDL $0x800, %EDI
	MOVL %EAX, (%EDI) # First high entry
	ADDL $0x800, %EDI

	LEAL PAGING_PDT, %EAX
	ADDL $0x703, %EAX   # Virt-Phys offset + (present + writable)
	MOVL %EAX, (%EDI)
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
	LEAL PAGING_PML4T, %EAX
	ADDL $0x700, %EAX
	MOVL %EAX, %CR3

	# Enable PAE-paging
	MOVL %CR4, %EAX
	ORL $1<<5, %EAX
	MOVL %EAX, %CR4

	POPA
	RET
