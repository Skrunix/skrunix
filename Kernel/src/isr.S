.code64
.section .text
.org 0x0
.altmacro

.global flushIDT
flushIDT:
	MOVQ %RDI, %RAX
	LIDT (%RAX)
	RET

isrStub:
	# TODO:
	CALL isrHandler

	STI
	IRETQ

.macro INT_HANDLER number:req
isr\number:
	CLI
	MOVQ $\number, %RDI
	JMP isrStub
.endm

.macro INT_HANDLERS count:req
.set i, 0
.rept \count
	INT_HANDLER %i
	.set i, i + 1
.endr
.endm

INT_HANDLERS 256


.section .data

.macro ISR_ADDRESS number:req
	.quad isr\number
.endm

.global DefaultIntHandlers
DefaultIntHandlers:
.set i, 0
.rept 256
	ISR_ADDRESS %i
	.set i, i + 1
.endr
