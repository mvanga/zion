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

#include <arch/segment.h>
#include <zion/types.h>

extern void gdt_write(uint32_t);

struct gdt_ptr gdt_ptr;
struct gdt_entry gdt_table[5];

void gdt_set(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt_table[num].base_low = (base & 0xFFFF);
	gdt_table[num].base_middle = (base >> 16) & 0xFF;
	gdt_table[num].base_high = (base >> 24) & 0xFF;

	gdt_table[num].limit_low = (limit & 0xFFFF);
	gdt_table[num].granularity = (limit >> 16) & 0x0F;

	gdt_table[num].granularity |= gran & 0xF0;
	gdt_table[num].access = access;
}

void gdt_init(void)
{
	gdt_ptr.limit = (sizeof(uint64_t) * 3) - 1;
	gdt_ptr.base  = (uint32_t)&gdt_table;

	gdt_set(0, 0, 0, 0, 0);			/* Null segment */ 
	gdt_set(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);	/* Code segment */ 
	gdt_set(2, 0, 0xFFFFFFFF, 0x92, 0xCF);	/* Data segment */ 

	gdt_write((uint32_t)&gdt_ptr);
}
