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
#include <zion/jiffies.h>
#include <zion/stdio.h>

#include <arch/irq.h>
#include <arch/regs.h>
#include <arch/io.h>

static void timer_handler(struct regs *regs __attribute__((unused)))
{
	jiffies++;
}

int timer_init(void)
{
	uint32_t divisor;

	request_irq(0, &timer_handler);

	divisor = 1193180 / HZ;
	outb(0x36, 0x43);
	outb(divisor & 0xff, 0x40);
	outb((divisor >> 8) & 0xff, 0x40);

	return 0;
}
