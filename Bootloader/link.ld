OUTPUT_FORMAT(binary)

SECTIONS {
	.text : {
		*main.o(.text)
		*(.text)
	}

	.data : {
		*(.data)
	}

	DETECTED_MEMORY_START = ALIGN(8);
	DETECTED_MEMORY_PTR = 0xFAF8; /* 0x0050:0xFAF8 = 0xFFF8 */

	/DISCARD/ : {
		*(*)
	}
}
