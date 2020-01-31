.code16
.section .text
.org 0x0

/// Read from disk
///
/// Input:
///  - `DL`: Drive index
///  - `AX`: LBA of first sector to read
///  - `BX`: Number of sectors to read
///  - `CX:SI`: Where to load the sectors
/// Output:
///  - `Carry bit`: clear if successful
.global ReadDiskLBA
ReadDiskLBA:
	PUSHA

	MOVW %AX, .DAPTargetSector
	MOVW %BX, .DAPSectors
	MOVW %CX, .DAPTargetPointerSegment
	MOVW %SI, .DAPTargetPointerOffset
	MOVB $0x42, %AH
	LEAW .DiskAddressPacket, %SI
	INT $0x13

	# TODO: Handle return code on error (in AH)

	POPA
	RET


.section .data

.DiskAddressPacket:
	.byte 0x10			// Size of DAP
	.byte 0				// Unused (zero)
.DAPSectors:
	.word 0				// Number of sectors to read (max 127)
.DAPTargetPointerOffset:
	.word 0				// Output buffer offset
.DAPTargetPointerSegment:
	.word 0				// Output buffer segment
.DAPTargetSector:
	.quad 0				// LBA of first sector to read
