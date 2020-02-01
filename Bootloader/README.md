# Bootloader

## Stage1

446 bytes (in the MBR header) that locate, load, and execute Stage2

## Stage2

A larger block of code that:

- Locate and load the Kernel
- Enable A20
- Detect Memory
- Execute Kernel
