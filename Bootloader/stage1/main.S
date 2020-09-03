.code16
.section .text
.org 0x0

# TODO: Determine later
.set BYTES_PER_SECTOR, 512
# TODO: Determine later
.set LBA_TO_LOAD, 1
# TODO: Determine later
.set SECTORS_TO_LOAD, 10
# Moving words is twice as fast as moving bytes
.set WORDS_TO_RELOCATE, BYTES_PER_SECTOR >> 1

# End of free space
.set STACK_SEGMENT, 0x0070
.set STACK_SIZE, 0x9900
# Where the MBR is loaded
.set BOOT_SEGMENT, 0x07C0
# Where to move stage1
.set RELOCATE_SEGMENT, 0x0050
# Where to load stage2
.set STAGE2_SEGMENT, 0x0070

Start:
	CLI
Relocate:
	# From segment
	MOVW $BOOT_SEGMENT, %AX
	MOVW %AX, %DS
	# To segment
	MOVW $RELOCATE_SEGMENT, %AX
	MOVW %AX, %ES
	# Set relocation counter
	MOVW $WORDS_TO_RELOCATE, %CX
	# Clear offsets
	XOR %SI, %SI
	XOR %DI, %DI
	# Do the move
	REP MOVSW
	# Long jump to the new code location
	LJMP $RELOCATE_SEGMENT, $Segmentation

Segmentation:
	# Point `DS` to the new code location
	MOVW %AX, %DS
	# Prepare the stack
	MOVW $STACK_SIZE, %AX
	MOVW %AX, %BP
	MOVW %AX, %SP
	MOVW $STACK_SEGMENT, %AX
	MOVW %AX, %SS

	# Enable interrupts
	STI

Stage1:
	LEAW strStage1, %SI
	CALL PrintString

	# Check for disk extensions
	CALL CheckDiskExtensions
	JC DiskExtensionsError
	LEAW strDiskExtensions, %SI
	CALL PrintString

	# Load stage 2
	MOVW $STAGE2_SEGMENT, %AX
	MOVW %AX, %CX
	MOVW $0, %AX
	MOVW %AX, %SI
	MOVW $LBA_TO_LOAD, %AX
	MOVW $SECTORS_TO_LOAD, %BX
	CALL ReadDiskLBA
	JC DiskReadError
	LEAW strDiskRead, %SI
	CALL PrintString

	# Call stage 2
	JMP $STAGE2_SEGMENT, $Start

DiskExtensionsError:
	LEAW strDiskExtensionsError, %SI
	CALL PrintString
	JMP Halt

DiskReadError:
	LEAW strDiskReadError, %SI
	CALL PrintString
	JMP Halt

Halt:
	CLI
	HLT
	JMP Halt


.section .data

strStage1:
	.asciz "\r\nStarting Stage 1\r\n"
strDiskExtensions:
	.asciz "BIOS disk extensions found\r\n"
strDiskExtensionsError:
	.asciz "BIOS does not support disk extensions addressing.\r\n"
strDiskRead:
	.asciz "Read stage 2 from disk\r\n"
strDiskReadError:
	.asciz "Disk read failed.\r\n"
