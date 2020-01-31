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

	# Call kernel
	JMP $LOAD_SEGMENT, $Start

DiskReadError:
	LEAW strDiskReadError, %SI
	CALL PrintString
	JMP Halt

Halt:
	CLI
	HLT
	JMP Halt

.section .data

strStage2:
	.asciz "\r\nStarting Stage 2\r\n"
strDiskRead:
	.asciz "Read kernel from disk\r\n"
strDiskReadError:
	.asciz "Disk read failed.\r\n"
