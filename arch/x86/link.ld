ENTRY(start_phys)
KERNEL_VMA = 0xc0000000;

SECTIONS
{
	. = 0x100000;
	.setup : {
		*(.setup)
	}

	. += 0xC0000000;

	.text : AT(ADDR(.text) - 0xC0000000) {
		*(.text)
		__text_end = .;
	}

	.data ALIGN(4096) : AT(ADDR(.data) - 0xC0000000) {
		*(.data)
		*(.rodata)
	}
	. = ALIGN(4096);

	.bss ALIGN(4096) : AT(ADDR(.bss) - 0xC0000000) {
		bss = .;
		*(.bss)
	}
	__phys_begin = .;
}
