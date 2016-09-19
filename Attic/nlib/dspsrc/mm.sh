#!/bin/bash

tic54x-as -mcpu=545 $1.s -o $1.o
tic54x-ld $1.o -T ../res/memmap.dsp -o $1.elf
tic54x-objcopy -O binary $1.elf $1.bin
../script/halfwordify.py $1.bin $1.hex
