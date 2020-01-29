OUTPUT_FORMAT(binary)

SECTIONS {
	.text : {
		*main.o(.text)
		*(.text)
	}
	.data : {
		*(.data)
	}
}
