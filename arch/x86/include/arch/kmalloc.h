#ifndef ZION_ARCH_X86_MEM_H
#define ZION_ARCH_X86_MEM_H

#define KERN_ALIGN	(1 << 0)
#define KERN_PHYS	(1 << 1)

void arch_kmalloc_init(void);
void *kmalloc_unsafe(unsigned int size, unsigned int flags);

#endif
