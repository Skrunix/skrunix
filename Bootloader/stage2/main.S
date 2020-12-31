.code16
.section .text
.org 0x0

# TODO: Determine later
.set BYTES_PER_SECTOR, 512
# TODO: Determine later
.set LBA_TO_LOAD, 11
# TODO: Determine later
.set SECTORS_TO_LOAD, 80

# Where the kernel should be loaded
.set LOAD_SEGMENT, 0x1000
.set KERNEL_OLD, 0x10000 - 0x0700
.set KERNEL_START, 0x100000 - 0x0700
# Moving longs is four times as fast as moving bytes
.set LONGS_TO_MOVE, SECTORS_TO_LOAD * (BYTES_PER_SECTOR >> 2)

Start:
	MOVW $0x0070, %AX
	MOVW %AX, %DS
	LEAW strStage2, %SI
	CALL PrintString

	# Play with A20 line
	CALL A20Status
	CALL EnableA20
	CALL A20Status
	CALL DisableA20
	CALL A20Status
	CALL EnableA20
	CALL A20Status

	# Load kernel
	MOVW $LOAD_SEGMENT, %AX
	MOVW %AX, %CX
	MOVW $0, %AX
	MOVW %AX, %SI
	MOVW $LBA_TO_LOAD, %AX
	MOVW $SECTORS_TO_LOAD, %BX
	CALL ReadDiskLBA
	JC DiskReadError
	LEAW strDiskRead, %SI
	CALL PrintString
	# Get memory map
	CALL DetectMemory

	LEAW strProtectedJump, %SI
	CALL PrintString

	# Load GDT32 and jump to Protected mode
	CLI
	XORL %EAX, %EAX
	MOVW %DS, %AX
	SHLL $4, %EAX
	ADDL GDT32DescriptorStart, %EAX
	MOVL %EAX, GDT32DescriptorStart
	LGDT GDT32Descriptor
	MOVL %CR0, %EAX
	ORB $0x1, %AL
	MOVL %EAX, %CR0
	LJMP $0x08, $Start32

DiskReadError:
	LEAW strDiskReadError, %SI
	CALL PrintString
	JMP Halt

.global Halt
Halt:
	CLI
	HLT
	JMP Halt


.code32

Start32:
	MOVL $0x10, %EAX
	MOVW %AX, %DS
	MOVW %AX, %ES
	MOVW %AX, %FS
	MOVW %AX, %GS
	MOVW %AX, %SS

	MOVL $1920, %EDX
	LEAL strProtectedMode, %ESI
	CALL PrintString32

	# Copy kernel from $KERNEL_OLD to $KERNEL_START
	MOVL $0, %EDX
	LEAW strCopyKernelHigh, %SI
	CALL PrintString32
	# From address
	MOVL $KERNEL_OLD, %EAX
	MOVL %EAX, %ESI
	# To address
	MOVL $KERNEL_START, %EAX
	MOVL %EAX, %EDI
	# Set relocation counter
	MOVL $LONGS_TO_MOVE, %ECX
	# Do the move
	REP MOVSL
	# Restore ESI
	XOR %ESI, %ESI

	# Detect and use CPUID to detect long mode
	CALL DetectCPUID
	JC NoCPUID
	MOVL $80, %EDX
	LEAW strCPUID, %SI
	CALL PrintString32

	CALL DetectLongMode
	JC NoLongMode
	MOVL $160, %EDX
	LEAW strLongMode, %SI
	CALL PrintString32

	# Setup Long mode paging
	CALL Paging64
	MOVL $240, %EDX
	LEAW strPagingEnabled, %SI
	CALL PrintString32

	# Switch to (long) compatibility mode
	MOVL $0xC0000080, %ECX
	RDMSR
	ORL $1<<8, %EAX
	WRMSR
	# Enable paging
	MOVL %CR0, %EAX
	ORL $1<<31, %EAX
	MOVL %EAX, %CR0

	# Load GDT64 and jump to Long mode
	CLI
	XORL %EAX, %EAX
	# TODO: Get this value from DS somehow
	MOVW $0x0700, %AX
	ADDL GDT64DescriptorStart, %EAX
	MOVL %EAX, GDT64DescriptorStart
	LGDT GDT64Descriptor
	LJMP $0x08, $Start64+0x0700


.code64

Start64:
	CLI

	# Stack no longer uses segments
	MOVL $0xA000, %EAX
	MOVL %EAX, %ESP
	MOVL %EAX, %EBP

	MOV $0x10, %RAX
	MOVW %AX, %DS
	MOVW %AX, %ES
	MOVW %AX, %FS
	MOVW %AX, %GS
	MOVW %AX, %SS

	MOVL $320, %EDX
	MOVQ $strInLongMode, %RAX
	ADDQ $0x0700, %RAX # Data no longer uses segments
	MOVQ %RAX, %RSI
	MOVQ $PrintString64, %RAX
	ADDQ $0x0700, %RAX # Code no longer uses segments
	CALL *%RAX

	# Load kernel segments
	MOVQ $0x20, %RAX
	MOVW %AX, %DS
	MOVW %AX, %ES
	MOVW %AX, %FS
	MOVW %AX, %GS
	MOVW %AX, %SS

	# Jump to kernel
	PUSHQ $0x18
	MOVABSQ $0xFFFF800000100000, %RAX
	PUSHQ %RAX
	LRETQ

NoCPUID:
	MOVL $80, %EDX
	LEAW strNoCPUID, %SI
	CALL PrintString32
	JMP Halt32

NoLongMode:
	MOVL $160, %EDX
	LEAW strNoLongMode, %SI
	CALL PrintString32
	JMP Halt32

Halt32:
	CLI
	HLT
	JMP Halt32


.section .data

strStage2:
	.asciz "\r\nStarting Stage 2\r\n"
strProtectedJump:
	.asciz "\r\nSwitching to protected mode...\r\n"
strProtectedMode:
	.asciz "Protected mode enabled!"
strDiskRead:
	.asciz "Read kernel from disk\r\n"
strDiskReadError:
	.asciz "Disk read failed.\r\n"
strCopyKernelHigh:
	.asciz "Copying kernel to high memory..."
strCPUID:
	.asciz "CPUID supported"
strNoCPUID:
	.asciz "No CPUID support"
strLongMode:
	.asciz "Long mode supported"
strNoLongMode:
	.asciz "No long mode support"
strPagingEnabled:
	.asciz "Paging enabled           "
strInLongMode:
	.asciz "In long mode"
