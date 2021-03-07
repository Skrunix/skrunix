OUTPUT_FORMAT(binary)

_KernelOffset = 0xFFFF800000000000;

SECTIONS {
	. = _KernelOffset + 0x100000;

	_KernelStart = .;

	.text BLOCK(4K) : {
		_KernelTextStart = .;
		*boot.o(.text)
		*(.text.startup)
		*(.text)
	}

	.rodata BLOCK(4K) : {
		_KernelRODataStart = .;
		*(.rodata*)
	}

	.data BLOCK(4K) : {
		_KernelDataStart = .;
		*(.data*)
	}

	.bss BLOCK(4K) : {
		_KernelBSSStart = .;
		*(.bss*)
	}

	/DISCARD/ : {
		*(.rela.text.startup)
		*(.rela.text)
		*(.rela.data)
		*(.comment)
		*(.symtab)
		*(.strtab)
		*(.shstrtab)
		*(*)
	}

	_KernelEnd = ALIGN(4K);

	_KernelTextSize = SIZEOF(.text);
	_KernelRODataSize = SIZEOF(.rodata);
	_KernelDataSize = SIZEOF(.data);
	_KernelBSSSize = SIZEOF(.bss);
}
