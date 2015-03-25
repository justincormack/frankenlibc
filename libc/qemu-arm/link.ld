ENTRY(_Reset)
SECTIONS
{
	. = 0x10000;
	.startup . : { startup.o(.text) }
	.text : { *(.text) }
	.data : { *(.data) }
	.bss : { *(.bss COMMON) }
	. = ALIGN(8);
	. = . + 0x10000; /* 64kB stack */
	stack_top = .;
}
