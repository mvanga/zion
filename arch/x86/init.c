#include <zion/types.h>
#include <zion/stdio.h>

#include <arch/early_printk.h>
#include <arch/segment.h>
#include <arch/timer.h>

extern int main();

int arch_main(uint32_t magic, unsigned int *mb_info)
{
	early_printk_init();
	printk("Hello world! 0x%08x\n", magic);

	gdt_init();
	idt_init();

	timer_init();

	asm volatile ("sti");

	return main();
}
