TOPDIR = ..

include ../Makefile.global

#OBJECTS = test.o
LIBOBJECTS = nokio.o dsp.o flashdbg.o gensio.o ptimer.o lights.o ccont.o lcd.o interrupt.o dspblocks.o

all: crt0.o libnlib.a

libnlib.a : $(LIBOBJECTS)
	$(AR) csr libnlib.a $(LIBOBJECTS)

crt0.o : crt0.s
	$(GAS) $(GOPS) crt0.s -o crt0.o

clean:
	rm $(LIBOBJECTS) libnlib.a crt0.o
