#!/usr/bin/python
import struct
import sys
name = sys.argv[1]

file = open(name+".hex","r")

line = ""

while 1:
	x = file.readline()
	if not x:
		break
	x = x[0:-1]
	line += x
file.close()

ptr = 0
packed = ""
while 1:
	try:
		xpos = line.index('x', ptr)
	except ValueError:
		break
	try:
		comma = line.index(',', ptr)
	except ValueError:
		comma = len(line)
	x = int(line[xpos+1:comma], 16)
	packed += struct.pack("<H", x);
	ptr = comma + 1


file = open(name+".bin", "wb")
file.write(packed)
file.close()
