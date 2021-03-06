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

#include <arch/regs.h>
#include <arch/io.h>
#include <arch/irq.h>

isr_t irq_handlers[256];

void irq_disable(unsigned char irq)
{
	uint16_t port;
	uint8_t value;

	if (irq < 8) {
		port = 0x21;
	} else {
		port = 0xa1;
		irq -= 8;
	}
	value = inb(port) | (1 << irq);
	outb(port, value);        
}

void irq_enable(unsigned char irq)
{
	uint16_t port;
	uint8_t value;

	if (irq < 8) {
		port = 0x21;
	} else {
		port = 0xa1;
		irq -= 8;
	}
	value = inb(port) & ~(1 << irq);
	outb(port, value);        
}

void request_exception(int n, isr_t handler)
{
	if (n >= 32)
		return;
	irq_handlers[n] = handler;
}

void request_irq(int n, isr_t handler)
{
	irq_handlers[n+32] = handler;
	irq_enable(n);
}

void dump(struct regs *r)
{
	printk("  ds = %p, edi = %p, esi = %p, ebp = %p\n", r->ds, r->edi, r->esi, r->ebp);
	printk(" esp = %p, ebx = %p, edx = %p, ecx = %p\n", r->esp, r->ebx, r->edx, r->ecx);
	printk(" eax = %p, int = %p, err = %p,  ss = %p\n", r->eax, r->int_no, r->err_code, r->ss);
	printk("uesp = %p, efl = %p,  cs = %p, eip = %p\n", r->useresp, r->eflags, r->cs, r->eip);
}

void isr_handler(struct regs *regs)
{
	printk("caught exception: 0x%X error=%p\n", regs->int_no, regs->err_code);
	dump(regs);
	if (irq_handlers[regs->int_no])
		(irq_handlers[regs->int_no])(regs);
	else
		printk("no handler available\n");
	for (;;);
}

void irq_handler(struct regs *regs)
{
	if (irq_handlers[regs->int_no])
		(irq_handlers[regs->int_no])(regs);
	if (regs->int_no >= 40)
		outb(0x20, 0xa0);
	outb(0x20, 0x20);
}
