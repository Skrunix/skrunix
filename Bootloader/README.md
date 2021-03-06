# Bootloader

## Stage1

446 bytes (in the MBR header) that locate, load, and execute Stage2

## Stage2

A larger block of code that:

- Locate and load the Kernel
- Enable A20
- Detect Memory
- Load a GDT
- Enter Protected mode
- Detect CPUID
- Load a GDT (64 bit)
- Enable paging
- Enter Long mode
- Execute Kernel

# Memory Map

## Usable memory for bootloader

| Start      | End        | Use         |
|------------|------------|-------------|
| 0x00000500 | 0x00007BFF | free        |
| 0x00007C00 | 0x00007DFF | boot sector |
| 0x00007E00 | 0x0007FFFF | free        |
| 0x000A0000 | 0x000BFFFF | video       |
| 0x00100000 | 0x00EFFFFF | free        |
| 0x01000000 | 0xC0000000 | free        |

## Usable memory after bootloader

| Start      | End        | Use             |
|------------|------------|-----------------|
| 0x00000000 | 0x000004FF | free            |
| 0x00000500 | 0x000006FF | boot sector (f) |
|*0x00000500 | 0x00000508 | k-end ptr (r)   |
| 0x00000700 | -          | stage 2 (f)     |
| -          | - (4K)     | page table (r)  |
| -          | - (4K)     | page table (r)  |
| -          | - (4K)     | page table (r)  |
| -          | - (4K)     | page table (r)  |
| -          | -          | mem map (f)     |
| -          | 0x0000FFFF | stack (f)       |
| 0x00010000 | 0x0001FFFF | kernel load (f) |
| 0x00020000 | 0x0008FFFF | free            |
| 0x00090000 | 0x0009FFFF | scratch (f)     |
| 0x000A0000 | 0x000BFFFF | video           |
| 0x00100000 | -          | kernel          |

###### `(f)` is free to use after the bootloader
###### `(r)` can be reclaimed after seting up page tables
