#!/usr/bin/env python3

import sys

if len(sys.argv) != 2:
	print("usage: {} <0xaddress>".format(sys.argv[0]))
	sys.exit(1)

addressString = sys.argv[1]
if addressString.startswith("0x"):
	addressString = addressString[2:]

address = int(addressString, 16)


offset = address & 0xFFF
address >>= 12

pdIndex = address & 0x1FF
address >>= 9

pdtIndex = address & 0x1FF
address >>= 9

pdptIndex = address & 0x1FF
address >>= 9

pml4tIndex = address & 0x1FF
address >>= 9

pml5tIndex = address & 0x1FF
address >>= 9

print("PML5T PML4T  PDPT   PDT    PD  OFFSET")
print("{:>5} {:>5} {:>5} {:>5} {:>5}   {:>5}".format(pml5tIndex, pml4tIndex, pdptIndex, pdtIndex, pdIndex, offset))
