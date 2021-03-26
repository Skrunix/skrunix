#!/usr/bin/env python3

import sys

if len(sys.argv) != 2:
	print("usage: {} <seg>:<offset>".format(sys.argv[0]))
	sys.exit(1)

segOff = sys.argv[1].split(':')
segment = int(segOff[0], 16)
offset = int(segOff[1], 16)

print("Physical Address: 0x{:02X}".format((segment << 4) + offset))
