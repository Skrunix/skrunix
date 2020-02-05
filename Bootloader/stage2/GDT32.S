.code16
.section .text
.org 0x0


.section .data

.gdt32Start:
	.long 0
	.long 0

.gdt32BootloaderCode:
	.word 0xFFFF # Limit 0:15
	.word 0x7C00 # Base 0:15
	.byte 0x00 # Base 16:23
	.byte 0b10011010 # Access Byte
	.byte 0b11001111 # Flags | Limit 16:19
	.byte 0x00 # Base 24:31

.gdt32BootloaderData:
	.word 0xFFFF # Limit 0:15
	.word 0x7C00 # Base 0:15
	.byte 0x00 # Base 16:23
	.byte 0b10010010 # Access Byte
	.byte 0b11001111 # Flags | Limit 16:19
	.byte 0x00 # Base 24:31

.gdt32End:

.global GDT32Descriptor
GDT32Descriptor:
	.word .gdt32End - .gdt32Start - 1
.global GDT32DescriptorStart
GDT32DescriptorStart:
	.long .gdt32Start
