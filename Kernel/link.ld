OUTPUT_FORMAT(binary)

SECTIONS {
	. = 0x10000;
	.text : {
		*boot.o(.text)
		*(.text)
	}
	.data : {
		*(.data)
	}
}
