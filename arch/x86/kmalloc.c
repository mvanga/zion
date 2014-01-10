#include <zion/stdlib.h>

#include <arch/kmalloc.h>
#include <arch/config.h>

unsigned int alloc_pos;
extern unsigned int __phys_begin;

void arch_kmalloc_init(void)
{
	alloc_pos = (unsigned int)&__phys_begin;
}

void *kmalloc_unsafe(unsigned int size, unsigned int flags)
{
	unsigned int ret;

	/* Check if memory alignment is requested */
	if ((flags & KERN_ALIGN) && (alloc_pos & 0xfffff000)){
		alloc_pos &= 0xfffff000;
		alloc_pos += 4096;
	}

	/* If we go past the 4MB that we mapped, error! */
	if (alloc_pos + size > 0xc0400000)
		return NULL;

	ret = alloc_pos;
	alloc_pos += size;

	/* If the physical address is requested, adjust the address */
	if (flags & KERN_PHYS)
		return (void *)(ret - KERNEL_VMA);

	return (void *)ret;
}
