OUTPUT_FORMAT(binary)

SECTIONS {
	.text : {
		*main.o(.text)
		*(.text)
	}

	.data : {
		*(.data)
	}

	. += 0x700;
	. = ALIGN(4K) - 0x700;
	KERNEL_END = .;

	PAGING_PML4T = KERNEL_END + 0K;
	PAGING_PDPT  = KERNEL_END + 4K;
	PAGING_PDT   = KERNEL_END + 8K;
	PAGING_PT    = KERNEL_END + 12K; /* Unused */
	DETECTED_MEMORY_START = KERNEL_END + 16K + 0x700 - 0x500; /* stage1 segments */

	/DISCARD/ : {
		*(*)
	}
}
