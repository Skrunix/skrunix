OUTPUT_FORMAT(binary)

SECTIONS {
	. = 0x10000;
	.text : {
		*boot.o(.text)
		*(.text)
	}
	.bss : {
		*(.bss)
	}
	. = . + SIZEOF(.bss);
	.data : {
		*(.data)
		*(.rodata)
	}
	KernelEnd = .;
}
