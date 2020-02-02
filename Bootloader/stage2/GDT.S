.code16
.section .text
.org 0x0


.section .data

.gdtStart:
	.long 0
	.long 0

.gdtBootloaderCode:
	.word 0xFFFF # Limit 0:15
	.word 0x7C00 # Base 0:15
	.byte 0x00 # Base 16:23
	.byte 0b10011010 # Access Byte
	.byte 0b11001111 # Flags | Limit 16:19
	.byte 0x00 # Base 24:31

.gdtBootloaderData:
	.word 0xFFFF # Limit 0:15
	.word 0x7C00 # Base 0:15
	.byte 0x00 # Base 16:23
	.byte 0b10010010 # Access Byte
	.byte 0b11001111 # Flags | Limit 16:19
	.byte 0x00 # Base 24:31

.gdtKernelTempCode:
	.word 0xFFFF # Limit 0:15
	.word 0x0000 # Base 0:15
	.byte 0x01 # Base 16:23
	.byte 0b10011010 # Access Byte
	.byte 0b11001111 # Flags | Limit 16:19
	.byte 0x00 # Base 24:31

.gdtKernelTempData:
	.word 0xFFFF # Limit 0:15
	.word 0x0000 # Base 0:15
	.byte 0x01 # Base 16:23
	.byte 0b10010010 # Access Byte
	.byte 0b11001111 # Flags | Limit 16:19
	.byte 0x00 # Base 24:31


.gdtEnd:

.global GDTDescriptor
GDTDescriptor:
	.word .gdtEnd - .gdtStart - 1
.global GDTDescriptorStart
GDTDescriptorStart:
	.long .gdtStart
