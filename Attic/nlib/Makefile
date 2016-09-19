TOPDIR = .
include Makefile.global

all: src res test

src:
	make -C src

res:
	make -C res

test:
	make -C test

dspsrc:
	make -C dspsrc

clean:
	make -C src clean
	make -C res clean
	make -C test clean

.PHONY: src res test dspsrc
