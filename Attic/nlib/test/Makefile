TOPDIR = ..

include $(TOPDIR)/Makefile.global

OBJECTS = test.o

test.bin: test.elf
	$(OBJCOPY) -O binary test.elf test.bin

test.elf : $(OBJECTS)
	ln -sf ../src/crt0.o .
	$(CC) $(CFLAGS_LINK) $(OBJECTS) -lnlib -o test.elf
	$(OBJDUMP) -D test.elf >test.lst

clean:
	rm $(OBJECTS) test.bin test.elf test.lst crt0.o
