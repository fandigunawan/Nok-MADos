/* 
simple memmap for dsp shared mem loader 
merge data and code sections..
*/
MEMORY {
    ram(RWXAIL) : ORIGIN = 0xF00, LENGTH = 256
}

SECTIONS {
    .text : { 
	*(.text)
	*(.data) 
    } > ram
}
