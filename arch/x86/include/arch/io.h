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

#ifndef ZION_ASM_IO_H
#define ZION_ASM_IO_H

#include <zion/types.h>

/* Basic port I/O */
static inline void outb(uint8_t v, uint16_t port)
{
	asm volatile("outb %0,%1" : : "a" (v), "dN" (port));
}
static inline uint8_t inb(uint16_t port)
{
	uint8_t v;
	asm volatile("inb %1,%0" : "=a" (v) : "dN" (port));
	return v;
}

static inline void outw(uint16_t v, uint16_t port)
{
	asm volatile("outw %0,%1" : : "a" (v), "dN" (port));
}
static inline uint16_t inw(uint16_t port)
{
	uint16_t v;
	asm volatile("inw %1,%0" : "=a" (v) : "dN" (port));
	return v;
}

static inline void outl(uint32_t v, uint16_t port)
{
	asm volatile("outl %0,%1" : : "a" (v), "dN" (port));
}
static inline uint32_t inl(uint32_t port)
{
	uint32_t v;
	asm volatile("inl %1,%0" : "=a" (v) : "dN" (port));
	return v;
}

#endif
