/*
 * Zion: a capability-based microkernel for real-time systems
 * Copyright (C) 2013 Manohar vanga
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
*/

#include <zion/types.h>
#include <zion/stdio.h>

#include <arch/early_printk.h>
#include <arch/segment.h>
#include <arch/timer.h>
#include <arch/kmalloc.h>

extern int main();
extern unsigned int __phys_begin;

int arch_main(uint32_t magic, unsigned int *mb_info)
{
	early_printk_init();
	printk("Hello world! 0x%08x\n", magic);

	gdt_init();
	idt_init();

	/* Set up basic arch malloc (unsafe) */
	arch_kmalloc_init();

	timer_init();
	asm volatile ("sti");

	return main();
}
