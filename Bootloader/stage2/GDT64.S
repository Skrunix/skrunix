.code16
.section .text
.org 0x0


.section .data

.gdt64Start:
	.word 0xFFFF # Limit 0:15
	.word 0x0000 # Base 0:15
	.byte 0x00 # Base 16:23
	.byte 0b00000000 # Access Byte
	.byte 0b00000001 # Flags | Limit 16:19
	.byte 0x00 # Base 24:31

.gdt64BootloaderCode:
	.word 0xFFFF # Limit 0:15
	.word 0x0000 # Base 0:15
	.byte 0x00 # Base 16:23
	.byte 0b10011010 # Access Byte
	.byte 0b10101111 # Flags | Limit 16:19
	.byte 0x00 # Base 24:31

.gdt64BootloaderData:
	.word 0xFFFF # Limit 0:15
	.word 0x0000 # Base 0:15
	.byte 0x00 # Base 16:23
	.byte 0b10010010 # Access Byte
	.byte 0b00001111 # Flags | Limit 16:19
	.byte 0x00 # Base 24:31

.gdt64KernelTempCode:
	.word 0xFFFF # Limit 0:15
	.word 0x0000 # Base 0:15
	.byte 0x00 # Base 16:23
	.byte 0b10011010 # Access Byte
	.byte 0b10101111 # Flags | Limit 16:19
	.byte 0x00 # Base 24:31

.gdt64KernelTempData:
	.word 0xFFFF # Limit 0:15
	.word 0x0000 # Base 0:15
	.byte 0x00 # Base 16:23
	.byte 0b10010010 # Access Byte
	.byte 0b00000000 # Flags | Limit 16:19
	.byte 0x00 # Base 24:31

.gdt64End:

.global GDT64Descriptor
GDT64Descriptor:
	.word .gdt64End - .gdt64Start - 1
.global GDT64DescriptorStart
GDT64DescriptorStart:
	.quad .gdt64Start
