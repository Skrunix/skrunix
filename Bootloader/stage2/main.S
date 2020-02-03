.code16
.section .text
.org 0x0

# TODO: Determine later
.set LBA_TO_LOAD, 11
# TODO: Determine later
.set SECTORS_TO_LOAD, 10

# Where the kernel should be loaded
.set LOAD_SEGMENT, 0x1000

Start:
	MOVW $0x07C0, %AX
	MOVW %AX, %DS
	LEAW strStage2, %SI
	CALL PrintString

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

	# Play with A20 line
	CALL A20Status
	CALL EnableA20
	CALL A20Status
	CALL DisableA20
	CALL A20Status
	CALL EnableA20
	CALL A20Status
	
	# Get memory map
	CALL DetectMemory

	LEAW strProtectedJump, %SI
	CALL PrintString

	# Load GDT and jump to Protected mode
	CLI
	XORL %EAX, %EAX
	MOVW %DS, %AX
	SHLL $4, %EAX
	ADDL GDTDescriptorStart, %EAX
	MOVL %EAX, GDTDescriptorStart
	LGDT GDTDescriptor
	MOVL %CR0, %EAX
	ORB $0x1, %AL
	MOVL %EAX, %CR0
	LJMP $0x08, $Start32

DiskReadError:
	LEAW strDiskReadError, %SI
	CALL PrintString
	JMP Halt

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
	
	MOVL $0x400, %EAX
	MOVL %EAX, %ESP
	MOVL %EAX, %EBP

	MOVL $1920, %EDX
	LEAL strProtectedMode, %ESI
	CALL PrintString32

	# Call kernel
	MOVL $0x1000, %EAX
	MOVL %EAX, %ESP
	MOVL %EAX, %EBP
	MOVL $0x20, %EAX
	MOVW %AX, %DS
	MOVW %AX, %ES
	MOVW %AX, %FS
	MOVW %AX, %GS
	MOVW %AX, %SS
	JMP $0x18, $Start


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
