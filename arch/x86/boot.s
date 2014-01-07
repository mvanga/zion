#include <arch/config.h>

.extern arch_main

.equ MBOOT_PAGE_ALIGN,    1<<0
.equ MBOOT_MEM_INFO,      1<<1
.equ MBOOT_HEADER_MAGIC,  0x1badb002
.equ MBOOT_HEADER_FLAGS,  MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
.equ MBOOT_CHECKSUM,      -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

/* The multiboot header structure goes in the beginning of code segment */
.section .text
.code32
.align 4
.globl mboot
mboot:
	.long MBOOT_HEADER_MAGIC
	.long MBOOT_HEADER_FLAGS
	.long MBOOT_CHECKSUM

/* Reserve space for the boot page table/page directory */
.section .data
.align 0x1000
kpage_dir:
	.space 0x1000, 0x00
kpage_table_main:
	.space 0x1000, 0x00
kpage_table_stack:
	.space 0x1000, 0x00

.section .text
.equ start_phys, (start - 0xc0000000)
.globl start_phys
start:
	/* Save the multiboot magic and info structure on GRUB stack */
	pushl %eax
	pushl %ebx

	/* Initialize the main page table for the kernel */
	movl $kpage_table_main, %eax
	subl $KERNEL_VMA, %eax
	mov $0x3, %ebx
	mov $0x400, %ecx
fill_pt:
	movl %ebx, (%eax)
	addl $0x1000, %ebx
	addl $0x4, %eax
	loop fill_pt

	/* Initialize the stack page table for the kernel */
	movl $kpage_table_stack, %eax
	subl $KERNEL_VMA, %eax
	addl $0xffc, %eax
	movl $sys_stack, %ebx
	subl $KERNEL_VMA, %ebx
	orl $0x3, %ebx
	movl %ebx, (%eax)

	/* Load the physical address of the page directory */
	movl $kpage_dir, %eax
	subl $KERNEL_VMA, %eax

	/* Set up page directory entry for low and high pt */
	movl $kpage_table_main, %ebx
	subl $KERNEL_VMA, %ebx
	orl $0x1, %ebx

	/* Set first entry in page directory */
	movl %ebx, (%eax)

	/* Set the 768th entry in page directory */
	addl $0xc00, %eax
	movl %ebx, (%eax)

	/* Load the physical address of the page directory */
	movl $kpage_dir, %eax
	subl $KERNEL_VMA, %eax
	/* Set up page directory entry for kernel stack pt */
	movl $kpage_table_stack, %ebx
	subl $KERNEL_VMA, %ebx
	orl $0x1, %ebx

	/* Set the 895th entry in pagedir (stack grows down at 0xe0000000 */
	addl $0xdfc, %eax
	movl %ebx, (%eax)

	/* Load physical address of kernel page dir into cr3 */
	movl $kpage_dir, %ebx
	subl $KERNEL_VMA, %ebx
	movl %ebx, %cr3

	/* Set the paging bit in cr0 */
	movl %cr0, %ebx
	orl $0x80000000, %ebx
	movl %ebx, %cr0

	/* Pop back multiboot info from stack */
	popl %ebx
	popl %eax

	/* jump to the higher half kernel */
	jmp $0x08, $higherhalf

higherhalf:
	/* Unmap the first 4MB of memory (we don't need it anymore) */
	movl $kpage_dir, %ecx
	movl $0x0, (%ecx)
	invlpg 0

	/* Load the stack we mapped earlier */
	mov $0xe0000000, %esp

	/* Push the multiboot information onto the stack */
	pushl %ebx
	pushl %eax

	/* Call arch main */
	call arch_main

hang:
	jmp hang


.section .bss
.align 32
.skip 0x2000
sys_stack:
