OUTPUT_FORMAT(binary)

SECTIONS {
	. = 0x10000;
	_KernelTextSizeStart = .;
	.text : {
		*boot.o(.text)
		*(.text*)
	}
	_KernelTextSizeEnd = .;
	_KernelBSSSizeStart = .;
	.bss : {
		*(.bss*)
	}
	_KernelBSSSizeEnd = .;
	_KernelDataSizeStart = .;
	.data : {
		*(.data*)
		*(.rodata*)
	}
	_KernelDataSizeEnd = .;
	. = ALIGN(4096);
	KernelEnd = .;
	KernelTextSize = _KernelTextSizeEnd - _KernelTextSizeStart;
	KernelDataSize = _KernelDataSizeEnd - _KernelDataSizeStart;
	KernelBSSSize = _KernelBSSSizeEnd - _KernelBSSSizeStart;
}
