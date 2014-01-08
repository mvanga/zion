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

#ifndef ARCH_X86_ASM_IRQ_H
#define ARCH_X86_ASM_IRQ_H

#include <arch/regs.h>

typedef void (*isr_t)(struct regs *);
extern isr_t irq_handlers[256];

void request_exception(int n, isr_t handler);
void request_irq(int n, isr_t handler);
void irq_disable(unsigned char irq);
void irq_enable(unsigned char irq);

#endif
